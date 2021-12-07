/** \addtogroup Core
 *  @{
 */

#ifndef INV_SHARED_H_
#   define INV_SHARED_H_

/*****************************************************************************/
/*!@file IPS_shared.h @copyright
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
/*!@file            IPS_shared.h
 *
 * @details         These are the variables that are shared between the CLA
 *                  and CPU
 *                  TODO long_description.
 *****************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "IPS_..."
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

#include "_module/mdlADC/_config/mdlADC_cnf.h"
#include "_module/mdlCMPSS/_config/mdlCMPSS_cnf.h"


//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#if defined(_LAUNCHXL_F280049C)
#   define SYSCLK 100e6
#elif defined(_91_S230_0181a)
#   define SYSCLK 99e6
#endif

//#define BUFFER_SIZE     1024 // NOTE: keep to a power of 2
//#define FILTER_ORDER    28U
//#define FILTER_LENGTH   (FILTER_ORDER + 1U)


// PWM frequency and derived values
//
#define EPWMCLK         SYSCLK                                  //!< Clock for ePWM modules
#define PWM_Frequency   85000.0
#define PWM_Period      (uint16_t)(EPWMCLK/PWM_Frequency)
#define PWM_180deg      (uint16_t)(0.5*EPWMCLK/PWM_Frequency)   // 50% = 180°
#define PWM_DB          (uint16_t) (EPWMCLK*350.0e-9)           // Deadband = 350ns (approx. 1.5 more for the gate drive waveforms)


// ADC and DAC settings
//
#define  VADC_REF  3.3                                          //!< ADC reference voltage
//#define  VDAC_REF  3.3                                          // DAC reference voltage
//#define  DAC_RANGE 4095.0                                       // DAC 12 bit range
//#define  ADC_RANGE 4095.0                                       // ADC 12 bit range


//
// Globals
//
//Task 1 (C) Variables

//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables


// Defines for Analog-Digital Input Signals


// ADC A Result Registers
//
#define ADC_V_GYR   (float) AdcaResultRegs.ADCRESULT0           //!< Measured gyrator voltage
#define ADC_V_BUS   (float) AdcaResultRegs.ADCRESULT1           //!< Measured DC bus voltage


// ADC B Result Registers
//
#define ADC_I_GYR   (float) AdcbResultRegs.ADCRESULT0           //!< Measured gyrator current
#define ADC_PH_INV  (float) AdcbResultRegs.ADCRESULT1           //!< Measured inverter current phase difference


//#define WAITSTEP asm(" RPT #255 || NOP")                        //!< Assembly delay command


//Shared CLA C28x Task (C) Variables
//
extern float phase_setpoint;                                    //!< Setpoint for phase shift of PWM2A=B+ wrt PWM7B=A+ in [ticks]
extern volatile float phase_limit;                              //!< Limit for phase shift of PWM2A=B+ wrt PWM7B=A+ in [ticks]
extern volatile float I_gyr_ref_cla;                            //!< Reference of gyrator current as input for CLA control loop

extern volatile float b2;
extern volatile float b1;
extern volatile float b0;
extern volatile float a1;
extern volatile float a0;

extern volatile float ek[3];                                    //!< error signals ek-0, ek-1, ek-2
extern volatile float uk[3];
extern volatile float delta;

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

// Function Prototypes

// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.
//
__attribute__((interrupt)) void Cla1Task1();
__attribute__((interrupt)) void Cla1Task2();
__attribute__((interrupt)) void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCTION SECTION - END
//=============================================================================


/******************************************************************************
 * THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 * UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 * MAY LEAD TO PROSECUTION.
 *****************************************************************************/
#endif /* INV_SHARED_H_ */

/** @}*/

