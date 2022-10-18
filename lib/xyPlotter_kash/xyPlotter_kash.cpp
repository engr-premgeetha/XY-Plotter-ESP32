#include<Arduino.h>
#include"xyPlotter_kash.h"
#include"../../include/XY_ESP32_Pin.h"

/**
 * @brief Construct a new XYPlotter::XYPlotter object
 * 
 * @param MotorX 
 * @param MotorY 
 * @param servo_pen 
 */
XYPlotter::XYPlotter(class Stepper* MotorX, class Stepper* MotorY, class Servo* ServoPen){
    this->motorX = MotorX;
    this->motorY = MotorY;
    this->servo_pen = ServoPen;
}

/**
 * @brief 
 * 
 */
void XYPlotter::stepcalculation(int xsteps/*=0*/, int ysteps/*=0*/){
    if(xsteps !=0, ysteps !=0){
        motorX->set_no_of_steps(xsteps);
        motorY->set_no_of_steps(ysteps);
    }
    else{
        motorX->set_no_of_steps(motorX->calculateTotalStep());
        motorY->set_no_of_steps(motorY->calculateTotalStep());
    }
}

/**
 * @brief 
 * 
 */
void XYPlotter::begin(int servo, int xsteps/*=0*/, int ysteps/*=0*/){
    servo_pen->attach(servo);
    servo_pen->write(PEN_UP);
    motorX->resetMotor();
    motorY->resetMotor();
    this->stepcalculation(xsteps,ysteps);
    this->current_position.x_pos=motorX->get_step_number();
    this->current_position.y_pos=motorY->get_step_number();
}

/**
 * @brief 
 * 
 * @return xyPoint 
 */
xyPoint XYPlotter::get_current_position(){
    return current_position;
}

/**
 * @brief 
 * 
 * @param point 
 */
void XYPlotter::move_to(xyPoint* point){
    this->target_position.x_pos = point->x_pos - this->current_position.x_pos;
    this->target_position.y_pos = point->y_pos - this->current_position.y_pos;

    motorY->step_to(this->target_position.y_pos);
    this->current_position.y_pos=motorY->get_step_number();
    motorX->step_to(this->target_position.x_pos);
    this->current_position.x_pos=motorX->get_step_number();       
}

/**
 * @brief go and press the point
 * 
 * @param point 
 */
void XYPlotter::press_point(xyPoint* point){
    this->move_to(point);
    servo_pen->write(PEN_DOWN);
    delay(2500);
    servo_pen->write(PEN_UP);
    delay(500);
}