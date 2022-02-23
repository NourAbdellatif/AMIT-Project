#ifndef		ADC_INTERFACE_H
#define		ADC_INTERFACE_H

void		ADC_voidInit(void);
void		ADC_voidEnable(void);
void		ADC_voidDisable(void);

void		ADC_voidEnableInterrupt(void);
void		ADC_voidDisableInterrupt(void);

void		ADC_voidSetChannel(u8 ChannelId);
u16			ADC_u16ReadValue(void);

void		ADC_voidSetCallBack(void (*Copy_Pf)(void));
void		__vector_16	(void)	__attribute__((signal,used));

#endif