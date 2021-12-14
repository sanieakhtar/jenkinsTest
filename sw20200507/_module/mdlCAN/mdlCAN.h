/** \addtogroup Modules
 *  @{
 */

#ifndef MDLCAN_H_
    #define MDLCAN_H_

/*****************************************************************************/
/*!@file mdlCAN.h @copyright
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
/*!@file            mdlCAN.h
 *
 * @details         This module provides functions for the cyclic transmission
 *                  and reception of CAN messages.
 *                  The required CAN messages are specified in the
 *                  configuration file mdlCAN_cnf.h.
 *****************************************************************************/


/*****************************************************************************/
/*! \addtogroup mdlCAN Controller Area Network
 *@brief  Configure cyclic CAN messages
 *
 *  This module provides functions for the cyclic transmission and reception
 *  of CAN messages.
 *  @{
 *****************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlCAN_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlCAN_cnf_...".
//      Please avoid identical declaration elsewhere!
//
//      This settlement EXCLUDES private declarations and definitions
//      which validity is bound to this file.
//
//*****************************************************************************



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes
#include <stdint.h>
#include "driverlib.h"
#include "globals.h"
#include "./_config/mdlCAN_cnf.h"


//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//#ifndef uint8_t
//    typedef uint16_t uint8_t;
//#endif

/*!@brief
 * Internal mdlCAN error identifier.
 */
typedef enum mdlCAN_ERROR
{
    e_mdlCAN_ERROR__no    = 0,  //!< No error present.
    e_mdlCAN_ERROR__init,       //!< Error occurred during initialization of CAN module.
    e_mdlCAN_ERROR__rxTimeout   //!< CAN message not received in time.
}mdlCAN_ERROR_t;


/*!@brief
* Message descriptor.
*/
typedef struct mdlCAN_cfg_MSG
{
  mdlCAN_cnf_CAN_t      port;   //!< Option to decide whether to use CAN for comm or test. Always comms. Can be replaced. typedef not needed.
  uint32_t                id;   //!< The CAN message ID.
  CAN_MsgFrameType id_format;   //!< Define whether the standard or extended ID format is used.
  CAN_MsgObjType   direction;   //!< Define whether it is transmitting or receiving
  uint8_t             length;   //!< Data length. Maximum is 8 bytes.
  uint8_t           priority;   //!< CAN priority -> Currently NOT USED!! Message object 1 has the highest priority.
  uint16_t            period;   //!< Transmission/reception period in [ms]. Maximum is 32767ms.
                                //!< Transmit messages are sent at this period.
                                //!< Receive messages are checked for new data at this period.
                                //!< A period of 0xFFFF prevents transmission and checking for new data.
  uint8_t            timeout;   //!< Time [no. of periods] within which a new msg must be received.
                                //!< E.g. for period=100ms and timeout=2, local data will become invalid
                                //!< if no reception within 300ms. A timeout of 0xFF disables timeout checking.
}mdlCAN_cfg_MSG_t;

/*!@brief
* Descriptor for bit timing settings.
*/
typedef struct mdlCAN_cfg_CAN
{
  uint32_t              base;   //!< Base address of CAN module.
  uint16_t              baud;   //!< Bitrate of the CAN module [kbit/s]. Each CAN module can only operate at one bitrate.
  uint8_t            bitTime;   //!< Bit time recommended for the above baud rate.
  uint32_t            regVal;   //!< CAN_BTR register settings recommended for the above baud rate.
}mdlCAN_cfg_CAN_t;


/*!@brief
 * CAN message slot.
 * Connects timing, data and configuration.
 */
struct mdlCAN_SLOT
{
    uint16_t                data[mdlCAN_cnf_MAX_MSG_DATA_LENGTH];       //!< buffer for msg payload
    uint16_t                                            nextCall;       //!< time [ms] until next transmit/receive
    uint8_t                                           msgsMissed;       //!< no. of missed messages (@ref mdlCAN_cfg_MSG_t) since last update of message
    bool                                              msgUpdated;       //!< flag indicating whether message data was updated
    mdlCAN_cfg_MSG_t*                                        cfg;       //!< pointer to configuration of msg
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

void                mdlCAN_init(void);
void                mdlCAN_exec(void);

bool                mdlCAN_dataUpdated(mdlCAN_cnf_MSG_t msg);
void                mdlCAN_dataWait(mdlCAN_cnf_MSG_t msg);

uint16_t*           mdlCAN_getDataRef(mdlCAN_cnf_MSG_t msg);
mdlCAN_ERROR_t      mdlCAN_updateData(mdlCAN_cnf_MSG_t msg, uint16_t* buf);

void                mdlCAN_transmitMessage(mdlCAN_cnf_MSG_t msg);

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
#endif /* MODULE_MDLCAN_MDLCAN_H_ */

/** @}*/

