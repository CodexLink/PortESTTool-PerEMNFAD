/*
    Name: IoT MesC Library Core Header, Two-In-One
    Created by: Janrey "CodexLink" Licas
    Created on: 11/14/2019 - 21:23
*/

#pragma once // A Normal Declaration of Anti-Duplicate Guard.

/*
    ! >|- definition |> Device Definitions -|<
        * |> Each device has its own functionality and with that, I want to combine the libraries and
        * functions of the two controllers for formality.
        * Please respect the device, on where you want to upload / burn the ino files. Wrong definition would occur abnormalities.

    ! NOTE
        * The name of the device was converted to Hexadecimal because of the desire of something formal. TLDR; Personal Preference
*/
#define IOT_DEVICE_CONTROLLER_AVR_DATASENS 0x4e6f64654d4355
#define IOT_DEVICE_CONTROLLER_ESP_SERVICE_NET 0x41726475696e6f20415652
#define DEBUG_ENABLED

/*
    ! >|- definition |> Universal Serial Filter -<|
*/
#ifdef DEBUG_ENABLED
    #if Cmd_Func == println || print
        #define SerialH_Call(Cmd_Func, Params) Serial.Cmd_Func(Params)
        #define SerialL_Call(Cmd_Func, Params) Serial1.Cmd_Func(Params)
    #else
        #define SerialH_Call(Cmd_Func, Params)
        #define SerialL_Call(Cmd_Func, Params)
#endif
/*
    ! >|- Macro Protection Layer 1 -|<

    * |> Checks device definitions logic. It can detect both defined, or not defined.
    * It occurs errors on one of the following:
    *   |> Both Device Definitions are defined.
    *   |> Both Device Definitions are not defined.

    ! NOTE
        * Any other such illegal device definitions will not be considered, unless you define it here.
*/

// ! Device Definition Phase 1
#if !defined(IOT_DEVICE_CONTROLLER_AVR_DATASENS) && !defined(IOT_DEVICE_CONTROLLER_ESP_SERVICE_NET)
    #error "IoTMesC Core Initialization Halted. No other such candidate device definition could be equal to current set device definition."
#elif defined(IOT_DEVICE_CONTROLLER_AVR_DATASENS) && defined(IOT_DEVICE_CONTROLLER_ESP_SERVICE_NET)
    #error "IoTMesC Core Initialization Halted. Both candidate devices are defined. Please define only one!"
#endif

// ! Macro Layer 2 Definitions for IOT_DEVICE_CONTROLLER_AVR_DATASENS
// * IOT_DEVICE_CONTROLLER_AVR_DATASENS — Device Definition Declarations
#if defined(IOT_DEVICE_CONTROLLER_AVR_DATASENS)
    #ifndef IOT_DEVICE_CONTROLLER_AVR_DATASENS_GUARD
        #define IOT_DEVICE_CONTROLLER_AVR_DATASENS_GUARD
    #endif

    #ifndef LIBRARY_IOT_AVR_GUARD
        #define LIBRARY_IOT_AVR_GUARD
        #ifdef LCD_FALLBACK_I2C
            #include "AlternativeCore/LiquidCrystal_I2C.h"
        #else
            #include <Adafruit_GFX>
            #include "PrimaryCore/TFT_ILI9163C.h"
        #endif

        #ifdef TEMP_FALLBACK_SENS
            #include "AlternativeCore/DHT.h"
        #else
            #include "PrimaryCore/Adafruit_SHT31.h"
        #endif

        #ifdef GAS_FALLBACK_SENS
            #include "AlternativeCore/MQ135.h"
        #else
            #include "PrimaryCore/CSS811.h"
        #endif

        #ifdef SERIAL_DEV_UNO
            #include <SoftwareSerial>
        #endif

        #ifdef SEGMENT_CUST_DECODER_ENABLE
            #include "PrimaryCore/ShiftOut.h"
        #endif

        #ifdef MULTIPLEXER_ENABLE
            #include "PrimaryCore/ShiftIn.h"
        #endif

        #ifdef MFRC_REQUIRE_EXTENDED_ENABLE
            #include "AlternativeCore/MFRC522Extended.h"
        #else
            #include "PrimaryCore/MFRC522.h"
        #endif

        // ! 4. Libraries with No Fallback Required When Current Library is Down / Not-Working.
        #include "PrimaryCore/MemoryFree.h"
        #include "PrimaryCore/DS1302.h"
        #include "PrimaryCore/SoftReset.h"

        // * These Libraries Doesn't Require A Copy from a Repository.
        // * That is because Arduino Files does include it already, so mostly likely you have it.
        #include <Wire>
        #include <SPI>
        #include <EEPROM>
    #endif // * Definition End Point |> LIBRARY_IOT_AVR_GUARD

/*
    * namespace |> AVR_DEV_DECL ~= Arduino AVR Device Declarations

    *     -> It Contains All Sets of Device and Sensor Pins
    *         -> Uses Namespace and ENUM for Call Identity Uniqueness

    ! Hierarchy Device Definitions

    * |> 1. Controller
    * |> 2. Seven Segmnet Decoder
    * |> 3. SPI Interfacer
    * |> 4. I^2C Interfacer
    * |> 5. Various Sensor That Doesn't Need Any Interfacer (In short, Digital Read)
    *
    ! NOTE
        * You can use all of those declarations in a following format.
        *   |> AVR_DEV_DECL::<Device>_DEF::<PROTOCOL>_PIN_DEF
        *   |> Values cannot be replaced.
*/

/*
    * definition |> LIBRARY_IOT_AVR_GUARD ~= Library Initializer with #Define Guard

    *   -> Use for Alternation of Library Use.
    *       -> Library Hierarchy:
    *           1. LCD Sensor
    *           2. TEMP Sensor
    *           3. GAS Sensor
    *           4. Software Serial
    *           4. Controllers and Stuff and Anything That Doesn't Need Any Fallback Library.
    *
    *       -> Definition Options To Declare at Arduino Sketch
    *           1. LCD_FALLBACK_I2C
    *           2. TEMP_FALLBACK_SENS
    *           3. GAS_FALLBACK_SENS
    *           4. SERIAL_DEV_UNO
    *
    ! NOTE
        * Not definiting fall back definitions will automatically process the arduino sketch.
        * To render with the latest sensor library that I currently have.
*/

    namespace IoTMesC_AVR_DEV_DECL
    {
        class IotMesC_AVR_DRVR;
        namespace SEVEN_SEG_CTRLLER_DEF : uint16_t
        {
            enum SEVEN_SEG_CONSTRAINTS : uint8_t
            {
                DATA_COUNTER_ITER = 6,
                RESERVED_MAX_ITER = 7,
                MAX_CURR_CANDIDATE_VAL = 17
            };

            const uint8_t SevenSegment_Payload[SEVEN_SEG_CONSTRAINTS::MAX_CURR_CANDIDATE_VAL][SEVEN_SEG_CONSTRAINTS::RESERVED_MAX_ITER] = {
                {1, 1, 1, 1, 1, 1, 0}, // 0
                {0, 1, 1, 0, 0, 0, 0}, // 1
                {1, 1, 0, 1, 1, 0, 1}, // 2
                {1, 1, 1, 1, 0, 0, 1}, // 3
                {0, 1, 1, 0, 0, 1, 1}, // 4
                {1, 0, 1, 1, 0, 1, 1}, // 5
                {1, 0, 1, 1, 1, 1, 1}, // 6
                {1, 1, 1, 0, 0, 0, 0}, // 7
                {1, 1, 1, 1, 1, 1, 1}, // 8
                {1, 1, 1, 1, 0, 1, 1}, // 9
                {0, 0, 0, 0, 0, 0, 1}, // Dash
                {1, 1, 1, 0, 1, 1, 1}, // A
                {1, 0, 0, 1, 1, 1, 1}, // E
                {1, 0, 0, 0, 1, 1, 1}, // F
                {0, 1, 1, 0, 0, 0, 0}, // I
                {1, 0, 1, 1, 0, 1, 1}, // S
                {1, 1, 0, 0, 1, 0, 1}  // ?
            };
        } // * namespace SEVEN_SEG_CTRLLER_DEF:uint16_t

        // ! |> 3. Sensors and Devices | Pin Declarations
        namespace SENS_N_DEVS_PIN_DECL
        {
            enum TFT_LCD_PIN_DEF : uint8_t
            {
                TFT_LCD_DC = 38,
                TFT_LCD_CS = 39
            };

            enum MFRC522_PIN_DEF : uint8_t
            {
                RFID_RST_PIN = 8,
                RFID_SS_PIN = 53
            };

            enum RTC1302_PIN_DEF : uint8_t
            {
                RESPin = 10,
                SDAPin = 11,
                SCLPin = 12
            };

            enum PIR_MINI_PIN_DEF : uint8_t
            {
                MAIN_PIN = NULL,
                LED_TRIP_PIN = NULL
            };

            enum MQ135_PIN_DEF : uint8_t
            {
                MAIN_PIN = NULL
            };

            namespace DIP_SWITCH_CONFIG_DEF
            {
                enum DIP_SWITCH_PIN_DEF : uint8_t
                {
                    SWITCH_PIN_ONE = NULL,
                    SWITCH_PIN_TWO = NULL,
                    SWITCH_PIN_THREE = NULL,
                    SWITCH_PIN_FOUR = NULL
                };
                enum SWITCH_DEFINED_MODE : uint8_t
                {
                    MCU_RESIST_INPUT = INPUT_PULLUP,
                    SWITCH_INPUT = INPUT,
                    SWITCH_OUTPUT = OUTPUT
                };
            } // * namespace DIP_SWITCH_CONFIG_DEF

        } // * namespace SENS_PERIPS_PIN_DECL

        /*
            * namespace |> UTIL_CONST_DECL ~= Utility Constant Declarations
            * -> All Declaratives are defined here specifically used for anti-magic numbers.

        */
        namespace UTIL_CONST_DECL
        {
            enum CONST_ANTI_MAGIC : uint8_t
            {
                ZERO_REAL_INT = 0,
                NULL_SET_DATA = 0,
                VAL_INDEX_OFFSET = 1,
                ARR_INDEX_OFFSET = 1,
                SEG_INDEX_DP_EXEMPT_OFFSET = 2,
                CHAR_SERIAL_BUFFER_SIZE = 128
            };
            enum MILLIS_RETURN_VAL : uint8_t
            {
                CST_RET_UNKNOWN_VAL,
                CST_RET_CURR_RESULT,
                CST_RET_PREV_RESULT,
                CST_RET_INTERV_HIT
            };

            // ! Potential Backup when TFTLCD Fails. Please Elaborate more...
            enum LCD_I2C_CONSTRAINT : uint8_t
            {
                LCD_I2C_ADDR = 0x67,
                LCD_I2C_MAX_W = 20,
                LCD_I2C_MAX_H = 4,
                LCD_I2C_POS_START_X = 0,
                LCD_I2C_POS_START_Y = 0,
                LCD_I2C_POS_END_X = LCD_I2C_POS_START_X - CONST_ANTI_MAGIC::VAL_INDEX_OFFSET,
                LCD_I2C_POS_END_y = LCD_I2C_POS_START_Y - CONST_ANTI_MAGIC::VAL_INDEX_OFFSET
            };

            enum AVR_SERIAL_DECL : uint16_t
            {
                DEFAULT_PRTRCL_BAUDRATE = 0x2580, // 9600
                HOST_BAUDRATE = 0x01c200,         // 115200
                LISTEN_BAUDRATE = 0x01c200        // 115200
            };

        } // namespace UTIL_CONST_DECL
    }

    // * Class Declarations
    class IoTMesC_AVR_DEV_DECL::IotMesC_AVR_DRVR
    {

        public:
            // * Device and Peripherals Initializers.
            inline void init_DevSens() const;
            inline void init_DevSPI() const;
            inline void init_DevWire() const;

            uint32_t SketchTimeHit(UTIL_CONST_DECL::MILLIS_RETURN_VAL ParamCondition);


            static void DIP_PINStats() const;

            void

        private:
            uint8_t DataCounter_Update[SEVEN_SEG_CTRLLER_DEF::SEVEN_SEG_CONSTRAINTS::DATA_COUNTER_ITER] = {UTIL_CONST_DECL::CONST_ANTI_MAGIC::NULL_SET_DATA};
            static uint32_t SketchTime_CurStats;
            static uint8_t SerialByteCnt;
            static uint16_t SRAM_FreeCnt;


        protected:
    };

#endif // * Definition End Point |> IOT_DEVICE_CONTROLLER_AVR_DATASENS







// * IOT_DEVICE_CONTROLLER_ESP_SERVICE_NET — Device Definition Declarations

#if defined(IOT_DEVICE_CONTROLLER_ESP_SERVICE_NET)
    #ifndef IOT_DEVICE_CONTROLLER_ESP_SERVICE_NET_GUARD
       #define IOT_DEVICE_CONTROLLER_ESP_SERVICE_NET_GUARD
    #endif

    #ifndef LIBRARY_IOT_ESP_GUARD
        #define LIBRARY_IOT_ESP_GUARD


    #endif
    namespace IoTMesC_NMCU_DEV_DECL
    {
        class IoTMesC_NMCU_DRVR;

        namespace MyNamespace
        {
            enum MyEnum
            {

            };

            enum MyEnum
            {

            };

            enum ModeFlags
            {
                DISABLED_FLAG = -2,
                ERROR_FLAG = -1,
                SUCCESS_FLAG = 0,
                IDLE_MODE = 1,
                DEBUG_MODE = 2,
                RECONATTMPT_MODE = 3,
                RETRY_MODE = 4,
                DEPENDENT_MODE = 5,
                LOW_VOLT_MODE = 6,
                EMERGENCY_MODE = 7,
                RESET_FLAG = 8

            } SetFlagHandler;

        }
        namespace MyNamespace
        {
            enum MyEnum
            {

            };
            enum MyEnum
            {

            };
        }
    }

    class IoTMesC_NMCU_DRVR
    {
    private:
        /* data */
    public:
        IoTMesC_NMCU_DRVR(/* args */) {}
        ~IoTMesC_NMCU_DRVR() {}
    };
#endif

/*
    Name: IoT MesC Library Core Header, Two-In-One
    Created by: Janrey "CodexLink" Licas
    Created on: 11/14/2019 - 21:23
*/