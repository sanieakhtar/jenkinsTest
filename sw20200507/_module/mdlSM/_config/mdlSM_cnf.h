/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLSM__CONFIG_MDLSM_CNF_H_
	#define MODULE_MDLSM__CONFIG_MDLSM_CNF_H_

/******************************************************************************/
/*!@file mdlSPI_cnf.h @copyright
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
/*!@file            mdlSM_cnf.h
 *
 * @details         Configure state machine.
 ******************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlSM_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlSM_cnf_...".
//      Please avoid identical declaration elsewhere!
//
//      This settlement EXCLUDES private declarations and definitions
//      which validity is bound to this file.
//
//*****************************************************************************




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// For complete integration of the module you just have to
//	#include the "mdlSM_cnf.h" to you project
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
     * List of all states known to the mdlSM
     */
    typedef enum mdlSM_cnf_States
    {
        e_mdlSM_cnf_State__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 1. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: list of configured states
    //>>

        e_mdlSM_cnf_State__Boot,        //!< Initial state of the state machine
        e_mdlSM_cnf_State__Idle,        //!< Idle state of inverter before the PFC becomes operational
        e_mdlSM_cnf_State__Standby,     //!< Inverter remains in standby and monitors for faults or operate command
        e_mdlSM_cnf_State__Operate,     //!< Inverter operates to regulate the output
        e_mdlSM_cnf_State__Error,       //!< When faults are detected, system enters this state to wait for resolution

    //<<
    //<<<< 1. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlSM_cnf_State__endOfList
    }mdlSM_cnf_States_t;


    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 2. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: Specific defines to adjust the
    //              state machine module
    //>>

        #define mdlSM_cnf_TICKS_PER_MS             0.1F     //!< The number of OS ticks per millisecond.
        #define mdlSM_cnf_SAMPLE_INTERVAL        100        //!< Interval for sampling boost converter voltage for stability in [ms]

        #define mdlSM_cnf_BOOT_DELAY             500        //!< Delay between boot and standby states in [ms]
        #define mdlSM_cnf_STAY_IN_ERROR_DELAY   1000        //!< Delay before transition from error state is permitted [ms]
        #define mdlSM_cnf_CLEAR_ERROR_DELAY     2000        //!< Delay between attempting to clear an error in [ms]
        #define mdlSM_cnf_DISABLE_DELAY          200        //!< Delay between operate and standby states in [ms]
        #define mdlSM_cnf_OPERATE_DELAY          300        //!< Delay between standby and operate states in [ms]


    //<<
    //<<<< 2. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------


#endif /* MODULE_MDLSM__CONFIG_MDLSM_CNF_H_ */

#ifdef	LOAD_MODULE_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 3. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	List here the configuration for each state.
    //
    // IMPORTANT:   THE ORDER IS DEFINED THROUGH
    //              YOUR NAMING ORDER ABOVE.
    //
    // SYNTAX:      {state ID),
    //
    // EXAMPLES:
    //
    //
    //>>
        // State IDs
        { 0},   // Boot,
        { 1},   // Idle,
        { 2},   // Standby,
        { 3},   // Operate,
        { 4}    // Error,

    //<<
    //<<<< 3. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//		MODULE CONFIGURATION	- END
//==============================================================================

/** @}*/

