/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/****************************************************************************
*
* Comments:
*   This file contains the functions which write and read the SPI memories
*   using the ECSPI driver in interrupt mode.
*
****************************************************************************/

#include <stdio.h>
#include "ecspi_xfer.h"
#include "uart_imx.h"
#include "debug_console_imx.h"
#include "spi_memory.h"

/******************************************************************************
*
* Function Name : M25P32_ReadStatus
* Comments  : This function reads memory status register
* Return: Status read.
*
******************************************************************************/
uint8_t M25P32_ReadStatus(void)
{
    uint8_t Txbuffer[2];
    uint8_t Rxbuffer[2];

    PRINTF("Read memory status ... ");
    /* write instruction */
    Txbuffer[0] = SPI_MEMORY_READ_STATUS;
    Txbuffer[1] = 0xFF;
    if(!ECSPI_XFER_TransferBlocking((uint8_t*)Txbuffer, (uint8_t*)Rxbuffer, 2))
        PRINTF("Read memory status error!\n\r");

    /* The received second byte is real value of status register */
    PRINTF("0x%02x\n\r", Rxbuffer[1]);
    return Rxbuffer[1];
}

/******************************************************************************
*
* Function Name : M25P32_SetWriteEnable
* Comments  : This function sets latch to enable/disable memory write
*             operation
*
******************************************************************************/
void M25P32_SetWriteEnable(bool enable)
{
    uint8_t Txbuffer[1];
  
    if(enable)
    {
      PRINTF("Enable write latch in memory ...");
      Txbuffer[0] = SPI_MEMORY_WRITE_ENABLE;
    }
    else
    {
      PRINTF("Disable write latch in memory ...");
      Txbuffer[0] = SPI_MEMORY_WRITE_DISABLE;
    }
    /* write instruction */
    if(!ECSPI_XFER_TransferBlocking((uint8_t*)Txbuffer, 0, 1))
        PRINTF("Set memory write enable error!\n\r");

    PRINTF("OK\n\r");
}

/******************************************************************************
*
* Function Name : M25P32_SetProtection
* Comments  : This function sets write protection in memory status register
*
******************************************************************************/
void M25P32_SetProtection(bool protect)
{
    uint8_t protection;
    uint8_t Txbuffer[2];

    /* enable write operation */
    M25P32_SetWriteEnable(true);
    /* read status register */
    M25P32_ReadStatus();

    if(protect)
    {
        PRINTF("Write protect memory ... ");
        protection = 0xFF;
    }
    else
    {
        PRINTF("Write unprotect memory ... ");
        protection = 0x00;
    }

    Txbuffer[0] = SPI_MEMORY_WRITE_STATUS; 
    Txbuffer[1] = protection;
    /* write instruction */
    if(!ECSPI_XFER_TransferBlocking((uint8_t*)Txbuffer, 0, 2))
        PRINTF("Set memory protection error!\n\r");

    PRINTF("OK\n\r");
    M25P32_ReadStatus();
}

/******************************************************************************
*
* Function Name : M25P32_EraseChip
* Comments  : This function erases the whole memory SPI chip
*
******************************************************************************/
void M25P32_EraseChip(void)
{
    uint8_t Txbuffer[1];
    volatile uint32_t i, j;
  
    /* Enable Write */
    M25P32_SetWriteEnable(true);
    M25P32_ReadStatus();
  
    PRINTF("Erase whole memory chip:\n\r");
    Txbuffer[0] = SPI_MEMORY_BULK_ERASE;
    /* write instruction */
    if(!ECSPI_XFER_TransferBlocking((uint8_t*)Txbuffer, 0, 1))
        PRINTF("Erase memory error!\n\r");

    /* wait erase end */
    while(M25P32_ReadStatus() & 1)
    {
        //M25P32_ReadStatus();
        for(i=0; i<0xFFF; i++)
        for(j=0; j<0xFF; j++);
    }

    PRINTF("Erase chip ...OK\n\r");
}

/******************************************************************************
*
* Function Name : M25P32_WriteData
* Comments  : This function writes data buffer to memory using page write
* Return: Number of bytes written.
*
******************************************************************************/
uint32_t M25P32_WriteData (uint32_t addr, uint32_t size, uint8_t* data)
{
    uint8_t Txbuffer[50];
    uint32_t i;

    /* Enable Write */
    M25P32_SetWriteEnable(true);

    PRINTF("Page write %d bytes to location 0x%08x in memory:\n\r", size, addr);
  
    /* Write instruction, address and data */
    Txbuffer[0] = SPI_MEMORY_PAGE_PROGRAM;
    for(i=SPI_MEMORY_ADDRESS_BYTES; i; i--)
    {
        Txbuffer[i] = (uint8_t)(addr & 0xFF);
        addr >>= 8;
    }
    for(i=SPI_MEMORY_ADDRESS_BYTES+1; i<size+SPI_MEMORY_ADDRESS_BYTES+1; i++)
        Txbuffer[i] = *data++;
    /* write instruction */
    if(!ECSPI_XFER_TransferBlocking((uint8_t*)Txbuffer, 0, size+4))
        PRINTF("Write memory data error!\n\r");

    while(M25P32_ReadStatus() & 1)
    {
        for(i=0; i<0xFF; i++);  //wait write completed
    }

    data -= size;
    for(i=0; i<size; i++)
        PRINTF("0x%02x\t", data[i]);
    PRINTF("\n\r");
    return size;
}

/******************************************************************************
*
* Function Name : M25P32_ReadData
* Comments  : This function reads data from memory into given buffer
* Return: Number of bytes read.
*
******************************************************************************/
uint32_t M25P32_ReadData (uint32_t addr, uint32_t size, uint8_t* data)
{
    uint8_t Txbuffer[50];
    uint32_t i;

    PRINTF("Reading %d bytes from location 0x%08x in memory:\n\r", size, addr);
    /* Read instruction, address and data */
    Txbuffer[0] = SPI_MEMORY_READ_DATA;
    for(i=SPI_MEMORY_ADDRESS_BYTES; i; i--)
    {
        Txbuffer[i] = (uint8_t)(addr & 0xFF);
        addr >>= 8;
    }
    for(i=SPI_MEMORY_ADDRESS_BYTES+1; i<size+SPI_MEMORY_ADDRESS_BYTES+1; i++)
        Txbuffer[i] = 0xFF;
    /* write instruction */
    if(!ECSPI_XFER_TransferBlocking((uint8_t*)Txbuffer, data, size+4))
        PRINTF("Read memory data error!\n\r");

    for(i=0; i<size; i++)
        PRINTF("0x%02x\t", data[i+1+SPI_MEMORY_ADDRESS_BYTES]);
    PRINTF("\n\r");
    return size;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
