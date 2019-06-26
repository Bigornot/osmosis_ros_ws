#ifndef OSMOSIS_RECOV_HPP
#define OSMOSIS_RECOV_HPP

#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Bool.h>

class Recov
{
  private:
    std_msgs::Bool recov_msg_;

  protected:
    ros::NodeHandle nh_;
    ros::Subscriber Call_sub_;
    bool recovery_;

  public:
    Recov();
    bool is_recovery_on();
    void run();
    virtual void pub_topic_recov(std_msgs::Bool)=0;
};

#endif
