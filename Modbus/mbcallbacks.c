/**
  ******************************************************************************
  * @file      mbcallbacks.c
  * @author    
  * @version   
  * @brief     This file provides  common functions for the mbcallbacks.c                
  ******************************************************************************
*/
/* ------------------------Includes ----------------------------------*/
#include "mbcallbacks.h"

#include "ModbusDataHandler.h" 
/* ------------------------External variables -------------------------*/


/* ------------------------Global variables----------------------------*/
//**********DEFINES FOR HOLDING REGISTERS*******************/

 /** OUTPUT array for holding registers */
short   OutRegHoldingBuf[REG_HOLDING_NREGS];
 
 /** INPUT array for holding registers */
short   InputRegHoldingBuf[REG_HOLDING_NREGS];

uint8_t modbus_mutex = 0;

/* ------------------------Local variables----------------------------*/


//**************************eMBRegInputCB************************/

/*! \ingroup modbus_registers
 * \brief Callback function used if the value of a <em>Input Register</em>
 *   is required by the protocol stack. The starting register address is given
 *   by \c usAddress and the last register is given by <tt>usAddress +
 *   usNRegs - 1</tt>.
 *
 * \param pucRegBuffer A buffer where the callback function should write
 *   the current value of the modbus registers to.
 * \param usAddress The starting address of the register. Input registers
 *   are in the range 1 - 65535.
 * \param usNRegs Number of registers the callback function must supply.
 *
 * \return The function must return one of the following error codes:
 *   - eMBErrorCode::MB_ENOERR If no error occurred. In this case a normal
 *       Modbus response is sent.
 *   - eMBErrorCode::MB_ENOREG If the application can not supply values
 *       for registers within this range. In this case a 
 *       <b>ILLEGAL DATA ADDRESS</b> exception frame is sent as a response.
 *   - eMBErrorCode::MB_ETIMEDOUT If the requested register block is
 *       currently not available and the application dependent response
 *       timeout would be violated. In this case a <b>SLAVE DEVICE BUSY</b>
 *       exception is sent as a response.
 *   - eMBErrorCode::MB_EIO If an unrecoverable error occurred. In this case
 *       a <b>SLAVE DEVICE FAILURE</b> exception is sent as a response.
 */

eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
   return MB_ENOREG;
}

//**************************eMBRegHoldingCB************************/
/*! \ingroup modbus_registers
 * \brief Callback function used if a <em>Holding Register</em> value is
 *   read or written by the protocol stack. The starting register address
 *   is given by \c usAddress and the last register is given by
 *   <tt>usAddress + usNRegs - 1</tt>.
 *
 * \param pucRegBuffer If the application registers values should be updated the
 *   buffer points to the new registers values. If the protocol stack needs
 *   to now the current values the callback function should write them into
 *   this buffer.
 * \param usAddress The starting address of the register.
 * \param usNRegs Number of registers to read or write.
 * \param eMode If eMBRegisterMode::MB_REG_WRITE the application register 
 *   values should be updated from the values in the buffer. For example
 *   this would be the case when the Modbus master has issued an 
 *   <b>WRITE SINGLE REGISTER</b> command.
 *   If the value eMBRegisterMode::MB_REG_READ the application should copy 
 *   the current values into the buffer \c pucRegBuffer.
 *
 * \return The function must return one of the following error codes:
 *   - eMBErrorCode::MB_ENOERR If no error occurred. In this case a normal
 *       Modbus response is sent.
 *   - eMBErrorCode::MB_ENOREG If the application can not supply values
 *       for registers within this range. In this case a 
 *       <b>ILLEGAL DATA ADDRESS</b> exception frame is sent as a response.
 *   - eMBErrorCode::MB_ETIMEDOUT If the requested register block is
 *       currently not available and the application dependent response
 *       timeout would be violated. In this case a <b>SLAVE DEVICE BUSY</b>
 *       exception is sent as a response.
 *   - eMBErrorCode::MB_EIO If an unrecoverable error occurred. In this case
 *       a <b>SLAVE DEVICE FAILURE</b> exception is sent as a response.
 */
int tempADR;

eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                 eMBRegisterMode eMode )
{
    eMBErrorCode eStatus = MB_ENOERR;
    int  iRegIndex;
    uint16_t MBValue = 0x0000;
    
    //usAddress -= 40001;
	  //tempADR = usAddress;
	
    if( ( usAddress >= REG_HOLDING_START ) &&
        ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - REG_HOLDING_START);
        
        switch ( eMode )
        {
            /* Pass current register values to the protocol stack. */
        case MB_REG_READ:       
            
            while( usNRegs > 0 )
							
            {
							  //osDelay(100);
                MBValue =  WriteParamToModbusStack(iRegIndex);
              
                *pucRegBuffer++ = ( unsigned char )( MBValue>> 8 );
                *pucRegBuffer++ = ( unsigned char )( MBValue & 0xFF );
              
               // *pucRegBuffer++ = ( unsigned char )( OutRegHoldingBuf[iRegIndex] >> 8 );
               // *pucRegBuffer++ = ( unsigned char )( OutRegHoldingBuf[iRegIndex] & 0xFF );
                iRegIndex++;
                usNRegs--;
            }
            
            break;

            /* Update current register values with new values from the
             * protocol stack. */
        case MB_REG_WRITE :
       
            while( usNRegs > 0 )
            {
                 OutRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
                 OutRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
                  
               /* Read parameters from Modbus stack */
                 ReadParamFromModbusStack(iRegIndex, OutRegHoldingBuf[iRegIndex]);
                 
                 iRegIndex++;
                 usNRegs--;
            }          
            
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}

//**************************eMBRegCoilsCB************************/
/*! \ingroup modbus_registers
 * \brief Callback function used if a <em>Coil Register</em> value is
 *   read or written by the protocol stack. If you are going to use
 *   this function you might use the functions xMBUtilSetBits(  ) and
 *   xMBUtilGetBits(  ) for working with bitfields.
 *
 * \param pucRegBuffer The bits are packed in bytes where the first coil
 *   starting at address \c usAddress is stored in the LSB of the
 *   first byte in the buffer <code>pucRegBuffer</code>.
 *   If the buffer should be written by the callback function unused
 *   coil values (I.e. if not a multiple of eight coils is used) should be set
 *   to zero.
 * \param usAddress The first coil number.
 * \param usNCoils Number of coil values requested.
 * \param eMode If eMBRegisterMode::MB_REG_WRITE the application values should
 *   be updated from the values supplied in the buffer \c pucRegBuffer.
 *   If eMBRegisterMode::MB_REG_READ the application should store the current
 *   values in the buffer \c pucRegBuffer.
 *
 * \return The function must return one of the following error codes:
 *   - eMBErrorCode::MB_ENOERR If no error occurred. In this case a normal
 *       Modbus response is sent.
 *   - eMBErrorCode::MB_ENOREG If the application does not map an coils
 *       within the requested address range. In this case a 
 *       <b>ILLEGAL DATA ADDRESS</b> is sent as a response.
 *   - eMBErrorCode::MB_ETIMEDOUT If the requested register block is
 *       currently not available and the application dependent response
 *       timeout would be violated. In this case a <b>SLAVE DEVICE BUSY</b>
 *       exception is sent as a response.
 *   - eMBErrorCode::MB_EIO If an unrecoverable error occurred. In this case
 */

eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
    return MB_ENOREG;
}


//**************************eMBRegDiscreteCB************************/
/*! \ingroup modbus_registers
 * \brief Callback function used if a <em>Input Discrete Register</em> value is
 *   read by the protocol stack.
 *
 * If you are going to use his function you might use the functions
 * xMBUtilSetBits(  ) and xMBUtilGetBits(  ) for working with bitfields.
 *
 * \param pucRegBuffer The buffer should be updated with the current
 *   coil values. The first discrete input starting at \c usAddress must be
 *   stored at the LSB of the first byte in the buffer. If the requested number
 *   is not a multiple of eight the remaining bits should be set to zero.
 * \param usAddress The starting address of the first discrete input.
 * \param usNDiscrete Number of discrete input values.
 * \return The function must return one of the following error codes:
 *   - eMBErrorCode::MB_ENOERR If no error occurred. In this case a normal
 *       Modbus response is sent.
 *   - eMBErrorCode::MB_ENOREG If no such discrete inputs exists.
 *       In this case a <b>ILLEGAL DATA ADDRESS</b> exception frame is sent 
 *       as a response.
 *   - eMBErrorCode::MB_ETIMEDOUT If the requested register block is
 *       currently not available and the application dependent response
 *       timeout would be violated. In this case a <b>SLAVE DEVICE BUSY</b>
 *       exception is sent as a response.
 *   - eMBErrorCode::MB_EIO If an unrecoverable error occurred. In this case
 *       a <b>SLAVE DEVICE FAILURE</b> exception is sent as a response.
 */

eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}

static uint32_t lock_nesting_count = 0;

 /**
   * @brief  Function: _critical_enter for  modbus
   * @param  None
   * @retval None
  */
void __critical_enter(void)
{
    /* Lock interrupts. */
      //  __disable_irq();
         ++lock_nesting_count;
}

 /**
   * @brief  Function: _critical_exit for  modbus
   * @param  None
   * @retval None
  */
void __critical_exit(void)
{
    /* Unlock interrupts only when we are exiting the outermost nested call. */
    --lock_nesting_count;
   if (lock_nesting_count == 0) {

     //  __enable_irq();
    }
}


