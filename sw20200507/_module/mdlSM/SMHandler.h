/** \addtogroup Modules
 *  @{
 */

#ifndef SM_HANDLER_H_
#   define SM_HANDLER_H_

/*****************************************************************************/
/*!@file SMHandler.h @copyright
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
/*!@file            SMHandler.h
 *
 * @details         Declares support structures for the implementation of the
 *                  state machine handler e.g. operation enumerators for each
 *                  state, type definitions for the state machine and function
 *                  declarations for state machine execution
 *
 *****************************************************************************/

/*****************************************************************************/
/*! \addtogroup mdlStatemachine State Machine
 *@brief  State machine handler support structures
 *  
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


//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes
#include <stdint.h>
#include <stdio.h>

//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


/*!@brief
 * List of operation actions of each state
 */
typedef enum stateActions {
    ENTRY_ACTION = 1,
    EXIT_ACTION,
    DO_ACTION,
    WHOAMI
}stateActions_t;


/*!@brief
 * Define the structure for the state machine state identifying parameter.
 *
 * @param   *state      pointer to current state and current state operation
 * @param   *nextState  pointer to the next state to transition to and next
 *                      operation to execute
 */
struct SM_st {
    const int* (*state)(struct SM_st *, stateActions_t);
    const int* (*nextState)(struct SM_st *, stateActions_t);
};


/*!@brief
 * Define state machine structure SM_st as type SM
 */
typedef struct SM_st SM;


/*!@brief
 * /// todo TODO
 */
typedef const int* (*SMState)(SM*, stateActions_t);


// Function declarations

void SM_init(SM *me, SMState state);
void SM_exec(SM *me);


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


/*!@brief   Determines which is the next state to the system should transition
 *
 *@param    *me     pointer to current state machine object
 *@param    state   next state to which the state machine should transition
 *
 *@return   none
 *
 *@note     Inline function
 *\n
 */
inline void SM_tran(SM *me, SMState state)
{
    me->nextState = state;
}


//-------------------------------------------------------------------------------
/*!@brief   Determine the current state of the system. The function call returns
 *          an integer that corresponds to @mdlSM_cnf_States_t to determine
 *          what the current state is
 *
 *@param    *me     pointer to current state machine object
 *
 *@return   const   returns an integer respective to current state
 *@
 *@note     Inline function
 *\n
 */
inline const int* SM_getState(SM *me)
{
    return me->state(me, WHOAMI);
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCTION SECTION - END
//=============================================================================


/*****************************************************************************/
/*! @}
 *  Close the Doxygen group.
 *****************************************************************************/

#endif /* SM_SMHANDLER_H_ */


/******************************************************************************
 * THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 * UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 * MAY LEAD TO PROSECUTION.
 *****************************************************************************/

/** @}*/

