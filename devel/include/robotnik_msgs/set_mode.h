// Generated by gencpp from file robotnik_msgs/set_mode.msg
// DO NOT EDIT!


#ifndef ROBOTNIK_MSGS_MESSAGE_SET_MODE_H
#define ROBOTNIK_MSGS_MESSAGE_SET_MODE_H

#include <ros/service_traits.h>


#include <robotnik_msgs/set_modeRequest.h>
#include <robotnik_msgs/set_modeResponse.h>


namespace robotnik_msgs
{

struct set_mode
{

typedef set_modeRequest Request;
typedef set_modeResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct set_mode
} // namespace robotnik_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::robotnik_msgs::set_mode > {
  static const char* value()
  {
    return "961700910d81510cfbb56c2b771e2e2f";
  }

  static const char* value(const ::robotnik_msgs::set_mode&) { return value(); }
};

template<>
struct DataType< ::robotnik_msgs::set_mode > {
  static const char* value()
  {
    return "robotnik_msgs/set_mode";
  }

  static const char* value(const ::robotnik_msgs::set_mode&) { return value(); }
};


// service_traits::MD5Sum< ::robotnik_msgs::set_modeRequest> should match 
// service_traits::MD5Sum< ::robotnik_msgs::set_mode > 
template<>
struct MD5Sum< ::robotnik_msgs::set_modeRequest>
{
  static const char* value()
  {
    return MD5Sum< ::robotnik_msgs::set_mode >::value();
  }
  static const char* value(const ::robotnik_msgs::set_modeRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::robotnik_msgs::set_modeRequest> should match 
// service_traits::DataType< ::robotnik_msgs::set_mode > 
template<>
struct DataType< ::robotnik_msgs::set_modeRequest>
{
  static const char* value()
  {
    return DataType< ::robotnik_msgs::set_mode >::value();
  }
  static const char* value(const ::robotnik_msgs::set_modeRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::robotnik_msgs::set_modeResponse> should match 
// service_traits::MD5Sum< ::robotnik_msgs::set_mode > 
template<>
struct MD5Sum< ::robotnik_msgs::set_modeResponse>
{
  static const char* value()
  {
    return MD5Sum< ::robotnik_msgs::set_mode >::value();
  }
  static const char* value(const ::robotnik_msgs::set_modeResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::robotnik_msgs::set_modeResponse> should match 
// service_traits::DataType< ::robotnik_msgs::set_mode > 
template<>
struct DataType< ::robotnik_msgs::set_modeResponse>
{
  static const char* value()
  {
    return DataType< ::robotnik_msgs::set_mode >::value();
  }
  static const char* value(const ::robotnik_msgs::set_modeResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // ROBOTNIK_MSGS_MESSAGE_SET_MODE_H