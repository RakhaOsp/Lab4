
"use strict";

let SetSpeed = require('./SetSpeed.js')
let TorqueEnable = require('./TorqueEnable.js')
let StartController = require('./StartController.js')
let SetCompliancePunch = require('./SetCompliancePunch.js')
let RestartController = require('./RestartController.js')
let SetComplianceMargin = require('./SetComplianceMargin.js')
let SetTorqueLimit = require('./SetTorqueLimit.js')
let SetComplianceSlope = require('./SetComplianceSlope.js')
let StopController = require('./StopController.js')

module.exports = {
  SetSpeed: SetSpeed,
  TorqueEnable: TorqueEnable,
  StartController: StartController,
  SetCompliancePunch: SetCompliancePunch,
  RestartController: RestartController,
  SetComplianceMargin: SetComplianceMargin,
  SetTorqueLimit: SetTorqueLimit,
  SetComplianceSlope: SetComplianceSlope,
  StopController: StopController,
};
