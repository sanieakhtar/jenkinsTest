/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file mdlADC.c @copyright
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
/*!@file            mdlADC.c
 * @brief           Functions to configure and start ADC conversions and to
 *                  read the conversion result.
 *//*
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/


/*****************************************************************************/
/*! \addtogroup mdlADC ADC
 * @brief  Configure on-chip ADCs including SOCs
 *
 *  This module provides functions for setup of the ADC modules and the
 *  conversions (SOCs) to be performed.
 *  @{
 *****************************************************************************/


//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=



//=============================================================================
// Includes
#include "device.h"
#include "mdlADC.h"


//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

static mdlADC_cfg_ADC_t cfg[e_mdlADC_cnf_ADC__endOfList] = {
#define LOAD_MODULE_CONFIGURATION
    #include "./_config/mdlADC_cnf.h"
#undef  LOAD_MODULE_CONFIGURATION
};

static mdlADC_cfg_SOC_t soc[e_mdlADC_cnf_SOC__endOfList] = {
#define LOAD_SOC_CONFIGURATION
    #include "./_config/mdlADC_cnf.h"
#undef  LOAD_SOC_CONFIGURATION
};


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

void mdlADC_initADC(mdlADC_cnf_ADC_t thisADC);
void mdlADC_initSOC(mdlADC_cnf_SOC_t thisSOC);

    //-------------------------
    // Public Section
    //*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Initialize ADC conversions (SOCs) and ADC modules needed.
 *
 *@ref      mdlADC_cfg_SOC_t
 *@ref      mdlADC_cfg_ADC_t
 *@ref      mdlADC_cnf.h
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variables soc[] and cfg[].
 *          Each ADC module will only be initialized only once and only if used.
 *\n
 */
void mdlADC_init(void)
{
    uint8_t i;
    uint32_t adc_base;

    bool ADCA_initialized = false;
#ifdef ADCB_BASE
    bool ADCB_initialized = false;
#endif
#ifdef ADCC_BASE
    bool ADCC_initialized = false;
#endif
//#ifdef ADCD_BASE
//    bool ADCD_initialized = false;
//#endif

    // For each configured ADC SOC
    for(i = 0; i < e_mdlADC_cnf_SOC__endOfList; i++)
    {

        adc_base = cfg[soc[i].adcNumber].base;

        // Each module should only be initialized once.
        // If module has already been initialized, skip initialization.
        if(ADCA_BASE == adc_base)
        {
            // If not yet done, initialize this ADC module
            if(!ADCA_initialized)
            {
                ADCA_initialized = true;
                mdlADC_initADC((mdlADC_cnf_ADC_t) soc[i].adcNumber);
            }
        } // end if

#ifdef ADCB_BASE
        else if(ADCB_BASE == adc_base)
        {
            // If not yet done, initialize this ADC module
            if(!ADCB_initialized)
            {
                ADCB_initialized = true;
                mdlADC_initADC((mdlADC_cnf_ADC_t) soc[i].adcNumber);
            }
        } //end else if
#endif

#ifdef ADCC_BASE
        else if(ADCC_BASE == adc_base)
        {
            // If not yet done, initialize this ADC module
            if(!ADCC_initialized)
            {
                ADCC_initialized = true;
                mdlADC_initADC((mdlADC_cnf_ADC_t) soc[i].adcNumber);
            }
        } //end else if
#endif

//#ifdef ADCD_BASE
//        else if(ADCD_BASE == adc_base)
//        {
//            // If not yet done, initialize this ADC module
//            if(!ADCD_initialized)
//            {
//                ADCD_initialized = true;
//                mdlADC_initADC((mdlADC_cnf_ADC_t) soc[i].adcNumber);
//            }
//        } //end else if
//#endif
        else
        {
            // Not supported ADC base
            ASSERT(0);
        } //end else

        //
        // Initialize SOC
        //
        mdlADC_initSOC((mdlADC_cnf_SOC_t) i);

    }// end for
}


//------------------------------------------------------------------------------------------------
/*!@brief   Start conversion of specific SOC.
 *
 *@ref      mdlADC_cfg_SOC_t
 *@ref      mdlADC_cfg_ADC_t
 *@ref      mdlADC_cnf.h
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variables
 *          soc[] and cfg[].
 *
 *\n
 */
void mdlADC_startConversion(mdlADC_cnf_SOC_t thisSOC)
{
    ADC_forceSOC(cfg[soc[thisSOC].adcNumber].base, soc[thisSOC].socNumber);
}


//------------------------------------------------------------------------------------------------
/*!@brief   Read conversion result of specific SOC.
 *
 *@ref      mdlADC_cfg_SOC_t
 *@ref      mdlADC_cfg_ADC_t
 *@ref      mdlADC_cnf.h
 *
 *@return   conversion result
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variables
 *          soc[] and cfg[].
 *\n
 */
uint16_t mdlADC_readResult(mdlADC_cnf_SOC_t thisSOC)
{
    uint32_t adc_base;
    uint32_t adc_result_base;

    adc_base = cfg[soc[thisSOC].adcNumber].base;

    //
    // Set the base for result registers matching the base of the control registers
    //
    if(adc_base == ADCA_BASE)
    {
        adc_result_base = ADCARESULT_BASE;
    }

#ifdef ADCB_BASE
    else if(adc_base == ADCB_BASE)
    {
        adc_result_base = ADCBRESULT_BASE;
    }
#endif

#ifdef ADCC_BASE
    else if(adc_base == ADCC_BASE)
    {
        adc_result_base = ADCCRESULT_BASE;
    }
#endif

//#ifdef ADCD_BASE
//    else if(adc_base == ADCD_BASE)
//    {
//        adc_result_base = ADCDRESULT_BASE;
//    }
//#endif

    return ADC_readResult(adc_result_base, soc[thisSOC].socNumber);
}


    //-------------------------
    // Private Section
    //*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Initialize ADC module.
 *
 *@ref      mdlADC_cfg_ADC_t
 *@ref      mdlADC_cnf.h
 *
 *@param    thisADC     number of ADC module
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into static variable cfg[].
 *@note     Signal mode is not configurable for this device (single-ended only).
 *@note     Resolution is not configurable for this device (12-bit only).
 *
 *\n
 */
void mdlADC_initADC(mdlADC_cnf_ADC_t thisADC)
{
    //
    // Set ADCCLK divider
    //
    ADC_setPrescaler(cfg[thisADC].base, cfg[thisADC].clkPrescale);

    //
    // Set reference to internal or external
    //
    if(cfg[thisADC].refVoltage < sizeof(ADC_ReferenceVoltage))
    {
        // Use internal reference
        ADC_setVREF(cfg[thisADC].base, ADC_REFERENCE_INTERNAL, cfg[thisADC].refVoltage);
    }
    else
    {
        // If reference voltage does not match above cases, configure for external reference
        // 3rd argument is meaningless in this case!
        ADC_setVREF(cfg[thisADC].base, ADC_REFERENCE_EXTERNAL, (ADC_ReferenceVoltage) 0);
    }

    //
    // Set pulse positions
    //
    ADC_setInterruptPulseMode(cfg[thisADC].base, cfg[thisADC].pulseMode);

    //
    // Set the priority mode of the SOCs
    //
    ADC_setSOCPriority(cfg[thisADC].base, cfg[thisADC].priorityMode);

    //
    // If SOC burst mode is configured for an ADC module, set it up and enable it.
    // When burst mode is enabled, the trigger selected by the ADC_setupSOC()
    // API will no longer have an effect on the SOCs in round-robin mode (not high priority).
    //
    if(cfg[thisADC].burstEnable)
    {
        ADC_setBurstModeConfig(cfg[thisADC].base, cfg[thisADC].burstTrigger, cfg[thisADC].burstSize);
        ADC_enableBurstMode(cfg[thisADC].base);
    }
    else
    {
        ADC_disableBurstMode(cfg[thisADC].base);
    }

    //
    // Power up the ADC and then delay for 1 ms
    //
    ADC_enableConverter(cfg[thisADC].base);
    DEVICE_DELAY_US(1000);

}

//------------------------------------------------------------------------------------------------
/*!@brief   Initialize ADC SOC.
 *
 *@ref      mdlADC_cfg_SOC_t
 *@ref      mdlADC_cnf.h
 *
 *@param    thisSOC    : number of SOC
 *
 *@return   none
 *\n
 *@note     Uses the configurations loaded from the config header file into static variable soc[].
 *
 *\n
 */
void mdlADC_initSOC(mdlADC_cnf_SOC_t thisSOC)
{
    uint32_t adc_base;
    uint16_t acq_window;

    adc_base = cfg[soc[thisSOC].adcNumber].base;

    //
    // Set the acquisition window length extra long for the internal temperature
    // sensor connected to mdlADC_cnf_ADC_BASE_TEMP_UC channel mdlADC_cnf_ADC_CH_TEMP_UC (requires > 700ns)
    //
    if((adc_base == mdlADC_cnf_ADC_BASE_TEMP_UC) && (soc[thisSOC].channel == mdlADC_cnf_ADC_CH_TEMP_UC))
    {
        acq_window = mdlADC_cnf_SH_TIME_TEMP_UC;
    }

    // For all other channels use the default window length
    else
    {
        acq_window = mdlADC_cnf_SH_TIME_DEFAULT;
    }
    //
    // Configure SOC
    //
    ADC_setupSOC(adc_base, soc[thisSOC].socNumber, soc[thisSOC].trigger, soc[thisSOC].channel, acq_window);

    if(soc[thisSOC].intNumber != 0xFF)
    {
        //
        // Configure SOC interrupt. Enable the interrupt and make
        // sure its flag is cleared.
        //
        ADC_setInterruptSource(adc_base, soc[thisSOC].intNumber, soc[thisSOC].socNumber);
        ADC_enableInterrupt(adc_base, soc[thisSOC].intNumber);
        ADC_clearInterruptStatus(adc_base, soc[thisSOC].intNumber);
    }

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
