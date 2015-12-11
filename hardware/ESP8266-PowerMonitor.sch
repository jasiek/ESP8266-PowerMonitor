EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ESP8266-PowerMonitor-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X15 P2
U 1 1 5664CCBA
P 8000 2700
F 0 "P2" H 8000 3500 50  0000 C CNN
F 1 "CONN_01X15" V 8100 2700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15" H 8000 2700 60  0001 C CNN
F 3 "" H 8000 2700 60  0000 C CNN
	1    8000 2700
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X15 P1
U 1 1 5664CCEF
P 6800 2700
F 0 "P1" H 6800 3500 50  0000 C CNN
F 1 "CONN_01X15" V 6900 2700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15" H 6800 2700 60  0001 C CNN
F 3 "" H 6800 2700 60  0000 C CNN
	1    6800 2700
	-1   0    0    -1  
$EndComp
Text Notes 8100 3350 0    60   ~ 0
GND
Text Notes 8100 3450 0    60   ~ 0
3.3V
Text Notes 6550 3350 0    60   ~ 0
GND
Text Notes 6600 3450 0    60   ~ 0
5V
Text Notes 8100 3050 0    60   ~ 0
GPIO15\n
$Comp
L R R1
U 1 1 5664D0EB
P 7650 3700
F 0 "R1" V 7730 3700 50  0000 C CNN
F 1 "220" V 7650 3700 50  0000 C CNN
F 2 "" V 7580 3700 30  0001 C CNN
F 3 "" H 7650 3700 30  0000 C CNN
	1    7650 3700
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P3
U 1 1 5664D153
P 8000 4000
F 0 "P3" H 8000 4150 50  0000 C CNN
F 1 "CONN_01X02" V 8100 4000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 8000 4000 60  0001 C CNN
F 3 "" H 8000 4000 60  0000 C CNN
	1    8000 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 3400 7800 3400
Wire Wire Line
	7650 3400 7650 3550
Wire Wire Line
	7650 3850 7650 3950
Wire Wire Line
	7650 3950 7800 3950
Wire Wire Line
	7800 3000 7500 3000
Wire Wire Line
	7500 3000 7500 4050
Wire Wire Line
	7500 4050 7800 4050
Text Notes 8150 4000 0    60   ~ 0
+
Text Notes 8150 4100 0    60   ~ 0
-
$Comp
L CONN_01X05 P4
U 1 1 5664D204
P 6800 4300
F 0 "P4" H 6800 4600 50  0000 C CNN
F 1 "CONN_01X05" V 6900 4300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05" H 6800 4300 60  0001 C CNN
F 3 "" H 6800 4300 60  0000 C CNN
	1    6800 4300
	-1   0    0    -1  
$EndComp
Text Notes 6450 4300 0    60   ~ 0
I2C
$Comp
L CONN_01X03 P5
U 1 1 566A8677
P 8000 4700
F 0 "P5" H 8000 4900 50  0000 C CNN
F 1 "CONN_01X03" V 8100 4700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 8000 4700 60  0001 C CNN
F 3 "" H 8000 4700 60  0000 C CNN
	1    8000 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3300 7450 3300
Wire Wire Line
	7450 3300 7450 5000
Wire Wire Line
	7450 4600 7800 4600
Wire Wire Line
	7400 3400 7400 5200
Wire Wire Line
	7400 4700 7800 4700
Connection ~ 7650 3400
Wire Wire Line
	7000 3400 7350 3400
Wire Wire Line
	7350 3400 7350 4800
Wire Wire Line
	7350 4800 7800 4800
Text Notes 8150 4650 0    60   ~ 0
GND
Text Notes 8150 4750 0    60   ~ 0
3.3V\n
Text Notes 8150 4850 0    60   ~ 0
5V
Wire Wire Line
	7000 4100 7450 4100
Connection ~ 7450 4100
Wire Wire Line
	7000 4400 7400 4400
Connection ~ 7400 4400
Wire Wire Line
	7000 4500 7350 4500
Connection ~ 7350 4500
$Comp
L CONN_01X03 P6
U 1 1 566A8D76
P 6800 5100
F 0 "P6" H 6800 5300 50  0000 C CNN
F 1 "CONN_01X03" V 6900 5100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 6800 5100 60  0001 C CNN
F 3 "" H 6800 5100 60  0000 C CNN
	1    6800 5100
	-1   0    0    1   
$EndComp
Wire Wire Line
	7400 5200 7000 5200
Connection ~ 7400 4700
Wire Wire Line
	7450 5000 7000 5000
Connection ~ 7450 4600
Text Notes 6350 5150 0    60   ~ 0
1Wire
$EndSCHEMATC
