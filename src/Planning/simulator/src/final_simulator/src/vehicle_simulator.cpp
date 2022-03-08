/**
 * @file vehicle_model.cpp
 * @author Eunsan Jo (eunsan.mountain@gmail.com)
 * @brief 차량의 움직임에 대한 클래스
 * @details
 * @version 0.1
 * @date 2018-11-16
 *
 * @copyright Copyright (c) 2018
 *
 */

#include "vehicle_simulator.h"
#include "autonomous_msg/AccelBrakeSteering.h"
#include "autonomous_msg/VehicleInput.h"
#include "autonomous_msg/VehicleOutput.h"
#include "autonomous_msg/Control.h"
#include "ublox_msgs/NavPVT.h"
#include "std_msgs/Float64.h"
#include <cmath>
#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <string>
#include <tf/transform_broadcaster.h>
#include <visualization_msgs/MarkerArray.h>
#include <iostream>
#include <string>
#include "kusv_msgs/State.h"

using namespace std;

#define PI 3.14159265358979323846 /* pi */

/**
 * @brief Construct a new Vehicle:: Vehicle object
 *
 * @param vehicle_ID : ck
 */
Vehicle::Vehicle() {
  m_rosPubVehicle_output =
      m_rosNodeHandler.advertise<autonomous_msg::VehicleOutput>(
          "/vehicle_output", 10);
//  m_rosPubVehicle_output_global =
//      m_rosNodeHandler.advertise<autonomous_msg::VehicleOutput>(
//          "/vehicle_output", 10);
  m_rosPubVehiclePose = 
      m_rosNodeHandler.advertise<ublox_msgs::NavPVT>(
		  "/localization/pose_estimation/estimated_state", 10);

  m_rosSubVehicle_Input =
      m_rosNodeHandler.subscribe("vehicle_input", 10, &Vehicle::callback, this);

  vehicle_state_pub = m_rosNodeHandler.advertise<kusv_msgs::State>(
              "/vehicle_state",10);

  //double init_x, init_y, init_yaw; // used for local coordinate
  //double init_lon, init_lat, init_lon_next, init_lat_next; // from two global waypoints to calculate init_yaw
  
  m_rosNodeHandler.param("sim_vehicle/ns", m_vehicle_namespace, std::string(""));
  m_rosNodeHandler.param("sim_vehicle/init_lon", m_init_lon, 0.0);
  m_rosNodeHandler.param("sim_vehicle/init_lat", m_init_lat, 0.0);
  m_rosNodeHandler.param("sim_vehicle/init_lon_next", m_init_lon_next, 0.0);
  m_rosNodeHandler.param("sim_vehicle/init_lat_next", m_init_lat_next, 0.0);
  ROS_INFO("initial lon = %f \n",m_init_lon);
  ROS_INFO("initial lat = %f \n",m_init_lat);
  this->convertInitialState(m_init_lon, m_init_lat, m_init_lon_next, m_init_lat_next);
  //this->setInitialState(m_init_x, m_init_y, m_init_yaw, 0.0);

  m_dDt = 0.0;
  m_dPrevTime = ros::Time::now().toSec();
}

Vehicle::~Vehicle() {}

void Vehicle::callback(const autonomous_msg::VehicleInput::ConstPtr &msg) {
  m_dAccelInput = msg->accel;
  m_dBrakeInput = msg->brake;
  
  if (m_dAccelInput > 1.0) {
    m_dAccelInput = 1.0;
  } else if (m_dAccelInput < -1.0) {
    m_dAccelInput = -1.0;
  }
  if (m_dBrakeInput > 1.0) {
    m_dBrakeInput = 1.0;
  } else if (m_dBrakeInput < 0.0) {
    m_dBrakeInput = 0.0;
  }

  m_dFrontAngle_rps = msg->steering;
}

void Vehicle::convertInitialState(double init_lon, double init_lat, double init_lon_next, double init_lat_next) {
  // convert to local points
  double temp_dX, temp_dY;
  double init_lon_rad, init_lat_rad, init_lon_next_rad, init_lat_next_rad;
  
  init_lon_rad = init_lon * PI / 180.0;
  init_lat_rad = init_lat * PI / 180.0;
  init_lon_next_rad = init_lon_next * PI / 180.0;
  init_lat_next_rad = init_lat_next * PI / 180.0;
  
  m_dX = 0.0; // init_lon -> reference pose X
  m_dY = 0.0; // init_lat -> reference pose Y
  
  temp_dX = (init_lon_next_rad - init_lon_rad)*(this->NormalRadius(m_a, m_b, init_lon_next_rad)*cos(init_lat_next_rad));
  temp_dY = (init_lat_next_rad - init_lat_rad)*(this->MeridionalRadius(m_a, m_b, init_lat_next_rad));
  m_dYaw = atan2(temp_dY, temp_dX); // [rad]
  m_dVehicleVel_ms = 0.0;

}

double Vehicle::MeridionalRadius(double a, double b, double lat){
  return pow(a*b, 2) / sqrt( pow((pow( a*cos(lat), 2) + pow( b*sin(lat), 2 )), 3));
}

double Vehicle::NormalRadius(double a, double b, double lat){
  return (a*a) / sqrt(pow( a*cos(lat), 2 ) + pow( b*sin(lat), 2));
}

bool Vehicle::simVehicleModel() {
  // Calculate dt_ by dividing the previous time and the current time
  m_dDt = ros::Time::now().toSec() - m_dPrevTime;
  if (m_dDt <= 0.0) {
    return false;
  }
  m_dPrevTime = ros::Time::now().toSec();

  this->simVehicleLongitudinalModel();
  this->simVehicleLateralModel();

  // publish vehicle state (local pose, states)
  autonomous_msg::VehicleOutput output;
  output.x = m_dX;
  output.y = m_dY;
  output.yaw = m_dYaw;
  output.velocity = m_dVehicleVel_ms;
  output.id = m_vehicle_namespace;

  vehicle_state.speed_ms = m_dVehicleVel_ms;
  vehicle_state.speed_kmh = m_dVehicleVel_ms*3.6;

  m_rosPubVehicle_output.publish(output);
  vehicle_state_pub.publish(vehicle_state);
  //ROS_INFO("%f %f",output.x, output.y);
  //m_rosPubVehicle_output_global.publish(output);
  
  // publish pose same as estimated pose(lon, lat, heading)
  ublox_msgs::NavPVT vehiclePose;
  double temp_lon_rad, temp_lat_rad;
  double init_lon_rad, init_lat_rad, init_lon_next_rad, init_lat_next_rad;

  init_lon_rad = m_init_lon * PI / 180.0;
  init_lat_rad = m_init_lat * PI / 180.0;
  init_lon_next_rad = m_init_lon_next * PI / 180.0;
  init_lat_next_rad = m_init_lat_next * PI / 180.0;
  
  temp_lon_rad = m_dX/(this->NormalRadius(m_a, m_b, init_lon_next_rad)*cos(init_lat_next_rad)) + init_lon_rad;
  temp_lat_rad = m_dY/(this->MeridionalRadius(m_a, m_b, init_lat_next_rad)) + init_lat_rad;
  cout<<temp_lon_rad<<" "<<temp_lat_rad<<endl;

  vehiclePose.lon = (temp_lon_rad * 180.0 / PI)*10000000.0; // [deg*10000000.0]
  vehiclePose.lat = (temp_lat_rad * 180.0 / PI)*10000000.0; // [deg*10000000.0]
  vehiclePose.heading = m_dYaw * 180.0 / PI *100000;     // [deg*100000]
  //ROS_INFO("%f %f",vehiclePose.lon, vehiclePose.lat);
  cout<<vehiclePose.lon<<" "<<vehiclePose.lat<<endl;
  m_rosPubVehiclePose.publish(vehiclePose);
  return true;
}

void Vehicle::simVehicleLongitudinalModel() {
  /* Longutudinal simulation using accel (0~1) and brake (0~1)
   * TODO: FIX the code below
   * Input: accel(0~1) and brake(0~1)
   * Output: m_dVehicleVel_ms
   */

  if (m_dVehicleVel_ms < 0.0001 && m_dBrakeInput >= 0.0001) {
    m_dVehicleVel_ms = 0.0;
    return;
  }
  if (m_dVehicleVel_ms < 0.0001 && m_dAccelInput <= 0.0001 && m_dAccelInput > 0) {
    m_dVehicleVel_ms = 0.0;
    return;
  }

  double t_motor = m_dAccelConst * m_dAccelInput; // Nm //Minus is for test - jy
  double t_brake = m_dBrakeConst * m_dBrakeInput; // Nm

  double j_m_eq = m_dIm + m_dIt + m_dIw * m_dGearRatio * m_dGearRatio +
                  m_dMass * m_dReff * m_dReff * m_dGearRatio * m_dGearRatio;

  double rollingResistance = 0.015 * m_dMass * 9.81 * cos(m_dSlope_rad);
  if (m_dVehicleVel_ms < 0.0) {
    rollingResistance *= -1.0;
  }
  double aeroDrag =
      0.5 * 1.225 * 0.32 * 1.55 * 1.8 * m_dVehicleVel_ms * m_dVehicleVel_ms;
  double dOmega_motor =
      (t_motor -
       m_dGearRatio * m_dReff *
           (rollingResistance + aeroDrag + m_dMass * 9.81 * sin(m_dSlope_rad)) -
       m_dGearRatio * t_brake) /
      j_m_eq;

  m_dVehicleVel_ms += m_dDt * (m_dReff * (dOmega_motor * m_dGearRatio));
}

void Vehicle::simVehicleLateralModel() {
  /* Dynamics simulation using velocity and steering angle
   * TODO: FIX the code below.
   * Input(Sensors output) : m_dFrontAngle_rps
   * output : pose.position.x, pose.position.y, yaw
   */
  double max_alpha_rad = 7.0 * PI / 180.0;

  double dx = 0.0;
  double dy = 0.0;
  double dslipAngle = 0.0;
  double dyaw = 0.0;
  double dyawrate = 0.0;

  double Fyf = 0.0;
  double Fyr = 0.0;

  if (m_dFrontAngle_rps > 28.0 * PI / 180.0) {
    m_dFrontAngle_rps = 28.0 * PI / 180.0;
  } else if (m_dFrontAngle_rps < -28.0 * PI / 180.0) {
    m_dFrontAngle_rps = -28.0 * PI / 180.0;
  }

  if (fabs(m_dVehicleVel_ms) >= 5.0) // 5.0 || m_dVehicleVel_ms <= -5.0)
  {
    dx = m_dDt * m_dVehicleVel_ms * cos(m_dYaw + m_dSlipAngle);
    dy = m_dDt * m_dVehicleVel_ms * sin(m_dYaw + m_dSlipAngle);

    double alpha_f = m_dFrontAngle_rps - m_dSlipAngle -
                     (m_dLf * m_dYawRate) / (m_dVehicleVel_ms);
    if (alpha_f > max_alpha_rad) {
      alpha_f = max_alpha_rad;
    } else if (alpha_f < -1.0 * max_alpha_rad) {
      alpha_f = -1.0 * max_alpha_rad;
    }
    Fyf = (2 * m_dCf) * alpha_f;

    double alpha_r = -m_dSlipAngle + (m_dLr * m_dYawRate) / (m_dVehicleVel_ms);
    if (alpha_r > max_alpha_rad) {
      alpha_r = max_alpha_rad;
    } else if (alpha_r < -1.0 * max_alpha_rad) {
      alpha_r = -1.0 * max_alpha_rad;
    }
    Fyr = (2 * m_dCr) * alpha_r;

    dslipAngle = m_dDt * (Fyf / (m_dMass * m_dVehicleVel_ms) +
                          Fyr / (m_dMass * m_dVehicleVel_ms) - m_dYawRate);

    dyaw = m_dDt * m_dYawRate;
    dyawrate =
        m_dDt *
        ((2 * m_dLf * m_dCf) / (m_dInertia) *
             (m_dFrontAngle_rps - m_dSlipAngle -
              (m_dLf * m_dYawRate) / (m_dVehicleVel_ms)) -
         (2 * m_dLr * m_dCr) / (m_dInertia) *
             (-m_dSlipAngle + (m_dLr * m_dYawRate) / (m_dVehicleVel_ms)));

    m_dX += dx;
    m_dY += dy;
    m_dSlipAngle += dslipAngle;
    m_dYaw += dyaw;
    m_dYawRate += dyawrate;
  } else {
    m_dSlipAngle = atan((m_dLr * tan(m_dFrontAngle_rps)) / (m_dLf + m_dLr));

    dx = m_dDt * m_dVehicleVel_ms * cos(m_dYaw + m_dSlipAngle);
    dy = m_dDt * m_dVehicleVel_ms * sin(m_dYaw + m_dSlipAngle);

    m_dYawRate = ((m_dVehicleVel_ms * cos(m_dSlipAngle)) / (m_dLf + m_dLr)) *
                 (tan(m_dFrontAngle_rps));
    dyaw = m_dDt * m_dYawRate;

    m_dX += dx;
    m_dY += dy;
    m_dYaw += dyaw;
  }
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "sim_vehicle");
  Vehicle vehicle;
  // The approximate control time is 100 Hz
  ros::Rate loop_rate(100);
  while (ros::ok()) {
    vehicle.simVehicleModel();
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
