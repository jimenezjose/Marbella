// Marbella is a hacked RC car platform for autonomous driving research.

#include <Arduino.h>
#include <VescUart.h>
#include <SoftwareSerial.h>

#include "signals/low_pass_filter.hpp"
#include "control/steering_motor.hpp"

const int knobPin = A0;
int motorPin = 5;

// SteeringMotor steeringMotor(9);
SoftwareSerial bluetoothSerial(9, 10); // RX (interupt pin), TX

VescUart UART;
float current = 1.0; 

void setup() {
  Serial.begin(9600);
  // Inputs.
  pinMode(knobPin, INPUT);
  // Outputs.
  // steeringMotor.init();
  pinMode(motorPin, OUTPUT);

  // vesc setup
  Serial.begin(115200);
  while (!Serial) {;}
  UART.setSerialPort(&Serial);

  // bluetooth setup
  bluetoothSerial.begin(9600);
}

void loop() {
  // read knob value
  int knobValue = analogRead(knobPin);
  Serial.print("knobValue: ");
  Serial.println(knobValue);
  bluetoothSerial.print("knobValue: ");
  bluetoothSerial.println(knobValue);

  // Throttle
  // int currentRequest = map(knobValue, 0, 1023, 0, 7);
  // UART.setCurrent(currentRequest);

  // if ( UART.getVescValues() ) {
  //   Serial.println(UART.data.rpm);
  //   Serial.println(UART.data.inpVoltage);
  //   Serial.println(UART.data.ampHours);
  //   Serial.println(UART.data.tachometerAbs);
  // }

  // Steering
  // double angle = map(knobValue, 0, 1023, -90, 90);
  // steeringMotor.setAngle(angle);
  // Serial.print("Steering angle: ");
  // Serial.println(steeringMotor.getAngle());

  // Throttle
  int accelerationRequest = map(knobValue, 0, 1023, 0, 255);
  analogWrite(motorPin, accelerationRequest);
}
