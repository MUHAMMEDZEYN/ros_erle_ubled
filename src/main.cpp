//ROS includes

#include "ros/ros.h"

#include "std_msgs/UInt8.h"
#include "std_msgs/UInt16.h"

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

uint8_t patt;
uint16_t init_number_leds=0;
int message_type=0;
bool initialized=false;

void patternCallback (const std_msgs::UInt8::ConstPtr& msg)
{
	ROS_INFO("I heard: [%i] pattern\n", msg->data);
	patt= msg->data;
	message_type=2;//message= preset pattern type
}


void initCallback (const std_msgs::UInt16::ConstPtr& msg)
{
    ROS_INFO("I heard: [%i] number of leds", msg->data);
    init_number_leds= msg->data;
    message_type=1;//message=initialization type
}

int main(int argc, char *argv[])
{
	uint16_t old_led_num=0;//to store old quantity of leds 
	DycoLED ubled;//Create DycoLED obkect

	ros::init(argc, argv, "ubled_strip");

	ros::NodeHandle n,init_topic;

	//Subscribe to the topics
  	ros::Subscriber sub = n.subscribe("ubled_preset_pattern", 1000, patternCallback);
  	ros::Subscriber sub_init = init_topic.subscribe("quantity_leds",1000,initCallback);

	ros::Rate loop_rate(25000); //25 khz

	while(ros::ok()){//Loop

		//ROS_INFO("message is type %i\n", message_type);
		if (message_type==1)//Initialization message
			{
				if (init_number_leds!=old_led_num)//New led quantity, initialize
				{
					initialized= ubled.init(init_number_leds); //initialize nuº of leds,
					//set the return value to true
					old_led_num=init_number_leds;//store the leds quantity to compare in the next loop
				}
			}

		if (message_type==2)//Prestablished pattern message
  	 		{
  	 			if (initialized==true)//LEDs Already initialized
  	 			{
  	 				ubled.set_leds(init_number_leds,patt);//Writte pattern	
				}
  	 			else//False, LEDs are not initialize
  	 			{
  	 				ROS_INFO("Ubleds not initialized, please publish initialization message\n");
  	 			}
		
  	 		}
	  	ros::spinOnce();
	  	loop_rate.sleep();//sleep until 25KHz is done
  		}
}


