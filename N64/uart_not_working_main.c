#include <stdio.h>
#include <inttypes.h>
#include "drivers/mss_uart/mss_uart.h"

//#define CONTROLLER_DATA_REG ((uint8_t *) FPGA_FABRIC_BASE)
//#define CONTROLLER_DATA_REG ((uint8_t *) 0x40050000)

int main()
{
	uint8_t tx_buff[4];
	uint8_t rx_buff[4];
	uint8_t tx_msg_length; //in bytes
	uint8_t rx_msg_length; //in bytes
	int i;

//	MSS_UART_init(
//			&g_mss_uart1,
//			MSS_UART_57600_BAUD,
//			MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT
//	);
//
//	MSS_UART_init(
//				&g_mss_uart0,
//				MSS_UART_57600_BAUD,
//				MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT
//		);
//
//	while(1) {
//		tx_msg_length = 4;
//		for(i = 0; i < tx_msg_length; i++){
//			tx_buff[i] = *(CONTROLLER_DATA_REG + i);
//		}
//		printf("hello world");
//		//printf("%u", (unsigned) *tx_buff);
//		//MSS_UART_polled_tx(&g_mss_uart1, tx_buff, tx_msg_length);
//
//		rx_msg_length = 4;
//		if(MSS_UART_get_rx(&g_mss_uart1, rx_buff, rx_msg_length)) {
//			//printf("%u", (unsigned)*rx_buff);
//		}
//		else {
//			printf("FAIL");
//		}
//	}
	return 0;
}
