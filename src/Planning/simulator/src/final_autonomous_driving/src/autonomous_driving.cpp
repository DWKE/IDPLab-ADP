#include "autonomous_msg/PolyfitLaneDataArray.h"
#include "autonomous_msg/VehicleInput.h"
#include "autonomous_msg/VehicleOutput.h"
#include "autonomous_msg/Control.h"
#include "std_msgs/Float64.h"
#include <cmath>
#include <ros/ros.h>
#include <string>

class AutonomousDriving {
protected:
    ros::NodeHandle m_rosNodeHandler; // node handler
    ros::Publisher m_rosPubVehicleInput; // send to vehicle simulator node

    ros::Subscriber m_rosSubVehicleState; // receive vehicle state from vehicle simulator node
    ros::Subscriber m_rosSubDrivingInput; // receive control input from planning node (gear, brake, steer, speed)

    std::string m_vehicle_namespace_param;

public:
    AutonomousDriving() {
        m_rosSubVehicleState = m_rosNodeHandler.subscribe(
                    "/vehicle_output", 10, &AutonomousDriving::vehicleStateCallback, this);

        m_rosPubVehicleInput =
                m_rosNodeHandler.advertise<autonomous_msg::VehicleInput>(
                    "vehicle_input", 10);

        m_rosSubDrivingInput = m_rosNodeHandler.subscribe(
                    "/control_cmd", 10, &AutonomousDriving::drivingInputCallback, this);

        m_rosNodeHandler.param("autonomous_driving/ns", m_vehicle_namespace_param,
                               std::string(""));
    }
    double m_targetSpeed_ms = 0.0;

    ~AutonomousDriving() {}

protected:
    //autonomous_msg::PolyfitLaneDataArray m_polyLanes;
    autonomous_msg::Control m_drivingInput;
    autonomous_msg::VehicleInput m_vehicleInput;
    //autonomous_msg::PolyfitLaneData m_midPolyLane;
    autonomous_msg::VehicleOutput m_vehicleState;
    //autonomous_msg::VehicleOutput m_lidarOutput;
    //double m_limitSpeed = 0.0;
    //bool isLidarDataExist = false;


public:
    /**
   * @brief Temporary functions for debugging pure pursuit
   *
   * @param VehicleInput accel and brake
   */
    void drivingInputCallback(const autonomous_msg::Control::ConstPtr &msg) {
        m_drivingInput.gear  = msg->gear;  // uint8 0: forward, 1: neutral, 2: backward
        m_drivingInput.speed = msg->speed; // float64 0 ~ 20[km/h]
        m_drivingInput.steer = -msg->steer; // float64 -28 ~ 28[deg]
        m_drivingInput.brake = msg->brake; // uint8 1 ~ 200

        //if(m_drivingInput.gear==2) m_drivingInput.speed=-m_drivingInput.speed;

        if(m_drivingInput.gear==2) {
            m_drivingInput.speed=-m_drivingInput.speed;
            m_drivingInput.steer=-m_drivingInput.steer;
        }

        m_targetSpeed_ms = m_drivingInput.speed / 3.6;
        m_vehicleInput.steering = m_drivingInput.steer * 3.141592 / 180.0; // -28~28[deg] -> (float64) [rad/s]
        if (m_drivingInput.brake < 1) { // uint8 1 ~ 200 -> (float64) 0~1
            m_vehicleInput.brake = 0.0;
        } else {
            m_vehicleInput.brake = ((double)m_drivingInput.brake - 1.0)/199.0;
        }
    }

    void vehicleStateCallback(const autonomous_msg::VehicleOutput::ConstPtr &msg) {
        m_vehicleState = *msg;
        ROS_INFO("Callback");
    }

    void controlVehicleSpeed(double targetSpeed_ms) {
        if (m_drivingInput.gear == 0) { // gear = 0: forward
            double error = targetSpeed_ms - m_vehicleState.velocity;
//            ROS_INFO("targetSpeed_ms = %f \n", targetSpeed_ms);
//            ROS_INFO("m_vehicleState.velocity = %f \n", m_vehicleState.velocity);
//            ROS_INFO("error = %f \n", error);

            if (error > 0) {
                m_vehicleInput.accel = error * 0.1 + 0.08; // accel gain
                m_vehicleInput.brake = 0.0;
            } else {
                m_vehicleInput.accel = 0.0;
                m_vehicleInput.brake = error * (-0.2); // brake gain
            }
        }else if(m_drivingInput.gear == 2) {
            double error = targetSpeed_ms - m_vehicleState.velocity;
            if (error < 0) {
                m_vehicleInput.accel = error * 0.1 + 0.08; // accel gain
                m_vehicleInput.brake = 0.0;
            } else {
                m_vehicleInput.accel = 0.0;
                m_vehicleInput.brake = error * (-0.2); // brake gain
            }
        }

    }

    void publishVehicleInput() { m_rosPubVehicleInput.publish(m_vehicleInput); }
};

int main(int argc, char **argv) {

    ros::init(argc, argv, "sim_controller");

    AutonomousDriving autonomousDriving;

    // double prev_csvLaneMarkTime = ros::Time::now().toSec();
    // The approximate control time is 100 Hz
    ros::Rate loop_rate(100);
    while (ros::ok()) {
        autonomousDriving.controlVehicleSpeed(autonomousDriving.m_targetSpeed_ms);
        /*     autonomousDriving.findDrivingWay();
    autonomousDriving.calcSteeringAngle(); */
        autonomousDriving.publishVehicleInput();

        /*  if ((ros::Time::now().toSec() - prev_csvLaneMarkTime) > 1.0) {
      prev_csvLaneMarkTime = ros::Time::now().toSec();
    } */
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
