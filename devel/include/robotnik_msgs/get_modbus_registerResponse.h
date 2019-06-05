// Generated by gencpp from file robotnik_msgs/get_modbus_registerResponse.msg
// DO NOT EDIT!


#ifndef ROBOTNIK_MSGS_MESSAGE_GET_MODBUS_REGISTERRESPONSE_H
#define ROBOTNIK_MSGS_MESSAGE_GET_MODBUS_REGISTERRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace robotnik_msgs
{
template <class ContainerAllocator>
struct get_modbus_registerResponse_
{
  typedef get_modbus_registerResponse_<ContainerAllocator> Type;

  get_modbus_registerResponse_()
    : ret(false)
    , value(0)  {
    }
  get_modbus_registerResponse_(const ContainerAllocator& _alloc)
    : ret(false)
    , value(0)  {
  (void)_alloc;
    }



   typedef uint8_t _ret_type;
  _ret_type ret;

   typedef uint16_t _value_type;
  _value_type value;





  typedef boost::shared_ptr< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> const> ConstPtr;

}; // struct get_modbus_registerResponse_

typedef ::robotnik_msgs::get_modbus_registerResponse_<std::allocator<void> > get_modbus_registerResponse;

typedef boost::shared_ptr< ::robotnik_msgs::get_modbus_registerResponse > get_modbus_registerResponsePtr;
typedef boost::shared_ptr< ::robotnik_msgs::get_modbus_registerResponse const> get_modbus_registerResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace robotnik_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'robotnik_msgs': ['/home/afavier/osmosis_ws/src/robotnik_msgs/msg', '/home/afavier/osmosis_ws/devel/share/robotnik_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "538660b29f52203f8c773272f9bff3df";
  }

  static const char* value(const ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x538660b29f52203fULL;
  static const uint64_t static_value2 = 0x8c773272f9bff3dfULL;
};

template<class ContainerAllocator>
struct DataType< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robotnik_msgs/get_modbus_registerResponse";
  }

  static const char* value(const ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool ret\n\
uint16 value\n\
\n\
";
  }

  static const char* value(const ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.ret);
      stream.next(m.value);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct get_modbus_registerResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::robotnik_msgs::get_modbus_registerResponse_<ContainerAllocator>& v)
  {
    s << indent << "ret: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.ret);
    s << indent << "value: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.value);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBOTNIK_MSGS_MESSAGE_GET_MODBUS_REGISTERRESPONSE_H