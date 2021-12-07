/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLOPSMODE_MDLOPSMODE_H_
    #define MODULE_MDLOPSMODE_MDLOPSMODE_H_

/*****************************************************************************/
/*!@file mdlOpsMode.h @copyright
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
/*!@file            mdlOpsMode.h
 *
 * @details         This module is used to retrieve the current operating state
 *                  of the inverter by reading the status of GPIO33 & GPIO34 as
 *                  follows:
 *
 *                  Mode        | GPIO33 | GPIO34
 *                  Development |   0    |   X
 *                  Test        |   1    |   0
 *                  Field       |   1    |   1
 *
 *****************************************************************************/

/*****************************************************************************/
/*! \addtogroup mdlOpsMode Operation Mode
 *@brief This module is used to retrieve the current operating state
 *       of the inverter by reading the status of GPIO33 & GPIO34 as
 *       follows:
 *
 *                  Mode        | GPIO33 | GPIO34
 *                  Development |   0    |   X
 *                  Test        |   1    |   0
 *                  Field       |   1    |   1
 *  
 *  @{
 *****************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlOpsMode_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlOpsMode_cnf_...".
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
#include <stdbool.h>
#include "globals.h"
#include "./_config/mdlOpsMode_cnf.h"

//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//typedef uint16_t uint8_t;
//TODO \todo : remove unnecessary typedef


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

void                    mdlOpsMode_init(void);
mdlOpsMode_cnf_Mode_t   mdlOpsMode_getMode(void);


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
#endif /* MODULE_MDLOPSMODE_MDLOPSMODE_H_ */

/** @}*/
