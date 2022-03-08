;; Auto-generated. Do not edit!


(when (boundp 'kusv_msgs::DrivingMode)
  (if (not (find-package "KUSV_MSGS"))
    (make-package "KUSV_MSGS"))
  (shadow 'DrivingMode (find-package "KUSV_MSGS")))
(unless (find-package "KUSV_MSGS::DRIVINGMODE")
  (make-package "KUSV_MSGS::DRIVINGMODE"))

(in-package "ROS")
;;//! \htmlinclude DrivingMode.msg.html


(defclass kusv_msgs::DrivingMode
  :super ros::object
  :slots (_mode ))

(defmethod kusv_msgs::DrivingMode
  (:init
   (&key
    ((:mode __mode) nil)
    )
   (send-super :init)
   (setq _mode __mode)
   self)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:serialization-length
   ()
   (+
    ;; bool _mode
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _mode
       (if _mode (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _mode
     (setq _mode (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get kusv_msgs::DrivingMode :md5sum-) "f3124ebba8ebedcd8ba82847d482ceb7")
(setf (get kusv_msgs::DrivingMode :datatype-) "kusv_msgs/DrivingMode")
(setf (get kusv_msgs::DrivingMode :definition-)
      "bool mode

")



(provide :kusv_msgs/DrivingMode "f3124ebba8ebedcd8ba82847d482ceb7")


