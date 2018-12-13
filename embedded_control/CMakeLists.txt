cmake_minimum_required(VERSION 2.8.3)
project(embedded_control)


find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  sensor_msgs
  message_generation
)

 add_message_files(
   FILES
   sensor_data.msg
   cmd_control.msg
)

 generate_messages(
   DEPENDENCIES
   std_msgs
   geometry_msgs
   sensor_msgs
 )
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES embedded_control
CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs message_runtime
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp executable

add_executable(joy_publisher src/joy.cpp)
target_link_libraries(joy_publisher ${catkin_LIBRARIES})
add_dependencies(joy_publisher joy_publisher_generate_messages_cpp)

#add_executable(convert src/convert.cpp)
#target_link_libraries(convert ${catkin_LIBRARIES})
#add_dependencies(convert generate_messages_cpp)

