# stepper-motor-speed-profiling
 
This code is for profiling the speed of stepper motor being used via stepper motor driver.
   The code is designed to calculate the delay value in microseconds needed in between two consecutive steps.
   Any motor driver can be used, untill its using PWM signals to control the speed of motor.
   This code is based on 1:1:6:1:1 type partition of steps in which every section is experiencing a different speed.
   For example for 20000 steps the partition would be 2000 4000 16000 18000 20000 steps.
   The speed profile is as follows for first partition there is a linear acceleration ramp, for the subsequent partition there is an acceleration parabola to acheive 
   the desired maximum and constant speed. For the next partition there is a constant speed, then we have first deceleration parabola, followed by another deceleration parabola.
   The motive is to get a smooth jerk-less transition in between varying speed right from begining to end.
   
   initial delay is the delay in microseconds for stepper to start
   desired delay is the delay in microseconds required to reach the required delay, its also the starting delay of acceleration profile
   required delay is the delay in microseconds at contant speed also the end of acceleration parabola and the beginning of deceleration parabola.    
 