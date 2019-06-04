
"use strict";

let BatteryStatus = require('./BatteryStatus.js');
let MotorsStatus = require('./MotorsStatus.js');
let Data = require('./Data.js');
let ptz = require('./ptz.js');
let InverterStatus = require('./InverterStatus.js');
let alarmmonitor = require('./alarmmonitor.js');
let State = require('./State.js');
let alarmsmonitor = require('./alarmsmonitor.js');
let RobotnikMotorsStatus = require('./RobotnikMotorsStatus.js');
let AlarmSensor = require('./AlarmSensor.js');
let Alarms = require('./Alarms.js');
let encoders = require('./encoders.js');
let MotorsStatusDifferential = require('./MotorsStatusDifferential.js');
let inputs_outputs = require('./inputs_outputs.js');
let named_input_output = require('./named_input_output.js');
let ElevatorStatus = require('./ElevatorStatus.js');
let MotorStatus = require('./MotorStatus.js');
let named_inputs_outputs = require('./named_inputs_outputs.js');
let ElevatorAction = require('./ElevatorAction.js');
let Interfaces = require('./Interfaces.js');
let Cartesian_Euler_pose = require('./Cartesian_Euler_pose.js');
let Axis = require('./Axis.js');
let StringArray = require('./StringArray.js');
let SetElevatorResult = require('./SetElevatorResult.js');
let SetElevatorFeedback = require('./SetElevatorFeedback.js');
let SetElevatorAction = require('./SetElevatorAction.js');
let SetElevatorActionFeedback = require('./SetElevatorActionFeedback.js');
let SetElevatorGoal = require('./SetElevatorGoal.js');
let SetElevatorActionResult = require('./SetElevatorActionResult.js');
let SetElevatorActionGoal = require('./SetElevatorActionGoal.js');

module.exports = {
  BatteryStatus: BatteryStatus,
  MotorsStatus: MotorsStatus,
  Data: Data,
  ptz: ptz,
  InverterStatus: InverterStatus,
  alarmmonitor: alarmmonitor,
  State: State,
  alarmsmonitor: alarmsmonitor,
  RobotnikMotorsStatus: RobotnikMotorsStatus,
  AlarmSensor: AlarmSensor,
  Alarms: Alarms,
  encoders: encoders,
  MotorsStatusDifferential: MotorsStatusDifferential,
  inputs_outputs: inputs_outputs,
  named_input_output: named_input_output,
  ElevatorStatus: ElevatorStatus,
  MotorStatus: MotorStatus,
  named_inputs_outputs: named_inputs_outputs,
  ElevatorAction: ElevatorAction,
  Interfaces: Interfaces,
  Cartesian_Euler_pose: Cartesian_Euler_pose,
  Axis: Axis,
  StringArray: StringArray,
  SetElevatorResult: SetElevatorResult,
  SetElevatorFeedback: SetElevatorFeedback,
  SetElevatorAction: SetElevatorAction,
  SetElevatorActionFeedback: SetElevatorActionFeedback,
  SetElevatorGoal: SetElevatorGoal,
  SetElevatorActionResult: SetElevatorActionResult,
  SetElevatorActionGoal: SetElevatorActionGoal,
};
