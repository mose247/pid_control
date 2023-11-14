/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   // Initialize errors
   err = 0.0;
   err_d = 0.0;
   err_i = 0.0;

   // Inititalize coefficients
   kp = Kpi;
   kd = Kdi;
   ki = Kii;

   // Initialize delta time
   dt = 0.0;
}


void PID::UpdateError(double cte) {
   // error derivative
   if(dt > 0){
      err_d = (err - cte) / dt;
   } 
   else{
      err_d = 0.0;
   }

   // error integral
   err_i += cte*dt;

   // proportional error
   err = cte;
}

double PID::TotalError() {
   // compute control signal
   double control = kp*err + kd*err_d + ki*err_i;
   if(control < min_output){
      control = min_output;
   }
   if(control > max_output){
      control = max_output;
   }

   return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   dt = new_delta_time;
}