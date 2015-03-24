#ifndef THREAD_ROS_H
#define THREAD_ROS_H

#include <qthread.h>
#include <iostream>
#include <sys/time.h>

#include <QThread>

#include "shared_memory.h"

#include <ros/ros.h>
#include "ros_erle_ubled/presetPattern.h"


class Thread_ROS:public QThread
{
public:
    Thread_ROS(Shared_Memory* shared_memory);
private:
    Shared_Memory* shared_memory;
    ros::Publisher preset_pattern_pub;
protected:
    void run();
};

#endif // THREAD_ROS_H
