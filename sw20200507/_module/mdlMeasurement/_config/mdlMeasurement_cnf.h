/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLMEASUREMENT_CONFIG_MDLMEASUREMENT_CNF_H_
	#define MODULE_MDLMEASUREMENT_CONFIG_MDLMEASUREMENT_CNF_H_

/******************************************************************************/
/*!@file mdlMeasurement_cnf.h @copyright
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
/*!@file            mdlMeasurement_cnf.h
 *
 * @details         TODO long_description.
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
//	#include the "mdlMeasurement_cnf.h" to you project
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
    // EXPLANATION:	TODO description
    //>>

        // Gains for voltages (gain = physical voltage [V] / voltage @ ADC pin [V])
        //
    #define mdlMeasurement_VGYR_GAIN         (1./.00260)                 //!< gyrator voltage gain
    #define mdlMeasurement_VBUS_GAIN         (1./.00346)                 //!< bus voltage gain
    #define mdlMeasurement_V24V_GAIN         (1./.10000)                 //!< supply voltage gain

    // Gains for currents (gain = physical current [A]/ voltage @ ADC pin [V])
    //
// THIS IS THE REAL ONE:
    #define mdlMeasurement_IGYR_GAIN         (1./(.01273 * 3))           //!< gyrator current gain [A/V]
//    #define mdlMeasurement_IGYR_GAIN         (1./.03358 /.63662)         //!< gyrator current gain [A/V]
    #define mdlMeasurement_IINV_GAIN         (1./.05000)                 //!< inverter current gain [A/V]

    // Gains for phase (gain = physical value [°]/ voltage @ ADC pin [V])
    //
    #define mdlMeasurement_PHINV_GAIN        (1./.00917)                 //!< inverter phase [°/V]

    // Gain for temperature measurement to standardize CMPSS configuration
    //
    #define mdlMeasurement_TEMP_GAIN         (1./1.0000)                 //!< temperature conversion gain

    //<<
    //<<<< 1. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif /* MODULE_MDLMEASUREMENT_CONFIG_MDLMEASUREMENT_CNF_H_ */


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//		MODULE CONFIGURATION	- END
//==============================================================================

/** @}*/

