/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLADC_MDLADC_H_
#define MODULE_MDLADC_MDLADC_H_

/*****************************************************************************/
/*!@file mdlADC.h @copyright
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
/*!@file            mdlADC.h
 *
 * @details         Provides functions for setup of the ADC modules and the
 *                  conversions (SOCs) to be performed.
 *                  The settings specific for an ADC module are stored in
 *                  mdlADC_cfg_ADC_t those for the SOCs in mdlADC_cfg_SOC_t.
 *
 *                  A configured conversion may be started by software and the
 *                  result can subsequently be read.
 *****************************************************************************/

/*****************************************************************************/
/*! \addtogroup mdlADC ADC
 *@brief  Configure on-chip ADCs including SOCs
 *
 *  This module provides functions for setup of the ADC modules and the
 *  conversions (SOCs) to be performed.
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
#include "driverlib.h"
#include "./_config/mdlADC_cnf.h"
//#include "../mdlNTC/mdlNTC.h"
//#include "../mdlHAL/mdlHAL.h"

//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//#ifndef uint8_t
//    typedef uint16_t uint8_t;
//#endif

/*!@brief
* ADC module configuration descriptor.
*
* @ref mdlADC_cnf.h
*/
typedef struct mdlADC_cfg_ADC
{
  uint32_t                        base;     //!< base address of the ADC module (ADCA_BASE, etc.)
  ADC_ClkPrescale          clkPrescale;     //!< ADC clock pre-scaler (scales down the SYSCLK)
  ADC_ReferenceVoltage      refVoltage;     //!< internal reference voltage (ADC_REFERENCE_2_5V or ADC_REFERENCE_3_3V)
  ADC_PulseMode              pulseMode;     //!< pulseMode parameter (ADC_PULSE_END_OF_ACQ_WIN = early interrupt, ADC_PULSE_END_OF_CONV = late)
  ADC_PriorityMode        priorityMode;     //!< priority mode of the SOCs
  bool                     burstEnable;     //!< burst enable flag
  ADC_Trigger             burstTrigger;     //!< event that will trigger a burst of conversions to start
  uint8_t                    burstSize;     //!< the number of SOCs converted during a burst sequence (1..16, where 1=1 SOC converted)
}mdlADC_cfg_ADC_t;


/*!@brief
* ADC SOC configuration descriptor.
*
* @ref mdlADC_cnf.h
*/
typedef struct mdlADC_cfg_SOC
{
  mdlADC_cnf_ADC_t           adcNumber;     //!< number of used ADC module
  ADC_Channel                  channel;     //!< channel to be sampled
  ADC_SOCNumber              socNumber;     //!< number of SOC (0..15) to be configured
  ADC_Trigger                  trigger;     //!< event that will trigger the SOC
  ADC_IntNumber              intNumber;     //!< number of interrupt to be configured (0xFF = no interrupt)
// commented, because all SOCs use the same acquistion window length anyway
//  uint32_t                sampleWindow;   //!< acquistion window length
}mdlADC_cfg_SOC_t;


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

void        mdlADC_init(void);
void        mdlADC_startConversion(mdlADC_cnf_SOC_t thisSOC);
uint16_t    mdlADC_readResult(mdlADC_cnf_SOC_t thisSOC);


// Return on-chip temperature
// todo should be moved to measurement module
static inline float mdlADC_get_Temp_uC()
{
    return ADC_getTemperatureC(mdlADC_readResult(e_mdlADC_cnf_SOC__Temp_uC), mdlADC_V_REF);
}


/* UNUSED
 *
// Return boost converter voltage
static inline float mdlADC_get_V_boost()
{
	return (mdlADC_VBOOST_GAIN * mdlADC_V_REF / mdlADC_12BIT_RANGE) * mdlADC_readResult(e_mdlADC_cnf_SOC__Vboost);
}

// Return buck converter voltage
static inline float mdlADC_get_V_buck()
{
	return (mdlADC_VBUCK_GAIN * mdlADC_V_REF / mdlADC_12BIT_RANGE) * mdlADC_readResult(e_mdlADC_cnf_SOC__Vbuck);
}

static inline float mdlADC_get_V_15()
{
	return (mdlADC_V15_GAIN * mdlADC_V_REF / mdlADC_12BIT_RANGE) * mdlADC_readResult(e_mdlADC_cnf_SOC__V15);
//}

//// Return NTC1 temperature in °C
//static inline float mdlADC_get_Temp_1()
//{
//    // Conversion function assumes 3.3V ADC reference
//    return mdlNTC_getTemp(epcos8016, mdlADC_readResult(e_mdlADC_cnf_SOC__Temp1));
//}
//
//// Return NTC2 temperature in °C
//static inline float mdlADC_get_Temp_2()
//{
//    // Conversion function assumes 3.3V ADC reference
//    return mdlNTC_getTemp(epcos8016, mdlADC_readResult(e_mdlADC_cnf_SOC__Temp2));
//}
//
//// Return NTC3 temperature in °C
//static inline float mdlADC_get_Temp_3()
//{
//    // Conversion function assumes 3.3V ADC reference
//    return mdlNTC_getTemp(epcos8016, mdlADC_readResult(e_mdlADC_cnf_SOC__Temp3));
//}
//// Return NTC4 temperature in °C
//static inline float mdlADC_get_Temp_4()
//{
//    // Conversion function assumes 3.3V ADC reference
//    return mdlNTC_getTemp(epcos8016, mdlADC_readResult(e_mdlADC_cnf_SOC__Temp4));
//}
 *
 */


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
#endif /* MODULE_MDLADC_MDLADC_H_ */

/** @}*/
