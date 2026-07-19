#include "clock.h"
#include <stdint.h>


#define GPIOA_ADDR_BASE 0x40020000
#define TIM5_ADDR 0x40000C00



void capture_init(){
   
    clock_enable_AHB1( GPIOA_peripheral );
    clock_enable_APB1( TIM5_peripheral );

// GPIOA pin 0 as alternate function for TIM5_CH1
    uint32_t* GPIOA_MODER = (uint32_t*) (GPIOA_ADDR_BASE + 0x00);
    *GPIOA_MODER &= ~( 0b11 << 0 ); // clear bits for PA0
    *GPIOA_MODER |= ( 0b10 << 0 );  // SET GPIOA0 AS ALTERNATE FUNCTION

    uint32_t* GPIOA_AFRL = (uint32_t*) (GPIOA_ADDR_BASE + 0x20);
    *GPIOA_AFRL &= ~( 0b1111 << 0 );
    *GPIOA_AFRL |= ( 0b0010 << 0 );  // SET GPIOA0 AS AF2 ( TIM5_CH1 )




 //use pa0 for TIM5_CH1 input capture
 //use pa1 for TIM5_CH2 input capture

    uint32_t *TIM5_PSC = (uint32_t*) (TIM5_ADDR + 0x28);
    uint32_t *TIM5_ARR = (uint32_t*) (TIM5_ADDR + 0x2C);

    *TIM5_ARR = 0xFFFFFFFF; // max value for 32 bit counter
    *TIM5_PSC = 16 - 1; 
   
   
    uint16_t *TIM5_CCMR1 = (uint16_t*) (TIM5_ADDR + 0x18);
    *TIM5_CCMR1 &= ~(0b11<<0); 
    *TIM5_CCMR1 |= (0b01<<0); //CC1 channel map with TI1 (input capture 1)

    *TIM5_CCMR1 &= ~(0b11<<8); 
    *TIM5_CCMR1 |= (0b10<<8); //CC2 channel map with TI1 (input capture 2)


    //use TIM5_CCER to set capture on rising edge
    uint16_t *TIM5_CCER = (uint16_t*) (TIM5_ADDR + 0x20);
    *TIM5_CCER &= ~(0b111<<1); //  rising edge for channel 1 ;
    *TIM5_CCER |= (1<<0); // enable capture for channel 1

    *TIM5_CCER &= ~(0b1111<<4);
    *TIM5_CCER |= (0b11<<4); // falling edge for channel 2 ;  enable capture for channel 2


    // reset value of CNT

    uint16_t *TIM5_SMCR = (uint16_t*) (TIM5_ADDR + 0x08);
    *TIM5_SMCR |= (0b100 << 0) | (0b101<<4); // reset value of CNT when rising trigger input 

    uint16_t* TIM5_CR1 = (uint16_t*) (TIM5_ADDR + 0x00);
    *TIM5_CR1 |= ( 1 << 0 ); // enable counter for timer5


}

uint32_t capture_frequency()
{
   uint32_t *TIM5_CCR1 = (uint32_t*) (TIM5_ADDR + 0x34);
   return *TIM5_CCR1;
}

uint32_t capture_pulse_width(){
          uint32_t *TIM5_CCR1 = (uint32_t*) (TIM5_ADDR + 0x34);
          uint32_t *TIM5_CCR2 = (uint32_t*) (TIM5_ADDR + 0x38);
          return *TIM5_CCR2;
}
