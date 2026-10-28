#ifndef ENCODERS

#define ENCODERS

extern int E_PA;
extern float RPMA;
extern float speed_km_hr;

extern volatile unsigned long pulsesA;

void encoders_init();

// Returns nothing and increments the volatile pulse;
void countPulsesA();


float RPM_CalculationA();

float speed_conversion(float);

void print_RPMA();


#endif