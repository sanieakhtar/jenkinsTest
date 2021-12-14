/**
 * \addtogroup Modules
 *  @{
 */

#ifndef SM_SMTIMER_H_
#   define SM_SMTIMER_H_

/*****************************************************************************/
/*!@file SMTimer.h @copyright
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
/*!@file            SMTimer.h
 *
 * @details         This is the implementation of a timer module that is used
 *                  to supplement the state machine handler and the execution
 *                  of the state machine transitions.
 *
 *****************************************************************************/

/*****************************************************************************/
/*! \addtogroup mdlStatemachine State Machine
 *@brief  Timer module written for state machine functional execution and
 *        transition handling.
 *
 *  @{
 *****************************************************************************/

#include <stdint.h>
#include <stdbool.h>


/*!@brief
 * New type definition for the timer object, holds the current and reload values of the timer
 */
typedef struct SMTimer_st {
    int32_t counter;
    int32_t reload;
}SMTimer;


//------------------------------------------------------------------------------------------------
/*!@brief   Initialize the timer object to initial values. Inline function.
 *
 *@param    SMTimer Pointer to timer object
 *
 *@return   none
 *\n
 */
inline void SMTimerInitialize(SMTimer *me)
{
    me->counter =  0;
    me->reload  =  0;
}


//------------------------------------------------------------------------------------------------
/*!@brief   \a <Load the timer with values at which to fire regularly. Function unclear as function
 *          is not in use.>
 *
 *@param    SMTimer Pointer to timer object
 *@param    tm      Value at which timer should fire
 *
 *@return   none
 *\n
 *@note     \b <Not being used>
 *\n
 */
inline void SMTimerFireEvery(SMTimer *me, uint32_t tm)
{
    me->counter = tm;
    me->reload  = tm;
}


//------------------------------------------------------------------------------------------------
/*!@brief   Initialize the timer to starting values. Timer counts down to zero, not up to a value.
 *          Inline function.
 *
 *@param    SMTimer Pointer to timer object.
 *@param    tm      Starting value of the timer
 *
 *@return   none
 *\n
 */
inline void SMTimerFireIn(SMTimer *me, uint32_t tm)
{
    me->counter = tm;
    me->reload  =  0;
}


//------------------------------------------------------------------------------------------------
/*!@brief   Checks if the timer has finished counting down (called "having been fired") by testing
 *          if the counter parameter is equal to zero. Inline function.
 * 
 *@param    SMTimer Pointer to timer object.
 *
 *@return   bool    True if the timer has finished counting down
 *@return   bool    False if the timer is still counting down
 *\n
 */
inline bool SMTimerHasFired(SMTimer *me)
{
    return (me->counter == 0);
}


//------------------------------------------------------------------------------------------------
/*!@brief   Checks if the timer is inactive or not by testing the value of the counter parameter.
 *          Inline function.
 *
 *@param    SMTimer Pointer to timer object.
 *
 *@return   bool    True if the timer is inactive
 *@return   bool    False if the timing is active
 *\n
 */
inline bool SMTimerIsInactive(SMTimer *me)
{
    return (me->counter < 0);
}


//------------------------------------------------------------------------------------------------
/*!@brief   Reload the timer counter to the value of the reload parameter. Inline function.
 *
 *@param    SMTimer Pointer to timer object.
 *
 *@return   none
 *\n
 */
inline void SMTimerReload(SMTimer *me)
{
    if (me->reload != 0) {
        me->counter = me->reload;
    }
}


//------------------------------------------------------------------------------------------------
/*!@brief   Count down timer by one. Inline function.
 *
 *@param    SMTimer Pointer to timer object.
 *
 *@return   none
 *\n
 */
inline void SMTimerDecrement(SMTimer *me)
{
    me->counter--;
}


//------------------------------------------------------------------------------------------------
/*!@brief   Cancel timer object. Inline function.
 *
 *@param    SMTimer Pointer to timer object.
 *
 *@return   none
 *
 *@note     SHOULD ONLY BE USED WHEN MULTIPLE TIMER OBJECTS HAVE BEEN DECLARED. This function will
 *@note     stop the execution/counting down of the timer object passed. If only one object is
 *@note     being used for multiple actions, calling this function will create unforeseen outcomes.
 *\n
 */
inline void SMTimerCancel(SMTimer *me)
{
    me->counter =   -1;
    me->reload  =    0;
}


//------------------------------------------------------------------------------------------------
/*!@brief   If the state machine timer is running, ticks the timer by one i.e. decreases the value
 *          of the counter by one. If the timer has run out, executes the command passed in as the
 *          second parameter. Conditions:
 *
 *          - if the timer is not running, do nothing
 *          - if timer has run out, execute action and reload timer
 *          - if timer is running and has not run out, decrement timer by one
 *
 *@param    macro_tmr       pointer to timer object containing current and reset value of timer
 *@param    macro_action    action to be carried out once the timer has run out
 *
 *@return   none
 *\n
 */
#define SMTimerTick(macro_tmr, macro_action)\
    do {\
        if (SMTimerIsInactive(macro_tmr)) {\
            continue;\
        }\
        if (SMTimerHasFired(macro_tmr)) {\
            (macro_action);\
            SMTimerReload(macro_tmr);\
        }\
        SMTimerDecrement(macro_tmr);\
    } while (0)


/*****************************************************************************/
/*! @}
 *  Close the Doxygen group.
 *****************************************************************************/

#endif /* SM_SMTIMER_H_ */


/******************************************************************************
 * THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 * UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 * MAY LEAD TO PROSECUTION.
 *****************************************************************************/

/** @}*/

