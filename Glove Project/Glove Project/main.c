#define			F_CPU	16000000

#include		"Std_Types.h"
#include		"Bit_Math.h"

#include		"ADC_interface.h"
#include		"DIO_interface.h"
#include		"LCD_interface.h"

#include		<util/delay.h>

void readValues(
u16 Thumb,
u16 Index,
u16 Middle,
u16 Ring,
u16 Pinky
){
	//Thumb Channel
	ADC_voidSetChannel(PIN0);
	Thumb = ADC_u16ReadValue();
	Thumb = ((Thumb * 5000UL)/1024);
	//Index Channel
	ADC_voidSetChannel(PIN1);
	Index = ADC_u16ReadValue();
	Index = ((Index * 5000UL)/1024);
	//Middle Channel
	ADC_voidSetChannel(PIN2);
	Middle = ADC_u16ReadValue();
	Middle = ((Middle * 5000UL)/1024);
	//Ring Channel
	ADC_voidSetChannel(PIN3);
	Ring = ADC_u16ReadValue();
	Ring = ((Ring * 5000UL)/1024);
	//Pinky Channel
	ADC_voidSetChannel(PIN4);
	Pinky = ADC_u16ReadValue();
	Pinky = ((Pinky * 5000UL)/1024);
}

int main(void)
{
	//LCD Display
	DIO_voidSetPinDirection(PORTD,PIN1,OUTPUT);
	DIO_voidSetPinDirection(PORTD,PIN2,OUTPUT);
	DIO_voidSetPinDirection(PORTD,PIN3,OUTPUT);
	
	//Finger sensors input
	DIO_voidSetPinDirection(PORTA,PIN0,INPUT);   //Thumb
	DIO_voidSetPinDirection(PORTA,PIN1,INPUT);	 //Index
	DIO_voidSetPinDirection(PORTA,PIN2,INPUT);	 //Middle
	DIO_voidSetPinDirection(PORTA,PIN3,INPUT);	 //Ring
	DIO_voidSetPinDirection(PORTA,PIN4,INPUT);	 //Pinky
	
	//ADC Initialization
	ADC_voidInit();
	ADC_voidEnable();
	
	u16 Thumb  =0;
	u16 Index  =0;
	u16 Middle =0;
	u16 Ring   =0;
	u16 Pinky  =0;
	
	//readValues(Thumb,Index,Middle,Ring,Pinky);
	///*	LCD init	  */
	LCD_voidInit8bit();
	DIO_voidSetPortDirection(PORTC,0xFF);
	
	while(1)
	{
			ADC_voidSetChannel(PIN0);
			Thumb = ADC_u16ReadValue();
			Thumb = ((Thumb * 5000UL)/1024);
			//Index Channel
			ADC_voidSetChannel(PIN1);
			Index = ADC_u16ReadValue();
			Index = ((Index * 5000UL)/1024);
			//Middle Channel
			ADC_voidSetChannel(PIN2);
			Middle = ADC_u16ReadValue();
			Middle = ((Middle * 5000UL)/1024);
			//Ring Channel
			ADC_voidSetChannel(PIN3);
			Ring = ADC_u16ReadValue();
			Ring = ((Ring * 5000UL)/1024);
			//Pinky Channel
			ADC_voidSetChannel(PIN4);
			Pinky = ADC_u16ReadValue();
			Pinky = ((Pinky * 5000UL)/1024);
			if(Thumb>2500 && Index>2500 && Middle>2500 && Ring>2500 && Pinky>2500 )
			{
				LCD_voidGotoXY(0,0);
				LCD_voidLCDClear();
				_delay_ms(10);
				LCD_voidWriteString("Good Luck");
				_delay_ms(100);
			}
			else if(Thumb>2500 && Index<=2500 && Middle<=2500 && Ring<=2500 && Pinky<=2500 ){
				//Thumb Straight
				LCD_voidGotoXY(0,0);
				LCD_voidLCDClear();
				LCD_voidWriteString("Good Job");
				LCD_voidGotoXY(1,1);
				_delay_ms(100);
			}
			else if(Thumb<=2500 && Index>2500 && Middle<=2500 && Ring<=2500 && Pinky>2500 )
			{
				// Index and Pinky Straight
				LCD_voidGotoXY(0,0);
				LCD_voidLCDClear();
				_delay_ms(10);
				LCD_voidWriteString("Awesome");
				_delay_ms(100);
			}
			else if(Thumb>2500 && Index>2500 && Middle<=2500 && Ring<=2500 && Pinky>2500 )
			{
				// Thumb,Index and Pinky Straight
				LCD_voidGotoXY(0,0);
				LCD_voidLCDClear();
				_delay_ms(10);
				LCD_voidWriteString("I love you");
				_delay_ms(100);
			}
			else if(Thumb>2500 && Index>2500 && Middle>2500 && Ring<=2500 && Pinky>2500 )
			{
				// Thumb,Index,middle and Pinky Straight
				LCD_voidGotoXY(0,0);
				LCD_voidLCDClear();
				_delay_ms(10);
				LCD_voidWriteString("I love you alot");
				_delay_ms(100);
			}
			else if(Thumb<=2500 && Index>2500 && Middle>2500 && Ring<=2500 && Pinky<=2500 ){
				//Thumb Straight
				LCD_voidGotoXY(0,0);
				LCD_voidLCDClear();
				LCD_voidWriteString("I see you");
				LCD_voidGotoXY(1,1);
				_delay_ms(100);
			}
			else if(Thumb<=2500 && Index>2500 && Middle<=2500 && Ring<=2500 && Pinky<=2500 ){
				//Thumb Straight
				LCD_voidGotoXY(0,0);
				LCD_voidLCDClear();
				LCD_voidWriteString("You");
				LCD_voidGotoXY(1,1);
				_delay_ms(100);
			}
			
	}
	return 0 ;
}