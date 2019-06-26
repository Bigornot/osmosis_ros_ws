#ifndef OSMOSIS_RECOV_HPP
#define OSMOSIS_RECOV_HPP


#include <iostream>
#include <math.h>
#include <cmath>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>

using namespace std;

class Recov
{
  private :
    bool recovery;

    std_msgs::Bool rok;
    ros::NodeHandle nh_;

  public :
    Recov();
    bool makeRecovery();
    void run();
    virtual void pub_topic_recov(std_msgs::Bool)=0;
    bool recovery_action_;

};

#endif
