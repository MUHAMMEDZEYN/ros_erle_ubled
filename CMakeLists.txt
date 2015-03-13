cmake_minimum_required(VERSION 2.8.3)
project(ros_erle_ubled)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg )

## Generate messages in the 'msg' folder
add_message_files(DIRECTORY msg FILES presetPattern.msg)

## Generate added messages and services with any dependencies listed here
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(ros_erle_ubled_main src/GPIO_BBB.cpp src/DycoLEDDriver.cpp src/DycoLED_Linux.cpp src/ros_erle_ubled_main.cpp)
target_link_libraries(ros_erle_ubled_main ${catkin_LIBRARIES})
add_dependencies(ros_erle_ubled_main ros_erle_ubled_generate_messages_cpp)

add_executable(ros_erle_ubled_writer examples/ros_erle_ubled_writer.cpp)
target_link_libraries(ros_erle_ubled_writer ${catkin_LIBRARIES})
add_dependencies(ros_erle_ubled_writer ros_erle_ubled_generate_messages_cpp)

file(GLOB SCRIPTS ${PROJECT_SOURCE_DIR}/examples/*)
  catkin_install_python(PROGRAMS
  ${SCRIPTS}
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(
	TARGETS ros_erle_ubled_main
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

