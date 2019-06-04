; Auto-generated. Do not edit!


(cl:in-package osmosis_control-msg)


;//! \htmlinclude TeleopMsg.msg.html

(cl:defclass <TeleopMsg> (roslisp-msg-protocol:ros-message)
  ((is_active
    :reader is_active
    :initarg :is_active
    :type cl:boolean
    :initform cl:nil)
   (cmd_vel
    :reader cmd_vel
    :initarg :cmd_vel
    :type geometry_msgs-msg:Twist
    :initform (cl:make-instance 'geometry_msgs-msg:Twist)))
)

(cl:defclass TeleopMsg (<TeleopMsg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TeleopMsg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TeleopMsg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name osmosis_control-msg:<TeleopMsg> is deprecated: use osmosis_control-msg:TeleopMsg instead.")))

(cl:ensure-generic-function 'is_active-val :lambda-list '(m))
(cl:defmethod is_active-val ((m <TeleopMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader osmosis_control-msg:is_active-val is deprecated.  Use osmosis_control-msg:is_active instead.")
  (is_active m))

(cl:ensure-generic-function 'cmd_vel-val :lambda-list '(m))
(cl:defmethod cmd_vel-val ((m <TeleopMsg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader osmosis_control-msg:cmd_vel-val is deprecated.  Use osmosis_control-msg:cmd_vel instead.")
  (cmd_vel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TeleopMsg>) ostream)
  "Serializes a message object of type '<TeleopMsg>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_active) 1 0)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'cmd_vel) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TeleopMsg>) istream)
  "Deserializes a message object of type '<TeleopMsg>"
    (cl:setf (cl:slot-value msg 'is_active) (cl:not (cl:zerop (cl:read-byte istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'cmd_vel) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TeleopMsg>)))
  "Returns string type for a message object of type '<TeleopMsg>"
  "osmosis_control/TeleopMsg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TeleopMsg)))
  "Returns string type for a message object of type 'TeleopMsg"
  "osmosis_control/TeleopMsg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TeleopMsg>)))
  "Returns md5sum for a message object of type '<TeleopMsg>"
  "377211ff04d8aeef101557fb8d185e9f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TeleopMsg)))
  "Returns md5sum for a message object of type 'TeleopMsg"
  "377211ff04d8aeef101557fb8d185e9f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TeleopMsg>)))
  "Returns full string definition for message of type '<TeleopMsg>"
  (cl:format cl:nil "bool is_active~%geometry_msgs/Twist cmd_vel~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TeleopMsg)))
  "Returns full string definition for message of type 'TeleopMsg"
  (cl:format cl:nil "bool is_active~%geometry_msgs/Twist cmd_vel~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TeleopMsg>))
  (cl:+ 0
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'cmd_vel))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TeleopMsg>))
  "Converts a ROS message object to a list"
  (cl:list 'TeleopMsg
    (cl:cons ':is_active (is_active msg))
    (cl:cons ':cmd_vel (cmd_vel msg))
))
