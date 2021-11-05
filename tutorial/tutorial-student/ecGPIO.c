// Distributed for LAB: GPIO

#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "ecGPIO.h"

void GPIO_init(GPIO_TypeDef *Port, int pin, int mode){     
   
   if (Port == GPIOA)
      RCC_GPIOA_enable();
	 if(Port == GPIOB)
			RCC_GPIOB_enable();
   if (Port == GPIOC)
      RCC_GPIOC_enable();
   // Make it for GPIOB, GPIOD..GPIOH

   // You can make a more general function of
   // void RCC_GPIO_enable(GPIO_TypeDef *Port); 

   GPIO_mode(Port, pin, mode);
   // The rest are default values
}


// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
void GPIO_mode(GPIO_TypeDef *Port, int pin, int mode){
  Port->MODER &= ~(3UL << (2*pin));     
  Port->MODER |= mode << (2*pin);    
}


// GPIO Read
void GPIO_write(GPIO_TypeDef *Port, int pin, int output)
{
   
   if(output==HIGH)
      Port->ODR|=(1UL<<pin);
   else
      Port->ODR&=~(1UL<<pin);
}
int GPIO_read(GPIO_TypeDef *Port,int pin)
{
   int btVal=0;
   // read bit value of button
   btVal = (GPIOC->IDR)&(1UL<<pin);
   return btVal;
}
// GPIO OuputSpeed: Low speed(00), Mid speed(01), High speed(10), Very high speed(11)
void GPIO_ospeed(GPIO_TypeDef* Port, int pin, int speed){
   Port->OSPEEDR &= ~(speed << (2*pin));
   Port->OSPEEDR |= (speed << (2*pin));
}


// GPIO OutputType: Push-Pull(0), Open-Drain(1)
void GPIO_otype(GPIO_TypeDef* Port, int pin, int type){
   Port->OTYPER &= ~(type << pin);
}


// GPIO Pull-Up Pull-Down: NO PUPD(00), PU(01), PD(10), Reserved(11)
void GPIO_pudr(GPIO_TypeDef* Port, int pin, int pudr){
   Port->PUPDR &= ~(pudr << (2*pin));
   Port->PUPDR |= (pudr << (2*pin));
}
