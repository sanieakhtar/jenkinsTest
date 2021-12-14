/**
 * \defgroup Modules
 * @{
 */


/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLADC_CONFIG_MDLADC_CNF_H_
	#define MODULE_MDLADC_CONFIG_MDLADC_CNF_H_

/******************************************************************************/
/*!@file mdlADC_cnf.h @copyright
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
/*!@file            mdlADC_cnf.h
 *
 * @details         Configuration data of the ADC module.
 ******************************************************************************/


/*****************************************************************************/
/*! \addtogroup mdlADC ADC
 *@brief  Configure on-chip ADCs including SOCs
 *
 *  This module provides functions for setup of the ADC modules and the
 *  conversions (SOCs) to be performed.
 *  @{
 *****************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlADC_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlADC_cnf_...".
//      Please avoid identical declaration elsewhere!
//
//      This settlement EXCLUDES private declarations and definitions
//      which validity is bound to this file.
//
//*****************************************************************************


#include <stdint.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// For complete integration of the module you just have to
//	#include the "mdlADC_cnf.h" to you project
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
     * List of SOCs to be configured by the mdlADC.
     */
    typedef enum mdlADC_cnf_SOC
    {
        e_mdlADC_cnf_SOC__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 1. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: list of configured ADC conversions (SOCs)
    //              A channel can be sampled more than once.
    //
    //              Configuration data -> refer to
    //              4. SELF-CONFIGURATION SECTION
    //>>

        //
        // ADC-A SOCs
        //
        e_mdlADC_cnf_SOC__V_gyr,         //!< gyrator voltage (A4) to be sampled @ switching frequency
        e_mdlADC_cnf_SOC__V_bus,         //!< DC bus voltage (A8)

        //
        // ADC-B SOCs
        //
        e_mdlADC_cnf_SOC__I_gyr,         //!< gyrator current (B10) to be sampled @ switching frequency
        e_mdlADC_cnf_SOC__Ph_inv,        //!< inverter phase (B6) to be sampled @ 1kHz (AIO2)
        e_mdlADC_cnf_SOC__V_24V_avg,     //!< 24V supply voltage (B3)
        e_mdlADC_cnf_SOC__Temp_uC,       //!< chip temperature (channel B14), requires an acquisition time of at least 700 ns!!

        //
        // ADC-C SOCs
        //
//        e_mdlADC_cnf_SOC__V_24V,         //!< 24V supply voltage (C14)
//        e_mdlADC_cnf_SOC__V_bus_avg,     //!< filtered DC bus voltage (C5)
//        e_mdlADC_cnf_SOC__I_inv_avg,     //!< filtered inverter current (C3)
        e_mdlADC_cnf_SOC__I_inv,         //!< inverter current (C8)
//        e_mdlADC_cnf_SOC__Temp_gyr,      //!< gyrator temperature (C4)
        e_mdlADC_cnf_SOC__Temp_gyr_avg,  //!< filtered gyrator temperature (C1)
        e_mdlADC_cnf_SOC__Temp_A,        //!< temperature A (C10)
        e_mdlADC_cnf_SOC__Temp_B,        //!< temperature B (C15)

    //<<
    //<<<< 1. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlADC_cnf_SOC__endOfList
    }mdlADC_cnf_SOC_t;


    /*!@brief
     * List of ADC modules to be configured by the mdlADC.
     */
    typedef enum mdlADC_cnf_ADC
    {
        e_mdlADC_cnf_ADC__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 2. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: list of ADC modules to be configured
    //
    //              Configuration data -> refer to
    //              5. SELF-CONFIGURATION SECTION
    //>>

        e_mdlADC_cnf_ADC__A,                                            //!< module ADC-A
        e_mdlADC_cnf_ADC__B,                                            //!< module ADC-B
        e_mdlADC_cnf_ADC__C,                                            //!< module ADC-C

    //<<
    //<<<< 2. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlADC_cnf_ADC__endOfList
    }mdlADC_cnf_ADC_t;


    // Macros to be used in calculations
    #define mdlADC_12BIT_RANGE              4095U                       //!< ADC 12 bit range
    #define mdlADC_12BIT_OFFSET             2048U                       //!< ADC offset for signals with DC

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 3. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: Specific defines to adjust the
    //              ADC module
    //>>

    #define mdlADC_V_REF                    3.3f                        //!< ADC ext. ref. voltage for all ADC modules
    #define mdlADC_RANGE                    mdlADC_12BIT_RANGE          //!< Numerical range of ADC modules
    #define mdlADC_OFFSET                   mdlADC_12BIT_OFFSET         //!< ADC offset

    // Acquisition window duration in SYSCLK cycles should be a value between 1 and 512 cycles
    // inclusive. The selected duration must be at least as long as one ADCCLK cycle.
    #define  mdlADC_cnf_SH_TIME_DEFAULT     20                          //!< S&H time for all ADC channels: 20+1*SYSCLK = 212ns@99MHz

    // Settings for internal temperature sensor connect to ADC-B14
    #define  mdlADC_cnf_ADC_BASE_TEMP_UC    ADCB_BASE                   //!< ADC module of chip temp. sensor is B
    #define  mdlADC_cnf_ADC_CH_TEMP_UC      ADC_CH_ADCIN14              //!< ADC channel of chip temp. sensor is 14
    #define  mdlADC_cnf_SH_TIME_TEMP_UC     99                          //!< S&H time for ADC-B14 (chip temp.):100+1*SYSCLK = 1020ns@99MHz

    //<<
    //<<<< 3. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------


#endif /* MODULE_MDLADC_CONFIG_MDLADC_CNF_H_ */

#ifdef  LOAD_MODULE_CONFIGURATION

    // Use these macros in the configuration below.
    // Burst mode: allows a single trigger to walk through the round-robin SOCs one or more at a time.
    #define BURST_ENABLE        1
    #define BURST_DISABLE       0

    // Select external reference (ADC_REFERENCE_2_5V or ADC_REFERENCE_3_3V will use internal reference)
//    #define ADC_REFERENCE_EXT   ((ADC_ReferenceVoltage)0xFF)

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 4. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: List of settings for the ADC module(s) of the microcontroller
    //
    // IMPORTANT:   THE ORDER IS DEFINED THROUGH YOUR NAMING ORDER ABOVE -> refer to mdlADC_cnf_ADC_t
    //
    // SYNTAX:      {base, pre-scaler, referenceVoltage, pulseMode, priorityMode, burstEnable, burstTrigger, burstSize},
    //
    // EXAMPLES:    configure ADC-A clock to SYSCLK/4, use internal 2.5V ref., SOC 0-1 hi pri and others in round robin, enable burst mode triggered by EPWM8 SOCB and perform 1 SOC
    //              {ADCA_BASE, ADC_CLK_DIV_4_0, ADC_REFERENCE_2_5V, ADC_MODE_SINGLE_ENDED, ADC_PULSE_END_OF_ACQ_WIN, ADC_PRI_THRU_SOC1_HIPRI, BURST_ENABLE, ADC_TRIGGER_EPWM8_SOCB, 1},
    //
    //              configure ADC-C clock to SYSCLK/4, use internal 3.3V ref., all SOCs in round robin mode, disable burst mode
    //              {ADCC_BASE, ADC_CLK_DIV_4_0, ADC_REFERENCE_3_3V, ADC_MODE_SINGLE_ENDED, ADC_PULSE_END_OF_ACQ_WIN, ADC_PRI_ALL_ROUND_ROBIN, BURST_DISABLE, ADC_TRIGGER_SW_ONLY, 0},
    //
    //              configure ADC-B clock to SYSCLK/4, use external ref., all SOCs in round robin mode, disable burst mode
    //              {ADCB_BASE, ADC_CLK_DIV_4_0, ADC_REFERENCE_EXTERNAL, ADC_MODE_SINGLE_ENDED, ADC_PULSE_END_OF_ACQ_WIN, ADC_PRI_ALL_ROUND_ROBIN, BURST_DISABLE, ADC_TRIGGER_SW_ONLY, 0},
    //
    //>>

    // configure ADC-A clock to SYSCLK/4, use internal 3.3V ref., SOC0 is high priority, remaining in round robin mode, disable burst mode but
    {ADCA_BASE, ADC_CLK_DIV_4_0, ADC_REFERENCE_3_3V, ADC_PULSE_END_OF_ACQ_WIN, ADC_PRI_SOC0_HIPRI, BURST_DISABLE, ADC_TRIGGER_SW_ONLY, 0},

    // configure ADC-B clock to SYSCLK/4, use internal 3.3V ref., SOC0+1 are high priority, remaining in round robin mode, enable burst mode, but trigger only one SOC at a time
    {ADCB_BASE, ADC_CLK_DIV_4_0, ADC_REFERENCE_3_3V, ADC_PULSE_END_OF_ACQ_WIN, ADC_PRI_THRU_SOC1_HIPRI, BURST_ENABLE, ADC_TRIGGER_EPWM8_SOCA, 1},

    // configure ADC-C clock to SYSCLK/4, use internal 3.3V ref., all SOCs in round robin mode, enable burst mode, but trigger only one SOC at a time
    {ADCC_BASE, ADC_CLK_DIV_4_0, ADC_REFERENCE_3_3V, ADC_PULSE_END_OF_ACQ_WIN, ADC_PRI_ALL_ROUND_ROBIN, BURST_ENABLE, ADC_TRIGGER_EPWM8_SOCA, 1},

    //<<
    //<<<< 4. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif

#ifdef	LOAD_SOC_CONFIGURATION

    // If no interrupt shall be configured, use this macro for the entry "interrupt number" in
    // the configurations below.
    #define ADC_INT_DISABLED (ADC_IntNumber) 0xFF

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 5. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	List of settings for the SOCs (start of conversion) of the ADC modules
    //
    // IMPORTANT:   THE ORDER IS DEFINED THROUGH YOUR NAMING ORDER ABOVE -> refer to mdlADC_cnf_SOC_t
    //              If multiple channels of the same ADC module are configured (usually the case),
    //              the function mdlADC_init() will initialize each ADC module only once.
    //              If a module is not used, it will not be configured by mdlADC_init().
    //
    // SYNTAX:      {ADC module, channel, SOC no., trigger (ADC_TRIGGER_SW_ONLY = not trig.), interrupt no. (0xFF=no int.)},
    //
    // EXAMPLES:    ADC-A2 input to be sampled by SOC-0 triggered by EPWM8 SOCA, flags interrupt 1 at end of conversion
    //              {e_mdlADC_cnf_ADC__A, ADC_CH_ADCIN2, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM8_SOCA, ADC_INT_NUMBER1},
    //
    //              ADC-A3 input to be sampled by SOC-2, no trigger and no interrupt configured
    //              {e_mdlADC_cnf_ADC__A, ADC_CH_ADCIN3, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, 0xFF},
    //
    //
    //>>


    // ADC-A
    //
    // V_gyr -> A4, high priority SOC, triggered by PWM, no interrupt
    {e_mdlADC_cnf_ADC__A, ADC_CH_ADCIN4, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM3_SOCA, ADC_INT_DISABLED},

    // V_bus -> A8
    {e_mdlADC_cnf_ADC__A, ADC_CH_ADCIN8, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM8_SOCA, ADC_INT_DISABLED},


    // ADC-B set to burst mode below, therefore given triggers for standard SOCs are don't care here!
    //
    //I_gyr -> B10, high priority SOC, triggered by PWM, synchronously to V_gyr, flag interrupt 1 at end of conversion
//    {e_mdlADC_cnf_ADC__B, ADC_CH_ADCIN2, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM3_SOCA, ADC_INT_NUMBER1},
    {e_mdlADC_cnf_ADC__B, ADC_CH_ADCIN10, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM3_SOCA, ADC_INT_NUMBER1},
    // changed to change input from high pass filter to low pass filter?

    // Ph_inv -> B6, high prio SOC
    {e_mdlADC_cnf_ADC__B, ADC_CH_ADCIN6, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM8_SOCA, ADC_INT_DISABLED},

    // V_24V_avg -> B3
    {e_mdlADC_cnf_ADC__B, ADC_CH_ADCIN3, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_INT_DISABLED},

    //Temp_uC -> B14
    {e_mdlADC_cnf_ADC__B, ADC_CH_ADCIN14, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_INT_DISABLED},


    // ADC-C set to burst mode below, therefore given triggers are don't care here!
    //
//    // V_24V -> C14
//    {e_mdlADC_cnf_ADC__C, ADC_CH_ADCIN14, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_INT_DISABLED},
//
//    // V_bus_avg -> C5
//    {e_mdlADC_cnf_ADC__C, ADC_CH_ADCIN5, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_INT_DISABLED},
//
//    // I_inv_avg -> C3
//    {e_mdlADC_cnf_ADC__C, ADC_CH_ADCIN3, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_INT_DISABLED},

    // I_INV -> C8
    {e_mdlADC_cnf_ADC__C, ADC_CH_ADCIN8, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_INT_DISABLED},

    // Temp_gyr_avg -> C1
    {e_mdlADC_cnf_ADC__C, ADC_CH_ADCIN1, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_INT_DISABLED},

    // Temp_A -> C10
    {e_mdlADC_cnf_ADC__C, ADC_CH_ADCIN10, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_INT_DISABLED},

    // Temp_B -> C15
    {e_mdlADC_cnf_ADC__C, ADC_CH_ADCIN15, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_INT_DISABLED},

    //<<
    //<<<< 5. SELF-CONFIGURATION SECTION	- END
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


/** @}*/

