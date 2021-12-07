/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLERROR_MDLERROR_H_
    #define MODULE_MDLERROR_MDLERROR_H_

/*****************************************************************************/
/*!@file mdlError.h @copyright
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
/*!@file            mdlError.h
 *
 * @details         This module sets up a list of error objects and provides
 *                  access to the information (such as error code, error
 *                  message, enabled or not, flagged or not) of each one.
 *****************************************************************************/

/*****************************************************************************/
/*! \addtogroup mdlError Error Manager
 *@brief  Configure error types
 *  
 *  @{
 *****************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlError_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlError_cnf_...".
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
#include "driverlib.h"
#include "globals.h"
#include "./_config/mdlError_cnf.h"

//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//#ifndef uint8_t
//typedef uint16_t uint8_t;
//#endif


/*!@brief
* Error module error flag descriptor.
*
* @ref mdlEPWM_cnf.h
*/
typedef struct mdlError_cfg_ErrorFlag
{
  uint16_t                          code;       //!< error code
  char         msg[mdlError_cnf_MSG_LEN];       //!< error message
  bool                           enabled;       //!< 1 = enable error flag
  bool                           flagged;       //!< 1 = flagged
  uint16_t                         count;       //!< number of occurrences
}mdlError_cfg_ErrorFlag_t;


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

void        mdlError_init(void);
uint16_t    mdlError_getErrorCode(void);
bool        mdlError_get(mdlError_cnf_ErrorFlag_t flag);
bool        mdlError_isEnabled(mdlError_cnf_ErrorFlag_t flag);
bool        mdlError_set(mdlError_cnf_ErrorFlag_t flag);
void        mdlError_clear(mdlError_cnf_ErrorFlag_t flag);

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
#endif /* MODULE_MDLERROR_MDLERROR_H_ */

/** @}*/

