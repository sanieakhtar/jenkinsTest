/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLEPWM_MDLEPWM_H_
    #define MODULE_MDLEPWM_MDLEPWM_H_

/*****************************************************************************/
/*!@file mdlEPWM.h @copyright
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
/*!@file            mdlEPWM.h
 *
 * @details         Provides functions to set up the ePWM module and its
 *                  submodules.
 *****************************************************************************/

/*****************************************************************************/
/*! \addtogroup mdlEPWM EPWM
 *@brief  Configure the on-chip ePWMs including the submodules
 *
 *  Provides functions to set up the ePWM module and its submodules.
 *  @{
 *****************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlEPWM_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlEPWM_cnf_...".
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
#include "inv_cnf.h"                    // IPS configuration
#include "./_config/mdlEPWM_cnf.h"


//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//#ifndef uint8_t
//typedef uint16_t uint8_t;
//#endif

/*!@brief
* EPWM module time base counter configuration descriptor.
*
* @ref mdlEPWM_cnf.h
*/
typedef struct mdlEPWM_cfg_TB
{
  EPWM_ClockDivider         clkPrescale;                //!< EPWM clock pre-scaler (scales down the EPWMCLK)
  uint16_t                       period;                //!< timer period
  EPWM_SyncOutPulseMode     syncOutMode;                //!< pulse out mode
  bool               enablePhaseLoading;                //!< 1 = enable phase shift loading
  uint16_t                   phaseCount;                //!< phase shift count value
  bool                   enableDeadband;                //!< enable or disable deadband
  uint16_t                deadbandCount;                //!<
  EPWM_TimeBaseCountMode      countMode;                //!<
}mdlEPWM_cfg_TB_t;


/*!@brief
* EPWM module counter compare configuration descriptor.
*
* @ref mdlEPWM_cnf.h
*/
typedef struct mdlEPWM_cfg_CC
{
  uint16_t                   dutyCycleA;                //!< number of EPWMCLK ticks for CMPA
  EPWM_CounterCompareLoadMode loadModeA;                //!< shadow load mode (specify when to load CC)
  uint16_t                   dutyCycleB;                //!< number of EPWMCLK ticks for CMPB
  EPWM_CounterCompareLoadMode loadModeB;                //!< shadow load mode (specify when to load CC)
}mdlEPWM_cfg_CC_t;


/*!@brief
* EPWM module action qualifier configuration descriptor.
*
* @ref mdlEPWM_cnf.h
*/
typedef struct mdlEPWM_cfg_AQ
{
  EPWM_ActionQualifierOutputModule epwmOutput;          //!< EPWM output
  uint16_t                            actions;          //!< actions defined in EPWM_ActionQualifierEventAction may be ORed
}mdlEPWM_cfg_AQ_t;


/*!@brief
* EPWM module configuration descriptor.
*
* @ref mdlEPWM_cnf.h
*/
typedef struct mdlEPWM_cfg_EPWM
{
  uint32_t                 base;                        //!< base address of the EPWM module (EPWM1_BASE, etc.)
  mdlEPWM_cfg_TB_t           tb;                        //!< time-base submodule settings
  mdlEPWM_cfg_CC_t           cc;                        //!< counter-compare submodule settings
  mdlEPWM_cfg_AQ_t           aq;                        //!< action qualifier submodule settings
}mdlEPWM_cfg_EPWM_t;


/*!@brief
* EPWM event trigger submodule configuration descriptor.
*
* @ref mdlEPWM_cnf.h
*/
typedef struct mdlEPWM_cfg_ET
{
  uint32_t                 base;                        //!< base address of the EPWM module (EPWM1_BASE, etc.)
  uint16_t           adcSOCType;                        //!< SOC type (e.g. EPWM_SOC_A or EPWM_SOC_B)
  uint16_t            socSource;                        //!< event that triggers the SOC (e.g. EPWM_SOC_TBCTR_ZERO, EPWM_SOC_TBCTR_U_CMPA, ..)
  uint16_t           eventCount;                        //!< determines which event triggers the SOC (0=disabled, 1=1st event,..)
  bool                   enable;                        //!< 1=enable during initialization
}mdlEPWM_cfg_ET_t;


/*!@brief
* EPWM trip zone submodule configuration descriptor.
*
* @ref mdlEPWM_cnf.h
*/
typedef struct mdlEPWM_cfg_TZ
{
  uint32_t                 base;                        //!< base address of the EPWM module (EPWM1_BASE, etc.)
  uint16_t             tzSignal;                        //!< signal defined for EPWM_enableTripZoneSignals()
  EPWM_TripZoneEvent    tzEvent;                        //!< event such as "Digital Compare A event 1"
  EPWM_TripZoneAction  tzAction;                        //!< action to be performed (e.g. output low)
  uint16_t         tzForceEvent;                        //!< event to force during initialization (e.g. EPWM_TZ_FORCE_EVENT_OST), see EPWM_forceTripZoneEvent()
}mdlEPWM_cfg_TZ_t;

/*!@brief
* EPWM digital compare submodule configuration descriptor.
*
* @ref mdlEPWM_cnf.h
*/
typedef struct mdlEPWM_cfg_DC
{
  uint32_t                                      base;   //!< base address of the EPWM module (EPWM1_BASE, etc.)
  EPWM_DigitalCompareTripInput            tripSource;   //!< source to digital compare submodule (e.g. EPWM_DC_TRIP_TRIPINx or EPWM_DC_TRIP_COMBINATION)
  uint16_t                      combinationSource[6];   //!< list of signals for combination input (only relevant if tripSouce=EPWM_DC_TRIP_COMBINATION)
  EPWM_DigitalCompareType                     dcType;   //!< one of four digital compare inputs (e.g. EPWM_DC_TYPE_DCAH)
  EPWM_DigitalCompareEvent                   dcEvent;   //!< digital compare event (EPWM_DC_EVENT_1 or EPWM_DC_EVENT_2)
  EPWM_DigitalCompareEventSource       dcEventSource;   //!< filtered or unfiltered signal (e.g. EPWM_DC_EVENT_SOURCE_FILT_SIGNAL or EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL)
  uint16_t                               windowCount;   //!< filter blanking window length in TBCLK count
  EPWM_TripZoneDigitalCompareOutputEvent dcTripEvent;   //!< the event that causes Trip Zone (e.g. EPWM_TZ_EVENT_DCXL_LOW)
}mdlEPWM_cfg_DC_t;

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

void mdlEPWM_initTripZones(void);
void mdlEPWM_init(void);

bool mdlEPWM_isTripZoneFlagged(mdlEPWM_cnf_TZ_t thisTZ);
void mdlEPWM_clearTripZoneFlags(mdlEPWM_cnf_TZ_t thisTZ);
void mdlEPWM_forceTripZone(mdlEPWM_cnf_TZ_t thisTZ);

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
#endif /* MODULE_MDLEPWM_MDLEPWM_H_ */

/** @}*/

