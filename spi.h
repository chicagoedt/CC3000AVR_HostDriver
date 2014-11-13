/*
             BUTTLOAD - Butterfly ISP Programmer

              Copyright (C) Dean Camera, 2007.
              
             dean [at] fourwalledcubicle [dot] com
                  www.fourwalledcubicle.com

           Released under the GPL Licence, Version 2.

	Modified by John Sabino on 10/01/2013 for Chicago EDT.

*/
#ifndef SPI_H
#define SPI_H

#ifndef F_CPU
	#warning (CC3000AVR-HostDriver/spi.h): F_CPU not defined! Defaulting to 4MHz. 
	//#define F_CPU 4000000UL
#endif

#ifndef POWER_EN_LOW()
	#error POWER_EN_LOW() not defined! Please place a preprocessor definition of the following type in main(). POWER_EN_LOW() {PORTB &= ~(1 << PORTB0);}.
#endif

#ifndef IRQ_HIGH()
	#error IRQ_HIGH() not defined! Please place a preprocessor definition of the following type in main(). IRQ_HIGH() {PORTB |= (1 << PORTB0);}.
#endif

#ifndef IRQ_IS_LOW()
	#error IRQ_IS_LOW() not defined! Please place a preprocessor definition of the following type in main(). IRQ_IS_LOW() bit_is_clear(PINB, PINB0)
#endif

	// INCLUDES:
	#include <avr/io.h>
	#include <string.h>
	#include <util/delay.h>


	//Definitions:

	#define	CC3000_MINIMAL_TX_SIZE      (130 + 1)  
	#define	CC3000_MAXIMAL_TX_SIZE      (1519 + 1)

//	#define CC3000_RX_BUFFER_SIZE   (CC3000_MINIMAL_TX_SIZE)
//	#define CC3000_TX_BUFFER_SIZE   (CC3000_MAXIMAL_TX_SIZE)
/*	
	//*****************************************************************************
	//                  ERROR CODES
	//*****************************************************************************
	#define ESUCCESS        0
	#define EFAIL          -1
	#define EERROR          EFAIL

	//=============================================================================
*/
	#define READ                            (3)
	#define WRITE                           (1)
	#define HI(value)                       (((value) & 0xFF00) >> 8)
	#define LO(value)                       ((value) & 0x00FF)
	#define HEADERS_SIZE_EVNT               (SPI_HEADER_SIZE + 5)
	#define SPI_HEADER_SIZE                 (5)

	//=============================================================================

	#define eSPI_STATE_POWERUP              (0)
	#define eSPI_STATE_INITIALIZED          (1)
	#define eSPI_STATE_IDLE                 (2)
	#define eSPI_STATE_WRITE_IRQ            (3)
	#define eSPI_STATE_WRITE_FIRST_PORTION  (4)
	#define eSPI_STATE_WRITE_EOT            (5)
	#define eSPI_STATE_READ_IRQ             (6)
	#define eSPI_STATE_READ_FIRST_PORTION   (7)
	#define eSPI_STATE_READ_EOT             (8)

	// The magic number that resides at the end of the TX/RX buffer (1 byte after the allocated size)
	// for the purpose of detection of the overrun. The location of the memory where the magic number
	// resides shall never be written. In case it is written - the overrun occured and either recevie function
	// or send function will stuck forever.
	#define CC3000_BUFFER_MAGIC_NUMBER (0xDE)			
	//=============================================================================

	// MACROS:
//#define SPI_SPIOFF()	     MACROS{ PRR |= (1 << PRSPI); }MACROE
	/*CC3000_ASSERT_CS sets the chip select line high, and then doubles the SCK frequency to improve synchronization.*/
	#undef CC3000_ASSERT_CS 		{PORTB &= ~(1 << PORTB0); SPSR |= (1 << SPI2X);}
	#undef CC3000_DEASSERT_CS 		{PORTB |= (1 << PORTB0);}

#ifndef CC3000_ASSERT_CS
	#error CC3000_ASSERT_CS not defined! Please use the template on line 86 to setup the Chip Select assertion macro. 
#endif

#ifndef CC3000_DEASSERT_CS
	#error CC3000_DEASSERT_CS not defined! Please use the template on line 87 to setup the Chip Select deassertion macro. 
#endif

	// ======================================================================================	

	
	typedef void (*gcSpiHandleRx)(void *p);
	typedef void (*gcSpiHandleTx)(void);

	extern unsigned char wlan_tx_buffer[];
/*
	typedef struct
	{
		  gcSpiHandleRx  SPIRxHandler;

		  unsigned short usTxPacketLength;
		  unsigned short usRxPacketLength;
		  unsigned long  ulSpiState;
		  unsigned char *pTxPacket;
		  unsigned char *pRxPacket;

	} tSpiInformation;
*/
	

	// PROTOTYPES:
	extern long SPI_SPITransmit(const long Data);
	extern void SpiOpen(gcSpiHandleRx pfRxHandler);
	extern long SpiWrite(unsigned char *pUserBuffer, unsigned short usLength);
	extern void SpiClose(void);
	extern void SpiResumeSpi(void);
	extern long SpiFirstWrite(unsigned char *ucBuf, unsigned short usLength);
	extern void SpiWriteDataSynchronous(unsigned char *data, unsigned short size);
	extern void SpiReadDataSynchronous(unsigned char *data, unsigned short size);	
	extern void SpiReadHeader(void);
	extern inline init_spi(void);
	extern void SPI_IRQ(void);
	extern void SpiCleanGPIOISR(void);	
	extern long TXBufferIsEmpty(void);
	extern long RXBufferIsEmpty(void);
	
	//Additional
	extern void SpiWriteAsync(const unsigned char *data, unsigned short size);
	extern void SpiPauseSpi(void);
	extern void SSIContReadOperation(void);
	extern void cc3k_int_poll(void);

	
#endif
