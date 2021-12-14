/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLSCI__CONFIG_MDLSCI_CNF_H_
	#define MODULE_MDLSCI__CONFIG_MDLSCI_CNF_H_

/******************************************************************************/
/*!@file mdlSCI_cnf.h @copyright
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
/*!@file            mdlSCI_cnf.h
 *
 * @details         TODO long_description.
 ******************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlSCI_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlSCI_cnf_...".
//      Please avoid identical declaration elsewhere!
//
//      This settlement EXCLUDES private declarations and definitions
//      which validity is bound to this file.
//
//*****************************************************************************


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// For complete integration of the module you just have to
//	#include the "mdlSCI_cnf.h" to you project
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

//#ifndef uint8_t
//typedef uint16_t uint8_t;
//#endif

    /*!@brief
     * List of serial interfaces to be configured by the mdlSCI.
     */
    typedef enum mdlSCI_cnf_SCI
    {
        e_mdlSCI_cnf_SCI__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 1. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: list of configured serial ports
    //>>

        e_mdlSCI_cnf_SCI__debug,            //!< Port for debugging and system info

    //<<
    //<<<< 1. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlSCI_cnf_SCI__endOfList
    }mdlSCI_cnf_SCI_t;


    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 2. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: Specific defines to adjust the
    //              SCI module
    //>>

    #define mdlSCI_cnf_TICKS_PER_MS     0.1F    //!< Number of OS ticks per millisecond.

    //<<
    //<<<< 2. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------


#endif /* MODULE_MDLSCI__CONFIG_MDLSCI_CNF_H_ */

#ifdef	LOAD_MODULE_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 3. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	List here the configuration for each serial interface
    //
    // IMPORTANT:   THE ORDER IS DEFINED THROUGH YOUR
    //              NAMING ORDER ABOVE.
    //
    // SYNTAX:      {base, baud, length, stopBits, parity, rxBuffer, txBuffer, rxCycleTime[ms], txCycleTime[ms]},
    //
    // EXAMPLES:    configure SCIA port for 115200 baud, 8-N-1, use the buffers configured in mdlFIFO, receive every 20ms, transmit every 100ms
    //              {SCIA_BASE, 115200, SCI_CONFIG_WLEN_8, SCI_CONFIG_PAR_NONE, SCI_CONFIG_STOP_ONE, e_mdlFIFO_cnf_buf__receive, e_mdlFIFO_cnf_buf__transmit, 20, 100},
    //
    //              configure SCIB port for 19200 baud, 8-O-1, use no buffers, receive every 10ms, transmit every 10ms
    //              {SCIB_BASE, 19200, SCI_CONFIG_WLEN_8, SCI_CONFIG_PAR_ODD, SCI_CONFIG_STOP_ONE, e_mdlFIFO_cnf_buf__none,  e_mdlFIFO_cnf_buf__none, 10, 10},
    //

    //>>

//    // serial port for debugging
//    {SCIB_BASE, 115200, SCI_CONFIG_WLEN_8, SCI_CONFIG_PAR_NONE, SCI_CONFIG_STOP_ONE, e_mdlFIFO_cnf_buf__none, e_mdlFIFO_cnf_buf__none, 0, 100},
    // serial port for debugging
    {SCIB_BASE, 115200, SCI_CONFIG_WLEN_8, SCI_CONFIG_PAR_NONE, SCI_CONFIG_STOP_ONE},

    //<<
    //<<<< 3. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//		MODULE CONFIGURATION	- END
//==============================================================================

/** @}*/

