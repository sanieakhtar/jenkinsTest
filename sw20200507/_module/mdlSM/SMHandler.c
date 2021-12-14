/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file SMHandler.c @copyright
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
/*!@file            SMHandler.c
 *
 * @details         TODO
 *
 *****************************************************************************/
 
/*****************************************************************************/
/*! \addtogroup mdlStatemachine State Machine
 *@brief  State Machine Handler
 *
 *  TODO
 *  
 *  @{
 *****************************************************************************/

//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=



//=============================================================================
// Includes
#include <stdbool.h>
#include "SMHandler.h"

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
    // Private Pre-declaration
    //*************************

    //-------------------------
    // Public Section
    //*************************

    //-------------------------
    // Private Section
    //*************************

// TODO ADD FUNCTION INFORMATION

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
inline static bool isTran(SM *me) {
    return (me->state != me->nextState);
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
inline static void finishTran(SM *me) {
    me->state = me->nextState;
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
void SM_init(SM *me, SMState state)
{
    me->nextState   =   state;
    me->state       =   state;
    me->state(me, ENTRY_ACTION);
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
void SM_exec(SM *me)
{
    if (isTran(me))
    {
        me->state(me, EXIT_ACTION);
        me->nextState(me, ENTRY_ACTION);
        finishTran(me);
    }
    else
    {
        me->state(me, DO_ACTION);
    }
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCTION SECTION - END
//=============================================================================


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


/******************************************************************************
 * THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 * UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 * MAY LEAD TO PROSECUTION.
 *****************************************************************************/

/** @}*/

