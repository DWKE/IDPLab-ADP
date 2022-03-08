cmake_minimum_required(VERSION 3.0.2)
project(can_tx_subscriber)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  rospy
  std_msgs
)

add_message_files(
  FILES
  Foward.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES can_tx_subscriber
  CATKIN_DEPENDS message_runtime roscpp std_msgs
  DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(can_tx_subscriber src/can_tx_subscriber.cpp)
target_link_libraries(can_tx_subscriber ${catkin_LIBRARIES})
add_dependencies(can_tx_subscriber ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
















































































catkin_package(




)







include_directories(

  ${catkin_INCLUDE_DIRS}
)





















































































