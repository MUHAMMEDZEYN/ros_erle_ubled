# ros-hydro-erle-ubled

Support forums and chats
------------------------

Please ask your questions not related to bugs/feauture requests on:

- [Erle Robotics Forum](http://forum.erlerobotics.com/)

We'd like to keep the project bugtracker as free as possible, so please contact via the above methods.

Programs
-------- 

```
rosrun ros_erle_ubled ros_erle_ubled_main
```

### Installing from source

```
cd ~/ros_catkin_ws/src
git clone https://github.com/ros_erle_ubled
cd ..
catkin_make_isolated
source devel_isolated/setup.bash
```
or 

```
cd ~/ros_catkin_ws/src

wstool init src 
set -t src ros_erle_statusled --git https://github.com/erlerobot/ros_erle_ubled
wstool update -t src
```
Then use regular `catkin_make_isolated` for build and install.

### Running examples
C++:
```
rosrun ros_erle_ubled ros_erle_buzzer_writer
```

Python:
```
rosrun ros_erle_ubled ros_erle_buzzer_writer.py
```

Links
-----

  - [Erle Robotics](www.erlerobotics.com)
  - [Erle-Brain](https://erlerobotics.com/blog/product/erle-brain/)
