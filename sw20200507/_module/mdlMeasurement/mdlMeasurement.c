/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file mdlMeasurement.c @copyright
 *      THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 *\n    UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE
 *\n    FILES MAY LEAD TO PROSECUTION.
 *\n
 *\n    IPT Technology GmbH
 *\n    Im Martelacker 14
 *\n    79588 Efringen-Kirchen
 *\n    Germany
 *\n    Phone:   +49 7621 662 0
 *\n    Fax:     +49 7621 662 144
 *\n    info@ipt-technology.com
 *\n    www.ipt-technology.com
 *****************************************************************************/


/*****************************************************************************/
/*!@file            mdlMeasurement.c
 * @brief           TODO description short
 *
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=

//*****************************************************************************
/*! \addtogroup mdlMeasurement Measurement
*@brief  Measurement Modul
*
*   A Detailed Description starts here.
* @{
*/
//*****************************************************************************


//=============================================================================
// Includes

#include "mdlMeasurement.h"
//#include "globals.h"
#include "device.h"
#include "../mdlADC/mdlADC.h"
#include "../mdlNTC/mdlNTC.h"

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
/*!@brief   Initialize the Measurement Module
 *
 *@return   none
 *\n
 *@note
 *\n
 */
void mdlMeasurement_init(void)
{
    // Initialize ADC modules and set up conversions to be performed
    //
    mdlADC_init();
    // Enable the on-chip temperature sensor
    //
    ASysCtl_enableTemperatureSensor();
}



//------------------------------------------------------------------------------------------------
/*!@brief   Get all measured values and update global variables
 *
 *@ref      globals.h
 *
 *@return   none
 *\n
 *@note     TODO \todo need to adapt the function mdlNTC_getTemp() as per functional spec DO501008-0152a
 *\n
 */
void mdlMeasurement_update(void)
{
//    Temp_gyr_avg =   mdlNTC_getTemp(TDK_B57703M, mdlADC_readResult(e_mdlADC_cnf_SOC__Temp_gyr_avg));
//    Temp_A       =   mdlNTC_getTemp(TDK_B57703M, mdlADC_readResult(e_mdlADC_cnf_SOC__Temp_A));
//    Temp_B       =   mdlNTC_getTemp(TDK_B57703M, mdlADC_readResult(e_mdlADC_cnf_SOC__Temp_B));
//    Temp_uC      =   mdlADC_get_Temp_uC();

    I_gyr        =   (float) (mdlMeasurement_IGYR_GAIN * mdlADC_V_REF / mdlADC_RANGE) * mdlADC_readResult(e_mdlADC_cnf_SOC__I_gyr);
    V_gyr        =   (float) (mdlMeasurement_VGYR_GAIN * mdlADC_V_REF / mdlADC_RANGE) * mdlADC_readResult(e_mdlADC_cnf_SOC__V_gyr);

    V_24V        =   (float) (mdlMeasurement_V24V_GAIN * mdlADC_V_REF / mdlADC_RANGE) * mdlADC_readResult(e_mdlADC_cnf_SOC__V_24V_avg);
    V_bus        =   (float) (mdlMeasurement_VBUS_GAIN * mdlADC_V_REF / mdlADC_RANGE) * mdlADC_readResult(e_mdlADC_cnf_SOC__V_bus);
    I_inv        =   (float) (mdlMeasurement_IINV_GAIN * mdlADC_V_REF / mdlADC_RANGE) * mdlADC_readResult(e_mdlADC_cnf_SOC__I_inv);
//    Ph_inv       =   (float) (mdlMeasurement_PHINV_GAIN * mdlADC_V_REF / mdlADC_RANGE) * mdlADC_readResult(e_mdlADC_cnf_SOC__Ph_inv);
}

    //-------------------------
    // Private Section
    //*************************


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

