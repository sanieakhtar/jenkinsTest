/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file mdlCMPSS.c @copyright
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
/*!@file            mdlCMPSS.c
 * @brief           Configure comparators of the analog subsystem.
 *//*
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/


/*****************************************************************************/
/*! \addtogroup mdlCMPSS Comparators
 *@brief  Configure on-chip comparators
 *
 *  This module provides functions to configure the comparators of the
 *  analog subsystem.
 *  @{
 *****************************************************************************/


//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes
#include "device.h"
#include "mdlCMPSS.h"

//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

static mdlCMPSS_cfg_CMPSS_t cfg[e_mdlCMPSS_cnf_CMPSS__endOfList] = {
#define LOAD_CMPSS_CONFIGURATION
    #include "./_config/mdlCMPSS_cnf.h"
#undef  LOAD_CMPSS_CONFIGURATION
};

static bool enbdisCfg[e_mdlCMPSS_cnf_CMPSS__endOfList] = {true,true,true,true,true,false,false}; //,true,true,true};
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

void mdlCMPSS_initCMPMux(void);
    //-------------------------
    // Public Section
    //*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Initialize configured CMPSS modules.
 *
 *@ref      mdlCMPSS_cfg_CMPSS_t
 *@ref      mdlCMPSS_cnf.h
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variable cfg[].
 *@note     In operation mode development some of the trips will be not be triggered. [?]
 *\n
 */
void mdlCMPSS_init(void)
{

    uint8_t i = 0;

    mdlCMPSS_initCMPMux();
    // For each configured CMPSS
    for(i = 0; i < e_mdlCMPSS_cnf_CMPSS__endOfList; i++)
    {
        // Check the arguments
        ASSERT((cfg[i].comparator == e_mdlCMPSS__comparator_COMPH) || (cfg[i].comparator == e_mdlCMPSS__comparator_COMPL));

        // Enable the CMPSS module
        //
        CMPSS_enableModule(cfg[i].base);

        //
        // Configure the selected comparator:
        // - source for negative input (i.e. internal DAC or external pin)
        // - inverted or not inverted output
        //
        if(e_mdlCMPSS__comparator_COMPH == cfg[i].comparator)
        {
            CMPSS_configHighComparator(cfg[i].base, cfg[i].config);
        }
        else
        {
            CMPSS_configLowComparator(cfg[i].base, cfg[i].config);
        }

        // If input is not external pin, configure DAC
        if(!(cfg[i].config & CMPSS_INSRC_PIN))
        {
            //
            // Set the configuration for the internal comparator DAC.
            // The following settings may be ORed:
            // - VDDA / VDAC = the voltage reference
            // - value register loaded from shadow register on system clock / PWM sync
            // - DAC value source is the user programmed shadow register (DACVALS) / the ramp generator register (RAMPSTS)
            // Use VDDA as the reference for the DAC and set DAC value to configured value.
            //
            CMPSS_configDAC(cfg[i].base, CMPSS_DACREF_VDDA | CMPSS_DACVAL_SYSCLK | cfg[i].DACsource);
            if(e_mdlCMPSS__comparator_COMPH == cfg[i].comparator)
            {
//                CMPSS_setDACValueHigh(cfg[i].base, cfg[i].DACinitValue);
                CMPSS_setDACValueHigh(cfg[i].base, mdlCMPSS_DACinitValue(cfg[i].tripLimit, cfg[i].gain));
            }
            else
            {
//                CMPSS_setDACValueLow(cfg[i].base, cfg[i].DACinitValue);
                CMPSS_setDACValueLow(cfg[i].base, mdlCMPSS_DACinitValue(cfg[i].tripLimit, cfg[i].gain));
            }
        }


        // Set comparator hysteresis
        CMPSS_setHysteresis(cfg[i].base, mdlCMPSS_cnf_CMP_HYSTERESIS);


        // If COMPH, complete configuration for it
        if(e_mdlCMPSS__comparator_COMPH == cfg[i].comparator)
        {
            // If the DAC value is determined by the ramp generator, configure ramp generator
            // Only available for comarator COMPH!
            if(CMPSS_DACSRC_RAMP == cfg[i].DACsource)
            {
                //
                // Configure ramp generator for slope compensation.
                // Settings are:
                // - ramp maximum reference value.
                // - ramp decrement value (value to be subtracted each system clock cycle)
                // - ramp delay in system clock cycles (13-bit)
                // - number of the PWMSYNC source to reset the ramp generator (e.g. 2=PWMSYNC2)
                // - 1=load directly from max ramp shadow RAMPMAXREFS or 0=load from latched value in reg. RAMPMAXREFA
                CMPSS_configRamp(cfg[i].base, mdlCMPSS_cnf_SLOPE_MAX, cfg[i].decrementVal, mdlCMPSS_cnf_SLOPE_DELAY, cfg[i].pwmSyncSrc, true);
            }

            // If filter output is used, configure filter
            if((CMPSS_TRIP_FILTER | CMPSS_TRIP_LATCH |
                CMPSS_TRIPOUT_FILTER | CMPSS_TRIPOUT_LATCH) & cfg[i].outputs)
            {
                //
                // Configure digital filter. Parameters for this function are:
                // - clock pre-scale (0..1023). The actual pre-scale used is 1 more than this value!
                // - sample window size (0..32)
                // - threshold (window/2 .. window-1) The actual threshold used is 1 more than this value!
                //
                // Subtract one of clock pre-scale and threshold to match function parameters
                CMPSS_configFilterHigh(cfg[i].base, cfg[i].samplePrescale-1, cfg[i].sampleWindow, cfg[i].threshold-1);

                //
                // Initialize the filter logic and start filtering
                //
                CMPSS_initFilterHigh(cfg[i].base);
            }

            //
            // Clear the latch output
            //
            CMPSS_clearFilterLatchHigh(cfg[i].base);

            //
            // Configure the output signals CTRIP (to CMPSS X-Bar) and CTRIPOUT (to output X-Bar).
            // Function parameter is a logical OR of CMPSS_TRIPOUT_xxx and CMPSS_TRIP_xxx values.
            // Available are:
            // - CMPSS_TRIPXXX_ASYNC_COMP - The asynchronous comparator output.
            // - CMPSS_TRIPXXX_SYNC_COMP - The synchronous comparator output.
            // - CMPSS_TRIPXXX_FILTER - The output of the digital filter.
            // - CMPSS_TRIPXXX_LATCH - The latched output of the digital filter.
            CMPSS_configOutputsHigh(cfg[i].base, cfg[i].outputs);

        }

        // If COMPL, complete configuration for it
        else
        {
            // If filter output is used, configure filter
            if((CMPSS_TRIP_FILTER | CMPSS_TRIP_LATCH |
                CMPSS_TRIPOUT_FILTER | CMPSS_TRIPOUT_LATCH) & cfg[i].outputs)
            {
                //
                // Configure digital filter. Parameters for this function are:
                // - clock pre-scale (0..1023). The actual pre-scale used is 1 more than this value!
                // - sample window size (0..32)
                // - threshold (window/2 .. window-1) The actual threshold used is 1 more than this value!
                //
                // Subtract one of clock pre-scale and threshold to match function parameters
                CMPSS_configFilterLow(cfg[i].base, cfg[i].samplePrescale-1, cfg[i].sampleWindow, cfg[i].threshold-1);

                //
                // Initialize the filter logic and start filtering
                //
                CMPSS_initFilterLow(cfg[i].base);

            }

            //
            // Clear the latch output
            //
            CMPSS_clearFilterLatchLow(cfg[i].base);

            //
            // Configure the output signals CTRIP (to ePWM X-Bar) and CTRIPOUT (to output X-Bar).
            // Function parameter is a logical OR of CMPSS_TRIPOUT_xxx and CMPSS_TRIP_xxx values.
            // Available are:
            // - CMPSS_TRIPXXX_ASYNC_COMP - The asynchronous comparator output.
            // - CMPSS_TRIPXXX_SYNC_COMP - The synchronous comparator output.
            // - CMPSS_TRIPXXX_FILTER - The output of the digital filter.
            // - CMPSS_TRIPXXX_LATCH - The latched output of the digital filter.
            CMPSS_configOutputsLow(cfg[i].base, cfg[i].outputs);

        } // end else
    } // end for

}

//------------------------------------------------------------------------------------------------
/*!@brief   Disable configured CMPSS modules.
 *
 *@ref      mdlCMPSS_cfg_CMPSS_t
 *@ref      mdlCMPSS_cnf.h
 *
 *@return   none
 *\n
 *@note     disbale the cmpss module if it is already enabled in test mode or in development mode
 *@note     In operation mode development some of the trips will be not be triggered.
 *@note     Currently not being used
  *\n
 */
void mdlCMPSS_deinit_development(void)
{

    uint8_t i;

    // Check the arguments
    ASSERT((e_mdlCMPSS__comparator_COMPH == cfg[i].comparator) || (e_mdlCMPSS__comparator_COMPL == cfg[i].comparator));

    // For each configured CMPSS
    for(i = 0; i < e_mdlCMPSS_cnf_CMPSS__endOfList ; i++)
    {
       if(enbdisCfg[i] == false)
       {
            //
            // disable  the CMPSS module based on static boolean flag
            //
            CMPSS_disableModule(cfg[i].base);
        }

    } // end for

}

//------------------------------------------------------------------------------------------------
/*!@brief   Get comparator latch status.
 *
 *@ref      mdlCMPSS_cfg_CMPSS_t
 *@ref      mdlCMPSS_cnf.h
 *
 *@param    thisComp    : number of specified comparator
 *
 *@return   true if comparator output latched (even if physical error is gone), otherwise false
 *\n
 *@note     Uses the configuration loaded from the config header file into static variable cfg[].
 *
 *\n
 */

bool mdlCMPSS_isCompLatched(mdlCMPSS_cnf_CMPSS_t thisComp)
{
    uint16_t status;
    status = CMPSS_getStatus(cfg[thisComp].base);

    // The condition checks whether the high or low comparator is being checked
    if(e_mdlCMPSS__comparator_COMPH == cfg[thisComp].comparator)
    {
        // return status of high comparator COMPH
        return (status & CMPSS_STS_HI_LATCHFILTOUT);
    }
    else if(e_mdlCMPSS__comparator_COMPL == cfg[thisComp].comparator)
    {
        // return status of low comparator COMPL
        return (status & CMPSS_STS_LO_LATCHFILTOUT);
    }
    else
    {
        return false;
    }
}


//------------------------------------------------------------------------------------------------
/*!@brief   Get comparator status.
 *
 *@ref      mdlCMPSS_cfg_CMPSS_t
 *@ref      mdlCMPSS_cnf.h
 *
 *@param    thisComp    : number of specified comparator
 *
 *@return   true if physical error still present, false if error has been cleared
 *\n
 *@note     Uses the configuration loaded from the config header file into static variable cfg[].
 *
 *\n
 */

bool mdlCMPSS_isErrorStillPresent(mdlCMPSS_cnf_CMPSS_t thisComp)
{
    uint16_t status;
    status = CMPSS_getStatus(cfg[thisComp].base);

    // The condition checks whether the high or low comparator is being checked
    if(e_mdlCMPSS__comparator_COMPH == cfg[thisComp].comparator)
    {
           // return status of high comparator COMPH
           return (status & CMPSS_STS_HI_FILTOUT);
    }
    else if(e_mdlCMPSS__comparator_COMPL == cfg[thisComp].comparator)
    {
           // return status of low comparator COMPL
           return (status & CMPSS_STS_LO_FILTOUT);
    }
    else
    {
           return false;
    }
}

//------------------------------------------------------------------------------------------------
/*!@brief   Clear comparator latch.
 *
 *@ref      mdlCMPSS_cfg_CMPSS_t
 *@ref      mdlCMPSS_cnf.h
 *
 *@param    thisComp    : number of specified comparator
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into static variable cfg[].
 *
 *\n
 */

void mdlCMPSS_clearCompLatch(mdlCMPSS_cnf_CMPSS_t thisComp)
{
    if(e_mdlCMPSS__comparator_COMPH == cfg[thisComp].comparator)
    {
        // clear latch of high comparator COMPH
        CMPSS_clearFilterLatchHigh(cfg[thisComp].base);
    }
    else if(e_mdlCMPSS__comparator_COMPL == cfg[thisComp].comparator)
    {
        // clear latch of low comparator COMPL
        CMPSS_clearFilterLatchLow(cfg[thisComp].base);
    }
}

//------------------------------------------------------------------------------------------------
/*!@brief   Set the maximum reference value loaded into the ramp generator of configured CMPSS
 *          module.
 *
 *@param    thisCMPSS    CMPSS configuration
 *@param    value        16-bit value for ramp generator loading
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variable
 *          cfg[].
 *\n
 */
void mdlCMPSS_setMaxRampValue(mdlCMPSS_cnf_CMPSS_t thisCMPSS, uint16_t value)
{
    CMPSS_setMaxRampValue(cfg[thisCMPSS].base, value);
}


//------------------------------------------------------------------------------------------------
/*!@brief   returns the value to be passed to the DAC to initialize the trip settings
 *
 *@param    tripValue   Value of the trip to be set in physical units i.e. amps/volts/degC
 *@param    gain        Gain value to be used when converting amps/volts to 12 bit value
 *
 *@return   12 bit value to initialize DAC
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variable
 *          cfg[]. The temperature value gains have been set to 1.0 to generalize function
 *\n
 */
uint16_t mdlCMPSS_DACinitValue(float tripValue, float gain)
{
    //
    // Uses the trip values and gains configured in the _cnf.h file
    // Division by gain is actually multiplication by gain since gains
    // are inverted.
    // Multiplied by (mdlADC_12BIT_RANGE / mdlADC_V_REF) to convert
    // to 12 bit value while remaining in range defined by mdlADC_V_REF
    //
    return tripValue / gain * mdlADC_12BIT_RANGE / mdlADC_V_REF;
}


//------------------------------------------------------------------------------------------------
/*!@brief   returns the value to be passed to the DAC to initialize the trip settings
 *
 *@param    tripValue   Value of the trip to be set in physical units i.e. amps/volts/degC
 *@param    gain        Gain value to be used when converting amps/volts to 12 bit value
 *
 *@return   12 bit value to initialize DAC
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variable
 *          cfg[]. The temperature value gains have been set to 1.0 to generalize function
 *\n
 */
void mdlCMPSS_DACvalueUpdate(float tripValueUpdate[])
{
//    mdlCMPSS_initCMPMux();
    uint8_t i;

    // Loop over current and voltage trip modules only
    for(i = 0; i < e_mdlCMPSS_cnf_CMPSS__endOfList; i++)
//    for(i = 0; i < e_mdlCMPSS_cnf_CMPSS__TempATripMax; i++)
    {
        //
        // Enable the CMPSS module
        //
        CMPSS_enableModule(cfg[i].base);

        if(cfg[i].comparator == e_mdlCMPSS__comparator_COMPH)
        {
            if ((tripValueUpdate[i] !=  CMPSS_getDACValueHigh(cfg[i].base)) && (tripValueUpdate[i] > 0)){
                CMPSS_setDACValueHigh(cfg[i].base, mdlCMPSS_DACinitValue(tripValueUpdate[i], cfg[i].gain));
            }
        }
        else if (cfg[i].comparator == e_mdlCMPSS__comparator_COMPL)
        {
            if ((tripValueUpdate[i] != CMPSS_getDACValueLow(cfg[i].base)) && (tripValueUpdate[i] > 0)){
                CMPSS_setDACValueLow(cfg[i].base, mdlCMPSS_DACinitValue(tripValueUpdate[i], cfg[i].gain));
            }
        }
    }
}

    //-------------------------
    // Private Section
    //*************************

void mdlCMPSS_initCMPMux(void)
{
    // +24V_FEED AIO1
    ASysCtl_selectCMPLPMux(ASYSCTL_CMPLPMUX_SELECT_1, 1);  // +24V_FEED @ C0 to CMPSS1 Low on positive PIN
    ASysCtl_selectCMPLPMux(ASYSCTL_CMPLPMUX_SELECT_3, 3);  // +24V_FEED @ B3 to CMPSS3 Low on positive PIN

    // OUT_OF_PHASE AIO2
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_1, 0);  // +24V_FEED @ A2 to CMPSS1 High on positive PIN

    // V_GYR AIO3
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_2, 2);  // V_GYR @ (A4 to CMPSS2 High on positive PIN) pin 30 -> CMPSS2 High Positive
    // This has been changed to select a different input to the comparator. The signal from pin 30
    // comes after a physical low pass filter on the control board. (originally 0)


    // I_GYR AIO4
//    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_3, 2);  // I_GYR @ [B2] B10 to CMPSS3 High on positive PIN (originally 0)
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_3, 4);
    // changed from HPMUX to LPMUX to correct comparator operations. See TRM pg. 1415, Analogue Group 3 (check to see if HPMUX also works)

    // INV_I AIO5
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_4, 0);  // INV_I @ B4 to CMPSS4 High on positive PIN

    // GYR_Overtemp AIO6
    ASysCtl_selectCMPLPMux(ASYSCTL_CMPLPMUX_SELECT_2, 1);  // +GYR_Overtemp @ C to CMPSS2 Low on positive PIN

    // Temp_B_Overtemp AIO7
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_5, 2);  // Temp_B_Overtemp @ PGA5_IN to CMPSS5 High on positive PIN

    // V_Bus AIO8
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_6, 1);  // +V_Bus @ C5 to CMPSS6 High on positive PIN
    ASysCtl_selectCMPLPMux(ASYSCTL_CMPLPMUX_SELECT_6, 2);  // +V_Bus @ C5 to CMPSS6 Low on positive PIN

    // Temp_A_Overtemp AIO7
    ASysCtl_selectCMPHPMux(ASYSCTL_CMPHPMUX_SELECT_7, 2);  // Temp_A_Overtemp @ PGA7_IN to CMPSS7 High on positive PIN

}

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

/** @}*/

