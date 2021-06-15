#include <stdint.h>
#include "sysio.h"
#include "xilinx_uart_ps.h"

#define XUartPs_IsTransmitFull(BaseAddress)		0 //	 \
//	((sys_read32((BaseAddress) + XUARTPS_SR_OFFSET) & 	\
//	 (u32)XUARTPS_SR_TXFULL) == (u32)XUARTPS_SR_TXFULL)

#define XUartPs_WriteReg(BaseAddress, RegOffset, RegisterValue) \
//	sys_write32((BaseAddress) + (u32)(RegOffset), (u32)(RegisterValue))

#define XUARTPS_FIFO_OFFSET	0x0000

void XUartPs_SendByte(uint32_t BaseAddress, uint8_t Data)
{
	/* Wait until there is space in TX FIFO */
	while (XUartPs_IsTransmitFull(BaseAddress)) {
		;
	}

	/* Write the byte into the TX FIFO */
	XUartPs_WriteReg(BaseAddress, XUARTPS_FIFO_OFFSET, (u32)Data);
}
