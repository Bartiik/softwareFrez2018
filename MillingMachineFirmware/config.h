#pragma once
#ifndef config

#define config

#define DEBUG

// PINOUT

#define RX0_PIN					0   // RX PIN - DO NOT USE <- CONNECTED TO USB
#define TX0_PIN					1	// TX PIN - DO NOT USE <- CONNECTED TO USB
#define X_MAX_ENDSTOP_PIN		2   // PWM PIN
#define X_MIN_ENDSTOP_PIN		3   // PWM PIN
#define SERVO_4_PIN				4   // PWM PIN
#define SERVO_3_PIN				5   // PWM PIN // Analog In 1
#define SERVO_2_PIN				6   // PWM PIN
#define N_C						7   // NOT CONNECTED, DO NOT USE
#define D8_ENABLE_PIN			8   // PWM PIN
#define D9_ENABLE_PIN			9   // PWM PIN
#define D10_ENABLE_PIN			10  // PWM PIN
#define SERVO_1_PIN				11  // PWM PIN
#define PS_ON_PIN				12  // PWM PIN
#define LED_PIN					13  // PWM PIN
#define Y_MIN_ENDSTOP_PIN		14  // TX3
#define Y_MAX_ENDSTOP_PIN		15  // RX3
#define UNKNOWN_PIN				16  // TX2
#define UNKNOWN_PIN				17  // RX2
#define Z_MIN_ENDSTOP_PIN		18  // TX1
#define Z_MAX_ENDSTOP_PIN		19  // RX1
#define UNKNOWN_PIN				20  // SDA
#define UNKNOWN_PIN				21  // SCL
#define N_C						22  // NOT CONNECTED, DO NOT USE
#define UNKNOWN_PIN				23
#define E1_ENABLE_PIN			24
#define UNKNOWN_PIN				25
#define E1_STEP_PIN				26
#define UNKNOWN_PIN				27
#define E1_DIR_PIN				28
#define UNKNOWN_PIN				29
#define E2_ENABLE_PIN			30
#define UNKNOWN_PIN				31
#define UNKNOWN_PIN				32
#define UNKNOWN_PIN				33
#define E2_DIR_PIN				34
#define UNKNOWN_PIN				35
#define E2_STEP_PIN				36
#define UNKNOWN_PIN				37
#define X_ENABLE_PIN			38
#define UNKNOWN_PIN				39
#define UNKNOWN_PIN				40
#define UNKNOWN_PIN				41
#define UNKNOWN_PIN				42
#define UNKNOWN_PIN				43
#define UNKNOWN_PIN				44  // PWM PIN
#define UNKNOWN_PIN				45  // PWM PIN
#define Z_STEP_PIN				46  // PWM PIN
#define UNKNOWN_PIN				47
#define Z_DIR_PIN				48
#define UNKNOWN_PIN				49
#define UNKNOWN_PIN				50  // MISO
#define UNKNOWN_PIN				51  // MOSI
#define UNKNOWN_PIN				52
#define UNKNOWN_PIN				53
#define X_STEP_PIN				A0  // ANALOG PIN
#define X_DIR_PIN				A1  // ANALOG PIN
#define Y_ENABLE_PIN			A2  // ANALOG PIN
#define UNKNOWN_PIN				A3  // ANALOG PIN
#define UNKNOWN_PIN				A4  // ANALOG PIN
#define UNKNOWN_PIN				A5  // ANALOG PIN
#define Y_STEP_PIN				A6  // ANALOG PIN
#define Y_DIR_PIN				A7  // ANALOG PIN
#define Z_ENABLE_PIN			A8  // ANALOG PIN
#define UNKNOWN_PIN				A9  // ANALOG PIN
#define UNKNOWN_PIN				A10 // ANALOG PIN
#define UNKNOWN_PIN				A11 // ANALOG PIN
#define UNKNOWN_PIN				A12 // ANALOG PIN
#define THERM_0_PIN				A13 // ANALOG PIN
#define THERM_1_PIN				A14 // ANALOG PIN
#define THERM_2_PIN				A15 // ANALOG PIN

// possible States

#define INIT_STATE				0
#define IDLE_STATE				1
#define COMMAND_STATE			2
#define ERROR_STATE				3

//					PARAMETERS

// SERIAL
#define BAUD_RATE				115200
#define DUMMY_VALUE				1234.56789




//					STATIC COMMANDS

#define COMMUNICATION_TEST_COMMAND			"unknown command"
#define STANDARD_REPLY_COMMAND				"unknown command"
#define ROTATE_TABLE_COMMAND				"unknown command"
#define BED_LEVELING_COMMAND				"unknown command"
#define ERROR_COMMAND						"unknown command"
#define BEGIN_PROCESS_COMMAND				"unknown command"
#define END_PROCESS_COMMAND					"unknown command"
#define RESET_COMMAND						"unknown command"



#endif // !