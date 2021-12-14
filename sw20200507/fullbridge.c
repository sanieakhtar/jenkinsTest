/**
 * \defgroup Core
 * @{
 */

/**
 * \addtogroup Core
 *  @{
 */

/*****************************************************************************/
/*!@file fullbridge.c @copyright
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
/*!@file            Fullbridge.c
 * @brief           Abstraction layer for DC/AC converter.
 *//*
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes
#include "globals.h"
#include "fullbridge.h"
#include "inv_shared.h"
#include "_module/mdlEPWM/mdlEPWM.h"
#include "_module/mdlMeasurement/_config/mdlMeasurement_cnf.h"



//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

static float phaseSetpoint  = 0.0F;         /*!< Initialize to zero, so that the initial call with
                                                 new setpoint equal to zero will set voref_adc to zero.*/
static float refSetpoint    = 0.0F;         /*!< Initialize to zero, so that the initial call with
                                                 new setpoint equal to zero will set voref_adc to zero.*/



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


    //-------------------------
    // Public Section
    //*************************


void fullbridge_init(void)
{

}


void fullbridge_disable(void)
{
    // Force trip zone flags to disable PWMs
    mdlEPWM_forceTripZone(e_mdlEPWM_cnf_TZ__OST_DCAEVT1_ePWM2A);
    mdlEPWM_forceTripZone(e_mdlEPWM_cnf_TZ__OST_DCAEVT1_ePWM2B);
    mdlEPWM_forceTripZone(e_mdlEPWM_cnf_TZ__OST_DCAEVT1_ePWM7A);
    mdlEPWM_forceTripZone(e_mdlEPWM_cnf_TZ__OST_DCAEVT1_ePWM7B);

    DEBUG_PRINT("Fullbridge off");

    // Clear global status flag
    CLEARFLAG(EnableFlags, e_global_enableFlag__fullbridgePWM);
}

void fullbridge_enable(void)
{
    // Force CLA initialization task, which resets the soft-start
    CLA_forceTasks(CLA1_BASE, CLA_TASKFLAG_2);

    // Try to clear trip zone flags to enable PWMs
    mdlEPWM_clearTripZoneFlags(e_mdlEPWM_cnf_TZ__OST_DCAEVT1_ePWM2A);
    mdlEPWM_clearTripZoneFlags(e_mdlEPWM_cnf_TZ__OST_DCAEVT1_ePWM2B);
    mdlEPWM_clearTripZoneFlags(e_mdlEPWM_cnf_TZ__OST_DCAEVT1_ePWM7A);
    mdlEPWM_clearTripZoneFlags(e_mdlEPWM_cnf_TZ__OST_DCAEVT1_ePWM7B);

    DEBUG_PRINT("Fullbridge on");

    // Set global status flag
    SETFLAG(EnableFlags, e_global_enableFlag__fullbridgePWM);
}



//------------------------------------------------------------------------------------------------
/*!@brief   Write the peak current setting in [bits/A] to the shared variable il_max.
 *
 *@param[in]    new_setpoint    :   peak current setting in [A]
 *@param[in]    I_Slope         :   current slope setting in [A per Tick]
 *
 *@return       action          :   see @ref setOutputCurrent_t
 *\n
  *@note    Call this function at the time rate specified by your application i.e. SYSTICK_TIMER.
 *\n        CLA il_max peak current reference will be stepped up or down at I_Slope rate.
 */
eFullbridge_Ramp_t fullbridge_rampPhase(float newSetpoint, float rampTime)
{
    //local variables

    eFullbridge_Ramp_t action;
    float diff;
    float phaseSlope= newSetpoint / rampTime;
    //------------------------------

    diff = newSetpoint - phaseSetpoint;
    // No change of setpoint
    if(diff == 0)
    {
        action = e_Fullbridge_Ramp__noAction;
    }
    // If new setpoint differs from current setpoint
    else
    {
        // Ramp up or down setpoint in steps
        if(diff >= phaseSlope)
        {
            phaseSetpoint += phaseSlope;
            action = e_Fullbridge_Ramp__rampUp;
        }
        else if(diff <= -phaseSlope)
        {
            phaseSetpoint -= phaseSlope;
            action = e_Fullbridge_Ramp__rampDown;
        }
        else
        {
            phaseSetpoint = newSetpoint;
            action = e_Fullbridge_Ramp__done;
        }

        // Convert to ADC bits and assign value to output voltage reference
        // used by 2p2z-controller implemented in CLA.
        //il_max = Isetpoint * 1/Sensor_getGain(&Sensor_I_buck1); //(KI * DAC_RANGE / VDAC_REF);

        phase_limit = (uint16_t)phaseSetpoint;
    }

    return action;
}



//------------------------------------------------------------------------------------------------
/*!@brief   Write the peak current setting in [bits/A] to the shared variable il_max.
 *
 *@param[in]    new_setpoint    :   peak current setting in [A]
 *@param[in]    I_Slope         :   current slope setting in [A per Tick]
 *
 *@return       action          :   see @ref setOutputCurrent_t
 *\n
  *@note    Call this function at the time rate specified by your application i.e. SYSTICK_TIMER.
 *\n        CLA il_max peak current reference will be stepped up or down at I_Slope rate.
 */
eFullbridge_Ramp_t fullbridge_rampRef(float newSetpoint, float rampTime)
{
    //local variables

    eFullbridge_Ramp_t action;
    float diff;
    float refSlope= newSetpoint/rampTime;
    //------------------------------

    diff = newSetpoint - refSetpoint;
    // No change of setpoint
    if(diff == 0)
    {
        action = e_Fullbridge_Ramp__noAction;
    }
    // If new setpoint differs from current setpoint
    else
    {
        // Ramp up or down setpoint in steps
        if(diff >= refSlope)
        {
            refSetpoint += refSlope;
            action = e_Fullbridge_Ramp__rampUp;
        }
        else if(diff <= -refSlope)
        {
            refSetpoint -= refSlope;
            action = e_Fullbridge_Ramp__rampDown;
        }
        else
        {
            refSetpoint = newSetpoint;
            action = e_Fullbridge_Ramp__done;
        }

//        I_gyr_ref_cla = ((uint16_t) ((refSetpoint / mdlMeasurement_IGYR_GAIN) * 4095.0 / 3.3));
        I_gyr_ref_cla = (uint16_t) ((refSetpoint / mdlMeasurement_IGYR_GAIN) * mdlADC_RANGE / VADC_REF);
//        I_gyr_ref_cla = (float) (refSetpoint / mdlMeasurement_IGYR_GAIN) * (float) (mdlADC_RANGE / VADC_REF);


        // This reference value depends on:
        // The number of turns on the current converter
        // The resistor being used in the current feedback circuit
        // The conversion factor between the transformer (either 1 or 2)
        // Supply voltage (3.3)
        // The gain
        // ref = setpoint * (resistance / conversion_factor / turns) * 4095 / supply voltage
    }

    return action;
}


//------------------------------------------------------------------------------------------------
/*!@brief   Reset the Current Setpoint
 *
 *@return   none
 *\n
 *@note     Set's the Current Setpoint @ref Isetpoint to zero which start a new Ramp with @ref setBuckMaxPeakCurrent
 *\n
 */
void fullbridge_resetRef(void)
{
    //TODO local variables

    //------------------------------

    refSetpoint = 0.0F;
    I_gyr_ref_cla = 0.0F;

    return;
}


//------------------------------------------------------------------------------------------------
/*!@brief   Reset the Current Setpoint
 *
 *@return   none
 *\n
 *@note     Set's the Current Setpoint @ref Psetpoint to zero which start a new Ramp
 *\n
 */
void fullbridge_resetPhase(void)
{
    //TODO local variables

    //------------------------------


    phaseSetpoint = 0;
    phase_limit = 0;

    return;
}

//------------------------------------------------------------------------------------------------
/*!@brief   Update gyrator reference voltage to new value set by user over CAN
 *
 * @return   None
 *
 * @note     Move to Fullbridge.c, since direct impact on Fullbridge, fits better there
 *\n
 */
void fullbridge_updatePeakRef(uint16_t peakRefUpdate)
{
    if ((peakRefUpdate != I_gyr_ref) && (peakRefUpdate > 0)) {
        I_gyr_ref = peakRefUpdate;
    }
}

    //-------------------------
    // Private Section
    //*************************



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

