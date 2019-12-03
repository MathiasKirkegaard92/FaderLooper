#include <TimerOne.h>

const int PIN_VOUT = 1;


inline int clip(int in, int lo, int hi) {
    if (in > hi) {
        return hi;
    } else if (in < lo) {
        return lo;
    } else {
        return in;
    }
};


volatile double duty;

// Controller variables 
double target, pos, error, error_last;

// Controller state variables
double P, I, D;

// Controller constants
double Kp = 5;
double Ki = 0.001;
double Kd = 0.000;
double Fs = 1000;
const int I_MAX = 100;

double compute_pid(){
  
  error_last = error;
  error = target - pos;
  
  P = Kp * error;
  
  I += Ki * error;
  I = clip(I,-I_MAX, I_MAX);

  D = Kd * (error - error_last);

  return P + I + D;
  
  };

void setup() {
 pinMode(PIN_VOUT, OUTPUT);
  Timer1.initialize(1/Fs * 1000000);  // Period of Fs in microseconds
  Timer1.attachInterrupt(compute_pid); 
  Serial.begin(115200);
}


void loop() {
  // put your main code here, to run repeatedly:

}
