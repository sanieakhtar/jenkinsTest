/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file mdlMonitor.c @copyright
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
/*!@file            mdlMonitor.c
 * @brief           Monitor variables against thresholds and perform a delayed
 *                  action
 *//*
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/

/*****************************************************************************/
/*! \addtogroup mdlMonitor Monitor
 *@brief  Configure variable to be monitored and their thresholds
 *
 *
 *  @{
 *****************************************************************************/


//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes
#include "inv_cnf.h"
#include "mdlMonitor.h"
//#include "../mdlNTC/mdlNTC.h"
//#include "../mdlError/mdlError.h"
#include "../mdlSM/mdlSM.h"


//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

static uint16_t count[e_mdlMonitor_cnf_CHECK__endOfList];

static mdlMonitor_cfg_Monitor_t cfg[e_mdlMonitor_cnf_CHECK__endOfList] = {
#define LOAD_MODULE_CONFIGURATION
    #include "./_config/mdlMonitor_cnf.h"
#undef  LOAD_MODULE_CONFIGURATION
};

#define MonitorEnabled(index)   (count[index] != 0xFFFF)
#define MonitorReset(index)     (count[index] = 0)
#define MonitorDisable(index)       (count[index] = 0xFFFF)

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

void mdlMonitor_call(void (*fp)(uint16_t), uint16_t arg);

    //-------------------------
    // Public Section
    //*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Initialize monitoring delay counters
 *
 *@ref      mdlMonitor_cfg_Monitor_t
 *@ref      mdlMonitor_cnf.h
 *
 *@return   none
 *\n
 *@note     none
  *\n
 */
void mdlMonitor_init(void)
{
    uint8_t i;

    // For each configured check
    for(i = 0; i < e_mdlMonitor_cnf_CHECK__endOfList; i++)
    {
        MonitorReset(i);
    }
}


//------------------------------------------------------------------------------------------------
/*!@brief   Execute all configured monitoring conditions.
 *
 *@ref      mdlMonitor_cfg_Monitor_t
 *@ref      mdlMonitor_cnf.h
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variable cfg[].
  *\n
 */
void mdlMonitor_exec(void)
{

#define MonitorCondition(type, value, threshold) \
     ((e_mdlMonitor_type__equalThreshold == type) && (value == threshold)) ||\
     ((e_mdlMonitor_type__notEqualThreshold == type) && (value != threshold)) ||\
     ((e_mdlMonitor_type__aboveThreshold == type) && (value > threshold)) ||\
     ((e_mdlMonitor_type__belowThreshold == type) && (value < threshold))

    uint8_t i;

    // For each configured monitor condition
    for(i = 0; i < e_mdlMonitor_cnf_CHECK__endOfList; i++)
    {
        // If monitored condition is true, increment and check timing counter
        if(MonitorCondition(cfg[i].type, *cfg[i].value, cfg[i].threshold))
        {
            // If monitor is enabled
            if(MonitorEnabled(i))
            {
                // If delay counter has expired, perform configured action
                if(count[i] >= cfg[i].errorDelay)
                {
                    MonitorDisable(i);
                    // Execute configured function with configured argument
                    mdlMonitor_call(cfg[i].fn, cfg[i].arg);
                }
                else
                {
                    count[i]++;     // increment delay counter
                }
            } // end if
        } // end if

        // Monitored condition is false, reset counter
        else
        {
            MonitorReset(i);
        }
    } // end for
}

//------------------------------------------------------------------------------------------------
/*!@brief   Reset the specified monitor in order to re-arm it.
 *
 *@ref      mdlMonitor_cnf_CHECK_t
 *
 *@param    i   number of configured monitor
 *
 *@note     This will reset the timer of the monitor and thus re-enable it.
 *
 *\n
 */
void mdlMonitor_reset(mdlMonitor_cnf_CHECK_t i)
{
    // If i in valid range,
    if(i < e_mdlMonitor_cnf_CHECK__endOfList)
    {
        MonitorReset(i);
    }
}


    //-------------------------
    // Private Section
    //*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Call configured function with configured argument.
 *
 *@ref      mdlMonitor_cfg_Monitor_t
 *@ref      mdlMonitor_cnf.h
 *
 *@return   none
 *\n
 *@note     Uses the configuration loaded from the config header file into the static variable cfg[].
  *\n
 */
void mdlMonitor_call(void (*fp)(uint16_t), uint16_t arg)
{
    fp(arg);
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

