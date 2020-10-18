#ifndef GyemsRmdProtocol_h
#define GyemsRmdProtocol_h

#include <Arduino.h>
#include <map>
#include <queue>

struct GyemsRmdReplys {
  struct PidParameters {
    struct Pid {
      uint8_t kp;
      uint8_t ki;
    } position, speed, torque;
  } pid;

  struct Acceleration {
    int32_t val;
  } acc;

  struct Encoder {
    struct Position {
      uint16_t current;
      uint16_t origin;
      uint16_t offset;
    } rawPosition;

    int64_t angle;
  } encoder;
};

class GyemsRmdProtocol {

  typedef void setFunc(uint8_t *);

  setFunc setPid;
  setFunc setAccelerationVal;
  setFunc setEncoderPosition;
  setFunc setEncoderPositionOffset;
  setFunc setEncoderAngle;

  typedef void (GyemsRmdProtocol::*MFP)(uint8_t *);
  std::map<uint8_t, MFP> setter = {

      {0x30, &GyemsRmdProtocol::setPid},
      {0x31, &GyemsRmdProtocol::setPid},
      {0x32, &GyemsRmdProtocol::setPid},

      {0x33, &GyemsRmdProtocol::setAccelerationVal},
      {0x34, &GyemsRmdProtocol::setAccelerationVal},

      {0x90, &GyemsRmdProtocol::setEncoderPosition},

      {0x91, &GyemsRmdProtocol::setEncoderPositionOffset},
      {0x19, &GyemsRmdProtocol::setEncoderPositionOffset},

      {0x92, &GyemsRmdProtocol::setEncoderAngle},

  };

public:
  void write(uint8_t buf[]) { (this->*setter[buf[0]])(buf); }

  GyemsRmdReplys status;
};

#endif