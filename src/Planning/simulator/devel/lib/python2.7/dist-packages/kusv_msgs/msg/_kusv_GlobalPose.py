# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from kusv_msgs/kusv_GlobalPose.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import std_msgs.msg

class kusv_GlobalPose(genpy.Message):
  _md5sum = "57b9e4be8f27b18208f562fe0b5d18e5"
  _type = "kusv_msgs/kusv_GlobalPose"
  _has_header = True  # flag to mark the presence of a Header object
  _full_text = """Header header
float64 Latitude
float64 Longitude
float32 Heading
uint16 GPSQuality
uint16 LatStd
uint16 LonStd
uint16 HeadingStd

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id
"""
  __slots__ = ['header','Latitude','Longitude','Heading','GPSQuality','LatStd','LonStd','HeadingStd']
  _slot_types = ['std_msgs/Header','float64','float64','float32','uint16','uint16','uint16','uint16']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       header,Latitude,Longitude,Heading,GPSQuality,LatStd,LonStd,HeadingStd

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(kusv_GlobalPose, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.Latitude is None:
        self.Latitude = 0.
      if self.Longitude is None:
        self.Longitude = 0.
      if self.Heading is None:
        self.Heading = 0.
      if self.GPSQuality is None:
        self.GPSQuality = 0
      if self.LatStd is None:
        self.LatStd = 0
      if self.LonStd is None:
        self.LonStd = 0
      if self.HeadingStd is None:
        self.HeadingStd = 0
    else:
      self.header = std_msgs.msg.Header()
      self.Latitude = 0.
      self.Longitude = 0.
      self.Heading = 0.
      self.GPSQuality = 0
      self.LatStd = 0
      self.LonStd = 0
      self.HeadingStd = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_3I().pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_2df4H().pack(_x.Latitude, _x.Longitude, _x.Heading, _x.GPSQuality, _x.LatStd, _x.LonStd, _x.HeadingStd))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 28
      (_x.Latitude, _x.Longitude, _x.Heading, _x.GPSQuality, _x.LatStd, _x.LonStd, _x.HeadingStd,) = _get_struct_2df4H().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_3I().pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_2df4H().pack(_x.Latitude, _x.Longitude, _x.Heading, _x.GPSQuality, _x.LatStd, _x.LonStd, _x.HeadingStd))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 28
      (_x.Latitude, _x.Longitude, _x.Heading, _x.GPSQuality, _x.LatStd, _x.LonStd, _x.HeadingStd,) = _get_struct_2df4H().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_2df4H = None
def _get_struct_2df4H():
    global _struct_2df4H
    if _struct_2df4H is None:
        _struct_2df4H = struct.Struct("<2df4H")
    return _struct_2df4H
_struct_3I = None
def _get_struct_3I():
    global _struct_3I
    if _struct_3I is None:
        _struct_3I = struct.Struct("<3I")
    return _struct_3I
