/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file mdlEPWM.c @copyright
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
/*!@file            mdlEPWM.c
 * @brief           Initializes ePWM module and its submodule according to the
 *                  settings in file mdlEPWM_cnf.h
 *//*
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes
#include "device.h"
#include "mdlEPWM.h"


//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

static mdlEPWM_cfg_EPWM_t cfg[e_mdlEPWM_cnf_EPWM__endOfList] = {
#define LOAD_EPWM_CONFIGURATION
    #include "./_config/mdlEPWM_cnf.h"
#undef  LOAD_EPWM_CONFIGURATION
};


static mdlEPWM_cfg_ET_t et[e_mdlEPWM_cnf_ET__endOfList] = {
#define LOAD_EVENT_TRIGGER_CONFIGURATION
    #include "./_config/mdlEPWM_cnf.h"
#undef  LOAD_EVENT_TRIGGER_CONFIGURATION
};


static mdlEPWM_cfg_TZ_t tz[e_mdlEPWM_cnf_TZ__endOfList] = {
#define LOAD_TRIP_ZONE_CONFIGURATION
    #include "./_config/mdlEPWM_cnf.h"
#undef  LOAD_TRIP_ZONE_CONFIGURATION
};


static mdlEPWM_cfg_DC_t dc[e_mdlEPWM_cnf_DC__endOfList] = {
#define LOAD_DIGITAL_COMPARE_CONFIGURATION
    #include "./_config/mdlEPWM_cnf.h"
#undef  LOAD_DIGITAL_COMPARE_CONFIGURATION
};

const uint16_t combi[] = {EPWM_DC_COMBINATIONAL_TRIPIN5,
                          EPWM_DC_COMBINATIONAL_TRIPIN7,
                          EPWM_DC_COMBINATIONAL_TRIPIN8,
                          EPWM_DC_COMBINATIONAL_TRIPIN9,
                          EPWM_DC_COMBINATIONAL_TRIPIN10};

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

    //-------------------------
    // Private Predeclaration
    //*************************

void mdlEPWM_initDeadband(mdlEPWM_cnf_EPWM_t thisEPWM);
void mdlEPWM_initEventTriggers(void);
void mdlEPWM_initDigitalCompare(void);

    //-------------------------
    // Public Section
    //*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Initialize EPWM conversions (SOCs) and EPWM modules needed.
 *
 *@ref      mdlEPWM_cfg_EPWM_t
 *@ref      mdlEPWM_cnf.h
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variables soc[] and cfg[].
 *          Each EPWM module will only be initialized only once and only if used.
 *\n
 */
void mdlEPWM_init(void)
{
    uint8_t i;

    // Initialize ePWM Digital Compare submodule
    mdlEPWM_initDigitalCompare();


    // For each configured EPWM
    for(i = 0; i < e_mdlEPWM_cnf_EPWM__endOfList; i++)
    {
        //////////////////////////////////////
        // Setup time base counter submodule
        //////////////////////////////////////

        // Set time base counter mode to up
        EPWM_setTimeBaseCounterMode(cfg[i].base, cfg[i].tb.countMode);

        // Set period
        EPWM_setPeriodLoadMode(cfg[i].base, EPWM_PERIOD_SHADOW_LOAD);   //shadow load is the default
        EPWM_setTimeBasePeriod(cfg[i].base, cfg[i].tb.period);

        // Set the time base clock pre-scalers
        EPWM_setClockPrescaler(cfg[i].base, cfg[i].tb.clkPrescale, EPWM_HSCLOCK_DIVIDER_1);

        if(cfg[i].tb.enablePhaseLoading)
        {
            // Enable loading of phase shift on sync event
            EPWM_enablePhaseShiftLoad(cfg[i].base);
            // Set phase
            EPWM_setPhaseShift(cfg[i].base, cfg[i].tb.phaseCount);
        }
        else
        {
            // Disable loading of phase shift on sync event
            EPWM_disablePhaseShiftLoad(cfg[i].base);
        }

        // Set the sync out pulse mode
        EPWM_setSyncOutPulseMode(cfg[i].base, cfg[i].tb.syncOutMode);

        // Clear counter
        EPWM_setTimeBaseCounter(cfg[i].base, 0);


        //////////////////////////////////////
        // Setup counter compare submodule
        // Currently only CMPA and CMPB are set
        // up and CMPC and CMPD are not.
        //////////////////////////////////////

        // Set the counter compare values for A and B
        EPWM_setCounterCompareValue(cfg[i].base, EPWM_COUNTER_COMPARE_A, cfg[i].cc.dutyCycleA);
        EPWM_setCounterCompareValue(cfg[i].base, EPWM_COUNTER_COMPARE_B, cfg[i].cc.dutyCycleB);

        // Set the Counter Compare shadow load modes for A and B
        // Sets up register CMPCTL (enables shadow mode and selects specified shadow load mode)
        EPWM_setCounterCompareShadowLoadMode(cfg[i].base, EPWM_COUNTER_COMPARE_A, cfg[i].cc.loadModeA);
        EPWM_setCounterCompareShadowLoadMode(cfg[i].base, EPWM_COUNTER_COMPARE_B, cfg[i].cc.loadModeB);


        //////////////////////////////////////
        // Setup action qualifier submodule
        //////////////////////////////////////

        EPWM_setActionQualifierActionComplete(cfg[i].base, cfg[i].aq.epwmOutput, cfg[i].aq.actions);


        //////////////////////////////////////
        // Setup deadband submodule
        //////////////////////////////////////

        if(cfg[i].tb.enableDeadband)
        {
            mdlEPWM_initDeadband((mdlEPWM_cnf_EPWM_t) i);
        }
        else
        {
            // Freeze loading from shadow register
            EPWM_setDeadBandControlShadowLoadMode(cfg[i].base, EPWM_DB_LOAD_FREEZE);
        }

    } // end for


    //////////////////////////////////////
    // Setup ePWM event trigger submodule
    //////////////////////////////////////

    mdlEPWM_initEventTriggers();

}

    //-------------------------
    // Private Section
    //*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Initialize EPWM Event Triggers.
 *
 *@ref      mdlEPWM_cfg_ET_t
 *@ref      mdlEPWM_cnf.h
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variable et[].
 *\n
 */
void mdlEPWM_initEventTriggers(void)
{
    uint8_t i;

    // For each configured Event Trigger
    for(i = 0; i < e_mdlEPWM_cnf_ET__endOfList; i++)
    {
        //////////////////////////////////////
        // Setup event triggers
        //////////////////////////////////////

        if(EPWM_SOC_A == et[i].adcSOCType || EPWM_SOC_B == et[i].adcSOCType )
        {
            //
            // Configure the ADC SOC trigger as specified and enable it
            // See self configuration section 7. in file mdlEPWM_cnf.h
            // Setup ETPS and ETSOCPS registers
            EPWM_setADCTriggerEventPrescale(et[i].base, (EPWM_ADCStartOfConversionType) et[i].adcSOCType, et[i].eventCount);
            // Setup ETSEL register
            EPWM_setADCTriggerSource(et[i].base, (EPWM_ADCStartOfConversionType) et[i].adcSOCType, (EPWM_ADCStartOfConversionSource) et[i].socSource);
            if(et[i].enable)
            {
                EPWM_enableADCTrigger(et[i].base, (EPWM_ADCStartOfConversionType) et[i].adcSOCType);
            }
        }
        else
        {
            EPWM_setInterruptEventCount(et[i].base, et[i].eventCount);
            EPWM_setInterruptSource(et[i].base, (uint16_t) et[i].socSource);
            if(et[i].enable)
            {
                EPWM_enableInterrupt(et[i].base);
            }
        }
    } // end for
}

//------------------------------------------------------------------------------------------------
/*!@brief   Initialize EPWM Trip Zones.
 *
 *@ref      mdlEPWM_cfg_TZ_t
 *@ref      mdlEPWM_cnf.h
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variable tz[].
 *\n
 */
void mdlEPWM_initTripZones(void)
{
    uint8_t i;


    // For each configured Trip Zone
    for(i = 0; i < e_mdlEPWM_cnf_TZ__endOfList; i++)
    {

        // Set outputs A and B low on digital compare A event 1
        // Sets the TZCTL register.
        EPWM_setTripZoneAction(tz[i].base, tz[i].tzEvent, tz[i].tzAction);

        // Enable specified Trip Zone signal as a source for the Trip Zone module.
        // Sets the TZSEL register.
        EPWM_enableTripZoneSignals(tz[i].base, tz[i].tzSignal);

#if (1 == mdlEPWM_cnf_TZ_FORCE_EVENT)
        // Force specified trip event now
        EPWM_forceTripZoneEvent(tz[i].base, tz[i].tzForceEvent);
#endif

    } // end for
}


//------------------------------------------------------------------------------------------------
/*!@brief   Initialize EPWM Digital Compare Submodule.
 *
 *@ref      mdlEPWM_cfg_DC_t
 *@ref      mdlEPWM_cnf.h
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variable dc[].
 *\n
 */
void mdlEPWM_initDigitalCompare(void)
{
    uint8_t i, j;
    EPWM_DigitalCompareModule dcModule;
    EPWM_DigitalCompareFilterInput dcFilterInput;
    EPWM_TripZoneDigitalCompareOutput dcTripType;

    // For each configured digital compare
    for(i = 0; i < e_mdlEPWM_cnf_DC__endOfList; i++)
    {

        // determine dcModule, dcFilterInput and dcTripType from dcType and dcEvent settings
        // dcType = EPWM_DC_TYPE_DCAL || EPWM_DC_TYPE_DCAH -> module A
        // dcType = EPWM_DC_TYPE_DCBL || EPWM_DC_TYPE_DCBH -> module B
        if((EPWM_DC_TYPE_DCAL == dc[i].dcType) || (EPWM_DC_TYPE_DCAH == dc[i].dcType))
        {
            // determine filter input from dcType setting
            dcModule = EPWM_DC_MODULE_A;                        // Set module to match type
            if(EPWM_DC_EVENT_1 == dc[i].dcEvent)
            {
                dcFilterInput = EPWM_DC_WINDOW_SOURCE_DCAEVT1;  // Set filter input to match type and event
                dcTripType = EPWM_TZ_DC_OUTPUT_A1;              // Set type to match type and event
            }
            else
            {
                dcFilterInput = EPWM_DC_WINDOW_SOURCE_DCAEVT2;  // Set filter input to match type and event
                dcTripType = EPWM_TZ_DC_OUTPUT_A2;              // Set type to match type and event
            }
        }
        else
        {
            dcModule = EPWM_DC_MODULE_B;                        // Set module to match type
            if(EPWM_DC_EVENT_1 == dc[i].dcEvent)
            {
                dcFilterInput = EPWM_DC_WINDOW_SOURCE_DCBEVT1;  // Set filter input to match type and event
                dcTripType = EPWM_TZ_DC_OUTPUT_B1;              // Set type to match type and event
            }
            else
            {
                dcFilterInput = EPWM_DC_WINDOW_SOURCE_DCBEVT2;  // Set filter input to match type and event
                dcTripType = EPWM_TZ_DC_OUTPUT_B2;              // Set type to match type and event
            }
        }

        //
        // If trip source is Trip Combination Input, enable configured signals now
        //
        if(EPWM_DC_TRIP_COMBINATION == dc[i].tripSource)
        {
            for(j = 0; j < sizeof(dc[i].combinationSource); ++j)
            {
                EPWM_enableDigitalCompareTripCombinationInput(dc[i].base, dc[i].combinationSource[j], dc[i].dcType);
            }
        }

        // Set the trip input (one of 15) to the submodules digital compare types (one of 4)
        // Set DCTRIPSEL register
        EPWM_selectDigitalCompareTripInput(dc[i].base, dc[i].tripSource, dc[i].dcType);

        // Set up the output (A1, A2, B1 or B2) and the event condition
        // Sets TZDCSEL register
        EPWM_setTripZoneDigitalCompareEventCondition(dc[i].base, dcTripType, dc[i].dcTripEvent);

        // Select filtered or unfiltered version of event
        EPWM_setDigitalCompareEventSource(dc[i].base, dcModule, dc[i].dcEvent, dc[i].dcEventSource);


        // Setup blanking filter, if filtered event source is selected
        if(EPWM_DC_EVENT_SOURCE_FILT_SIGNAL == dc[i].dcEventSource)
        {
            // Blanking window not inverted is the default
//            EPWM_disableDigitalCompareWindowInverseMode(cfg[i].base);
            // Time-base counter equal to period is the default
//            EPWM_setDigitalCompareBlankingEvent(cfg[i].base, EPWM_DC_WINDOW_START_TBCTR_PERIOD);
            // Set offset count, zero is the default
//            EPWM_setDigitalCompareWindowOffset(cfg[i].base, 0);

            // Set source
            EPWM_setDigitalCompareFilterInput(dc[i].base, dcFilterInput);
            // Enable blanking
            EPWM_enableDigitalCompareBlankingWindow(dc[i].base);
            // Set blanking window length
            EPWM_setDigitalCompareWindowLength(dc[i].base, dc[i].windowCount);
        }

        // Default to asynchronous mode (i.e. not synched to TBCLK)
        EPWM_setDigitalCompareEventSyncMode(dc[i].base, dcModule, dc[i].dcEvent, EPWM_DC_EVENT_INPUT_NOT_SYNCED);

    } // end for
}


//------------------------------------------------------------------------------------------------
/*!@brief   Initialize EPWM module deadband settings
 *
 *@ref      mdlEPWM_cfg_EPWM_t
 *@ref      mdlEPWM_cnf.h
 *
 *@param    thisEPWM    : number of EPWM module
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into static variable cfg[].
 *
 *\n
 */

void mdlEPWM_initDeadband(mdlEPWM_cnf_EPWM_t thisEPWM)
{

    // Use EPWMA as the input for both RED and FED
    //
    EPWM_setRisingEdgeDeadBandDelayInput(cfg[thisEPWM].base, EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(cfg[thisEPWM].base, EPWM_DB_INPUT_EPWMA);

    //
    // Set the RED and FED values
    //
    EPWM_setFallingEdgeDelayCount(cfg[thisEPWM].base, cfg[thisEPWM].tb.deadbandCount);
    EPWM_setRisingEdgeDelayCount(cfg[thisEPWM].base, cfg[thisEPWM].tb.deadbandCount);

    // Do not invert the Rising Edge delayed output
    EPWM_setDeadBandDelayPolarity(cfg[thisEPWM].base, EPWM_DB_RED, EPWM_DB_POLARITY_ACTIVE_HIGH);
    // Invert the Falling Edge delayed output
    EPWM_setDeadBandDelayPolarity(cfg[thisEPWM].base, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);

    //
    // Use the delayed signals instead of the original signals
    //
    EPWM_setDeadBandDelayMode(cfg[thisEPWM].base, EPWM_DB_RED, true);
    EPWM_setDeadBandDelayMode(cfg[thisEPWM].base, EPWM_DB_FED, true);

    //
    // DO NOT Swap Output A with Output B
    //
    EPWM_setDeadBandOutputSwapMode(cfg[thisEPWM].base, EPWM_DB_OUTPUT_A, false);
    EPWM_setDeadBandOutputSwapMode(cfg[thisEPWM].base, EPWM_DB_OUTPUT_B, false);

}


//------------------------------------------------------------------------------------------------
/*!@brief   Force Trip Zone event.
 *
 *@ref      mdlEPWM_cfg_TZ_t
 *@ref      mdlEPWM_cnf.h
 *
 *@param    thisTZ    : number of Trip Zone
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into static variable tz[].
 *
 *\n
 */

void mdlEPWM_forceTripZone(mdlEPWM_cnf_TZ_t thisTZ)
{

    // Force specified trip event
    EPWM_forceTripZoneEvent(tz[thisTZ].base, tz[thisTZ].tzForceEvent);

}


//------------------------------------------------------------------------------------------------
/*!@brief   Get Trip Zone status.
 *
 *@ref      mdlEPWM_cfg_TZ_t
 *@ref      mdlEPWM_cnf.h
 *
 *@param    thisTZ    : number of specified Trip Zone
 *
 *@return   true = one or more trip signals are flagged, false = nothing flagged or no matching flags
 *\n
 *@note     Uses the configuration loaded from the config header file into static variable tz[].
 *          A trip zone forced by software, will only set flags of register TZFLG but not of registers
 *          TZOSTFLG / TZCBCFLG. However, this function will check the individual flags in the
 *          latter registers and thus return false in case of a software forced trip.
 *
 *\n
 */

bool mdlEPWM_isTripZoneFlagged(mdlEPWM_cnf_TZ_t thisTZ)
{
    uint16_t tz_flags;

    // If any cycle-by-cycle signal has been specified for this trip zone, check the CBC flags
    if(tz[thisTZ].tzSignal & 0x00FF)
    {
        // Get flag status from register TZCBCFLG of specific ePWM module
        tz_flags = EPWM_getCycleByCycleTripZoneFlagStatus(tz[thisTZ].base);

        // If any of the specified trip zone signal(s) matches current flag(s), return true
        if(tz_flags & tz[thisTZ].tzSignal)
        {
            return true;
        }
    }

    // If any one-shot signal has been specified for this trip zone, check the OST flags
    if(tz[thisTZ].tzSignal & 0xFF00)
    {
        // Get flag status from register TZOSTFLG of specific ePWM module and align
        tz_flags = EPWM_getOneShotTripZoneFlagStatus(tz[thisTZ].base);
        tz_flags <<= 8U;

        // If any of the specified trip zone signal(s) matches current flag(s), return true
        if(tz_flags & tz[thisTZ].tzSignal)
        {
            return true;
        }
    }

    return false;

}


//------------------------------------------------------------------------------------------------
/*!@brief   Clear Trip Zone event flags.
 *
 *@ref      mdlEPWM_cfg_TZ_t
 *@ref      mdlEPWM_cnf.h
 *
 *@param    thisTZ    : number of Trip Zone
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into static variable tz[].
 *
 *\n
 */

void mdlEPWM_clearTripZoneFlags(mdlEPWM_cnf_TZ_t thisTZ)
{

    uint16_t flags_to_clear = 0U;

    // If any cycle-by-cycle signal has been specified for this trip zone, clear the following flags
    if(tz[thisTZ].tzSignal & 0x00FF)
    {
        flags_to_clear |= EPWM_TZ_FLAG_CBC;

        // If DCAEVT2 was specified, clear it additionally
        if(tz[thisTZ].tzSignal & EPWM_TZ_SIGNAL_DCAEVT2)
        {
            flags_to_clear |= EPWM_TZ_FLAG_DCAEVT2;
        }
        // If DCBEVT2 was specified, clear it additionally
        if(tz[thisTZ].tzSignal & EPWM_TZ_SIGNAL_DCBEVT2)
        {
            flags_to_clear |= EPWM_TZ_FLAG_DCBEVT2;
        }

        // Clear specified trip flag(s) in register TZCBCFLG
        EPWM_clearCycleByCycleTripZoneFlag(tz[thisTZ].base, tz[thisTZ].tzSignal);
    }

    // If any one-shot signal has been specified for this trip zone, clear the following flags
    if(tz[thisTZ].tzSignal & 0xFF00)
    {
        flags_to_clear |= EPWM_TZ_FLAG_OST;

        // If DCAEVT1 was specified, clear it additionally
        if(tz[thisTZ].tzSignal & EPWM_TZ_SIGNAL_DCAEVT1)
        {
            flags_to_clear |= EPWM_TZ_FLAG_DCAEVT1;
        }
        // If DCBEVT1 was specified, clear it additionally
        if(tz[thisTZ].tzSignal & EPWM_TZ_SIGNAL_DCBEVT1)
        {
            flags_to_clear |= EPWM_TZ_FLAG_DCBEVT1;
        }

        // Clear specified flag(s) in register TZOSTFLG
        EPWM_clearOneShotTripZoneFlag(tz[thisTZ].base, (tz[thisTZ].tzSignal >> 8U));
    }

    // Try to clear the selected flag(s) in register TZFLG
    EPWM_clearTripZoneFlag(tz[thisTZ].base, flags_to_clear);

}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCTION SECTION - END
//=============================================================================


/******************************************************************************
 * THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 * UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 * MAY LEAD TO PROSECUTION.
 *****************************************************************************/

/** @}*/

