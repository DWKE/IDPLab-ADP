;; Auto-generated. Do not edit!


(when (boundp 'kusv_msgs::DetectedObjectArray)
  (if (not (find-package "KUSV_MSGS"))
    (make-package "KUSV_MSGS"))
  (shadow 'DetectedObjectArray (find-package "KUSV_MSGS")))
(unless (find-package "KUSV_MSGS::DETECTEDOBJECTARRAY")
  (make-package "KUSV_MSGS::DETECTEDOBJECTARRAY"))

(in-package "ROS")
;;//! \htmlinclude DetectedObjectArray.msg.html


(defclass kusv_msgs::DetectedObjectArray
  :super ros::object
  :slots (_objects ))

(defmethod kusv_msgs::DetectedObjectArray
  (:init
   (&key
    ((:objects __objects) (let (r) (dotimes (i 0) (push (instance kusv_msgs::DetectedObject :init) r)) r))
    )
   (send-super :init)
   (setq _objects __objects)
   self)
  (:objects
   (&rest __objects)
   (if (keywordp (car __objects))
       (send* _objects __objects)
     (progn
       (if __objects (setq _objects (car __objects)))
       _objects)))
  (:serialization-length
   ()
   (+
    ;; kusv_msgs/DetectedObject[] _objects
    (apply #'+ (send-all _objects :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; kusv_msgs/DetectedObject[] _objects
     (write-long (length _objects) s)
     (dolist (elem _objects)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; kusv_msgs/DetectedObject[] _objects
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _objects (let (r) (dotimes (i n) (push (instance kusv_msgs::DetectedObject :init) r)) r))
     (dolist (elem- _objects)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get kusv_msgs::DetectedObjectArray :md5sum-) "94be68693b8e7643b968d741be775fc4")
(setf (get kusv_msgs::DetectedObjectArray :datatype-) "kusv_msgs/DetectedObjectArray")
(setf (get kusv_msgs::DetectedObjectArray :definition-)
      "kusv_msgs/DetectedObject[] objects

================================================================================
MSG: kusv_msgs/DetectedObject
uint32 id
string label

geometry_msgs/Pose pose
geometry_msgs/Point[] convex_hull

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

")



(provide :kusv_msgs/DetectedObjectArray "94be68693b8e7643b968d741be775fc4")


