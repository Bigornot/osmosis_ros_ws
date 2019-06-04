// Auto-generated. Do not edit!

// (in-package osmosis_control.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class TeleopMsg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.is_active = null;
      this.cmd_vel = null;
    }
    else {
      if (initObj.hasOwnProperty('is_active')) {
        this.is_active = initObj.is_active
      }
      else {
        this.is_active = false;
      }
      if (initObj.hasOwnProperty('cmd_vel')) {
        this.cmd_vel = initObj.cmd_vel
      }
      else {
        this.cmd_vel = new geometry_msgs.msg.Twist();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type TeleopMsg
    // Serialize message field [is_active]
    bufferOffset = _serializer.bool(obj.is_active, buffer, bufferOffset);
    // Serialize message field [cmd_vel]
    bufferOffset = geometry_msgs.msg.Twist.serialize(obj.cmd_vel, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type TeleopMsg
    let len;
    let data = new TeleopMsg(null);
    // Deserialize message field [is_active]
    data.is_active = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [cmd_vel]
    data.cmd_vel = geometry_msgs.msg.Twist.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 49;
  }

  static datatype() {
    // Returns string type for a message object
    return 'osmosis_control/TeleopMsg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '377211ff04d8aeef101557fb8d185e9f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool is_active
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
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new TeleopMsg(null);
    if (msg.is_active !== undefined) {
      resolved.is_active = msg.is_active;
    }
    else {
      resolved.is_active = false
    }

    if (msg.cmd_vel !== undefined) {
      resolved.cmd_vel = geometry_msgs.msg.Twist.Resolve(msg.cmd_vel)
    }
    else {
      resolved.cmd_vel = new geometry_msgs.msg.Twist()
    }

    return resolved;
    }
};

module.exports = TeleopMsg;
