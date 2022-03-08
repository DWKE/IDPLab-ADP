// Generated by gencpp from file autonomous_msg/VehicleInput.msg
// DO NOT EDIT!


#ifndef AUTONOMOUS_MSG_MESSAGE_VEHICLEINPUT_H
#define AUTONOMOUS_MSG_MESSAGE_VEHICLEINPUT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace autonomous_msg
{
template <class ContainerAllocator>
struct VehicleInput_
{
  typedef VehicleInput_<ContainerAllocator> Type;

  VehicleInput_()
    : steering(0.0)
    , accel(0.0)
    , brake(0.0)  {
    }
  VehicleInput_(const ContainerAllocator& _alloc)
    : steering(0.0)
    , accel(0.0)
    , brake(0.0)  {
  (void)_alloc;
    }



   typedef double _steering_type;
  _steering_type steering;

   typedef double _accel_type;
  _accel_type accel;

   typedef double _brake_type;
  _brake_type brake;





  typedef boost::shared_ptr< ::autonomous_msg::VehicleInput_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autonomous_msg::VehicleInput_<ContainerAllocator> const> ConstPtr;

}; // struct VehicleInput_

typedef ::autonomous_msg::VehicleInput_<std::allocator<void> > VehicleInput;

typedef boost::shared_ptr< ::autonomous_msg::VehicleInput > VehicleInputPtr;
typedef boost::shared_ptr< ::autonomous_msg::VehicleInput const> VehicleInputConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autonomous_msg::VehicleInput_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autonomous_msg::VehicleInput_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::autonomous_msg::VehicleInput_<ContainerAllocator1> & lhs, const ::autonomous_msg::VehicleInput_<ContainerAllocator2> & rhs)
{
  return lhs.steering == rhs.steering &&
    lhs.accel == rhs.accel &&
    lhs.brake == rhs.brake;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::autonomous_msg::VehicleInput_<ContainerAllocator1> & lhs, const ::autonomous_msg::VehicleInput_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace autonomous_msg

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::autonomous_msg::VehicleInput_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autonomous_msg::VehicleInput_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autonomous_msg::VehicleInput_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autonomous_msg::VehicleInput_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autonomous_msg::VehicleInput_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autonomous_msg::VehicleInput_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autonomous_msg::VehicleInput_<ContainerAllocator> >
{
  static const char* value()
  {
    return "78d4e62033b2c4038de1aac2b20b2457";
  }

  static const char* value(const ::autonomous_msg::VehicleInput_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x78d4e62033b2c403ULL;
  static const uint64_t static_value2 = 0x8de1aac2b20b2457ULL;
};

template<class ContainerAllocator>
struct DataType< ::autonomous_msg::VehicleInput_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autonomous_msg/VehicleInput";
  }

  static const char* value(const ::autonomous_msg::VehicleInput_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autonomous_msg::VehicleInput_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 steering\n"
"float64 accel\n"
"float64 brake\n"
;
  }

  static const char* value(const ::autonomous_msg::VehicleInput_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autonomous_msg::VehicleInput_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.steering);
      stream.next(m.accel);
      stream.next(m.brake);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VehicleInput_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autonomous_msg::VehicleInput_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autonomous_msg::VehicleInput_<ContainerAllocator>& v)
  {
    s << indent << "steering: ";
    Printer<double>::stream(s, indent + "  ", v.steering);
    s << indent << "accel: ";
    Printer<double>::stream(s, indent + "  ", v.accel);
    s << indent << "brake: ";
    Printer<double>::stream(s, indent + "  ", v.brake);
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTONOMOUS_MSG_MESSAGE_VEHICLEINPUT_H
