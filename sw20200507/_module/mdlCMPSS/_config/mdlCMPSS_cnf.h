/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLCMPSS_CONFIG_MDLCMPSS_CNF_H_
	#define MODULE_MDLCMPSS_CONFIG_MDLCMPSS_CNF_H_

/******************************************************************************/
/*!@file mdlCMPSS_cnf.h @copyright
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
/*!@file            mdlCMPSS_cnf.h
 *
 * @details         Configure the comparators of the analog subsystem.
 ******************************************************************************/


/*****************************************************************************/
/*! \addtogroup mdlCMPSS Comparators
 *@brief  Configure on-chip comparators
 *
 *  This module provides functions to configure the comparators of the
 *  analog subsystem.
 *  @{
 *****************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlCMPSS_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlCMPSS_cnf_...".
//      Please avoid identical declaration elsewhere!
//
//      This settlement EXCLUDES private declarations and definitions
//      which validity is bound to this file.
//
//*****************************************************************************


#include <stdint.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// For complete integration of the module you just have to
//	#include the "mdlCMPSS_cnf.h" to you project
//
//	CONFIGURATION STEPS
//	---------------------
//	1. Search for "SELF-CONFIGURATION SECTION"s and do your desired configurations
//	2. Have a look for the "LOAD_MODULE_CONFIGURATION" section if present and fit
//		this section to your needs
//
//	ATTENTION:	Often the configurations in the second step are dependent on
//				the configurations of the first.
//				(The number of "objects" for example.)
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//		MODULE CONFIGURATION	- START
//==============================================================================

    /*!@brief
     * List of CMPSSs to be configured by the mdlCMPSS.
     */
    typedef enum mdlCMPSS_cnf_CMPSS
    {
        e_mdlCMPSS_cnf_CMPSS__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 1. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: list of configured comparators
    //
    //>>

        e_mdlCMPSS_cnf_CMPSS__VsupplyTripMax,           //!< trip on supply voltage > DACL output
        e_mdlCMPSS_cnf_CMPSS__VsupplyTripMin,           //!< trip on supply voltage < DACL output

        e_mdlCMPSS_cnf_CMPSS__VbusTripMax,              //!< trip on bus voltage > DACH output
        e_mdlCMPSS_cnf_CMPSS__VbusTripMin,              //!< trip on bus voltage < DACL output

        e_mdlCMPSS_cnf_CMPSS__VgyrTripMax,              //!< trip on gyrator voltage > DACH output
        e_mdlCMPSS_cnf_CMPSS__IgyrTripMax,              //!< trip on gyrator current > DACH output
        e_mdlCMPSS_cnf_CMPSS__IinvTripMax,              //!< trip on inverter current > DACH output

//        e_mdlCMPSS_cnf_CMPSS__TempATripMax,             //!< trip on temperature A > DACH output
//        e_mdlCMPSS_cnf_CMPSS__TempBTripMax,             //!< trip on temperature B > DACH output
//        e_mdlCMPSS_cnf_CMPSS__TempGyrTripMax,           //!< trip on temperature gyrator > DACH output

    //<<
    //<<<< 1. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlCMPSS_cnf_CMPSS__endOfList
    }mdlCMPSS_cnf_CMPSS_t;


    /*!@brief
     * Enum to choose between high and low comparator
     */
    typedef enum mdlCMPSS_comparator{
        e_mdlCMPSS__comparator_COMPH,
        e_mdlCMPSS__comparator_COMPL
    }mdlCMPSS_comparator_t;


    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 2. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	Common settings
    //>>

    // Constants of internal DACs
    #define mdlCMPSS_DAC_RANGE      4095u           //!< range of internal DACs is 12-bit
    #define mdlCMPSS_DAC_V_REF      mdlADC_V_REF    //!< default to the ADC reference (selection possible for each DAC, but is not implemented)


    // Amount of hysteresis to be passed to CMPSS_setHysteresis().
    #define HYSTERESIS_NONE         0               //!< no hysteresis
    #define HYSTERESIS_TYPICAL      1               //!< typical hysteresis
    #define HYSTERESIS_2_TYPICAL    2               //!< 2 x typical hysteresis
    #define HYSTERESIS_3_TYPICAL    3               //!< 3 x typical hysteresis
    #define HYSTERESIS_4_TYPICAL    4               //!< 4 x typical hysteresis

    // Common amount of hysteresis to be passed to CMPSS_setHysteresis().
    // Select from available values HYSTERESIS_... above.
    #define mdlCMPSS_cnf_CMP_HYSTERESIS  HYSTERESIS_TYPICAL     //!< selected hysteresis

    // Common settings for the ramp generator to be passed to CMPSS_configRamp()
    // 16-bit maximum reference loaded into ramp generator during initialization
    #define mdlCMPSS_cnf_SLOPE_MAX        0                     //!< Initial setting for the maximum reference value
    // 13-bit delay value for the start of the slope generator in system clock cycles
    #define mdlCMPSS_cnf_SLOPE_DELAY      0                     //!< No delay

    //<<
    //<<<< 2. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------


#endif /* MODULE_MDLCMPSS_CONFIG_MDLCMPSS_CNF_H_ */

#ifdef	LOAD_CMPSS_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 3. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION: List here the configuration for each CMPSS module.
    //
    // IMPORTANT:   THE ORDER IS DEFINED THROUGH YOUR NAMING ORDER ABOVE.
    //
    //              Only the configuration of the High Side Comparators COMPH is currently supported!
    //
    //              These common settings are applied to all configured CMPSS modules:
    //              - negative comparator input connected to internal DAC
    //              - comparator output is not inverted, i.e. output = 1, if +in > -in
    //              - comparator output asynchronous path disabled
    //              - comparator hysteresis is set to mdlCMPSS_cnf_CMP_HYSTERESIS (see above)
    //              - DAC reference = VDDA
    //              - DAC value loaded from shadow on system clock
    //              - ramp generator maximum reference is initialized to mdlCMPSS_cnf_SLOPE_MAX (see above)
    //              - ramp generator delay is set to mdlCMPSS_cnf_SLOPE_DELAY (see above)
    //              - ramp generator is loaded directly from shadow register RAMPMAXREFS instead of from RAMPMAXREFA
    //
    // SYNTAX:      {base, comparator H or L, comparator configuration (such as source for neg. input, inverted output),
    //               initial DAC value, gain for respective DAC,
    //               ramp settings: DAC source (ramp or shadow reg.), ramp decrement, ramp reset by PWM no.,
    //               filter settings: clk pre-scaler (1..1024), sample window (0..32), threshold (window/2+1 .. window)
    //               output signals CTRIP (to ePWM X-Bar) and CTRIPOUT (to output X-Bar) configuration
    //
    // EXAMPLES:    see below
    //
    //
    //>>


    // Configure comparator for MAXIMUM SUPPLY VOLTAGE detection
    // CMPSS1 COMPL, negative input source is DAC, output is not inverted
    {CMPSS1_BASE, e_mdlCMPSS__comparator_COMPL, (CMPSS_INSRC_DAC),
    // DAC init = maximum supply voltage
    INV_cnf__V_24V_MAX_TRIP, mdlMeasurement_V24V_GAIN,
//    (INV_cnf__V_24V_MAX_TRIP / mdlMeasurement_V24V_GAIN * mdlADC_12BIT_RANGE / mdlADC_V_REF),
    // load DAC from user value, i.e. no ramp generator
    CMPSS_DACSRC_SHDW, 0, 0,
    // filter settings: use filtering (4=clk pre-scaler, 32=sample window length, 32=threshold)
    4, 32, 32,
    // output settings: filtered trip signal to ePWM and async signal for debugging output
    (CMPSS_TRIP_LATCH | CMPSS_TRIPOUT_ASYNC_COMP)},




    // Configure comparator for MINIMUM SUPPLY VOLTAGE detection
    // CMPSS3 COMPL, negative input source is DAC, output is inverted
    {CMPSS3_BASE, e_mdlCMPSS__comparator_COMPL, (CMPSS_INSRC_DAC|CMPSS_INV_INVERTED),
    // DAC init = minimum supply voltage
    INV_cnf__V_24V_MIN_TRIP, mdlMeasurement_V24V_GAIN,
//    (INV_cnf__V_24V_MIN_TRIP / mdlMeasurement_V24V_GAIN * mdlADC_12BIT_RANGE / mdlADC_V_REF),
    // load DAC from user value, i.e. no ramp generator
    CMPSS_DACSRC_SHDW, 0, 0,
    // filter settings: use filtering (4=clk pre-scaler, 32=sample window length, 32=threshold)
    4, 32, 32,
    // output settings: filtered trip signal to ePWM and async signal for debugging output
    (CMPSS_TRIP_LATCH | CMPSS_TRIPOUT_ASYNC_COMP)},




    // Configure comparator for MAXIMUM BUS VOLTAGE detection
    // CMPSS6 COMPH, negative input source is DAC, output is not inverted
    {CMPSS6_BASE, e_mdlCMPSS__comparator_COMPH, (CMPSS_INSRC_DAC),
    // DAC init = maximum bus voltage
    INV_cnf__V_BUS_MAX_TRIP, mdlMeasurement_VBUS_GAIN,
//    (INV_cnf__V_BUS_MAX_TRIP / mdlMeasurement_VBUS_GAIN * mdlADC_12BIT_RANGE / mdlADC_V_REF),
    // load DAC from user value, i.e. no ramp generator
    CMPSS_DACSRC_SHDW, 0, 0,
    // filter settings: use filtering (4=clk pre-scaler, 32=sample window length, 32=threshold)
    4, 32, 32,
    // output settings: filtered trip signal to ePWM and async signal for debugging output
    (CMPSS_TRIP_LATCH | CMPSS_TRIPOUT_ASYNC_COMP)},




    // Configure comparator for MINIMUM BUS VOLTAGE detection
    // CMPSS6 COMPL, negative input source is DAC, output is inverted
    {CMPSS6_BASE, e_mdlCMPSS__comparator_COMPL, (CMPSS_INSRC_DAC|CMPSS_INV_INVERTED),
    // DAC init = minimum bus voltage
    INV_cnf__V_BUS_MIN_TRIP, mdlMeasurement_VBUS_GAIN,
//    (INV_cnf__V_BUS_MIN_TRIP / mdlMeasurement_VBUS_GAIN * mdlADC_12BIT_RANGE / mdlADC_V_REF),
    // load DAC from user value, i.e. no ramp generator
    CMPSS_DACSRC_SHDW, 0, 0,
    // filter settings: use filtering (4=clk pre-scaler, 32=sample window length, 32=threshold)
    4, 32, 32,
    // output settings: filtered trip signal to ePWM and async signal for debugging output
    (CMPSS_TRIP_LATCH | CMPSS_TRIPOUT_ASYNC_COMP)},

    // Configure comparator for MAXIMUM GYRATOR VOLTAGE detection
    // CMPSS2 COMPH, negative input source is DAC, output is not inverted
    {CMPSS2_BASE, e_mdlCMPSS__comparator_COMPH, (CMPSS_INSRC_DAC),
    // DAC init = maximum gyrator current
    INV_cnf__V_GYR_TRIP, mdlMeasurement_VGYR_GAIN,
//    (INV_cnf__V_GYR_TRIP / mdlMeasurement_VGYR_GAIN * mdlADC_12BIT_RANGE / mdlADC_V_REF),
    // load DAC from user value, i.e. no ramp generator
    CMPSS_DACSRC_SHDW, 0, 0,
    // filter settings: use filtering (4=clk pre-scaler, 32=sample window length, 32=threshold)
    4, 32, 29,
    // output settings: filtered trip signal to ePWM and async signal for debugging output
    (CMPSS_TRIP_LATCH | CMPSS_TRIPOUT_ASYNC_COMP)},




    // Configure comparator for MAXIMUM GYRATOR CURRENT detection
    // CMPSS3 COMPH, negative input source is DAC, output is not inverted
    {CMPSS3_BASE, e_mdlCMPSS__comparator_COMPH, (CMPSS_INSRC_DAC),
    // DAC init = maximum gyrator current
    INV_cnf__I_GYR_TRIP, mdlMeasurement_IGYR_GAIN,
//    (INV_cnf__I_GYR_TRIP / mdlMeasurement_IGYR_GAIN * mdlADC_12BIT_RANGE / mdlADC_V_REF),
    // load DAC from user value, i.e. no ramp generator
    CMPSS_DACSRC_SHDW, 0, 0,
    // filter settings: use filtering (4=clk pre-scaler, 32=sample window length, 32=threshold)
    4, 32, 32,
    // output settings: filtered trip signal to ePWM and async signal for debugging output
    (CMPSS_TRIP_LATCH | CMPSS_TRIPOUT_ASYNC_COMP)},




    // Configure comparator for MAXIMUM INVERTER CURRENT detection
    // CMPSS4 COMPH, negative input source is DAC, output is not inverted
    {CMPSS4_BASE, e_mdlCMPSS__comparator_COMPH, (CMPSS_INSRC_DAC),
    // DAC init = maximum inverter current
    INV_cnf__I_INV_TRIP, mdlMeasurement_IINV_GAIN,
//    (INV_cnf__I_INV_TRIP / mdlMeasurement_IINV_GAIN * mdlADC_12BIT_RANGE / mdlADC_V_REF),
    // load DAC from user value, i.e. no ramp generator
    CMPSS_DACSRC_SHDW, 0, 0,
    // filter settings: use filtering (4=clk pre-scaler, 32=sample window length, 32=threshold)
    4, 32, 32,
    // output settings: filtered trip signal to ePWM and async signal for debugging output
    (CMPSS_TRIP_LATCH | CMPSS_TRIPOUT_ASYNC_COMP)},



/*
 *
    // Configure comparator for maximum temperature A detection
    //
    // TODO: {NOTE: The minimum must be detected because this is a NTC sensor!
    // Does this need to be implemented?}
    //
    // CMPSS7 COMPH, negative input source is DAC, output is inverted
    {CMPSS7_BASE, e_mdlCMPSS__comparator_COMPH, (CMPSS_INSRC_DAC|CMPSS_INV_INVERTED),
    // DAC init = minimum voltage at NTC input
    INV_cnf__TempA_MIN_TRIP, mdlMeasurement_TEMP_GAIN,
//    (INV_cnf__TempA_MIN_TRIP * mdlADC_12BIT_RANGE / mdlADC_V_REF),
    // load DAC from user value, i.e. no ramp generator
    CMPSS_DACSRC_SHDW, 0, 0,
    // filter settings: use filtering (4=clk pre-scaler, 32=sample window length, 32=threshold)
    4, 32, 32,
    // output settings: filtered trip signal to ePWM and async signal for debugging output
    (CMPSS_TRIP_LATCH | CMPSS_TRIPOUT_ASYNC_COMP)},




    // Configure comparator for maximum temperature B detection
    //
    // TODO: {NOTE: The minimum must be detected because this is a NTC sensor!
    // Does this need to be implemented?}
    //
    // CMPSS5 COMPH, negative input source is DAC, output is inverted
    {CMPSS5_BASE, e_mdlCMPSS__comparator_COMPH, (CMPSS_INSRC_DAC|CMPSS_INV_INVERTED),
    // DAC init = minimum voltage at NTC input
    INV_cnf__TempB_MIN_TRIP, mdlMeasurement_TEMP_GAIN,
//    (INV_cnf__TempB_MIN_TRIP * mdlADC_12BIT_RANGE / mdlADC_V_REF),
    // load DAC from user value, i.e. no ramp generator
    CMPSS_DACSRC_SHDW, 0, 0,
    // filter settings: use filtering (4=clk pre-scaler, 32=sample window length, 32=threshold)
    4, 32, 32,
    // output settings: filtered trip signal to ePWM and async signal for debugging output
    (CMPSS_TRIP_LATCH | CMPSS_TRIPOUT_ASYNC_COMP)},




    // Configure comparator for maximum gyrator temperature detection
    //
    // TODO: {NOTE: The minimum must be detected because this is an NTC sensor!
    // Does this need to be implemented?}
    //
    // CMPSS2 COMPL, negative input source is DAC, output is inverted
    {CMPSS2_BASE, e_mdlCMPSS__comparator_COMPL, (CMPSS_INSRC_DAC|CMPSS_INV_INVERTED),
    // DAC init = minimum voltage at NTC input
    INV_cnf__TempGYR_MIN_TRIP, mdlMeasurement_TEMP_GAIN,
//    (INV_cnf__TempGYR_MIN_TRIP * mdlADC_12BIT_RANGE / mdlADC_V_REF),
    // load DAC from user value, i.e. no ramp generator
    CMPSS_DACSRC_SHDW, 0, 0,
    // filter settings: use filtering (4=clk pre-scaler, 32=sample window length, 32=threshold)
    4, 32, 32,
    // output settings: filtered trip signal to ePWM and async signal for debugging output
    (CMPSS_TRIP_LATCH | CMPSS_TRIPOUT_ASYNC_COMP)},


    */

    //<<
    //<<<< 3. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//		MODULE CONFIGURATION	- END
//==============================================================================

/*****************************************************************************/
/*! @}
 *  Close the Doxygen group.
 *****************************************************************************/

/** @}*/

