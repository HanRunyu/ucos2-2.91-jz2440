/**************************************************************************
*                                                                         *
*   PROJECT     : ARM port for UCOS-II                                    *
*                                                                         *
*   MODULE      : S3C2440.h                                               *
*                                                                         *
*	AUTHOR		: HanRunyu												  *
*				  URL  : http://github.com/HanRunyu 					  *
*																		  *
*	PROCESSOR	: s3c2440  (32 bit ARM920T RISC core from Samsung)		  *
*																		  *
*	TOOLCHAIN	: arm-linux-gnueabi-gcc(Linaro 7.5.0)					  *
*                                                                         *
*   DESCRIPTION :                                                         *
*   S3C2440 processor register definition header file.                    *
*                                                                         *
**************************************************************************/



#ifndef __S3C2410X_H__
#define __S3C2410X_H__


#include "def.h"
#include "frmwrk.h"


#ifdef __cplusplus
extern "C" {
#endif

/* ********************************************************************* */
/* Interface macro & data definition */

// Memory control 
#define rBWSCON    (*(volatile U32 *)0x48000000) //Bus width & wait status
#define rBANKCON0  (*(volatile U32 *)0x48000004) //Boot ROM control
#define rBANKCON1  (*(volatile U32 *)0x48000008) //BANK1 control
#define rBANKCON2  (*(volatile U32 *)0x4800000c) //BANK2 cControl
#define rBANKCON3  (*(volatile U32 *)0x48000010) //BANK3 control
#define rBANKCON4  (*(volatile U32 *)0x48000014) //BANK4 control
#define rBANKCON5  (*(volatile U32 *)0x48000018) //BANK5 control
#define rBANKCON6  (*(volatile U32 *)0x4800001c) //BANK6 control
#define rBANKCON7  (*(volatile U32 *)0x48000020) //BANK7 control
#define rREFRESH   (*(volatile U32 *)0x48000024) //DRAM/SDRAM refresh
#define rBANKSIZE  (*(volatile U32 *)0x48000028) //Flexible Bank Size
#define rMRSRB6    (*(volatile U32 *)0x4800002c) //Mode register set for SDRAM
#define rMRSRB7    (*(volatile U32 *)0x48000030) //Mode register set for SDRAM


// USB Host
#define rHcRevision        		(*(volatile U32 *)0x49000000) //Control and status group
#define rHcControl          	(*(volatile U32 *)0x49000004) //
#define rHcCommonStatus     	(*(volatile U32 *)0x49000008) //
#define rHcInterruptStatus  	(*(volatile U32 *)0x4900000c) //
#define rHcInterruptEnable  	(*(volatile U32 *)0x49000010) //
#define rHcInterruptDisable 	(*(volatile U32 *)0x49000014) //
#define rHcHCCA             	(*(volatile U32 *)0x49000018) //Memory pointer group
#define rHcPeriodCuttentED  	(*(volatile U32 *)0x4900001c) //
#define rHcControlHeadED    	(*(volatile U32 *)0x49000020) //
#define rHcControlCurrentED 	(*(volatile U32 *)0x49000024) //
#define rHcBulkHeadED			(*(volatile U32 *)0x49000028) //
#define rHcBulkCurrentED    	(*(volatile U32 *)0x4900002c) //
#define rHcDoneHead         	(*(volatile U32 *)0x49000030) //Frame counter group
#define rHcRmInterval       	(*(volatile U32 *)0x49000034) //
#define rHcFmRemaining      	(*(volatile U32 *)0x49000038) //
#define rHcFmNumber         	(*(volatile U32 *)0x4900003c) //
#define rHcPeriodicStart    	(*(volatile U32 *)0x49000040) //
#define rHcLSThreshold      	(*(volatile U32 *)0x49000044) //
#define rHcRhDescriptorA    	(*(volatile U32 *)0x49000048) //Root hub group
#define rHcRhDescriptorB    	(*(volatile U32 *)0x4900004c) //
#define rHcRhStatus         	(*(volatile U32 *)0x49000050) //
#define rHcRhPortStatus1		(*(volatile U32 *)0x49000054) //
#define rHcRhPortStatus2		(*(volatile U32 *)0x49000058) //


// INTERRUPT
#define rSRCPND     (*(volatile U32 *)0x4a000000) //Interrupt request status
#define rINTMOD     (*(volatile U32 *)0x4a000004) //Interrupt mode control
#define rINTMSK     (*(volatile U32 *)0x4a000008) //Interrupt mask control
#define rPRIORITY   (*(volatile U32 *)0x4a00000c) //IRQ priority control
#define rINTPND     (*(volatile U32 *)0x4a000010) //Interrupt request status
#define rINTOFFSET  (*(volatile U32 *)0x4a000014) //Interruot request source offset
#define rSUBSRCPND  (*(volatile U32 *)0x4a000018) //Sub source pending
#define rINTSUBMSK  (*(volatile U32 *)0x4a00001c) //Interrupt sub mask


// DMA
#define rDISRC0     (*(volatile U32 *)0x4b000000) //DMA 0 Initial source
#define rDISRCC0    (*(volatile U32 *)0x4b000004) //DMA 0 Initial source control
#define rDIDST0     (*(volatile U32 *)0x4b000008) //DMA 0 Initial Destination
#define rDIDSTC0    (*(volatile U32 *)0x4b00000c) //DMA 0 Initial Destination control
#define rDCON0      (*(volatile U32 *)0x4b000010) //DMA 0 Control
#define rDSTAT0     (*(volatile U32 *)0x4b000014) //DMA 0 Status
#define rDCSRC0     (*(volatile U32 *)0x4b000018) //DMA 0 Current source
#define rDCDST0     (*(volatile U32 *)0x4b00001c) //DMA 0 Current destination
#define rDMASKTRIG0 (*(volatile U32 *)0x4b000020) //DMA 0 Mask trigger

#define rDISRC1     (*(volatile U32 *)0x4b000040) //DMA 1 Initial source
#define rDISRCC1    (*(volatile U32 *)0x4b000044) //DMA 1 Initial source control
#define rDIDST1     (*(volatile U32 *)0x4b000048) //DMA 1 Initial Destination
#define rDIDSTC1    (*(volatile U32 *)0x4b00004c) //DMA 1 Initial Destination control
#define rDCON1      (*(volatile U32 *)0x4b000050) //DMA 1 Control
#define rDSTAT1     (*(volatile U32 *)0x4b000054) //DMA 1 Status
#define rDCSRC1     (*(volatile U32 *)0x4b000058) //DMA 1 Current source
#define rDCDST1     (*(volatile U32 *)0x4b00005c) //DMA 1 Current destination
#define rDMASKTRIG1 (*(volatile U32 *)0x4b000060) //DMA 1 Mask trigger

#define rDISRC2     (*(volatile U32 *)0x4b000080) //DMA 2 Initial source
#define rDISRCC2    (*(volatile U32 *)0x4b000084) //DMA 2 Initial source control
#define rDIDST2     (*(volatile U32 *)0x4b000088) //DMA 2 Initial Destination
#define rDIDSTC2    (*(volatile U32 *)0x4b00008c) //DMA 2 Initial Destination control
#define rDCON2      (*(volatile U32 *)0x4b000090) //DMA 2 Control
#define rDSTAT2     (*(volatile U32 *)0x4b000094) //DMA 2 Status
#define rDCSRC2     (*(volatile U32 *)0x4b000098) //DMA 2 Current source
#define rDCDST2     (*(volatile U32 *)0x4b00009c) //DMA 2 Current destination
#define rDMASKTRIG2 (*(volatile U32 *)0x4b0000a0) //DMA 2 Mask trigger

#define rDISRC3     (*(volatile U32 *)0x4b0000c0) //DMA 3 Initial source
#define rDISRCC3    (*(volatile U32 *)0x4b0000c4) //DMA 3 Initial source control
#define rDIDST3     (*(volatile U32 *)0x4b0000c8) //DMA 3 Initial Destination
#define rDIDSTC3    (*(volatile U32 *)0x4b0000cc) //DMA 3 Initial Destination control
#define rDCON3      (*(volatile U32 *)0x4b0000d0) //DMA 3 Control
#define rDSTAT3     (*(volatile U32 *)0x4b0000d4) //DMA 3 Status
#define rDCSRC3     (*(volatile U32 *)0x4b0000d8) //DMA 3 Current source
#define rDCDST3     (*(volatile U32 *)0x4b0000dc) //DMA 3 Current destination
#define rDMASKTRIG3 (*(volatile U32 *)0x4b0000e0) //DMA 3 Mask trigger


// CLOCK & POWER MANAGEMENT
#define rLOCKTIME   (*(volatile U32 *)0x4c000000) //PLL lock time counter
#define rMPLLCON    (*(volatile U32 *)0x4c000004) //MPLL Control
#define rUPLLCON    (*(volatile U32 *)0x4c000008) //UPLL Control
#define rCLKCON     (*(volatile U32 *)0x4c00000c) //Clock generator control
#define rCLKSLOW    (*(volatile U32 *)0x4c000010) //Slow clock control
#define rCLKDIVN    (*(volatile U32 *)0x4c000014) //Clock divider control
#define rCAMDIVN	(*(volatile U32 *)0x4c000018) //Camera clock divider control


// LCD CONTROLLER
#define rLCDCON1    (*(volatile U32 *)0x4d000000) //LCD control 1
#define rLCDCON2    (*(volatile U32 *)0x4d000004) //LCD control 2
#define rLCDCON3    (*(volatile U32 *)0x4d000008) //LCD control 3
#define rLCDCON4    (*(volatile U32 *)0x4d00000c) //LCD control 4
#define rLCDCON5    (*(volatile U32 *)0x4d000010) //LCD control 5
#define rLCDSADDR1  (*(volatile U32 *)0x4d000014) //STN/TFT Frame buffer start address 1
#define rLCDSADDR2  (*(volatile U32 *)0x4d000018) //STN/TFT Frame buffer start address 2
#define rLCDSADDR3  (*(volatile U32 *)0x4d00001c) //STN/TFT Virtual screen address set
#define rREDLUT     (*(volatile U32 *)0x4d000020) //STN Red lookup table
#define rGREENLUT   (*(volatile U32 *)0x4d000024) //STN Green lookup table 
#define rBLUELUT    (*(volatile U32 *)0x4d000028) //STN Blue lookup table
#define rDITHMODE   (*(volatile U32 *)0x4d00004c) //STN Dithering mode
#define rTPAL       (*(volatile U32 *)0x4d000050) //TFT Temporary palette
#define rLCDINTPND  (*(volatile U32 *)0x4d000054) //LCD Interrupt pending
#define rLCDSRCPND  (*(volatile U32 *)0x4d000058) //LCD Interrupt source
#define rLCDINTMSK  (*(volatile U32 *)0x4d00005c) //LCD Interrupt mask
#define rTCONSEL	(*(volatile U32 *)0x4d000060) //TCON(LPC3600/LCC3600) control


// NAND flash
#define rNFCONF     (*(volatile U32 *)0x4e000000) //NAND Flash configuration
#define rNFCONT		(*(volatile U32 *)0x4e000004) //NAND flash control
#define rNFCMD      (*(volatile U8 *)0x4e000008)  //NADD Flash command
#define rNFADDR     (*(volatile U8 *)0x4e00000c)  //NAND Flash address
#define rNFDATA     (*(volatile U8 *)0x4e000010)  //NAND Flash data
#define rNFMECCD0   (*(volatile U32 *)0x4e000014) //NAND flash main area ECC0/1
#define rNFMECCD1	(*(volatile U32 *)0x4e000018) //NAND flash main area ECC2/3
#define rNFSECCD	(*(volatile U32 *)0x4e00001c) //NAND flash spare area ECC
#define rNFSTAT     (*(volatile U32 *)0x4e000020) //NAND Flash operation status
#define rNFESTAT0	(*(volatile U32 *)0x4e000024) //NAND flash ECC status for I/O[7:0]
#define rNFESTAT1	(*(volatile U32 *)0x4e000028) //NAND flash ECC status for I/O[15:8]
#define rNFMECC0	(*(volatile U32 *)0x4e00002c) //NAND flash main area ECC0 status
#define rNFMECC1	(*(volatile U32 *)0x4e000030) //NAND flash main area ECC1 status
#define rNFSECC		(*(volatile U32 *)0x4e000034) //NAND flash spare area ECC status
#define rNFSBLK		(*(volatile U32 *)0x4e000038) //NAND flash start block address
#define rNFEBLK		(*(volatile U32 *)0x4e00003c) //NAND flash end block address


// Camera Interface
#define rCISRCFMT		(*(volatile U32 *)0x4f000000) //Input source format                                
#define rCIWDOFST       (*(volatile U32 *)0x4f000004) //Window offset register                             
#define rCIGCTRL        (*(volatile U32 *)0x4f000008) //Global control register                            
#define rCICOYSA1       (*(volatile U32 *)0x4f000018) //Y 1st frame start address for codec DMA            
#define rCICOYSA2       (*(volatile U32 *)0x4f00001c) //Y 2nd frame start address for codec DMA            
#define rCICOYSA3       (*(volatile U32 *)0x4f000020) //Y 3nd frame start address for codec DMA            
#define rCICOYSA4       (*(volatile U32 *)0x4f000024) //Y 4th frame start address for codec DMA            
#define rCICOCBSA1      (*(volatile U32 *)0x4f000028) //Cb 1st frame start address for codec DMA           
#define rCICOCBSA2      (*(volatile U32 *)0x4f00002c) //Cb 2nd frame start address for codec DMA           
#define rCICOCBSA3      (*(volatile U32 *)0x4f000030) //Cb 3nd frame start address for codec DMA           
#define rCICOCBSA4      (*(volatile U32 *)0x4f000034) //Cb 4th frame start address for codec DMA           
#define rCICOCRSA1      (*(volatile U32 *)0x4f000038) //Cr 1st frame start address for codec DMA           
#define rCICOCRSA2      (*(volatile U32 *)0x4f00003c) //Cr 2nd frame start address for codec DMA           
#define rCICOCRSA3      (*(volatile U32 *)0x4f000040) //Cr 3nd frame start address for codec DMA           
#define rCICOCRSA4      (*(volatile U32 *)0x4f000044) //Cr 4th frame start address for codec DMA           
#define rCICOTRGFMT     (*(volatile U32 *)0x4f000048) //Target image format of codec DMA                   
#define rCICOCTRL       (*(volatile U32 *)0x4f00004c) //Codec DMA control related                          
#define rCICOSCPRERATIO (*(volatile U32 *)0x4f000050) //Codec pre-scaler ratio control                     
#define rCICOSCPREDST   (*(volatile U32 *)0x4f000054) //Codec pre-scaler destination format                
#define rCICOSCCTRL     (*(volatile U32 *)0x4f000058) //Codec main-scaler control                          
#define rCICOTAREA      (*(volatile U32 *)0x4f00005c) //Codec scaler target area                           
#define rCICOSTATUS     (*(volatile U32 *)0x4f000064) //Codec path status                                  
#define rCIPRCLRSA1     (*(volatile U32 *)0x4f00006c) //RGB 1st frame start address for preview DMA        
#define rCIPRCLRSA2     (*(volatile U32 *)0x4f000070) //RGB 2nd frame start address for preview DMA        
#define rCIPRCLRSA3     (*(volatile U32 *)0x4f000074) //RGB 3nd frame start address for preview DMA        
#define rCIPRCLRSA4     (*(volatile U32 *)0x4f000078) //RGB 4th frame start address for preview DMA        
#define rCIPRTRGFMT     (*(volatile U32 *)0x4f00007c) //Target image format of preview DMA                 
#define rCIPRCTRL       (*(volatile U32 *)0x4f000080) //Preview DMA control related                        
#define rCIPRSCPRERATIO (*(volatile U32 *)0x4f000084) //Preview pre-scaler ratio control                   
#define rCIPRSCPREDST   (*(volatile U32 *)0x4f000088) //Preview pre-scaler destination format              
#define rCIPRSCCTRL     (*(volatile U32 *)0x4f00008c) //Preview main-scaler control                        
#define rCIPRTAREA      (*(volatile U32 *)0x4f000090) //Preview scaler target area                         
#define rCIPRSTATUS     (*(volatile U32 *)0x4f000098) //Preview path status                                
#define rCIIMGCPT       (*(volatile U32 *)0x4f0000a0) //Image capture enable command       


// UART
#define rULCON0     (*(volatile U32 *)0x50000000) //UART 0 Line control
#define rUCON0      (*(volatile U32 *)0x50000004) //UART 0 Control
#define rUFCON0     (*(volatile U32 *)0x50000008) //UART 0 FIFO control
#define rUMCON0     (*(volatile U32 *)0x5000000c) //UART 0 Modem control
#define rUTRSTAT0   (*(volatile U32 *)0x50000010) //UART 0 Tx/Rx status
#define rUERSTAT0   (*(volatile U32 *)0x50000014) //UART 0 Rx error status
#define rUFSTAT0    (*(volatile U32 *)0x50000018) //UART 0 FIFO status
#define rUMSTAT0    (*(volatile U32 *)0x5000001c) //UART 0 Modem status
#define rUBRDIV0    (*(volatile U32 *)0x50000028) //UART 0 Baud rate divisor

#define rULCON1     (*(volatile U32 *)0x50004000) //UART 1 Line control
#define rUCON1      (*(volatile U32 *)0x50004004) //UART 1 Control
#define rUFCON1     (*(volatile U32 *)0x50004008) //UART 1 FIFO control
#define rUMCON1     (*(volatile U32 *)0x5000400c) //UART 1 Modem control
#define rUTRSTAT1   (*(volatile U32 *)0x50004010) //UART 1 Tx/Rx status
#define rUERSTAT1   (*(volatile U32 *)0x50004014) //UART 1 Rx error status
#define rUFSTAT1    (*(volatile U32 *)0x50004018) //UART 1 FIFO status
#define rUMSTAT1    (*(volatile U32 *)0x5000401c) //UART 1 Modem status
#define rUBRDIV1    (*(volatile U32 *)0x50004028) //UART 1 Baud rate divisor

#define rULCON2     (*(volatile U32 *)0x50008000) //UART 2 Line control
#define rUCON2      (*(volatile U32 *)0x50008004) //UART 2 Control
#define rUFCON2     (*(volatile U32 *)0x50008008) //UART 2 FIFO control
#define rUMCON2     (*(volatile U32 *)0x5000800c) //UART 2 Modem control
#define rUTRSTAT2   (*(volatile U32 *)0x50008010) //UART 2 Tx/Rx status
#define rUERSTAT2   (*(volatile U32 *)0x50008014) //UART 2 Rx error status
#define rUFSTAT2    (*(volatile U32 *)0x50008018) //UART 2 FIFO status
#define rUMSTAT2    (*(volatile U32 *)0x5000801c) //UART 2 Modem status
#define rUBRDIV2    (*(volatile U32 *)0x50008028) //UART 2 Baud rate divisor

#ifdef __BIG_ENDIAN
#define rUTXH0      (*(volatile U8 *)0x50000023) //UART 0 Transmission Hold
#define rURXH0      (*(volatile U8 *)0x50000027) //UART 0 Receive buffer
#define rUTXH1      (*(volatile U8 *)0x50004023) //UART 1 Transmission Hold
#define rURXH1      (*(volatile U8 *)0x50004027) //UART 1 Receive buffer
#define rUTXH2      (*(volatile U8 *)0x50008023) //UART 2 Transmission Hold
#define rURXH2      (*(volatile U8 *)0x50008027) //UART 2 Receive buffer

#define WrUTXH0(ch) (*(volatile U8 *)0x50000023)=(U8)(ch)
#define RdURXH0()   (*(volatile U8 *)0x50000027)
#define WrUTXH1(ch) (*(volatile U8 *)0x50004023)=(U8)(ch)
#define RdURXH1()   (*(volatile U8 *)0x50004027)
#define WrUTXH2(ch) (*(volatile U8 *)0x50008023)=(U8)(ch)
#define RdURXH2()   (*(volatile U8 *)0x50008027)

#define UTXH0       (0x50000020+3)  //Byte_access address by DMA
#define URXH0       (0x50000024+3)
#define UTXH1       (0x50004020+3)
#define URXH1       (0x50004024+3)
#define UTXH2       (0x50008020+3)
#define URXH2       (0x50008024+3)

#else //Little Endian
#define rUTXH0 (*(volatile U8 *)0x50000020) //UART 0 Transmission Hold
#define rURXH0 (*(volatile U8 *)0x50000024) //UART 0 Receive buffer
#define rUTXH1 (*(volatile U8 *)0x50004020) //UART 1 Transmission Hold
#define rURXH1 (*(volatile U8 *)0x50004024) //UART 1 Receive buffer
#define rUTXH2 (*(volatile U8 *)0x50008020) //UART 2 Transmission Hold
#define rURXH2 (*(volatile U8 *)0x50008024) //UART 2 Receive buffer

#define WrUTXH0(ch) (*(volatile U8 *)0x50000020)=(U8)(ch)
#define RdURXH0()   (*(volatile U8 *)0x50000024)
#define WrUTXH1(ch) (*(volatile U8 *)0x50004020)=(U8)(ch)
#define RdURXH1()   (*(volatile U8 *)0x50004024)
#define WrUTXH2(ch) (*(volatile U8 *)0x50008020)=(U8)(ch)
#define RdURXH2()   (*(volatile U8 *)0x50008024)

#define UTXH0       (0x50000020)    //Byte_access address by DMA
#define URXH0       (0x50000024)
#define UTXH1       (0x50004020)
#define URXH1       (0x50004024)
#define UTXH2       (0x50008020)
#define URXH2       (0x50008024)
#endif


// PWM TIMER
#define rTCFG0  (*(volatile U32 *)0x51000000) //Timer 0 configuration
#define rTCFG1  (*(volatile U32 *)0x51000004) //Timer 1 configuration
#define rTCON   (*(volatile U32 *)0x51000008) //Timer control
#define rTCNTB0 (*(volatile U32 *)0x5100000c) //Timer count buffer 0
#define rTCMPB0 (*(volatile U32 *)0x51000010) //Timer compare buffer 0
#define rTCNTO0 (*(volatile U32 *)0x51000014) //Timer count observation 0
#define rTCNTB1 (*(volatile U32 *)0x51000018) //Timer count buffer 1
#define rTCMPB1 (*(volatile U32 *)0x5100001c) //Timer compare buffer 1
#define rTCNTO1 (*(volatile U32 *)0x51000020) //Timer count observation 1
#define rTCNTB2 (*(volatile U32 *)0x51000024) //Timer count buffer 2
#define rTCMPB2 (*(volatile U32 *)0x51000028) //Timer compare buffer 2
#define rTCNTO2 (*(volatile U32 *)0x5100002c) //Timer count observation 2
#define rTCNTB3 (*(volatile U32 *)0x51000030) //Timer count buffer 3
#define rTCMPB3 (*(volatile U32 *)0x51000034) //Timer compare buffer 3
#define rTCNTO3 (*(volatile U32 *)0x51000038) //Timer count observation 3
#define rTCNTB4 (*(volatile U32 *)0x5100003c) //Timer count buffer 4
#define rTCNTO4 (*(volatile U32 *)0x51000040) //Timer count observation 4


// USB DEVICE
#ifdef __BIG_ENDIAN
//<ERROR IF BIG_ENDIAN>
#define rFUNC_ADDR_REG     (*(volatile U8 *)0x52000143) //Function address
#define rPWR_REG           (*(volatile U8 *)0x52000147) //Power management
#define rEP_INT_REG        (*(volatile U8 *)0x5200014b) //EP Interrupt pending and clear
#define rUSB_INT_REG       (*(volatile U8 *)0x5200015b) //USB Interrupt pending and clear
#define rEP_INT_EN_REG     (*(volatile U8 *)0x5200015f) //Interrupt enable
#define rUSB_INT_EN_REG    (*(volatile U8 *)0x5200016f)
#define rFRAME_NUM1_REG    (*(volatile U8 *)0x52000173) //Frame number lower byte
#define rFRAME_NUM2_REG    (*(volatile U8 *)0x52000177) //Frame number higher byte
#define rINDEX_REG         (*(volatile U8 *)0x5200017b) //Register index
#define rMAXP_REG          (*(volatile U8 *)0x52000183) //Endpoint max packet
#define rEP0_CSR           (*(volatile U8 *)0x52000187) //Endpoint 0 status
#define rIN_CSR1_REG       (*(volatile U8 *)0x52000187) //In endpoint control status
#define rIN_CSR2_REG       (*(volatile U8 *)0x5200018b)
#define rOUT_CSR1_REG      (*(volatile U8 *)0x52000193) //Out endpoint control status
#define rOUT_CSR2_REG      (*(volatile U8 *)0x52000197)
#define rOUT_FIFO_CNT1_REG (*(volatile U8 *)0x5200019b) //Endpoint out write count
#define rOUT_FIFO_CNT2_REG (*(volatile U8 *)0x5200019f)
#define rEP0_FIFO          (*(volatile U8 *)0x520001c3) //Endpoint 0 FIFO
#define rEP1_FIFO          (*(volatile U8 *)0x520001c7) //Endpoint 1 FIFO
#define rEP2_FIFO          (*(volatile U8 *)0x520001cb) //Endpoint 2 FIFO
#define rEP3_FIFO          (*(volatile U8 *)0x520001cf) //Endpoint 3 FIFO
#define rEP4_FIFO          (*(volatile U8 *)0x520001d3) //Endpoint 4 FIFO
#define rEP1_DMA_CON       (*(volatile U8 *)0x52000203) //EP1 DMA interface control
#define rEP1_DMA_UNIT      (*(volatile U8 *)0x52000207) //EP1 DMA Tx unit counter
#define rEP1_DMA_FIFO      (*(volatile U8 *)0x5200020b) //EP1 DMA Tx FIFO counter
#define rEP1_DMA_TTC_L     (*(volatile U8 *)0x5200020f) //EP1 DMA total Tx counter
#define rEP1_DMA_TTC_M     (*(volatile U8 *)0x52000213)
#define rEP1_DMA_TTC_H     (*(volatile U8 *)0x52000217)
#define rEP2_DMA_CON       (*(volatile U8 *)0x5200021b) //EP2 DMA interface control
#define rEP2_DMA_UNIT      (*(volatile U8 *)0x5200021f) //EP2 DMA Tx unit counter
#define rEP2_DMA_FIFO      (*(volatile U8 *)0x52000223) //EP2 DMA Tx FIFO counter
#define rEP2_DMA_TTC_L     (*(volatile U8 *)0x52000227) //EP2 DMA total Tx counter
#define rEP2_DMA_TTC_M     (*(volatile U8 *)0x5200022b)
#define rEP2_DMA_TTC_H     (*(volatile U8 *)0x5200022f)
#define rEP3_DMA_CON       (*(volatile U8 *)0x52000243) //EP3 DMA interface control
#define rEP3_DMA_UNIT      (*(volatile U8 *)0x52000247) //EP3 DMA Tx unit counter
#define rEP3_DMA_FIFO      (*(volatile U8 *)0x5200024b) //EP3 DMA Tx FIFO counter
#define rEP3_DMA_TTC_L     (*(volatile U8 *)0x5200024f) //EP3 DMA total Tx counter
#define rEP3_DMA_TTC_M     (*(volatile U8 *)0x52000253)
#define rEP3_DMA_TTC_H     (*(volatile U8 *)0x52000257)
#define rEP4_DMA_CON       (*(volatile U8 *)0x5200025b) //EP4 DMA interface control
#define rEP4_DMA_UNIT      (*(volatile U8 *)0x5200025f) //EP4 DMA Tx unit counter
#define rEP4_DMA_FIFO      (*(volatile U8 *)0x52000263) //EP4 DMA Tx FIFO counter
#define rEP4_DMA_TTC_L     (*(volatile U8 *)0x52000267) //EP4 DMA total Tx counter
#define rEP4_DMA_TTC_M     (*(volatile U8 *)0x5200026b)
#define rEP4_DMA_TTC_H     (*(volatile U8 *)0x5200026f)

#else  // Little Endian
#define rFUNC_ADDR_REG     (*(volatile U8 *)0x52000140) //Function address
#define rPWR_REG           (*(volatile U8 *)0x52000144) //Power management
#define rEP_INT_REG        (*(volatile U8 *)0x52000148) //EP Interrupt pending and clear
#define rUSB_INT_REG       (*(volatile U8 *)0x52000158) //USB Interrupt pending and clear
#define rEP_INT_EN_REG     (*(volatile U8 *)0x5200015c) //Interrupt enable
#define rUSB_INT_EN_REG    (*(volatile U8 *)0x5200016c)
#define rFRAME_NUM1_REG    (*(volatile U8 *)0x52000170) //Frame number lower byte
#define rFRAME_NUM2_REG    (*(volatile U8 *)0x52000174) //Frame number higher byte
#define rINDEX_REG         (*(volatile U8 *)0x52000178) //Register index
#define rMAXP_REG          (*(volatile U8 *)0x52000180) //Endpoint max packet
#define rEP0_CSR           (*(volatile U8 *)0x52000184) //Endpoint 0 status
#define rIN_CSR1_REG       (*(volatile U8 *)0x52000184) //In endpoint control status
#define rIN_CSR2_REG       (*(volatile U8 *)0x52000188)
#define rOUT_CSR1_REG      (*(volatile U8 *)0x52000190) //Out endpoint control status
#define rOUT_CSR2_REG      (*(volatile U8 *)0x52000194)
#define rOUT_FIFO_CNT1_REG (*(volatile U8 *)0x52000198) //Endpoint out write count
#define rOUT_FIFO_CNT2_REG (*(volatile U8 *)0x5200019c)
#define rEP0_FIFO          (*(volatile U8 *)0x520001c0) //Endpoint 0 FIFO
#define rEP1_FIFO          (*(volatile U8 *)0x520001c4) //Endpoint 1 FIFO
#define rEP2_FIFO          (*(volatile U8 *)0x520001c8) //Endpoint 2 FIFO
#define rEP3_FIFO          (*(volatile U8 *)0x520001cc) //Endpoint 3 FIFO
#define rEP4_FIFO          (*(volatile U8 *)0x520001d0) //Endpoint 4 FIFO
#define rEP1_DMA_CON       (*(volatile U8 *)0x52000200) //EP1 DMA interface control
#define rEP1_DMA_UNIT      (*(volatile U8 *)0x52000204) //EP1 DMA Tx unit counter
#define rEP1_DMA_FIFO      (*(volatile U8 *)0x52000208) //EP1 DMA Tx FIFO counter
#define rEP1_DMA_TTC_L     (*(volatile U8 *)0x5200020c) //EP1 DMA total Tx counter
#define rEP1_DMA_TTC_M     (*(volatile U8 *)0x52000210)
#define rEP1_DMA_TTC_H     (*(volatile U8 *)0x52000214)
#define rEP2_DMA_CON       (*(volatile U8 *)0x52000218) //EP2 DMA interface control
#define rEP2_DMA_UNIT      (*(volatile U8 *)0x5200021c) //EP2 DMA Tx unit counter
#define rEP2_DMA_FIFO      (*(volatile U8 *)0x52000220) //EP2 DMA Tx FIFO counter
#define rEP2_DMA_TTC_L     (*(volatile U8 *)0x52000224) //EP2 DMA total Tx counter
#define rEP2_DMA_TTC_M     (*(volatile U8 *)0x52000228)
#define rEP2_DMA_TTC_H     (*(volatile U8 *)0x5200022c)
#define rEP3_DMA_CON       (*(volatile U8 *)0x52000240) //EP3 DMA interface control
#define rEP3_DMA_UNIT      (*(volatile U8 *)0x52000244) //EP3 DMA Tx unit counter
#define rEP3_DMA_FIFO      (*(volatile U8 *)0x52000248) //EP3 DMA Tx FIFO counter
#define rEP3_DMA_TTC_L     (*(volatile U8 *)0x5200024c) //EP3 DMA total Tx counter
#define rEP3_DMA_TTC_M     (*(volatile U8 *)0x52000250)
#define rEP3_DMA_TTC_H     (*(volatile U8 *)0x52000254)
#define rEP4_DMA_CON       (*(volatile U8 *)0x52000258) //EP4 DMA interface control
#define rEP4_DMA_UNIT      (*(volatile U8 *)0x5200025c) //EP4 DMA Tx unit counter
#define rEP4_DMA_FIFO      (*(volatile U8 *)0x52000260) //EP4 DMA Tx FIFO counter
#define rEP4_DMA_TTC_L     (*(volatile U8 *)0x52000264) //EP4 DMA total Tx counter
#define rEP4_DMA_TTC_M     (*(volatile U8 *)0x52000268)
#define rEP4_DMA_TTC_H     (*(volatile U8 *)0x5200026c)
#endif   // __BIG_ENDIAN


// WATCH DOG TIMER
#define rWTCON   (*(volatile U32 *)0x53000000) //Watch-dog timer mode
#define rWTDAT   (*(volatile U32 *)0x53000004) //Watch-dog timer data
#define rWTCNT   (*(volatile U32 *)0x53000008) //Eatch-dog timer count


// IIC
#define rIICCON  (*(volatile U32 *)0x54000000) //IIC control
#define rIICSTAT (*(volatile U32 *)0x54000004) //IIC status
#define rIICADD  (*(volatile U32 *)0x54000008) //IIC address
#define rIICDS   (*(volatile U32 *)0x5400000c) //IIC data shift
#define rIICVC   (*(volatile U32 *)0x54000010) //IIC multi-master line control


// IIS
#define rIISCON  (*(volatile U32 *)0x55000000) //IIS Control
#define rIISMOD  (*(volatile U32 *)0x55000004) //IIS Mode
#define rIISPSR  (*(volatile U32 *)0x55000008) //IIS Prescaler
#define rIISFCON (*(volatile U32 *)0x5500000c) //IIS FIFO control

#ifdef __BIG_ENDIAN
#define IISFIFO  ((volatile U16 *)0x55000012) //IIS FIFO entry

#else //Little Endian
#define IISFIFO  ((volatile U16 *)0x55000010) //IIS FIFO entry

#endif


// I/O PORT 
#define rGPACON    (*(volatile U32 *)0x56000000) //Port A control
#define rGPADAT    (*(volatile U32 *)0x56000004) //Port A data

#define rGPBCON    (*(volatile U32 *)0x56000010) //Port B control
#define rGPBDAT    (*(volatile U32 *)0x56000014) //Port B data
#define rGPBUP     (*(volatile U32 *)0x56000018) //Pull-up control B

#define rGPCCON    (*(volatile U32 *)0x56000020) //Port C control
#define rGPCDAT    (*(volatile U32 *)0x56000024) //Port C data
#define rGPCUP     (*(volatile U32 *)0x56000028) //Pull-up control C

#define rGPDCON    (*(volatile U32 *)0x56000030) //Port D control
#define rGPDDAT    (*(volatile U32 *)0x56000034) //Port D data
#define rGPDUP     (*(volatile U32 *)0x56000038) //Pull-up control D

#define rGPECON    (*(volatile U32 *)0x56000040) //Port E control
#define rGPEDAT    (*(volatile U32 *)0x56000044) //Port E data
#define rGPEUP     (*(volatile U32 *)0x56000048) //Pull-up control E

#define rGPFCON    (*(volatile U32 *)0x56000050) //Port F control
#define rGPFDAT    (*(volatile U32 *)0x56000054) //Port F data
#define rGPFUP     (*(volatile U32 *)0x56000058) //Pull-up control F

#define rGPGCON    (*(volatile U32 *)0x56000060) //Port G control
#define rGPGDAT    (*(volatile U32 *)0x56000064) //Port G data
#define rGPGUP     (*(volatile U32 *)0x56000068) //Pull-up control G

#define rGPHCON    (*(volatile U32 *)0x56000070) //Port H control
#define rGPHDAT    (*(volatile U32 *)0x56000074) //Port H data
#define rGPHUP     (*(volatile U32 *)0x56000078) //Pull-up control H

#define rGPJCON    (*(volatile U32 *)0x560000d0) //Port J control
#define rGPJDAT    (*(volatile U32 *)0x560000d4) //Port J data
#define rGPJUP     (*(volatile U32 *)0x560000d8) //Pull-up control J

#define rMISCCR    (*(volatile U32 *)0x56000080) //Miscellaneous control
#define rDCLKCON   (*(volatile U32 *)0x56000084) //DCLK0/1 control
#define rEXTINT0   (*(volatile U32 *)0x56000088) //External interrupt control register 0
#define rEXTINT1   (*(volatile U32 *)0x5600008c) //External interrupt control register 1
#define rEXTINT2   (*(volatile U32 *)0x56000090) //External interrupt control register 2
#define rEINTFLT0  (*(volatile U32 *)0x56000094) //Reserved
#define rEINTFLT1  (*(volatile U32 *)0x56000098) //Reserved
#define rEINTFLT2  (*(volatile U32 *)0x5600009c) //External interrupt filter control register 2
#define rEINTFLT3  (*(volatile U32 *)0x560000a0) //External interrupt filter control register 3
#define rEINTMASK  (*(volatile U32 *)0x560000a4) //External interrupt mask
#define rEINTPEND  (*(volatile U32 *)0x560000a8) //External interrupt pending
#define rGSTATUS0  (*(volatile U32 *)0x560000ac) //External pin status
#define rGSTATUS1  (*(volatile U32 *)0x560000b0) //Chip ID(0x32410000)
#define rGSTATUS2  (*(volatile U32 *)0x560000b4) //Reset type
#define rGSTATUS3  (*(volatile U32 *)0x560000b8) //Saved data0(32-bit) before entering POWER_OFF mode 
#define rGSTATUS4  (*(volatile U32 *)0x560000bc) //Saved data0(32-bit) before entering POWER_OFF mode 


// RTC
#ifdef __BIG_ENDIAN
#define rRTCCON    (*(volatile U8 *)0x57000043) //RTC control
#define rTICNT     (*(volatile U8 *)0x57000047) //Tick time count
#define rRTCALM    (*(volatile U8 *)0x57000053) //RTC alarm control
#define rALMSEC    (*(volatile U8 *)0x57000057) //Alarm second
#define rALMMIN    (*(volatile U8 *)0x5700005b) //Alarm minute
#define rALMHOUR   (*(volatile U8 *)0x5700005f) //Alarm Hour
#define rALMDAY    (*(volatile U8 *)0x57000063) //Alarm day
#define rALMMON    (*(volatile U8 *)0x57000067) //Alarm month
#define rALMYEAR   (*(volatile U8 *)0x5700006b) //Alarm year
#define rBCDSEC    (*(volatile U8 *)0x57000073) //BCD second
#define rBCDMIN    (*(volatile U8 *)0x57000077) //BCD minute
#define rBCDHOUR   (*(volatile U8 *)0x5700007b) //BCD hour
#define rBCDDAY    (*(volatile U8 *)0x5700007f) //BCD day
#define rBCDDATE   (*(volatile U8 *)0x57000083) //BCD date
#define rBCDMON    (*(volatile U8 *)0x57000087) //BCD month
#define rBCDYEAR   (*(volatile U8 *)0x5700008b) //BCD year

#else //Little Endian
#define rRTCCON    (*(volatile U8 *)0x57000040) //RTC control
#define rTICNT     (*(volatile U8 *)0x57000044) //Tick time count
#define rRTCALM    (*(volatile U8 *)0x57000050) //RTC alarm control
#define rALMSEC    (*(volatile U8 *)0x57000054) //Alarm second
#define rALMMIN    (*(volatile U8 *)0x57000058) //Alarm minute
#define rALMHOUR   (*(volatile U8 *)0x5700005c) //Alarm Hour
#define rALMDAY    (*(volatile U8 *)0x57000060) //Alarm day
#define rALMMON    (*(volatile U8 *)0x57000064) //Alarm month
#define rALMYEAR   (*(volatile U8 *)0x57000068) //Alarm year
#define rBCDSEC    (*(volatile U8 *)0x57000070) //BCD second
#define rBCDMIN    (*(volatile U8 *)0x57000074) //BCD minute
#define rBCDHOUR   (*(volatile U8 *)0x57000078) //BCD hour
#define rBCDDAY    (*(volatile U8 *)0x5700007c) //BCD day
#define rBCDDATE   (*(volatile U8 *)0x57000080) //BCD date
#define rBCDMON    (*(volatile U8 *)0x57000084) //BCD month
#define rBCDYEAR   (*(volatile U8 *)0x57000088) //BCD year
#endif  //RTC


// ADC
#define rADCCON    (*(volatile U32 *)0x58000000) //ADC control
#define rADCTSC    (*(volatile U32 *)0x58000004) //ADC touch screen control
#define rADCDLY    (*(volatile U32 *)0x58000008) //ADC start or Interval Delay
#define rADCDAT0   (*(volatile U32 *)0x5800000c) //ADC conversion data 0
#define rADCDAT1   (*(volatile U32 *)0x58000010) //ADC conversion data 1                   
#define rADCUPDN   (*(volatile U32 *)0x58000014) //Stylus up or down interrupt status


// SPI          
#define rSPCON0    (*(volatile U32 *)0x59000000) //SPI0 control
#define rSPSTA0    (*(volatile U32 *)0x59000004) //SPI0 status
#define rSPPIN0    (*(volatile U32 *)0x59000008) //SPI0 pin control
#define rSPPRE0    (*(volatile U32 *)0x5900000c) //SPI0 baud rate prescaler
#define rSPTDAT0   (*(volatile U32 *)0x59000010) //SPI0 Tx data
#define rSPRDAT0   (*(volatile U32 *)0x59000014) //SPI0 Rx data

#define rSPCON1    (*(volatile U32 *)0x59000020) //SPI1 control
#define rSPSTA1    (*(volatile U32 *)0x59000024) //SPI1 status
#define rSPPIN1    (*(volatile U32 *)0x59000028) //SPI1 pin control
#define rSPPRE1    (*(volatile U32 *)0x5900002c) //SPI1 baud rate prescaler
#define rSPTDAT1   (*(volatile U32 *)0x59000030) //SPI1 Tx data
#define rSPRDAT1   (*(volatile U32 *)0x59000034) //SPI1 Rx data


// SD Interface
#define rSDICON     (*(volatile U32 *)0x5a000000) //SDI control
#define rSDIPRE     (*(volatile U32 *)0x5a000004) //SDI baud rate prescaler
#define rSDICARG    (*(volatile U32 *)0x5a000008) //SDI command argument
#define rSDICCON    (*(volatile U32 *)0x5a00000c) //SDI command control
#define rSDICSTA    (*(volatile U32 *)0x5a000010) //SDI command status
#define rSDIRSP0    (*(volatile U32 *)0x5a000014) //SDI response 0
#define rSDIRSP1    (*(volatile U32 *)0x5a000018) //SDI response 1
#define rSDIRSP2    (*(volatile U32 *)0x5a00001c) //SDI response 2
#define rSDIRSP3    (*(volatile U32 *)0x5a000020) //SDI response 3
#define rSDIDTIMER  (*(volatile U32 *)0x5a000024) //SDI data/busy timer
#define rSDIBSIZE   (*(volatile U32 *)0x5a000028) //SDI block size
#define rSDIDCON    (*(volatile U32 *)0x5a00002c) //SDI data control
#define rSDIDCNT    (*(volatile U32 *)0x5a000030) //SDI data remain counter
#define rSDIDSTA    (*(volatile U32 *)0x5a000034) //SDI data status
#define rSDIFSTA    (*(volatile U32 *)0x5a000038) //SDI FIFO status
#define rSDIIMSK    (*(volatile U32 *)0x5a00003c) //SDI interrupt mask

#ifdef __BIG_ENDIAN
#define rSDIDAT    (*(volatile U32 *)0x5a000043) //SDI data
#define SDIDAT     0x5a000043
#else  // Little Endian
#define rSDIDAT    (*(volatile U32 *)0x5a000040) //SDI data
#define SDIDAT     0x5a000040
#endif   //SD Interface
             

// AC97 Audio-CODEC Interface
#define rAC_GLBCTRL	   (*(volatile U32 *)0x5b000000) //AC97 global control register
#define rAC_GLBSTAT	   (*(volatile U32 *)0x5b000004) //AC97 global status register
#define rAC_CODEC_CMD  (*(volatile U32 *)0x5b000008) //AC97 codec command register
#define rAC_CODEC_STAT (*(volatile U32 *)0x5b00000c) //AC97 codec status register
#define rAC_PCMADDR	   (*(volatile U32 *)0x5b000010) //AC97 PCM out/in channel FIFO address register
#define rAC_MICADDR	   (*(volatile U32 *)0x5b000014) //AC97 mic in channel FIFO address register
#define rAC_PCMDATA    (*(volatile U32 *)0x5b000018) //AC97 PCM out/in channel FIFO data register
#define rAC_MICDATA	   (*(volatile U32 *)0x5b00001c) //AC97 MIC in channel FIFO data register


// ISR
#define pISR_RESET     (*(U32 *)(ISR_BADDR+0x0))
#define pISR_UNDEF     (*(U32 *)(ISR_BADDR+0x4))
#define pISR_SWI       (*(U32 *)(ISR_BADDR+0x8))
#define pISR_PABORT    (*(U32 *)(ISR_BADDR+0xc))
#define pISR_DABORT    (*(U32 *)(ISR_BADDR+0x10))
#define pISR_RESERVED  (*(U32 *)(ISR_BADDR+0x14))
#define pISR_IRQ       (*(U32 *)(ISR_BADDR+0x18))
#define pISR_FIQ       (*(U32 *)(ISR_BADDR+0x1c))

#define aISR_EINT0     (ISR_BADDR+0x20)
#define pISR_EINT0     (*(U32 *)aISR_EINT0)
#define pISR_EINT1     (*(U32 *)(ISR_BADDR+0x24))
#define pISR_EINT2     (*(U32 *)(ISR_BADDR+0x28))
#define pISR_EINT3     (*(U32 *)(ISR_BADDR+0x2c))
#define pISR_EINT4_7   (*(U32 *)(ISR_BADDR+0x30))
#define pISR_EINT8_23  (*(U32 *)(ISR_BADDR+0x34))
#define pISR_CAM	   (*(U32 *)(ISR_BADDR+0x38))
#define pISR_BAT_FLT   (*(U32 *)(ISR_BADDR+0x3c))
#define pISR_TICK      (*(U32 *)(ISR_BADDR+0x40))
#define pISR_WDT_AC97  (*(U32 *)(ISR_BADDR+0x44))
#define pISR_TIMER0    (*(U32 *)(ISR_BADDR+0x48))
#define pISR_TIMER1    (*(U32 *)(ISR_BADDR+0x4c))
#define pISR_TIMER2    (*(U32 *)(ISR_BADDR+0x50))
#define pISR_TIMER3    (*(U32 *)(ISR_BADDR+0x54))
#define pISR_TIMER4    (*(U32 *)(ISR_BADDR+0x58))
#define pISR_UART2     (*(U32 *)(ISR_BADDR+0x5c))
#define pISR_LCD       (*(U32 *)(ISR_BADDR+0x60))
#define pISR_DMA0      (*(U32 *)(ISR_BADDR+0x64))
#define pISR_DMA1      (*(U32 *)(ISR_BADDR+0x68))
#define pISR_DMA2      (*(U32 *)(ISR_BADDR+0x6c))
#define pISR_DMA3      (*(U32 *)(ISR_BADDR+0x70))
#define pISR_SDI       (*(U32 *)(ISR_BADDR+0x74))
#define pISR_SPI0      (*(U32 *)(ISR_BADDR+0x78))
#define pISR_UART1     (*(U32 *)(ISR_BADDR+0x7c))
#define pISR_NFCON     (*(U32 *)(ISR_BADDR+0x80))
#define pISR_USBD      (*(U32 *)(ISR_BADDR+0x84))
#define pISR_USBH      (*(U32 *)(ISR_BADDR+0x88))
#define pISR_IIC       (*(U32 *)(ISR_BADDR+0x8c))
#define pISR_UART0     (*(U32 *)(ISR_BADDR+0x90))
#define pISR_SPI1      (*(U32 *)(ISR_BADDR+0x94))
#define pISR_RTC       (*(U32 *)(ISR_BADDR+0x98))
#define pISR_ADC       (*(U32 *)(ISR_BADDR+0x9c))


// PENDING BIT
#define BIT_EINT0      (0x1)
#define BIT_EINT1      (0x1<<1)
#define BIT_EINT2      (0x1<<2)
#define BIT_EINT3      (0x1<<3)
#define BIT_EINT4_7    (0x1<<4)
#define BIT_EINT8_23   (0x1<<5)
#define BIT_CAM        (0x1<<6)
#define BIT_BAT_FLT    (0x1<<7)
#define BIT_TICK       (0x1<<8)
#define BIT_WDT_AC97   (0x1<<9)
#define BIT_TIMER0     (0x1<<10)
#define BIT_TIMER1     (0x1<<11)
#define BIT_TIMER2     (0x1<<12)
#define BIT_TIMER3     (0x1<<13)
#define BIT_TIMER4     (0x1<<14)
#define BIT_UART2      (0x1<<15)
#define BIT_LCD        (0x1<<16)
#define BIT_DMA0       (0x1<<17)
#define BIT_DMA1       (0x1<<18)
#define BIT_DMA2       (0x1<<19)
#define BIT_DMA3       (0x1<<20)
#define BIT_SDI        (0x1<<21)
#define BIT_SPI0       (0x1<<22)
#define BIT_UART1      (0x1<<23)
#define BIT_NFCON	   (0x1<<24)
#define BIT_USBD       (0x1<<25)
#define BIT_USBH       (0x1<<26)
#define BIT_IIC        (0x1<<27)
#define BIT_UART0      (0x1<<28)
#define BIT_SPI1       (0x1<<29)
#define BIT_RTC        (0x1<<30)
#define BIT_ADC        (0x1<<31)
#define BIT_ALLMSK     (0xffffffff)

#define BIT_SUB_ALLMSK (0x7ff)
#define BIT_SUB_AC97   (0x1<<14)
#define BIT_SUB_WDT	   (0x1<<13)
#define BIT_SUB_CAM_P  (0x1<<12)
#define BIT_SUB_CAM_C  (0x1<<11)
#define BIT_SUB_ADC_S  (0x1<<10)
#define BIT_SUB_TC     (0x1<<9)
#define BIT_SUB_ERR2   (0x1<<8)
#define BIT_SUB_TXD2   (0x1<<7)
#define BIT_SUB_RXD2   (0x1<<6)
#define BIT_SUB_ERR1   (0x1<<5)
#define BIT_SUB_TXD1   (0x1<<4)
#define BIT_SUB_RXD1   (0x1<<3)
#define BIT_SUB_ERR0   (0x1<<2)
#define BIT_SUB_TXD0   (0x1<<1)
#define BIT_SUB_RXD0   (0x1<<0)

#define ClearPending(bit)     \
{                             \
    rSRCPND = bit;            \
    rINTPND = bit;            \
    rINTPND;                  \
}       
//Wait until rINTPND is changed for the case that the ISR is very short.


/* ARM modes */
#define USERMODE        0x10
#define FIQMODE         0x11
#define IRQMODE         0x12
#define SVCMODE         0x13
#define ABORTMODE       0x17
#define UNDEFMODE       0x1b
#define MODEMASK        0x1f
#define NOINT           0xc0


/* ********************************************************************* */
/* Interface function definition */


/* ********************************************************************* */

#ifdef __cplusplus
}
#endif

#endif /*__S3C2410X_H__*/
