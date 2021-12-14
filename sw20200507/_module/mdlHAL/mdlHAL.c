/** \addtogroup Modules
 *  @{
 */

/*****************************************************************************/
/*!@file HAL.c @copyright
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
/*!@file            mdlHAL.c
 * @brief           TODO description short
 *//*
 *  details         The detailed description can be found
 *                  in corresponding header.
 *****************************************************************************/



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes
#include "mdlHAL.h"


//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*!@brief
* Pin descriptor.
*/
typedef struct mdlHAL_cfg_PIN
{
  uint32_t                   pinNumber; //!< GPIO number of the pin
  uint32_t                     pinType; //!< pin type such as GPIO_PIN_TYPE_STD, GPIO_PIN_TYPE_PULLUP, etc.
  uint32_t                   pinConfig; //!< alternate function of the pin
  GPIO_Direction                   dir; //!< pin direction such as GPIO_DIR_MODE_IN
  GPIO_AnalogMode           analogMode; //!< digital or analog mode
  GPIO_QualificationMode      qualMode; //!< qualification mode (for inputs only)
  GPIO_CoreSelect                 core; //!< selected master core such as GPIO_CORE_CPU1, GPIO_CORE_CPU1_CLA1, etc.
  uint32_t                    polarity; //!< set to 1 if active high, 0 if active low for outputs
                                        //!< set to 1 if normal polarity, 0 if inverted polarity for inputs
  uint32_t                     initVal; //!< value to write to the pin at time of configuration (for outputs only)

}mdlHAL_cfg_PIN_t;


static mdlHAL_cfg_PIN_t cfg[e_mdlHAL_cnf_PIN__endOfList] = {
#define LOAD_MODULE_CONFIGURATION
    #include "./_config/mdlHAL_cnf.h"
#undef  LOAD_MODULE_CONFIGURATION
};

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
/*!@brief   Initialise HAL
 *
 *@ref
 *
 *@return   none
 *\n
 *@note     none
 *\n
 */
void mdlHAL_init(void)
{
    uint16_t i;

    // Initialize all configured pins
    for(i = 0; i < e_mdlHAL_cnf_PIN__endOfList; i++)
    {
        // invert polarity of input, if polarity configured to 0
        if(!cfg[i].polarity && (GPIO_DIR_MODE_IN == cfg[i].dir))
        {
            GPIO_setPadConfig(cfg[i].pinNumber, cfg[i].pinType | GPIO_PIN_TYPE_INVERT);
        }
        // this is either an output or no inversion configured
        else
        {
            GPIO_setPadConfig(cfg[i].pinNumber, cfg[i].pinType);
        }
        GPIO_setPinConfig(cfg[i].pinConfig);
        GPIO_setDirectionMode(cfg[i].pinNumber, cfg[i].dir);
        GPIO_setMasterCore(cfg[i].pinNumber, cfg[i].core);
        if ((cfg[i].pinNumber >= 224U) && (cfg[i].pinNumber <= 247U) || (cfg[i].pinNumber == 22) || (cfg[i].pinNumber == 23))
        {
            GPIO_setAnalogMode(cfg[i].pinNumber, cfg[i].analogMode);
        }

        // for inputs only
        if(GPIO_DIR_MODE_IN == cfg[i].dir)
        {
            GPIO_setQualificationMode(cfg[i].pinNumber, cfg[i].qualMode);
        }
        // for outputs only
        else
        {
            GPIO_writePin(cfg[i].pinNumber, cfg[i].initVal);
        }

    }// end for
}


//------------------------------------------------------------------------------------------------
/*!@brief   Return configured numerical pin number of pin.
 *
 *@ref      mdlHAL_cnf_PIN_t
 *
 *@param    i       :   number of configuration
 *
 *@return   identifying number of the pin
 *\n
 *@note     none
 *\n
 */
uint16_t mdlHAL_getPinNumber(mdlHAL_cnf_PIN_t i)
{
    return (uint16_t) cfg[i].pinNumber;
}

//------------------------------------------------------------------------------------------------
/*!@brief   Read value present at configured pin
 *
 *@ref      mdlHAL_cnf_PIN_t
 *
 *@param    i       :   number of configuration
 *
 *@return   Returns the value in the data register of the specified pin.
 *\n
 *@note     Actual value read from the pin will depend on the configured polarity.
 *@note     1=standard polarity: 1 will be read as 1
 *@note     0=inverse polarity:  1 will be read as 0
 *\n
 */
uint32_t mdlHAL_readPin(mdlHAL_cnf_PIN_t i)
{
    uint32_t val;

    val = GPIO_readPin(cfg[i].pinNumber);

    return val;
}

//------------------------------------------------------------------------------------------------
/*!@brief   Write value to configured pin
 *
 *@ref      mdlHAL_cnf_PIN_t
 *
 *@param    i       :   number of configuration
 *@param    val     :   value to write to the pin
 *
 *@return   none
 *\n
 *@note     Actual value written to the pin will depend on the configured polarity.
 *@note     1=standard polarity: 1 will be written as 1
 *@note     0=inverse polarity:  1 will be written as 0
 *\n
 */
void mdlHAL_writePin(mdlHAL_cnf_PIN_t i, uint32_t val)
{
    GPIO_writePin(cfg[i].pinNumber, !(cfg[i].polarity^val));
}

//------------------------------------------------------------------------------------------------
/*!@brief   Toggle configured pin
 *
 *@ref      mdlHAL_cnf_PIN_t
 *
 *@param    i       :   number of configuration
 *
 *@return   none
 *\n
 *@note     none
 *\n
 */
void mdlHAL_togglePin(mdlHAL_cnf_PIN_t i)
{
    GPIO_togglePin(cfg[i].pinNumber);
}

    //-------------------------
    // Private Section
    //*************************



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCTION SECTION - END
//=============================================================================


/******************************************************************************
 * THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
 * UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
 * MAY LEAD TO PROSECUTION.
 *****************************************************************************/

/** @}*/

