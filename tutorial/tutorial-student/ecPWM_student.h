/**
******************************************************************************
* @author  SSSLAB
* @Mod		 2021-8-12 by YKKIM  	
* @brief   Embedded Controller:  Tutorial PWMout
*					 											- LED Toggle
* 
******************************************************************************
*/
#include "stm32f411xe.h"
#include "ecGPIO.h"
#include "ecRCC.h"
//#include "ecPWM.h"
#include "ecSysTick.h"
#include "ecEXTI.h"


uint32_t _count=0;

#define LED_PIN 	5
#define BUTTON_PIN 13

void setup(void);
	
int main(void) { 
	// Initialiization --------------------------------------------------------
	
	RCC_PLL_init();                         // System Clock = 84MHz
	SysTick_init(1);                         // for delay_ms()
	GPIO_init(GPIOA, LED_PIN, AF);     // GPIOA 5 ALTERNATE function
	GPIO_ospeed(GPIOA, LED_PIN, HIGH);   // GPIOA 5 HIGH SPEED
	
	// TEMP: TIMER Register Initialiization --------------------------------------------------------		
	TIM_TypeDef *TIMx;
	TIMx = TIM2;
	
	// GPIO: ALTERNATIVE function setting
	GPIOA->AFR[0]	 = 1<<(4*LED_PIN);          // AF1 at PA5 = TIM2_CH1 (p.150)

	// TIMER: PWM setting
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;			// Enable TIMER clock
	
	TIMx->CR1 &= ~TIM_CR1_DIR;					// Direction Up-count
	
	uint32_t prescaler = 839;
	TIMx->PSC = prescaler;						// Set Timer CLK: (PSC+1)= 84Mhz/0.1MHz --> PSC= 840-1
	
	TIMx->ARR = 99;								// Set ARR:  (ARR+1) = 100kHz/1kHz  --> ARR=100-1.    
	
	TIMx->CCMR1 &= ~TIM_CCMR1_OC1M;                     // Clear ouput compare mode bits for channel 1
	TIMx->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // OC1M = 110 for PWM Mode 1 output on ch1. #define TIM_CCMR1_OC1M_1          (0x2UL << TIM_CCMR1_OC1M_Pos)
	TIMx->CCMR1	|= TIM_CCMR1_OC1PE;                     // Output 1 preload enable (make CCR1 value changable)
	TIMx->CCER &= ~TIM_CCER_CC1P;                       // select output polarity: active high	
	TIMx->CCER  |= TIM_CCER_CC1E;						// Enable output for ch1
	TIMx->CCR1  = 99/2; 								// Output Compare Register for channel 1 (default duty ratio = 50%)
	
	TIMx->CR1  |= TIM_CR1_CEN;							// Enable counter

	

	// Inifinite Loop ----------------------------------------------------------
	while(1){
		for (int i=0;i<3;i++){
		TIM2->CCR1 = 99*i/2;
		delay_ms(100);
		}
	}
}