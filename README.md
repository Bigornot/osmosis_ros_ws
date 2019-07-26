# osmosis_ros_ws

This a version of the osmosis_control package of the OSMOSIS project, improved during june/july 2019 @LAAS-CNRS TOULOUSE.

This package is currently made to be launched with gazebo.
Once you have ROS (kinetic) and Gazebo (we worked on the 7.15.0, we have not checked if it can work with the newer versions) installed, you can launch the project with these instructions :

1) Download and launch the simulation files on gitlab :

      IN A FIRST SHELL:
      mkdir osmosis_ws
      cd osmosis_ws
      mkdir osmosis_simulation_ws
      cd osmosis_simulation_ws
      mkdir src
      cd src
      git clone https://gitlab.com/osmosis/summit_xl_sim -b kinetic-devel
      git clone https://gitlab.com/osmosis/summit_xl_common -b kinetic-devel
      git clone https://gitlab.com/osmosis/robotnik_msgs -b kinetic-devel
      git clone https://gitlab.com/osmosis/robotnik_sensors -b kinetic-devel
      git clone https://gitlab.com/osmosis/osmosis_simulation
      cd ..
      catkin_make
      source devel/setup.bash
      roslaunch osmosis_simulation summit_xl_simulation.launch
      
2) Add and launch this osmosis_control package :

      IN ANOTHER SHELL, IN THE FOLDER osmosis_ws:
      git clone https://github.com/DistractedBoyfriend/osmosis_ros_ws
      cd osmosis_ros_ws
      catkin_make
      source devel/setup.bash
      roslaunch osmosis_control osmosisControl.launch
 
 You might want to switch on the "ftm" branch of this repository if you want to work on our fault tolerance mechanism.
 
 2019 @LAAS-CNRS TOULOUSE
 MESSIOUX Antonin/FAVIER Anthony
