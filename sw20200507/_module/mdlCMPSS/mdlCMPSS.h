/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLCMPSS_MDLCMPSS_H_
    #define MODULE_MDLCMPSS_MDLCMPSS_H_

/*****************************************************************************/
/*!@file mdlCMPSS.h @copyright
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
/*!@file            mdlCMPSS.h
 *
 * @details         Configure the comparators of the analog subsystem.
 *****************************************************************************/


/*****************************************************************************/
/*! \addtogroup mdlCMPSS Comparators
 *@brief  Configure on-chip comparators
 *
 *  This module provides functions to configure the comparators of the 
 *  analog subsystem.
 *  @{
 *****************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlCMPSS__..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlCMPSS_cnf_...".
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
//#include "globals.h"  // added through measurement.h
#include "inv_cnf.h"
#include "../mdlADC/mdlADC.h"
#include "../mdlMeasurement/mdlMeasurement.h"
#include "./_config/mdlCMPSS_cnf.h"

//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*!@brief
 * CMPSS module configuration descriptor.
 *
 * @ref mdlCMPSS_cnf.h
 */
typedef struct mdlCMPSS_cfg_CMPSS
{
  uint32_t                         base;    //!< base address of the CMPSS module (CMPSSx_BASE, x=1..8)
  mdlCMPSS_comparator_t      comparator;    //!< selects COMPH or COMPL for configuration
  uint16_t                       config;    //!< comparator configuration (CMPSS_INSRC_DAC/CMPSS_INSRC_PIN may be ORed with CMPSS_INV_INVERTED or CMPSS_OR_ASYNC_OUT_W_FILT)
//  uint16_t                 DACinitValue;    //!< DAC initial value
  float                       tripLimit;    //!< Trip limit in volts/amps
  float                            gain;    //!< Trip gain - varies according to the trip being set
  uint16_t                    DACsource;    //!< select as source for DAC value either the shadow or the ramp register (CMPSS_DACSRC_SHDW / CMPSS_DACSRC_RAMP)
  uint16_t                 decrementVal;    //!< value to be subtracted from DAC value each system clock cycle
  uint16_t                   pwmSyncSrc;    //!< number of the PWMSYNC source to reset the ramp generator (e.g. 2=PWMSYNC2)
  uint16_t               samplePrescale;    //!< filter clock prescaler (1..1024).
  uint16_t                 sampleWindow;    //!< filter sample window size (0..32)
  uint16_t                    threshold;    //!< filter threshold (window/2+1 .. window)
  uint16_t                      outputs;    //!< output signals CTRIP (to ePWM X-Bar) and CTRIPOUT (to output X-Bar)
}mdlCMPSS_cfg_CMPSS_t;


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

void mdlCMPSS_init(void);
bool mdlCMPSS_isCompLatched(mdlCMPSS_cnf_CMPSS_t thisComp);
bool mdlCMPSS_isErrorStillPresent(mdlCMPSS_cnf_CMPSS_t thisComp);
void mdlCMPSS_clearCompLatch(mdlCMPSS_cnf_CMPSS_t thisComp);
void mdlCMPSS_setMaxRampValue(mdlCMPSS_cnf_CMPSS_t thisCMPSS, uint16_t value);
void mdlCMPSS_deinit_development(void);
uint16_t mdlCMPSS_DACinitValue(float tripValue, float gain);
void mdlCMPSS_DACvalueUpdate(float tripValueUpdate[]);

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
#endif /* MODULE_MDLCMPSS_MDLCMPSS_H_ */

/** @}*/

