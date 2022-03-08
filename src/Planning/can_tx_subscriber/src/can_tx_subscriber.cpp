#include "ros/ros.h"
#include "std_msgs/String.h"
#include <can_msgs/Frame.h>

#define SPEED_ID 1366
#define SAS_ANGLE_ID 688
#define BRAKE_ID 809

static int brake;
static int speed;

static double sas_angle;

void CanCallback(const can_msgs::FrameConstPtr &can_msg)
{
  unsigned int can_id = can_msg->id;

  // Get speed data (km/h)
  if (can_id == SPEED_ID)
    speed = (double)can_msg->data.at(4);

  // Get steering angle data (degree)
  if (can_id == SAS_ANGLE_ID)
  {
    int8_t angle_data_L = can_msg->data.at(0);
    int8_t angle_data_H = can_msg->data.at(1);

    sas_angle = (double)((((int16_t)angle_data_H) << 8) + (angle_data_L)) * 0.1;
  }

  if (can_id == BRAKE_ID)
    brake = (can_msg->data.at(4) & 0x02);

  ROS_INFO("Velocity : %2d km/h Steering Angle : %4.3f degree Brake : %3d", speed, sas_angle, brake);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "can_tx_subscriber");
  ros::NodeHandle n;
  ros::Subscriber can_sub = n.subscribe("can_tx", 10, CanCallback);

  ros::spin();

  return 0;
}