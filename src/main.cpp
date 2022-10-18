#include <Arduino.h>
#include "XY_ESP32_Pin.h"
#include "xyPlotter_kash.h"

#define OK 10
#define RESET 11


Stepper MotorX(XP,XD,XH,XL);
Stepper MotorY(YP,YD,YH,YL);
Servo servo_pen;
Servo servo_vol;
Servo servo_pow;

XYPlotter myPlotter(&MotorX,&MotorY,&servo_pen);
xyPoint point[12] ={ {14920,24804}/*0*/,{14920,12498}/*1*/,{14920,13904}/*2*/,
                     {14920,15237}/*3*/,{14920,16634}/*4*/,{14920,17772}/*5*/,
                     {14920,19184}/*6*/,{14920,20540}/*7*/,{14920,22149}/*8*/,
                     {14920,23252}/*9*/,{7428,24761}/*OK*/,{0,0}    /*Reset*/ };

bool display=false;
bool once=false;
int serial_input = 0;
bool joystick_mode_status = false;

void joystick_mode(){
  int joyX = analogRead(X);
  int joyY = analogRead(Y);

  if(joyX < 1000){
    MotorY.step(false);
  }
  else if(joyX > 2500){
    MotorY.step(true);
  }
  if(joyY < 1000){
    MotorX.step(false);
  }
  else if(joyY > 2500){
    MotorX.step(true);
  }

  if(digitalRead(SW)){
    servo_pen.write(PEN_UP);
  }
  else{
    servo_pen.write(PEN_DOWN);
  }

  if( ((joyX < 2500) && (joyX > 1000)) && ((joyY < 2500) && (joyY > 1000))){
    display = true;
  } else if( ((joyX > 2500) || (joyX < 1000)) || ((joyY > 2500) || (joyY < 1000))){
    once = true;    
  }

  if(display && once){
    display = false;
    once = false;
    Serial.print("MotorX:");
    Serial.println(MotorX.get_step_number());
    Serial.print("MotorY:");
    Serial.println(MotorY.get_step_number());
  }
}

void enter_pin(int pin){

  myPlotter.move_to(&point[RESET]);

  int digit1=int(pin/1000);
  int digit2=int(pin/100)%10;
  int digit3=int(pin/10)%10;
  int digit4=int(pin%10);

  myPlotter.press_point(&point[digit1]);
  myPlotter.press_point(&point[digit2]);
  myPlotter.press_point(&point[digit3]);
  myPlotter.press_point(&point[digit4]);

  myPlotter.press_point(&point[OK]);

  myPlotter.move_to(&point[RESET]);
}

void safe_on(){
  servo_vol.write(VOL_CLOSE);
  delay(1000);
  servo_pow.write(POW_CLOSE);
  delay(7000);
  servo_pow.write(POW_OPEN);
  delay(3000);
  servo_vol.write(VOL_OPEN); 
}

void power_on(){
  servo_pow.write(POW_CLOSE);
  delay(500);
  servo_pow.write(POW_OPEN);
}

void charger_on(){
  digitalWrite(RELAY, HIGH);
}

void charger_off(){
  digitalWrite(RELAY, LOW);
}

void setup(){
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT);
  servo_vol.attach(SERVO_VOL);
  servo_pow.attach(SERVO_POW);
  myPlotter.begin(SERVO_PEN,X_LIMIT,Y_LIMIT);

}

void loop(){
  if(Serial.available()){
    int temp = Serial.parseInt();
    if(temp != 0){
      serial_input = temp;
    }
  }

 /*  if(joystick_mode_status){
    joystick_mode();
  } */

  switch (serial_input){
    case 1:
      //Serial.println("JoyStickMode");
      joystick_mode();
    break;
    
    case 2:
      Serial.println("PinMode");
      while(true){
        if(Serial.available()){
          int temp = Serial.parseInt();
          if(temp != 0){
            Serial.println(temp);
            enter_pin(temp);
            break;
          }
        }
      }
      serial_input = 0;
    break;

    case 3:
      Serial.println("SafeMode");
      safe_on();
      serial_input = 0;
    break;

    case 4:
      Serial.println("PowerON");
      power_on();
      serial_input = 0;
    break;

    case 5:
      Serial.println("ChargerON");
      charger_on();
      serial_input = 0;
    break;

    case 6:
      Serial.println("ChargerOFF");
      charger_off();
      serial_input = 0;
    break;

    default:
      Serial.println("Default Mode");
    break;
  }
}