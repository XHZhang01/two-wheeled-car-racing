/* EGR */

#include <hw_types.h>
#include<uartStdio.h>
#include<soc_AM335x.h>
#include<hw_tsc_adc_ss.h>

int main() {

	/* Activate ADC */
	HWREG(SOC_CM_WKUP_REGS + (0Xbc)) &= ~(0x3);
	HWREG(SOC_CM_WKUP_REGS + (0Xbc)) |= (0x2);

	/* Deactivate WriteProtect */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_CTRL) |= (1 << 2);

	/* Choose Steps */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPENABLE) |= (1 << 2);

	/* Mode */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) &= ~((1 << 0)|(1 << 1));
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) |= (1 << 0);

	/* Analog pins */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) &= ~((1 << 19)|(1 << 20)|(1 << 21)|(1 << 22));
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) |= (1 << 19);

	/* Positive reference voltage: VDDA */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) &= ~((1 << 12)|(1 << 14));

	/* FIFO */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) &= ~(1 << 26);

	/* 16 samples avergae */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) &= ~((1 << 2)|(1 << 3)|(1 << 4));
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(1)) |= (1 << 4);

	/* Start */
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_CTRL) |= (1 << 0);

	while (1)
	{

		/* Read ADC value */
		unsigned int myadcvalue;
		myadcvalue = HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_FIFODATA(0));

		/* Output to computer screen */
		UARTprintf("Current analog value: ");
		UARTPutNum(myadcvalue);
		UARTprintf("\r\n");

	}
	return 0;
}
