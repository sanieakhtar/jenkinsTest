/**
 * \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLMONITOR__CONFIG_MDLMONITOR_CNF_H_
	#define MODULE_MDLMONITOR__CONFIG_MDLMONITOR_CNF_H_

/******************************************************************************/
/*!@file mdlMonitor_cnf.h @copyright
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
/*!@file            mdlMonitor_cnf.h
 *
 * @details         The monitor checks the value of a variable against a
 *                  threshold. If the result of the check is true, a delayed
 *                  action is performed (call of a function with an argument).
 *                  Different types of checks can be configured such as "match
 *                  threshold", above or below threshold.
 *                  Depending on the configured delay the action will be
 *                  performed immediately or with a delay.
 *                  In this way one can set up flexible thresholds and delays
 *                  for e.g. flagging and clearing error conditions or for
 *                  turning on and off fans.
 ******************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlMonitor_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlMonitor_cnf_...".
//      Please avoid identical declaration elsewhere!
//
//      This settlement EXCLUDES private declarations and definitions
//      which validity is bound to this file.
//
//*****************************************************************************


#include <stdint.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// For complete integration of the module you just have to
//	#include the "mdlMonitor_cnf.h" to you project
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
     * List of variables to be monitored.
     */
    typedef enum mdlMonitor_cnf_CHECK
    {
        e_mdlMonitor_cnf_CHECK__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 1. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: list of configured checks
    //
    //>>

        //
        // Monitor NTC temperature sensor problems to flag or clear errors accordingly
        //
//        e_mdlMonitor_cnf_CHECK__flagTemp1SensorError,       //!< if temperature 1 is not available, flag error
//        e_mdlMonitor_cnf_CHECK__flagTemp2SensorError,       //!< if temperature 2 is not available, flag error
//        e_mdlMonitor_cnf_CHECK__flagTemp3SensorError,       //!< if temperature 3 is not available, flag error
//        e_mdlMonitor_cnf_CHECK__flagTemp4SensorError,       //!< if temperature 4 is not available, flag error
//
//        e_mdlMonitor_cnf_CHECK__clearTemp1SensorError,      //!< if temperature 1 is valid, clear error
//        e_mdlMonitor_cnf_CHECK__clearTemp2SensorError,      //!< if temperature 2 is valid, clear error
//        e_mdlMonitor_cnf_CHECK__clearTemp3SensorError,      //!< if temperature 3 is valid, clear error
//        e_mdlMonitor_cnf_CHECK__clearTemp4SensorError,      //!< if temperature 4 is valid, clear error
//
//        //
//        // Monitor temperatures to flag or clear errors accordingly
//        //
//        e_mdlMonitor_cnf_CHECK__flagOvertemp1Error,         //!< if temperature 1 is above threshold, flag error
//        e_mdlMonitor_cnf_CHECK__flagOvertemp2Error,         //!< if temperature 2 is above threshold, flag error
//        e_mdlMonitor_cnf_CHECK__flagOvertemp3Error,         //!< if temperature 3 is above threshold, flag error
//        e_mdlMonitor_cnf_CHECK__flagOvertemp4Error,         //!< if temperature 4 is above threshold, flag error
//        e_mdlMonitor_cnf_CHECK__flagOvertempuCError,        //!< if chip temperature is above threshold, flag error
//
//        e_mdlMonitor_cnf_CHECK__clearOvertemp1Error,        //!< if temperature 1 is below threshold, clear error
//        e_mdlMonitor_cnf_CHECK__clearOvertemp2Error,        //!< if temperature 2 is below threshold, clear error
//        e_mdlMonitor_cnf_CHECK__clearOvertemp3Error,        //!< if temperature 3 is below threshold, clear error
//        e_mdlMonitor_cnf_CHECK__clearOvertemp4Error,        //!< if temperature 4 is below threshold, clear error
//        e_mdlMonitor_cnf_CHECK__clearOvertempuCError,       //!< if chip temperature is below threshold, clear error

        //
        // Monitor max. temperature to control fans accordingly
        //
        e_mdlMonitor_cnf_CHECK__enableFans,                 //!< if max. temperature is above threshold, enable fans
        e_mdlMonitor_cnf_CHECK__disableFans,                //!< if max. temperature is below threshold, disable fans


    //<<
    //<<<< 1. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlMonitor_cnf_CHECK__endOfList
    }mdlMonitor_cnf_CHECK_t;


    /*!@brief
     * Available types of thresholds.
     */
    typedef enum mdlMonitor_type
    {
        e_mdlMonitor_type__equalThreshold  = 0,
        e_mdlMonitor_type__notEqualThreshold,
        e_mdlMonitor_type__aboveThreshold,
        e_mdlMonitor_type__belowThreshold,

        e_mdlMonitor_type__endOfList
    }mdlMonitor_type_t;


    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 2. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: Specific defines to adjust the
    //              monitor module
    //>>

        #define mdlMonitor_cnf_TICKS_PER_MS         0.1F  //!< The number of OS ticks per millisecond.

    //<<
    //<<<< 2. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------


#endif /* MODULE_MDLMONITOR__CONFIG_MDLMONITOR_CNF_H_ */

#ifdef	LOAD_MODULE_CONFIGURATION
//#if 0  //need to add appropriate variable we want to monitor
//
//    //----------------------------------------------
//    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//    //>>>> 3. SELF-CONFIGURATION SECTION	- START
//    //
//    // EXPLANATION:	Configured conditions to be monitored
//    //              For more details refer to mdlMonitor_cfg_Monitor_t
//    //
//    // SYNTAX:      {ptr to variable, threshold, threshold type, error delay [OS ticks] (0=no delay), action (=function), argument (to be passed to funciton)},
//    //
//    // EXAMPLES:    Flag over-temperature error if Temp_ntc1 > 80 for more than 30s
//    //              {&Temp_ntc1, 80, e_mdlMonitor_type__aboveThreshold, 3000, mdlSM_flagError, e_mdlError_cnf_ErrorFlag__Temp1High},
//    //
//    //              Clear over-temperature error if Temp_ntc1 < 60 for more than 5s
//    //              {&Temp_ntc1, 60, e_mdlMonitor_type__belowThreshold,  500, mdlSM_clearError, e_mdlError_cnf_ErrorFlag__Temp1High},
//    //>>
//
//    // Flag temperature sensor error if temperature not available (NTC open/short circuited) for more than 1s
//    {&Temp_ntc1, ABSOLUTE_ZERO, e_mdlMonitor_type__equalThreshold,  100, mdlSM_flagError, e_mdlError_cnf_ErrorFlag__Temp1Sensor},
//    // Flag temperature sensor error if temperature not available (NTC open/short circuited) for more than 1s
//    {&Temp_ntc2, ABSOLUTE_ZERO, e_mdlMonitor_type__equalThreshold,  100, mdlSM_flagError, e_mdlError_cnf_ErrorFlag__Temp2Sensor},
//    // Flag temperature sensor error if temperature not available (NTC open/short circuited) for more than 1s
//    {&Temp_ntc3, ABSOLUTE_ZERO, e_mdlMonitor_type__equalThreshold,  100, mdlSM_flagError, e_mdlError_cnf_ErrorFlag__Temp3Sensor},
//    // Flag temperature sensor error if temperature not available (NTC open/short circuited) for more than 1s
//    {&Temp_ntc4, ABSOLUTE_ZERO, e_mdlMonitor_type__equalThreshold,  100, mdlSM_flagError, e_mdlError_cnf_ErrorFlag__Temp4Sensor},
//
//    // Clear temperature sensor error if valid for more than 5s
//    {&Temp_ntc1, ABSOLUTE_ZERO, e_mdlMonitor_type__notEqualThreshold,  500, mdlSM_clearError, e_mdlError_cnf_ErrorFlag__Temp1Sensor},
//    // Clear temperature sensor error if valid for more than 5s
//    {&Temp_ntc2, ABSOLUTE_ZERO, e_mdlMonitor_type__notEqualThreshold,  500, mdlSM_clearError, e_mdlError_cnf_ErrorFlag__Temp2Sensor},
//    // Clear temperature sensor error if valid for more than 5s
//    {&Temp_ntc3, ABSOLUTE_ZERO, e_mdlMonitor_type__notEqualThreshold,  500, mdlSM_clearError, e_mdlError_cnf_ErrorFlag__Temp3Sensor},
//    // Clear temperature sensor error if valid for more than 5s
//    {&Temp_ntc4, ABSOLUTE_ZERO, e_mdlMonitor_type__notEqualThreshold,  500, mdlSM_clearError, e_mdlError_cnf_ErrorFlag__Temp4Sensor},
//
//    // Flag over-temperature error if above threshold for more than 30s
//    {&Temp_ntc1, INV_cnf__Temp1_TRIP, e_mdlMonitor_type__aboveThreshold, 3000, mdlSM_flagError, e_mdlError_cnf_ErrorFlag__Temp1High},
//    // Flag over-temperature error if above threshold for more than 30s
//    {&Temp_ntc2, INV_cnf__Temp2_TRIP, e_mdlMonitor_type__aboveThreshold, 3000, mdlSM_flagError, e_mdlError_cnf_ErrorFlag__Temp2High},
//    // Flag over-temperature error if above threshold for more than 30s
//    {&Temp_ntc3, INV_cnf__Temp3_TRIP, e_mdlMonitor_type__aboveThreshold, 3000, mdlSM_flagError, e_mdlError_cnf_ErrorFlag__Temp3High},
//    // Flag over-temperature error if above threshold for more than 30s
//    {&Temp_ntc4, INV_cnf__Temp4_TRIP, e_mdlMonitor_type__aboveThreshold, 3000, mdlSM_flagError, e_mdlError_cnf_ErrorFlag__Temp4High},
//    // Flag over-temperature error if above threshold for more than 30s
//    {&Temp_uC, INV_cnf__TempuC_TRIP, e_mdlMonitor_type__aboveThreshold, 3000, mdlSM_flagError, e_mdlError_cnf_ErrorFlag__TempuCHigh},
//
//    // Clear over-temperature error if below threshold for more than 5s
//    {&Temp_ntc1, INV_cnf__Temp1_CLR_TRIP, e_mdlMonitor_type__belowThreshold,  500, mdlSM_clearError, e_mdlError_cnf_ErrorFlag__Temp1High},
//    // Clear over-temperature error if below threshold for more than 5s
//    {&Temp_ntc2, INV_cnf__Temp2_CLR_TRIP, e_mdlMonitor_type__belowThreshold,  500, mdlSM_clearError, e_mdlError_cnf_ErrorFlag__Temp2High},
//    // Clear over-temperature error if below threshold for more than 5s
//    {&Temp_ntc3, INV_cnf__Temp3_CLR_TRIP, e_mdlMonitor_type__belowThreshold,  500, mdlSM_clearError, e_mdlError_cnf_ErrorFlag__Temp3High},
//    // Clear over-temperature error if below threshold for more than 5s
//    {&Temp_ntc4, INV_cnf__Temp4_CLR_TRIP, e_mdlMonitor_type__belowThreshold,  500, mdlSM_clearError, e_mdlError_cnf_ErrorFlag__Temp4High},
//    // Clear over-temperature error if below threshold for more than 5s
//    {&Temp_uC, INV_cnf__TempuC_CLR_TRIP, e_mdlMonitor_type__belowThreshold,  500, mdlSM_clearError, e_mdlError_cnf_ErrorFlag__TempuCHigh},
//
//    // Enable fans if temperature over threshold for more than 1s
//    {&Temp_max, INV_cnf__Temp_FAN_ON, e_mdlMonitor_type__aboveThreshold,  100, mdlSM_controlFans, 1},
//    // Disable fans if temperature below threshold for more than 20s
//    {&Temp_max, INV_cnf__Temp_FAN_OFF, e_mdlMonitor_type__belowThreshold, 2000, mdlSM_controlFans, 0},
//
//    // Flag mains supply low error, if AC mains voltage below threshold for more than 100ms
//    {&V_ac_rms, INV_cnf__V_AC_TRIP, e_mdlMonitor_type__belowThreshold, 10, mdlSM_flagError, e_mdlError_cnf_ErrorFlag__VACLow},
//    // Clear mains supply low error, if AC mains voltage above threshold for more than 500ms
//    {&V_ac_rms, INV_cnf__V_AC_CLR_TRIP, e_mdlMonitor_type__aboveThreshold, 50, mdlSM_clearError, e_mdlError_cnf_ErrorFlag__VACLow},
//
//    // Signal mains supply not present, if AC mains voltage below threshold for more than 5s
//    {&V_ac_rms, INV_cnf__V_AC_NOT_PRESENT, e_mdlMonitor_type__belowThreshold, (INV_cnf__V_AC_DETECT_TIME*mdlMonitor_cnf_TICKS_PER_MS), mdlSM_setACMainsSupplyStatus, 0},
//    // Signal mains supply present, if AC mains voltage above threshold for more than 5s
//    {&V_ac_rms, INV_cnf__V_AC_PRESENT, e_mdlMonitor_type__aboveThreshold, (INV_cnf__V_AC_DETECT_TIME*mdlMonitor_cnf_TICKS_PER_MS), mdlSM_setACMainsSupplyStatus, 1},
//
//    //<<
//    //<<<< 3. SELF-CONFIGURATION SECTION	- END
//    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//    //----------------------------------------------
//#endif

//    // Enable fans if temperature over threshold for more than 1s
//    {&Temp_max, INV_cnf__Temp_FAN_ON, e_mdlMonitor_type__aboveThreshold,  100, mdlSM_controlFans, 1},
//    // Disable fans if temperature below threshold for more than 20s
//    {&Temp_max, INV_cnf__Temp_FAN_OFF, e_mdlMonitor_type__belowThreshold, 2000, mdlSM_controlFans, 0},

#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//		MODULE CONFIGURATION	- END
//==============================================================================

/** @}*/

