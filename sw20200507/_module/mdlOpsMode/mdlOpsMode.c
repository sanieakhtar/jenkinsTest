/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file mdlOpsMode.c @copyright
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
/*!@file            mdlOpsMode.c
 * @brief           Determine current operating mode of the system
 *//*
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes
#include <string.h>
#include <stdio.h>
#include "mdlOpsMode.h"
#include "_module/mdlHAL/mdlHAL.h"

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
/*!@brief   Initialize the  operation mode module.
 *
 *
 *@return   none
 *\n
 *@note     Calls mdlOpsMode_getMode() to initialize the global OpsMode module
 *\n
 */
void mdlOpsMode_init(void)
{
    mdlOpsMode_getMode();           //calling the getMode function initializes the operation mode

}

//------------------------------------------------------------------------------------------------
/*!@brief   Read GPIO33 & GPIO34 to determine ops mode
 *
 *@ref
 *
 *@param
 *
 *@return   operation mode mdlOpsMode_cnf_Mode_t
 *\n
 *@note     none
 *\n
 */
mdlOpsMode_cnf_Mode_t mdlOpsMode_getMode(void)
{
    uint32_t val1, val2;
    val1 = mdlHAL_readPin(e_mdlHAL_cnf_PIN__OPS_Mode_SelectionA);
    val2 = mdlHAL_readPin(e_mdlHAL_cnf_PIN__OPS_Mode_SelectionB);

    if (val1 == 0)
    {
        OPS_Mode = e_mdlOpsMode_cnf_Mode_Development;
    }
    else if (( val1 == 1) && ( val2 == 0))
    {
        OPS_Mode = e_mdlOpsMode_cnf_Mode_Test;
    }
    else if (( val1 == 1) && ( val2 == 1))
    {
        OPS_Mode = e_mdlOpsMode_cnf_Mode_Field;
    }
    else
    {
        OPS_Mode = e_mdlOpsMode_cnf_Mode_Not_Supported;
    }

  return OPS_Mode;
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
