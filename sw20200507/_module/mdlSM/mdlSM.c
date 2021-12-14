/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file mdlSM.c @copyright
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
/*!@file            mdlSM.c
 * @brief           Module for state machine implementation.
 *//*
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "f28004x_device.h"
#include "device.h"
#include "fullbridge.h"
#include "inv_cnf.h"
#include "inv_shared.h"
#include "mdlSM.h"
//#include "globals.h" // included through CMPSS.h and SM.h

#include "../mdlHAL/mdlHAL.h"
#include "../mdlCMPSS/mdlCMPSS.h"
#include "../mdlError/mdlError.h"
#include "../mdlDebounce/mdlDebounce.h"


//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*!@brief
 *  Array of configured states, initialized with settings from configuration file.
 */
static mdlSM_cfg_State_t cfg[e_mdlSM_cnf_State__endOfList] = {
#define LOAD_MODULE_CONFIGURATION
#   include "./_config/mdlSM_cnf.h"
#undef  LOAD_MODULE_CONFIGURATION
};


//static mdlDebounce_Input_t ORgate_Fault_ext;        //!< State of the SIL OR gate
static mdlDebounce_Input_t operate;
static mdlDebounce_Input_t ext_sil;
mdlSM_INV_t theINV;                                 //!< State machine object declaration

SMTimer timeout;                                    //!< Timer object for timed actions
SMTimer transOPERATE;
SMTimer transSTANDBY;
SMTimer clearERROR;


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

const int* mdlSM_Boot(mdlSM_INV_t *me, stateActions_t action);
const int* mdlSM_Idle(mdlSM_INV_t *me, stateActions_t action);
const int* mdlSM_Standby(mdlSM_INV_t *me, stateActions_t action);
const int* mdlSM_Operate(mdlSM_INV_t *me, stateActions_t action);
const int* mdlSM_Error(mdlSM_INV_t *me, stateActions_t action);

static void mdlSM_checkForErrors(void);
static void mdlSM_clearAllErrors(void);

//-------------------------
// Public Section
//*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Set the initial state.
 *
 *@ref      mdlSM.h
 *@ref      mdlSM_cnf_States_t
 *
 *@return   none
 *\n
 */
void mdlSM_init(void)
{
    // Initialize used timers
    SMTimerInitialize(&timeout);

    // Point to function mdlSM_Boot()
    SM_init((SM*)&theINV, (SMState)mdlSM_Boot);
}

//------------------------------------------------------------------------------------------------
/*!@brief   Trigger the state machine.
 *
 *@ref      mdlSM.h
 *@ref      mdlSM_cnf_States_t
 *
 *@return   none
 *
 *@note     Call in a cyclic manner
 *          - to check if a change of stat is required.
 *          - to trigger regular tasks within a state.
 *\n
 */
void mdlSM_exec(void)
{
    // Check if a state transition is required
    SM_exec((SM*)&theINV);
}

//------------------------------------------------------------------------------------------------
/*!@brief   Get the current state.
 *
 *@ref      mdlSM_cnf_States_t
 *@ref      mdlSM.h
 *@ref      mdlSM_cnf.h
 *
 *@return   The numerical ID configured for the current state.
 *\n
 */
uint8_t mdlSM_getStateID(void)
{
    return *SM_getState((SM*)&theINV);
}


//-------------------------
// Private Section
//*************************



////------------------------------------------------------------------------------------------------
///*!@brief   Control fan.
// * todo this function should be moved elsewhere
// *
// *@param    enable  > 0 -> enable fan
// *                  = 0 -> disable fan
// *
// *@return   none
// *
// *@note
// *\n
// */
//void mdlSM_controlFans(uint16_t enable)
//{
//    mdlHAL_writePin(e_mdlHAL_cnf_PIN__enableFan, enable);
//
//    DEBUG_PRINT("Fan off");
//    // Clear global status flag
//    CLEARFLAG(EnableFlags, e_global_enableFlag__fan);
//
//    DEBUG_PRINT("Fan on");
//    // Set global status flag
//    SETFLAG(EnableFlags, e_global_enableFlag__fan);
//}


//------------------------------------------------------------------------------------------------
/*!@brief   Flag an error.
 *
 *@return   none
 *
 *@note
 *\n
 */
void mdlSM_flagError(uint16_t flag)
{
    // If error flagged, transition to error state
    if(mdlError_set((mdlError_cnf_ErrorFlag_t) flag))
    {
        // Transition to ERROR state
        SM_tran((SM*)&theINV, (SMState)mdlSM_Error);
    }

    // If error originates from INV AIOs, set fault pin to low (high for testing)
    if(flag != e_mdlError_cnf_ErrorFlag___FAULT_SIL)
    {
        // TODO Set _FAULT_UC to low (high for testing)
        mdlHAL_writePin(e_mdlHAL_cnf_PIN___FAULT_uC, LOW);
    }
}


//------------------------------------------------------------------------------------------------
/*!@brief   Check latches of comparators to see if errors have been latched. Set respective flags
 *          of the errors that are present and latched
 *
 *@return   none
 *\n
 */
static void mdlSM_checkForErrors(void)
{

    mdlDebounce_update(&ext_sil);

    // Check state of comparator latch for max. supply voltage detection
    if(mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__VsupplyTripMax))
    {
        mdlSM_flagError(e_mdlError_cnf_ErrorFlag__VsupplyMax);
    }

    // Check state of comparator latch for min. supply voltage detection
    if(mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__VsupplyTripMin))
    {
        mdlSM_flagError(e_mdlError_cnf_ErrorFlag__VsupplyMin);
    }

    // Check state of comparator latch for max. bus voltage detection
    if(mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__VbusTripMax))
    {
        mdlSM_flagError(e_mdlError_cnf_ErrorFlag__VbusMax);
    }

    // Check state of comparator latch for min. bus voltage detection
    if(mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__VbusTripMin))
    {
        mdlSM_flagError(e_mdlError_cnf_ErrorFlag__VbusMin);
    }

    // Check state of comparator latch for max. gyrator voltage detection
    if(mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__VgyrTripMax))
    {
        mdlSM_flagError(e_mdlError_cnf_ErrorFlag__VgyrHigh);
    }

    // Check state of comparator latch for max. gyrator current detection
    if(mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__IgyrTripMax))
    {
        mdlSM_flagError(e_mdlError_cnf_ErrorFlag__IgyrHigh);
    }

    // Check state of comparator latch for max. inverter current detection
    if(mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__IinvTripMax))
    {
        mdlSM_flagError(e_mdlError_cnf_ErrorFlag__IinvHigh);
    }

    // Check state of external fault pin
    if(!mdlDebounce_getState(&ext_sil))
    {
        // If pin is low, flag error
        mdlSM_flagError(e_mdlError_cnf_ErrorFlag___FAULT_SIL);
    }
}

//------------------------------------------------------------------------------------------------
/*!@brief   Clear all error flags.
 *
 *@return   none
 *
 *@note     Depending on the type of error flag, a check of the error condition may be necessary.
 *
 *\n
 */
static void mdlSM_clearAllErrors(void)
{
    uint8_t i;
    //    mdlDebounce_update(&ext_sil);
    //    bool SIL_STATE  = LOW;
    //    bool check = false;

    // For each configured error flag
    for(i = 1; i < e_mdlError_cnf_ErrorFlag__endOfList; i++)
    {
        // Clear error flag and possibly hardware latches, depending on type
        // of error.
        switch(i)
        {
        case e_mdlError_cnf_ErrorFlag__VsupplyMax:
            // Clear and check state of comparator latch connected to supply voltage
            if(!mdlCMPSS_isErrorStillPresent(e_mdlCMPSS_cnf_CMPSS__VsupplyTripMax))
            {
                mdlCMPSS_clearCompLatch(e_mdlCMPSS_cnf_CMPSS__VsupplyTripMax);
            }
            if(!mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__VsupplyTripMax))
            {
                mdlError_clear(e_mdlError_cnf_ErrorFlag__VsupplyMax);
            }
            break;

        case e_mdlError_cnf_ErrorFlag__VsupplyMin:
            // Clear and check state of comparator latch connected to supply voltage
            if(!mdlCMPSS_isErrorStillPresent(e_mdlCMPSS_cnf_CMPSS__VsupplyTripMin))
            {
                mdlCMPSS_clearCompLatch(e_mdlCMPSS_cnf_CMPSS__VsupplyTripMin);
            }
            if(!mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__VsupplyTripMin))
            {
                mdlError_clear(e_mdlError_cnf_ErrorFlag__VsupplyMin);
            }
            break;

        case e_mdlError_cnf_ErrorFlag__VbusMax:
            // Clear and check state of comparator latch connected to DC bus voltage
            if(!mdlCMPSS_isErrorStillPresent(e_mdlCMPSS_cnf_CMPSS__VbusTripMax))
            {
                mdlCMPSS_clearCompLatch(e_mdlCMPSS_cnf_CMPSS__VbusTripMax);
            }
            if(!mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__VbusTripMax))
            {
                mdlError_clear(e_mdlError_cnf_ErrorFlag__VbusMax);
            }
            break;

        case e_mdlError_cnf_ErrorFlag__VbusMin:
            // Clear and check state of comparator latch connected to DC bus voltage
            if(!mdlCMPSS_isErrorStillPresent(e_mdlCMPSS_cnf_CMPSS__VbusTripMin))
            {
                mdlCMPSS_clearCompLatch(e_mdlCMPSS_cnf_CMPSS__VbusTripMin);
            }
            if(!mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__VbusTripMin))
            {
                mdlError_clear(e_mdlError_cnf_ErrorFlag__VbusMin);
            }
            break;

        case e_mdlError_cnf_ErrorFlag__VgyrHigh:
            // Clear and check state of comparator latch connected to gyrator voltage
            if(!mdlCMPSS_isErrorStillPresent(e_mdlCMPSS_cnf_CMPSS__VgyrTripMax))
            {
                mdlCMPSS_clearCompLatch(e_mdlCMPSS_cnf_CMPSS__VgyrTripMax);
            }
            if(!mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__VgyrTripMax))
            {
                mdlError_clear(e_mdlError_cnf_ErrorFlag__VgyrHigh);
            }
            break;

        case e_mdlError_cnf_ErrorFlag__IgyrHigh:
            // Clear and check state of comparator latch connected to gyrator current
            if(!mdlCMPSS_isErrorStillPresent(e_mdlCMPSS_cnf_CMPSS__IgyrTripMax))
            {
                mdlCMPSS_clearCompLatch(e_mdlCMPSS_cnf_CMPSS__IgyrTripMax);
            }
            if(!mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__IgyrTripMax))
            {
                mdlError_clear(e_mdlError_cnf_ErrorFlag__IgyrHigh);
            }
            break;

        case e_mdlError_cnf_ErrorFlag__IinvHigh:
            // Clear and check state of comparator latch connected to inverter current
            if(!mdlCMPSS_isErrorStillPresent(e_mdlCMPSS_cnf_CMPSS__IinvTripMax))
            {
                mdlCMPSS_clearCompLatch(e_mdlCMPSS_cnf_CMPSS__IinvTripMax);
            }
            if(!mdlCMPSS_isCompLatched(e_mdlCMPSS_cnf_CMPSS__IinvTripMax))
            {
                mdlError_clear(e_mdlError_cnf_ErrorFlag__IinvHigh);
            }
            break;

        case e_mdlError_cnf_ErrorFlag___FAULT_SIL:
            // Get state of _FAULT_SIL through debounce sequence
            if(mdlDebounce_getState(&ext_sil))
            {
                // If pin is high, fault has been removed so clear flag
                mdlError_clear(e_mdlError_cnf_ErrorFlag___FAULT_SIL);
            }
            break;

        default:
            // To prevent unprecedented clearing of error flags,
            // do nothing in default case. Assert if error is found
            ASSERT(i < e_mdlError_cnf_ErrorFlag__endOfList);
            break;
        } //end switch
    }// end for
}


//------------------------------------------------------------------------------------------------
/*!@brief   State handler for state BOOT
 *
 *@return   pointer to numerical ID configured for the this state.
 *\n
 */
const int* mdlSM_Boot(mdlSM_INV_t *me, stateActions_t action)
{
    const int *result = 0;

    switch(action)
    {
    case ENTRY_ACTION:
        DEBUG_PRINT("> BOOT");

        // Set delay for transition to STANDBY state
        SMTimerFireIn(&transSTANDBY, mdlSM_cnf_BOOT_DELAY * mdlSM_cnf_TICKS_PER_MS);
        break;

    case DO_ACTION:
        // Only check for 24V supply in BOOT. Start checking for other errors when in STANDBY
        if (V_24V > INV_cnf__V_24V_MIN_TRIP)
        {
            SMTimerTick(&transSTANDBY, SM_tran((SM*)&theINV, (SMState)mdlSM_Idle));
        }
        else
        {
            DEBUG_PRINT("V24_Low");
        }
        break;

    case EXIT_ACTION:
        DEBUG_PRINT("BOOT >");
        break;

    case WHOAMI:
        // point to ID configured for this state
        result = &cfg[e_mdlSM_cnf_State__Boot].stateID;
        break;
    } // end switch

    return result;
}


//------------------------------------------------------------------------------------------------
/*!@brief   State handler for state IDLE
 *
 *@return   pointer to numerical ID configured for the this state.
 *\n
 */
const int* mdlSM_Idle(mdlSM_INV_t *me, stateActions_t action)
{
    const int *result = 0;

    switch(action)
    {
    case ENTRY_ACTION:
        DEBUG_PRINT("> IDLE");

        // Set delay for transition to STANDBY state
        SMTimerFireIn(&transSTANDBY, mdlSM_cnf_BOOT_DELAY * mdlSM_cnf_TICKS_PER_MS);
        break;

    case DO_ACTION:
        // Only check for bus voltage in IDLE. Start checking for other errors when in STANDBY
        if (V_bus > INV_cnf__V_BUS_MIN_TRIP)
        {
            SMTimerTick(&transSTANDBY, SM_tran((SM*)&theINV, (SMState)mdlSM_Standby));
        }
        else
        {
            DEBUG_PRINT("V_BUS_Low");
        }
        break;

    case EXIT_ACTION:
        DEBUG_PRINT("IDLE >");
        break;

    case WHOAMI:
        // point to ID configured for this state
        result = &cfg[e_mdlSM_cnf_State__Idle].stateID;
        break;
    } // end switch

    return result;
}


//------------------------------------------------------------------------------------------------
/*!@brief   State handler for state STANDBY
 *
 *@return   pointer to numerical ID configured for the this state.
 *\n
 */
const int* mdlSM_Standby(mdlSM_INV_t *me, stateActions_t action)
{
    const int *result = 0;

    switch(action)
    {
    case ENTRY_ACTION:
        DEBUG_PRINT("> STANDBY");

        // Set /FAULT_uC pin to high to indicate that no fault is present
        mdlHAL_writePin(e_mdlHAL_cnf_PIN___FAULT_uC, HIGH);

        // Initialize debouncing of input pins
        mdlDebounce_init(&operate, e_mdlHAL_cnf_PIN__operate);
        mdlDebounce_init(&ext_sil, e_mdlHAL_cnf_PIN___FAULT_SIL);

        mdlSM_clearAllErrors();

        // Initialize timeout for transition to operate state
        SMTimerFireIn(&transOPERATE, mdlSM_cnf_OPERATE_DELAY * mdlSM_cnf_TICKS_PER_MS);
        break;

    case DO_ACTION:
        // Check if any error condition is present
        mdlSM_checkForErrors();

        // Update values of input pins through debounce sequence
        mdlDebounce_update(&operate);
        mdlDebounce_update(&ext_sil);

        // Read input pins through debounce sequence. If both pins high, advance timer to transition
        // to OPERATE
        if(mdlDebounce_getState(&operate) && mdlDebounce_getState(&ext_sil))
        {
            // On timeout, transition to OPERATE
            SMTimerTick(&transOPERATE, SM_tran((SM*)&theINV, (SMState)mdlSM_Operate));
        }

        // If one of the two inputs pins is low, restart timer to transition to OPERATE. Timer will
        // keep getting restarted until both inputs are high.
        if(!mdlDebounce_getState(&operate) || !mdlDebounce_getState(&ext_sil))
        {
            // restart timer for transition to OPERATE
            SMTimerFireIn(&transOPERATE, mdlSM_cnf_OPERATE_DELAY * mdlSM_cnf_TICKS_PER_MS);
        }
        break;

    case EXIT_ACTION:
        DEBUG_PRINT("STANDBY >");
        break;

    case WHOAMI:
        // point to ID configured for this state
        result = &cfg[e_mdlSM_cnf_State__Standby].stateID;
        break;
    } // end switch

    return result;
}


//------------------------------------------------------------------------------------------------
/*!@brief   State handler for state OPERATE
 *
 *@return   pointer to numerical ID configured for the this state.
 *\n
 */
const int* mdlSM_Operate(mdlSM_INV_t *me, stateActions_t action)
{
    const int *result = 0;

    switch(action)
    {
    case ENTRY_ACTION:
        DEBUG_PRINT("> OPERATE");

        // Set /FAULT_uC pin to high to indicate that no fault is present
        mdlHAL_writePin(e_mdlHAL_cnf_PIN___FAULT_uC, HIGH);
        mdlSM_clearAllErrors();
        fullbridge_resetPhase();
        fullbridge_resetRef();
        fullbridge_init();
        fullbridge_enable();
        SMTimerFireIn(&transSTANDBY, mdlSM_cnf_DISABLE_DELAY * mdlSM_cnf_TICKS_PER_MS);
        break;

    case DO_ACTION:
        // Check if any error condition is present
        mdlSM_checkForErrors();

        // Update values of input pins through debounce sequence
        mdlDebounce_update(&operate);
        mdlDebounce_update(&ext_sil);

        fullbridge_rampPhase(EPWM_getTimeBasePeriod(EPWM7_BASE) >> 1, 200.0F);
        fullbridge_rampRef(I_gyr_ref, 200.0F);

        // Keep restarting the timer for transition since no transition to STANDBY is needed
        if(mdlDebounce_getState(&operate) && mdlDebounce_getState(&ext_sil))
        {
            SMTimerFireIn(&transSTANDBY, mdlSM_cnf_DISABLE_DELAY * mdlSM_cnf_TICKS_PER_MS);
        }

        // If one of the two inputs pins is low, start ticking timer to go to STANDBY
        if(!mdlDebounce_getState(&operate) || !mdlDebounce_getState(&ext_sil))
        {
            SMTimerTick(&transSTANDBY, SM_tran((SM*)&theINV, (SMState)mdlSM_Standby));
        }
        break;

    case EXIT_ACTION:
        fullbridge_disable();
        DEBUG_PRINT("OPERATE >");
        break;

    case WHOAMI:
        // point to ID configured for this state
        result = &cfg[e_mdlSM_cnf_State__Operate].stateID;
        break;
    } // end switch

    return result;
}

//------------------------------------------------------------------------------------------------
/*!@brief   State handler for state ERROR
 *
 *@return   pointer to numerical ID configured for the this state.
 *
 *
 *\n
 */
const int* mdlSM_Error(mdlSM_INV_t *me, stateActions_t action)
{
    const int *result = 0;
    static bool attemptClearError;

    switch(action)
    {
    case ENTRY_ACTION:
        DEBUG_PRINT("> ERROR");

        // Set fault output at /FAULT_uC to low to indicate error
        mdlHAL_writePin(e_mdlHAL_cnf_PIN___FAULT_uC, LOW);

        // Set minimum time to remain in ERROR state
        //            SMTimerFireIn(&timeout, mdlSM_cnf_STAY_IN_ERROR_DELAY * mdlSM_cnf_TICKS_PER_MS);
        SMTimerFireIn(&clearERROR, mdlSM_cnf_STAY_IN_ERROR_DELAY * mdlSM_cnf_TICKS_PER_MS);
        SMTimerFireIn(&transSTANDBY, mdlSM_cnf_CLEAR_ERROR_DELAY * mdlSM_cnf_TICKS_PER_MS);

        // Flag to attempt clearing error in error module
        attemptClearError = false;
        break;

    case DO_ACTION:
        // Check if any error is flagged
        // In this way several error flags may be set
        mdlSM_checkForErrors();

        // Update operate and external SIL fault pins to update readings in case of any changes
        mdlDebounce_update(&operate);
        mdlDebounce_update(&ext_sil);

        // If errors are present, tick down timer to clear error, at the end, set flag to attempt clearing error latch
        // In case of a new error restart timer to transition to STANDBY if errors have been cleared
        if (mdlError_get(e_mdlError_cnf_ErrorFlag__OverallError))
        {
            SMTimerTick(&clearERROR, attemptClearError = true);
            SMTimerFireIn(&transSTANDBY, mdlSM_cnf_CLEAR_ERROR_DELAY * mdlSM_cnf_TICKS_PER_MS);
        }

        // Attempt to clear error after timer runs out. If flag is not cleared, restart timer to attempt clearing error flag & reset attempt flag
        if (attemptClearError == true)
        {
            // If there are no more errors, the flag will be cleared but the transition to STANDBY will not be started.
            // The CAN will indicate "no errors" but "state == ERROR". This can also serve as an indicator to flip the
            // operate switch
            mdlSM_clearAllErrors();
            if (mdlError_get(e_mdlError_cnf_ErrorFlag__OverallError))
            {
                // Restart timer to attempt to clear error. Adds delay to allow the error to be physically corrected
                attemptClearError = false;
                SMTimerFireIn(&clearERROR, mdlSM_cnf_STAY_IN_ERROR_DELAY * mdlSM_cnf_TICKS_PER_MS);
            }
        }

        // If no more errors and operate pin has been set to off, tick timer to transition to Standby state
        //            if (!mdlError_get(e_mdlError_cnf_ErrorFlag__OverallError) && !mdlDebounce_getState(&operate))
        if (!mdlError_get(e_mdlError_cnf_ErrorFlag__OverallError) && mdlHAL_readPin(e_mdlHAL_cnf_PIN__operate) == LOW)
        {
            SMTimerTick(&transSTANDBY, SM_tran((SM*)&theINV, (SMState)mdlSM_Standby));
        }

        //            if(!mdlError_get(e_mdlError_cnf_ErrorFlag__OverallError))
        //            {
        //                // On timeout, transition to STANDBY state
        ////                SMTimerTick(&timeout, SM_tran((SM*)&theINV, (SMState)mdlSM_Standby));
        //                SMTimerTick(&transSTANDBY, SM_tran((SM*)&theINV, (SMState)mdlSM_Standby));
        //
        //            }
        //
        //           /// TODO \todo PRINT MESSAGE TO SCREEN TO CLEAR FLAG IF NO ERRORS
        //            if(attemptClearError == true) // internal
        //            {
        ////                DEBUG_PRINT("Set flag");
        //                // If clear error flag set, clear errors
        //                // This comes from CAN
        //
        ////                if(clearSignal == true)
        ////                if(INV_Control.clearError == 1)
        //                mdlSM_clearAllErrors();
        //                if (mdlError_get(e_mdlError_cnf_ErrorFlag__OverallError))
        //                {
        ////                if(INV_Control.changeState == 1)
        ////                {
        ////                    mdlSM_clearAllErrors();
        //                    // Set minimum time until next clear
        //                    SMTimerFireIn(&transSTANDBY, mdlSM_cnf_CLEAR_ERROR_DELAY * mdlSM_cnf_TICKS_PER_MS);
        //                    attemptClearError = false;   // do not permit to clear error
        ////                    clearSignal = false;
        ////                    INV_Control.clearError = 0;
        ////                    INV_Control.changeState = 0;
        //                }
        //            }
        //            else
        //            {
        //                // On timeout, enable clearing error
        //                // after this time, 10s, the flag to try to clear error flag is set
        //                // cannot be shorter than 10s due to CAN communication issue
        //                SMTimerTick(&timeout, attemptClearError = true);
        //            }
        break;

    case EXIT_ACTION:
        //            INV_Control.changeState = 0;
        // TODO: RETURN _FAULT_uC TO HIGH (low for testing)
        mdlHAL_writePin(e_mdlHAL_cnf_PIN___FAULT_uC, HIGH);
        DEBUG_PRINT("ERROR >");
        break;

    case WHOAMI:
        // point to ID configured for this state
        result = &cfg[e_mdlSM_cnf_State__Error].stateID;
        break;
    } // end switch

    return result;
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

