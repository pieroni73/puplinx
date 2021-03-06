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

/* [] END OF FILE */
#include "project.h"
#include "time.h"
#include "decadriver/deca_device_api.h"

int writetospi(uint16 headerLength, const uint8 *headerBuffer, uint32 bodylength, const uint8 *bodyBuffer){
    if(SPIM_UWB_initVar == 1u){
        for(uint16 i=0u; i < headerLength; i++){
            SPIM_UWB_WriteTxData(headerBuffer[i]);
            while((SPIM_UWB_ReadTxStatus() & SPIM_UWB_STS_SPI_DONE) == 0u);
            SPIM_UWB_ClearRxBuffer();
            SPIM_UWB_ClearTxBuffer();
        }

        for(uint32 i=0u; i < bodylength; i++){
            SPIM_UWB_WriteTxData(0x00);
            SPIM_UWB_WriteTxData(bodyBuffer[i]);
            while((SPIM_UWB_ReadTxStatus() & SPIM_UWB_STS_SPI_DONE) == 0u);
            SPIM_UWB_ClearRxBuffer();
            SPIM_UWB_ClearTxBuffer();
        }
        
        return 0u;
    }
    return -1;
}

int readfromspi(uint16 headerLength, const uint8 *headerBuffer, uint32 readlength, uint8 *readBuffer){
    if(SPIM_UWB_initVar == 1u){
        for(uint16 i=0u; i < headerLength; i++){
            SPIM_UWB_WriteTxData(headerBuffer[i]);
            while((SPIM_UWB_ReadTxStatus() & SPIM_UWB_STS_SPI_DONE) == 0u);
            SPIM_UWB_ClearRxBuffer();
            SPIM_UWB_ClearTxBuffer();
        }

        for(uint32 i=0u; i < readlength; i++){
            SPIM_UWB_WriteTxData(0x00);
            while((SPIM_UWB_ReadTxStatus() & SPIM_UWB_STS_SPI_DONE) == 0u);
            SPIM_UWB_ClearTxBuffer();
            if(SPIM_UWB_GetRxBufferSize() > 0u){
                readBuffer[i] = SPIM_UWB_ReadRxData();
            }
        }
        
        return 0u;
    }
    
    return -1u;
}

void deca_sleep(unsigned int time_ms)
{
    CyDelay(time_ms);
}