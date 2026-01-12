/*******************************************************************************
                                                    Jose Jorge Jimenez-Olivas

File Name:       steering_motor.hpp
Description:     Steering motor control.
*******************************************************************************/
#ifndef STEERING_MOTOR_HPP
#define STEERING_MOTOR_HPP /* multiple inclusion guard */

#include <Arduino.h>
#include <Servo.h>

#include "../signals/low_pass_filter.hpp"

class SteeringMotor {
private:
    Servo steeringServo;
    int steeringServoPin;
    LowPassFilter filter;
    double angle;
public:
  SteeringMotor(int servoPin) : filter(0.8), angle(0) {
    this->steeringServoPin = servoPin;
  }

  void init() {
    steeringServo.attach(steeringServoPin);
  }

  void setAngle(double steeringAngle) {
    angle = constrain(steeringAngle, -90, 90);
    steeringServo.write(angle + 90);
  }

  double getAngle() {
    return angle;
  }

};

#endif /* STEERING_MOTOR_HPP */