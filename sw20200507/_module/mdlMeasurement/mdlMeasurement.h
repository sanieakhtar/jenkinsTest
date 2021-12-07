/** \addtogroup Modules
 *  @{
 */

#ifndef MDLMEASUREMENT_H_
    #define MDLMEASUREMENT_H_

/*****************************************************************************/
/*!@file mdlMeasurement.h @copyright
 *      THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 *\n    UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE
 *\n    FILES MAY LEAD TO PROSECUTION.
 *\n
 *\n    IPT Technology GmbH
 *\n    Im Martelacker 14
 *\n    79588 Efringen-Kirchen
 *\n    Germany
 *\n    Phone:   +49 7621 662 0
 *\n    Fax:     +49 7621 662 144
 *\n    info@ipt-technology.com
 *\n    www.ipt-technology.com
 *****************************************************************************/


/*****************************************************************************/
/*!@file            mdlMeasurement.h
 *
 * @details         Provides functions to acquire measurements.
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
//*****************************************************************************
/*! \addtogroup mdlMeasurement Measurement
*@brief  Measurement Module
*
*   A Detailed Description starts here.
* @{
*/
//*****************************************************************************
#include <stdint.h>
#include "./_config/mdlMeasurement_cnf.h"
#include "globals.h"

void mdlMeasurement_init(void);
void mdlMeasurement_update(void);

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
#endif /* MDLMEASUREMENT_H_ */

/** @}*/

