/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file mdlError.c @copyright
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
/*!@file            mdlError.c
 * @brief           Manages a list of errors.
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
#include "mdlError.h"



//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

static mdlError_cfg_ErrorFlag_t error[e_mdlError_cnf_ErrorFlag__endOfList] = {
#define LOAD_MODULE_CONFIGURATION
#include "./_config/mdlError_cnf.h"
#undef  LOAD_MODULE_CONFIGURATION
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


//-------------------------
// Public Section
//*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Initialize error module.
 *
 *@ref      mdlError_cfg_ErrorFlag_t
 *@ref      mdlError_cnf.h
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variable error[].
 *\n
 */
void mdlError_init(void)
{
    uint8_t i;

    error[e_mdlError_cnf_ErrorFlag__OverallError].code = 0;              // reset overall error code

    // For each configured error flag
    for(i = 0; i < e_mdlError_cnf_ErrorFlag__endOfList; i++)
    {
        // clear error flag
        error[i].flagged = 0;

        // reset error counter
        error[i].count = 0;

    }// end for
}


//------------------------------------------------------------------------------------------------
/*!@brief   Get error flag.
 *
 *@ref      mdlError_cfg_ErrorFlag_t
 *
 *@param    i   number of error flag
 *
 *@return   true if error flag set, otherwise false.
 *\n
 *@note     TODO: Is this used anywhere?? Refactor
 *\n
 */
bool mdlError_get(mdlError_cnf_ErrorFlag_t i)
{
    // If i not in valid range, exit.
    if(i >= e_mdlError_cnf_ErrorFlag__endOfList)
    {
        return false;
    }
    else
    {
        return error[i].flagged;
    }
}


//------------------------------------------------------------------------------------------------
/*!@brief   Get error code.
 *
 *@ref      mdlError_cfg_ErrorFlag_t
 *
 *
 *@return   Current error code (i.e. code of the error that occurred first).
 *\n
 *@note     none
 *\n
 */
uint16_t mdlError_getErrorCode(void)
{
    return error[e_mdlError_cnf_ErrorFlag__OverallError].code;
}


//------------------------------------------------------------------------------------------------
/*!@brief   Get error enable flag.
 *
 *@ref      mdlError_cfg_ErrorFlag_t
 *
 *@param    i   number of error flag
 *
 *@return   true if error enabled, otherwise false.
 *\n
 *@note     none
 *\n
 */
bool mdlError_isEnabled(mdlError_cnf_ErrorFlag_t i)
{
    // If i not in valid range, exit.
    if(i >= e_mdlError_cnf_ErrorFlag__endOfList)
    {
        return false;
    }
    else
    {
        return error[i].enabled;
    }
}


//------------------------------------------------------------------------------------------------
/*!@brief   Set error flag.
 *
 *@ref      mdlError_cfg_ErrorFlag_t
 *
 *@param    i   number of error flag
 *
 *@return   true, if overall error enabled AND error number i enabled AND
 *          error number i not yet flagged and sets error number i and
 *          ovrerall error flag
 *\n
 *@note     none
 *\n
 */
bool mdlError_set(mdlError_cnf_ErrorFlag_t i)
{
#ifdef DEBUG
    char text[14];
#endif

    // If i not valid, exit.
    if((e_mdlError_cnf_ErrorFlag__OverallError == i) || (i >= e_mdlError_cnf_ErrorFlag__endOfList))
    {
        return false;
    }

    // If errors enabled AND
    // error no. i enabled AND
    // error no. i not flagged, flag error no. i
    if(error[e_mdlError_cnf_ErrorFlag__OverallError].enabled && error[i].enabled && !error[i].flagged)
    {
        error[i].flagged = true;        // set error flag
        if(error[i].count != ~0x0)
        {
            error[i].count++;           // increment error count
        }

#ifdef DEBUG
        // Limit length of debug message to 14
        sprintf(text, "F%04u-", error[i].code);
        strncat(text, error[i].msg, mdlError_cnf_MSG_LEN);
        DEBUG_PRINT(text);
#endif
        // If overall error not yet flagged, set overall error flag
        //if(!error[e_mdlError_cnf_ErrorFlag__OverallError].flagged)
        if(error[e_mdlError_cnf_ErrorFlag__OverallError].code == 0)
        {
            error[e_mdlError_cnf_ErrorFlag__OverallError].flagged = true;            // set overall error flag
            error[e_mdlError_cnf_ErrorFlag__OverallError].code = error[i].code;      // save error code to overall error

            strncpy(error[e_mdlError_cnf_ErrorFlag__OverallError].msg, error[i].msg, mdlError_cnf_MSG_LEN); // set overall error msg

            if(error[e_mdlError_cnf_ErrorFlag__OverallError].count != ~0x0)
            {
                error[e_mdlError_cnf_ErrorFlag__OverallError].count++;           // increment overall error count
            }

#ifdef DEBUG
            // Limit length of debug message to 14
            sprintf(text, "E%04u-", error[e_mdlError_cnf_ErrorFlag__OverallError].code);
            strncat(text, error[e_mdlError_cnf_ErrorFlag__OverallError].msg, mdlError_cnf_MSG_LEN);
            DEBUG_PRINT(text);
#endif
        }
        return true;
    }
    return false;
}


//------------------------------------------------------------------------------------------------
/*!@brief   Clear error flag.
 *
 *@ref      mdlError_cfg_ErrorFlag_t
 *
 *@param    flag   number of error flag
 *
 *@return   none
 *\n
 *@note     none
 *\n
 */
void mdlError_clear(mdlError_cnf_ErrorFlag_t flag)
{
    uint8_t i;

#ifdef DEBUG
    char text[15];
#endif

    // If i not valid, exit.
    if((flag == e_mdlError_cnf_ErrorFlag__OverallError) || (flag >= e_mdlError_cnf_ErrorFlag__endOfList))
    {
        return;
    }

    // If error flagged, clear it
    if(error[flag].flagged)
    {
        error[flag].flagged = false;       // clr error flag

#ifdef DEBUG
        // Limit length of debug message to 14
        sprintf(text, "C%04u-", error[flag].code);
        strncat(text, error[flag].msg, mdlError_cnf_MSG_LEN);
        DEBUG_PRINT(text);
#endif

        // If no more error flags, clear also overall error flag.
        // If further flags set, update error code.
        // For each configured error flag
        for(i = 1; i < e_mdlError_cnf_ErrorFlag__endOfList; i++)
        {
            // If error no. i flagged,
            if(error[i].flagged)
            {
                break;
            }

        }// end for

        // If no more errors
        if(e_mdlError_cnf_ErrorFlag__endOfList == i)
        {
            error[e_mdlError_cnf_ErrorFlag__OverallError].flagged = false;       // clr overall error flag
            error[e_mdlError_cnf_ErrorFlag__OverallError].code = 0;              // reset overall error code
        }
        // If error no. i newly flagged
        else if(error[e_mdlError_cnf_ErrorFlag__OverallError].code != error[i].code)
        {
            error[e_mdlError_cnf_ErrorFlag__OverallError].flagged = true;            // set overall error flag
            error[e_mdlError_cnf_ErrorFlag__OverallError].code = error[i].code;      // set overall error code
            if(error[e_mdlError_cnf_ErrorFlag__OverallError].count != ~0x0)
            {
                error[e_mdlError_cnf_ErrorFlag__OverallError].count++;               // increment error count
            }
            strncpy(error[e_mdlError_cnf_ErrorFlag__OverallError].msg, error[i].msg, mdlError_cnf_MSG_LEN); // set overall error msg
#ifdef DEBUG
            // Limit length of debug message to 14
            sprintf(text, "E%03u-", error[e_mdlError_cnf_ErrorFlag__OverallError].code);
            strncat(text, error[e_mdlError_cnf_ErrorFlag__OverallError].msg, mdlError_cnf_MSG_LEN);
            DEBUG_PRINT(text);
#endif
        }
    }
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

