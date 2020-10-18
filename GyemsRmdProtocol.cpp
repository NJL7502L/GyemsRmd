#include <Arduino.h>
#include "GyemsRmdProtocol.h"

void GyemsRmdProtocol::setPid(uint8_t *buf) {
  GyemsRmdReplys::PidParameters pid;

  pid.position.kp = buf[2];
  pid.position.ki = buf[3];
  pid.speed.kp = buf[4];
  pid.speed.ki = buf[5];
  pid.torque.kp = buf[6];
  pid.torque.ki = buf[7];

  status.pid = pid;
};

void GyemsRmdProtocol::setAccelerationVal(uint8_t *buf) {
  status.acc.val = *(int32_t *)(&buf[4]);
};

void GyemsRmdProtocol::setEncoderPosition(uint8_t *buf) {
  status.encoder.rawPosition.current = *(uint16_t *)(&buf[2]);
  status.encoder.rawPosition.origin = *(uint16_t *)(&buf[4]);
  status.encoder.rawPosition.offset = *(uint16_t *)(&buf[6]);
};

void GyemsRmdProtocol::setEncoderPositionOffset(uint8_t *buf) {
  status.encoder.rawPosition.offset = *(uint16_t *)(&buf[6]);
};

void GyemsRmdProtocol::setEncoderAngle(uint8_t *buf) {
  *(&buf + 8) = 0; // buf[8] に 0をセットしておく//これダメやろうな...
  status.encoder.angle = *(int64_t *)(&buf[1]);
};
