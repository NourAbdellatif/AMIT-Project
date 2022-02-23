#include		"Std_Types.h"
#include		"Bit_Math.h"

#include		"ADC_interface.h"
#include		"ADC_private.h"
#include		"ADC_config.h"

#ifndef			NULL
#define			NULL				(void *)0
#endif

static void (*ADC_CallBack)(void) = NULL;

void		ADC_voidInit(void)
{
	/*	Voltage Refernce	(2.56 or 5 or any volt)			*/
	#if		ADC_VOLTAGE_REF	==	ADC_AVCC
			SET_BIT(ADMUX_REG,6);
			CLR_BIT(ADMUX_REG,7);
	#elif	ADC_VOLTAGE_REF	==	ADC_AREF	
			CLR_BIT(ADMUX_REG,6);
			CLR_BIT(ADMUX_REG,7);
	#elif	ADC_VOLTAGE_REF	==	ADC_INTERNAL
			SET_BIT(ADMUX_REG,6);
			SET_BIT(ADMUX_REG,7);
	#else
			#error	"Wrong Choice of ADC Refernce Voltage"
	#endif
	/*	PreScaller Selection								*/
	#if		ADC_PRESCALLER	==	ADC_DIV_2
			SET_BIT(ADCSRA_REG,0);
			CLR_BIT(ADCSRA_REG,1);
			CLR_BIT(ADCSRA_REG,2);
	#elif	ADC_PRESCALLER	==	ADC_DIV_4	
			CLR_BIT(ADCSRA_REG,0);
			SET_BIT(ADCSRA_REG,1);
			CLR_BIT(ADCSRA_REG,2);
	#elif	ADC_PRESCALLER	==	ADC_DIV_8
			SET_BIT(ADCSRA_REG,0);
			SET_BIT(ADCSRA_REG,1);
			CLR_BIT(ADCSRA_REG,2);
	#elif	ADC_PRESCALLER	==	ADC_DIV_16
			CLR_BIT(ADCSRA_REG,0);
			CLR_BIT(ADCSRA_REG,1);
			SET_BIT(ADCSRA_REG,2);
	#elif	ADC_PRESCALLER	==	ADC_DIV_32
			SET_BIT(ADCSRA_REG,0);
			CLR_BIT(ADCSRA_REG,1);
			SET_BIT(ADCSRA_REG,2);
	#elif	ADC_PRESCALLER	==	ADC_DIV_64
			CLR_BIT(ADCSRA_REG,0);
			SET_BIT(ADCSRA_REG,1);
			SET_BIT(ADCSRA_REG,2);
	#elif	ADC_PRESCALLER	==	ADC_DIV_128
			SET_BIT(ADCSRA_REG,0);
			SET_BIT(ADCSRA_REG,1);
			SET_BIT(ADCSRA_REG,2);
	#else
			#error	"Wrong Choice of ADC Prescaller"
	#endif	
	/*	Trigger Source Selection							*/
	
	/*	Disable ADC											*/
	CLR_BIT(ADCSRA_REG,7);
	/*	Disable ADC Interrupt and Clear The Flag			*/
	CLR_BIT(ADCSRA_REG,3);
	SET_BIT(ADCSRA_REG,4);
}
void		ADC_voidEnable(void)
{
			SET_BIT(ADCSRA_REG,7);
}
void		ADC_voidDisable(void)
{
			CLR_BIT(ADCSRA_REG,7);
}
void		ADC_voidEnableInterrupt(void)
{
			SET_BIT(ADCSRA_REG,3);
}
void		ADC_voidDisableInterrupt(void)
{
			CLR_BIT(ADCSRA_REG,3);
}
void		ADC_voidSetChannel(u8 ChannelId)
{
	switch(ChannelId)
	{
		case	0	:	CLR_BIT(ADMUX_REG,0);
						CLR_BIT(ADMUX_REG,1);
						CLR_BIT(ADMUX_REG,2);
						CLR_BIT(ADMUX_REG,3);
						CLR_BIT(ADMUX_REG,4);
						break;
		case	1	:	SET_BIT(ADMUX_REG,0);
						CLR_BIT(ADMUX_REG,1);
						CLR_BIT(ADMUX_REG,2);
						CLR_BIT(ADMUX_REG,3);
						CLR_BIT(ADMUX_REG,4);
						break;
		case	2	:	CLR_BIT(ADMUX_REG,0);
						SET_BIT(ADMUX_REG,1);
						CLR_BIT(ADMUX_REG,2);
						CLR_BIT(ADMUX_REG,3);
						CLR_BIT(ADMUX_REG,4);
						break;
		case	3	:	SET_BIT(ADMUX_REG,0);
						SET_BIT(ADMUX_REG,1);
						CLR_BIT(ADMUX_REG,2);
						CLR_BIT(ADMUX_REG,3);
						CLR_BIT(ADMUX_REG,4);
						break;
		case	4	:	CLR_BIT(ADMUX_REG,0);
						CLR_BIT(ADMUX_REG,1);
						SET_BIT(ADMUX_REG,2);
						CLR_BIT(ADMUX_REG,3);
						CLR_BIT(ADMUX_REG,4);
						break;
		case	5	:	SET_BIT(ADMUX_REG,0);
						CLR_BIT(ADMUX_REG,1);
						SET_BIT(ADMUX_REG,2);
						CLR_BIT(ADMUX_REG,3);
						CLR_BIT(ADMUX_REG,4);
						break;
		case	6	:	CLR_BIT(ADMUX_REG,0);
						SET_BIT(ADMUX_REG,1);
						SET_BIT(ADMUX_REG,2);
						CLR_BIT(ADMUX_REG,3);
						CLR_BIT(ADMUX_REG,4);
						break;
		case	7	:	SET_BIT(ADMUX_REG,0);
						SET_BIT(ADMUX_REG,1);
						SET_BIT(ADMUX_REG,2);
						CLR_BIT(ADMUX_REG,3);
						CLR_BIT(ADMUX_REG,4);
						break;
	}
	
}
u16			ADC_u16ReadValue(void)
{
	/*			Start Conversion					*/
	SET_BIT(ADCSRA_REG,6);
	/*			Polling								*/
	while((GET_BIT(ADCSRA_REG,4)==0));
	/*			Read the Value						*/
	return	ADC_REG;
	
}

void		ADC_voidSetCallBack(void (*Copy_Pf)(void))
{
	ADC_CallBack = Copy_Pf;
}

void		__vector_16	(void)
{
	ADC_CallBack();
}
