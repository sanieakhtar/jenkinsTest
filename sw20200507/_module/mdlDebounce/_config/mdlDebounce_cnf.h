/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLDEBOUNCE__CONFIG_MDLDEBOUNCE_CNF_H_
	#define MODULE_MDLDEBOUNCE__CONFIG_MDLDEBOUNCE_CNF_H_

/******************************************************************************/
/*!@file mdlDebounce_cnf.h @copyright
 *      THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 *\n    UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 *      MAY LEAD TO PROSECUTION.
 *\n
 *\n    IPT Technology GmbH
 *\n    Im Martelacker 14
 *\n    79588 Efringen-Kirchen
 *\n    Germany
 *\n    Phone:   +49 7628 692 96-0
 *\n    Fax:     +49 7628 692 96-99
 *\n    info@ipt-technology.com
 *\n    www.ipt-technology.com
 ******************************************************************************/


/******************************************************************************/
/*!@file            mdlDebounce_cnf.h
 *
 * @details         Module for debouncing input signals such as from a
 *                  connected switch.
 *                  There are two different debounce times: one for the high
 *                  to low transition and for the low to high.
 ******************************************************************************/


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


#include <stdint.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// For complete integration of the module you just have to
//	#include the "mdlDebounce_cnf.h" to you project
//
//	CONFIGURATION STEPS
//	---------------------
//	1. Search for "SELF-CONFIGURATION SECTION"s and do your desired configurations
//	2. Have a look for the "LOAD_MODULE_CONFIGURATION" section if present and fit
//		this section to your needs
//
//	ATTENTION:	Often the configurations in the second step are dependend on
//				the configurations of the first.
//				(The number of "objects" for example.)
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//		MODULE CONFIGURATION	- START
//==============================================================================

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 1. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	macros to adjust the behavior of the module
    //>>

    #define mdlDebounce_cnf_TICKS_PER_MS         0.1F //!< The number of OS ticks per millisecond.
    #define mdlDebounce_cnf_HIGH_TO_LOW_TIME    50    //!< time in [ms] for debouncing a high to low transition
    #define mdlDebounce_cnf_LOW_TO_HIGH_TIME    50    //!< time in [ms] for debouncing a low to high transition

    //<<
    //<<<< 1. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------


#endif /* MODULE_MDLDEBOUNCE__CONFIG_MDLDEBOUNCE_CNF_H_ */

#ifdef	LOAD_MODULE_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 2. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	TODO description
    //>>

    //<<
    //<<<< 2. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//		MODULE CONFIGURATION	- END
//==============================================================================

/** @}*/

