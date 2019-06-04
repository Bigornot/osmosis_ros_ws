# Install script for directory: /home/afavier/osmosis_ws/src/robotnik_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/afavier/osmosis_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robotnik_msgs/msg" TYPE FILE FILES
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/encoders.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/inputs_outputs.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/ptz.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/Data.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/Interfaces.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/Axis.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/AlarmSensor.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/Alarms.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/MotorStatus.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/MotorsStatus.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/State.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/BatteryStatus.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/MotorsStatusDifferential.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/InverterStatus.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/RobotnikMotorsStatus.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/ElevatorAction.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/ElevatorStatus.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/Cartesian_Euler_pose.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/alarmmonitor.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/alarmsmonitor.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/named_inputs_outputs.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/named_input_output.msg"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/msg/StringArray.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robotnik_msgs/srv" TYPE FILE FILES
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/get_digital_input.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/set_analog_output.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/set_mode.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/set_ptz.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/get_mode.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/set_digital_output.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/set_odometry.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/set_height.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/enable_disable.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/home.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/axis_record.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/set_float_value.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/SetMotorStatus.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/SetElevator.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/get_alarms.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/ack_alarm.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/set_modbus_register.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/get_modbus_register.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/GetBool.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/set_CartesianEuler_pose.srv"
    "/home/afavier/osmosis_ws/src/robotnik_msgs/srv/set_named_digital_output.srv"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robotnik_msgs/action" TYPE FILE FILES "/home/afavier/osmosis_ws/src/robotnik_msgs/action/SetElevator.action")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robotnik_msgs/msg" TYPE FILE FILES
    "/home/afavier/osmosis_ws/devel/share/robotnik_msgs/msg/SetElevatorAction.msg"
    "/home/afavier/osmosis_ws/devel/share/robotnik_msgs/msg/SetElevatorActionGoal.msg"
    "/home/afavier/osmosis_ws/devel/share/robotnik_msgs/msg/SetElevatorActionResult.msg"
    "/home/afavier/osmosis_ws/devel/share/robotnik_msgs/msg/SetElevatorActionFeedback.msg"
    "/home/afavier/osmosis_ws/devel/share/robotnik_msgs/msg/SetElevatorGoal.msg"
    "/home/afavier/osmosis_ws/devel/share/robotnik_msgs/msg/SetElevatorResult.msg"
    "/home/afavier/osmosis_ws/devel/share/robotnik_msgs/msg/SetElevatorFeedback.msg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robotnik_msgs/cmake" TYPE FILE FILES "/home/afavier/osmosis_ws/build/robotnik_msgs/catkin_generated/installspace/robotnik_msgs-msg-paths.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/afavier/osmosis_ws/devel/include/robotnik_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/afavier/osmosis_ws/devel/share/roseus/ros/robotnik_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/afavier/osmosis_ws/devel/share/common-lisp/ros/robotnik_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/afavier/osmosis_ws/devel/share/gennodejs/ros/robotnik_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND "/usr/bin/python" -m compileall "/home/afavier/osmosis_ws/devel/lib/python2.7/dist-packages/robotnik_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/afavier/osmosis_ws/devel/lib/python2.7/dist-packages/robotnik_msgs")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/afavier/osmosis_ws/build/robotnik_msgs/catkin_generated/installspace/robotnik_msgs.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robotnik_msgs/cmake" TYPE FILE FILES "/home/afavier/osmosis_ws/build/robotnik_msgs/catkin_generated/installspace/robotnik_msgs-msg-extras.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robotnik_msgs/cmake" TYPE FILE FILES
    "/home/afavier/osmosis_ws/build/robotnik_msgs/catkin_generated/installspace/robotnik_msgsConfig.cmake"
    "/home/afavier/osmosis_ws/build/robotnik_msgs/catkin_generated/installspace/robotnik_msgsConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robotnik_msgs" TYPE FILE FILES "/home/afavier/osmosis_ws/src/robotnik_msgs/package.xml")
endif()

