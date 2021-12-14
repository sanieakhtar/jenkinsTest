/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file mdlNTC.c @copyright
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
/*!@file            mdlNTC.c
 * @brief           Provide temperature for connected NTC sensor
 *//*
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/

/*****************************************************************************/
/*! \addtogroup mdlNTC NTC Sensor
 *@brief  Provide temperature in °C for connected NTC
 *
 *  @{
 *****************************************************************************/



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes
#include "mdlNTC.h"


//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*!@brief
 * Look-up table for temperatures in [°C] and ADC samples for EPCOS
 * type 8016 NTC sensor.
 *
 *         +---( 51R )---------+---+--( 4k7 )---\+3.3V>
 *         |                   |   |
 *  (NTC EPCOS 8016)           |   |
 *         |           1uF/50V |   |
 *         +---( 51R )-+-||----+   +------------\TEMP>
 *                     |
 *                     v
 *                    GND
 */
//mdlNTC_NTC_t epcos8016[mdlNTC_SIZE_OF_LUT] =
//                            { {-55.0, 4076.},
//                              {-50.0, 4067.},
//                              {-45.0, 4055.},
//                              {-40.0, 4039.},
//                              {-35.0, 4018.},
//                              {-30.0, 3990.},
//                              {-25.0, 3953.},
//                              {-20.0, 3906.},
//                              {-15.0, 3848.},
//                              {-10.0, 3775.},
//                              { -5.0, 3686.},
//                              {   .0, 3580.},
//                              {  5.0, 3456.},
//                              { 10.0, 3313.},
//                              { 15.0, 3152.},
//                              { 20.0, 2976.},
//                              { 25.0, 2786.},
//                              { 30.0, 2586.},
//                              { 35.0, 2381.},
//                              { 40.0, 2176.},
//                              { 45.0, 1973.},
//                              { 50.0, 1777.},
//                              { 55.0, 1591.},
//                              { 60.0, 1417.},
//                              { 65.0, 1257.},
//                              { 70.0, 1112.},
//                              { 75.0,  981.},
//                              { 80.0,  864.},
//                              { 85.0,  760.},
//                              { 90.0,  669.},
//                              { 95.0,  588.},
//                              {100.0,  517.},
//                              {105.0,  455.},
//                              {110.0,  401.},
//                              {115.0,  354.},
//                              {120.0,  313.},
//                              {125.0,  277.},
//                              {130.0,  246.},
//                              {135.0,  218.},
//                              {140.0,  194.},
//                              {145.0,  173.},
//                              {150.0,  155.},
//                              {155.0,  139.}};

/*!@brief
 * Look-up table for temperatures in [°C] and ADC samples for TDK
 * type B57703M0103A039 NTC sensor.
 *
 *         +-------------------\+3.3V>
 *         |
 * (NTC TDK B57703M)
 *         |
 *         +-------------------\TEMP>
 *         |
 *      ( 10k )
 *         |
 *         v
 *        GND
 */

mdlNTC_NTC_t TDK_B57703M[mdlNTC_SIZE_OF_LUT] =
                             {{-55.0, 4054.},
                              {-50.0, 4036.},
                              {-45.0, 4011.},
                              {-40.0, 3978.},
                              {-35.0, 3934.},
                              {-30.0, 3877.},
                              {-25.0, 3804.},
                              {-20.0, 3713.},
                              {-15.0, 3602.},
                              {-10.0, 3469.},
                              { -5.0, 3313.},
                              {  0.0, 3136.},
                              {  5.0, 2939.},
                              { 10.0, 2726.},
                              { 15.0, 2503.},
                              { 20.0, 2275.},
                              { 25.0, 2048.},
                              { 30.0, 1828.},
                              { 35.0, 1618.},
                              { 40.0, 1424.},
                              { 45.0, 1245.},
                              { 50.0, 1085.},
                              { 55.0,  942.},
                              { 60.0,  816.},
                              { 65.0,  706.},
                              { 70.0,  611.},
                              { 75.0,  528.},
                              { 80.0,  458.},
                              { 85.0,  397.},
                              { 90.0,  344.},
                              { 95.0,  299.},
                              {100.0,  261.},
                              {105.0,  228.},
                              {110.0,  199.},
                              {115.0,  175.},
                              {120.0,  153.},
                              {125.0,  135.}};


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

    //-------------------------
    // Private Predeclaration
    //*************************


    //-------------------------
    // Public Section
    //*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Convert ADC result to temperature reading in °C.
 *
 *@param   *me              Pointer to look-up table to be used for the conversion
 *@param    adc_result      ADC conversion result in bits
 *
 *@return   temperature reading in °C, or ABSOLUTE_ZERO if ADC value is out of range
 *\n
 *@note     none
 *
 *\n
 */
float mdlNTC_getTemp(mdlNTC_NTC_t *me, uint16_t adc_result)
{
    int i;
    float val = adc_result;         // convert to float for further calculations
    float result = ABSOLUTE_ZERO;   // init to absolute zero to indicate an invalid reading

    // If out of range (greater than 1st entry)
    if (val > me[0].val)
    {
    }
    // If out of range (less than last entry)
    else if (val < me[mdlNTC_SIZE_OF_LUT - 1].val)
    {
//        result = 5504.85;               //set to maximum
    }
    // Is in range, hence calculate temperature
    else
    {
        // Search neighboring points in lut
        for (i = (mdlNTC_SIZE_OF_LUT - 1); val > me[i].val; i--)
        {
            // do nothing
        }

        // If value matches upper bound
        if (val == me[i].val)
        {
            result = me[i].temp;       //set to matching temperature
        }
        else
        {
            //interpolate linearly between neighboring points
            result = (me[i+1].temp - me[i].temp) / (me[i+1].val - me[i].val);
            result *= (val - me[i+1].val);
            result += me[i+1].temp;
        }//end else
    }//end else

    return result;
}

    //-------------------------
    // Private Section
    //*************************



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


/** @}*/

