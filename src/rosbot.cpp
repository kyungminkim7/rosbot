#include <ros/ros.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rosbot");
  ros::NodeHandle nh;

  ROS_INFO_STREAM("Hello world!");
  return 0;
}
