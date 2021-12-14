/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file mdlCAN.c @copyright
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
/*!@file            mdlCAN.c
 * @brief           Manage cyclic transmission and reception of CAN messages
 *//*
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/


/*****************************************************************************/
/*! \addtogroup mdlCAN Controller Area Network
 *@brief  Configure cyclic CAN messages
 *
 *  This module provides functions for the cyclic transmission and reception
 *  of CAN messages.
 *  @{
 *****************************************************************************/


//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes
//
#include <limits.h>
#include "device.h"
#include "mdlCAN.h"

//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

static mdlCAN_cfg_CAN_t cfgMod[e_mdlCAN_cnf_CAN__endOfList] = {
#define LOAD_MODULE_CONFIGURATION
    #include "./_config/mdlCAN_cnf.h"
#undef  LOAD_MODULE_CONFIGURATION
};

static mdlCAN_cfg_MSG_t cfgMsg[e_mdlCAN_cnf_MSG__endOfList] = {
#define LOAD_MESSAGE_CONFIGURATION
    #include "./_config/mdlCAN_cnf.h"
#undef  LOAD_MESSAGE_CONFIGURATION
};


///*!@brief
// * CAN message slot.
// * Connects timing, data and configuration.
// */
//struct mdlCAN_SLOT
//{
//    uint16_t                data[mdlCAN_cnf_MAX_MSG_DATA_LENGTH];       //!< buffer for msg payload
//    uint16_t                                            nextCall;       //!< time [ms] until next transmit/receive
//    uint8_t                                           msgsMissed;       //!< no. of missed messages (@ref mdlCAN_cfg_MSG_t) since last update of message
//    bool                                              msgUpdated;       //!< flag indicating whether message data was updated
//    mdlCAN_cfg_MSG_t*                                        cfg;       //!< pointer to configuration of msg
//};


/*!@brief
 * Local array of objects, each holding the configuration of the CAN message,
 * its data bytes and time for next transmit or receive.
 */
static struct mdlCAN_SLOT slot[e_mdlCAN_cnf_MSG__endOfList];



/*!@brief
 * Structure that holds current time and sleep time both in [ms].
 */
typedef struct Timer_st {
    uint16_t    currentTime;
    uint16_t    sleepTime;
}Timer;

#define mdlCAN_MAX_SLEEPTIME    5000  //(uint16_t)0x7FFF     //!< This is an illegal sleep value used to initialize sleepTime variable.

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

    static void mdlCAN_setupModules(void);
    static void mdlCAN_startModules(void);
    static void mdlCAN_setupMessages(void);
    static void mdlCAN_calculateSleeptime(Timer *me);
    static void mdlCAN_transmit_receive(Timer *me);
    static bool mdlCAN_readMessage(uint32_t base, uint32_t objID, uint16_t *msgData, uint16_t msgLen);

    //-------------------------
    // Public Section
    //*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Initialise CAN modules
 *
 *@ref      mdlCAN_cfg_MSG_t
 *@ref      mdlCAN_cnf.h
 *
 *@return   none
 *\n
 *@note     CAN tx and rx pins must be configured elsewhere (i.e. in mdlHAL_cnf.h)!
 *\n
 */
void mdlCAN_init(void)
{
    uint8_t i, ii;

    //
    // Initialize the required CAN modules:
    // - put in initialization mode
    // - select clock
    // - set bitrate
    //
    mdlCAN_setupModules();

    //
    // Set up the CAN messages for each CAN module
    //
    mdlCAN_setupMessages();

    // For each configured CAN message, set up times for transmission and expected reception
    for(i = 0; i < e_mdlCAN_cnf_MSG__endOfList; i++)
    {

        // Point to message configuration
        slot[i].cfg              = &(cfgMsg[i]);

        // If period is outside legal range, do not transmit this CAN message!
        // Therefore also set nextCall to a value outside range.
        if (0xFFFF == slot[i].cfg->period)
        {
            slot[i].nextCall     = 0xFFFF;  //transmission/reception disabled
        }
        else
        {
            // Initialize time for start of CAN transmission depending on type of message
            if(CAN_MSG_OBJ_TYPE_TX == slot[i].cfg->direction)
            {
                slot[i].nextCall     = mdlCAN_cnf_TX_STARTUP_DELAY;
            }
            else if(CAN_MSG_OBJ_TYPE_RX == slot[i].cfg->direction)
            {
                slot[i].nextCall     = mdlCAN_cnf_RX_STARTUP_DELAY;
            }
            else
            {
                slot[i].nextCall     = 0xFFFF;  //transmission/reception disabled
            }
        }

        // Initialize data to all zeros
        for(ii=0; ii < mdlCAN_cnf_MAX_MSG_DATA_LENGTH; ii++)
        {
            slot[i].data[ii] = 0;
        }

        // Initialize to maximum
        slot[i].msgsMissed = ~0;

        // Initialize flag to false
        slot[i].msgUpdated = false;

    } // end for

    // Start CAN modules
    mdlCAN_startModules();
}



//------------------------------------------------------------------------------------------------
/*!@brief   Transmit and receive the configured CAN messages.
 *
 *
 *@return   none
 *\n
 *@note     The CAN message objects must first be set up by mdlCAN_init().
 *\n
 */
void mdlCAN_exec(void)
{
    static Timer    tmr = {0, 0};    //!< Timers (counting in [ms]) that control activity of CAN module.
    static uint16_t sleep_count = 0; //!< Tick counter for inactivity of CAN module.


    // Decrement sleep time counter while CAN module inactive
    if(sleep_count)
    {
        sleep_count -= 1;
    }
    // Counter for sleep time has expired. CAN module activity is required.
    else
    {

        // Increment timer (counting in [ms] -> see mdlCAN_cnf_TICKS_PER_MS) by sleep time
        tmr.currentTime += tmr.sleepTime;
        // Limit to valid range
        if (tmr.currentTime > mdlCAN_MAX_SLEEPTIME)
        {
            tmr.currentTime -= mdlCAN_MAX_SLEEPTIME;
        }

        // Transmit and receive required CAN messages
        mdlCAN_transmit_receive(&tmr);

        // Calculate sleep time (time of inactivity) until next CAN module activity
        mdlCAN_calculateSleeptime(&tmr);

        // Set required number of ticks, until next CAN module activity.
        sleep_count = (mdlCAN_cnf_TICKS_PER_MS * tmr.sleepTime) - 1;


    }//end else
}

//------------------------------------------------------------------------------------------------
/*!@brief   Transmit single CAN message using data from local buffer.
 *
 *@ref     mdlCAN_cnf_MSG_t
 *@ref     cfgMsg
 *@ref     cfgMod
 *
 *@param    msg is the number of the configured message.
 *
 *@return   none
 *
 *@note     This function does not set up any cyclic transmission of the CAN message.
 *
 *\n
 */
void mdlCAN_transmitMessage(mdlCAN_cnf_MSG_t msg)
{
    // Use library function for direct CAN message send
    // Message data slot[].data must have slot[i].cfg->length entries of type uint16_t !!
    CAN_sendMessage(cfgMod[slot[msg].cfg->port].base,
                    msg+1,
                    slot[msg].cfg->length,
                    slot[msg].data);

    // Wait for busy bit to clear, transfer between CAN and CAN Mailbox RAM
    // IF1 register is used inside CAN driver for transmit.
    while((HWREGH(cfgMod[slot[msg].cfg->port].base + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) == CAN_IF1CMD_BUSY)
    {
    }
}

//------------------------------------------------------------------------------------------------
/*!@brief   Returns a reference to the data buffer of message 'msg'.
 *
 *@ref      mdlCAN_cnf_MSG_t
 *
 *@param    msg     :   The message identifier @ref mdlCAN_cnf_MSG.
 *
 *@return   Reference to the data buffer of message 'msg'.
 *\n
 *@note
 *\n
 */
uint16_t* mdlCAN_getDataRef(mdlCAN_cnf_MSG_t msg)
{

    return slot[msg].data;

}

//------------------------------------------------------------------------------------------------
/*!@brief   Returns the whether data bytes where updated or not for message 'msg'.
 *
 *@ref      mdlCAN_cnf_MSG_t
 *
 *@param    msg         :   The message identifier @ref mdlCAN_cnf_MSG_t
 *
 *@return   msgUpdated  :   Indicates if local data buffer was updated by receive message in time.
 *\n                        Indicates if local data buffer was written to transmit message.
 *@note
 *\n
 */
bool mdlCAN_dataUpdated(mdlCAN_cnf_MSG_t msg)
{

    return slot[msg].msgUpdated;

}

//------------------------------------------------------------------------------------------------
/*!@brief   Clear the msgUpdated flag of message 'msg'.
 *
 *@ref      mdlCAN_cnf_MSG_t
 *
 *@param    msg         :   The message identifier @ref mdlCAN_cnf_MSG_t
 *
 *@return   msgUpdated  :   Indicates if local data buffer was updated by receive message in time.
 *\n                        Indicates if local data buffer was written to transmit message.
 *@note
 *\n
 */
void mdlCAN_dataWait(mdlCAN_cnf_MSG_t msg)
{

    slot[msg].msgUpdated = false;

}

//------------------------------------------------------------------------------------------------
/*!@brief   Update local buffer for the CAN message passed as first argument.
 *
 *@ref      mdlCAN_ERROR_t
 *
 *@param    msg     :   number of CAN message to be updated
 *@param    buf     :   pointer to data buffer
 *
 *@return   error   :   see @ref mdlCAN_ERROR_t
 *\n
 *@note     none
 *\n
 */
mdlCAN_ERROR_t mdlCAN_updateData(mdlCAN_cnf_MSG_t msg, uint16_t* buf)
{
    mdlCAN_ERROR_t  error = e_mdlCAN_ERROR__no;
    int i;

    // If message is of type transmit
    if(CAN_MSG_OBJ_TYPE_TX == slot[msg].cfg->direction)
    {
        // Copy length bytes from buffer to local transmit buffer
        for(i = 0; i < slot[msg].cfg->length; ++i)
        {
            slot[msg].data[i] = buf[i];
        }
    }

    // If message is of type receive
    else if(CAN_MSG_OBJ_TYPE_RX == slot[msg].cfg->direction)
    {
        // If valid received message
        if(slot[msg].msgUpdated)
        {
            // Copy length bytes from local receive buffer to buffer
            for(i = 0; i < slot[msg].cfg->length; ++i)
            {
                buf[i] = slot[msg].data[i];
            }
        }
        else
        {
            error = e_mdlCAN_ERROR__rxTimeout;
        }
    }

    else
    {
        // Not supported
        ASSERT(0);
    }

    return error;
}

    //-------------------------
    // Private Section
    //*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Initialize the CAN modules.
 *
 *@ref      mdlCAN_cnf.h
 *
 *@return   none
 *\n
 *@note     Each configured CAN module will be initialized.
 *          To start the CAN module(s), i.e. exit initialization mode, use mdlCAN_startModules().
 *\n
 */
static void mdlCAN_setupModules(void)
{

    uint8_t i;

    // For each configured CAN module
    for( i = 0; i < e_mdlCAN_cnf_CAN__endOfList; i++)
    {

        //
        // Check the arguments.
        //
        ASSERT(CAN_isBaseValid(cfgMod[i].base));

        //
        // Initialize the CAN controller module
        //
        CAN_initModule(cfgMod[i].base);

        //
        // Clock source can be selected for each CAN module from one of these:
        // - CAN_CLOCK_SOURCE_SYS  - Peripheral System Clock, i.e. the same as CPU clock
        // - CAN_CLOCK_SOURCE_XTAL - External Oscillator
        // - CAN_CLOCK_SOURCE_AUX  - Auxiliary Clock Input from GPIO
        //
        CAN_selectClockSource(cfgMod[i].base, CAN_CLOCK_SOURCE_SYS);

        //
        // Set up the CAN bus bit rate for the CAN module
        // Refer to the Driver Library User Guide for information on how to set
        // tighter timing control. Additionally, consult the device data sheet
        // for more information about the CAN module clocking.
        //
        CAN_setBitRate(cfgMod[i].base, SysCtl_getClock(DEVICE_OSCSRC_FREQ), (uint32_t) cfgMod[i].baud * 1000U, cfgMod[i].bitTime);
        // Alternatively set write value to bit timing register directly, because the bit time setting alone
        // will not always work for all kinds of bus lengths.
//        HWREG(cfgMod[i].base + CAN_O_BTR) = cfgMod[i].regVal;

    } // end for
}

//------------------------------------------------------------------------------------------------
/*!@brief   Start the CAN modules.
 *
 *@ref      mdlCAN_cnf.h
 *
 *@return   none
 *\n
 *@note     Each configured CAN module will be started by CAN_startModule().
 *
 *\n
 */
static void mdlCAN_startModules(void)
{

    uint8_t i;

    // For each configured CAN module
    for( i = 0; i < e_mdlCAN_cnf_CAN__endOfList; i++)
    {
        //
        // Check the arguments.
        //
        ASSERT(CAN_isBaseValid(cfgMod[i].base));

        // Start configured CAN module
        CAN_startModule(cfgMod[i].base);
    }
}

//------------------------------------------------------------------------------------------------
/*!@brief   Setup the configured CAN messages.
 *
 *@ref      mdlCAN_cnf.h
 *
 *
 *@return   none
 *\n
 *@note     Call mdlCAN_setupModule() prior to this which will clear the message RAM.
 *\n
 */
static void mdlCAN_setupMessages(void)
{
    uint8_t i;
    #define ID_MASK 0

    // For each configured CAN message
    for( i = 0; i < e_mdlCAN_cnf_MSG__endOfList; i++)
    {
        // Setup each message object with ID i+1, using the settings stored in variable cfg
        // and configured in file mdlCAN_cnf.h
        CAN_setupMessageObject(cfgMod[cfgMsg[i].port].base,
                               i+1,                 // object ID aka mailbox number (1..32)
                               cfgMsg[i].id,
                               cfgMsg[i].id_format,
                               cfgMsg[i].direction,
                               ID_MASK,
                               CAN_MSG_OBJ_NO_FLAGS,
                               cfgMsg[i].length);

    }//end for

}

//------------------------------------------------------------------------------------------------
/*!@brief   Calculate the time the CAN module can be sleeping until the next messages needs
 *          to be transmitted.
 *
 *@param    me    Pointer to timer
 *
 *@return   none
 *\n
 *@note     none
 *\n
 */
static void mdlCAN_calculateSleeptime(Timer *me)
{
    #define MAX_SLEEPTIME 10000     //!< Maximum sleep time in [ms]

    uint16_t i;
    uint16_t newTime;

    // Initialize to maximum
    me->sleepTime = mdlCAN_MAX_SLEEPTIME;

    // For each defined CAN message calculate the remaining time to the next required
    // activity and determine the shortest time of inactivity.
    for(i = 0; i < e_mdlCAN_cnf_MSG__endOfList; i++)
    {
        // Current time is greater than next scheduled activity, i.e. missed activity.
        // Re-schedule next transmission.
        if( me->currentTime > slot[i].nextCall )
        {
            newTime = (slot[i].nextCall + mdlCAN_MAX_SLEEPTIME) - me->currentTime;
        }
        /*else if( time == slot[i].nextCall )
        {
            // Not possible. All channels have been processed for this time point.
        }*/
        // Remaining time = time for next activity - current time
        else
        {
            newTime = slot[i].nextCall - me->currentTime;
        }

        // Save shortest time as new sleep time
        if( newTime < me->sleepTime )
        {
            me->sleepTime = newTime;
        }

    }//end for

    // Limit to valid range
    // TODO what's the maximum?
    if (me->sleepTime > MAX_SLEEPTIME)
    {
        me->sleepTime = MAX_SLEEPTIME;
    }

}

//------------------------------------------------------------------------------------------------
/*!@brief   Read new data of a Message Object and verify the DLC (data length code) is equal
 *          to or greater than the specified message length.
 *
 *@param    base is the base address of the CAN controller.
 *@param    objID is the object number to read (1-32).
 *@param    msgData is a pointer to the array to store the message data.
 *@param    msgLen is the expected message length (0-8 bytes, set to 0, if length is don't care).
 *
 *@return   Returns \b true if new data was retrieved and DLC is greater or equal to \e msgLen,
 *          else returns \b false.
 *
 *@note     This function is based on the implementation of the driverlib function
 *          CAN_readMessage().
 *          The message object requested by the \e objID must first be setup using the
 *          CAN_setupMessageObject() function.
 *          If the DLC of the received message is larger than the \e msgData buffer provided,
 *          then it is possible for a buffer overflow to occur.
 *\n
 */
static bool mdlCAN_readMessage(uint32_t base, uint32_t objID,
                               uint16_t *msgData, uint16_t msgLen)
{
    bool status = false;
    uint16_t msgCtrl = 0U;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((objID <= 32U) && (objID != 0U));
    ASSERT(msgLen <= 8U);

    //
    // Set the Message Data A, Data B, and control values to be read
    // on request for data from the message object.
    //
    // Transfer the message object to the message object IF register.
    //
    HWREG_BP(base + CAN_O_IF2CMD) =
    ((uint32_t)CAN_IF2CMD_DATA_A | (uint32_t)CAN_IF2CMD_DATA_B |
     (uint32_t)CAN_IF2CMD_CONTROL | (objID & CAN_IF2CMD_MSG_NUM_M));

    //
    // Wait for busy bit to clear
    //
    while((HWREGH(base + CAN_O_IF2CMD) & CAN_IF2CMD_BUSY) == CAN_IF2CMD_BUSY)
    {
    }

    //
    // Read out the IF control Register.
    //
    msgCtrl = HWREGH(base + CAN_O_IF2MCTL);

    //
    // See if there is new data available.
    //
    if((msgCtrl & CAN_IF2MCTL_NEWDAT) == CAN_IF2MCTL_NEWDAT)
    {
        // Verify that the DLC of the received message is greater or equal to the expected
        // number of data bytes
        if((msgCtrl & CAN_IF2MCTL_DLC_M) >= msgLen)
        {
            //
            // Read out the data from the CAN registers.
            //
            CAN_readDataReg(msgData, (base + CAN_O_IF2DATA),
                            (msgCtrl & CAN_IF2MCTL_DLC_M));

            status = true;
        }

        //
        // Now clear out the new data flag
        //
        HWREG_BP(base + CAN_O_IF2CMD) = ((uint32_t)CAN_IF2CMD_TXRQST |
                (objID & CAN_IF2CMD_MSG_NUM_M));

        //
        // Wait for busy bit to clear
        //
        while((HWREGH(base + CAN_O_IF2CMD) & CAN_IF2CMD_BUSY) ==
                CAN_IF2CMD_BUSY)
        {
        }
    }

    return(status);
}

//------------------------------------------------------------------------------------------------
/*!@brief   Transmit and receive the configured CAN messages based on timer.
 *
 *@param    me    Pointer to timers.
 *
 *@return   none
 *\n
 *@note     none
 *\n
 */
static void mdlCAN_transmit_receive(Timer *me)
{
    uint16_t i = 0;

    // For each defined CAN message, i.e. for each mailbox (up to 32 possible)
    for( i = 0; i < e_mdlCAN_cnf_MSG__endOfList; i++)
    {
        // If time is due, transmit message or check for received message
        if( me->currentTime == slot[i].nextCall )
        {
            // Increment counter for invalid/missing messages. Will be reset on successful transmit/receive.
            // At the moment this counter is only relevant for received messages, as CAN_sendMessage() does
            // not return any errors.
            if(~0 != slot[i].msgsMissed)
            {
                slot[i].msgsMissed += 1;
            }

            // If message is of type transmit
            if(CAN_MSG_OBJ_TYPE_TX == slot[i].cfg->direction)
            {
                // Transmit CAN message using data in local buffer.
                // Message data slot[].data must have slot[i].cfg->length entries of type uint16_t !!
                CAN_sendMessage(cfgMod[slot[i].cfg->port].base, i+1, slot[i].cfg->length, slot[i].data);

                // Data successfully written (CAN_sendMessage does currently not return any error codes)
                // -> reset counter and set flag to true.
                slot[i].msgsMissed = 0;
                slot[i].msgUpdated = true;
            }

            // If message is of type receive
            else if(CAN_MSG_OBJ_TYPE_RX == slot[i].cfg->direction)
            {
                // Check, if new and sufficient data bytes were received and read data from
                // mailbox i+1 and save to local buffer.
                // This will clear the new data flag.
                if(mdlCAN_readMessage(cfgMod[slot[i].cfg->port].base, i+1, slot[i].data, slot[i].cfg->length))
                {
                    // Data successfully read -> reset counter and set flag to true.
                    slot[i].msgsMissed = 0;
                    slot[i].msgUpdated = true;

                }
                // Data could not be read
                else
                {
                    // If time since last update > timeout, flag data as invalid
//                    if(slot[i].msgsMissed > slot[i].cfg->timeout)
                    if(slot[i].msgsMissed > 2)
                    {
                        // Set flag to false
                        slot[i].msgUpdated = false;
                    }
                }
            }

            // The message types CAN_MSG_OBJ_TYPE_TX_REMOTE and CAN_MSG_OBJ_TYPE_RXTX_REMOTE
            // should be handled by the CAN controller.
            else
            {
                // Do nothing!
            }

            // Set due time for next transmission/reception
            slot[i].nextCall = me->currentTime + slot[i].cfg->period;

            // If outside valid range, roll over
            if( slot[i].nextCall > mdlCAN_MAX_SLEEPTIME )
            {
                slot[i].nextCall -= mdlCAN_MAX_SLEEPTIME;
            }
        }// end if
    }// end for
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCTION SECTION - END
//=============================================================================

/*****************************************************************************/
/*! @}
 *  Close the Doxygen group.
 *****************************************************************************/

/******************************************************************************
 * THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 * UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 * MAY LEAD TO PROSECUTION.
 *****************************************************************************/


/** @}*/

