#include <stdint.h>
#include "clock.h"

#define ADDR_EXTI 0x40013C00
#define ADDR_NVIC 0xE000E100

void exti0_init()
{
     clock_enable_AHB1(GPIOA_peripheral);

     uint32_t* EXTI_RTSR = (uint32_t*) (ADDR_EXTI + 0x08);
     *EXTI_RTSR |= (1<<0);    //set rising for EXTI0

     uint32_t* EXTI_IMR = (uint32_t*) (ADDR_EXTI + 0x00);
     *EXTI_IMR |= ( 1<< 0);  // enable EXTI0

     // setup NVIC to manage interupt from EXTI
     // ARM M4 ref manual
     // exti0 in the position 6 in vector table ( ISER0 - bit 6 )
     uint32_t* NVIC_ISER0 = (uint32_t*) (ADDR_NVIC + 0x00);
     *NVIC_ISER0 |= (1<<6);
}

void exti0_handler()
{
     uint32_t* EXTI_PR = (uint32_t*) (ADDR_EXTI + 0x14);
     *EXTI_PR |= ( 1<< 0);  // clear interrupt event flag
}
