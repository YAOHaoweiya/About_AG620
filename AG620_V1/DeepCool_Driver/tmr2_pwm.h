#ifndef __TMR2_PWM_H
#define __TMR2_PWM_H

#include "at32f425.h"

#define LIGHT 200  //0~670
void tmr2_pwm_init(void);

void cpu_led_state(uint8_t state);
void gpu_led_state(uint8_t state);


#endif /* __TMR2_PWM_H */
