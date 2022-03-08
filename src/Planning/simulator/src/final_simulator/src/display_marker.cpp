#include "autonomous_msg/LanePointDataArray.h"
#include "autonomous_msg/PolyfitLaneDataArray.h"
#include "autonomous_msg/VehicleOutput.h"
#include "visualization_msgs/Marker.h"
#include "visualization_msgs/MarkerArray.h"
#include <math.h>
#include <ros/ros.h>
#include <string>
#include <tf/tf.h>
#include "kusv_msgs/WaypointArray.h"

#define PI 3.1415926579

class Display {
protected:
  ros::NodeHandle m_rosNodeHandler;

  ros::Publisher m_rosPubVehiclesMarker;
  ros::Subscriber m_rosSubVehicle_Output;

public:
  Display() {

    m_rosPubVehiclesMarker =
        m_rosNodeHandler.advertise<visualization_msgs::Marker>("vehicle_marker",
                                                               10);
    m_rosSubVehicle_Output = m_rosNodeHandler.subscribe(
        "/vehicle_output", 10, &Display::vehicleOutputCallback, this);
  }

  ~Display() {}

protected:
  std::string m_sVehicle_id = "";
  double m_dVehicleX = 0.0;
  double m_dVehicleY = 0.0;
  double m_dVehicleYaw = 0.0;
  bool m_isVehicleExist = false;

public:
  void vehicleOutputCallback(const autonomous_msg::VehicleOutput::ConstPtr &msg) {
    m_sVehicle_id = msg->id;
    m_dVehicleX = msg->x;
    m_dVehicleY = msg->y;
    m_dVehicleYaw = msg->yaw;
    m_isVehicleExist = true;
  }

  void mark_vehicle() {
    if (m_isVehicleExist == true) {
      tf::Quaternion q_temp;
      tf::Matrix3x3 m(q_temp);
      q_temp.setRPY(90.0 / 180.0 * PI, 0, 180.0 / 180.0 * PI + m_dVehicleYaw);
      tf::Quaternion q(q_temp.getX(), q_temp.getY(), q_temp.getZ(),
                       q_temp.getW());

      visualization_msgs::Marker vehicle_marker;
      vehicle_marker.header.frame_id = "/world";
      vehicle_marker.header.stamp = ros::Time::now();
      vehicle_marker.ns = m_sVehicle_id;
      vehicle_marker.id = 0;
      // Set the marker type
      vehicle_marker.type = visualization_msgs::Marker::MESH_RESOURCE;
      vehicle_marker.mesh_resource =
          "file:///home/d/IDPLab-ADP/src/Planning/simulator/src/final_simulator/meshes/BMW_X5_4.dae";
      vehicle_marker.mesh_use_embedded_materials = false;

      vehicle_marker.pose.position.x = m_dVehicleX;
      vehicle_marker.pose.position.y = m_dVehicleY;
      vehicle_marker.pose.position.z = 0.0;
      vehicle_marker.pose.orientation.x = q.getX();
      vehicle_marker.pose.orientation.y = q.getY();
      vehicle_marker.pose.orientation.z = q.getZ();
      vehicle_marker.pose.orientation.w = q.getW();
      // Set the scale of the marker
      vehicle_marker.scale.x = 1.0;
      vehicle_marker.scale.y = 1.0;
      vehicle_marker.scale.z = 1.0;

      vehicle_marker.color.r = 1.0;
      vehicle_marker.color.g = 1.0;
      vehicle_marker.color.b = 1.0;
      vehicle_marker.color.a = 1.0;

      vehicle_marker.lifetime = ros::Duration(0.1);

      m_rosPubVehiclesMarker.publish(vehicle_marker);
    }
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "sim_display");
  // Vehicle vehicle;
  Display display;

  double prev_vehiclesMarkTime = ros::Time::now().toSec();

  ros::Rate loop_rate(100);
  while (ros::ok()) {
    
    if ((ros::Time::now().toSec() - prev_vehiclesMarkTime) > 0.1) {
      prev_vehiclesMarkTime = ros::Time::now().toSec();
      display.mark_vehicle();
    }

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
