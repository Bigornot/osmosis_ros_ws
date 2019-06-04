;; Auto-generated. Do not edit!


(when (boundp 'osmosis_control::TeleopMsg)
  (if (not (find-package "OSMOSIS_CONTROL"))
    (make-package "OSMOSIS_CONTROL"))
  (shadow 'TeleopMsg (find-package "OSMOSIS_CONTROL")))
(unless (find-package "OSMOSIS_CONTROL::TELEOPMSG")
  (make-package "OSMOSIS_CONTROL::TELEOPMSG"))

(in-package "ROS")
;;//! \htmlinclude TeleopMsg.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass osmosis_control::TeleopMsg
  :super ros::object
  :slots (_is_active _cmd_vel ))

(defmethod osmosis_control::TeleopMsg
  (:init
   (&key
    ((:is_active __is_active) nil)
    ((:cmd_vel __cmd_vel) (instance geometry_msgs::Twist :init))
    )
   (send-super :init)
   (setq _is_active __is_active)
   (setq _cmd_vel __cmd_vel)
   self)
  (:is_active
   (&optional __is_active)
   (if __is_active (setq _is_active __is_active)) _is_active)
  (:cmd_vel
   (&rest __cmd_vel)
   (if (keywordp (car __cmd_vel))
       (send* _cmd_vel __cmd_vel)
     (progn
       (if __cmd_vel (setq _cmd_vel (car __cmd_vel)))
       _cmd_vel)))
  (:serialization-length
   ()
   (+
    ;; bool _is_active
    1
    ;; geometry_msgs/Twist _cmd_vel
    (send _cmd_vel :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _is_active
       (if _is_active (write-byte -1 s) (write-byte 0 s))
     ;; geometry_msgs/Twist _cmd_vel
       (send _cmd_vel :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _is_active
     (setq _is_active (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; geometry_msgs/Twist _cmd_vel
     (send _cmd_vel :deserialize buf ptr-) (incf ptr- (send _cmd_vel :serialization-length))
   ;;
   self)
  )

(setf (get osmosis_control::TeleopMsg :md5sum-) "377211ff04d8aeef101557fb8d185e9f")
(setf (get osmosis_control::TeleopMsg :datatype-) "osmosis_control/TeleopMsg")
(setf (get osmosis_control::TeleopMsg :definition-)
      "bool is_active
geometry_msgs/Twist cmd_vel

================================================================================
MSG: geometry_msgs/Twist
# This expresses velocity in free space broken into its linear and angular parts.
Vector3  linear
Vector3  angular

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
")



(provide :osmosis_control/TeleopMsg "377211ff04d8aeef101557fb8d185e9f")


