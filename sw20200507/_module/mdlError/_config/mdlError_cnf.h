/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLERROR__CONFIG_MDLERROR_CNF_H_
	#define MODULE_MDLERROR__CONFIG_MDLERROR_CNF_H_

/******************************************************************************/
/*!@file mdlError_cnf.h @copyright
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
/*!@file            mdlError_cnf.h
 *
 * @details         This module sets up a list of error objects and provides
 *                  access to the information (such as error code, error
 *                  message, enabled or not, flagged or not) of each one.
 ******************************************************************************/


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


#include <stdint.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// For complete integration of the module you just have to
//	#include the "mdlError_cnf.h" to you project
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


    /*!@brief
     * List of errors to be managed by the mdlError module.
     */
    typedef enum mdlError_cnf_ErrorFlag
    {
        e_mdlError_cnf_ErrorFlag__OverallError     =  0,        //!< use this as an overall error flag, i.e.
                                                                //!< if disabled, all errors are disabled
                                                                //!< code will hold the code of the error that occurred first
                                                                // TODO: SHOULD HOLD VALUE OF ERROR THAT OCCURED LAST!!

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 1. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION: List of error flags.
    //              Enter matching settings in
    //              2. SELF-CONFIGURATION SECTION below.
    //>>

        e_mdlError_cnf_ErrorFlag__VsupplyMax,                   //!< 24V supply voltage above limit, flagged by comparator CMPSS1L
        e_mdlError_cnf_ErrorFlag__VsupplyMin,                   //!< 24V supply voltage below limit, flagged by comparator CMPSS3L

        e_mdlError_cnf_ErrorFlag__VbusMax,                      //!< bus voltage above limit, flagged by comparator CMPSS6H
        e_mdlError_cnf_ErrorFlag__VbusMin,                      //!< bus voltage below limit, flagged by comparator CMPSS6L

        e_mdlError_cnf_ErrorFlag__VgyrHigh,                     //!< gyrator voltage above limit, flagged by comparator CMPSS2H
        e_mdlError_cnf_ErrorFlag__IgyrHigh,                     //!< gyrator current above limit, flagged by comparator CMPSS3H
        e_mdlError_cnf_ErrorFlag__IinvHigh,                     //!< inverter current above limit, flagged by comparator CMPSS4H

        e_mdlError_cnf_ErrorFlag___FAULT_SIL,                    //!< external SIL fault from hardware

//        e_mdlError_cnf_ErrorFlag__Fault_ext                     //!< over temperature input active
//        e_mdlError_cnf_ErrorFlag__TempAHigh,                    //!< temperature A above limit, flagged by comparator CMPSS7H
//        e_mdlError_cnf_ErrorFlag__TempBHigh,                    //!< temperature B above limit, flagged by comparator CMPSS5H
//        e_mdlError_cnf_ErrorFlag__TempGyrHigh,                  //!< temperature of gyrator above limit, flagged by comparator CMPSS2L
//        e_mdlError_cnf_ErrorFlag__FanDriver,                    //!< fan driver chip problem (open/short circuit)



    //<<
    //<<<< 1. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlError_cnf_ErrorFlag__endOfList
    }mdlError_cnf_ErrorFlag_t;

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 2. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: Specific defines to adjust the
    //              error module
    //>>

        #define  mdlError_cnf_MSG_LEN    8         //!< max. length of error messages

    //<<
    //<<<< 2. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------



#endif /* MODULE_MDLERROR__CONFIG_MDLERROR_CNF_H_ */

#ifdef	LOAD_MODULE_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 3. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	List of configurations for each error type.
    //              Refer to mdlError_cfg_ErrorFlag_t for details on each entry.
    //
    // IMPORTANT:   THE ORDER IS DEFINED THROUGH YOUR NAMING ORDER ABOVE.
    //
    // SYNTAX:      {error code, error message (up to mdlError_cnf_MSG_LEN chars), error enable flag},
    //

        //
        // Limit message to mdlError_cnf_MSG_LEN chars!!!
        //    "123456789"
        //
        // Overall error
        // -> if disabled all errors are disabled
        // -> error code will hold the code of the error that occurred first
        {  0, "All", true},

        // 24V supply voltage above limit, flagged by comparator CMPSS1L
        {201, "V_24V H", true},

        // 24V supply voltage below limit, flagged by comparator CMPSS3L
        {202, "V_24V L", true},

        // bus voltage above limit, flagged by comparator CMPSS6H
        {203, "V_bus H", true},

        // bus voltage above limit, flagged by comparator CMPSS6L
        {204, "V_bus L", true},

        // gyrator voltage above limit, flagged by comparator CMPSS2H
        {301, "V_gyr H", true},

        // gyrator current above limit, flagged by comparator CMPSS3H
        {302, "I_gyr H", true},

        // inverter current above limit, flagged by comparator CMPSS4H
        {303, "I_inv H", true},

        // external pwm enable SIL fault
        {  0, "SIL", true},


//        // temperature A above limit, flagged by comparator CMPSS7H
//        {406, "TempA H", true},
//
//        // temperature B above limit, flagged by comparator CMPSS5H
//        {407, "TempB H", true},
//
//        // temperature of gyrator above limit, flagged by comparator CMPSS2L
//        {408, "TmpGyr H", true},
//
//        // temperature of µC above limit
//        {405, "TempuC H", true},
//
//        // temperature A sensor problem (open/short circuit)
//        {1, "TempA X", true},
//
//        // temperature B sensor problem (open/short circuit)
//        {2, "TempB X", true},
//
//        // gyrator temperature sensor problem (open/short circuit)
//        {3, "TmpGyr X", true},
//
//        // fan driver chip problem (open/short circuit)
//        {5, "Fan", true},

    //<<
    //<<<< 3. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//		MODULE CONFIGURATION	- END
//==============================================================================

/** @}*/

