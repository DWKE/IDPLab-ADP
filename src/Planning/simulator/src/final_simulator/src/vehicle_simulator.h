#ifndef VEHICLE_SIMULATOR_H
#define VEHICLE_SIMULATOR_H

#include "autonomous_msg/VehicleInput.h"
#include "visualization_msgs/Marker.h"
#include <geometry_msgs/Pose.h>
#include <ros/ros.h>
#include <string>
#include <tf/transform_broadcaster.h>
#include "kusv_msgs/State.h"

#define PI 3.14159265358979323846 /* pi */

class Vehicle {
protected:
  ros::NodeHandle m_rosNodeHandler;
  ros::Publisher m_rosPubVehicle_output;
  ros::Publisher m_rosPubVehicle_output_global;
  ros::Publisher m_rosPubVehiclePose;
  ros::Subscriber m_rosSubVehicle_Input;
  ros::Publisher vehicle_state_pub;
  
  //tf::TransformBroadcaster m_rosTfBroadcaster;
  ros::Publisher m_rosPubVehicleMarker;

  std::string m_vehicle_namespace;
  kusv_msgs::State vehicle_state;

  double m_dAccelInput = 0.0;
  double m_dBrakeInput = 0.0;
  double m_dFrontAngle_rps = 0.0;

  double m_dDt = 0.0;
  double m_dPrevTime;

  double m_a = 6378137.0;       // semi-major axis [m]
  double m_b = 6356752.314245;  // semi-minor axis [m]

  double m_init_lon = 0.0;
  double m_init_lat = 0.0;
  double m_init_lon_next = 0.0;
  double m_init_lat_next = 0.0; // from two global waypoints to calculate init_yaw

  double m_dX = 0.0;
  double m_dY = 0.0;
  double m_dYaw = 0.0;
  double m_dYawRate = 0.0;
  double m_dSlipAngle = 0.0;
  double m_dVehicleVel_ms = 0;

  double m_dCr = 183350.0; // N/rad
  double m_dCf = 154700.0; // N/rad

  double m_dMass = 250.0;             // kg
  double m_dInertia = 400.0;          // kg*m^2
  double m_dWheelBase = 1.04;      // m
  double m_dLf = 0.54;                // m
  double m_dLr = 0.5;                // m

  double m_dIw = 0.3312; // kg m^2
  double m_dIt = 0.060;  // kg m^2
  double m_dIm = 0.015;  // kg m^2

  double m_dSlope_rad = 0.0 / 180.0 * PI; // rad (=degree/180.0*PI)

  double m_dReff = 0.305;           // m
  double m_dGearRatio = 1.0 / 7.98; // m

  double m_dAccelConst = 293.1872055; // Nm T_motor = accel(0~1)*m_dAccelConst
  double m_dBrakeConst = 4488.075;    // Nm T_Brake = brake(0~1)*m_dAccelConst

  double m_dP = 0.1;
  double m_dI = 0.01;

public:
  Vehicle();
  ~Vehicle();
  /*void setInitialState(double x = 0.0, double y = 0.0, double yaw = 0.0,
                       double speed_mps = 0.0);*/
  void convertInitialState(double init_lon, double init_lat, double init_lon_next, double init_lat_next);
  double MeridionalRadius(double a, double b, double lat);
  double NormalRadius(double a, double b, double lat);
  bool simVehicleModel();
  void simVehicleController(double &aceel_out, double &brake_out);
  void simVehicleLongitudinalModel();
  void simVehicleLateralModel();
  void callback(const autonomous_msg::VehicleInput::ConstPtr &msg);

private:
  //void broadcasting_tf_vehicle();
};

#endif
