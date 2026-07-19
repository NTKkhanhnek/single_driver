#include "clock.h"
#include <stdint.h>

#define TIM4_ADDR 0x40000800
#define GPIOB_ADDR_BASE 0x40020400
// use TIM4_CH1,2,3,4 to generate PWM signal, use PB 6,7,8,9 to output PWM signal
//output compare mode


/*
*@brief: generate PWm: T=1s, pulse_width = 0.5s(DT = 50%)
* use TIM4_CH1 
*/

void pwm_init(){
 clock_enable_AHB1( GPIOB_peripheral );

 clock_enable_APB1( TIM4_peripheral );

// GPIOB pin 6, 7, 8, 9 as alternate function for TIM4_CH1
uint32_t* GPIOB_MODER = (uint32_t*) (GPIOB_ADDR_BASE + 0x00);
	*GPIOB_MODER &= ~( 0xFF << 12 );  //clear bits for PB6, PB7, PB8, PB9
	*GPIOB_MODER |= ( 0b10 << 12 )|( 0b10 << 14 )|( 0b10 << 16 )|( 0b10 << 18 );  
  // SET GPIOB6, PB7, PB8, PB9 AS ALTERNATE FUNCTION

  uint32_t* GPIOB_AFRL = (uint32_t*) (GPIOB_ADDR_BASE + 0x20);
	*GPIOB_AFRL &= ~( 0xFF << 24 ); 
	*GPIOB_AFRL |= ( 0b0010 << 24 )|( 0b0010 << 28 );  // SET GPIOB6,7 AS AF2 ( TIM4_CH1,2 )

  uint32_t* GPIOB_AFRH = (uint32_t*) (GPIOB_ADDR_BASE + 0x24);
	*GPIOB_AFRH &= ~( 0xFF << 0 ); 
	*GPIOB_AFRH |= ( 0b0010 << 0 )|( 0b0010 << 4 );  // SET GPIOB8,9 AS AF2 ( TIM4_CH3,4 )

 uint32_t *TIM4_PSC = (uint32_t*) (TIM4_ADDR + 0x28);
 uint32_t *TIM4_ARR = (uint32_t*) (TIM4_ADDR + 0x2C);
   *TIM4_PSC = 16 - 1;  
   *TIM4_ARR = 20000; // period : 20ms

   //CH1 use TIM4_CCR1
     uint32_t *TIM4_CCR1 = (uint32_t*) (TIM4_ADDR + 0x34);
       *TIM4_CCR1 = 0;   // value of pulse width 


// select output compare mode ( PWM mode 1 )
uint16_t* TIM4_CCMR1 = (uint16_t*) (TIM4_ADDR + 0x18);
 *TIM4_CCMR1 &= ~((0b11<<0)|(0b11<<8)); //output compare mode for CH1, CH2
 *TIM4_CCMR1 &= ~((0b111<<4)|(0b111<<12)); // clear bits for CH1, CH2
 *TIM4_CCMR1 |=  (0b110 << 4)|(0b110<<12); // PWM mode 1 for CH1,CH2

 uint16_t* TIM4_CCMR2 = (uint16_t*) (TIM4_ADDR + 0x1C);
  *TIM4_CCMR2 &= ~((0b11<<0)|(0b11<<8)); //output compare mode for CH3, CH4
  *TIM4_CCMR2 &= ~((0b111<<4)|(0b111<<12)); // clear bits for CH3, CH4
  *TIM4_CCMR2 |=  (0b110 << 4)|(0b110<<12); // PWM mode 1 for CH3,CH4



// enable CH1,2,3,4 output 
uint16_t* TIM4_CCER = (uint16_t*) (TIM4_ADDR + 0x20);
 *TIM4_CCER |= ( 1 << 0 )|( 1 << 4 )|( 1 << 8 )|( 1 << 12 ); // enable CH1,2,3,4 output
 
// enable counter
uint16_t* TIM4_CR1 = (uint16_t*) (TIM4_ADDR + 0x00);
 *TIM4_CR1 |= ( 1 << 0 ); // enable counter for timer4
}


void control_motor(uint8_t motor, uint16_t pulse_width)
{
 

  if(pulse_width <=1100) pulse_width = 1100;
  if (pulse_width >= 1950) pulse_width = 1950;






 switch(motor) {
    case 1:
        uint32_t *CCR = (uint32_t*) (TIM4_ADDR + 0x34);
        break;
    case 2:
        uint32_t *CCR = (uint32_t*) (TIM4_ADDR + 0x38);
        break;
    case 3:
       uint32_t *CCR = (uint32_t*) (TIM4_ADDR + 0x3C);
        break;
    case 4:
        uint32_t *CCR = (uint32_t*) (TIM4_ADDR + 0x40);
        break; 
 }

 *CCR = pulse_width;

}


