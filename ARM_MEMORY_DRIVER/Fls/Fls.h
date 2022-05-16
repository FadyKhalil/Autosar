/*
 * Fls.h
 *
 *  Created on: May 10, 2022
 *      Author: fady
 */

#ifndef MCAL_Fls_Fls_H_
#define MCAL_Fls_Fls_H_

/***Give Datatype readable name*/
typedef u32 Fls_AddressType;
typedef u32 Fls_LengthType;

typedef enum
{
	Fpro_enuOK = 0,
	Fls_enuNullPointer,
	Fls_enuControlRegisterLock,
	Fls_enuSectorNumberWrong,
	Fls_enuExceedFlash


}Std_ReturnType;


typedef struct
{
	u8 Error;
	u8 EndOfOperation;

}Fls_Interrupt;

typedef struct
{
	u8 FlashAccessLatency;
	Fls_Interrupt Interrupt;

}Fls_Config;

/********************DEFINES*********************/

/*this Option relevant the the structure Fls_Config
 *
 * !Note: Using this bit depends on the voltage level connected
 *
 * */
#define PAGESIZE_BYTE			0x00
#define PAGESIZE_HALF_WORD		0x01
#define PAGESIZE_WORD			0x02
#define PAGESIZE_DOUBLE_WORD	0x03

/*SectorNumber
 *
 * !NOTE : STM32F401C
 *
 * */
#define SECTOR_0				0
#define SECTOR_1				1
#define SECTOR_2				2
#define SECTOR_3				3
#define SECTOR_4				4
#define SECTOR_5				5


/*
 * Function Name:				Fls_vidInit
 *
 * Description:					Configure the Flash driver
 *
 * parameter:					ConfigPtr (pointer to structure)
 *
 * return:						void
 * */
extern void Fls_vidInit(const Fls_Config* ConfigPtr);

/*
 * Function Name:				Fls_enuMassErase
 *
 * Description:					To delete all Flash memory
 *
 * parameter:					void
 *
 * return:						void
 * */
extern Std_ReturnType Fls_enuMassErase(void);

/*
 * Function Name:				Fls_enuSectorErase
 *
 * Description:					Sector Number to be deleted
 *
 * parameter:					SectorNumber (Sector Number to be deleted)
 * 										in range {SECTOR_1, SECTOR_2, SECTOR_3, SECTOR_4, SECTOR_5}
 *
 * return:						ErrorStatus
 * */
extern Std_ReturnType Fls_enuSectorErase(u8 SectorNumber);

/*
 * Function Name:				Fls_enuOneTimeProgramming
 *
 * Description:					This is a section in a memory can be only programed one time
 * 											& never can be erased in run time to rewrite on it you need to powerOFF/PowerON
 * 											the Microcontroller
 *
 * parameter:					Data --> Address of the variable or Buffer
 * 								BufferSize --> size of the buffer
 *
 * 								if you will send a normal variable with one index then SET BufferSize with 1
 *
 * return:						ErrorStatus
 *
 * !!!! NOTE = Make sure the Buffersize is multiple of 2 always and the data sent MUST be at LEAST 8 BYTE * n;
 * 			MIN n = 1 , MAX n = 16;
 * */
extern Std_ReturnType Fls_enuOneTimeProgramming(pu32 Data, u8 BufferSize);


/*
 * Function Name:				Fls_enuProgrammingFlash
 *
 * Description:					Program Flash memory
 *
 * parameter:					@ Data --> Address of the variable or Buffer
 * 								@ MemoryAddress --> the flash Adress to store the variable
 * 									in range {0x08000000 ->  0x0803FFFF}
 *								@ Copy_u8Pagesize --> Pagesize to program the data
 *									in range {PAGESIZE_BYTE, PAGESIZE_HALF_WORD, PAGESIZE_WORD, PAGESIZE_DOUBLE_WORD}
 *
 * return:						ErrorStatus
 * */
extern Std_ReturnType Fls_Write(Fls_AddressType TargetAddress, Fls_LengthType Length, u64 Data);








#endif /* MCAL_Fls_Fls_H_ */
