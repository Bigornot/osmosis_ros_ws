
"use strict";

let SetElevator = require('./SetElevator.js')
let axis_record = require('./axis_record.js')
let enable_disable = require('./enable_disable.js')
let home = require('./home.js')
let set_height = require('./set_height.js')
let set_named_digital_output = require('./set_named_digital_output.js')
let GetBool = require('./GetBool.js')
let set_digital_output = require('./set_digital_output.js')
let get_mode = require('./get_mode.js')
let set_ptz = require('./set_ptz.js')
let get_digital_input = require('./get_digital_input.js')
let set_float_value = require('./set_float_value.js')
let ack_alarm = require('./ack_alarm.js')
let get_alarms = require('./get_alarms.js')
let set_analog_output = require('./set_analog_output.js')
let set_mode = require('./set_mode.js')
let set_modbus_register = require('./set_modbus_register.js')
let set_CartesianEuler_pose = require('./set_CartesianEuler_pose.js')
let SetMotorStatus = require('./SetMotorStatus.js')
let get_modbus_register = require('./get_modbus_register.js')
let set_odometry = require('./set_odometry.js')

module.exports = {
  SetElevator: SetElevator,
  axis_record: axis_record,
  enable_disable: enable_disable,
  home: home,
  set_height: set_height,
  set_named_digital_output: set_named_digital_output,
  GetBool: GetBool,
  set_digital_output: set_digital_output,
  get_mode: get_mode,
  set_ptz: set_ptz,
  get_digital_input: get_digital_input,
  set_float_value: set_float_value,
  ack_alarm: ack_alarm,
  get_alarms: get_alarms,
  set_analog_output: set_analog_output,
  set_mode: set_mode,
  set_modbus_register: set_modbus_register,
  set_CartesianEuler_pose: set_CartesianEuler_pose,
  SetMotorStatus: SetMotorStatus,
  get_modbus_register: get_modbus_register,
  set_odometry: set_odometry,
};
