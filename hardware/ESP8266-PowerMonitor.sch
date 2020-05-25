EESchema Schematic File Version 4
EELAYER 30 0
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
L RF_Module:ESP-12F U2
U 1 1 5E9EB5E9
P 6850 3650
F 0 "U2" H 6850 4631 50  0000 C CNN
F 1 "ESP-12F" H 6850 4540 50  0000 C CNN
F 2 "RF_Module:ESP-12E" H 6850 3650 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 6500 3750 50  0001 C CNN
	1    6850 3650
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AMS1117-3.3 U1
U 1 1 5E9ED335
P 4150 3700
F 0 "U1" H 4150 3942 50  0000 C CNN
F 1 "AMS1117-3.3" H 4150 3851 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4150 3900 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 4250 3450 50  0001 C CNN
	1    4150 3700
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5E9FB45C
P 4150 3150
F 0 "JP1" H 4150 3355 50  0000 C CNN
F 1 "3.3V BYPASS" H 4150 3264 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_TrianglePad1.0x1.5mm" H 4150 3150 50  0001 C CNN
F 3 "~" H 4150 3150 50  0001 C CNN
	1    4150 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5E9FE989
P 3600 3850
F 0 "C1" H 3715 3896 50  0000 L CNN
F 1 "0.1uF" H 3715 3805 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3638 3700 50  0001 C CNN
F 3 "~" H 3600 3850 50  0001 C CNN
	1    3600 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 5E9FF675
P 4650 3850
F 0 "C2" H 4768 3896 50  0000 L CNN
F 1 "10uF" H 4768 3805 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_4x5.3" H 4688 3700 50  0001 C CNN
F 3 "~" H 4650 3850 50  0001 C CNN
	1    4650 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 3700 3600 3700
Connection ~ 3600 3700
Wire Wire Line
	4450 3700 4650 3700
Wire Wire Line
	3600 4000 4150 4000
Wire Wire Line
	4150 4000 4650 4000
Connection ~ 4150 4000
Wire Wire Line
	3600 3700 3600 3150
Wire Wire Line
	3600 3150 4000 3150
Wire Wire Line
	4300 3150 4650 3150
Wire Wire Line
	4650 3150 4650 3700
Connection ~ 4650 3700
Wire Wire Line
	4650 3150 4650 2250
Wire Wire Line
	4650 2250 5200 2250
Wire Wire Line
	6850 2250 6850 2850
Connection ~ 4650 3150
Wire Wire Line
	4650 4000 4650 4900
Wire Wire Line
	6850 4900 6850 4350
Connection ~ 4650 4000
Wire Wire Line
	4650 4900 5800 4900
$Comp
L Device:R R1
U 1 1 5EA0AB12
P 5550 3050
F 0 "R1" V 5450 3050 50  0000 C CNN
F 1 "10k" V 5550 3050 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5480 3050 50  0001 C CNN
F 3 "~" H 5550 3050 50  0001 C CNN
	1    5550 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5EA0C348
P 5550 3250
F 0 "R2" V 5450 3250 50  0000 C CNN
F 1 "10k" V 5550 3250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5480 3250 50  0001 C CNN
F 3 "~" H 5550 3250 50  0001 C CNN
	1    5550 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5700 3050 5800 3050
Wire Wire Line
	6250 3250 5700 3250
Wire Wire Line
	5400 3050 5200 3050
Wire Wire Line
	5200 3050 5200 2250
Connection ~ 5200 2250
Wire Wire Line
	5200 2250 6850 2250
Wire Wire Line
	5400 3250 5200 3250
Wire Wire Line
	5200 3250 5200 3050
Connection ~ 5200 3050
$Comp
L Device:R R4
U 1 1 5EA0DCAB
P 8200 3050
F 0 "R4" V 8100 3050 50  0000 C CNN
F 1 "10k" V 8200 3050 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 8130 3050 50  0001 C CNN
F 3 "~" H 8200 3050 50  0001 C CNN
	1    8200 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 5EA0EA76
P 8200 3950
F 0 "R6" V 8100 3950 50  0000 C CNN
F 1 "10k" V 8200 3950 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 8130 3950 50  0001 C CNN
F 3 "~" H 8200 3950 50  0001 C CNN
	1    8200 3950
	0    1    1    0   
$EndComp
Wire Wire Line
	7450 3050 7900 3050
Wire Wire Line
	8800 2250 8800 3050
Wire Wire Line
	8800 3050 8350 3050
Connection ~ 6850 2250
Wire Wire Line
	8800 4900 8800 3950
Wire Wire Line
	8800 3950 8350 3950
Connection ~ 6850 4900
Wire Wire Line
	8050 3950 7450 3950
$Comp
L Switch:SW_DIP_x01 SW1
U 1 1 5EA11774
P 5800 3850
F 0 "SW1" V 5754 3980 50  0000 L CNN
F 1 "SW_RESET" V 5845 3980 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_Push_1P1T_NO_6x6mm_H9.5mm" H 5800 3850 50  0001 C CNN
F 3 "~" H 5800 3850 50  0001 C CNN
	1    5800 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	5800 3550 5800 3050
Connection ~ 5800 3050
Wire Wire Line
	5800 3050 6250 3050
Wire Wire Line
	5800 4150 5800 4900
Connection ~ 5800 4900
Wire Wire Line
	5800 4900 6850 4900
Wire Wire Line
	9350 3250 8800 3250
Wire Wire Line
	8800 3250 8800 3050
Connection ~ 8800 3050
Wire Wire Line
	9350 3350 8400 3350
Wire Wire Line
	8400 3350 8400 3150
Wire Wire Line
	8400 3150 7450 3150
Wire Wire Line
	9350 3450 8300 3450
Wire Wire Line
	8300 3450 8300 3350
Wire Wire Line
	8300 3350 7450 3350
Wire Wire Line
	9350 3550 7900 3550
Wire Wire Line
	7900 3550 7900 3050
Connection ~ 7900 3050
Wire Wire Line
	7900 3050 8050 3050
Wire Wire Line
	9350 3650 8800 3650
Wire Wire Line
	8800 3650 8800 3950
Connection ~ 8800 3950
$Comp
L Device:R R5
U 1 1 5EA1A4E0
P 8200 3250
F 0 "R5" V 8300 3250 50  0000 C CNN
F 1 "10k" V 8200 3250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 8130 3250 50  0001 C CNN
F 3 "~" H 8200 3250 50  0001 C CNN
	1    8200 3250
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 5EA1E8A4
P 7750 5400
F 0 "R3" H 7820 5446 50  0000 L CNN
F 1 "470" V 7750 5350 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 7680 5400 50  0001 C CNN
F 3 "~" H 7750 5400 50  0001 C CNN
	1    7750 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 4900 7650 4900
Wire Wire Line
	7750 5550 7750 5700
Wire Wire Line
	7650 5700 7650 4900
Connection ~ 7650 4900
Wire Wire Line
	7650 4900 8800 4900
$Comp
L Converter_ACDC:HLK-PM03 PS1
U 1 1 5EA0B50B
P 2850 3850
F 0 "PS1" H 2850 4175 50  0000 C CNN
F 1 "HLK-PM03" H 2850 4084 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_HiLink_HLK-PMxx" H 2850 3550 50  0001 C CNN
F 3 "http://www.hlktech.net/product_detail.php?ProId=59" H 3250 3500 50  0001 C CNN
	1    2850 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3750 3450 3750
Wire Wire Line
	3450 3750 3450 3700
Wire Wire Line
	3450 3700 3600 3700
Wire Wire Line
	3250 3950 3450 3950
Wire Wire Line
	3450 3950 3450 4000
Wire Wire Line
	3450 4000 3600 4000
Connection ~ 3600 4000
$Comp
L Device:C C3
U 1 1 5EA34A36
P 5100 3850
F 0 "C3" H 5215 3896 50  0000 L CNN
F 1 "100nF" H 5215 3805 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5138 3700 50  0001 C CNN
F 3 "~" H 5100 3850 50  0001 C CNN
	1    5100 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 3700 5100 3700
Wire Wire Line
	5100 4000 4650 4000
Text GLabel 9350 3250 2    50   Input ~ 0
+3.3V
Text GLabel 9350 3350 2    50   Input ~ 0
TXD
Text GLabel 9350 3450 2    50   Input ~ 0
RXD
Text GLabel 9350 3550 2    50   Input ~ 0
_PROG
Text GLabel 9350 3650 2    50   Input ~ 0
GND
Text GLabel 7650 5700 3    50   Input ~ 0
GND
Text GLabel 7750 5700 3    50   Input ~ 0
PULSE
Text GLabel 1450 6000 0    50   Input ~ 0
GND
Text GLabel 1450 6100 0    50   Input ~ 0
PULSE
Text GLabel 1450 6400 0    50   Input ~ 0
+3.3V
Text GLabel 1450 6500 0    50   Input ~ 0
TXD
Text GLabel 1450 6600 0    50   Input ~ 0
RXD
Text GLabel 1450 6700 0    50   Input ~ 0
_PROG
Text GLabel 1450 6800 0    50   Input ~ 0
GND
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 5EA43248
P 1900 6100
F 0 "J1" H 1872 5982 50  0000 R CNN
F 1 "CONN_PULSE" H 1872 6073 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1900 6100 50  0001 C CNN
F 3 "~" H 1900 6100 50  0001 C CNN
	1    1900 6100
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 5EA4449E
P 1900 6600
F 0 "J2" H 1872 6532 50  0000 R CNN
F 1 "CONN_PROG" H 1872 6623 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 1900 6600 50  0001 C CNN
F 3 "~" H 1900 6600 50  0001 C CNN
	1    1900 6600
	-1   0    0    1   
$EndComp
Wire Wire Line
	1450 6000 1700 6000
Wire Wire Line
	1700 6100 1450 6100
Wire Wire Line
	1450 6400 1700 6400
Wire Wire Line
	1700 6500 1450 6500
Wire Wire Line
	1450 6600 1700 6600
Wire Wire Line
	1700 6700 1450 6700
Wire Wire Line
	1450 6800 1700 6800
Text GLabel 1600 3750 0    50   Input ~ 0
AC-L
Text GLabel 1600 3950 0    50   Input ~ 0
AC-N
Text GLabel 1450 7150 0    50   Input ~ 0
AC-L
Text GLabel 1450 7250 0    50   Input ~ 0
AC-N
$Comp
L Device:Polyfuse F1
U 1 1 5EA6BA40
P 2050 3750
F 0 "F1" V 1825 3750 50  0000 C CNN
F 1 "100mA" V 1916 3750 50  0000 C CNN
F 2 "Fuse:Fuse_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2100 3550 50  0001 L CNN
F 3 "~" H 2050 3750 50  0001 C CNN
	1    2050 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	2200 3750 2450 3750
Wire Wire Line
	1900 3750 1600 3750
Wire Wire Line
	1600 3950 2450 3950
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 5EA79AB2
P 1900 7250
F 0 "J3" H 1872 7132 50  0000 R CNN
F 1 "CONN_AC" H 1872 7223 50  0000 R CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 1900 7250 50  0001 C CNN
F 3 "~" H 1900 7250 50  0001 C CNN
	1    1900 7250
	-1   0    0    1   
$EndComp
Wire Wire Line
	1700 7150 1450 7150
NoConn ~ 6250 3450
NoConn ~ 6250 3650
NoConn ~ 6250 3750
NoConn ~ 6250 3850
NoConn ~ 6250 3950
NoConn ~ 6250 4050
NoConn ~ 6250 4150
NoConn ~ 7450 4050
NoConn ~ 7450 3850
Wire Wire Line
	1700 7250 1450 7250
Text GLabel 8900 2000 2    50   Input ~ 0
+3.3V
Text GLabel 8900 1900 2    50   Input ~ 0
GND
Text GLabel 8900 1800 2    50   Input ~ 0
DS18B20_DQ
Wire Wire Line
	6850 2250 8800 2250
Wire Wire Line
	8900 2000 8800 2000
Wire Wire Line
	8800 2000 8800 2250
Connection ~ 8800 2250
Wire Wire Line
	8900 1900 8700 1900
Wire Wire Line
	8700 1900 8700 3650
Wire Wire Line
	8700 3650 8800 3650
Connection ~ 8800 3650
Text GLabel 3900 6300 2    50   Input ~ 0
DS18B20_DQ
Text GLabel 3900 6200 2    50   Input ~ 0
GND
Text GLabel 3900 6400 2    50   Input ~ 0
+3.3V
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 5EA4E231
P 3550 6300
F 0 "J4" H 3658 6581 50  0000 C CNN
F 1 "CONN_TEMP" H 3658 6490 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3550 6300 50  0001 C CNN
F 3 "~" H 3550 6300 50  0001 C CNN
	1    3550 6300
	1    0    0    -1  
$EndComp
Text GLabel 9350 2400 2    50   Input ~ 0
SDA
Text GLabel 9350 2500 2    50   Input ~ 0
SCL
Wire Wire Line
	9350 2500 7800 2500
Wire Wire Line
	7800 2500 7800 3550
Wire Wire Line
	7800 3550 7450 3550
Wire Wire Line
	9350 2400 7700 2400
Wire Wire Line
	7700 2400 7700 3450
Wire Wire Line
	7700 3450 7450 3450
Wire Wire Line
	7600 3650 7600 2000
Wire Wire Line
	7600 1800 8900 1800
Wire Wire Line
	7600 3650 7450 3650
Text GLabel 3900 6800 2    50   Input ~ 0
+3.3V
Text GLabel 3900 7100 2    50   Input ~ 0
SDA
Text GLabel 3900 7000 2    50   Input ~ 0
SCL
Text GLabel 3900 6900 2    50   Input ~ 0
GND
$Comp
L Connector:Conn_01x04_Male J5
U 1 1 5EAA8055
P 3400 6900
F 0 "J5" H 3508 7181 50  0000 C CNN
F 1 "CONN_I2C" H 3508 7090 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 3400 6900 50  0001 C CNN
F 3 "~" H 3400 6900 50  0001 C CNN
	1    3400 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 6800 3900 6800
Wire Wire Line
	8800 3250 8350 3250
Connection ~ 8800 3250
Wire Wire Line
	7750 5250 7750 3750
Wire Wire Line
	7750 3750 7450 3750
Wire Wire Line
	8050 3250 7750 3250
Wire Wire Line
	7750 3250 7750 3750
Connection ~ 7750 3750
Wire Wire Line
	3900 6200 3750 6200
Wire Wire Line
	3750 6300 3900 6300
Wire Wire Line
	3900 6400 3750 6400
Wire Wire Line
	3600 6900 3900 6900
Wire Wire Line
	3900 7000 3600 7000
Wire Wire Line
	3600 7100 3900 7100
$Comp
L Device:R R7
U 1 1 5ECB0601
P 8150 2000
F 0 "R7" V 7943 2000 50  0000 C CNN
F 1 "4.7k" V 8034 2000 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 8080 2000 50  0001 C CNN
F 3 "~" H 8150 2000 50  0001 C CNN
	1    8150 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	8300 2000 8800 2000
Connection ~ 8800 2000
Wire Wire Line
	8000 2000 7600 2000
Connection ~ 7600 2000
Wire Wire Line
	7600 2000 7600 1800
NoConn ~ 7450 3250
$EndSCHEMATC
