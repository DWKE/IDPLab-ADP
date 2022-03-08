;; Auto-generated. Do not edit!


(when (boundp 'kusv_msgs::State)
  (if (not (find-package "KUSV_MSGS"))
    (make-package "KUSV_MSGS"))
  (shadow 'State (find-package "KUSV_MSGS")))
(unless (find-package "KUSV_MSGS::STATE")
  (make-package "KUSV_MSGS::STATE"))

(in-package "ROS")
;;//! \htmlinclude State.msg.html


(defclass kusv_msgs::State
  :super ros::object
  :slots (_speed_ms _speed_kmh ))

(defmethod kusv_msgs::State
  (:init
   (&key
    ((:speed_ms __speed_ms) 0.0)
    ((:speed_kmh __speed_kmh) 0.0)
    )
   (send-super :init)
   (setq _speed_ms (float __speed_ms))
   (setq _speed_kmh (float __speed_kmh))
   self)
  (:speed_ms
   (&optional __speed_ms)
   (if __speed_ms (setq _speed_ms __speed_ms)) _speed_ms)
  (:speed_kmh
   (&optional __speed_kmh)
   (if __speed_kmh (setq _speed_kmh __speed_kmh)) _speed_kmh)
  (:serialization-length
   ()
   (+
    ;; float64 _speed_ms
    8
    ;; float64 _speed_kmh
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _speed_ms
       (sys::poke _speed_ms (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _speed_kmh
       (sys::poke _speed_kmh (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _speed_ms
     (setq _speed_ms (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _speed_kmh
     (setq _speed_kmh (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get kusv_msgs::State :md5sum-) "628ebfdb24aaf42618651c8520152d92")
(setf (get kusv_msgs::State :datatype-) "kusv_msgs/State")
(setf (get kusv_msgs::State :definition-)
      "float64 speed_ms
float64 speed_kmh

")



(provide :kusv_msgs/State "628ebfdb24aaf42618651c8520152d92")


