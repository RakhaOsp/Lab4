
"use strict";

let contact = require('./contact.js');
let accelerometr = require('./accelerometr.js');
let tactile = require('./tactile.js');
let coord = require('./coord.js');
let state = require('./state.js');
let fsrInput = require('./fsrInput.js');
let rigid = require('./rigid.js');
let newtactile = require('./newtactile.js');

module.exports = {
  contact: contact,
  accelerometr: accelerometr,
  tactile: tactile,
  coord: coord,
  state: state,
  fsrInput: fsrInput,
  rigid: rigid,
  newtactile: newtactile,
};
