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
LIBS:74141
LIBS:russian-nixies
LIBS:nixiesp-cache
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
L 74HC595 U1
U 1 1 59219343
P 8800 4400
F 0 "U1" H 8950 5000 50  0000 C CNN
F 1 "74HC595" H 8800 3800 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 8800 4400 50  0001 C CNN
F 3 "" H 8800 4400 50  0001 C CNN
	1    8800 4400
	0    -1   -1   0   
$EndComp
$Comp
L 74HC595 U5
U 1 1 59217C2D
P 6000 4400
F 0 "U5" H 6150 5000 50  0000 C CNN
F 1 "74HC595" H 6000 3800 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 6000 4400 50  0001 C CNN
F 3 "" H 6000 4400 50  0001 C CNN
	1    6000 4400
	0    -1   -1   0   
$EndComp
$Comp
L IN-12A N4
U 1 1 59219102
P 6450 1650
F 0 "N4" H 6225 2475 50  0000 L BNN
F 1 "HH:XM:SS" H 6450 1650 50  0000 L BNN
F 2 "nixiesp:russian-nixies-IN-12" H 6450 1800 50  0001 C CNN
F 3 "" H 6450 1650 60  0001 C CNN
	1    6450 1650
	0    -1   -1   0   
$EndComp
$Comp
L IN-12A N3
U 1 1 592191F2
P 5050 1950
F 0 "N3" H 4825 2775 50  0000 L BNN
F 1 "HH:MX:SS" H 5050 1950 50  0000 L BNN
F 2 "nixiesp:russian-nixies-IN-12" H 5050 2100 50  0001 C CNN
F 3 "" H 5050 1950 60  0001 C CNN
	1    5050 1950
	0    -1   -1   0   
$EndComp
NoConn ~ 7750 2900
$Comp
L GND #PWR01
U 1 1 5921B3EB
P 2050 6850
F 0 "#PWR01" H 2050 6600 50  0001 C CNN
F 1 "GND" H 2050 6700 50  0000 C CNN
F 2 "" H 2050 6850 50  0001 C CNN
F 3 "" H 2050 6850 50  0001 C CNN
	1    2050 6850
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5921B517
P 1850 6400
F 0 "R3" V 1930 6400 50  0000 C CNN
F 1 "330" V 1850 6400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1780 6400 50  0001 C CNN
F 3 "" H 1850 6400 50  0001 C CNN
	1    1850 6400
	-1   0    0    1   
$EndComp
$Comp
L R R2
U 1 1 5921B56C
P 2050 6400
F 0 "R2" V 2130 6400 50  0000 C CNN
F 1 "330" V 2050 6400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1980 6400 50  0001 C CNN
F 3 "" H 2050 6400 50  0001 C CNN
	1    2050 6400
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 5921B5AD
P 2250 6400
F 0 "R1" V 2330 6400 50  0000 C CNN
F 1 "330" V 2250 6400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 2180 6400 50  0001 C CNN
F 3 "" H 2250 6400 50  0001 C CNN
	1    2250 6400
	-1   0    0    1   
$EndComp
$Comp
L R R4
U 1 1 5921B5F5
P 1650 6400
F 0 "R4" V 1730 6400 50  0000 C CNN
F 1 "330" V 1650 6400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1580 6400 50  0001 C CNN
F 3 "" H 1650 6400 50  0001 C CNN
	1    1650 6400
	-1   0    0    1   
$EndComp
$Comp
L R R5
U 1 1 5921B652
P 1450 6400
F 0 "R5" V 1530 6400 50  0000 C CNN
F 1 "330" V 1450 6400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1380 6400 50  0001 C CNN
F 3 "" H 1450 6400 50  0001 C CNN
	1    1450 6400
	-1   0    0    1   
$EndComp
$Comp
L R R6
U 1 1 5921B6AC
P 1250 6400
F 0 "R6" V 1330 6400 50  0000 C CNN
F 1 "330" V 1250 6400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1180 6400 50  0001 C CNN
F 3 "" H 1250 6400 50  0001 C CNN
	1    1250 6400
	-1   0    0    1   
$EndComp
$Comp
L IN-12A N5
U 1 1 5921FC78
P 2250 1950
F 0 "N5" H 2025 2775 50  0000 L BNN
F 1 "HH:MM:SX" H 2250 1950 50  0000 L BNN
F 2 "nixiesp:russian-nixies-IN-12" H 2250 2100 50  0001 C CNN
F 3 "" H 2250 1950 60  0001 C CNN
	1    2250 1950
	0    -1   -1   0   
$EndComp
$Comp
L IN-12A N6
U 1 1 5921FE00
P 3650 1650
F 0 "N6" H 3425 2475 50  0000 L BNN
F 1 "HH:MM:XS" H 3650 1650 50  0000 L BNN
F 2 "nixiesp:russian-nixies-IN-12" H 3650 1800 50  0001 C CNN
F 3 "" H 3650 1650 60  0001 C CNN
	1    3650 1650
	0    -1   -1   0   
$EndComp
$Comp
L 74HC595 U8
U 1 1 5921FF85
P 3200 4400
F 0 "U8" H 3350 5000 50  0000 C CNN
F 1 "74HC595" H 3200 3800 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 3200 4400 50  0001 C CNN
F 3 "" H 3200 4400 50  0001 C CNN
	1    3200 4400
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR02
U 1 1 592255AD
P 2450 5100
F 0 "#PWR02" H 2450 4850 50  0001 C CNN
F 1 "GND" H 2450 4950 50  0000 C CNN
F 2 "" H 2450 5100 50  0001 C CNN
F 3 "" H 2450 5100 50  0001 C CNN
	1    2450 5100
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR03
U 1 1 59225623
P 1400 5400
F 0 "#PWR03" H 1400 5250 50  0001 C CNN
F 1 "VCC" H 1400 5550 50  0000 C CNN
F 2 "" H 1400 5400 50  0001 C CNN
F 3 "" H 1400 5400 50  0001 C CNN
	1    1400 5400
	0    -1   -1   0   
$EndComp
$Comp
L CONN_02X04 J2
U 1 1 592253DB
P 2100 5250
F 0 "J2" H 2100 5500 50  0000 C CNN
F 1 "ESP8266" H 2100 5000 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_2x04_Pitch2.54mm" H 2100 4050 50  0001 C CNN
F 3 "" H 2100 4050 50  0001 C CNN
	1    2100 5250
	-1   0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 5922BC9E
P 2050 6700
F 0 "D2" H 2050 6800 50  0000 C CNN
F 1 "LED" H 2050 6600 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 2050 6700 50  0001 C CNN
F 3 "" H 2050 6700 50  0001 C CNN
	1    2050 6700
	0    -1   -1   0   
$EndComp
$Comp
L LED D3
U 1 1 5922BD1C
P 1850 6700
F 0 "D3" H 1850 6800 50  0000 C CNN
F 1 "LED" H 1850 6600 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 1850 6700 50  0001 C CNN
F 3 "" H 1850 6700 50  0001 C CNN
	1    1850 6700
	0    -1   -1   0   
$EndComp
$Comp
L LED D4
U 1 1 5922BDBF
P 1650 6700
F 0 "D4" H 1650 6800 50  0000 C CNN
F 1 "LED" H 1650 6600 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 1650 6700 50  0001 C CNN
F 3 "" H 1650 6700 50  0001 C CNN
	1    1650 6700
	0    -1   -1   0   
$EndComp
$Comp
L LED D9
U 1 1 5922BE3F
P 1450 6700
F 0 "D9" H 1450 6800 50  0000 C CNN
F 1 "LED" H 1450 6600 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 1450 6700 50  0001 C CNN
F 3 "" H 1450 6700 50  0001 C CNN
	1    1450 6700
	0    -1   -1   0   
$EndComp
$Comp
L LED D10
U 1 1 5922BECA
P 1250 6700
F 0 "D10" H 1250 6800 50  0000 C CNN
F 1 "LED" H 1250 6600 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 1250 6700 50  0001 C CNN
F 3 "" H 1250 6700 50  0001 C CNN
	1    1250 6700
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR04
U 1 1 5922B5E7
P 5850 5400
F 0 "#PWR04" H 5850 5250 50  0001 C CNN
F 1 "VCC" H 5850 5550 50  0000 C CNN
F 2 "" H 5850 5400 50  0001 C CNN
F 3 "" H 5850 5400 50  0001 C CNN
	1    5850 5400
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR05
U 1 1 5922B952
P 8650 5400
F 0 "#PWR05" H 8650 5250 50  0001 C CNN
F 1 "VCC" H 8650 5550 50  0000 C CNN
F 2 "" H 8650 5400 50  0001 C CNN
F 3 "" H 8650 5400 50  0001 C CNN
	1    8650 5400
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR06
U 1 1 5922BAAC
P 8950 5400
F 0 "#PWR06" H 8950 5150 50  0001 C CNN
F 1 "GND" H 8950 5250 50  0000 C CNN
F 2 "" H 8950 5400 50  0001 C CNN
F 3 "" H 8950 5400 50  0001 C CNN
	1    8950 5400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5922BBC0
P 6150 5400
F 0 "#PWR07" H 6150 5150 50  0001 C CNN
F 1 "GND" H 6150 5250 50  0000 C CNN
F 2 "" H 6150 5400 50  0001 C CNN
F 3 "" H 6150 5400 50  0001 C CNN
	1    6150 5400
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR08
U 1 1 5922BF6F
P 3050 5400
F 0 "#PWR08" H 3050 5250 50  0001 C CNN
F 1 "VCC" H 3050 5550 50  0000 C CNN
F 2 "" H 3050 5400 50  0001 C CNN
F 3 "" H 3050 5400 50  0001 C CNN
	1    3050 5400
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR09
U 1 1 5922BFEC
P 3350 5400
F 0 "#PWR09" H 3350 5150 50  0001 C CNN
F 1 "GND" H 3350 5250 50  0000 C CNN
F 2 "" H 3350 5400 50  0001 C CNN
F 3 "" H 3350 5400 50  0001 C CNN
	1    3350 5400
	1    0    0    -1  
$EndComp
NoConn ~ 10800 1150
$Comp
L LM1117-3.3 U10
U 1 1 592AA286
P 1500 4900
F 0 "U10" H 1600 4650 50  0000 C CNN
F 1 "LM1117-3.3" H 1500 5150 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-223" H 1500 4900 50  0001 C CNN
F 3 "" H 1500 4900 50  0001 C CNN
	1    1500 4900
	0    -1   1    0   
$EndComp
$Comp
L IN-12A N2
U 1 1 592192B4
P 9250 1650
F 0 "N2" H 9025 2475 50  0000 L BNN
F 1 "XH:MM:SS" H 9250 1650 50  0000 L BNN
F 2 "nixiesp:russian-nixies-IN-12" H 9250 1800 50  0001 C CNN
F 3 "" H 9250 1650 60  0001 C CNN
	1    9250 1650
	0    -1   -1   0   
$EndComp
$Comp
L BS107 Q2
U 1 1 592AC4C6
P 1450 3550
F 0 "Q2" H 1650 3625 50  0000 L CNN
F 1 "BS107" H 1200 3750 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 1650 3475 50  0001 L CIN
F 3 "" H 1450 3550 50  0001 L CNN
	1    1450 3550
	-1   0    0    -1  
$EndComp
$Comp
L BS107 Q1
U 1 1 592ACDBD
P 1250 3800
F 0 "Q1" H 1450 3875 50  0000 L CNN
F 1 "BS107" H 1450 3800 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 1450 3725 50  0001 L CIN
F 3 "" H 1250 3800 50  0001 L CNN
	1    1250 3800
	-1   0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 592AD40C
P 1350 3200
F 0 "R8" V 1430 3200 50  0000 C CNN
F 1 "15k" V 1350 3200 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1280 3200 50  0001 C CNN
F 3 "" H 1350 3200 50  0001 C CNN
	1    1350 3200
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 592AD4D5
P 1150 3450
F 0 "R7" V 1230 3450 50  0000 C CNN
F 1 "15k" V 1150 3450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 1080 3450 50  0001 C CNN
F 3 "" H 1150 3450 50  0001 C CNN
	1    1150 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 592AD553
P 1150 4050
F 0 "#PWR010" H 1150 3800 50  0001 C CNN
F 1 "GND" H 1150 3900 50  0000 C CNN
F 2 "" H 1150 4050 50  0001 C CNN
F 3 "" H 1150 4050 50  0001 C CNN
	1    1150 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 592AE6F1
P 10400 900
F 0 "#PWR011" H 10400 650 50  0001 C CNN
F 1 "GND" H 10400 750 50  0000 C CNN
F 2 "" H 10400 900 50  0001 C CNN
F 3 "" H 10400 900 50  0001 C CNN
	1    10400 900 
	0    1    1    0   
$EndComp
$Comp
L GND #PWR012
U 1 1 592AF75B
P 8950 3250
F 0 "#PWR012" H 8950 3000 50  0001 C CNN
F 1 "GND" H 8950 3100 50  0000 C CNN
F 2 "" H 8950 3250 50  0001 C CNN
F 3 "" H 8950 3250 50  0001 C CNN
	1    8950 3250
	1    0    0    -1  
$EndComp
$Comp
L BS107 Q3
U 1 1 592B0897
P 7300 4750
F 0 "Q3" H 7500 4825 50  0000 L CNN
F 1 "BS107" H 7500 4750 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 7500 4675 50  0001 L CIN
F 3 "" H 7300 4750 50  0001 L CNN
	1    7300 4750
	-1   0    0    -1  
$EndComp
$Comp
L BS107 Q4
U 1 1 592B0CA4
P 7750 4750
F 0 "Q4" H 7950 4825 50  0000 L CNN
F 1 "BS107" H 7950 4750 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 7950 4675 50  0001 L CIN
F 3 "" H 7750 4750 50  0001 L CNN
	1    7750 4750
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 592B0D40
P 7200 4950
F 0 "#PWR013" H 7200 4700 50  0001 C CNN
F 1 "GND" H 7200 4800 50  0000 C CNN
F 2 "" H 7200 4950 50  0001 C CNN
F 3 "" H 7200 4950 50  0001 C CNN
	1    7200 4950
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 592B1199
P 7200 4400
F 0 "R9" V 7280 4400 50  0000 C CNN
F 1 "15k" V 7200 4400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 7130 4400 50  0001 C CNN
F 3 "" H 7200 4400 50  0001 C CNN
	1    7200 4400
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 592B12F4
P 7650 4400
F 0 "R10" V 7730 4400 50  0000 C CNN
F 1 "15k" V 7650 4400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 7580 4400 50  0001 C CNN
F 3 "" H 7650 4400 50  0001 C CNN
	1    7650 4400
	1    0    0    -1  
$EndComp
$Comp
L IN-12A N1
U 1 1 59219309
P 7850 1950
F 0 "N1" H 7625 2775 50  0000 L BNN
F 1 "HX:MM:SS" H 7850 1950 50  0000 L BNN
F 2 "nixiesp:russian-nixies-IN-12" H 7850 2100 50  0001 C CNN
F 3 "" H 7850 1950 60  0001 C CNN
	1    7850 1950
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 592AD7D9
P 2250 1400
F 0 "R11" V 2330 1400 50  0000 C CNN
F 1 "10k" V 2250 1400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 2180 1400 50  0001 C CNN
F 3 "" H 2250 1400 50  0001 C CNN
	1    2250 1400
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 592AE63C
P 3650 1100
F 0 "R12" V 3730 1100 50  0000 C CNN
F 1 "10k" V 3650 1100 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3580 1100 50  0001 C CNN
F 3 "" H 3650 1100 50  0001 C CNN
	1    3650 1100
	1    0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 592AE6EF
P 5050 1400
F 0 "R13" V 5130 1400 50  0000 C CNN
F 1 "10k" V 5050 1400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 4980 1400 50  0001 C CNN
F 3 "" H 5050 1400 50  0001 C CNN
	1    5050 1400
	1    0    0    -1  
$EndComp
$Comp
L R R14
U 1 1 592AE7DF
P 6450 1100
F 0 "R14" V 6530 1100 50  0000 C CNN
F 1 "10k" V 6450 1100 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 6380 1100 50  0001 C CNN
F 3 "" H 6450 1100 50  0001 C CNN
	1    6450 1100
	1    0    0    -1  
$EndComp
$Comp
L R R15
U 1 1 592AE91A
P 7850 1400
F 0 "R15" V 7930 1400 50  0000 C CNN
F 1 "10k" V 7850 1400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 7780 1400 50  0001 C CNN
F 3 "" H 7850 1400 50  0001 C CNN
	1    7850 1400
	1    0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 592AE9E2
P 9250 1100
F 0 "R16" V 9330 1100 50  0000 C CNN
F 1 "10k" V 9250 1100 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 9180 1100 50  0001 C CNN
F 3 "" H 9250 1100 50  0001 C CNN
	1    9250 1100
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J1
U 1 1 592B31AF
P 1550 4250
F 0 "J1" H 1550 4400 50  0000 C CNN
F 1 "Power 9-15V" V 1650 4250 50  0000 C CNN
F 2 "Connectors:BARREL_JACK" H 1550 4250 50  0001 C CNN
F 3 "" H 1550 4250 50  0001 C CNN
	1    1550 4250
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR014
U 1 1 592B3E62
P 8750 3250
F 0 "#PWR014" H 8750 3000 50  0001 C CNN
F 1 "GND" H 8750 3100 50  0000 C CNN
F 2 "" H 8750 3250 50  0001 C CNN
F 3 "" H 8750 3250 50  0001 C CNN
	1    8750 3250
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J3
U 1 1 592B52E4
P 1800 4250
F 0 "J3" H 1800 4400 50  0000 C CNN
F 1 "Nixie PSU low" V 2000 4250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 1800 4250 50  0001 C CNN
F 3 "" H 1800 4250 50  0001 C CNN
	1    1800 4250
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 J4
U 1 1 592B5B56
P 10600 850
F 0 "J4" H 10600 1000 50  0000 C CNN
F 1 "CONN_01X02" V 10700 850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 10600 850 50  0001 C CNN
F 3 "" H 10600 850 50  0001 C CNN
	1    10600 850 
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 5922BAB0
P 2250 6700
F 0 "D1" H 2250 6800 50  0000 C CNN
F 1 "LED" H 2250 6600 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 2250 6700 50  0001 C CNN
F 3 "" H 2250 6700 50  0001 C CNN
	1    2250 6700
	0    -1   -1   0   
$EndComp
$Comp
L 74141-DIP U7
U 1 1 592BC62A
P 7800 2900
F 0 "U7" H 7800 3650 50  0000 C CNN
F 1 "K155ID1" H 7800 3550 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 7800 2900 50  0001 C CNN
F 3 "" H 8000 3350 60  0000 C CNN
	1    7800 2900
	0    -1   -1   0   
$EndComp
$Comp
L 74141-DIP U6
U 1 1 592BC702
P 6400 2900
F 0 "U6" H 6400 3650 50  0000 C CNN
F 1 "K155ID1" H 6400 3550 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 6400 2900 50  0001 C CNN
F 3 "" H 6600 3350 60  0000 C CNN
	1    6400 2900
	0    -1   -1   0   
$EndComp
$Comp
L 74141-DIP U4
U 1 1 592BC7CD
P 5000 2900
F 0 "U4" H 5000 3650 50  0000 C CNN
F 1 "K155ID1" H 5000 3550 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 5000 2900 50  0001 C CNN
F 3 "" H 5200 3350 60  0000 C CNN
	1    5000 2900
	0    -1   -1   0   
$EndComp
$Comp
L 74141-DIP U2
U 1 1 592BC978
P 2200 2900
F 0 "U2" H 2200 3650 50  0000 C CNN
F 1 "K155ID1" H 2200 3550 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 2200 2900 50  0001 C CNN
F 3 "" H 2400 3350 60  0000 C CNN
	1    2200 2900
	0    -1   -1   0   
$EndComp
$Comp
L IN-6 N7
U 1 1 592BEC1C
P 7650 3950
F 0 "N7" H 7500 4175 50  0000 L BNN
F 1 "IN-6" H 7650 3950 50  0000 L BNN
F 2 "nixiesp:russian-nixies-IN-6" H 7650 4100 50  0001 C CNN
F 3 "" H 7650 3950 60  0001 C CNN
	1    7650 3950
	0    1    1    0   
$EndComp
$Comp
L IN-6 N10
U 1 1 592BF0B0
P 7200 3950
F 0 "N10" H 7050 4175 50  0000 L BNN
F 1 "IN-6" H 7200 3950 50  0000 L BNN
F 2 "nixiesp:russian-nixies-IN-6" H 7200 4100 50  0001 C CNN
F 3 "" H 7200 3950 60  0001 C CNN
	1    7200 3950
	0    1    1    0   
$EndComp
$Comp
L IN-6 N9
U 1 1 592BF164
P 1350 2750
F 0 "N9" H 1200 2975 50  0000 L BNN
F 1 "IN-6" H 1350 2750 50  0000 L BNN
F 2 "nixiesp:russian-nixies-IN-6" H 1350 2900 50  0001 C CNN
F 3 "" H 1350 2750 60  0001 C CNN
	1    1350 2750
	0    1    1    0   
$EndComp
$Comp
L IN-6 N8
U 1 1 592BF578
P 1150 3000
F 0 "N8" H 1000 3225 50  0000 L BNN
F 1 "IN-6" H 1150 3000 50  0000 L BNN
F 2 "nixiesp:russian-nixies-IN-6" H 1150 3150 50  0001 C CNN
F 3 "" H 1150 3000 60  0001 C CNN
	1    1150 3000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR015
U 1 1 592D5ABD
P 6150 3250
F 0 "#PWR015" H 6150 3000 50  0001 C CNN
F 1 "GND" H 6150 3100 50  0000 C CNN
F 2 "" H 6150 3250 50  0001 C CNN
F 3 "" H 6150 3250 50  0001 C CNN
	1    6150 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 592D5FB7
P 3350 3250
F 0 "#PWR016" H 3350 3000 50  0001 C CNN
F 1 "GND" H 3350 3100 50  0000 C CNN
F 2 "" H 3350 3250 50  0001 C CNN
F 3 "" H 3350 3250 50  0001 C CNN
	1    3350 3250
	1    0    0    -1  
$EndComp
$Comp
L 74141-DIP U3
U 1 1 592BC8A1
P 3600 2900
F 0 "U3" H 3600 3650 50  0000 C CNN
F 1 "K155ID1" H 3600 3550 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 3600 2900 50  0001 C CNN
F 3 "" H 3800 3350 60  0000 C CNN
	1    3600 2900
	0    -1   -1   0   
$EndComp
$Comp
L 74141-DIP U9
U 1 1 592F06C2
P 9200 2900
F 0 "U9" H 9200 3650 50  0000 C CNN
F 1 "K155ID1" H 9200 3550 50  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 9200 2900 50  0001 C CNN
F 3 "" H 9400 3350 60  0000 C CNN
	1    9200 2900
	0    -1   -1   0   
$EndComp
$Comp
L LM1117-3.3 U11
U 1 1 59313F53
P 1750 4750
F 0 "U11" H 1850 4500 50  0000 C CNN
F 1 "LM1117-3.3" H 1750 5000 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-223" H 1750 4750 50  0001 C CNN
F 3 "" H 1750 4750 50  0001 C CNN
	1    1750 4750
	0    -1   1    0   
$EndComp
Wire Wire Line
	1350 2250 1350 2450
Wire Wire Line
	1150 800  1150 2700
Connection ~ 7200 3650
Wire Wire Line
	7100 800  7100 3650
Wire Wire Line
	7100 3650 7650 3650
Wire Wire Line
	7650 4950 7200 4950
Wire Wire Line
	7950 4800 8050 4800
Wire Wire Line
	1250 6250 2250 6250
Connection ~ 1500 4450
Connection ~ 1850 4500
Wire Wire Line
	1850 4500 1850 4450
Wire Wire Line
	1600 4500 2400 4500
Wire Wire Line
	1600 4450 1600 4500
Wire Wire Line
	3650 3650 3650 3700
Wire Wire Line
	4800 3650 3650 3650
Wire Wire Line
	6450 3550 6450 3700
Wire Wire Line
	6700 3550 6450 3550
Connection ~ 2400 4750
Wire Wire Line
	1250 4450 1750 4450
Wire Wire Line
	2400 4500 2400 5100
Wire Wire Line
	5950 2450 5950 2150
Wire Wire Line
	6050 2150 6050 2450
Wire Wire Line
	6150 2450 6150 2150
Wire Wire Line
	6250 2150 6250 2450
Wire Wire Line
	6350 2450 6350 2150
Wire Wire Line
	6450 2150 6450 2450
Wire Wire Line
	6550 2450 6550 2150
Wire Wire Line
	6850 2150 6850 2450
Wire Wire Line
	8750 2150 8750 2450
Wire Wire Line
	8850 2450 8850 2150
Wire Wire Line
	8950 2150 8950 2450
Wire Wire Line
	9650 2450 9650 2150
Wire Wire Line
	3150 2450 3150 2150
Wire Wire Line
	3250 2150 3250 2450
Wire Wire Line
	3350 2150 3350 2450
Wire Wire Line
	3450 2150 3450 2450
Wire Wire Line
	3550 2150 3550 2450
Wire Wire Line
	3650 2150 3650 2450
Wire Wire Line
	3750 2450 3750 2150
Wire Wire Line
	4050 2150 4050 2450
Connection ~ 2250 800 
Connection ~ 3650 800 
Wire Wire Line
	2250 800  2250 1250
Connection ~ 5050 800 
Wire Wire Line
	3650 800  3650 950 
Connection ~ 6450 800 
Wire Wire Line
	5050 800  5050 1250
Connection ~ 7100 800 
Wire Wire Line
	6450 800  6450 950 
Connection ~ 9250 800 
Wire Wire Line
	9250 800  9250 950 
Connection ~ 7850 800 
Wire Wire Line
	7850 800  7850 1250
Wire Wire Line
	1150 800  10400 800 
Wire Wire Line
	1250 6250 1250 4450
Wire Wire Line
	6700 5100 6700 3550
Wire Wire Line
	8350 5100 6700 5100
Wire Wire Line
	1500 5200 1500 5400
Connection ~ 1150 2250
Wire Wire Line
	1350 2250 1150 2250
Wire Wire Line
	1350 4000 1350 3750
Wire Wire Line
	1150 4000 1350 4000
Wire Wire Line
	1150 4000 1150 4050
Wire Wire Line
	1750 5200 1850 5200
Connection ~ 5750 5400
Wire Wire Line
	8550 5400 8550 5100
Wire Wire Line
	5750 5400 5750 5100
Wire Wire Line
	2350 5300 8850 5300
Connection ~ 2400 5100
Connection ~ 2950 5400
Wire Wire Line
	2950 5400 2950 5100
Wire Wire Line
	3050 5100 3050 5400
Wire Wire Line
	3350 5400 3350 5100
Wire Wire Line
	6150 5400 6150 5100
Wire Wire Line
	8950 5400 8950 5100
Wire Wire Line
	8650 5400 8650 5100
Wire Wire Line
	5850 5400 5850 5100
Connection ~ 2050 6250
Connection ~ 1850 6250
Connection ~ 1650 6250
Connection ~ 1450 6250
Wire Wire Line
	1250 6850 2250 6850
Connection ~ 1500 5400
Wire Wire Line
	1400 5400 1850 5400
Connection ~ 3250 5300
Wire Wire Line
	2350 5100 2450 5100
Connection ~ 6050 5300
Wire Wire Line
	3250 5300 3250 5100
Wire Wire Line
	6050 5300 6050 5100
Wire Wire Line
	8850 5300 8850 5100
Wire Wire Line
	2850 3450 2850 3700
Wire Wire Line
	1850 3450 2850 3450
Wire Wire Line
	1850 3250 1850 3450
Wire Wire Line
	3050 3250 2050 3250
Wire Wire Line
	3050 3700 3050 3250
Wire Wire Line
	3150 3250 3150 3700
Wire Wire Line
	3250 3700 3250 3250
Wire Wire Line
	3450 3700 3450 3250
Connection ~ 1450 6850
Connection ~ 1650 6850
Connection ~ 1850 6850
Connection ~ 2050 6850
Wire Wire Line
	6250 3700 6250 3250
Wire Wire Line
	6050 3700 6050 3250
Wire Wire Line
	5950 3700 5950 3250
Wire Wire Line
	5550 3550 5550 3700
Wire Wire Line
	4550 3550 5550 3550
Wire Wire Line
	4550 3250 4550 3550
Wire Wire Line
	4650 3450 4650 3250
Wire Wire Line
	5650 3450 4650 3450
Wire Wire Line
	5650 3700 5650 3450
Wire Wire Line
	5850 3250 5850 3700
Wire Wire Line
	4850 3250 5850 3250
Wire Wire Line
	4800 5100 5550 5100
Wire Wire Line
	4800 3650 4800 5100
Wire Wire Line
	8450 3450 8450 3700
Wire Wire Line
	7450 3450 8450 3450
Wire Wire Line
	7450 3250 7450 3450
Wire Wire Line
	8650 3250 8650 3700
Wire Wire Line
	7650 3250 8650 3250
Wire Wire Line
	8850 3700 8850 3250
Wire Wire Line
	9050 3700 9050 3250
Wire Wire Line
	8550 3700 8550 3350
Wire Wire Line
	8550 3350 7550 3350
Wire Wire Line
	7550 3350 7550 3250
Wire Wire Line
	7350 3250 7350 3550
Wire Wire Line
	7350 3550 8350 3550
Wire Wire Line
	8350 3550 8350 3700
Wire Wire Line
	7500 4800 7500 4900
Wire Wire Line
	7500 4900 8150 4900
Wire Wire Line
	8150 4900 8150 3700
Wire Wire Line
	8150 3700 8750 3700
Wire Wire Line
	8950 3700 8950 3650
Wire Wire Line
	8950 3650 8050 3650
Wire Wire Line
	8050 3650 8050 4800
Wire Wire Line
	4750 3250 4750 3350
Wire Wire Line
	4750 3350 5750 3350
Wire Wire Line
	5750 3350 5750 3700
Wire Wire Line
	6150 3700 6150 3600
Wire Wire Line
	6150 3600 1650 3600
Wire Wire Line
	2750 3700 1750 3700
Wire Wire Line
	1750 3700 1750 3250
Wire Wire Line
	3350 3700 3350 3550
Wire Wire Line
	3350 3550 1850 3550
Wire Wire Line
	1450 3850 1850 3850
Wire Wire Line
	1850 3850 1850 3550
Wire Wire Line
	1950 3250 1950 3350
Wire Wire Line
	1950 3350 2950 3350
Wire Wire Line
	2950 3350 2950 3700
Wire Wire Line
	2350 5200 2750 5200
Wire Wire Line
	2750 5200 2750 5100
Wire Wire Line
	2350 5400 8550 5400
Wire Wire Line
	1500 4450 1500 4600
Wire Wire Line
	1800 4900 2400 4900
Connection ~ 2400 4900
Wire Wire Line
	2050 4750 2400 4750
Wire Wire Line
	1750 5050 1750 5400
Connection ~ 1750 5200
Wire Wire Line
	1750 5300 1850 5300
Connection ~ 1750 5400
Connection ~ 1750 5300
$EndSCHEMATC