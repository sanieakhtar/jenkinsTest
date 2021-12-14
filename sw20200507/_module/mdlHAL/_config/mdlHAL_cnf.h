/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLHAL__CONFIG_MDLHAL_CNF_H_
	#define MODULE_MDLHAL__CONFIG_MDLHAL_CNF_H_

/******************************************************************************/
/*!@file mdlHAL_cnf.h @copyright
 *      THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 *\n    UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 *      MAY LEAD TO PROSECUTION.
 *\n
 *\n    IPT Technology GmbH
 *\n    Im Martelacker 14
 *\n    79588 Efringen-Kirchen
 *\n    Germany
 *\n    Phone:   +49 7628 692 96-0
 *\n    Fax:     +49 7628 692 96-99
 *\n    info@ipt-technology.com
 *\n    www.ipt-technology.com
 ******************************************************************************/


/******************************************************************************/
/*!@file            mdlHAL_cnf.h
 *
 * @details         TODO long_description.
 ******************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlHAL_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlHAL_cnf_...".
//      Please avoid identical declaration elsewhere!
//
//      This settlement EXCLUDES private declarations and definitions
//      which validity is bound to this file.
//
//*****************************************************************************


#include <stdint.h>
#include <pin_map.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// For complete integration of the module you just have to
//	#include the "mdlHAL_cnf.h" to you project
//
//	CONFIGURATION STEPS
//	---------------------
//	1. Search for "SELF-CONFIGURATION SECTION"s and do your desired configurations
//	2. Have a look for the "LOAD_MODULE_CONFIGURATION" section if present and fit
//		this section to your needs
//
//	ATTENTION:	Often the configurations in the second step are dependent on
//				the configurations of the first.
//				(The number of "objects" for example.)
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//		MODULE CONFIGURATION	- START
//==============================================================================

    /*!@brief
     * List of all pins to be configured by the mdlHAL.
     */
    typedef enum mdlHAL_cnf_PIN
    {
        e_mdlHAL_cnf_PIN__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 1. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	list of configured pins
    //>>

        // digital outputs
#ifdef DEBUG
        e_mdlHAL_cnf_PIN__debugCPU_DIO11,           //!< ePWM3A output for debugging
        e_mdlHAL_cnf_PIN__debugCPU_DIO12,           //!< pin for debugging
        e_mdlHAL_cnf_PIN__debugCLA_DIO9,            //!< pin for debugging CLA
        e_mdlHAL_cnf_PIN__debugCLA_DIO10,           //!< pin for debugging CLA
        e_mdlHAL_cnf_PIN__debug_DIO14,              //!< pin for testing state switching b/w STBDY & OP
#endif
        e_mdlHAL_cnf_PIN__operate,                  //!< switch inverter to operate mode
        e_mdlHAL_cnf_PIN___FAULT_uC,                //!< indicate fault in uC
        e_mdlHAL_cnf_PIN___FAULT_SIL,               //!< external signal to transistor gate drives

        // PWM outputs
        e_mdlHAL_cnf_PIN__ePWM2A,                   //!< PWM output for fullbridge
        e_mdlHAL_cnf_PIN__ePWM2B,                   //!< PWM output for fullbridge
        e_mdlHAL_cnf_PIN__ePWM7A,                   //!< PWM output for fullbridge
        e_mdlHAL_cnf_PIN__ePWM7B,                   //!< PWM output for fullbridge

        // DIP switch (S201) digital inputs
        e_mdlHAL_cnf_PIN__DIPswitch1,               //!< !sel1 input (DIP switch)
        // Operation mode selection pins
        e_mdlHAL_cnf_PIN__OPS_Mode_SelectionA,
        e_mdlHAL_cnf_PIN__OPS_Mode_SelectionB,
        e_mdlHAL_cnf_PIN__DIPswitch4,               //!< !sel4 input (DIP switch)

        // serial port pins
        e_mdlHAL_cnf_PIN__SCIA_Rxd,                 //!< serial port A receive
        e_mdlHAL_cnf_PIN__SCIA_Txd,                 //!< serial port A transmit
        e_mdlHAL_cnf_PIN__SCIB_Rxd,                 //!< serial port B receive
        e_mdlHAL_cnf_PIN__SCIB_Txd,                 //!< serial port B transmit

        // CAN bus pins
        // CAN-A
        e_mdlHAL_cnf_PIN__CAN_A_Rx,                 //!< CAN bus receive
        e_mdlHAL_cnf_PIN__CAN_A_Tx,                 //!< CAN bus transmit
        // CAN-B
        e_mdlHAL_cnf_PIN__CAN_B_Rx,                 //!< CAN bus receive
        e_mdlHAL_cnf_PIN__CAN_B_Tx,                 //!< CAN bus transmit

        // SPI 4-wire bus pins
        e_mdlHAL_cnf_PIN__SPIB_Clk,                 //!< SPI-B clock
        e_mdlHAL_cnf_PIN__SPIB_SIMO,                //!< SPI-B SIMO
        e_mdlHAL_cnf_PIN__SPIB_SOMI,                //!< SPI-B SOMI
        e_mdlHAL_cnf_PIN__FRAM_CS,                  //!< CS line for FRAM (SPI-B)

        // Master Slave SYNC pins
        e_mdlHAL_cnf_PIN__MS_select,                //!< Master Slave select
        e_mdlHAL_cnf_PIN__MS_SYNC_RX,               //!< Slave SYNC RX
        e_mdlHAL_cnf_PIN__MS_SYNC_TX,               //!< Master SYNC TX


    //<<
    //<<<< 1. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlHAL_cnf_PIN__endOfList
    }mdlHAL_cnf_PIN_t;


    #endif /* MODULE_MDLHAL__CONFIG_MDLHAL_CNF_H_ */

#ifdef	LOAD_MODULE_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 2. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	List here the pin specifications.
    //              Refer to mdlHAL_cfg_PIN_t for details on each entry.
    //
    // IMPORTANT:   THE ORDER IS DEFINED THROUGH YOUR
    //              NAMING ORDER ABOVE.
    //
    // SYNTAX:      {pinNumber, pinType, pinConfig, dir, analogMode, qualMode, core, polarity, initVal},
    //
    // EXAMPLE:     configure GPIO9 as push-pull output, controlled by CPU1, active high, initialized to 0
    //              {  9, GPIO_PIN_TYPE_STD, 0, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_SYNC, GPIO_CORE_CPU1, 1, 0},
    //
    //              configure GPIO9 as floating input , qualified with 3 samples, active high
    //              {  3, GPIO_PIN_TYPE_STD, 0, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_3SAMPLE, GPIO_CORE_CPU1, 1, 0},
    //
    //>>

#ifdef DEBUG
    // digital outputs for debugging
    // DIO11 output on X104-5
//    {  4, GPIO_PIN_TYPE_STD, 0, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_SYNC, GPIO_CORE_CPU1, 1, 0},
    {  4, GPIO_PIN_TYPE_STD, GPIO_4_EPWM3_A, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_SYNC, GPIO_CORE_CPU1, 1, 0},
    // DIO12 output on X104-6
    {  5, GPIO_PIN_TYPE_STD, 0, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_SYNC, GPIO_CORE_CPU1, 1, 0},
    // DIO9 output on X104-1
    { 14, GPIO_PIN_TYPE_STD, GPIO_14_EPWM8_A, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_SYNC, GPIO_CORE_CPU1_CLA1, 1, 0},
    // DIO10 output on X104-2
    { 15, GPIO_PIN_TYPE_STD, 0, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_SYNC, GPIO_CORE_CPU1_CLA1, 1, 0},
    // DIO14 Input on X104-10
    { 12, GPIO_PIN_TYPE_INVERT, 0, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_6SAMPLE, GPIO_CORE_CPU1, 1, 0},
#endif

    // Digital input to switch inverter to operate state
    {  0, GPIO_PIN_TYPE_STD, 0, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_6SAMPLE, GPIO_CORE_CPU1, 1, 0},
    // Indicates the presence of a fault in the inverter uC. Active low. Stays high when no fault
    {  1, GPIO_PIN_TYPE_STD, 0, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_SYNC, GPIO_CORE_CPU1, 1, 0},
    // External relay enable signal, indicates relays are ready to be activated
    {  9, GPIO_PIN_TYPE_STD, 0, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_6SAMPLE, GPIO_CORE_CPU1, 1, 0},


    // Connect digital PWM outputs X126-DIO4 (aka B+) and X126-DIO5 (aka B-) of the board to peripheral ePWM2A and ePWM2B
    {  2, GPIO_PIN_TYPE_STD, GPIO_2_EPWM2_A, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_SYNC, GPIO_CORE_CPU1, 1, 0},
    {  3, GPIO_PIN_TYPE_STD, GPIO_3_EPWM2_B, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_SYNC, GPIO_CORE_CPU1, 1, 0},
    // Connect digital PWM outputs X126-DIO6 (aka A-) and X126-DIO7 (aka A+) of the board to peripheral ePWM7A and ePWM7B
    { 28, GPIO_PIN_TYPE_STD, GPIO_28_EPWM7_A, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_SYNC, GPIO_CORE_CPU1, 1, 0},
    { 29, GPIO_PIN_TYPE_STD, GPIO_29_EPWM7_B, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_SYNC, GPIO_CORE_CPU1, 1, 0},

    // DIP switch inputs 1..4, all set to inverted polarity (e.g. DIP sw on -> input pulled to gnd -> reading a 1)
    { 10, GPIO_PIN_TYPE_PULLUP, 0, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_6SAMPLE, GPIO_CORE_CPU1, 0, 0},
    //Mode selections pins 1 & 2
    { 33, GPIO_PIN_TYPE_STD, GPIO_33_GPIO33, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_6SAMPLE, GPIO_CORE_CPU1, 0, 0},
    { 34, GPIO_PIN_TYPE_STD, GPIO_34_GPIO34, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_6SAMPLE, GPIO_CORE_CPU1, 0, 0},
    { 40, GPIO_PIN_TYPE_PULLUP, 0, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_6SAMPLE, GPIO_CORE_CPU1, 0, 0},

    // serial port A pins
    { 17, GPIO_PIN_TYPE_STD, GPIO_17_SCIA_RX, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC, GPIO_CORE_CPU1, 1, 0},
    { 16, GPIO_PIN_TYPE_STD, GPIO_16_SCIA_TX, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC, GPIO_CORE_CPU1, 1, 0},
    // serial port B pins
    { 57, GPIO_PIN_TYPE_STD, GPIO_57_SCIB_RX, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC, GPIO_CORE_CPU1, 1, 0},
    { 56, GPIO_PIN_TYPE_STD, GPIO_56_SCIB_TX, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC, GPIO_CORE_CPU1, 1, 0},

    // CAN bus A pins
    { 30, GPIO_PIN_TYPE_STD, GPIO_30_CANA_RX, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC, GPIO_CORE_CPU1, 1, 0},
    { 31, GPIO_PIN_TYPE_STD, GPIO_31_CANA_TX, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC, GPIO_CORE_CPU1, 1, 0},

    // CAN bus B pins
    { 39, GPIO_PIN_TYPE_STD, GPIO_39_CANB_RX, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC, GPIO_CORE_CPU1, 1, 0},
    { 58, GPIO_PIN_TYPE_STD, GPIO_58_CANB_TX, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC, GPIO_CORE_CPU1, 1, 0},

    // SPI bus B pins: clk, SIMO, SOMI, CS for FRAM (use standard GPIOs not GPIO_xxx_SPISTEB function)
    { 26, GPIO_PIN_TYPE_STD, GPIO_26_SPIB_CLK, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC, GPIO_CORE_CPU1, 1, 0},
    {  7, GPIO_PIN_TYPE_STD, GPIO_7_SPIB_SIMO, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC, GPIO_CORE_CPU1, 1, 0},
    { 25, GPIO_PIN_TYPE_STD, GPIO_25_SPIB_SOMI, GPIO_DIR_MODE_IN, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC, GPIO_CORE_CPU1, 1, 0},
    { 27, GPIO_PIN_TYPE_STD,                0, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC, GPIO_CORE_CPU1, 0, 1},

    // Master Slave SYNC pins
    { 59, GPIO_PIN_TYPE_STD, GPIO_59_GPIO59, GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC , GPIO_CORE_CPU1, 1, 0},
    { 11, GPIO_PIN_TYPE_STD, GPIO_11_GPIO11, GPIO_DIR_MODE_IN,  GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC , GPIO_CORE_CPU1, 1, 0},
    {  6, GPIO_PIN_TYPE_STD, GPIO_6_GPIO6,   GPIO_DIR_MODE_OUT, GPIO_ANALOG_DISABLED, GPIO_QUAL_ASYNC , GPIO_CORE_CPU1, 1, 0},

    //<<
    //<<<< 2. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//		MODULE CONFIGURATION	- END
//==============================================================================

/** @}*/

