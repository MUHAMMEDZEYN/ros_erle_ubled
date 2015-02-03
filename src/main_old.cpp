//ROS includes
#include "ros/ros.h"

#include "std_msgs/UInt8.h"

#include <unistd.h> //for using sleep fn
#include "DycoLED_Linux.h"

//BBB Pin definitions
#define scl BBB_P9_14
#define sda BBB_P9_16

#define num_leds 20

//LED Preset Patterns
//-------------------//
//Change patt constant value in order to use it, from 0 to 22!
// Or, create you own patterns adding the in DycoLED_Linux.cpp
//
//                    preset_pattern[22]={{{BLUE,RED},{100,100},{1.0,1.0},10,2},
//                                       {{RED,BLUE,GREEN},{250,250,250},{1.0,1.0,1.0},15,3},
//                                       {{BLACK,YELLOW},{250,250},{1.0,1.0},15,2},
//                                       {{BLUE,YELLOW},{250,250},{1.0,1.0},15,2},
//                                       {{PURPLE,YELLOW},{250,250},{1.0,1.0},15,2},
//                                       {{RED,YELLOW},{250,250},{1.0,1.0},15,2},
//                                       {{GREEN,GREEN},{1000,1000},{1.0,1.0},1,2},
//                                       {{BLUE,BLUE},{1000,1000},{1.0,1.0},1,2},
//                                       {{BLACK,YELLOW},{500,500},{1.0,1.0},15,2},
//                                       {{BLACK,GREEN},{500,500},{1.0,1.0},15,2},
//                                       {{BLACK,BLUE},{500,500},{1.0,1.0},31,2},
//                                       {{GREEN,BLACK,GREEN,BLACK},{100,50,100,1000},{1.0,1.0,1.0,1.0},1,4},
//                                       {{RED,BLACK,RED,BLACK},{100,50,100,1000},{1.0,1.0,1.0,1.0},1,4},
//                                       {{BLUE,BLACK,BLUE,BLACK},{100,50,100,1000},{1.0,1.0,1.0,1.0},1,4},
//                                       {{YELLOW},{200},{0.1},10,1},
//                                       {{PURPLE},{200},{0.1},10,1},
//                                       {{GREEN,BLACK,GREEN,BLACK},{100,50,100,100},{1.0,1.0,1.0,1.0},1,4},
//                                       {{GREEN,BLUE,GREEN,BLUE},{100,100,100,100},{1.0,1.0,1.0,1.0},1,4},
//                                       {{BLUE,BLACK,BLUE,BLACK},{100,50,100,1000},{1.0,1.0,1.0,1.0},1,4},
//                                       {{RED,BLACK,RED,BLACK},{100,50,100,50},{1.0,1.0,1.0,1.0},1,4},
//                                       {{WHITE},{200},{0.05},1,1},
//                                       {{RED,RED,RED,RED},{100,100,100,100},{1.0,0.8,0.5,0.2},10,4},
//                                       };


//DycoLED in ROS

int patt;

void patternCallback (const std_msgs::UInt8::ConstPtr& msg)
{
  //ROS_INFO("I heard: [%s]", msg->data.c_str());
	ROS_INFO("I heard: [%i]", msg->data);
	patt= msg->data;
}


int main(int argc, char *argv[])
{
	DycoLED ubled;
	ubled.init();

	ros::init(argc, argv, "ubled_strip");

	ros::NodeHandle n;

  	ros::Subscriber sub = n.subscribe("ubled_pattern", 1000, patternCallback);

	ros::Rate loop_rate(25000); //25 khz

	while(ros::ok()){
  	 //ROS_INFO("Writing pattern %i\n",patt);
  	 //ubled.set_leds(num_leds,patt);
	 ubled.set_leds(patt,patt);
	 ros::spinOnce();
	 loop_rate.sleep();
  	}
}

