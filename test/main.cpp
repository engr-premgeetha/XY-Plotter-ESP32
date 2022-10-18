#include <Arduino.h>
#include <stepper_kash.h>

//Motor X
  //Limit Switches
  #define X_LIMIT 27
  #define X_HOME 26
  //Driver Pins
  #define X_PUL 19
  #define X_DIR 18

//Motor Y
  //Limit Switches
  #define Y_LIMIT 25
  #define Y_HOME 33
  //Driver Pins
  #define Y_PUL 23
  #define Y_DIR 22

Stepper MotorX(X_PUL,X_DIR,X_HOME,X_LIMIT);
Stepper MotorY(Y_PUL,Y_DIR,Y_HOME,Y_LIMIT);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  MotorX.resetMotor();
  MotorY.resetMotor();
  //MotorX.set_no_of_steps(MotorX.calculateTotalStep());
  //MotorY.set_no_of_steps(MotorY.calculateTotalStep()); // total number of steps for this motor
  /* Serial.println(MotorX.get_no_of_steps());
  Serial.println(MotorX.get_step_number());
  Serial.println(MotorY.get_no_of_steps());
  Serial.println(MotorY.get_step_number()); */
  yield();
}

void loop() {
  
}