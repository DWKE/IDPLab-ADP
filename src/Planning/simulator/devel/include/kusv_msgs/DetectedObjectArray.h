// Generated by gencpp from file kusv_msgs/DetectedObjectArray.msg
// DO NOT EDIT!


#ifndef KUSV_MSGS_MESSAGE_DETECTEDOBJECTARRAY_H
#define KUSV_MSGS_MESSAGE_DETECTEDOBJECTARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <kusv_msgs/DetectedObject.h>

namespace kusv_msgs
{
template <class ContainerAllocator>
struct DetectedObjectArray_
{
  typedef DetectedObjectArray_<ContainerAllocator> Type;

  DetectedObjectArray_()
    : objects()  {
    }
  DetectedObjectArray_(const ContainerAllocator& _alloc)
    : objects(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::kusv_msgs::DetectedObject_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::kusv_msgs::DetectedObject_<ContainerAllocator> >::other >  _objects_type;
  _objects_type objects;





  typedef boost::shared_ptr< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> const> ConstPtr;

}; // struct DetectedObjectArray_

typedef ::kusv_msgs::DetectedObjectArray_<std::allocator<void> > DetectedObjectArray;

typedef boost::shared_ptr< ::kusv_msgs::DetectedObjectArray > DetectedObjectArrayPtr;
typedef boost::shared_ptr< ::kusv_msgs::DetectedObjectArray const> DetectedObjectArrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::kusv_msgs::DetectedObjectArray_<ContainerAllocator1> & lhs, const ::kusv_msgs::DetectedObjectArray_<ContainerAllocator2> & rhs)
{
  return lhs.objects == rhs.objects;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::kusv_msgs::DetectedObjectArray_<ContainerAllocator1> & lhs, const ::kusv_msgs::DetectedObjectArray_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace kusv_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "94be68693b8e7643b968d741be775fc4";
  }

  static const char* value(const ::kusv_msgs::DetectedObjectArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x94be68693b8e7643ULL;
  static const uint64_t static_value2 = 0xb968d741be775fc4ULL;
};

template<class ContainerAllocator>
struct DataType< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "kusv_msgs/DetectedObjectArray";
  }

  static const char* value(const ::kusv_msgs::DetectedObjectArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "kusv_msgs/DetectedObject[] objects\n"
"\n"
"================================================================================\n"
"MSG: kusv_msgs/DetectedObject\n"
"uint32 id\n"
"string label\n"
"\n"
"geometry_msgs/Pose pose\n"
"geometry_msgs/Point[] convex_hull\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
;
  }

  static const char* value(const ::kusv_msgs::DetectedObjectArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.objects);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct DetectedObjectArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::kusv_msgs::DetectedObjectArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::kusv_msgs::DetectedObjectArray_<ContainerAllocator>& v)
  {
    s << indent << "objects[]" << std::endl;
    for (size_t i = 0; i < v.objects.size(); ++i)
    {
      s << indent << "  objects[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::kusv_msgs::DetectedObject_<ContainerAllocator> >::stream(s, indent + "    ", v.objects[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // KUSV_MSGS_MESSAGE_DETECTEDOBJECTARRAY_H