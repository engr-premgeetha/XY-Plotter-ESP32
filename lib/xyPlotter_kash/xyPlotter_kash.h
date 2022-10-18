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
 * @date Sep 27, 2022 
 * 
 */
#ifndef _xyPlotter_kash_
#define _xyPlotter_kash_
#include"stepper_kash.h"
#include<ESP32Servo.h>

/**
 * @brief 
 * 
 */
struct xyPoint{
    int x_pos;
    int y_pos;
};

/**
 * @brief 
 * 
 */
class XYPlotter{
    private: 
        
        xyPoint target_position;
        xyPoint current_position;
        Stepper *motorX;
        Stepper *motorY;
        Servo *servo_pen;
        /**
         * @brief 
         * 
         * @param xsteps 
         * @param ysteps 
         */
        void stepcalculation(int xsteps=0, int ysteps=0);

    public:
        /**
         * @brief Construct a new XYPlotter object
         * 
         * @param motorx 
         * @param motory 
         * @param servo_pen 
         */
        XYPlotter(class Stepper *motorx, class Stepper *motory, class Servo* servo_pen);

        /**
         * @brief 
         * 
         * @param servo 
         * @param xsteps 
         * @param ysteps 
         */
        void begin(int servo, int xsteps=0, int ysteps=0);

        /**
         * @brief 
         * 
         */
        void reset_plotter(void);

        /**
         * @brief Get the current position object
         * 
         * @return xyPoint 
         */
        xyPoint get_current_position(void);

        /**
         * @brief Set the position object
         * 
         * @param point 
         */
        void set_position(xyPoint* point);

        /**
         * @brief 
         * 
         * @param point 
         */
        void move_to(xyPoint* point);

        /**
         * @brief 
         * 
         * @param point 
         */
        void press_point(xyPoint* point);
};


#endif /*_xyPlotter_kash_*/
