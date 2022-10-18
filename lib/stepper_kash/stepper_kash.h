/*************************************************************************************************
* Copyright (C) 2022 by Prem Geetha
*Permission is hereby granted, free of charge, to any person
*obtaining a copy of this software and associated documentation files (the "Software"),
*to deal in the Software without restriction, including without limitation the rights to use, 
*copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,and to 
*permit persons to whom the Software is furnished to do so, subject to the following conditions:
*The above copyright notice and this permission notice shall be included in all copies or
*substantial portions of the Software.
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
*NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
*NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
*CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
*ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
*THE SOFTWARE.
**************************************************************************************************/
/**
 * @file stepper_kash.h
 * @brief This file has function that help manipulate a stepper motor using an External Driver and Sensor
 * 
 * Makes it easier to manipulate an XY Plotter and such
 * 
 * @author Prem Geetha
 * @date Sep 25, 2022 
 * 
 */
#ifndef _stepper_kash_
#define _stepper_kash_

#define delay_time 100

class Stepper{
    public:
        /**
         * @brief Construct a new Stepper object
         * 
         * @param pul 
         * @param dir 
         * @param home_sensor 
         * @param limit_sensor 
         * @param home_direction 
         * @param margin 
         */
        Stepper(int pul, int dir, int home_sensor,
                int limit_sensor, bool home_direction=true, int margin = 50);

        /**
         * @brief Sets slider near home sensor
         * 
         * @param None Takes No parameters
         * @return Nothing
         */
        void resetMotor(void);

        /**
         * @brief Set the Speed object
         * 
         * @param whatspeed Speed in microseconds
         * @return Nothing
         */

        void setSpeed(long whatspeed = 500);

        /**
         * @brief Moves one step in given direction
         * 
         * @param dir dir=true moves away from homesensor; dir=false moves towards home sensor
         */
        void step(bool dir=true);

        /**
         * @brief Moves the no of steps in given direction
         * 
         * @param number_of_steps no of steps to be moved; +ve => away from home; -ve => toward home
         */
        void step(int number_of_steps);

        /**
         * @brief return the version number
         * 
         * @return float 
         */
        float version(void);

        int calculateTotalStep(void);
        void set_no_of_steps(int no_of_steps);
        int get_no_of_steps(void);

        int get_step_number(void);

         /**
          * @brief Step to a location
          * 
          * @param steps_to_move 
          */
        void step_to(int steps_to_move);


    private:
        /**
         * @brief 
         * 
         * @param dir 
         */
        void move(bool dir);
        
        unsigned long step_delay; // delay between steps, in ms, based on speed
        int number_of_steps;      // total number of steps this motor can take
        int step_number;          // which step the motor is on
        int margin;               // margin of error
        bool home;                // set home direction
        bool limit;               // set limit direction

        //Sensor pin
        int home_sensor;           // home sensor pin number
        int limit_sensor;          // limit sensor pin number

        // motor pin numbers:   
        int pul;                   // pul pin of driver in which GPIO 
        int dir;                   //dir pin of driver in which GPIO

        unsigned long last_step_time; // time stamp in us of when the last step was taken
};

#endif /*_stepper_kash_*/