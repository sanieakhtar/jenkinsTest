/** \addtogroup Modules
 *  @{
 */

#ifndef MODULE_MDLCAN_CONFIG_MDLCAN_CNF_H_
	#define MODULE_MDLCAN_CONFIG_MDLCAN_CNF_H_

/******************************************************************************/
/*!@file mdlCAN_cnf.h @copyright
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
/*!@file            mdlCAN_cnf.h
 *
 * @details         Pre-configurations for the mdlCAN.
 ******************************************************************************/


/*****************************************************************************/
/*! \addtogroup mdlCAN Controller Area Network
 *@brief  Configure cyclic CAN messages
 *
 *  This module provides functions for the cyclic transmission and reception
 *  of CAN messages.
 *  @{
 *****************************************************************************/


//*****************************************************************************
//  GENERAL INFORMATION
//=============================================================================
//
//      All naming of definitions, declaration and similar
//      follow the same build up.
//      They always do start with the "mdlCAN_cnf_..."
//      (declarations/definitions/constants) to assign these to
//      this file.
//      Special definitions and declarations which existence is
//      dependent on configuration in the "config_???"-file are
//      always named "mdlCAN_cnf_...".
//      Please avoid identical declaration elsewhere!
//
//      This settlement EXCLUDES private declarations and definitions
//      which validity is bound to this file.
//
//*****************************************************************************


#include <stdint.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// For complete integration of the module you just have to
//	#include the "mdlCAN_cnf.h" to your project
//
//	CONFIGURATION STEPS
//	---------------------
//	1. Search for "SELF-CONFIGURATION SECTION"s and do your desired configurations
//	2. Have a look for the "LOAD_MODULE_CONFIGURATION" section if present and fit
//	   this section to your needs
//
//	ATTENTION:	Often the configurations in the second step are dependent on
//				the configurations of the first.
//				(The number of "objects" for example.)
//
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//		MODULE CONFIGURATION	- START
//==============================================================================



    /*!@brief
     * List of CAN modules to be configured by the mdlCAN.
     */
    typedef enum mdlCAN_cnf_CAN
    {
        e_mdlCAN_cnf_CAN__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 1. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: list of configured CAN interfaces
    //>>

        e_mdlCAN_cnf_CAN__comms,            //!< CAN bus for transmission of diagnostic data
                                            //!< and reception of control command from supervisory system,
                                            //!< i.e. from a PC or PLC
        e_mdlCAN_cnf_CAN__test,             //!< CAN bus for transmission of data (test only, purpose is unclear)

    //<<
    //<<<< 1. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlCAN_cnf_CAN__endOfList
    }mdlCAN_cnf_CAN_t;


    /*!@brief
     * List of all configured CAN messages.
     * The mdlCAN will reserve "e_mdlCAN_cnf_MSG__endOfList"
     * message buffers for automated CAN transmission.
     */
    typedef enum mdlCAN_cnf_MSG
    {
        e_mdlCAN_cnf_MSG__starter   = -1,
    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 2. SELF-CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	Name your message here to add
    //              it to configuration. The module
    //              will automatically reserve a
    //              buffer for your CAN message.
    //              Message object 1 (up to 32 possible) has the highest priority1
    //>>
        e_mdlCAN_cnf_MSG__inv_Data,                     //!< Transmitting Data message
        e_mdlCAN_cnf_MSG__inv_Status,                   //!< Transmitting Status message
        e_mdlCAN_cnf_MSG__inv_Info,                     //!< Transmitting Info message

        e_mdlCAN_cnf_MSG__inv_Control,                  //!< Receiving Control message
        e_mdlCAN_cnf_MSG__inv_ControlMux,               //!< Receiving Control message via MUX
        e_mdlCAN_cnf_MSG__inv_IVTripsUpdate,            //!< Receiving Trips Update 1 message
        e_mdlCAN_cnf_MSG__inv_CLAcoeffs,                //!< Receiving CLA coefficients
//        e_mdlCAN_cnf_MSG__inv_Test,                     //!< Transmitting Test message
    //<<
    //<<<< 2. SELF-CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------
        e_mdlCAN_cnf_MSG__endOfList
    }mdlCAN_cnf_MSG_t;


    // Standard CAN bitrates [bit/s] to be used in the module configuration below
    // If adding baud rates, make sure there is also a matching entry in the bit timing
    // table below (-> 6. SELF-CONFIGURATION SECTION)!
    #define mdlCAN_BITRATE_1000k    1000                //!< 1Mbit/s bitrate
    #define mdlCAN_BITRATE_500k      500                //!< 500kbit/s bitrate
    #define mdlCAN_BITRATE_250k      250                //!< 250kbit/s bitrate
    #define mdlCAN_BITRATE_125k      125                //!< 125kbit/s bitrate

    // Macro to convert floats to uint: subtract offset, scale and round up by half
    #define mdlCAN_FLOAT_TO_UINT(x, offset, factor) (((x - offset) / factor) + 0.5)

    // Macro to convert uints to floats: round down, scale and add offset back
    #define mdlCAN_UINT_TO_FLOAT(x, offset, factor) (((x - 0.5) * factor) + offset)

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 3. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: Specific defines to adjust the
    //              CAN module
    //>>

    #define mdlCAN_node_ID                  3       //!< CANopen node ID used as offset to CAN IDs

    // Conversion between physical and raw CAN values:
    // rawValue = (physicalValue - offset) / factor
    #define mdlCAN_cnf_V_FACTOR             0.1     //!< Scale factor for voltages
    #define mdlCAN_cnf_V_OFFSET               0     //!< Offset for voltages in [V]

    #define mdlCAN_cnf_I_FACTOR             0.1     //!< Scale factor for currents
    #define mdlCAN_cnf_I_OFFSET          -204.8     //!< Offset for currents in [A]

    #define mdlCAN_cnf_P_FACTOR             1.0     //!< Scale factor for power
    #define mdlCAN_cnf_P_OFFSET               0     //!< Offset for power in [W]

    #define mdlCAN_cnf_T_FACTOR               1     //!< Scale factor for temperatures
    #define mdlCAN_cnf_T_OFFSET             -40     //!< Offset for temperatures in [°C]

    #define mdlCAN_cnf_PHASE_FACTOR         0.1     //!< Scale factor for phase angle

    #define mdlCAN_cnf_U8_NOT_AVAIL        0xFF     //!< Value not available/out of range
    #define mdlCAN_cnf_U16_NOT_AVAIL     0xFFFF     //!< Value not available/out of range

    // Endianness for all defined CAN messages
    #define mdlCAN_cnf_BIG_ENDIAN             0     //!< 1 = use big endian byte order (Motorola), otherwise default to little endian (Intel)

    // Settings for buffer size and period calculation
    #define mdlCAN_cnf_MAX_MSG_DATA_LENGTH    8     //!< Maximum no. of bytes for all defined CAN messages (maximum is 8).
    #define mdlCAN_cnf_TICKS_PER_MS        0.1F     //!< The number of OS ticks per millisecond.

    // Start-up delays
    #define mdlCAN_cnf_TX_STARTUP_DELAY      0      //!< Delay in [ms] after starting up for CAN transmission.
    #define mdlCAN_cnf_RX_STARTUP_DELAY    200      //!< Delay in [ms] after starting up for CAN reception.

    //<<
    //<<<< 3. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------


    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 4. SELF-CONFIGURATION SECTION    - START
    //
    // EXPLANATION: Define structures for each CAN message.
    //              These may be used to write or read the CAN msg data.
    //
    //>>


    /*!@brief
     * Layout of Status CAN message (transmitted).
     * @ref e_mdlCAN_cnf_MSG__inv_Status
     */
    typedef struct
    {
        uint16_t     State_ID            ;              //!< State ID
        uint16_t     EnableFlags_LSB     ;              //!< Flags
        uint16_t     EnableFlags_MSB     ;              //!< Flags
#if mdlCAN_cnf_BIG_ENDIAN == 1
        uint16_t     ErrorCode_MSB       ;              //!< Error code
        uint16_t     ErrorCode_LSB       ;              //!< Error code
#else
        uint16_t     ErrorCode_LSB       ;              //!< Error code
        uint16_t     ErrorCode_MSB       ;              //!< Error code
#endif
        uint16_t     Spare0              ;              //!< Spare byte
        uint16_t     Spare1              ;              //!< Spare byte
        uint16_t     Spare2              ;              //!< Spare byte
    } mdlCAN_Status_Msg_Layout_t;


    /*!@brief
     * Layout of Data CAN message (transmitted).
     * @ref e_mdlCAN_cnf_MSG__inv_Data
     */
    typedef struct
    {
        uint16_t    multiplexer         ;               //!< CAN message multiplexer
#if mdlCAN_cnf_BIG_ENDIAN == 1
        uint16_t    PhaseAngleSet_MSB   ;               //!< Fullbridge phase angle setpoint
        uint16_t    PhaseAngleSet_LSB   ;               //!< Fullbridge phase angle setpoint
#else
        uint16_t    PhaseAngleSet_LSB   ;               //!< Fullbridge phase angle setpoint
        uint16_t    PhaseAngleSet_MSB   ;               //!< Fullbridge phase angle setpoint
#endif
#if mdlCAN_cnf_BIG_ENDIAN == 1
        uint16_t    I_inv_MSB           ;               //!< Fullbridge current
        uint16_t    I_inv_LSB           ;               //!< Fullbridge current
#else
        uint16_t    I_inv_LSB           ;               //!< Fullbridge current
        uint16_t    I_inv_MSB           ;               //!< Fullbridge current
#endif
#if mdlCAN_cnf_BIG_ENDIAN == 1
        uint16_t    PhaseAngle_MSB      ;               //!< Fullbridge phase angle measured
        uint16_t    PhaseAngle_LSB      ;               //!< Fullbridge phase angle measured
#else
        uint16_t    PhaseAngle_LSB      ;               //!< Fullbridge phase angle
        uint16_t    PhaseAngle_MSB      ;               //!< Fullbridge phase angle
#endif
    } mdlCAN_Data_MuxInverter_Msg_Layout_t;


    /*!@brief
     * Layout of Data CAN message (transmitted).
     * @ref e_mdlCAN_cnf_MSG__inv_Data
     */
    typedef struct
    {
        uint16_t    multiplexer         ;               //!< CAN message multiplexer
#if mdlCAN_cnf_BIG_ENDIAN == 1
        uint16_t    V_gyrator_MSB       ;               //!< Gyrator voltage
        uint16_t    V_gyrator_LSB       ;               //!< Gyrator voltage
#else
        uint16_t    V_gyrator_LSB       ;               //!< Gyrator voltage
        uint16_t    V_gyrator_MSB       ;               //!< Gyrator voltage
#endif
#if mdlCAN_cnf_BIG_ENDIAN == 1
        uint16_t    I_gyrator_MSB       ;               //!< Gyrator current
        uint16_t    I_gyrator_LSB       ;               //!< Gyrator current
#else
        uint16_t    I_gyrator_LSB       ;               //!< Gyrator current
        uint16_t    I_gyrator_MSB       ;               //!< Gyrator current
#endif
#if mdlCAN_cnf_BIG_ENDIAN == 1
        uint16_t    P_output_MSB        ;               //!< Output power
        uint16_t    P_output_LSB        ;               //!< Output power
#else
        uint16_t    P_output_LSB        ;               //!< Output power
        uint16_t    P_output_MSB        ;               //!< Output power
#endif
    } mdlCAN_Data_MuxGyrator_Msg_Layout_t;



    /*!@brief
     * Layout of Data CAN message (transmitted).
     * @ref e_mdlCAN_cnf_MSG__inv_Data
     */
    typedef struct
    {
        uint16_t    multiplexer         ;               //!< CAN message multiplexer
#if mdlCAN_cnf_BIG_ENDIAN == 1
        uint16_t    V_24V_MSB           ;               //!< 24V Supply voltage
        uint16_t    V_24V_LSB           ;               //!< 24V Supply voltage
#else
        uint16_t    V_24V_LSB           ;               //!< 24V Supply voltage
        uint16_t    V_24V_MSB           ;               //!< 24V Supply voltage
#endif
#if mdlCAN_cnf_BIG_ENDIAN == 1
        uint16_t    V_bus_MSB           ;               //!< DC bus voltage
        uint16_t    V_bus_LSB           ;               //!< DC bus voltage
#else
        uint16_t    V_bus_LSB           ;               //!< DC bus voltage
        uint16_t    V_bus_MSB           ;               //!< DC bus voltage
#endif
#if mdlCAN_cnf_BIG_ENDIAN == 1
        uint16_t    Spare1_MSB          ;               //!< Spare
        uint16_t    Spare1_LSB          ;               //!< Spare
#else
        uint16_t    Spare1_LSB          ;               //!< Spare
        uint16_t    Spare1_MSB          ;               //!< Spare
#endif
    } mdlCAN_Data_MuxVarious_Msg_Layout_t;


    /*!@brief
     * Layout of Info CAN message (transmitted).
     * @ref e_mdlCAN_cnf_MSG__inv_Info
     */
    typedef struct {
        uint16_t    multiplexer         ;               // CAN message multiplexer
        uint16_t    payload_byte0       ;               // CAN message payload byte
        uint16_t    payload_byte1       ;               // CAN message payload byte
        uint16_t    payload_byte2       ;               // CAN message payload byte
        uint16_t    payload_byte3       ;               // CAN message payload byte
        uint16_t    payload_byte4       ;               // CAN message payload byte
        uint16_t    payload_byte5       ;               // CAN message payload byte
        uint16_t    payload_byte6       ;               // CAN message payload byte
    }mdlCAN_InfoMsg_Layout_t;


    /*!@brief
     * Layout of Control CAN message (received).
     * @ref e_mdlCAN_cnf_MSG__inv_ControlMux
     */
    typedef struct {
        uint16_t    multi               ;
        uint16_t    controlSignal  :1   ;
//        uint16_t    enableOutput  :1    ;
    }mdlCAN_ControlMux_Layout_t;


    /*!@brief
     * Layout of Control CAN message (received).
     * @ref e_mdlCAN_cnf_MSG__inv_Control
     */
    typedef struct {
        uint16_t    inv_enOutput  :1    ;               //!< Inverter output enable flag
        uint16_t    inv_clrError  :1    ;               //!< Clear error flag
        uint16_t    inv_spareFlag :1    ;               //!< Spare flag, used for testing
        uint16_t    inv_spareBits :5    ;               //!< Spare var , used for testing
//        uint16_t    i_gyr_ref_LSB       ;               //!< Gyrator reference value LSB
//        uint16_t    i_gyr_ref_MSB       ;               //!< Gyrator reference value MSB
    }mdlCAN_ControlMsg_Layout_t;


    /*!@brief
     * Layout of trip update CAN message (received)
     * @ref e_mdlCAN_cnf_MSG__inv_IVTripsUpdate
     */
    typedef struct {
        uint16_t    v_gyr_trip_LSB      ;               //!< Gyrator voltage trip update value LSB
        uint16_t    v_gyr_trip_MSB      ;               //!< Gyrator voltage trip update value MSB
        uint16_t    i_gyr_trip_LSB      ;               //!< Gyrator current trip update value LSB
        uint16_t    i_gyr_trip_MSB      ;               //!< Gyrator current trip update value MSB
        uint16_t    i_inv_trip_LSB      ;               //!< Inverter current trip update value LSB
        uint16_t    i_inv_trip_MSB      ;               //!< Inverter current trip update value MSB
        uint16_t    i_gyr_ref_LSB       ;               //!< Gyrator reference value LSB
        uint16_t    i_gyr_ref_MSB       ;               //!< Gyrator reference value MSB
    }mdlCAN_TripsUpdate_Layout_t;


    /*!@brief
     * TODO Layout of auxiliary trip updates CAN message (received)
     * NOT SURE IF THIS IS NEEDED OR NOT YET
     * @ref e_mdlCAN_cnf_MSG__inv_VTripsUpdate
     */
    typedef struct {
        uint16_t    v_24v_tmax_LSB      ;               //!<
        uint16_t    v_24v_tmax_MSB      ;               //!<
        uint16_t    v_24v_tmin_LSB      ;               //!<
        uint16_t    v_24v_tmin_MSB      ;               //!<
        uint16_t    v_bus_tmax_LSB      ;               //!<
        uint16_t    v_bus_tmax_MSB      ;               //!<
        uint16_t    v_bus_tmin_LSB      ;               //!<
        uint16_t    v_bus_tmin_MSB      ;               //!<
    }mdlCAN_SupplyTripUpdate_Layout_t;


    /*!@brief
     * Layout of CLA coefficients (received)
     * @ref e_mdlCAN_cnf_MSG__inv_CLAcoeffs
     */
    typedef struct {
        uint16_t    inv_fsh_LSB          ;               //!< Inverter output enable flag
        uint16_t    inv_fsh_MSB          ;               //!< Clear error flag
        uint16_t    inv_f0h_LSB          ;               //!< Spare flag, used for testing
        uint16_t    inv_f0h_MSB          ;               //!< Spare var , used for testing
        uint16_t    inv_F_LSB            ;               //!< Gyrator reference value LSB
        uint16_t    inv_F_MSB            ;               //!< Gyrator reference value MSB
        uint16_t    inv_Kah_LSB          ;               //!< Gyrator reference value LSB
        uint16_t    inv_Kah_MSB          ;               //!< Gyrator reference value MSB
    }mdlCAN_CLAcoeffs_Layout_t;


    //<<
    //<<<< 4. SELF-CONFIGURATION SECTION    - END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif /* MODULE_MDLCAN_CONFIG_MDLCAN_CNF_H_ */


#ifdef	LOAD_MESSAGE_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 5. MESSAGE CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	Define here the CAN messages to be transmit and received
    //
    //              Refer to mdlCAN_cfg_MSG_t for details on each entry.
    //
    // IMPORTANT:   THE ORDER IS DEFINED THROUGH YOUR NAMING ORDER ABOVE.
    //              If more than one CAN module is used, order configured messages accordingly!
    //
    // SYNTAX:      {CAN-Module, CAN-ID, ID-Type, direction, length(*) [bytes], priority(**), period [ms], timeout [no. of periods]},
    //
    //              (*) for a transmit message the number of bytes to send, for a rx msg the minimum number of bytes to be received
    //              (**) priority currently not used
    //
    // EXAMPLES:    Transmit std ID message with 8 data bytes and an update rate of 1000ms
    //              {e_mdlCAN_cnf_CAN__comms, 0x210, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX,   8,   0,   1000,    0},
    //              Receive std ID message with an update rate of 100ms and with a maximum of 2 skipped messages allowed
    //              {e_mdlCAN_cnf_CAN__comms, 0x100, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX,   8,   0,    100,    2},
    //              Receive std ID message with an update rate of 50ms, a minimum of DLC of 4 bytes, and with no limit for skipped messages allowed
    //              {e_mdlCAN_cnf_CAN__comms, 0x100, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX,   4,   0,     50, 0xFF},
    //>>

    // TRANSMIT MESSAGES
    // IPS Data message
    {e_mdlCAN_cnf_CAN__comms, 0x180+mdlCAN_node_ID, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX,   8,   0,     20,   0},

    // IPS Status message
    {e_mdlCAN_cnf_CAN__comms, 0x280+mdlCAN_node_ID, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX,   8,   0,    100,   0},

    // IPS Info message
    {e_mdlCAN_cnf_CAN__comms, 0x380+mdlCAN_node_ID, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX,   8,   0,    100,   0},

    // RECEIVE MESSAGES
    // IPS Control receive message, allow a maximum of 2 skipped messages
    {e_mdlCAN_cnf_CAN__comms, 0x200+mdlCAN_node_ID, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX,   6,   0,     20,   2},

    // IPS Control MUX receive message, allow a maximum of 2 skipped messages
    {e_mdlCAN_cnf_CAN__comms, 0x210+mdlCAN_node_ID, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX,   8,   0,     20,   2},

    // IPS I/V updates receive message, allow a maximum of 2 skipped messages
    {e_mdlCAN_cnf_CAN__comms, 0x220+mdlCAN_node_ID, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX,   8,   0,     20,   2},

    // CLA coefficients received over CAN
    {e_mdlCAN_cnf_CAN__comms, 0x230+mdlCAN_node_ID, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX,   8,   0,     20,   2},

//    // IPS Test message
//    {e_mdlCAN_cnf_CAN__test, 0x180+mdlCAN_node_ID, CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX,    8,   0,    100,   0},

    //<<
    //<<<< 5. MESSAGE CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif

#ifdef	LOAD_MODULE_CONFIGURATION

    //----------------------------------------------
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>>> 6. INTERNAL MODULE CONFIGURATION SECTION	- START
    //
    // EXPLANATION:	Define here the settings for each CAN module used, including bit timing settings.
    //
    //              Refer to mdlCAN_cfg_CAN_t for details on each entry.
    //
    // IMPORTANT:   Bit timing parameters bit time and CAN_BTR depend on baud rate and CAN bus length!
    //              These were calculated using TI's bit timing calculator for the DCAN module.
    //              Where possible a length of 50m was assumed.
    //
    // SYNTAX:      {CAN bus module, bitrate, bit time, CAN_BTR register value}
    //
    //>>

        {CANA_BASE, mdlCAN_BITRATE_250k,  11, 0x035E3},
        {CANB_BASE, mdlCAN_BITRATE_250k,  11, 0x035E3},

// These are verified bit timing settings for a CAN bit clock of 99MHz @various standard baud rates:
//        {CANA_BASE, mdlCAN_BITRATE_125k,   8, 0x123A2},
//        {CANA_BASE, mdlCAN_BITRATE_250k,  11, 0x035E3},
//        {CANA_BASE, mdlCAN_BITRATE_500k,  18, 0x04BCA},
//        {CANA_BASE, mdlCAN_BITRATE_1000k, 11, 0x02688},    // will work only for CAN bus lengths < 10m

    //<<
    //<<<< 6. INTERNAL MODULE CONFIGURATION SECTION	- END
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //----------------------------------------------

#endif

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//		MODULE CONFIGURATION	- END
//==============================================================================


/*****************************************************************************/
/*! @}
 *  Close the Doxygen group.
 *****************************************************************************/

/** @}*/

