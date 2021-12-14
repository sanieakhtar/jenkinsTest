/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLSCI_MDLSCI_H_
    #define MODULE_MDLSCI_MDLSCI_H_

/*****************************************************************************/
/*!@file mdlSCI.h @copyright
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
/*!@file            mdlSCI.h
 *
 * @details         Provides functions for the cyclic transmission and
 *                  reception of RS232 messages.
 *****************************************************************************/

/*****************************************************************************/
/*! \addtogroup mdlSCI Serial Communications Interface
 *@brief  Configure cyclic serial messages
 *
 *  This module provides functions for the cyclic transmission and reception
 *  of RS232 messages.
 *  @{
 *****************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "TODO namingConvention_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "TODO namingConvention _...".
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
#include "driverlib.h"
//#include "globals.h"
#include "./_config/mdlSCI_cnf.h"

//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


/*!@brief
 * Internal mdlSCI error identifier.
 */
typedef enum mdlSCI_ERROR
{
    e_mdlSCI_ERROR__no    = 0,  //!< No error present.
    e_mdlSCI_ERROR__init,       //!< Error occurred during initialization of SCI module.
    e_mdlSCI_ERROR__FIFOempty,  //!< Software buffer empty.
    e_mdlSCI_ERROR__FIFOfull,   //!< Software buffer full.
    e_mdlSCI_ERROR__readFIFO,   //!< Can't read all data bytes from FIFO.
    e_mdlSCI_ERROR__writeFIFO,  //!< Can't write all data bytes to FIFO
    e_mdlSCI_ERROR__rxFIFOempty,//!< Hardware receive  buffer full.
    e_mdlSCI_ERROR__txFIFOfull //!< Hardware transmit buffer full.
}mdlSCI_ERROR_t;


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

void mdlSCI_init(void);
//void mdlSCI_exec(void);
//void mdlSCI_clearBreakDetect(uint32_t base);
void mdlSCI_writeCharArray(mdlSCI_cnf_SCI_t thisPort, uint16_t *data, uint8_t noOfBytes);

//mdlSCI_ERROR_t mdlSCI_transmit(mdlFIFO_cnf_buf_t thisFifo, mdlSCI_cnf_SCI_t thisPort);
//mdlSCI_ERROR_t mdlSCI_receive(mdlFIFO_cnf_buf_t thisFifo, mdlSCI_cnf_SCI_t thisPort);

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
#endif /* MODULE_MDLSCI_MDLSCI_H_ */

/** @}*/

