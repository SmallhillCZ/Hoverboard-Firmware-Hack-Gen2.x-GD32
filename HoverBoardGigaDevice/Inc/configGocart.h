#ifndef CONFIG_GOCART_H
#define CONFIG_GOCART_H

// GoCart (https://github.com/SmallhillCZ/gocart): hoverboard Manta, split boards TT-SD2.2 (TaoTao 2018), GD32F130C8T6.
// Selected via -D CONFIG_GOCART in platformio.ini (see configSelect.h).
// Board role comes from the build flag: -D MASTER (board with button, charger socket and buzzer)
// or -D SLAVE (board on the white flat master-slave cable).
// Control: ESP32 on the master's REMOTE header (USART0 = PB6/PB7) with REMOTE_UART protocol (remoteUart.c).

#if !defined(MASTER) && !defined(SLAVE)
	#error "configGocart.h: build with -D MASTER or -D SLAVE"
#endif

#ifdef GD32F130		// TARGET = 1
	#define LAYOUT 1
	#define LAYOUT_SUB 1	// layout 2.1.1 (ex 2.0)
#else
	#error "configGocart.h: only GD32F130 (TARGET=1) is used on TT-SD2.2"
#endif

#define BLDC_SINE			// silent sine-pwm motor control

#define DRIVING_MODE 0	//  0=pwm, 1=speed in revs/s*1024, 2=torque in NewtonMeter*1024, 3=iOdometer

#define BAT_CELLS         	10        // Manta: 36 V 10S
// BATTERY_LOW_SHUTOFF intentionally NOT defined: the board must run from a current-limited
// lab supply below 32 V for the first power-up. Below BAT_LOW_DEAD it only beeps.
//#define BATTERY_LOW_SHUTOFF
#define BATTERY_LOW_BEEP

#define BEEP_BACKWARDS

#if defined(MASTER)

	#ifdef GOCART_TEST
		// bench test without ESP32: motors zigzag slowly (pwm +-200 of 1000), LED panel follows the hall sensors
		#define REMOTE_DUMMY
		#define REMOTE_PERIOD 6
		#define TEST_HALL2LED
	#else
		#define REMOTE_UART		// ESP32 sends '/' iSpeed iSteer wStateMaster wStateSlave CRC16
	#endif

	#define SPEED_COEFFICIENT   -1	// direction is handled in the ESP32 software
	#define STEER_COEFFICIENT   1

	#define MASTER_OR_SINGLE
#endif

#if defined(MASTER) || defined(SLAVE)
	#define MASTERSLAVE_USART		1 	// PA2/PA3, original master-slave 4pin header (white flat cable)
#endif

#if defined(REMOTE_UART)
	#define REMOTE_USART			0 	// PB6/PB7, REMOTE header G-T-R-5V (former 433 MHz receiver)
#endif


#ifdef MASTER_OR_SINGLE
	#define INACTIVITY_TIMEOUT 	8        	// Minutes of not driving until poweroff (not very precise)

	#define CELL_LOW_LVL1     3.5       // Gently beeps, show green battery symbol above this Level.
	#define CELL_LOW_LVL2     3.3       // Battery almost empty, show orange battery symbol above this Level. Charge now!
	#define CELL_LOW_DEAD     3.0       // show red battery symbol above this Level (no shutoff, see above)
#endif


#define DC_CUR_LIMIT     		15        // Motor DC current limit in amps

#endif		// CONFIG_GOCART_H
