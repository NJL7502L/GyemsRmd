#ifndef GyemsRmd_h
#define GyemsRmd_h

#include <Arduino.h>
#include "GyemsRmdProtocol.h"
#include "../FlexCAN_T4/CanBus/CanBus.h"

class GyemsRmd {
protected:
  const int idHeader = 0x140;
  int id = idHeader + 1;

public:
  GyemsRmd();
  GyemsRmd(const int id) {
    if (id < 1 || id > 32)
      return;
    this->id = idHeader + id;
  };

  template <typename T> void read(T &canbus) {
    uint8_t buf[8] = {};
    while (canbus.available(id)) {
      canbus.read(id, buf);
    }
  };
  int a = 0;
};

#endif