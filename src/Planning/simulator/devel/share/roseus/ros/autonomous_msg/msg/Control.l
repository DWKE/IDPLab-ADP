;; Auto-generated. Do not edit!


(when (boundp 'autonomous_msg::Control)
  (if (not (find-package "AUTONOMOUS_MSG"))
    (make-package "AUTONOMOUS_MSG"))
  (shadow 'Control (find-package "AUTONOMOUS_MSG")))
(unless (find-package "AUTONOMOUS_MSG::CONTROL")
  (make-package "AUTONOMOUS_MSG::CONTROL"))

(in-package "ROS")
;;//! \htmlinclude Control.msg.html


(defclass autonomous_msg::Control
  :super ros::object
  :slots (_gear _speed _steer _brake ))

(defmethod autonomous_msg::Control
  (:init
   (&key
    ((:gear __gear) 0)
    ((:speed __speed) 0.0)
    ((:steer __steer) 0.0)
    ((:brake __brake) 0)
    )
   (send-super :init)
   (setq _gear (round __gear))
   (setq _speed (float __speed))
   (setq _steer (float __steer))
   (setq _brake (round __brake))
   self)
  (:gear
   (&optional __gear)
   (if __gear (setq _gear __gear)) _gear)
  (:speed
   (&optional __speed)
   (if __speed (setq _speed __speed)) _speed)
  (:steer
   (&optional __steer)
   (if __steer (setq _steer __steer)) _steer)
  (:brake
   (&optional __brake)
   (if __brake (setq _brake __brake)) _brake)
  (:serialization-length
   ()
   (+
    ;; uint8 _gear
    1
    ;; float64 _speed
    8
    ;; float64 _steer
    8
    ;; uint8 _brake
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _gear
       (write-byte _gear s)
     ;; float64 _speed
       (sys::poke _speed (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _steer
       (sys::poke _steer (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; uint8 _brake
       (write-byte _brake s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _gear
     (setq _gear (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float64 _speed
     (setq _speed (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _steer
     (setq _steer (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; uint8 _brake
     (setq _brake (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get autonomous_msg::Control :md5sum-) "dc7c18410f31d94bc1d86a60a384c0a6")
(setf (get autonomous_msg::Control :datatype-) "autonomous_msg/Control")
(setf (get autonomous_msg::Control :definition-)
      "uint8 gear
float64 speed
float64 steer
uint8 brake

")



(provide :autonomous_msg/Control "dc7c18410f31d94bc1d86a60a384c0a6")


