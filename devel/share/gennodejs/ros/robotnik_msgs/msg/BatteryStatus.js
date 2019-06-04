// Auto-generated. Do not edit!

// (in-package robotnik_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class BatteryStatus {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.voltage = null;
      this.level = null;
      this.time_remaining = null;
    }
    else {
      if (initObj.hasOwnProperty('voltage')) {
        this.voltage = initObj.voltage
      }
      else {
        this.voltage = 0.0;
      }
      if (initObj.hasOwnProperty('level')) {
        this.level = initObj.level
      }
      else {
        this.level = 0.0;
      }
      if (initObj.hasOwnProperty('time_remaining')) {
        this.time_remaining = initObj.time_remaining
      }
      else {
        this.time_remaining = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BatteryStatus
    // Serialize message field [voltage]
    bufferOffset = _serializer.float32(obj.voltage, buffer, bufferOffset);
    // Serialize message field [level]
    bufferOffset = _serializer.float32(obj.level, buffer, bufferOffset);
    // Serialize message field [time_remaining]
    bufferOffset = _serializer.uint32(obj.time_remaining, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BatteryStatus
    let len;
    let data = new BatteryStatus(null);
    // Deserialize message field [voltage]
    data.voltage = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [level]
    data.level = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [time_remaining]
    data.time_remaining = _deserializer.uint32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'robotnik_msgs/BatteryStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '86d6d9c22e09e64d16ee579abc60e177';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 voltage			# in volts
    float32 level			# in %
    uint32 time_remaining		# in minutes
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BatteryStatus(null);
    if (msg.voltage !== undefined) {
      resolved.voltage = msg.voltage;
    }
    else {
      resolved.voltage = 0.0
    }

    if (msg.level !== undefined) {
      resolved.level = msg.level;
    }
    else {
      resolved.level = 0.0
    }

    if (msg.time_remaining !== undefined) {
      resolved.time_remaining = msg.time_remaining;
    }
    else {
      resolved.time_remaining = 0
    }

    return resolved;
    }
};

module.exports = BatteryStatus;
