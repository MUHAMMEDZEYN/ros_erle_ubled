cmake_minimum_required(VERSION 2.8.3)
project(ros_erle_ubled)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs genmsg )

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
add_message_files( DIRECTORY msg FILES preset_pattern.msg init_number_leds.msg single_led_preset_pattern.msg)

## Generate added messages and services with any dependencies listed here
generate_messages( DEPENDENCIES std_msgs )

###################################
## catkin specific configuration ##
###################################
catkin_package()

###########
## Build ##
###########

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(main src/GPIO_BBB.cpp src/DycoLEDDriver.cpp src/DycoLED_Linux.cpp src/main_berria.cpp)
target_link_libraries(main ${catkin_LIBRARIES})
add_dependencies(main main_cpp)

add_executable(writer src/writer.cpp)
target_link_libraries(writer ${catkin_LIBRARIES})
add_dependencies(writer ros_erle_ubled_generate_messages_cpp)

file(GLOB SCRIPTS ${PROJECT_SOURCE_DIR}/examples/*)
  catkin_install_python(PROGRAMS
  ${SCRIPTS}
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(
	TARGETS writer main
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

