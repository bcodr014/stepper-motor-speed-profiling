/* This code is for profiling the speed of stepper motor being used via stepper motor driver.
 *  The code is designed to calculate the delay value in microseconds needed in between two consecutive steps.
 *  Any motor driver can be used, untill its using PWM signals to control the speed of motor.
 *  This code is based on 1:1:6:1:1 type partition of steps in which every section is experiencing a different speed.
 *  For example for 20000 steps the partition would be 2000 4000 16000 18000 20000 steps.
 *  The speed profile is as follows for first partition there is a linear acceleration ramp, for the subsequent partition there is an acceleration parabola to acheive 
 *  the desired maximum and constant speed. For the next partition there is a constant speed, then we have first deceleration parabola, followed by another deceleration parabola.
 *  The motive is to get a smooth jerk-less transition in between varying speed right from begining to end.
 *  
 *  initial delay is the delay in microseconds for stepper to start
 *  desired delay is the delay in microseconds required to reach the required delay, its also the starting delay of acceleration profile
 *  required delay is the delay in microseconds at contant speed also the end of acceleration parabola and the beginning of deceleration parabola.    
 *  
 */


float n = 20000;      //total number of steps
float id = 800;       //initial delay
float dd = 250;       //desired delay
float rd = 100;       //required delay

float m = (dd-id)/(0.1*n);

float a1 = (dd -rd)/(0.01*n*n);
float b1 = -2*a1*0.2*n;
float c1 = rd + a1*0.04*n*n;

float a2 = (dd -rd)/(0.01*n*n);
float b2 = -2*a2*0.8*n;
float c2 = rd + a2*0.64*n*n;

float a3 = (dd-id)/(0.01*n*n);
float b3 = -2*a3*n;
float c3 = id + a3*n*n;



float dly;           // stepper pulse delay (microsec)
int count = 0;      // count the number of steps

#define dirPin 8
#define stepPin 9

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
 
}


void loop(){
  digitalWrite(dirPin, LOW);  
  if (count<2000) {        //ramp phase
    dly = m*count + id;
    }
  else if (count>2000 && count<=4000){      //first acceleration parabola
    dly = a1*pow(count,2) + b1*count + c1;
    }
  else if (count>4000 && count<=16000){      //constant velocity
    dly = rd;
  }
  else if (count>16000 && count<=18000){       //first deceleration parabola
    dly = a2*pow(count,2) + b2*count + c2;
    }
  else if(count>18000 && count<=20000){      //second deceleration parabola
    dly = a3*pow(count,2) + b3*count + c3;
    }
 
 // Move stepper one pulse using delay just calculated
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(dly);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(dly);
  count ++;
  
}
 
 
