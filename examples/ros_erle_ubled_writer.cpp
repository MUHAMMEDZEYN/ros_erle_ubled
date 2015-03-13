#include <ros/ros.h>
#include "ros_erle_ubled/presetPattern.h"

#include <cstdlib>
#include <string.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ros_erle_ubled_client");

  if (argc != 3){
    ROS_INFO("Usage: rosrun ros_erle_ubled ros_erle_ubled_writter pattern index");
    return 1;
  }
  ros::NodeHandle n;
  ros::Publisher preset_pattern_pub = n.advertise<ros_erle_ubled::presetPattern>("ubled", 1000);

  ros_erle_ubled::presetPattern msg;

  msg.index = atoi(argv[2]);
  msg.value = atoi(argv[1]);

  ros::Rate loop_rate(1);

  while(ros::ok()){
      preset_pattern_pub.publish(msg);
      ros::spinOnce();
      loop_rate.sleep();
  }
  return 0;
}
