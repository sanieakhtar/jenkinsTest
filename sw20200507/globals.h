/**
 * \addtogroup Core
 *  @{
 */

#ifndef GLOBALS_H_
#   define GLOBALS_H_

/*****************************************************************************/
/*!@file globals.h @copyright
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
/*
 *
 * @details         TODO long_description.
 *****************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "TODO namingConvention_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "TODO namingConvention _...".
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
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "inv_cnf.h"
#include "_module/mdlSCI/mdlSCI.h"
#include "_module/mdlNTC/mdlNTC.h"
#include "_module/mdlOpsMode/_config/mdlOpsMode_cnf.h"


//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#ifdef GLOBALS
#   define EXTERN   /* nothing */
#   define INITIALIZE(...)   = __VA_ARGS__
#else
#   define EXTERN      extern
#   define INITIALIZE(...)
#endif  /* Define variables */


//// Bit operation macros
//#define SETBIT(ADDRESS, BIT)    (ADDRESS |= (1 << BIT))
//#define CLEARBIT(ADDRESS, BIT)  (ADDRESS &= ~(1 << BIT))
//#define TESTBIT(ADDRESS, BIT)   (ADDRESS & (1 << BIT))

// Write the string "\n\r msg" to the serial port SCI-B.
// NOTE: Use do { ... } while(0) construct here is to enable inserting this
//       block into other statements, while preserving the syntax with ";"
// NOTE: Limit no. of chars to 16, so everything will fit into the SCI modules
//       FIFO.
//
EXTERN char txt_string[20];
#define TERMINAL_PRINT(msg) \
    do \
    { \
        sprintf(txt_string, "\n\r"); \
        strncat(txt_string, msg, 16); \
        SCI_writeCharArray(SCIB_BASE, (uint16_t*)txt_string, 16); \
    } \
    while(0)


// Write the string "\n\r msg" to the serial port e_mdlSCI_cnf_SCI__debug (see mdlSCI_cnf.h).
// NOTE: Use do { ... } while(0) construct here is to enable inserting this
//       block into other statements, while preserving the syntax with ";"
// NOTE: Limit no. of chars to 16, so everything will fit into the SCI modules
//       FIFO.
//
#ifdef DEBUG
#define DEBUG_PRINT(msg) \
    do { \
        sprintf(txt_string, "\n\r"); \
        strncat(txt_string, msg, strlen(msg)); \
        mdlSCI_writeCharArray(e_mdlSCI_cnf_SCI__debug, (uint16_t*)txt_string, strlen(txt_string)); \
    } while(0)



/* Alternative to line mdlSCI_writeCharArray(...), using the software FIFO
// Write the debug string "\n\r msg" to the transmit buffer and then transmit
// through debug serial interface.

// NOTE: A buffer of that name must have been configured in mdlFIFO.
//       A serial interface of that name must have been configure in mdlSCI.
        mdlFIFO_write((uint8_t*) txt_string, strlen(txt_string), e_mdlFIFO_cnf_buf__transmit); \
        mdlSCI_transmit(e_mdlFIFO_cnf_buf__transmit, e_mdlSCI_cnf_SCI__debug); \
 */
#else
    #define DEBUG_PRINT(msg)
#endif




/*
 * THESE MACROS ARE USED IN THE FIFO MODULE
 * FIFO MODULE IS NOT USED
 * MACROS NOT NEEDED
//
// Macros to disable interrupts when entering critical section
// and enable interrupts when exiting critical sections
// NOTE: Use do { ... } while(0) construct here is to enable inserting this block
//       into other statements, while preserving the syntax with ";"
//
EXTERN volatile uint16_t SR_lock      INITIALIZE(0x0000u);

#define EnterCritical() \
  do {\
    if (++SR_lock == 1u) {\
      DINT;\
    }\
  } while(0)


#define ExitCritical() \
  do {\
    if (--SR_lock == 0u) {\
      EINT;\
    }\
  } while(0)
*/



// Flag manipulation macros
#define SETFLAG(ADDRESS, MASK) (ADDRESS |= MASK)
#define CLEARFLAG(ADDRESS, MASK) (ADDRESS &= ~MASK)


//EXTERN uint16_t EnableFlags             INITIALIZE(0);      //!< Various flags for debugging

/*!@brief
 * Various enable flags for diagnosis.
 */
enum global_enableFlag
{
    e_global_enableFlag__fullbridgePWM  = 0x0001,
    e_global_enableFlag__fan            = 0x0002,
    e_global_enableFlag__CLA_Control    = 0x0004,
    e_global_enableFlag__spare0         = 0x0008,
    e_global_enableFlag__spare1         = 0x0010,
    e_global_enableFlag__spare2         = 0x0020,
    e_global_enableFlag__spare3         = 0x0040,
    e_global_enableFlag__spare4         = 0x0080,
    e_global_enableFlag__spare5         = 0x0100,
    e_global_enableFlag__spare6         = 0x0200,
    e_global_enableFlag__spare7         = 0x0400,
    e_global_enableFlag__spare8         = 0x0800,
    e_global_enableFlag__spare9         = 0x1000,
    e_global_enableFlag__spare10        = 0x2000,
    e_global_enableFlag__spare11        = 0x4000,
    e_global_enableFlag__spare12        = 0x8000,
};


///*!@brief
// * voltage supply/bus trips that are configurable on the go
// */
//typedef enum update_VTrips
//{
//    VTrips_starter = -1,
//    update_VsupplyTripMax,         //!< trip on supply voltage > DACL output
//    update_VsupplyTripMin,         //!< trip on supply voltage < DACL output
//    update_VbusTripMax,            //!< trip on bus voltage > DACH output
//    update_VbusTripMin,            //!< trip on bus voltage < DACL output
//    update_VendOfList
//}update_VTrips_t;


//
// Analog readings
//

/*!@brief
 * Analog readings taken from the system.
 */

// Analog temperatures
EXTERN float Temp_A                     INITIALIZE(ABSOLUTE_ZERO);  //!< NTC
EXTERN float Temp_B                     INITIALIZE(ABSOLUTE_ZERO);  //!< NTC
EXTERN float Temp_gyr                   INITIALIZE(ABSOLUTE_ZERO);  //!< NTC
EXTERN float Temp_gyr_avg               INITIALIZE(ABSOLUTE_ZERO);  //!< NTC
EXTERN float Temp_uC                    INITIALIZE(ABSOLUTE_ZERO);  //!< on-chip temperature
EXTERN float Temp_max                   INITIALIZE(ABSOLUTE_ZERO);  //!< on-chip temperature

// DC voltages
//EXTERN volatile float V_24V             INITIALIZE(0.);             //!< 24V supply voltage
EXTERN volatile float V_24V             INITIALIZE(0.);             //!< 24V supply voltage filtered
EXTERN volatile float V_bus             INITIALIZE(0.);             //!< DC bus voltage
//EXTERN volatile float V_bus_avg         INITIALIZE(0.);             //!< DC bus voltage filtered

// Inverter
EXTERN volatile float I_inv             INITIALIZE(0.);             //!< Inverter current
EXTERN volatile float I_inv_avg         INITIALIZE(0.);             //!< Inverter current filtered
EXTERN volatile float I_inv_rms         INITIALIZE(0.);             //!< Inverter RMS current
//EXTERN volatile float Ph_inv            INITIALIZE(0.);             //!< Inverter phase

// Inverter output
EXTERN volatile float P_out             INITIALIZE(0.);             //!< Output power
EXTERN volatile float V_out             INITIALIZE(0.);             //!< Output voltage
EXTERN volatile float I_out             INITIALIZE(0.);             //!< Output current

// Gyrator output
EXTERN volatile float V_gyr             INITIALIZE(0.);             //!< Gyrator voltage measured
EXTERN volatile float I_gyr             INITIALIZE(0.);             //!< Gyrator current measured

EXTERN volatile bool clearSignal;                                   //!< Internal signal to clear errors and exit error state
EXTERN volatile bool enableSignal;                                  //!< Internal signal to enable output and enter operate state

EXTERN volatile float I_gyr_ref;                                    //!< Gyrator peak current reference, updated over CAN

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

/*!@brief
 * External signals
 */

EXTERN mdlOpsMode_cnf_Mode_t OPS_Mode;       //INITIALIZE(e_mdlOpsMode_cnf_Mode_Not_Supported);
EXTERN uint16_t EnableFlags             INITIALIZE(0);              //!< Various flags for debugging



// Messages over CAN
// DELETE
//EXTERN INV_cnf_Control_t INV_Control;                               //!< Control signals from CAN
EXTERN IV_Trips_Update_t IV_TripsUpdate;                            //!< Inverter/Gyrator current and voltage trip settings + gyrator reference voltage
EXTERN V_Trips_Update_t V_TripsUpdate;                              //!< Bus and 24V voltage trip settings
EXTERN float newControlTrips[update_IVendOfList];                   //!< Array to hold new trips for inverter/gyrator
EXTERN float discreteCoeffs[coeff_endOfList];                       //!< Array to hold intermediate values for CoEfficient calculations

//EXTERN uint16_t systick_counter             INITIALIZE(0);          // TODO \bug : is this used anywhere??



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

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCTION SECTION - END
//=============================================================================


/******************************************************************************
 * THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 * UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 * MAY LEAD TO PROSECUTION.
 *****************************************************************************/
#endif /* GLOBALS_H_ */


/** @}*/
