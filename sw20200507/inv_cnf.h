/**
 * \addtogroup Core
 *  @{
 */

#ifndef INV_CNF_H_
	#define INV_CNF_H_

/******************************************************************************/
/*!@file inv_cnf.h @copyright
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
/*!@file            inv_cnf.h
 *
 * @details         Configuration of the inverter.
 ******************************************************************************/


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


#include <stdint.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// For complete integration of the module you just have to
//	#include the "IPS_cnf.h" to you project
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

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 1. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	Various IPS settings.
    //>>

    // Frequencies
    #define INV_cnf__FULLBRIDGE_FREQ    85000.0f        //!< fullbridge converter frequency in [Hz]
    #define INV_cnf__BUCK_FREQ         140000.0f        //!< buck converter frequency in [Hz]
    #define INV_cnf__AC_FREQ               50.0f        //!< mains frequency in [Hz]

    // Fan control settings
    #define INV_cnf__Temp_FAN_ON           55.0f        //!< temperature threshold for turning fans on [degC]
    #define INV_cnf__Temp_FAN_OFF          45.0f        //!< temperature threshold for turning fans off [degC]

    // Over-voltage protection settings used by CMPSS module
    #define INV_cnf__V_24V_MAX_TRIP        27.0f        //!< 24V supply maximum trip voltage [V] (monitored by CMPSS)
    #define INV_cnf__V_24V_MIN_TRIP        22.0f        //!< 24V supply minimum trip voltage [V] (monitored by CMPSS)
    #define INV_cnf__V_BUS_MAX_TRIP       850.0f        //!< bus maximum trip voltage [V] (monitored by CMPSS)
    #define INV_cnf__V_BUS_MIN_TRIP       600.0f        //!< bus minimum trip voltage [V] (monitored by CMPSS)
    #define INV_cnf__V_GYR_TRIP           700.0f        //!< gyrator trip voltage [V] (monitored by CMPSS)

    // Overcurrent protection settings used by CMPSS module
    #define INV_cnf__I_INV_TRIP            40.0f        //!< inverter trip current [A] (monitored by CMPSS)
    #define INV_cnf__I_GYR_TRIP            50.0f        //!< gyrator trip current [A] (monitored by CMPSS)

    // Over-temperature protection settings used by CMPSS module
    #define INV_cnf__TempA_MIN_TRIP       0.123f        //!< minimum trip voltage for NTC input [V] (monitored by CMPSS)
    #define INV_cnf__TempB_MIN_TRIP       0.123f        //!< minimum trip voltage for NTC input [V] (monitored by CMPSS)
    #define INV_cnf__TempGYR_MIN_TRIP     0.100f        //!< minimum trip voltage for NTC input [V] (monitored by CMPSS)

//    // Over-temperature protection settings
//    // TODO {NOTE:THESE ARE NOT USED ANYWHERE. SHOULD THEY BE PUT IN USE OR REMOVED?}
//    #define INV_cnf__TempA_TRIP            75.0f        //!< temperature A over-temperature trip setting [degC]
//    #define INV_cnf__TempA_CLR_TRIP        70.0f        //!< temperature A clear over-temperature trip setting [degC]
//    #define INV_cnf__TempB_TRIP            75.0f        //!< temperature B over-temperature trip setting [degC]
//    #define INV_cnf__TempB_CLR_TRIP        70.0f        //!< temperature B clear over-temperature trip setting [degC]
//    #define INV_cnf__TempGYR_TRIP          75.0f        //!< gyrator over-temperature trip setting [degC]
//    #define INV_cnf__TempGYR_CLR_TRIP      70.0f        //!< gyrator clear over-temperature trip setting [degC]
//    #define INV_cnf__TempuC_TRIP           75.0f        //!< on-chip over-temperature trip setting [degC]
//    #define INV_cnf__TempuC_CLR_TRIP       70.0f        //!< on-chip clear over-temperature trip setting [degC]

    //<<
    //<<<< 1. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

    /*!@brief
     * IPS trip limits updated values
     */
    typedef struct IV_Trips_Update
    {
        uint16_t           V_GYR_Trip_Update;         //!< Gyrator voltage trip update value
        uint16_t           I_GYR_Trip_Update;         //!< Gyrator current trip update value
        uint16_t           I_INV_Trip_Update;         //!< Inverter current trip update value
    }IV_Trips_Update_t;



    /*!@brief
     * IPS trip limits updated values
     */
    typedef struct V_Trips_Update
    {
        uint16_t           V_24V_MaxT_Update;
        uint16_t           V_24V_MinT_Update;
        uint16_t           V_Bus_MaxT_Update;
        uint16_t           V_Bus_MinT_Update;
    }V_Trips_Update_t;



    /*!@brief
     * current and voltage trips that are configurable on the go
     */
    typedef enum update_ControlTrips
    {
        IVTrips_starter   =     -1,
        update_VgyrTripMax,              //!< trip on gyrator voltage > DACH output
        update_IgyrTripMax,              //!< trip on gyrator current > DACH output
        update_IinvTripMax,              //!< trip on inverter current > DACH output
        update_VsupplyTripMax,           //!< trip on supply voltage > DACL output
        update_VsupplyTripMin,           //!< trip on supply voltage < DACL output
        update_VbusTripMax,              //!< trip on bus voltage > DACH output
        update_VbusTripMin,              //!< trip on bus voltage < DACL output
        update_IVendOfList
    }update_ControlTrips_t;



    /*!@brief
     * Discrete voltage controller coefficients, calculated using inputs sent over CAN
     * to allow to change coefficients in CLA on the go
     */
    typedef enum update_CLAcoeffs
    {
        coeff_starter =         -1,
        coeff_K_V_z,
        coeff_bv2,
        coeff_bv1,
        coeff_bv0,
        coeff_av2,
        coeff_av1,
        coeff_av0,
        coeff_endOfList
    }update_CLAcoeffs_t;



#endif /* INV_CNF_H_ */

#ifdef	LOAD_MODULE_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 2. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	TODO description
    //>>

    //<<
    //<<<< 2. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//		MODULE CONFIGURATION	- END
//==============================================================================

/** @}*/
