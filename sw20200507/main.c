/**
 * \addtogroup Core
 *  @{
 */

/*****************************************************************************/
/*!@file main.c @copyright
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
/*!@file            main.c
 * @brief           Program main
 *
 * @details         Several built configurations for different types
 *                  of hardware exist.
 *                  See project properties > C2000 Compiler >
 *                  Advanced > Predefined Symbols:
 *                  _LAUNCHXL_F280049C  LaunchPad with 20MHz Xtal
 *                  _91_S230_0181a      IPT TS ControlBoard Ver. a with 12MHz Xtal
 *
 *****************************************************************************/



//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
//=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=




//=============================================================================
// Includes

#include "F28x_Project.h"
#include "driverlib.h"
#include "device/device.h"
#include "inv_shared.h"
#include "sys_cnf.h"
#include "BootConfig.h"

#define GLOBALS
#   include "globals.h"
#undef GLOBALS

#include "_module/mdlADC/mdlADC.h"                      // Analog to digital converters
#include "_module/mdlCAN/mdlCAN.h"                      // Controller Area Network communications
#include "_module/mdlCMPSS/mdlCMPSS.h"                  // Comparators
#include "_module/mdlEPWM/mdlEPWM.h"                    // EPWM management
#include "_module/mdlError/mdlError.h"                  // Error management
#include "_module/mdlHAL/mdlHAL.h"                      // Hardware Abstraction Layer
#include "_module/mdlMeasurement/mdlMeasurement.h"      // Measurement management
#include "_module/mdlMonitor/mdlMonitor.h"              // Monitor variables
#include "_module/mdlOpsMode/mdlOpsMode.h"              // Operation mode
#include "_module/mdlSM/mdlSM.h"                        // State machine

#ifdef DEBUG
#   include <math.h>                                    // CLA coeff calculation
#endif




//=============================================================================
// MACROS, DECLARATIONS AND DEFINES - START
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// CLA - CPU Shared Variables

// CLA1 to CPU
//
#pragma DATA_SECTION(phase_setpoint,"Cla1ToCpuMsgRAM")
    float phase_setpoint;

// CPU to CLA1
//
#pragma DATA_SECTION(phase_limit,"CpuToCla1MsgRAM")
    volatile float phase_limit;
#pragma DATA_SECTION(I_gyr_ref_cla,"CpuToCla1MsgRAM")
    volatile float I_gyr_ref_cla;
#ifdef DEBUG
#pragma DATA_SECTION(b2,"CpuToCla1MsgRAM")
    volatile float b2;
#pragma DATA_SECTION(b1,"CpuToCla1MsgRAM")
    volatile float b1;
#pragma DATA_SECTION(b0,"CpuToCla1MsgRAM")
    volatile float b0;
#pragma DATA_SECTION(a1,"CpuToCla1MsgRAM")
    volatile float a1;
#pragma DATA_SECTION(a0,"CpuToCla1MsgRAM")
    volatile float a0;
#endif

// Linker Defined variables
//
extern uint32_t Cla1ProgRunStart, Cla1ProgLoadStart, Cla1ProgLoadSize;
extern uint32_t Cla1ConstRunStart, Cla1ConstLoadStart, Cla1ConstLoadSize;


// Bit operation macros
//
#define SETBIT(ADDRESS, BIT)    (ADDRESS |= (1 << BIT))
#define CLEARBIT(ADDRESS, BIT)  (ADDRESS &= ~(1 << BIT))
#define TESTBIT(ADDRESS, BIT)   (ADDRESS & (1 << BIT))

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

// Initialize various peripherals
//
static void initSystickTimer(uint32_t base, uint32_t period);
static void initCla1(void);
static void initXBAR(void);
static void updateReadings(void);
static void update_Status_CANMsgData(void);
static void update_Info_CANMsgData(void);
static void update_Data_MuxInverter_CANMsgData(void);
static void update_Data_MuxGyrator_CANMsgData(void);
static void update_Data_MuxVarious_CANMsgData(void);
static void read_Control_CANMsgData(void);
static void read_DACupdate_CANMsgData(void);
static void read_CLAupdate_CANMsgData(void);
static void updateTemperatures(void);
static void setBootROMConfiguration(void);
extern void fullbridge_updatePeakRef(uint16_t peakRefUpdate);

//-------------------------
// Public Section
//*************************

// Main

 void main(void){
#ifdef DEBUG
    unsigned char *msg;
#endif

    // Initialize System Control and device clock and peripherals
    //
    Device_init();
    setBootROMConfiguration();

    // Initialize PIE, clear PIE registers, disable and clear all
    // CPU interrupts and flags
    //
    Interrupt_initModule();

    // Initialize the PIE vector table with pointers to the shell interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();
    Interrupt_enableMaster();

    // Setup the CLA
    // Trigger task 2 for the initialization of variables.
    //
    initCla1();
    CLA_forceTasks(CLA1_BASE, CLA_TASKFLAG_2);

    // Configure CPU timer SYSTICK_TIMER for system tick cycle
    //
    initSystickTimer(SYSTICK_TIMER, SYSTICK_CYCLE);

    // Initialize GPIOs
    //
    Device_initGPIO();
    mdlHAL_init();

    //Initialize the operation mode
    //
    mdlOpsMode_init();

    // Initialize multiplexers
    //
    initXBAR();

//    // Initialize ADC modules and set up conversions to be performed
//    //
//    mdlADC_init();

    // Initialize measurement module
    //
    mdlMeasurement_init();

    // Initialize serial ports
    //
    mdlSCI_init();

    // Print software info to configured serial port
    //
    TERMINAL_PRINT(versioninfo__SEPARATOR);
    TERMINAL_PRINT(versioninfo__SW_DESC_STR);
    TERMINAL_PRINT(versioninfo__SW_ID_STR);
    TERMINAL_PRINT(versioninfo__SW_VER_STR);
    TERMINAL_PRINT(versioninfo__SW_DATE);
    TERMINAL_PRINT(versioninfo__SEPARATOR);

#ifdef DEBUG
    // Transmit test message to serial port A
    //
    msg = "\r\nThis is port SCI-A.\0";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 21);

    // Transmit test message to serial port B
    //
    msg = "\r\nThis is port SCI-B.\0";
    SCI_writeCharArray(SCIB_BASE, (uint16_t*)msg, 21);
#endif

    if (e_mdlOpsMode_cnf_Mode_Development == OPS_Mode)
    {
        // Transmit to debug port
        //
        DEBUG_PRINT("The operation mode is development");
    }
    if (e_mdlOpsMode_cnf_Mode_Test == OPS_Mode )
    {
        // Transmit to debug port
        //
        DEBUG_PRINT("The operation mode is test");
    }

    // Initialize CAN communication module
    //
    mdlCAN_init();

    //Initialize monitor module
    //
    mdlMonitor_init();

    // Initialize state machine
    //
    mdlSM_init();

    // Initialize CMPSSs (comparators)
    //
    mdlCMPSS_init();

    // Initialize ePWMs including submodules
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);                              // disable ePWM time base clock sync
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_EPWM7, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);   // sync ePWM7 to ePWM1
    mdlEPWM_initTripZones();                                                            // initialize configured ePWM trip zones
    mdlEPWM_init();                                                                     // initialize configured ePWMs
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);                               // enable ePWM time base clock sync

    // Initial gyrator current peak reference value
    //
    I_gyr_ref = 35.0F;

    // enable PGA module (for debugging)
    //
    PGA_enable(PGA3_BASE);                  // enable selected PGA
    PGA_setGain(PGA3_BASE, PGA_GAIN_3);     // set PGA gain



    //--------------------------------------------------------------------------//
    // main loop
    //
    for(;;)
    {

        // Check for system tick timer overflow.
        // Cycle time is SYSTICK_CYCLE in [us], e.g. 1000 = 1ms.
        //
        if(CPUTimer_getTimerOverflowStatus(SYSTICK_TIMER))
        {
            // Execute the state machine handler
            //
            mdlSM_exec();

            // Update various readings such as temperatures, currents and voltages.
            // Cycle is set to once every 20ms.
            //
            updateReadings();

            // Transmit and receive the configured CAN messages.
            //
            mdlCAN_exec();

            // Update external settings/commands from CAN message ips_Control (received message)
            //
            read_Control_CANMsgData();
            read_DACupdate_CANMsgData();
            read_CLAupdate_CANMsgData();

            // Monitor configured variables
            //
             mdlMonitor_exec();

            CPUTimer_clearOverflowFlag(SYSTICK_TIMER);
        }
    }
    //--------------------------------------------------------------------------//
}


//------------------------------------------------------------------------------------------------
/*!@brief   Initialize one of the CPUs 32-bit timers as system tick timer.
 *
 *@param    base        : is the base address of the timer module.
 *@param    period      : is the timer period in us.
 *
 *@return   none
 *\n
 *@note     none
 *\n
 */
static void initSystickTimer(uint32_t base, uint32_t period)
{
    // Initialize timer period
    // For a pre-scaler of 0, DEVICE_SYSCLK_FREQ/1e6 timer increments take 1us.
    //
    CPUTimer_setPeriod(base, period * (DEVICE_SYSCLK_FREQ/1000000));

    // Initialize pre-scale counter to divide by 1 (timer runs at SYSCLKOUT)
    //
    CPUTimer_setPreScaler(base, 0);

    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(base);

    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(base);

    // Start the timer
    //
    CPUTimer_startTimer(base);
}


//------------------------------------------------------------------------------------------------
/*!@brief   Configure the ePWM X-BAR.
 *          Set the multiplexer output being configured.
 *          Set the multiplexer values that determine the signals passed to the ePWM modules.
 *
 *@return   none
 *\n
 *@note
 *\n
 */
static void initXBAR(void)
{
    // Configure TRIP4 INPUT to be CTRIP4H (trip signal from CMPSS4 COMPH comparator)
    //
    XBAR_setEPWMMuxConfig(XBAR_TRIP4, XBAR_EPWM_MUX06_CMPSS4_CTRIPH);
    XBAR_enableEPWMMux(XBAR_TRIP4, XBAR_MUX06);

    // Configure TRIP5 INPUT to be CTRIP3H (trip signal from CMPSS3 COMPH comparator)
    //
    XBAR_setEPWMMuxConfig(XBAR_TRIP5, XBAR_EPWM_MUX04_CMPSS3_CTRIPH);
    XBAR_enableEPWMMux(XBAR_TRIP5, XBAR_MUX04);

    // Configure TRIP7 INPUT to be CTRIP2H (trip signal from CMPSS2 COMPH comparator)
    //
    XBAR_setEPWMMuxConfig(XBAR_TRIP7, XBAR_EPWM_MUX02_CMPSS2_CTRIPH);
    XBAR_enableEPWMMux(XBAR_TRIP7, XBAR_MUX02);

    // Configure TRIP8 INPUT to be CTRIP6H or CTRIP6L (trip signal from CMPSS6 COMPH or COMPL comparator)
    //
    XBAR_setEPWMMuxConfig(XBAR_TRIP8, XBAR_EPWM_MUX10_CMPSS6_CTRIPH_OR_L);
    XBAR_enableEPWMMux(XBAR_TRIP8, XBAR_MUX10);

    // Configure TRIP9 INPUT to be CTRIP1L (trip signal from CMPSS1 COMPL comparator)
    //
    XBAR_setEPWMMuxConfig(XBAR_TRIP9, XBAR_EPWM_MUX01_CMPSS1_CTRIPL);
    XBAR_enableEPWMMux(XBAR_TRIP9, XBAR_MUX01);

    // Configure TRIP9 INPUT to be CTRIP3L (trip signal from CMPSS3 COMPL comparator)
    //
    XBAR_setEPWMMuxConfig(XBAR_TRIP9, XBAR_EPWM_MUX05_CMPSS3_CTRIPL);
    XBAR_enableEPWMMux(XBAR_TRIP9, XBAR_MUX05);

    // Configure TRIP10 INPUT to be CTRIP7H (trip signal from CMPSS7 COMPH comparator)
    //
    XBAR_setEPWMMuxConfig(XBAR_TRIP10, XBAR_EPWM_MUX12_CMPSS7_CTRIPH);
    XBAR_enableEPWMMux(XBAR_TRIP10, XBAR_MUX12);

    // Configure TRIP10 INPUT to be CTRIP5H (trip signal from CMPSS5 COMPH comparator)
    //
    XBAR_setEPWMMuxConfig(XBAR_TRIP10, XBAR_EPWM_MUX08_CMPSS5_CTRIPH);
    XBAR_enableEPWMMux(XBAR_TRIP10, XBAR_MUX08);

    // Configure TRIP10 INPUT to be CTRIP2L (trip signal from CMPSS2 COMPL comparator)
    //
    XBAR_setEPWMMuxConfig(XBAR_TRIP10, XBAR_EPWM_MUX03_CMPSS2_CTRIPL);
    XBAR_enableEPWMMux(XBAR_TRIP10, XBAR_MUX03);
}


//------------------------------------------------------------------------------------------------
/*!@brief   Update readings for display and for external communication.
 *
 *@return   none
 *\n
 */
static void updateReadings(void)
{

//    #define TICKS_PER_MS     0.1F   //!< The number of OS ticks per millisecond.
//    #define UPDATE_CYCLE    20      //!< Interval for updates in milliseconds.

    const float TICKS_PER_MS = 0.1;
    const int   UPDATE_CYCLE = 20;

    static uint16_t sleep_count = 0;
    static uint16_t msg_count = 0;

    // Decrement sleep time counter while inactive
    //
    if(sleep_count)
    {
        sleep_count -= 1;
    }

    // Counter for sleep time has expired. Update required.
    //
    else
    {
        // Set required number of ticks, until next update.
        //
        sleep_count = (TICKS_PER_MS * UPDATE_CYCLE) - 1;

        // Get current readings
        //
        mdlMeasurement_update();

        // Update CAN Data message with data, depending on count
        //
        switch(msg_count)
        {
            case 0:
                update_Data_MuxInverter_CANMsgData();
                msg_count++;
                break;
            case 1:
                update_Data_MuxGyrator_CANMsgData();
                msg_count++;
                break;
            case 2:
                update_Data_MuxVarious_CANMsgData();
                msg_count++;
                break;
            case 3:
                updateTemperatures();
                update_Data_MuxInverter_CANMsgData();
                update_Info_CANMsgData();
                msg_count++;
                break;
            case 4:
                update_Data_MuxGyrator_CANMsgData();
                update_Status_CANMsgData();
                msg_count = 0;
                break;
            default:
                msg_count = 0;
                break;
        }
    }
}



//------------------------------------------------------------------------------------------------
/*!@brief   Writes data to local buffer for transmission of Data CAN message.
 *
 *@ref      mdlCAN_Data_MuxInverter_Msg_Layout_t
 *@ref      e_mdlCAN_cnf_MSG__inv_Data
 *
 *@return
 *\n
 *@note
 *\n
 */
static void update_Data_MuxInverter_CANMsgData(void)
{

    mdlCAN_Data_MuxInverter_Msg_Layout_t *msg;       //!< pointer to CAN msg layout structure

    uint16_t u16_dummy;

    // Point to data section of message
    //
    msg = (mdlCAN_Data_MuxInverter_Msg_Layout_t*) mdlCAN_getDataRef(e_mdlCAN_cnf_MSG__inv_Data);
    msg->multiplexer = 0;                       // Set 8-bit mux

    // Inverter current (positive -> zero offset)
    //
    u16_dummy = mdlCAN_FLOAT_TO_UINT(I_inv, 0, mdlCAN_cnf_I_FACTOR);

    // Write data to message buffer (byte order in memory is little endian)
    //
    msg->I_inv_LSB = u16_dummy;
    msg->I_inv_MSB = (u16_dummy >> 8) & 0x3F;  // Limit to 12-bit

//    // PHASE ANGLE NOT BEING MEASURED AND TRANSMITTED ANYMORE
//
//    // Phase angle measured
//    //
//    u16_dummy = mdlCAN_FLOAT_TO_UINT(Ph_inv, 0, mdlCAN_cnf_PHASE_FACTOR);
//
//    // If out of range set to value not available
//    //
//    if((u16_dummy * mdlCAN_cnf_PHASE_FACTOR) > 360.0)
//    {
//        u16_dummy = mdlCAN_cnf_U16_NOT_AVAIL;
//    }
//
//    // Write data to message buffer (byte order in memory is little endian)
//    //
//    msg->PhaseAngle_LSB = u16_dummy;
//    msg->PhaseAngle_MSB = (u16_dummy >> 8) & 0x3F;  // Limit to 12-bit
//
//    // Phase angle setpoint
//    //
//    u16_dummy = mdlCAN_FLOAT_TO_UINT(360.0*phase_setpoint/PWM_Period, 0, mdlCAN_cnf_PHASE_FACTOR);
//
//    // If out of range set to value not available
//    //
//    if((u16_dummy * mdlCAN_cnf_PHASE_FACTOR) > 360.0)
//    {
//        u16_dummy = mdlCAN_cnf_U16_NOT_AVAIL;
//    }
//
//    // Write data to message buffer (byte order in memory is little endian)
//    //
//    msg->PhaseAngleSet_LSB = u16_dummy;
//    msg->PhaseAngleSet_MSB = (u16_dummy >> 8) & 0x3F;  // Limit to 12-bit
}


//------------------------------------------------------------------------------------------------
/*!@brief   Writes data to local buffer for transmission of Data CAN message.
 *
 *@ref      mdlCAN_Data_MuxGyrator_Msg_Layout_t
 *@ref      e_mdlCAN_cnf_MSG__inv_Data
 *
 *@return
 *\n
 *@note
 *\n
 */
static void update_Data_MuxGyrator_CANMsgData(void)
{

    mdlCAN_Data_MuxGyrator_Msg_Layout_t *msg;       //!< pointer to CAN msg layout structure

    uint16_t u16_dummy;

    // Point to data section of message
    //
    msg = (mdlCAN_Data_MuxGyrator_Msg_Layout_t*) mdlCAN_getDataRef(e_mdlCAN_cnf_MSG__inv_Data);
    msg->multiplexer = 1;                       // Set 8-bit mux

    // Gyrator voltage (positive -> zero offset)
    //
    u16_dummy = mdlCAN_FLOAT_TO_UINT(V_gyr, 0, mdlCAN_cnf_V_FACTOR);

    // Write data to message buffer (byte order in memory is little endian)
    //
    msg->V_gyrator_LSB = u16_dummy;
    msg->V_gyrator_MSB = (u16_dummy >> 8) & 0x3F;  // Limit to 14-bit

    // Gyrator current (positive -> zero offset)
    //
    u16_dummy = mdlCAN_FLOAT_TO_UINT(I_gyr, 0, mdlCAN_cnf_I_FACTOR);

    // Write data to message buffer (byte order in memory is little endian)
    //
    msg->I_gyrator_LSB = u16_dummy;
    msg->I_gyrator_MSB = (u16_dummy >> 8) & 0x3F;  // Limit to 12-bit

//    // Output power (positive -> zero offset)
//    u16_dummy = mdlCAN_FLOAT_TO_UINT(P_out, mdlCAN_cnf_P_OFFSET, mdlCAN_cnf_P_FACTOR); // Subtract offset, scale and round half up
//    // Write data to message buffer (byte order in memory is little endian)
//    msg->P_output_LSB = u16_dummy;
//    msg->P_output_MSB = (u16_dummy >> 8);
    msg->P_output_LSB = 0;
    msg->P_output_MSB = 0;

}


//------------------------------------------------------------------------------------------------
/*!@brief   Writes data to local buffer for transmission of Data CAN message.
 *
 *@ref      mdlCAN_Data_MuxVarious_Msg_Layout_t
 *@ref      e_mdlCAN_cnf_MSG__inv_Data
 *
 *@return
 *\n
 *@note
 *\n
 */
static void update_Data_MuxVarious_CANMsgData(void)
{

    mdlCAN_Data_MuxVarious_Msg_Layout_t *msg;       //!< pointer to CAN msg layout structure

    uint16_t u16_dummy;

    // Point to data section of message
    //
    msg = (mdlCAN_Data_MuxVarious_Msg_Layout_t*) mdlCAN_getDataRef(e_mdlCAN_cnf_MSG__inv_Data);
    msg->multiplexer = 2;                       // Set 8-bit mux

    // 24V supply voltage (positive -> zero offset)
    //
    u16_dummy = mdlCAN_FLOAT_TO_UINT(V_24V, 0, mdlCAN_cnf_V_FACTOR);

    // Write data to message buffer (byte order in memory is little endian)
    //
    msg->V_24V_LSB = u16_dummy;
    msg->V_24V_MSB = (u16_dummy >> 8) & 0x3F;  // Limit to 14-bit

    // DC bus voltage (positive -> zero offset)
    //
    u16_dummy = mdlCAN_FLOAT_TO_UINT(V_bus, 0, mdlCAN_cnf_V_FACTOR);

    // Write data to message buffer (byte order in memory is little endian)
    //
    msg->V_bus_LSB = u16_dummy;
    msg->V_bus_MSB = (u16_dummy >> 8) & 0x3F;  // Limit to 14-bit

    msg->Spare1_LSB = 0;
    msg->Spare1_MSB = 0;
}


//------------------------------------------------------------------------------------------------
/*!@brief   Writes data to local buffer for transmission of Status CAN message.
 *
 *@ref      mdlCAN_Status_Msg_Layout_t
 *@ref      e_mdlCAN_cnf_MSG__inv_Status
 *
 *@return
 *\n
 *@note
 *\n
 */
static void update_Status_CANMsgData(void)
{

    mdlCAN_Status_Msg_Layout_t *msg;
    uint16_t u16_dummy;

    // Point to data section of message
    //
    msg = (mdlCAN_Status_Msg_Layout_t*) mdlCAN_getDataRef(e_mdlCAN_cnf_MSG__inv_Status);

    // Error code
    //
    u16_dummy = mdlError_getErrorCode();    // Byte order in memory is little endian
    msg->ErrorCode_LSB = u16_dummy;         // LSB
    msg->ErrorCode_MSB = (u16_dummy >> 8);  // MSB

    // ID of current state
    msg->State_ID = mdlSM_getStateID();

    // Enable flags
    u16_dummy = EnableFlags;                // Byte order in memory is little endian
    msg->EnableFlags_LSB = u16_dummy;
    msg->EnableFlags_MSB = (u16_dummy >> 8);
}


//------------------------------------------------------------------------------------------------
/*!@brief   Writes data to local buffer for transmission of Info CAN message.
 *
 *@ref      mdlCAN_InfoMsg_Layout_t,
 *@ref      e_mdlCAN_cnf_MSG__inv_Info
 *
 *@return
 *\n
 *@note     Update the contents of the CAN message which includes a standard 8-bit multiplexer.
 *          CAN msg data according to structure mdlCAN_InfoMsg_Layout_t:
 *          Byte 0 -> 8-bit multiplexer
 *          Byte 1 -> payload byte 0
 *          Byte 2 -> payload byte 1
 *          Byte 3 -> payload byte 2
 *          Byte 4 -> payload byte 3
 *          Byte 5 -> payload byte 4
 *          Byte 6 -> payload byte 5
 *          Byte 7 -> payload byte 6
 *
 *          Multiplexed payload data:
 *          Mux = 0 -> temperatures
 *          Mux = 1 -> software version info (7 bytes)
 *          Mux = 2 -> error code / error flags
 *          Mux = 3 -> unconfigured
 *          Mux = 4 -> unconfigured
 *          Mux = 5 -> unconfigured
 *          Mux = 6 -> unconfigured
 *          Mux = 7 -> unconfigured
 *
 *\n
 */
static void update_Info_CANMsgData(void)
{
    const int MAX_MUX = 3;              //!< maximum multiplexer value

    static uint8_t multiplexer = 0;     //!< CAN message multiplexer
    mdlCAN_InfoMsg_Layout_t *msg;       //!< pointer to CAN msg layout structure

    uint16_t u16_dummy;
    uint8_t u8_dummy;
    uint8_t i;

    // Point to data section of message
    //
    msg = (mdlCAN_InfoMsg_Layout_t*) mdlCAN_getDataRef(e_mdlCAN_cnf_MSG__inv_Info);

    // set msg multiplexer byte
    //
    msg->multiplexer = multiplexer;

    // Set message payload depending on value of multiplexer
    //
    switch(multiplexer)
    {
    case 0:
        msg->payload_byte0 = versioninfo__SW_ID;
        msg->payload_byte1 = (uint32_t)versioninfo__SW_ID >> 8;
        msg->payload_byte2 = (uint32_t)versioninfo__SW_ID >> 16;
        msg->payload_byte3 = (uint32_t)versioninfo__SW_ID >> 24;
        msg->payload_byte4 = versioninfo__SW_VERSION_FIRST;
        msg->payload_byte5 = versioninfo__SW_VERSION_SECOND;
        msg->payload_byte6 = versioninfo__SW_VERSION_THIRD;
        break;

        // write temperatures to CAN msg
        //
    case 1: // TODO CHECK IF THIS STILL NEEDS TO BE THERE. IF NOT, REMOVE AND CORRECT CAN SYMBOLS
        // Update Temp_A
        //
        if((Temp_A > NTC_MAX_TEMP) || (ABSOLUTE_ZERO == Temp_A))
        {
            // Invalid value -> will appear as "mdlCAN_cnf_T_OFFSET" �C in CAN tool
            //
            msg->payload_byte0 = 0;
        }
        else
        {
            msg->payload_byte0 = mdlCAN_FLOAT_TO_UINT(Temp_A, mdlCAN_cnf_T_OFFSET, mdlCAN_cnf_T_FACTOR);
        }

        // Update Temp_B
        //
        if((Temp_B > NTC_MAX_TEMP) || (ABSOLUTE_ZERO == Temp_B))
        {
            // Invalid value -> will appear as "mdlCAN_cnf_T_OFFSET" �C in CAN tool
            //
            msg->payload_byte1 = 0;
        }
        else
        {
            msg->payload_byte1 = mdlCAN_FLOAT_TO_UINT(Temp_B, mdlCAN_cnf_T_OFFSET, mdlCAN_cnf_T_FACTOR);
        }

        // Update Temp_gyr_avg
        //
        if((Temp_gyr_avg > NTC_MAX_TEMP) || (ABSOLUTE_ZERO == Temp_gyr_avg))
        {
            // Invalid value -> will appear as "mdlCAN_cnf_T_OFFSET" �C in CAN tool
            //
            msg->payload_byte2 = 0;
        }
        else
        {
            msg->payload_byte2 = mdlCAN_FLOAT_TO_UINT(Temp_gyr_avg, mdlCAN_cnf_T_OFFSET, mdlCAN_cnf_T_FACTOR);
        }

        // Update Temp_uC (�C on-chip temperature)
        //
        if((Temp_uC > NTC_MAX_TEMP) || (ABSOLUTE_ZERO == Temp_uC))
        {
            // Invalid value -> will appear as "mdlCAN_cnf_T_OFFSET" �C in CAN tool
            //
            msg->payload_byte3 = 0;
        }
        else
        {
            msg->payload_byte3 = mdlCAN_FLOAT_TO_UINT(Temp_uC, mdlCAN_cnf_T_OFFSET, mdlCAN_cnf_T_FACTOR);
        }

        // Set remaining bytes to zero
        //
        msg->payload_byte4 = 0;
        msg->payload_byte5 = 0;
        msg->payload_byte6 = 0;
        break;

        // Write error code and flags to CAN msg
        //
    case 2:
        // Code of the first error that occurred. All proceeding errors will only be
        // indicated as flags until the first error is cleared
        //
        u16_dummy = mdlError_getErrorCode();

#if mdlCAN_cnf_BIG_ENDIAN == 1
        msg->payload_byte1 = u16_dummy;             // MSB
        msg->payload_byte0 = (u16_dummy >> 8);      // LSB
#else
        msg->payload_byte0 = u16_dummy;             // LSB
        msg->payload_byte1 = (u16_dummy >> 8);      // MSB
#endif
        // Error flags of all errors that have occurred
        //

        // Get flags 0 - 7
        u8_dummy = 0;
        for(i = 0; i < 8; ++i)
        {
            if(mdlError_get((mdlError_cnf_ErrorFlag_t) i))
                SETBIT(u8_dummy, i);
        }
        msg->payload_byte3 = u8_dummy;

        // Get flags 8 - 15
        u8_dummy = 0;
        for(i = 0; i < 8; ++i)
        {
            if(mdlError_get((mdlError_cnf_ErrorFlag_t) (i + 8)))
                SETBIT(u8_dummy, i);
        }
        msg->payload_byte4 = u8_dummy;


        // The following is a skeleton in case more errors to be detected are added in the error module
        // Get flags 16 - 23
        u8_dummy = 0;
        for(i = 0; i < 8; ++i)
        {
            if(mdlError_get((mdlError_cnf_ErrorFlag_t) (i + 16)))
                SETBIT(u8_dummy, i);
        }
        msg->payload_byte5 = u8_dummy;

        // Get flags 24 - 31
        u8_dummy = 0;
        for(i = 0; i < 8; ++i)
        {
            if(mdlError_get((mdlError_cnf_ErrorFlag_t) (i + 24)))
                SETBIT(u8_dummy, i);
        }
        msg->payload_byte6 = u8_dummy;
        break;

    case 3:
        // Check if the SIL fault flag is set instead of getting error code from overall error
        msg->payload_byte0 = mdlError_get(e_mdlError_cnf_ErrorFlag___FAULT_SIL);
        break;

    case 4:
    case 5:
    case 6:
    case 7:
        // do nothing
        break;

    default:
        // do nothing
        break;
    }

    // Advance multiplexer
    //
    if(++multiplexer > MAX_MUX)
    {
        // reset multiplexer to zero
        //
        multiplexer = 0;
    }
}

//------------------------------------------------------------------------------------------------
/*!@brief   Reads data from local message buffer filled by received Control CAN message,
 *          formats and saves to global vars.
 *          If data in local buffer is not up to date, global vars will be reset
 *
 *@ref      mdlCAN_ControlMsg_Layout_t,
 *@ref      e_mdlCAN_cnf_MSG__inv_Control
 *
 *@return
 *\n
 *@note     Call regularly.
 *\n
 */
static void read_Control_CANMsgData(void)
{
     // Check if local data is up to date
     //

    uint8_t mux = 0;     //!< CAN message multiplexer
    if(mdlCAN_dataUpdated(e_mdlCAN_cnf_MSG__inv_ControlMux))
    {

        // Pointer to message received from CAN
        //
        mdlCAN_ControlMux_Layout_t *msg_rx2;
        msg_rx2 = (mdlCAN_ControlMux_Layout_t*) mdlCAN_getDataRef(e_mdlCAN_cnf_MSG__inv_ControlMux);

        mux = msg_rx2->multi;

        switch(mux)
        {
            // write temperatures to CAN msg
        //
           case 0:
//               INV_Control.clearError = msg_rx2->controlSignal;
//               INV_Control.changeState = msg_rx2->controlSignal;
               break;
           case 1:
//               INV_Control.enableOutput = msg_rx2->controlSignal;
               break;
           case 2:
//               INV_Control.changeState = msg_rx2->controlSignal;
               break;

        }
//        if(INV_Control.clearError == 1)   { clearSignal = true;}
//        if(INV_Control.enableOutput == 1) { enableSignal = true;}
//        if(INV_Control.enableOutput == 0) { enableSignal = false;}
    }

//    //
//    // Data not up to date -> reset flags to defaults
//    //
//    else
//    {
////        INV_Control.enableOutput = 0;
////        INV_Control.clearError = 0;
//    }
}


//------------------------------------------------------------------------------------------------
/*!@brief   Reads data from local message buffer received over CAN to update the values of system
 *          trips. Following that, calls the DAC re-init function to update the DAC values to
 *          actually update the trip values.
 *          Reads data from local message buffer received over CAN to update the value of the peak
 *          gyrator reference current. After the value is read, it is updated in the state machine.
 *          If data in local buffer is not updated, global variables and DAC values will be reset
 *          to default values.
 *          Values are updated only when the system is in standby mode.
 *
 *@ref      mdlCAN_TripsUpdate_Layout_t,
 *@ref      e_mdlCAN_cnf_MSG__inv_TripsUpdate
 *
 *@return
 *\n
 *@note     Call regularly.
 *\n
 */
static void read_DACupdate_CANMsgData(void)
{
    // Dummy variables to hold direct messages from CAN before converting them to float
    //
    uint16_t u16_LSB        =   0;
    uint16_t u16_MSB        =   0;
    uint16_t u16_dummy      =   0;
    float    peakRefUpdate   =   0.0;
    int      StateID        =   mdlSM_getStateID();

    if (StateID == e_mdlSM_cnf_State__Standby) {
        if (mdlCAN_dataUpdated(e_mdlCAN_cnf_MSG__inv_IVTripsUpdate)) {

            // Pointer to message received from CAN and
            // point to data section of message
            //
            mdlCAN_TripsUpdate_Layout_t *msg_rx;
            msg_rx = (mdlCAN_TripsUpdate_Layout_t*) mdlCAN_getDataRef(e_mdlCAN_cnf_MSG__inv_IVTripsUpdate);

            // Update gyrator voltage maximum trip value
            //
            u16_LSB = msg_rx->v_gyr_trip_LSB;
            u16_MSB = msg_rx->v_gyr_trip_MSB;
            IV_TripsUpdate.V_GYR_Trip_Update = (u16_MSB << 8) + u16_LSB;
            newControlTrips[update_VgyrTripMax] = IV_TripsUpdate.V_GYR_Trip_Update;

            // Update gyrator current maximum trip value
            //
            u16_LSB = msg_rx->i_gyr_trip_LSB;
            u16_MSB = msg_rx->i_gyr_trip_MSB;
            IV_TripsUpdate.I_GYR_Trip_Update = (u16_MSB << 8) + u16_LSB;
            newControlTrips[update_IgyrTripMax] = IV_TripsUpdate.I_GYR_Trip_Update;

            // Update inverter current maximum trip value
            //
            u16_LSB = msg_rx->i_inv_trip_LSB;
            u16_MSB = msg_rx->i_inv_trip_MSB;
            IV_TripsUpdate.I_INV_Trip_Update = (u16_MSB << 8) + u16_LSB;
            newControlTrips[update_IinvTripMax] = IV_TripsUpdate.I_INV_Trip_Update;

            // Update the comparator DACs with new values
            //
            mdlCMPSS_DACvalueUpdate(newControlTrips);


            // Update gyrator peak current reference
            //
            u16_LSB = msg_rx->i_gyr_ref_LSB;
            u16_MSB = msg_rx->i_gyr_ref_MSB;
            u16_dummy = (u16_MSB << 8) + u16_LSB;

            // Convert peak current reference to float and update value in state machine
            //
            peakRefUpdate = mdlCAN_UINT_TO_FLOAT(u16_dummy, 0, 0.1);
            fullbridge_updatePeakRef(peakRefUpdate);

            // Updating the IPS_TripsUpdate variable is redundant. Kept this structure
            // for consistency and posterity.
            // New trips can be directly assigned to array at the summation
            // No "conversion to float" necessary since resolution is enough
            // as is over CAN. Checked with several values.
        }

//        // Supply and bus voltage trips. Partially implemented, NOT IN USE.
//        //
//        if (mdlCAN_dataUpdated(e_mdlCAN_cnf_MSG__inv_VTripsUpdate)) {
//
//            mdlCAN_SupplyTripUpdate_Layout_t *msg_rx;
//            msg_rx = (mdlCAN_SupplyTripUpdate_Layout_t*) mdlCAN_getDataRef(e_mdlCAN_cnf_MSG__inv_VTripsUpdate);
//
//            u16_LSB = msg_rx->v_24v_tmax_LSB;
//            u16_MSB = msg_rx->v_24v_tmax_MSB;
//            V_TripsUpdate.V_24V_MaxT_Update = (u16_MSB << 8) + u16_LSB;
//            newControlTrips[update_VsupplyTripMax] = V_TripsUpdate.V_24V_MaxT_Update;
//
//            u16_LSB = msg_rx->v_24v_tmin_LSB;
//            u16_MSB = msg_rx->v_24v_tmin_MSB;
//            V_TripsUpdate.V_24V_MinT_Update = (u16_MSB << 8) + u16_LSB;
//            newControlTrips[update_VsupplyTripMin] = V_TripsUpdate.V_24V_MinT_Update;
//
//            u16_LSB = msg_rx->v_bus_tmax_LSB;
//            u16_MSB = msg_rx->v_bus_tmax_MSB;
//            V_TripsUpdate.V_Bus_MaxT_Update = (u16_MSB << 8) + u16_LSB;
//            newControlTrips[update_VbusTripMax] = V_TripsUpdate.V_Bus_MaxT_Update;
//
//            u16_LSB = msg_rx->v_bus_tmin_LSB;
//            u16_MSB = msg_rx->v_bus_tmin_MSB;
//            V_TripsUpdate.V_Bus_MinT_Update = (u16_MSB << 8) + u16_LSB;
//            newControlTrips[update_VbusTripMin] = V_TripsUpdate.V_Bus_MinT_Update;
//
//            mdlCMPSS_DACvalueUpdate(newControlTrips);
//
//        }

        else {
            // do nothing, leave DAC values to last transmitted values
            //
        }
    }
}


//------------------------------------------------------------------------------------------------
/*!@brief   Reads data from local message buffer received over CAN to calculate and update
 *          the values of CLA coefficients.
 *
 *@ref      mdlCAN_CLAcoeffs_Layout_t,
 *@ref      e_mdlCAN_cnf_MSG__inv_CLAcoeffs
 *
 *@return
 *\n
 *@note     Call regularly.
 *\n
 */
static void read_CLAupdate_CANMsgData(void)
{
    // Dummy variables to hold direct messages from CAN before converting them to float
    //
    uint16_t u16_LSB        =   0u;
    uint16_t u16_MSB        =   0u;
    uint16_t u16_dummy      =   0u;
    float    f_s_h          =   0.0f;
    float    f_0_h          =   0.0f;
    float    F              =   0.0f;
    float    K_a_h          =   0.0f;
    int      StateID        =   mdlSM_getStateID();

    if (StateID == e_mdlSM_cnf_State__Standby) {
        if(mdlCAN_dataUpdated(e_mdlCAN_cnf_MSG__inv_CLAcoeffs)) {
            mdlCAN_CLAcoeffs_Layout_t *msg_rx;
            msg_rx = (mdlCAN_CLAcoeffs_Layout_t*) mdlCAN_getDataRef(e_mdlCAN_cnf_MSG__inv_CLAcoeffs);

            u16_LSB = msg_rx->inv_fsh_LSB;
            u16_MSB = msg_rx->inv_fsh_MSB;
            u16_dummy = (u16_MSB << 8) + u16_LSB;
            f_s_h = mdlCAN_UINT_TO_FLOAT(u16_dummy, 0.5, 1);


            u16_LSB = msg_rx->inv_f0h_LSB;
            u16_MSB = msg_rx->inv_f0h_MSB;
            u16_dummy = (u16_MSB << 8) + u16_LSB;
            f_0_h = mdlCAN_UINT_TO_FLOAT(u16_dummy, 0.5, 1);


            u16_LSB = msg_rx->inv_F_LSB;
            u16_MSB = msg_rx->inv_F_MSB;
            u16_dummy = (u16_MSB << 8) + u16_LSB;
            F = mdlCAN_UINT_TO_FLOAT(u16_dummy, 0.05, 0.1);


            u16_LSB = msg_rx->inv_Kah_LSB;
            u16_MSB = msg_rx->inv_Kah_MSB;
            u16_dummy = (u16_MSB << 8) + u16_LSB;
            K_a_h = mdlCAN_UINT_TO_FLOAT(u16_dummy, 0.5, 1);

            // Calculate discrete coefficients
            //
            discreteCoeffs[coeff_K_V_z] = K_a_h * tan((M_PI * f_0_h) / f_s_h) / (2* M_PI * f_0_h);
            discreteCoeffs[coeff_bv2] = 200 * M_PI * f_0_h * ((1 / F) + (1 / tan((M_PI * f_0_h) / f_s_h)));
            discreteCoeffs[coeff_bv1] = (400 * M_PI * f_0_h) / F;
            discreteCoeffs[coeff_bv0] = (float) (200.0f * M_PI * f_0_h * ((1.0f / F) - (1.0F / tan((M_PI * f_0_h) / f_s_h))));
            discreteCoeffs[coeff_av2] = 200 * M_PI * f_0_h * ((1 / tan((M_PI * f_0_h) / f_s_h)) + F);
            discreteCoeffs[coeff_av1] = (-400 * M_PI * f_0_h) / tan((M_PI * f_0_h) / f_s_h);
            discreteCoeffs[coeff_av0] = 200 * M_PI * f_0_h * ((1 / tan((M_PI * f_0_h) / f_s_h)) - F);

            // Calculate normalizad coefficients
            //
            b2 = discreteCoeffs[coeff_K_V_z] * (discreteCoeffs[coeff_bv2] / discreteCoeffs[coeff_av2]);
            b1 = discreteCoeffs[coeff_K_V_z] * (discreteCoeffs[coeff_bv1] / discreteCoeffs[coeff_av2]);
            b0 = discreteCoeffs[coeff_K_V_z] * (discreteCoeffs[coeff_bv0] / discreteCoeffs[coeff_av2]);
            a1 = discreteCoeffs[coeff_av1] / discreteCoeffs[coeff_av2];
            a0 = discreteCoeffs[coeff_av0] / discreteCoeffs[coeff_av2];
        }
    }
}


//--------------------------------------------------------------------------------
//
// CLA Initialization
//
// Description: This function will
// - copy over code and const from flash to CLA program and data ram respectively
// - Initialize the task vectors (MVECTx)
// - setup each task's trigger
// - enable each individual task
// - map program and data spaces to the CLA
// - run any one-time initialization task
//
// Please note that the CLA can only run code and access data that is in RAM.
// the user must assign constants (tables) to FLASH, and copy them over to
// RAM at run-time. They must be copied to a RAM that lies in the address space
// of the CLA, and prior to giving the CLA control over that space
//
//--------------------------------------------------------------------------------
static void initCla1( void )
{
    // Copy the program and constants from FLASH to RAM before configuring
    // the CLA
    //
#if defined(_FLASH)
    memcpy((uint32_t *) &Cla1ProgRunStart, (uint32_t *) &Cla1ProgLoadStart,
        (uint32_t)&Cla1ProgLoadSize );
    memcpy((uint32_t *) &Cla1ConstRunStart, (uint32_t *) &Cla1ConstLoadStart,
        (uint32_t)&Cla1ConstLoadSize );
#endif //defined(_FLASH)

    EALLOW;

    // CLA Program will reside in RAMLS0 (RAMLS1 spare) and data in RAMLS4, RAMLS5
    //
    MemCfg_setCLAMemType(MEMCFG_SECT_LS0, MEMCFG_CLA_MEM_PROGRAM);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS1, MEMCFG_CLA_MEM_PROGRAM);
//    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS0 = 1U;
//    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS1 = 1U;
//    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS2 = 0U;
//    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS3 = 0U;
//    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS4 = 0U;
//    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS5 = 0U;
//    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS6 = 0U;
//    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS7 = 0U;

    // Select CLA as the master of RAMLS0, RAMSL1, RAMLS4, RAMLS5
    //
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS0, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS1, MEMCFG_LSRAMMASTER_CPU_CLA1);
//    MemCfgRegs.LSxMSEL.bit.MSEL_LS0 = 1U;
//    MemCfgRegs.LSxMSEL.bit.MSEL_LS1 = 1U;
//    MemCfgRegs.LSxMSEL.bit.MSEL_LS2 = 0U;
//    MemCfgRegs.LSxMSEL.bit.MSEL_LS3 = 0U;
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS4, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS5, MEMCFG_LSRAMMASTER_CPU_CLA1);
//    MemCfgRegs.LSxMSEL.bit.MSEL_LS4 = 1U;
//    MemCfgRegs.LSxMSEL.bit.MSEL_LS5 = 1U;
//    MemCfgRegs.LSxMSEL.bit.MSEL_LS6 = 0U;
//    MemCfgRegs.LSxMSEL.bit.MSEL_LS7 = 0U;


    // Suppressing #770-D conversion from pointer to smaller integer
    // The CLA address range is 16 bits so the addresses passed to the MVECT
    // registers will be in the lower 64KW address space. Turn the warning
    // back on after the MVECTs are assigned addresses
    //

    // What is this??
#pragma diag_suppress = 770

    // Assign the task vectors and set the triggers for task 1 and 2
    //
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_1, (uint16_t) &Cla1Task1);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_2, (uint16_t) &Cla1Task2);
//    Cla1Regs.MVECT1 = (uint16_t)&Cla1Task1;
//    Cla1Regs.MVECT2 = (uint16_t)&Cla1Task2;
//    Cla1Regs.MVECT7 = (uint16_t)&Cla1Task7;

//    DmaClaSrcSelRegs.CLA1TASKSRCSEL1.bit.TASK1 = 1U; //ADCA0
//    DmaClaSrcSelRegs.CLA1TASKSRCSEL1.bit.TASK2 = 0U; //Software
//    DmaClaSrcSelRegs.CLA1TASKSRCSEL2.bit.TASK7 = 0U; //Software

    // Set the ADC-B interrupt 1 as the trigger for task 1
    // Refer to mdlADC_cnf.h for more details.
    //
    CLA_setTriggerSource(CLA_TASK_1, CLA_TRIGGER_ADCB1);

    // Software trigger is the default, so the following
    // statement is strictly not required.
    //
    CLA_setTriggerSource(CLA_TASK_2, CLA_TRIGGER_SOFTWARE);
    CLA_setTriggerSource(CLA_TASK_3, CLA_TRIGGER_SOFTWARE);

    // Enable the IACK instruction to start a task on CLA in software
    // for CLA1 tasks. Also, globally enable  a
    // subset of tasks by writing to their respective bits in the
    // MIER register
    //

    CLA_enableIACK(CLA1_BASE);
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_1 | CLA_TASKFLAG_2 | CLA_TASKFLAG_3);

    // The background task will be triggered by software; it shares
    // the same trigger source as task 8. Disable the hardware triggering
    // mechanism for the background task (if it is enabled) and then
    // set the trigger source for task 8 to 0 indicating a software
    // trigger.
    //
    // Enable the background task and start it. Enabling the background
    // task disables task 8.
    //

#pragma diag_warning = 770

    EDIS;
}

    //-------------------------
    // Interrupt Service Routines
    //*************************

//------------------------------------------------------------------------------------------------
/*!@brief   Update temperature readings.
 *
 *@return   none
 *
 *\n
 */
static void updateTemperatures(void)
{
    // Get on-chip temperature
    //
    Temp_uC = mdlADC_get_Temp_uC();

    // Determine maximum NTC temperature (used for fan control)
    //
    Temp_max = ABSOLUTE_ZERO;

    if(Temp_A > Temp_max)
    {
        Temp_max = Temp_A;
    }
    if(Temp_B > Temp_max)
    {
        Temp_max = Temp_B;
    }
}

static void setBootROMConfiguration(void)
{
    EALLOW;

    // Emulate Standalone BOOT, like when debugger is not connected
    //

    // Emulation address of EMU-BOOTPIN-CONFIG register
    //
//    (*((volatile uint32_t *)(0x00000D00))) = 0xA5FFFFFF;

    //HWREG(0x00000D00) = 0xA5FFFFFF;

    // Emulation BOOT - branch to Flash Entry Point
    //

    // Emulation address of EMU-BOOTPIN-CONFIG register
    //
    (*((volatile uint32_t *)(0x00000D00))) = 0xA5FFFFFF;

    // Emulation address of EMU-BOOTDEF-LOW register
//    (*((volatile uint32_t *)(0x00000D04))) = 0x00000003;

    EDIS;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCTION SECTION - END
//=============================================================================


/******************************************************************************
* THESE FILES ARE COPYRIGHT OF IPT TECHNOLOGY GMBH. ALL RIGHTS RESERVED.
* UNAUTHORISED COMMERCIAL USE, REPRODUCTION OR DISTRIBUTION OF THESE FILES
* MAY LEAD TO PROSECUTION.
*****************************************************************************/


/** @}*/
