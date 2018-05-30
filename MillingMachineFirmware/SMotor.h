#pragma once
#include <Arduino.h>
#include "config.h"

class SMotor
{
  private:
    uint8_t _dir_pin;
    uint8_t _step_pin;
    uint8_t _enable_pin;
    bool _enable;
    long  _abs_possition;

  public:

    SMotor();
    ~SMotor();
    void Init(uint8_t ,uint8_t, uint8_t);
    long GetAbsPossition();
    bool GetBoolEnable();
    void SetEnable(bool);
    void Step (int DIR);
};

extern SMotor XStepper;
extern SMotor YStepper;
extern SMotor ZStepper;