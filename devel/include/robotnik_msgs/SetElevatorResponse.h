// Generated by gencpp from file robotnik_msgs/SetElevatorResponse.msg
// DO NOT EDIT!


#ifndef ROBOTNIK_MSGS_MESSAGE_SETELEVATORRESPONSE_H
#define ROBOTNIK_MSGS_MESSAGE_SETELEVATORRESPONSE_H


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
struct SetElevatorResponse_
{
  typedef SetElevatorResponse_<ContainerAllocator> Type;

  SetElevatorResponse_()
    : ret(false)  {
    }
  SetElevatorResponse_(const ContainerAllocator& _alloc)
    : ret(false)  {
  (void)_alloc;
    }



   typedef uint8_t _ret_type;
  _ret_type ret;





  typedef boost::shared_ptr< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> const> ConstPtr;

}; // struct SetElevatorResponse_

typedef ::robotnik_msgs::SetElevatorResponse_<std::allocator<void> > SetElevatorResponse;

typedef boost::shared_ptr< ::robotnik_msgs::SetElevatorResponse > SetElevatorResponsePtr;
typedef boost::shared_ptr< ::robotnik_msgs::SetElevatorResponse const> SetElevatorResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e2cc9e9d8c464550830df49c160979ad";
  }

  static const char* value(const ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe2cc9e9d8c464550ULL;
  static const uint64_t static_value2 = 0x830df49c160979adULL;
};

template<class ContainerAllocator>
struct DataType< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robotnik_msgs/SetElevatorResponse";
  }

  static const char* value(const ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool ret\n\
\n\
";
  }

  static const char* value(const ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.ret);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetElevatorResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::robotnik_msgs::SetElevatorResponse_<ContainerAllocator>& v)
  {
    s << indent << "ret: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.ret);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBOTNIK_MSGS_MESSAGE_SETELEVATORRESPONSE_H