/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file mdlSCI.c @copyright
 *      THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 *\n    UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE
 *\n    FILES MAY LEAD TO PROSECUTION.
 *\n
 *\n    IPT Technology GmbH
 *\n    Im Martelacker 14
 *\n    79588 Efringen-Kirchen
 *\n    Germany
 *\n    Phone:   +49 7628 692 96-0
 *\n    Fax:     +49 7628 692 96-99
 *\n    info@ipt-technology.com
 *\n    www.ipt-technology.com
 *****************************************************************************/


/*****************************************************************************/
/*!@file            mdlSCI.c
 * @brief           Manage cyclic transmission and reception of RS232 messages
 *//*
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes
#include <stdbool.h>
#include "device.h"
#include "mdlSCI.h"

//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


/*!@brief
* Serial interface descriptor.
*
* @ref mdlFIFO_cnf.h
*/
typedef struct mdlSCI_cfg_SCI
{
  uint32_t                        base; //!< base address of the SCI port (SCIA_BASE, etc.)
  uint32_t                        baud; //!< baud rate
  uint32_t                      length; //!< no. of data bits
  SCI_ParityType                parity; //!< parity
  uint32_t                        stop; //!< no. of stop bits (SCI_CONFIG_STOP_ONE or SCI_CONFIG_STOP_TWO)
//  mdlFIFO_cnf_buf_t           rxBuffer; //!< assigned receive FIFO buffer used by mdlSCI_exec()
//  mdlFIFO_cnf_buf_t           txBuffer; //!< assigned transmit FIFO buffer used by mdlSCI_exec()
//  uint16_t                     rxCycle; //!< cycle time [ms] for handling cyclic reception
//  uint16_t                     txCycle; //!< cycle time [ms] for handling cyclic transmission
}mdlSCI_cfg_SCI_t;

///*!@brief
// * sleep time counter for module inactivity
// */
//struct mdlSCI_timer
//{
//    uint16_t             rx_sleep_time; //!< sleep time counter for handling cyclic reception
//    uint16_t             tx_sleep_time; //!< sleep time counter for handling cyclic transmission
//};
//static struct mdlSCI_timer timer[e_mdlSCI_cnf_SCI__endOfList];


static mdlSCI_cfg_SCI_t cfg[e_mdlSCI_cnf_SCI__endOfList] = {
#define LOAD_MODULE_CONFIGURATION
    #include "./_config/mdlSCI_cnf.h"
#undef  LOAD_MODULE_CONFIGURATION
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// MACROS, DECLARATIONS AND DEFINES - END
//=============================================================================



//_____________________________________________________________________________
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\\
///\/\/\/\/\/|  CODE SECTION   -   START    |\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\\
//"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""



//=============================================================================
// FUNCTION SECTION - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    //-------------------------
    // Private Predeclaration
    //*************************


    //-------------------------
    // Public Section
    //*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Initialize Serial Communications Interfaces (SCI)
 *
 *@ref      mdlSCI_cfg_SCI_t
 *@ref      mdlSCI_cnf.h
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded form the config header file into static variable cfg[].
 *\n
 */
void mdlSCI_init(void)
{
    uint8_t i;
    uint32_t freq;

    // Get the low-speed peripheral clock frequency
    freq = SysCtl_getLowSpeedClock(DEVICE_OSCSRC_FREQ);

    // Initialize all configured interfaces
    for(i = 0; i < e_mdlSCI_cnf_SCI__endOfList; i++)
    {
        // Check the arguments
        ASSERT(SCI_isBaseValid(cfg[i].base));

        // Initialize SCI and its FIFO
        SCI_performSoftwareReset(cfg[i].base);

        // Configure SCI baud rate and format
        SCI_setConfig(cfg[i].base, freq, cfg[i].baud,
                      (cfg[i].length | cfg[i].stop | cfg[i].parity)
                     );
        SCI_resetChannels(cfg[i].base);
        SCI_resetRxFIFO(cfg[i].base);
        SCI_resetTxFIFO(cfg[i].base);
        SCI_clearInterruptStatus(cfg[i].base, SCI_INT_TXFF | SCI_INT_RXFF);
        SCI_enableFIFO(cfg[i].base);
        SCI_enableModule(cfg[i].base);
        SCI_performSoftwareReset(cfg[i].base);

//        // Initialize counters for timing
//        timer[i].rx_sleep_time = (uint16_t)(cfg[i].rxCycle * mdlSCI_cnf_TICKS_PER_MS);
//        timer[i].tx_sleep_time = (uint16_t)(cfg[i].txCycle * mdlSCI_cnf_TICKS_PER_MS);

    }// end for
}

////------------------------------------------------------------------------------------------------
///*!@brief   Transmit and receive data via the configured serial communication interfaces.
// *
//  *@return   none
// *\n
// *@note     The SCI hardware must first be set up by mdlHAL_init().
// *          The SCI interfaces must first be set up by mdlSCI_init().
// *\n
// */
//void mdlSCI_exec(void)
//{
//    uint8_t i;
//
//    // For each configured serial interface
//    for(i = 0; i < e_mdlSCI_cnf_SCI__endOfList; i++)
//    {
//        // Check the arguments
//        ASSERT(SCI_isBaseValid(cfg[i].base));
//
//        // if a valid buffer was configured
//        if(cfg[i].rxBuffer != e_mdlFIFO_cnf_buf__none)
//        {
//
//            // Clear a possible break detect flag
//            mdlSCI_clearBreakDetect(cfg[i].base);
//
//            // Decrement sleep time counter while SCI module inactive
//            if(timer[i].rx_sleep_time)
//            {
//                timer[i].rx_sleep_time--;
//            }
//            // Counter for sleep time has expired. SCI module activity is required.
//            if(0 == timer[i].rx_sleep_time)
//            {
//                // Read data from serial interface and save to configured receive buffer
//                mdlSCI_receive(cfg[i].rxBuffer, (mdlSCI_cnf_SCI_t) i);
//                // Reset counter
//                timer[i].rx_sleep_time = (uint16_t)(cfg[i].rxCycle * mdlSCI_cnf_TICKS_PER_MS);
//            }
//        }
//
//        // if a valid buffer was configured
//        if(cfg[i].txBuffer != e_mdlFIFO_cnf_buf__none)
//        {
//            // Decrement sleep time counter while SCI module inactive
//            if(timer[i].tx_sleep_time)
//            {
//                timer[i].tx_sleep_time--;
//            }
//            // Counter for sleep time has expired. SCI module activity is required.
//            if(0 == timer[i].tx_sleep_time)
//            {
//                // Write data from transmit buffer to serial interface
//                mdlSCI_transmit(cfg[i].txBuffer, (mdlSCI_cnf_SCI_t) i);
//                // Reset counter
//                timer[i].tx_sleep_time = (uint16_t)(cfg[i].txCycle * mdlSCI_cnf_TICKS_PER_MS);
//            }
//        }
//
//    }// end for
//}

//------------------------------------------------------------------------------------------------
/*!@brief   Transmit data from FIFO to serial port.
 *
 *@details  Data from the FIFO thisBuf will be written to the hardware FIFO as long as there is
 *          space available, i.e. a maximum 16 bytes will be transferred.
 *
 *@param    thisBuf     :   FIFO buffer configured in mdlFIFO
 *@param    thisPort    :   serial interface configured in this module
 *
 *@return   none
 *\n
 */
void mdlSCI_writeCharArray(mdlSCI_cnf_SCI_t thisPort, uint16_t *data, uint8_t noOfBytes)
{

    //write data to specified port
    SCI_writeCharArray(cfg[thisPort].base, data, noOfBytes);

}

////------------------------------------------------------------------------------------------------
///*!@brief   Transmit data from FIFO to serial port.
// *
// *@details  Data from the FIFO thisBuf will be written to the hardware FIFO as long as there is
// *          space available, i.e. a maximum 16 bytes will be transferred.
// *
// *@param    thisBuf     :   FIFO buffer configured in mdlFIFO
// *@param    thisPort    :   serial interface configured in this module
// *
// *@return   none
// *\n
// *@note     Call this function cyclically.
// *\n
// */
//mdlSCI_ERROR_t mdlSCI_transmit(mdlFIFO_cnf_buf_t thisBuf, mdlSCI_cnf_SCI_t thisPort)
//{
//    mdlSCI_ERROR_t error = e_mdlSCI_ERROR__no;
//    uint8_t free, unread;
//    uint8_t data[16];
//
//    // if FIFO empty -> exit
////    unread = mdlFIFO_used(thisBuf);
//    if(unread == 0)
//    {
//        error = e_mdlSCI_ERROR__FIFOempty;
//        return error;
//    }
//
//    // if hardware transmit buffer full -> exit
//    free = 16 - SCI_getTxFIFOStatus(cfg[thisPort].base);
//    if(free == 0)
//    {
//        error = e_mdlSCI_ERROR__txFIFOfull;
//        return error;
//    }
//
//    // limit to free space of hardware transmit buffer
//    if(unread > free)
//    {
//        unread = free;
//    }
//
//    // if not possible to read unread no. of bytes from FIFO -> exit
////    if(!mdlFIFO_read(data, unread, thisBuf))
////    {
////        error = e_mdlSCI_ERROR__readFIFO;
////        return error;
////    }
//
//    //write data to specified port
//    SCI_writeCharArray(cfg[thisPort].base, data, unread);
//
//    return error;
//}

////------------------------------------------------------------------------------------------------
///*!@brief   Receive data from serial port and save to FIFO
// *
// *@details  Data from the hardware FIFO will be written to thisBuf as long as there is space
// *          available in thisBuf, i.e. a maximum 16 bytes will be transferred per call.
// *
// *@param    thisBuf     :   FIFO buffer configured in mdlFIFO
// *@param    thisPort    :   serial interface configured in this module
// *
// *@return   none
// *\n
// *@note     Call this function cyclically.
// *\n
// */
//mdlSCI_ERROR_t mdlSCI_receive(mdlFIFO_cnf_buf_t thisBuf, mdlSCI_cnf_SCI_t thisPort)
//{
//    mdlSCI_ERROR_t error = e_mdlSCI_ERROR__no;
//    uint8_t free, unread;
//    uint8_t data[16];
//
//    // if hardware receive buffer empty -> exit
//    unread = SCI_getRxFIFOStatus(cfg[thisPort].base);
//    if(unread == SCI_FIFO_RX0)
//    {
//        error = e_mdlSCI_ERROR__rxFIFOempty;
//        return error;
//    }
//
//    // if FIFO full -> exit
////    free = mdlFIFO_free(thisBuf);
//    if(free == 0)
//    {
//        error = e_mdlSCI_ERROR__FIFOfull;
//        return error;
//    }
//
//    // limit to free space of FIFO
//    if(unread > free)
//    {
//        unread = free;
//    }
//
//    // read unread no. of bytes from port
//    SCI_readCharArray(cfg[thisPort].base, data, unread);
//
////    // if not possible to write data to specified FIFO, flag error
////    if(!mdlFIFO_write(data, unread, thisBuf))
////    {
////        error = e_mdlSCI_ERROR__writeFIFO;
////    }
//
//    return error;
//}

////------------------------------------------------------------------------------------------------
///*!@brief   Check the break detect flag and clear it, if set.
// *
// *@param    base    base address of the SCI port
// *
// *@return   none
// *\n
// *@note     A break detect will block any further reception and therefore must be cleared!
// *\n
// */
//void mdlSCI_clearBreakDetect(uint32_t base)
//{
//
//#ifdef DEBUG
//    //                  01234567890123
//    char debug_txt[] = "Clr BRKDT SCIA";
//#endif
//
//    // If break detect flagged, reset SCI module
//    if(SCI_getRxStatus(base) & SCI_RXSTATUS_BREAK)
//    {
//        SCI_performSoftwareReset(base);  // perform software reset
//
//#ifdef DEBUG
//        switch(base)
//        {
//            case SCIA_BASE: //do nothing
//                break;
//#ifdef SCIB_BASE
//            case SCIB_BASE: debug_txt[13] += 1;
//                break;
//#endif
//#ifdef SCIC_BASE
//            case SCIC_BASE: debug_txt[13] += 2;
//                break;
//#endif
//#ifdef SCID_BASE
//            case SCID_BASE: debug_txt[13] += 3;
//                break;
//#endif
//            default:        //do nothing
//                break;
//        }
//        DEBUG_PRINT(debug_txt);
//#endif
//
//    }
//}

    //-------------------------
    // Private Section
    //*************************



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCTION SECTION - END
//=============================================================================


/******************************************************************************
 * THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 * UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 * MAY LEAD TO PROSECUTION.
 *****************************************************************************/

/** @}*/

