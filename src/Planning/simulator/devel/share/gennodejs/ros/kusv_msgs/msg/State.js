// Auto-generated. Do not edit!

// (in-package kusv_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class State {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.speed_ms = null;
      this.speed_kmh = null;
    }
    else {
      if (initObj.hasOwnProperty('speed_ms')) {
        this.speed_ms = initObj.speed_ms
      }
      else {
        this.speed_ms = 0.0;
      }
      if (initObj.hasOwnProperty('speed_kmh')) {
        this.speed_kmh = initObj.speed_kmh
      }
      else {
        this.speed_kmh = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type State
    // Serialize message field [speed_ms]
    bufferOffset = _serializer.float64(obj.speed_ms, buffer, bufferOffset);
    // Serialize message field [speed_kmh]
    bufferOffset = _serializer.float64(obj.speed_kmh, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type State
    let len;
    let data = new State(null);
    // Deserialize message field [speed_ms]
    data.speed_ms = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [speed_kmh]
    data.speed_kmh = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'kusv_msgs/State';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '628ebfdb24aaf42618651c8520152d92';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 speed_ms
    float64 speed_kmh
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new State(null);
    if (msg.speed_ms !== undefined) {
      resolved.speed_ms = msg.speed_ms;
    }
    else {
      resolved.speed_ms = 0.0
    }

    if (msg.speed_kmh !== undefined) {
      resolved.speed_kmh = msg.speed_kmh;
    }
    else {
      resolved.speed_kmh = 0.0
    }

    return resolved;
    }
};

module.exports = State;
