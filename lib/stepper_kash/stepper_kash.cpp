#include <Arduino.h>
#include "stepper_kash.h"

/**
 * @brief 
 * 
 */
Stepper::Stepper(int pul, int dir, int home_sensor,
                 int limit_sensor, bool home_direction /*=true*/, int margin /*=50*/){

  // Arduino pins for the motor control connection:
  this->pul = pul;
  this->dir = dir;
  this->home_sensor = home_sensor;
  this->limit_sensor = limit_sensor;

  if(home_direction){
    this->home = LOW;
    this->limit = HIGH;
  }
  else{
    this->home = HIGH;
    this->limit = LOW; 
  }

   // setup the pins on the microcontroller:
  pinMode(this->pul, OUTPUT);
  pinMode(this->dir, OUTPUT);

  pinMode(this->home_sensor, INPUT_PULLUP);
  pinMode(this->limit_sensor, INPUT_PULLUP);

  this->last_step_time = 0; // time stamp in us of the last step taken
  this->margin = margin; //margin of error for no of steps.
}


/*
 * Sets the speed in revs per minute
 */
void Stepper::setSpeed(long whatSpeed /*= 500*/ ){
  this->step_delay = whatSpeed;
}

/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void Stepper::step_to(int steps_to_move)
{
  int steps_left = abs(steps_to_move);  // how many steps to take
  bool direction ; 
  // determine direction based on whether steps_to_mode is + or -:
  if (steps_to_move > 0) { direction = this->limit; }
  if (steps_to_move < 0) { direction = this->home; }

  // decrement the number of steps, moving one step each time:
  while (steps_left > 0)
  {
    unsigned long now = micros();
    // move only if the appropriate delay has passed:
    if (now - this->last_step_time >= this->step_delay)
    {
      // get the timeStamp of when you stepped:
      this->last_step_time = now;
      // increment or decrement the step number,
      // depending on direction:
      if (direction == limit)
      {
        if((this->step_number == this->number_of_steps) && (!digitalRead(limit_sensor))) {
          steps_left = 0;
          return;
        }
        this->step_number++;
      }
      else if (direction == home)
      {
        if ( (this->step_number == 0) && (!digitalRead(home_sensor))) {
          steps_left = 0;
          this->step_number = 0;
          return;
        }
        this->step_number--;
      }
      // decrement the steps left:
      steps_left--;
      // step the motor to step number 0, 1, ..., {3 or 10}
      move(direction);
    }
  }
}

/* void Stepper::step(int steps_to_move)
{
  bool direction ; 
  // determine direction based on whether steps_to_mode is + or -:
  if (steps_to_move > 0) { direction = this->limit; }
  if (steps_to_move < 0) { direction = this->home; }

  // decrement the number of steps, moving one step each time:
  unsigned long now = micros();
  // move only if the appropriate delay has passed:
  if (now - this->last_step_time >= this->step_delay)
  {
    // get the timeStamp of when you stepped:
    this->last_step_time = now;
    // increment or decrement the step number,
    // depending on direction:
    if (direction == limit)
    {
      if(digitalRead(limit_sensor)){
        this->step_number++;
      }
      else{
        return;
      }
    }
    else if (direction == home)
    {
      if (digitalRead(home_sensor)) {
        this->step_number--;
      }
      else{
        this->step_number=0;
        return;
      }
    }
    move(direction);
  }
} */

void Stepper::step(bool dir)
{
   bool direction = limit; 
  // determine direction based on whether steps_to_mode is + or -:
  if (dir) { direction = this->limit; }
  if (!dir) { direction = this->home; }

  // decrement the number of steps, moving one step each time:
  unsigned long now = micros();
  // move only if the appropriate delay has passed:
  if (now - this->last_step_time >= this->step_delay)
  {
    // get the timeStamp of when you stepped:
    this->last_step_time = now;
    // increment or decrement the step number,
    // depending on direction:
    if (direction == limit)
    {
      if(digitalRead(limit_sensor)){
        this->step_number++;
      }
      else{
        return;
      }
    }
    else if (direction == home)
    {
      if (digitalRead(home_sensor)) {
        this->step_number--;
      }
      else{
        this->step_number=0;
        return;
      }
    }
    move(direction);
  }
}

/*
  version() returns the version of the library:
*/
float Stepper::version(void){
  return 1.0;
}

void Stepper::resetMotor(void){
  while (!digitalRead(this->home_sensor)){
    step(limit);
  }  
  while(digitalRead(this->home_sensor)){
    step(home);
  }
  this->step_number=0;
}
  
int Stepper::calculateTotalStep(){
  resetMotor();
  int i=0;
  while(digitalRead(this->limit_sensor)){
    step(limit);
    i++;
  }
  int j=0;
  while(digitalRead(this->home_sensor)){
    step(home);
    j++;
  }
  this->step_number=0;
  return ((i+j)/2)-margin;
}

/*
 * Moves the motor forward or backwards.
 */
void Stepper::move(bool dir){
  digitalWrite(this->dir, dir);
  digitalWrite(this->pul, HIGH);
  delayMicroseconds(50);
  digitalWrite(this->pul, LOW);
  delayMicroseconds(50);
}

void Stepper::set_no_of_steps(int no_of_steps){
  this->number_of_steps = no_of_steps;
}

int Stepper::get_no_of_steps(void){
  return this->number_of_steps;
}

int Stepper::get_step_number(void){
  return this->step_number;
}
