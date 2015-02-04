#include "ros/ros.h"
#include "ros_erle_ubled/single_led_preset_pattern.h"
#include "ros_erle_ubled/init_number_leds.h"
#include "ros_erle_ubled/preset_pattern.h"

// "std_msgs/UInt8.h"
//#include "std_msgs/UInt16.h"
//#include "std_msgs/String.h"
#include <cstdlib>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "ros_erle_ubled_client");
  
  //if (argc != 3){
  //  ROS_INFO("usage: ros_erle_ubled_client num_led/set_pattern number/pattern_number");
  //  return 1;
  //}

  // ros::NodeHandle n;
  // ros::Publisher led_pub = n.advertise<ros_erle_statusled::statusled>("statusled", 1000);
  // ros_erle_statusled::statusled msg;

  // msg.blue = atoi(argv[1])==1;
  // msg.red = atoi(argv[2])==1;
  // msg.green = true;

  ros::NodeHandle n,led_init_n;
  ros::Publisher quantity_pub = n.advertise<ros_erle_ubled::init_number_leds>("quantity_leds", 1000);  
  ros::Publisher led_init_pub = led_init_n.advertise<ros_erle_ubled::preset_pattern>("ubled_preset_pattern", 1000);

  ros_erle_ubled::init_number_leds init_msg;
  ros_erle_ubled::preset_pattern pattern_msg;

  ros::Rate loop_rate(10);

  init_msg.number_leds=20;
  pattern_msg.ubled_preset_pattern=0;
 //int count = 0;
  while (ros::ok()){
	
	ROS_INFO("printing leds init mssg\n");
  	quantity_pub.publish(init_msg);
	
	ros::spinOnce();
        loop_rate.sleep();
	
	ROS_INFO("printing led pattern\n");
	led_init_pub.publish(pattern_msg);
  	ros::spinOnce();
  	loop_rate.sleep();
  }  
  return 0;
}
