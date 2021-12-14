/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file mdlDebounce.c @copyright
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
/*!@file            mdlDebounce.c
 * @brief           Functions to debounce a signal from an input pin.
 *//*
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes
#include "_module/mdlHAL/mdlHAL.h"
#include "mdlDebounce.h"


//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

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

//------------------------------------------------------------------------------------------------
/*!@brief   Initialize debouncing of the input.
 *
 *@param    *me         pointer to the input object
 *@param     pin        input pin
 *
 *@return   none
 *\n
 *@note     none
 *\n
 */
void mdlDebounce_init(mdlDebounce_Input_t *me, mdlHAL_cnf_PIN_t pin)
{
    me->pin = pin;                          // save specified input pin
    me->changed = false;                    // reset var
    me->state = mdlHAL_readPin(me->pin);    // save the current state as the debounced state
}

//------------------------------------------------------------------------------------------------
/*!@brief   Return debounced state of input.
 *
 *@param    *me         pointer to the input object
 *
 *@return   none
 *\n
 *@note     none
 *\n
 */
bool mdlDebounce_getState(mdlDebounce_Input_t *me)
{
    return me->state;
}

//------------------------------------------------------------------------------------------------
/*!@brief   Update the state of the input
 *
 *@param    *me         : pointer to the input object
 *
 *@return   none
 *\n
 *@note     none
 *\n
 */
void mdlDebounce_update(mdlDebounce_Input_t *me)
{
    bool new_state;

    // read the current input signal
    new_state = (bool) mdlHAL_readPin(me->pin);

    // if no change, reset counter and var changed
    if(me->state == new_state)
    {
        me->changed = false;

        // if debounced state high, reset count to mdlDebounce_cnf_HIGH_TO_LOW_TIME
        if(me->state)
        {
            me->count = (mdlDebounce_cnf_HIGH_TO_LOW_TIME * mdlDebounce_cnf_TICKS_PER_MS);
        }
        // if debounced state low, reset count to mdlDebounce_cnf_LOW_TO_HIGH_TIME
        else
        {
            me->count = (mdlDebounce_cnf_LOW_TO_HIGH_TIME * mdlDebounce_cnf_TICKS_PER_MS);
        }
    }
    // change of state detected
    else
    {
        me->count--;        // decrement counter

        // if counter expired, update the state
        if(!(me->count))
        {
            me->changed = true;         // set flag
            me->state = new_state;      // update debounced state to new state

            // if debounced state high, reset count to mdlDebounce_cnf_HIGH_TO_LOW_TIME
            if(me->state)
            {
                me->count = (mdlDebounce_cnf_HIGH_TO_LOW_TIME * mdlDebounce_cnf_TICKS_PER_MS);
            }
            // if debounced state low, reset count to mdlDebounce_cnf_LOW_TO_HIGH_TIME
            else
            {
                me->count = (mdlDebounce_cnf_LOW_TO_HIGH_TIME * mdlDebounce_cnf_TICKS_PER_MS);
            }
        } // end if
    } // end else
}

    //-------------------------
    // Private Section
    //*************************



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCTION SECTION - END
//=============================================================================


/******************************************************************************
 * THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 * UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 * MAY LEAD TO PROSECUTION.
 *****************************************************************************/

/** @}*/

