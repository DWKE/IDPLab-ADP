; Auto-generated. Do not edit!


(cl:in-package kusv_msgs-msg)


;//! \htmlinclude DrivingMode.msg.html

(cl:defclass <DrivingMode> (roslisp-msg-protocol:ros-message)
  ((mode
    :reader mode
    :initarg :mode
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass DrivingMode (<DrivingMode>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DrivingMode>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DrivingMode)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name kusv_msgs-msg:<DrivingMode> is deprecated: use kusv_msgs-msg:DrivingMode instead.")))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <DrivingMode>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader kusv_msgs-msg:mode-val is deprecated.  Use kusv_msgs-msg:mode instead.")
  (mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DrivingMode>) ostream)
  "Serializes a message object of type '<DrivingMode>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'mode) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DrivingMode>) istream)
  "Deserializes a message object of type '<DrivingMode>"
    (cl:setf (cl:slot-value msg 'mode) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DrivingMode>)))
  "Returns string type for a message object of type '<DrivingMode>"
  "kusv_msgs/DrivingMode")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DrivingMode)))
  "Returns string type for a message object of type 'DrivingMode"
  "kusv_msgs/DrivingMode")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DrivingMode>)))
  "Returns md5sum for a message object of type '<DrivingMode>"
  "f3124ebba8ebedcd8ba82847d482ceb7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DrivingMode)))
  "Returns md5sum for a message object of type 'DrivingMode"
  "f3124ebba8ebedcd8ba82847d482ceb7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DrivingMode>)))
  "Returns full string definition for message of type '<DrivingMode>"
  (cl:format cl:nil "bool mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DrivingMode)))
  "Returns full string definition for message of type 'DrivingMode"
  (cl:format cl:nil "bool mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DrivingMode>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DrivingMode>))
  "Converts a ROS message object to a list"
  (cl:list 'DrivingMode
    (cl:cons ':mode (mode msg))
))
