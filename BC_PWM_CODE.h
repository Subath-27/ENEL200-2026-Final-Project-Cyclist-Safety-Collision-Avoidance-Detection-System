#ifndef BC_PWM
#define BC_PWM

//extern int OCR_ARRAY[100];

void BC_PWM_INIT(); // Initializes the pins, timers, registers, prescalers and performs Fast PWM to generate a 500khz waveform

void ADJUST_DUTY_RATIO_BOOST();
void ADJUST_DUTY_RATIO_BUCK();


#endif