/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLEPWM__CONFIG_MDLEPWM_CNF_H_
	#define MODULE_MDLEPWM__CONFIG_MDLEPWM_CNF_H_

/******************************************************************************/
/*!@file mdlEPWM_cnf.h @copyright
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
/*!@file            mdlEPWM_cnf.h
 *
 * @details         Configuration of the EPWM modules and their submodules.
 ******************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlEPWM_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlEPWM_cnf_...".
//      Please avoid identical declaration elsewhere!
//
//      This settlement EXCLUDES private declarations and definitions
//      which validity is bound to this file.
//
//*****************************************************************************


#include <stdint.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// For complete integration of the module you just have to
//	#include the "mdlEPWM_cnf.h" to you project
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

    #define mdlEPWM_CLK         DEVICE_SYSCLK_FREQ                                                      //!< EPWMCLK is SYSCLK for this device

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 1. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: Specific defines to adjust the
    //              ePWM module
    //>>

    // Valid only, if TBCLK = EPWMCLK, i.e. pre-scaler=1 and high speed pre-scaler=1!!!
    #define mdlEPWM_cnf_FB_PERIOD_TICKS       (uint16_t) (mdlEPWM_CLK/INV_cnf__FULLBRIDGE_FREQ)         // Full-bridge PWM (at current settings - 1165ticks)
    #define mdlEPWM_cnf_FB_DUTY_TICKS         (uint16_t) (0.5*mdlEPWM_CLK/INV_cnf__FULLBRIDGE_FREQ)     // 50% duty cycle (at current settings - 582 ticks)
    #define mdlEPWM_cnf_FB_DEADBAND_TICKS     (uint16_t) (mdlEPWM_CLK*350e-9)                           // Deadband = 350nsec (at current settings - 35 ticks)
//    #define mdlEPWM_cnf_FB_180DEG_PHASE_TICKS (uint16_t) (0.5*mdlEPWM_CLK/INV_cnf__FULLBRIDGE_FREQ)     // Max. phase shift - NOT USED ANYWHERE

    // Valid only, if TBCLK = EPWMCLK/2, i.e. pre-scaler=2 and high speed pre-scaler=1!!!
    #define mdlEPWM_cnf_SAMPLE_FREQ            1000.0F  // sampling frequency of ADC
    #define mdlEPWM_cnf_SAMPLE_PERIOD_TICKS   (uint16_t) (0.5*mdlEPWM_CLK/mdlEPWM_cnf_SAMPLE_FREQ)      // sampling triggers ADC
    #define mdlEPWM_cnf_SAMPLE_DUTY_TICKS     (uint16_t) (0.25*mdlEPWM_CLK/mdlEPWM_cnf_SAMPLE_FREQ)     // sampling trigger for ADC (291)

    // Enable initial software forced trip zone event
    #define mdlEPWM_cnf_TZ_FORCE_EVENT        1                                                         // 1 = force trip zones at initialization, 0 = do not force e.g. for testing

    //<<
    //<<<< 1. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------


    /*!@brief
     * List of EPWMs to be configured by the mdlEPWM module.
     */
    typedef enum mdlEPWM_cnf_EPWM
    {
        e_mdlEPWM_cnf_EPWM__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 2. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	List of time-base submodules to be configured.
    //              Enter matching settings in
    //              6. SELF-CONFIGURATION SECTION below.
    //>>

        e_mdlEPWM_cnf_EPWM__fullbridge_master,   //!< full-bridge master PWM the others are synced to
        e_mdlEPWM_cnf_EPWM__fullbridge_A,        //!< full-bridge PWM phase A
        e_mdlEPWM_cnf_EPWM__fullbridge_B,        //!< full-bridge PWM phase B
        e_mdlEPWM_cnf_EPWM__trigger_ADC,         //!< trigger ADC (ePWM3)
        e_mdlEPWM_cnf_EPWM__trigger_ADC_slow,    //!< trigger ADC (ePWM8)

    //<<
    //<<<< 2. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlEPWM_cnf_EPWM__endOfList
    }mdlEPWM_cnf_EPWM_t;


    /*!@brief
     * List of Event Triggers to be configured by the mdlEPWM module.
     */
    typedef enum mdlEPWM_cnf_ET
    {
        e_mdlEPWM_cnf_ET__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 3. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	List of event triggers (ADC SOCs or interrupts) to be configured.
    //              Enter matching settings in
    //              7. SELF-CONFIGURATION SECTION below.
    //>>

        //event trigger for ADC SOCs
        e_mdlEPWM_cnf_ET__ePWM3_SOCA_trigOnCmpA,    //!< trigger for ADC @ 85kHz
        e_mdlEPWM_cnf_ET__ePWM8_SOCA_trigOnCmpA,    //!< trigger for ADC @ 1kHz

    //<<
    //<<<< 3. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlEPWM_cnf_ET__endOfList
    }mdlEPWM_cnf_ET_t;


    /*!@brief
     * List of Digital Compares to be configured by the mdlEPWM module.
     */
    typedef enum mdlEPWM_cnf_DC
    {
        e_mdlEPWM_cnf_DC__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 4. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	List of digital compares to be configured
    //              Enter matching settings in
    //              8. SELF-CONFIGURATION SECTION below.
    //>>

        e_mdlEPWM_cnf_DC__OST_DCAEVT1_ePWM2,        //!< One-shot trip on Trip Combination Input
        e_mdlEPWM_cnf_DC__OST_DCAEVT1_ePWM7,        //!< One-shot trip on Trip Combination Input

    //<<
    //<<<< 4. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlEPWM_cnf_DC__endOfList
    }mdlEPWM_cnf_DC_t;


    /*!@brief
     * List of Trip Zones to be configured by the mdlEPWM module.
     */
    typedef enum mdlEPWM_cnf_TZ
    {
        e_mdlEPWM_cnf_TZ__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 5. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	List of trip zones to be configured
    //              Enter matching settings in
    //              9. SELF-CONFIGURATION SECTION below.
    //>>

        //trip ePWM2
        e_mdlEPWM_cnf_TZ__OST_DCAEVT1_ePWM2A,       //!< force A low on DCAEVT1 connected to Trip Combination Input
        e_mdlEPWM_cnf_TZ__OST_DCAEVT1_ePWM2B,       //!< force B low on DCAEVT1 connected to Trip Combination Input

        //trip ePWM7
        e_mdlEPWM_cnf_TZ__OST_DCAEVT1_ePWM7A,       //!< force A low on DCAEVT1 connected to Trip Combination Input
        e_mdlEPWM_cnf_TZ__OST_DCAEVT1_ePWM7B,       //!< force B low on DCAEVT1 connected to Trip Combination Input

    //<<
    //<<<< 5. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlEPWM_cnf_TZ__endOfList
    }mdlEPWM_cnf_TZ_t;


#endif /* MODULE_MDLEPWM__CONFIG_MDLEPWM_CNF_H_ */

// Macros to be used in the following configuration section
#define DISABLE_PHASE       0
#define ENABLE_PHASE        1
#define DISABLE_DEADBAND    0
#define ENABLE_DEADBAND     1

#ifdef	LOAD_EPWM_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 6. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION: Configuration of the EPWM Time-Base Submodule
    //              Refer to mdlEPWM_cfg_EPWM_t for details on each entry.
    //              Refer to mdlEPWM_cfg_TB_t for details on each entry.
    //              Refer to mdlEPWM_cfg_CC_t for details on each entry.
    //              Refer to mdlEPWM_cfg_AQ_t for details on each entry.
    //
    // IMPORTANT:   THE ORDER IS DEFINED THROUGH YOUR NAMING ORDER ABOVE.
    //              These settings are hard coded in mdlEPWM_init():
    //              - count mode = up
    //              - high speed clock pre-scaler = 1
    //              These settings are hard coded in mdlEPWM_initDeadband():
    //              - if deadband is enabled, a pair of complementary outputs will be generated from ePWMxA
    //
    // SYNTAX:      {
    //              EPWM module base,
    //              // {clk pre-scaler, period, duty cycle, sync pulse, phase shift enable, phase count, deadband enable, deadband count, blanking enable, blanking window},// this doesn't match
    //              {clk pre-scaler, period, sync pulse, phase shift enable, phase count, deadband enable, deadband count, count mode},
    //              {counter compare value A, shadow load mode A, counter compare value B, shadow load mode B},
    //              {EPWM output, actions (several may be ORed!)},
    //              },
    //
    // EXAMPLES:
    //
    //              Set up ePWM4 as a trigger for an interrupt (requires separate event trigger configuration -> see event trigger configuration below)
    //              {
    //              EPWM4_BASE,
    //              //set clk pre-scaler=4, set period, no sync pulse, disable phase loading, set phase=0, disable deadband, set deadband=0, count mode up
    //              {EPWM_CLOCK_DIVIDER_4, mdlEPWM_cnf_PWM4_PERIOD_TICKS, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE, DISABLE_PHASE, 0, DISABLE_DEADBAND, 0,EPWM_COUNTER_MODE_UP},
    //              //leave both CMPA and CMPB at zero, because these are not required
    //              {0, EPWM_COMP_LOAD_ON_CNTR_ZERO, 0, EPWM_COMP_LOAD_ON_CNTR_ZERO},
    //              //EPWM output A -> no actions
    //              {EPWM_AQ_OUTPUT_A, 0},
    //              },
    //
    //              Set up ePWM4 as a trigger for an interrupt (requires separate event trigger configuration -> see event trigger configuration below)
    //              {
    //              EPWM5_BASE,
    //              //set clk pre-scaler=4, set period, no sync pulse, disable phase loading, set phase=0, disable deadband, set deadband=0, count mode up/down
    //              {EPWM_CLOCK_DIVIDER_4, mdlEPWM_cnf_PWM5_PERIOD_TICKS, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE, DISABLE_PHASE, 0, DISABLE_DEADBAND, 0, EPWM_COUNTER_MODE_UP_DOWN},
    //              //leave both CMPA and CMPB at zero, because these are not required
    //              {0, EPWM_COMP_LOAD_ON_CNTR_ZERO, 0, EPWM_COMP_LOAD_ON_CNTR_ZERO},
    //              //EPWM output A -> no actions
    //              {EPWM_AQ_OUTPUT_A, 0},
    //              },
    //
    //>>

    // Sync master for PWM A and PWM B
    {
        EPWM1_BASE,
        //set clk pre-scaler=1, set period, generate sync pulse on counter zero, disable phase loading, set phase=0, enable deadband, set deadband
        {EPWM_CLOCK_DIVIDER_1, mdlEPWM_cnf_FB_PERIOD_TICKS, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO, DISABLE_PHASE, 0, ENABLE_DEADBAND, mdlEPWM_cnf_FB_DEADBAND_TICKS, EPWM_COUNTER_MODE_UP},
        //CMPA not used, CMPB not used
        {0, EPWM_COMP_LOAD_ON_CNTR_ZERO, 0, EPWM_COMP_LOAD_ON_CNTR_ZERO},
        //EPWM output A -> no actions
        {EPWM_AQ_OUTPUT_A, 0},
    },

    // PWM side A+/A- outputs
    {
        EPWM7_BASE,
        //set clk pre-scaler=1, set period, no sync pulse, enable phase loading, set phase=0, enable deadband, set deadband
        {EPWM_CLOCK_DIVIDER_1, mdlEPWM_cnf_FB_PERIOD_TICKS, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE, ENABLE_PHASE, 0, ENABLE_DEADBAND, mdlEPWM_cnf_FB_DEADBAND_TICKS, EPWM_COUNTER_MODE_DOWN},
        //set CMPA and load on counter=zero, CMPB not used
        {mdlEPWM_cnf_FB_DUTY_TICKS, EPWM_COMP_LOAD_ON_CNTR_ZERO, 0, EPWM_COMP_LOAD_ON_CNTR_ZERO},
        //
        // NOTE: In the inverter power board (91-S230-0183b) PWM A+ and A- are swapped in error.
        //       To correct this, output ePWM7A is configured here to low on counter == 0 and high on counter == CMPA,
        //       instead of high on counter == 0 and low on counter == CMPA
        //
        //EPWM output A high on counter == 0 and low on counter == CMPA
        {EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH_ZERO | EPWM_AQ_OUTPUT_LOW_DOWN_CMPA},
    },

    // PWM side B+/B- outputs
    {
        EPWM2_BASE,
        //set clk pre-scaler=1, set period, no sync pulse, enable phase loading, set phase=0, enable deadband, set deadband
        {EPWM_CLOCK_DIVIDER_1, mdlEPWM_cnf_FB_PERIOD_TICKS, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE, DISABLE_PHASE, 0, ENABLE_DEADBAND, mdlEPWM_cnf_FB_DEADBAND_TICKS, EPWM_COUNTER_MODE_UP},
        //set CMPA and load on counter=zero, CMPB not used
        {mdlEPWM_cnf_FB_DUTY_TICKS, EPWM_COMP_LOAD_ON_CNTR_ZERO, 0, EPWM_COMP_LOAD_ON_CNTR_ZERO},
        //EPWM output A high on counter == 0 and low on counter == CMPA
        {EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH_ZERO | EPWM_AQ_OUTPUT_LOW_UP_CMPA},
    },

    // Fast ADC trigger@fullbridge frequency: use ePWM3 which is synched to ePWM1
    {
        EPWM3_BASE,
        //set clk pre-scaler=1, set period, no sync pulse, enable phase loading, set phase=0, disable deadband, set deadband=0
        {EPWM_CLOCK_DIVIDER_1, mdlEPWM_cnf_FB_PERIOD_TICKS/2, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE, ENABLE_PHASE, 0, DISABLE_DEADBAND, 0, EPWM_COUNTER_MODE_UP},
        //set CMPA and load on counter=zero, CMPB not used
        {0, EPWM_COMP_LOAD_ON_CNTR_ZERO, 0, EPWM_COMP_LOAD_ON_CNTR_ZERO},
#ifdef DEBUG
        //set output (DIO11) for debugging
        {EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH_ZERO | EPWM_AQ_OUTPUT_LOW_UP_CMPA},
#else
        //EPWM output A -> no actions
        {EPWM_AQ_OUTPUT_A, 0},
#endif
    },

    // Slow ADC trigger: use ePWM8
    {
        EPWM8_BASE,
        //set clk pre-scaler=2, set period, no sync pulse, disable phase loading, set phase=0, disable deadband, set deadband=0
        {EPWM_CLOCK_DIVIDER_2, mdlEPWM_cnf_SAMPLE_PERIOD_TICKS, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE, DISABLE_PHASE, 0, DISABLE_DEADBAND, 0, EPWM_COUNTER_MODE_UP},
        //set CMPA and load on counter=zero, CMPB not used
        {mdlEPWM_cnf_SAMPLE_DUTY_TICKS, EPWM_COMP_LOAD_ON_CNTR_ZERO, 0, EPWM_COMP_LOAD_ON_CNTR_ZERO},
#ifdef DEBUG
        //set output (DIO9) for debugging
        {EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH_ZERO | EPWM_AQ_OUTPUT_LOW_UP_CMPA},
#else
        //EPWM output A -> no actions
        {EPWM_AQ_OUTPUT_A, 0},
#endif
    },

    //<<
    //<<<< 6. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif


// Macros to be used in the following configuration section
#define EPWM_INT 0xFF

#ifdef	LOAD_EVENT_TRIGGER_CONFIGURATION


    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 7. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	Configuration of the EPWM Event-Trigger Submodule.
    //              This submodule can provide triggers for the ADC conversions, i.e. SOCs
    //              (set type to EPWM_SOC_A or EPWM_SOC_B) or alternatively generate
    //              interrupts (set type=EPWM_INT).
    //              Refer to mdlEPWM_cfg_ET_t for details on each entry.
    //
    // IMPORTANT:   THE ORDER IS DEFINED THROUGH YOUR
    //              NAMING ORDER ABOVE.
    //
    // SYNTAX:      {EPWM module base, type (EPWM_SOC_A/B or EPWM_INT), trigger source, number of events before trigger, enable flag},
    //
    // EXAMPLES:
    //
    //              Set up ePWM4 to trigger an interrupt (requires separate PWM configuration -> see above)
    //              Trigger interrupt, if counter=0 for the 1st time
    //              {EPWM4_BASE, EPWM_INT, EPWM_INT_TBCTR_ZERO, 1, 1},
    //
    //              Set up ePWM5 to trigger an interrupt (requires separate PWM configuration -> see above)
    //              Trigger interrupt, if counter=0 for the 1st time, interrupt not enabled during initialization
    //              Interrupt must be enabled elsewhere!
    //              {EPWM5_BASE, EPWM_INT, EPWM_INT_TBCTR_ZERO, 1, 0},
    //>>

    //
    // Triggers for ADC SOCs
    //
    // Trigger SOCA, if counting up and counter=CMPA for the 1st time
    {EPWM3_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA, 1, 1},
    // Trigger SOCA, if counting up and counter=CMPA for the 1st time
    {EPWM8_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA, 1, 1},

    //<<
    //<<<< 7. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif


#ifdef	LOAD_DIGITAL_COMPARE_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 8. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION: Configuration of the EPWM Digital-Compare Submodule
    //              Refer to mdlEPWM_cfg_DC_t for details on each entry.
    //
    // IMPORTANT:   THE ORDER IS DEFINED THROUGH YOUR
    //              NAMING ORDER ABOVE.
    //
    // SYNTAX:      {EPWM module base, trip source, {list of up to 5 combination trip inputs (ignored if trip source is not the combination input!)},
    //               type, event, event source, blanking window length (if filt. signal is used)},
    //
    //>>

    // Trip combination input shall One-Shot trip PWM outputs 2 to low -> requires configuration of Trip Zone submodule (see below)
    // Select EPWM_DC_TRIP_COMBINATION as input and specify inputs to trip combination input
    {EPWM2_BASE, EPWM_DC_TRIP_COMBINATION, {EPWM_DC_COMBINATIONAL_TRIPIN4, EPWM_DC_COMBINATIONAL_TRIPIN5, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_COMBINATIONAL_TRIPIN8, EPWM_DC_COMBINATIONAL_TRIPIN9, EPWM_DC_COMBINATIONAL_TRIPIN10},
    // for DCAH input, generate digital compare event 1 (DCAEVT1=one-shot), use unfiltered version, event to cause trip zone
     EPWM_DC_TYPE_DCAH, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL, 0, EPWM_TZ_EVENT_DCXH_HIGH},

    // Trip combination input shall One-Shot trip PWM output 7 to low -> requires configuration of Trip Zone submodule (see below)
    // Select EPWM_DC_TRIP_COMBINATION as input and specify inputs to trip combination input
    {EPWM7_BASE, EPWM_DC_TRIP_COMBINATION, {EPWM_DC_COMBINATIONAL_TRIPIN4, EPWM_DC_COMBINATIONAL_TRIPIN5, EPWM_DC_COMBINATIONAL_TRIPIN7, EPWM_DC_COMBINATIONAL_TRIPIN8, EPWM_DC_COMBINATIONAL_TRIPIN9, EPWM_DC_COMBINATIONAL_TRIPIN10},
    // for DCAH input, generate digital compare event 1 (DCAEVT1=one-shot), use unfiltered version, event to cause trip zone
     EPWM_DC_TYPE_DCAH, EPWM_DC_EVENT_1, EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL, 0, EPWM_TZ_EVENT_DCXH_HIGH},

    //<<
    //<<<< 8. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif


#ifdef	LOAD_TRIP_ZONE_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 9. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION: Configuration of the EPWM Trip-Zone Submodule
    //              Refer to mdlEPWM_cfg_TZ_t for details on each entry.
    //
    // IMPORTANT:   THE ORDER IS DEFINED THROUGH YOUR
    //              NAMING ORDER ABOVE.
    //
    // SYNTAX:      {EPWM module base, trip zone signal (several may be ORed), trip zone event, trip zone action, event to force during initialization},
    //              When ORing signals:
    //              - never mix the arguments of EPWM_getOneShotTripZoneFlagStatus() and EPWM_getCycleByCycleTripZoneFlagStatus()!
    //              - mdlEPWM_isTripZoneFlagged() can only test for the ORed signals
    //
    // EXAMLES:     One-shot trip ePWM1A on TZ1, set TZ1 to TZ6, DCAEVT1/2, DCBEVT1/2 Trip Action for A to "force output low", force trip at initialization
    //              {EPWM1_BASE, EPWM_TZ_SIGNAL_OSHT1, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW, EPWM_TZ_FORCE_EVENT_OST},
    //
    //              Cycle-by-cycle trip ePWM 7 on Digital Compare Output A Event 2 Action, set TZ1 to TZ6, DCAEVT1/2, DCBEVT1/2 Trip Action for A to "force output low"
    //              {EPWM7_BASE, EPWM_TZ_SIGNAL_DCAEVT2,  EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW, EPWM_TZ_FORCE_EVENT_CBC},
    //
    //              One-shot trip ePWM1B on TZ1 or TZ2, set TZ1 to TZ6, DCAEVT1/2, DCBEVT1/2 Trip Action for B to "force output low", do not force trip at initialization
    //              {EPWM1_BASE, (EPWM_TZ_SIGNAL_OSHT1|EPWM_TZ_SIGNAL_OSHT2), EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW, 0},
    //
    // NOTE:        Valid Trip Zone Signal are:
    //              - EPWM_TZ_SIGNAL_CBC1       - TZ1 Cycle By Cycle
    //              - EPWM_TZ_SIGNAL_CBC2       - TZ2 Cycle By Cycle
    //              - EPWM_TZ_SIGNAL_CBC3       - TZ3 Cycle By Cycle
    //              - EPWM_TZ_SIGNAL_CBC4       - TZ4 Cycle By Cycle
    //              - EPWM_TZ_SIGNAL_CBC5       - TZ5 Cycle By Cycle
    //              - EPWM_TZ_SIGNAL_CBC6       - TZ6 Cycle By Cycle
    //              - EPWM_TZ_SIGNAL_DCAEVT2    - DCAEVT2 Cycle By Cycle
    //              - EPWM_TZ_SIGNAL_DCBEVT2    - DCBEVT2 Cycle By Cycle
    //              - EPWM_TZ_SIGNAL_OSHT1      - One-shot TZ1
    //              - EPWM_TZ_SIGNAL_OSHT2      - One-shot TZ2
    //              - EPWM_TZ_SIGNAL_OSHT3      - One-shot TZ3
    //              - EPWM_TZ_SIGNAL_OSHT4      - One-shot TZ4
    //              - EPWM_TZ_SIGNAL_OSHT5      - One-shot TZ5
    //              - EPWM_TZ_SIGNAL_OSHT6      - One-shot TZ6
    //              - EPWM_TZ_SIGNAL_DCAEVT1    - One-shot DCAEVT1
    //              - EPWM_TZ_SIGNAL_DCBEVT1    - One-shot DCBEVT1
    //
    //              If several trip zone signals are ORed, mdlEPWM_isTripZoneFlagged() will return true, if any signal is present.
    //              Therefore use a single signal for each trip zone, if you want to be able to differentiate between trip signals.
    //              Function mdlEPWM_clearTripZoneFlags() will try to to clear all flags for the specified signals.
    //>>

    // Trip Combination Input shall one-shot trip ePWM2 outputs -> requires configuration of Digital Compare submodule (see above)
    // One-shot trip ePWM2A on DCAEVT1, set TZ1 to TZ6, DCAEVT1/2, DCBEVT1/2 Trip Action for A to "force output low", trip at initialization
    {EPWM2_BASE, EPWM_TZ_SIGNAL_DCAEVT1, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW, EPWM_TZ_FORCE_EVENT_OST},
    // One-shot trip ePWM2B on DCAEVT1, set TZ1 to TZ6, DCAEVT1/2, DCBEVT1/2 Trip Action for A to "force output low", trip at initialization
    {EPWM2_BASE, EPWM_TZ_SIGNAL_DCAEVT1, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW, EPWM_TZ_FORCE_EVENT_OST},

    // Trip Combination Input shall one-shot trip ePWM7 outputs -> requires configuration of Digital Compare submodule (see above)
    // One-shot trip ePWM7A on DCAEVT1, set TZ1 to TZ6, DCAEVT1/2, DCBEVT1/2 Trip Action for A to "force output low", trip at initialization
    {EPWM7_BASE, EPWM_TZ_SIGNAL_DCAEVT1, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW, EPWM_TZ_FORCE_EVENT_OST},
    // One-shot trip ePWM7B on DCAEVT1, set TZ1 to TZ6, DCAEVT1/2, DCBEVT1/2 Trip Action for A to "force output low", trip at initialization
    {EPWM7_BASE, EPWM_TZ_SIGNAL_DCAEVT1, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW, EPWM_TZ_FORCE_EVENT_OST},

    //<<
    //<<<< 9. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//		MODULE CONFIGURATION	- END
//==============================================================================

/** @}*/

