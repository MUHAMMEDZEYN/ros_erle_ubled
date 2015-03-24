#include <QApplication>
#include "ubled_gui.h"
#include "thread_ros.h"

#include <ros/ros.h>

#include "shared_memory.h"

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "ros_erle_ubled_client");


    QApplication a(argc, argv);

    Shared_Memory* shared_memory = new Shared_Memory();

    new Ubled_GUI(shared_memory);

    Thread_ROS thread_ROS(shared_memory);
    thread_ROS.start();

    a.exec();

}
