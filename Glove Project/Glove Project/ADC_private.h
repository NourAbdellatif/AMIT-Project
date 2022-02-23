#ifndef		ADC_PRIVATE_H
#define		ADC_PRIVATE_H


#define			ADMUX_REG			*((volatile u8 *)0x27)
#define			ADCSRA_REG			*((volatile u8 *)0x26)
#define			ADCH_REG			*((volatile u8 *)0x25)
#define			ADCL_REG			*((volatile u8 *)0x24)
#define			ADC_REG				*((volatile u16 *)0x24)
#define			SFIOR_REG			*((volatile u8 *)0x50)

#define 		ADC_AVCC							1
#define 		ADC_INTERNAL						3
#define 		ADC_AREF							5

#define 		ADC_DIV_2							1
#define 		ADC_DIV_4							3
#define 		ADC_DIV_8							5
#define 		ADC_DIV_16							7
#define 		ADC_DIV_32							9
#define 		ADC_DIV_64							11
#define 		ADC_DIV_128							13


#endif