/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLHAL_MDLHAL_H_
    #define MODULE_MDLHAL_MDLHAL_H_

/*****************************************************************************/
/*!@file HAL.h @copyright
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
/*!@file            mdlHAL.h
 *
 * @details         Configures all used pins as specified in mdlHAL_cnf.h.
 *****************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlHAL_..."
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

//*****************************************************************************
/*! \addtogroup mdlHAL HAL
*@brief  hardware abstraction layer
*
*  This Module defines all hardware specific IO's as an Enumeration.
*  It also gives a Config enumeration wich provides the Register Addresses
*  to configure the MUX Register for special peripheral functionality
* @{
*/
//*****************************************************************************



//=============================================================================
// Includes
#include "./_config/mdlHAL_cnf.h"
#include "driverlib.h"


//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define ENABLE  1
#define DISABLE 0
#define HIGH    1
#define LOW     0

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

void     mdlHAL_init(void);
uint16_t mdlHAL_getPinNumber(mdlHAL_cnf_PIN_t i);
uint32_t mdlHAL_readPin(mdlHAL_cnf_PIN_t i);
void     mdlHAL_writePin(mdlHAL_cnf_PIN_t i, uint32_t val);
void     mdlHAL_togglePin(mdlHAL_cnf_PIN_t i);


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCTION SECTION - END
//=============================================================================

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


/******************************************************************************
 * THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 * UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 * MAY LEAD TO PROSECUTION.
 *****************************************************************************/
#endif /* MODULE_MDLHAL_MDLHAL_H_ */

/** @}*/

