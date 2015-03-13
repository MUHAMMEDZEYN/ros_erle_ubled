#include <ros/ros.h>
#include "ros_erle_ubled/presetPattern.h"

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <vector>

#include "DycoLED_Linux.h"

DycoLED ubled;
pthread_t tid;
int num_leds;

std::vector<int> color_led;


void* updateUbled(void* arg)
{
    struct timeval a, b;
    long totala, totalb;
    long diff;

    int cycle_control = 1;

    while(1){
        gettimeofday(&a, NULL);
        totala = a.tv_sec * 1000000 + a.tv_usec;

        for(int i = 0; i < num_leds; i++){
            ubled.set_single_led(i, color_led[i]);
        }

        gettimeofday(&b, NULL);
        totalb = b.tv_sec * 1000000 + b.tv_usec;
        diff = (totalb - totala) / 1000;

        if (diff <= 0)
            diff = cycle_control;
        else if(diff > cycle_control)
            diff = 1;
        else
            diff = cycle_control - diff;

        usleep(diff * 1000);

    }
}

void ubledCallback(const ros_erle_ubled::presetPattern::ConstPtr& msg)
{
    ROS_INFO("I heard Tune:");

    if(msg->index < color_led.size()){
        color_led[msg->index]= msg->value;
    }

}

int main(int argc, char* argv[])
{

    if(argc !=2){
        std::cout << "Usage: rosrun ros_erle_ubled ros_erle_ubled_main <num_leds>" << std::endl;
        return -1;
    }

    ros::init(argc, argv, "ubled_main");

    ros::NodeHandle n;

    num_leds = atoi(argv[1]);

    ubled.init(num_leds);

    ros::Subscriber sub = n.subscribe("ubled", 1000, ubledCallback);

    for(int i = 0; i < num_leds; i++){
        color_led.push_back(0);
    }

    int err;
    err = pthread_create(&(tid), NULL, &updateUbled, NULL);
    if(err!=0){
        printf("\ncan't create thread ");
        return -1;
    }
    ros::spin();
    return 0;
}
