#include "ros/ros.h"
#include "ros_erle_ubled/single_led_preset_pattern.h"
#include "ros_erle_ubled/init_number_leds.h"
#include "ros_erle_ubled/preset_pattern.h"

#include <cstdlib>
#include <string.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ros_erle_ubled_client");
  
  if (argc != 3){
    ROS_INFO("usage: writter number_of_leds/set_preset_pattern X");
    return 1;
  }

  ros::NodeHandle n,led_init_n;
  ros::Publisher quantity_pub = n.advertise<ros_erle_ubled::init_number_leds>("quantity_leds", 1000);  
  ros::Publisher preset_pattern_pub = led_init_n.advertise<ros_erle_ubled::preset_pattern>("ubled_preset_pattern", 1000);

  ros_erle_ubled::init_number_leds init_msg;
  ros_erle_ubled::preset_pattern pattern_msg;

  ros::Rate loop_rate(10);
  ros::Rate poll_rate(100);

 int count = 0;
 while (ros::ok()){

	while(quantity_pub.getNumSubscribers() == 0 && preset_pattern_pub.getNumSubscribers()==0 )
    	{
	 poll_rate.sleep();
	 ROS_INFO("Waiting subscriber...\n");
	}

	//if (std::string(argv[1])=="number_of_leds"){//Konparazioa gaizki dago, stringari \ kendu!	
	if (strcmp(argv[1],"number_of_leds")==0){
		//ROS_INFO("printing leds init mssg\n");
  		//quantity_pub.publish(init_msg);
		init_msg.number_leds=atoi(argv[2]);
		ROS_INFO("printing %i leds init mssg\n",init_msg.number_leds);
		quantity_pub.publish(init_msg);
	 }
        
	if (strcmp(argv[1],"set_preset_pattern")==0){
                //ROS_INFO("printing preset pattern  mssg\n");
                //led_init_pub.publish(init_msg);
                pattern_msg.ubled_preset_pattern=atoi(argv[2]);
                ROS_INFO("printing %i pattern  mssg\n",pattern_msg.ubled_preset_pattern);
        	preset_pattern_pub.publish(pattern_msg); 
	}

	ros::spinOnce();
        loop_rate.sleep();
	
	//ROS_INFO("printing led pattern\n");
	//led_init_pub.publish(pattern_msg);
  	//ros::spinOnce();
  	//loop_rate.sleep();
  }  
  return 0;
}
