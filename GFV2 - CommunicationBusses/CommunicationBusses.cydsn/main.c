/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"
#define SAMPLES_PER_SECOND 3

static uint16_t sampleWaitTimeInMilliseconds = 1000 / SAMPLES_PER_SECOND;
static char RXBytes[4];
uint8_t RXCounter = 0;
char *pbuffer;

CY_ISR_PROTO(ISR_UART_rx_handler);
void handleByteReceived(uint8_t byteReceived);
void Read2Bytes(uint8_t addr, uint8_t data[], uint8_t address);
float getTemp(uint8_t address);

char outputBuffer[256];


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_uart_rx_StartEx(ISR_UART_rx_handler);   
    UART_1_Start();
    Pin_LED_Write(0);
    
    for(;;)
    {
        
    }
}

CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_1_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_1_ReadRxData();
        UART_1_WriteTxData(byteReceived); // echo back
        
       handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}
void handleByteReceived(uint8_t byteReceived)
{
    RXBytes[RXCounter] = byteReceived;
    RXCounter = RXCounter + 1;
    if(RXCounter == 4){
        pbuffer = &RXBytes[0];
        switch(*pbuffer){
            case 'W':
            Pin_LED_Write(1);
            break;
        }
    }
}


/* [] END OF FILE */
