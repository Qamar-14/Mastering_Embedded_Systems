/*
 *
 * STM32F103x8_EXTI_driver.h
 *
 *
 *	Created on: 7/24/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */
#ifndef INC_STM32F103x8_EXTI_DRIVER_H_
#define INC_STM32F103x8_EXTI_DRIVER_H_

//-------------------------------------------------
// INCLUDES
//-------------------------------------------------

#include <STM32F103.h>
#include "GPIO_DRIVER/gpio.h"


//-------------------------------------------------
// CONFIG STRUCTURES
//-------------------------------------------------


typedef struct
{

	uint16_t EXTI_InputLineNumber;		// From 0 to 15

	GPIO_Typedef* GPIO_PORT; 		// Specifies the gpio port for the external interrupt

	uint16_t PIN;      			// Specifies the selected pin for the external interrupt

	uint8_t IVT_IRQ_NO;     		// This parameter must be set based on @ref IVT



}EXTI_GPIO_MAPPING_t;

typedef struct
{

	EXTI_GPIO_MAPPING_t EXTI_PIN; 		// Specifies the external interrupt GPIO mapping
						// This parameter must be set based on @ref EXTI_DEFINE

	uint8_t TRIGGER_CASE;     		// Specifies rising or falling edge trigger or both
						// This parameter must be set based on @ref EXTI_TRIGGER_DEFINE

	uint8_t IRQ_EN; 		   	// Enable or disable the EXTI IRQ (Configure the enable and mask bits that control the NVIC IRQ channel mapped to the
						// External Interrupt Controller (EXTI) so that an interrupt coming from one of the 20 lines can be correctly acknowledged.)
						// This parameter must be set based on @ref EXTI_IRQ_DEFINE

	void (* P_IRQ_CALLBACK)(void);		// Set the c function which will be called once the IRQ occurs

}EXTI_PIN_CONFIG_t;

//-------------------------------------------------
// @ref
//-------------------------------------------------

//EXTI_TRIGGER_DEFINE
#define  EXTI_TRIGGER_RISING			((uint8_t)0x0000u)
#define  EXTI_TRIGGER_FALLING			((uint8_t)0x0001u)
#define  EXTI_TRIGGER_RISING_FALLING 	((uint8_t)0x0002u)


//EXTI_IRQ_DEFINE
#define  EXTI_IRQ_ENABLE		1u
#define  EXTI_IRQ_DISABLE		0u

/*#define EXTI0	((uint16_t)0x0000u)
#define EXTI1	((uint16_t)0x0001u)
#define EXTI2	((uint16_t)0x0002u)
#define EXTI3	((uint16_t)0x0003u)
#define EXTI4	((uint16_t)0x0004u)
#define EXTI5	((uint16_t)0x0005u)
#define EXTI6	((uint16_t)0x0006u)
#define EXTI7	((uint16_t)0x0007u)
#define EXTI8	((uint16_t)0x0008u)
#define EXTI9	((uint16_t)0x0009u)
#define EXTI10	((uint16_t)0x000Au)
#define EXTI11	((uint16_t)0x000Bu)
#define EXTI12	((uint16_t)0x000Cu)
#define EXTI13	((uint16_t)0x000Du)
#define EXTI14	((uint16_t)0x000Eu)
#define EXTI15	((uint16_t)0x000Fu)
*/
#define EXTI0	0
#define EXTI1	1
#define EXTI2	2
#define EXTI3	3
#define EXTI4	4
#define EXTI5	5
#define EXTI6	6
#define EXTI7	8
#define EXTI9	9
#define EXTI10	10
#define EXTI11	11
#define EXTI12	12
#define EXTI13	13
#define EXTI14	14
#define EXTI15	15



//EXTI0
#define EXTI0PA0                (EXTI_GPIO_MAPPING_t){EXTI0, GPIOA, GPIO_PIN0, EXTI0_IRQ}
#define EXTI0PB0                (EXTI_GPIO_MAPPING_t){EXTI0, GPIOB, GPIO_PIN0, EXTI0_IRQ}
#define EXTI0PC0                (EXTI_GPIO_MAPPING_t){EXTI0, GPIOC, GPIO_PIN0, EXTI0_IRQ}
#define EXTI0PD0                (EXTI_GPIO_MAPPING_t){EXTI0, GPIOD, GPIO_PIN0, EXTI0_IRQ}


//EXTI1
#define EXTI1PA1                (EXTI_GPIO_MAPPING_t){EXTI1, GPIOA, GPIO_PIN1, EXTI1_IRQ}
#define EXTI1PB1                (EXTI_GPIO_MAPPING_t){EXTI1, GPIOB, GPIO_PIN1, EXTI1_IRQ}
#define EXTI1PC1                (EXTI_GPIO_MAPPING_t){EXTI1, GPIOC, GPIO_PIN1, EXTI1_IRQ}
#define EXTI1PD1                (EXTI_GPIO_MAPPING_t){EXTI1, GPIOD, GPIO_PIN1, EXTI1_IRQ}


//EXTI2
#define EXTI2PA2                (EXTI_GPIO_MAPPING_t){EXTI2, GPIOA, GPIO_PIN2, EXTI2_IRQ}
#define EXTI2PB2                (EXTI_GPIO_MAPPING_t){EXTI2, GPIOB, GPIO_PIN2, EXTI2_IRQ}
#define EXTI2PC2                (EXTI_GPIO_MAPPING_t){EXTI2, GPIOC, GPIO_PIN2, EXTI2_IRQ}
#define EXTI2PD2                (EXTI_GPIO_MAPPING_t){EXTI2, GPIOD, GPIO_PIN2, EXTI2_IRQ}


//EXTI3
#define EXTI3PA3                (EXTI_GPIO_MAPPING_t){EXTI3, GPIOA, GPIO_PIN3, EXTI3_IRQ}
#define EXTI3PB3                (EXTI_GPIO_MAPPING_t){EXTI3, GPIOB, GPIO_PIN3, EXTI3_IRQ}
#define EXTI3PC3                (EXTI_GPIO_MAPPING_t){EXTI3, GPIOC, GPIO_PIN3, EXTI3_IRQ}
#define EXTI3PD3                (EXTI_GPIO_MAPPING_t){EXTI3, GPIOD, GPIO_PIN3, EXTI3_IRQ}


//EXTI4
#define EXTI4PA4                (EXTI_GPIO_MAPPING_t){EXTI4, GPIOA, GPIO_PIN4, EXTI4_IRQ}
#define EXTI4PB4                (EXTI_GPIO_MAPPING_t){EXTI4, GPIOB, GPIO_PIN4, EXTI4_IRQ}
#define EXTI4PC4                (EXTI_GPIO_MAPPING_t){EXTI4, GPIOC, GPIO_PIN4, EXTI4_IRQ}
#define EXTI4PD4                (EXTI_GPIO_MAPPING_t){EXTI4, GPIOD, GPIO_PIN4, EXTI4_IRQ}


//EXTI5
#define EXTI5PA5                (EXTI_GPIO_MAPPING_t){EXTI5, GPIOA, GPIO_PIN5, EXTI5_IRQ}
#define EXTI5PB5                (EXTI_GPIO_MAPPING_t){EXTI5, GPIOB, GPIO_PIN5, EXTI5_IRQ}
#define EXTI5PC5                (EXTI_GPIO_MAPPING_t){EXTI5, GPIOC, GPIO_PIN5, EXTI5_IRQ}
#define EXTI5PD5                (EXTI_GPIO_MAPPING_t){EXTI5, GPIOD, GPIO_PIN5, EXTI5_IRQ}


//EXTI6
#define EXTI6PA6                (EXTI_GPIO_MAPPING_t){EXTI6, GPIOA, GPIO_PIN6, EXTI6_IRQ}
#define EXTI6PB6                (EXTI_GPIO_MAPPING_t){EXTI6, GPIOB, GPIO_PIN6, EXTI6_IRQ}
#define EXTI6PC6                (EXTI_GPIO_MAPPING_t){EXTI6, GPIOC, GPIO_PIN6, EXTI6_IRQ}
#define EXTI6PD6                (EXTI_GPIO_MAPPING_t){EXTI6, GPIOD, GPIO_PIN6, EXTI6_IRQ}


//EXTI7
#define EXTI7PA7                (EXTI_GPIO_MAPPING_t){EXTI7, GPIOA, GPIO_PIN7, EXTI7_IRQ}
#define EXTI7PB7                (EXTI_GPIO_MAPPING_t){EXTI7, GPIOB, GPIO_PIN7, EXTI7_IRQ}
#define EXTI7PC7                (EXTI_GPIO_MAPPING_t){EXTI7, GPIOC, GPIO_PIN7, EXTI7_IRQ}
#define EXTI7PD7                (EXTI_GPIO_MAPPING_t){EXTI7, GPIOD, GPIO_PIN7, EXTI7_IRQ}


//EXTI8
#define EXTI8PA8                (EXTI_GPIO_MAPPING_t){EXTI8, GPIOA, GPIO_PIN8, EXTI8_IRQ}
#define EXTI8PB8                (EXTI_GPIO_MAPPING_t){EXTI8, GPIOB, GPIO_PIN8, EXTI8_IRQ}
#define EXTI8PC8                (EXTI_GPIO_MAPPING_t){EXTI8, GPIOC, GPIO_PIN8, EXTI8_IRQ}
#define EXTI8PD8                (EXTI_GPIO_MAPPING_t){EXTI8, GPIOD, GPIO_PIN8, EXTI8_IRQ}


//EXTI9
#define EXTI9PA9                (EXTI_GPIO_MAPPING_t){EXTI9, GPIOA, GPIO_PIN9, EXTI9_IRQ}
#define EXTI9PB9                (EXTI_GPIO_MAPPING_t){EXTI9, GPIOB, GPIO_PIN9, EXTI9_IRQ}
#define EXTI9PC9                (EXTI_GPIO_MAPPING_t){EXTI9, GPIOC, GPIO_PIN9, EXTI9_IRQ}
#define EXTI9PD9                (EXTI_GPIO_MAPPING_t){EXTI9, GPIOD, GPIO_PIN9, EXTI9_IRQ}


//EXTI10
#define EXTI10PA10              (EXTI_GPIO_MAPPING_t){EXTI10, GPIOA, GPIO_PIN10, EXTI10_IRQ}
#define EXTI10PB10              (EXTI_GPIO_MAPPING_t){EXTI10, GPIOB, GPIO_PIN10, EXTI10_IRQ}
#define EXTI10PC10              (EXTI_GPIO_MAPPING_t){EXTI10, GPIOC, GPIO_PIN10, EXTI10_IRQ}
#define EXTI10PD10              (EXTI_GPIO_MAPPING_t){EXTI10, GPIOD, GPIO_PIN10, EXTI10_IRQ}


//EXTI11
#define EXTI11PA11              (EXTI_GPIO_MAPPING_t){EXTI11, GPIOA, GPIO_PIN11, EXTI11_IRQ}
#define EXTI11PB11              (EXTI_GPIO_MAPPING_t){EXTI11, GPIOB, GPIO_PIN11, EXTI11_IRQ}
#define EXTI11PC11              (EXTI_GPIO_MAPPING_t){EXTI11, GPIOC, GPIO_PIN11, EXTI11_IRQ}
#define EXTI11PD11              (EXTI_GPIO_MAPPING_t){EXTI11, GPIOD, GPIO_PIN11, EXTI11_IRQ}


//EXTI12
#define EXTI12PA12              (EXTI_GPIO_MAPPING_t){EXTI12, GPIOA, GPIO_PIN12, EXTI12_IRQ}
#define EXTI12PB12              (EXTI_GPIO_MAPPING_t){EXTI12, GPIOB, GPIO_PIN12, EXTI12_IRQ}
#define EXTI12PC12              (EXTI_GPIO_MAPPING_t){EXTI12, GPIOC, GPIO_PIN12, EXTI12_IRQ}
#define EXTI12PD12              (EXTI_GPIO_MAPPING_t){EXTI12, GPIOD, GPIO_PIN12, EXTI12_IRQ}


//EXTI13
#define EXTI13PA13              (EXTI_GPIO_MAPPING_t){EXTI13, GPIOA, GPIO_PIN13, EXTI13_IRQ}
#define EXTI13PB13              (EXTI_GPIO_MAPPING_t){EXTI13, GPIOB, GPIO_PIN13, EXTI13_IRQ}
#define EXTI13PC13              (EXTI_GPIO_MAPPING_t){EXTI13, GPIOC, GPIO_PIN13, EXTI13_IRQ}
#define EXTI13PD13              (EXTI_GPIO_MAPPING_t){EXTI13, GPIOD, GPIO_PIN13, EXTI13_IRQ}


//EXTI14
#define EXTI14PA14              (EXTI_GPIO_MAPPING_t){EXTI14, GPIOA, GPIO_PIN14, EXTI14_IRQ}
#define EXTI14PB14              (EXTI_GPIO_MAPPING_t){EXTI14, GPIOB, GPIO_PIN14, EXTI14_IRQ}
#define EXTI14PC14              (EXTI_GPIO_MAPPING_t){EXTI14, GPIOC, GPIO_PIN14, EXTI14_IRQ}
#define EXTI14PD14              (EXTI_GPIO_MAPPING_t){EXTI14, GPIOD, GPIO_PIN14, EXTI14_IRQ}


//EXTI15
#define EXTI15PA15              (EXTI_GPIO_MAPPING_t){EXTI15, GPIOA, GPIO_PIN15, EXTI15_IRQ}
#define EXTI15PB15              (EXTI_GPIO_MAPPING_t){EXTI15, GPIOB, GPIO_PIN15, EXTI15_IRQ}
#define EXTI15PC15              (EXTI_GPIO_MAPPING_t){EXTI15, GPIOC, GPIO_PIN15, EXTI15_IRQ}
#define EXTI15PD15              (EXTI_GPIO_MAPPING_t){EXTI15, GPIOD, GPIO_PIN15, EXTI15_IRQ}



//-------------------------------------------------
// APIs supported by "MCAL EXTI DRIVER"
//-------------------------------------------------
void MCAL_EXTI_Init		(EXTI_PIN_CONFIG_t* EXTI_Config);
void MCAL_EXTI_DeInit		(void);

void MCAL_EXTI_GPIO_Update	(EXTI_PIN_CONFIG_t* EXTI_Config);

void MCAL_EXTI_SET(EXTI_GPIO_MAPPING_t EXTI_Pin, uint8_t EXTI_TRIGGER ,uint8_t EXTI_IRQ ,void(*P_IRQ_FUNCTION)(void) );
#endif
