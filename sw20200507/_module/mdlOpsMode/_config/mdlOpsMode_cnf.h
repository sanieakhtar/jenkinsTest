/** \addtogroup Modules
 *  @{
 */


#ifndef MODULE_MDLOPSMODE_CONFIG_MDLOPSMODE_CNF_H_
	#define MODULE_MDLOPSMODE_CONFIG_MDLOPSMODE_CNF_H_

/******************************************************************************/
/*!@file mdlOpsMode_cnf.h @copyright
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
/*!@file            mdlOpsMode_cnf.h
 *
 * @details         Configuration data of the operation modes module
 *
 ******************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlOpsMode_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlOpsMode_cnf_...".
//      Please avoid identical declaration elsewhere!
//
//      This settlement EXCLUDES private declarations and definitions
//      which validity is bound to this file.
//
//*****************************************************************************


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// For complete integration of the module you just have to
//	#include the "mdlOpsMode_cnf.h" to you project
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
     * List of general modes of operation
     */
    typedef enum mdlOpsMode_cnf_Mode
    {
        e_mdlOpsMode_cnf_Mode_Starter   =   -1,



    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 1. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION: Enumeration for identification
    //              of operational mode.
    //              Enter matching settings in
    //              2. SELF-CONFIGURATION SECTION below.
    //>>

        e_mdlOpsMode_cnf_Mode_Development,                  //!< Development Mode Identifier
        e_mdlOpsMode_cnf_Mode_Test,                         //!< Test Mode Identifier
        e_mdlOpsMode_cnf_Mode_Field,                        //!< Field Mode Identifier
        e_mdlOpsMode_cnf_Mode_Not_Supported,                //!< Unsupported Mode Identifier

    }mdlOpsMode_cnf_Mode_t;


#endif /* MODULE_MDLOPSMODE_CONFIG_MDLOPSMODE_CNF_H_ */

#ifdef	LOAD_MODULE_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 3. SELF-CONFIGURATION SECTION	- START
    //
    //<<
    //<<<< 3. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//		MODULE CONFIGURATION	- END
//==============================================================================

/** @}*/
