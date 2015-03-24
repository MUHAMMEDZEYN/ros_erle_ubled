#include "thread_ros.h"

Thread_ROS::Thread_ROS(Shared_Memory* shared_memory)
{
    this->shared_memory = shared_memory;

    ros::NodeHandle n;
    preset_pattern_pub = n.advertise<ros_erle_ubled::presetPattern>("ubled", 1000);
}
void Thread_ROS::run()
{
    struct timeval a, b;
    long totalb, totala;
    long diff;

    int cycle_control = 20;

    while(1){

        gettimeofday(&a, NULL);
        totala = a.tv_sec * 1000000 + a.tv_usec;

        std::vector<int> ubled_status = shared_memory->getUbled_status();
        for(int i = 0; i< ubled_status.size(); i++){
            ros_erle_ubled::presetPattern msg;
            msg.index = i;
            msg.value = ubled_status[i];
            preset_pattern_pub.publish(msg);
        }

        ros::spinOnce();

        gettimeofday(&b, NULL);
        totalb = b.tv_sec * 1000000 + b.tv_usec;
        diff = (totalb - totala) / 1000;

        if (diff < 0 || diff > cycle_control)
            diff = cycle_control;
        else
            diff = cycle_control - diff;

        usleep(diff * 1000);
    }
}
