#include <stdint.h>
#include <stm32f4xx.h>
#include <SysTickDelay.h>

// East Led  PIN defines
#define GREEN_E 5
#define RED_E 10
#define YELLOW_E 4

// North Led PIN defines
#define GREEN_N 7
#define RED_N 9
#define YELLOW_N 6

void GPIO_init(void);


// Finite State Machine
typedef struct traffic_light{
	unsigned long out[2];
	unsigned long wait;
	unsigned long next[2];
//  INPUT: North traffic = Button Not Pressed (0), East Traffic = Button Pressed (1)
} traffic_light;


// Possible States
traffic_light state[4] = {
				{
						{GREEN_N, RED_E},
						100,
						{0,1}
				}, {
						{YELLOW_N, RED_E},
						200,
						{2,2} // always goes to next state
				}, {
						{RED_N, GREEN_E},
						100,
						{3,2}
				}, {
						{RED_N, YELLOW_E},
						200,
						{0,0} // always goes to next state
				},
		};

unsigned long currState = 0;
int main(void) {
	GPIO_init();
	SysTick_Init();

    /* Loop forever */
	while (1) {
		// OUTPUT
		GPIOA->ODR |= (1 << state[currState].out[0]); // North
		GPIOB->ODR |= (1 << state[currState].out[1]); // East

		// WAIT
		SysTick_Delay10ms(state[currState].wait);

		// TURN OFF
		GPIOA->ODR &= ~(1 << state[currState].out[0]); // North
		GPIOB->ODR &= ~(1 << state[currState].out[1]); // East

		// NEXT
		currState = state[currState].next[~GPIOC->IDR & (1 << 0)];
	};									//~ due to Negative logic
}

void GPIO_init(void) {
	// Enable Clock Peripherals
	RCC->AHB1ENR |= (1<<0); //Enables GPIOA peripheral (North)
	RCC->AHB1ENR |= (1<<1); //Enables GPIOB peripheral (East)
	RCC->AHB1ENR |= (1<<2); //Enables GPIOC peripheral (Button)


	/// North
	// RED
	//Set GPIOA_9 as Output (MODER[19:18] = 01)
	GPIOA->MODER &= ~(1<<19);
	GPIOA->MODER |= (1<<18);
	GPIOA->OTYPER &= ~(1<<9); // push-pull
	GPIOA->ODR &= ~(1<<9); //Initializes as LOW

	// YELLOW
	//Set GPIOA_6 as Output (MODER[13:12] = 01)
	GPIOA->MODER &= ~(1<<13);
	GPIOA->MODER |= (1<<12);
	GPIOA->OTYPER &= ~(1<<6); // push-pull
	GPIOA->ODR &= ~(1<<6); //Initializes as LOW

	// GREEN
	//Set GPIOA_7 as Output (MODER[15:14] = 01)
	GPIOA->MODER &= ~(1<<15);
	GPIOA->MODER |= (1<<14);
	GPIOA->OTYPER &= ~(1<<7); // push-pull
	GPIOA->ODR &= ~(1<<7); //Initializes as LOW


	///East
	// RED
	//Set GPIOB_10 as Output (MODER[21:20] = 01)
	GPIOB->MODER &= ~(1<<21);
	GPIOB->MODER |= (1<<20);
	GPIOB->OTYPER &= ~(1<<10); // push-pull
	GPIOB->ODR &= ~(1<<10); //Initializes as LOW

	// YELLOW
	//Set GPIOB_4 as Output (MODER[9:8] = 01)
	GPIOB->MODER &= ~(1<<9);
	GPIOB->MODER |= (1<<8);
	GPIOB->OTYPER &= ~(1<<4); // push-pull
	GPIOB->ODR &= ~(1<<4); //Initializes as LOW

	// GREEN
	//Set GPIOB_5 as Output (MODER[11:10] = 01)
	GPIOB->MODER &= ~(1<<11);
	GPIOB->MODER |= (1<<10);
	GPIOB->OTYPER &= ~(1<<5); // push-pull
	GPIOB->ODR &= ~(1<<5); //Initializes as LOW


	/// Button
	//Set GPIOC_0 as Input (MODER[1:0] = 00)
	GPIOC->MODER &= ~(1<<1);
	GPIOC->MODER &= ~(1<<0);
	//Set GPIOC_0 as Pull-up (negative logic) (PUPDR[1:0] = 01)
	GPIOC->PUPDR &= ~(1<<1);
	GPIOC->PUPDR |= (1<<0);
}
