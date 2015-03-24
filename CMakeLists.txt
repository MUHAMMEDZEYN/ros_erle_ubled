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

set(install_exetables ros_erle_ubled_writer ros_erle_ubled_main)

find_package(Qt4 COMPONENTS QtCore QtGui)
if (QT_FOUND)
    include(${QT_USE_FILE})
    include_directories(${CMAKE_CURRENT_BINARY_DIR})

    message(${CMAKE_CURRENT_SOURCE_DIR}/examples/gui)

    file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/examples/gui *.ui)
    file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/examples/gui resources/*.qrc)
    file(GLOB QT_MOC ${CMAKE_CURRENT_SOURCE_DIR}/examples/gui/shared_memory.h ${CMAKE_CURRENT_SOURCE_DIR}/examples/gui/thread_ros.h ${CMAKE_CURRENT_SOURCE_DIR}/examples/gui/ubled_gui.h)

    QT4_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
    QT4_WRAP_CPP(QT_MOC_HPP ${QT_MOC})
    QT4_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
    file(GLOB QT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/examples/gui/shared_memory.cpp     ${CMAKE_CURRENT_SOURCE_DIR}/examples/gui/thread_ros.cpp ${CMAKE_CURRENT_SOURCE_DIR}/examples/gui/ubled_gui.cpp ${CMAKE_CURRENT_SOURCE_DIR}/examples/gui/main.cpp)

    add_executable(ros_erle_ubled_gui ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
    message(${catkin_LIBRARIES})
    target_link_libraries(ros_erle_ubled_gui ${catkin_LIBRARIES} ${QT_LIBRARIES} ${ROS_LIBRARIES} ${catkin_LIBRARIES})
    add_dependencies(ros_erle_ubled_gui ros_erle_ubled_generate_messages_cpp)

    set(install_exetables ros_erle_ubled_writer ros_erle_ubled_main ros_erle_ubled_gui)
endif (QT_FOUND)

file(GLOB SCRIPTS ${PROJECT_SOURCE_DIR}/examples/*)
  catkin_install_python(PROGRAMS
  ${SCRIPTS}
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(
	TARGETS ${install_exetables}
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

