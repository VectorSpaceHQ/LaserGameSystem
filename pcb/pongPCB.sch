EESchema Schematic File Version 4
LIBS:pongPCB-cache
EELAYER 26 0
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
L Analog_DAC:MCP4922 U1
U 1 1 5C4B3E8F
P 5250 2800
F 0 "U1" H 5250 3378 50  0000 C CNN
F 1 "MCP4922" H 5250 3287 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 6050 2500 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/22250A.pdf" H 6050 2500 50  0001 C CNN
	1    5250 2800
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL082 U2
U 1 1 5C4B4004
P 7350 1700
F 0 "U2" H 7350 2067 50  0000 C CNN
F 1 "TL082" H 7350 1976 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7350 1700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 7350 1700 50  0001 C CNN
	1    7350 1700
	1    0    0    -1  
$EndComp
$Comp
L Logic_LevelTranslator:TXB0104RUT U3
U 1 1 5C4B4320
P 3200 5250
F 0 "U3" H 3200 4464 50  0000 C CNN
F 1 "levelshift" H 3200 4373 50  0000 C CNN
F 2 "Package_DIP:DIP-12_W7.62mm" H 3200 4500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/txb0104.pdf" H 3310 5345 50  0001 C CNN
	1    3200 5250
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL082 U2
U 2 1 5C4E1404
P 8650 1600
F 0 "U2" H 8650 1967 50  0000 C CNN
F 1 "TL082" H 8650 1876 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 8650 1600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 8650 1600 50  0001 C CNN
	2    8650 1600
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL082 U2
U 3 1 5C4E14AE
P 7350 1700
F 0 "U2" H 7308 1746 50  0000 L CNN
F 1 "TL082" H 7308 1655 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7350 1700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 7350 1700 50  0001 C CNN
	3    7350 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 5C4E162C
P 6600 1800
F 0 "R1" V 6395 1800 50  0000 C CNN
F 1 "1k" V 6486 1800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 6640 1790 50  0001 C CNN
F 3 "~" H 6600 1800 50  0001 C CNN
	1    6600 1800
	0    1    -1   0   
$EndComp
$Comp
L Device:R_US R3
U 1 1 5C4E1A32
P 6700 1300
F 0 "R3" V 6495 1300 50  0000 C CNN
F 1 "47k" V 6586 1300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 6740 1290 50  0001 C CNN
F 3 "~" H 6700 1300 50  0001 C CNN
	1    6700 1300
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R4
U 1 1 5C4E1B31
P 8050 1700
F 0 "R4" V 7845 1700 50  0000 C CNN
F 1 "10k" V 7936 1700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8090 1690 50  0001 C CNN
F 3 "~" H 8050 1700 50  0001 C CNN
	1    8050 1700
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR06
U 1 1 5C573BCE
P 5950 2500
F 0 "#PWR06" H 5950 2350 50  0001 C CNN
F 1 "+5V" H 5965 2673 50  0000 C CNN
F 2 "" H 5950 2500 50  0001 C CNN
F 3 "" H 5950 2500 50  0001 C CNN
	1    5950 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 2500 5950 2600
Wire Wire Line
	5950 2600 5800 2600
Connection ~ 5950 2600
Wire Wire Line
	5950 3100 5750 3100
$Comp
L power:GND #PWR01
U 1 1 5C573CA0
P 5250 3400
F 0 "#PWR01" H 5250 3150 50  0001 C CNN
F 1 "GND" H 5255 3227 50  0000 C CNN
F 2 "" H 5250 3400 50  0001 C CNN
F 3 "" H 5250 3400 50  0001 C CNN
	1    5250 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3400 5250 3350
Wire Wire Line
	5250 2400 5800 2400
Wire Wire Line
	5800 2400 5800 2600
Connection ~ 5800 2600
Wire Wire Line
	5800 2600 5750 2600
Wire Wire Line
	4750 2900 4450 2900
Wire Wire Line
	4450 2900 4450 3350
Wire Wire Line
	4450 3350 5250 3350
Connection ~ 5250 3350
Wire Wire Line
	5250 3350 5250 3300
Wire Wire Line
	5950 2600 5950 3100
Wire Wire Line
	6250 2700 5750 2700
$Comp
L power:GND #PWR05
U 1 1 5C5742CE
P 5950 1450
F 0 "#PWR05" H 5950 1200 50  0001 C CNN
F 1 "GND" H 5955 1277 50  0000 C CNN
F 2 "" H 5950 1450 50  0001 C CNN
F 3 "" H 5950 1450 50  0001 C CNN
	1    5950 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 1400 7250 1300
Wire Wire Line
	7250 1300 6850 1300
$Comp
L Device:R_POT RV1
U 1 1 5C5746E0
P 6200 1300
F 0 "RV1" V 5993 1300 50  0000 C CNN
F 1 "10k" V 6084 1300 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_ACP_CA6-H2,5_Horizontal" H 6200 1300 50  0001 C CNN
F 3 "~" H 6200 1300 50  0001 C CNN
	1    6200 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	7050 1600 6200 1600
Wire Wire Line
	6200 1600 6200 1450
Wire Wire Line
	6550 1300 6350 1300
Wire Wire Line
	6050 1300 5950 1300
Wire Wire Line
	5950 1300 5950 1450
$Comp
L power:+15V #PWR010
U 1 1 5C574D5A
P 7850 900
F 0 "#PWR010" H 7850 750 50  0001 C CNN
F 1 "+15V" H 7865 1073 50  0000 C CNN
F 2 "" H 7850 900 50  0001 C CNN
F 3 "" H 7850 900 50  0001 C CNN
	1    7850 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 1400 7850 1400
Wire Wire Line
	7850 1400 7850 900 
Connection ~ 7250 1400
$Comp
L Device:R_POT RV3
U 1 1 5C575057
P 7250 1000
F 0 "RV3" H 7180 1046 50  0000 R CNN
F 1 "10k" H 7180 955 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_ACP_CA6-H2,5_Horizontal" H 7250 1000 50  0001 C CNN
F 3 "~" H 7250 1000 50  0001 C CNN
	1    7250 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 1700 7650 1000
Wire Wire Line
	7650 1000 7400 1000
Wire Wire Line
	6450 1800 6250 1800
Wire Wire Line
	7000 1800 7000 1150
Wire Wire Line
	7000 1150 7250 1150
Wire Wire Line
	6750 1800 7000 1800
Connection ~ 7000 1800
Wire Wire Line
	7000 1800 7050 1800
$Comp
L power:-15V #PWR08
U 1 1 5C577925
P 7250 2150
F 0 "#PWR08" H 7250 2250 50  0001 C CNN
F 1 "-15V" H 7265 2323 50  0000 C CNN
F 2 "" H 7250 2150 50  0001 C CNN
F 3 "" H 7250 2150 50  0001 C CNN
	1    7250 2150
	-1   0    0    1   
$EndComp
Wire Wire Line
	7250 2000 7250 2150
NoConn ~ 7250 850 
$Comp
L power:GND #PWR012
U 1 1 5C5781FE
P 8200 1300
F 0 "#PWR012" H 8200 1050 50  0001 C CNN
F 1 "GND" H 8205 1127 50  0000 C CNN
F 2 "" H 8200 1300 50  0001 C CNN
F 3 "" H 8200 1300 50  0001 C CNN
	1    8200 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	8200 1300 8200 1500
Wire Wire Line
	8200 1500 8350 1500
Wire Wire Line
	8350 1700 8300 1700
Wire Wire Line
	7900 1700 7800 1700
Connection ~ 7650 1700
$Comp
L Device:R_US R7
U 1 1 5C5797EA
P 8650 2050
F 0 "R7" V 8445 2050 50  0000 C CNN
F 1 "10k" V 8536 2050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8690 2040 50  0001 C CNN
F 3 "~" H 8650 2050 50  0001 C CNN
	1    8650 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	8300 1700 8300 2050
Wire Wire Line
	8300 2050 8500 2050
Connection ~ 8300 1700
Wire Wire Line
	8300 1700 8200 1700
Wire Wire Line
	8800 2050 8950 2050
Wire Wire Line
	8950 2050 8950 1600
Wire Wire Line
	8950 1600 9400 1600
Connection ~ 8950 1600
Wire Wire Line
	7800 1700 7800 2150
Wire Wire Line
	7800 2150 9700 2150
Connection ~ 7800 1700
Wire Wire Line
	7800 1700 7650 1700
Text GLabel 10100 1600 2    50   Input ~ 0
X_ILDA-normal
Text GLabel 10100 1700 2    50   Input ~ 0
X_ILDA-inverted
$Comp
L Amplifier_Operational:TL082 U5
U 1 1 5C57BB5D
P 7650 3400
F 0 "U5" H 7650 3767 50  0000 C CNN
F 1 "TL082" H 7650 3676 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7650 3400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 7650 3400 50  0001 C CNN
	1    7650 3400
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL082 U5
U 2 1 5C57BB64
P 8950 3300
F 0 "U5" H 8950 3667 50  0000 C CNN
F 1 "TL082" H 8950 3576 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 8950 3300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 8950 3300 50  0001 C CNN
	2    8950 3300
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL082 U5
U 3 1 5C57BB6B
P 7650 3400
F 0 "U5" H 7608 3446 50  0000 L CNN
F 1 "TL082" H 7608 3355 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7650 3400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl081.pdf" H 7650 3400 50  0001 C CNN
	3    7650 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 5C57BB72
P 6900 3500
F 0 "R2" V 6695 3500 50  0000 C CNN
F 1 "1k" V 6786 3500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 6940 3490 50  0001 C CNN
F 3 "~" H 6900 3500 50  0001 C CNN
	1    6900 3500
	0    1    -1   0   
$EndComp
$Comp
L Device:R_US R5
U 1 1 5C57BB79
P 7000 3000
F 0 "R5" V 6795 3000 50  0000 C CNN
F 1 "47k" V 6886 3000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 7040 2990 50  0001 C CNN
F 3 "~" H 7000 3000 50  0001 C CNN
	1    7000 3000
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R6
U 1 1 5C57BB80
P 8350 3400
F 0 "R6" V 8145 3400 50  0000 C CNN
F 1 "10k" V 8236 3400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8390 3390 50  0001 C CNN
F 3 "~" H 8350 3400 50  0001 C CNN
	1    8350 3400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5C57BB88
P 6250 3150
F 0 "#PWR07" H 6250 2900 50  0001 C CNN
F 1 "GND" H 6255 2977 50  0000 C CNN
F 2 "" H 6250 3150 50  0001 C CNN
F 3 "" H 6250 3150 50  0001 C CNN
	1    6250 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3100 7550 3000
Wire Wire Line
	7550 3000 7150 3000
$Comp
L Device:R_POT RV2
U 1 1 5C57BB90
P 6500 3000
F 0 "RV2" V 6293 3000 50  0000 C CNN
F 1 "10k" V 6384 3000 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_ACP_CA6-H2,5_Horizontal" H 6500 3000 50  0001 C CNN
F 3 "~" H 6500 3000 50  0001 C CNN
	1    6500 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 3300 6500 3300
Wire Wire Line
	6500 3300 6500 3150
Wire Wire Line
	6850 3000 6650 3000
Wire Wire Line
	6350 3000 6250 3000
Wire Wire Line
	6250 3000 6250 3150
$Comp
L power:+15V #PWR011
U 1 1 5C57BB9C
P 8150 2600
F 0 "#PWR011" H 8150 2450 50  0001 C CNN
F 1 "+15V" H 8165 2773 50  0000 C CNN
F 2 "" H 8150 2600 50  0001 C CNN
F 3 "" H 8150 2600 50  0001 C CNN
	1    8150 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3100 8150 3100
Wire Wire Line
	8150 3100 8150 2600
Connection ~ 7550 3100
$Comp
L Device:R_POT RV4
U 1 1 5C57BBA5
P 7550 2700
F 0 "RV4" H 7480 2746 50  0000 R CNN
F 1 "10k" H 7480 2655 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_ACP_CA6-H2,5_Horizontal" H 7550 2700 50  0001 C CNN
F 3 "~" H 7550 2700 50  0001 C CNN
	1    7550 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 3400 7950 2700
Wire Wire Line
	7950 2700 7700 2700
Wire Wire Line
	7300 3500 7300 2850
Wire Wire Line
	7300 2850 7550 2850
Wire Wire Line
	7050 3500 7300 3500
Connection ~ 7300 3500
Wire Wire Line
	7300 3500 7350 3500
$Comp
L power:-15V #PWR09
U 1 1 5C57BBB4
P 7550 3850
F 0 "#PWR09" H 7550 3950 50  0001 C CNN
F 1 "-15V" H 7565 4023 50  0000 C CNN
F 2 "" H 7550 3850 50  0001 C CNN
F 3 "" H 7550 3850 50  0001 C CNN
	1    7550 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	7550 3700 7550 3850
NoConn ~ 7550 2550
$Comp
L power:GND #PWR013
U 1 1 5C57BBBC
P 8500 3000
F 0 "#PWR013" H 8500 2750 50  0001 C CNN
F 1 "GND" H 8505 2827 50  0000 C CNN
F 2 "" H 8500 3000 50  0001 C CNN
F 3 "" H 8500 3000 50  0001 C CNN
	1    8500 3000
	-1   0    0    1   
$EndComp
Wire Wire Line
	8500 3000 8500 3200
Wire Wire Line
	8500 3200 8650 3200
Wire Wire Line
	8650 3400 8600 3400
Wire Wire Line
	8200 3400 8100 3400
Connection ~ 7950 3400
$Comp
L Device:R_US R8
U 1 1 5C57BBC7
P 8950 3750
F 0 "R8" V 8745 3750 50  0000 C CNN
F 1 "10k" V 8836 3750 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8990 3740 50  0001 C CNN
F 3 "~" H 8950 3750 50  0001 C CNN
	1    8950 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	8600 3400 8600 3750
Wire Wire Line
	8600 3750 8800 3750
Connection ~ 8600 3400
Wire Wire Line
	8600 3400 8500 3400
Wire Wire Line
	9100 3750 9250 3750
Wire Wire Line
	9250 3750 9250 3300
Wire Wire Line
	9250 3300 9500 3300
Connection ~ 9250 3300
Wire Wire Line
	8100 3400 8100 3850
Wire Wire Line
	8100 3850 9850 3850
Connection ~ 8100 3400
Wire Wire Line
	8100 3400 7950 3400
Text GLabel 10200 3300 2    50   Input ~ 0
Y_ILDA-normal
Text GLabel 10200 3400 2    50   Input ~ 0
Y_ILDA-inverted
Wire Wire Line
	5750 3000 6050 3000
$Comp
L Device:Rotary_Encoder_Switch ENC1
U 1 1 5C58835F
P 5100 5400
F 0 "ENC1" H 5100 5767 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 5100 5676 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 4950 5560 50  0001 C CNN
F 3 "~" H 5100 5660 50  0001 C CNN
	1    5100 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 4950 4600 4950
Wire Wire Line
	4600 4950 4600 5300
Wire Wire Line
	4600 5300 4800 5300
Wire Wire Line
	4450 5400 4800 5400
Wire Wire Line
	4800 5500 4350 5500
Wire Wire Line
	4350 5500 4350 5350
Wire Wire Line
	4350 5350 3600 5350
Wire Wire Line
	4450 4550 3300 4550
Wire Wire Line
	4450 4550 4450 5400
$Comp
L power:+12V #PWR04
U 1 1 5C59809D
P 3300 4500
F 0 "#PWR04" H 3300 4350 50  0001 C CNN
F 1 "+12V" H 3315 4673 50  0000 C CNN
F 2 "" H 3300 4500 50  0001 C CNN
F 3 "" H 3300 4500 50  0001 C CNN
	1    3300 4500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 5C5981A1
P 3100 4500
F 0 "#PWR02" H 3100 4350 50  0001 C CNN
F 1 "+5V" H 3115 4673 50  0000 C CNN
F 2 "" H 3100 4500 50  0001 C CNN
F 3 "" H 3100 4500 50  0001 C CNN
	1    3100 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 5500 5400 5700
Wire Wire Line
	5400 5700 4250 5700
Wire Wire Line
	4250 5700 4250 5550
Wire Wire Line
	4250 5550 3600 5550
Wire Wire Line
	5400 5300 5650 5300
$Comp
L power:GND #PWR017
U 1 1 5C59C7F9
P 5650 5300
F 0 "#PWR017" H 5650 5050 50  0001 C CNN
F 1 "GND" H 5655 5127 50  0000 C CNN
F 2 "" H 5650 5300 50  0001 C CNN
F 3 "" H 5650 5300 50  0001 C CNN
	1    5650 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 4950 2050 4950
Wire Wire Line
	2800 5350 2050 5350
Wire Wire Line
	2800 5550 2050 5550
Text GLabel 2050 4950 0    50   Input ~ 0
DT1
Text GLabel 2050 5350 0    50   Input ~ 0
CLK2
Text GLabel 2050 5550 0    50   Input ~ 0
button1
Wire Wire Line
	4750 2800 4300 2800
$Comp
L Logic_LevelTranslator:TXB0104RUT U4
U 1 1 5C5B3ECE
P 4400 6750
F 0 "U4" H 4400 5964 50  0000 C CNN
F 1 "levelshift" H 4400 5873 50  0000 C CNN
F 2 "Package_DIP:DIP-12_W7.62mm" H 4400 6000 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/txb0104.pdf" H 4510 6845 50  0001 C CNN
	1    4400 6750
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder_Switch ENC2
U 1 1 5C5B3ED4
P 6300 6900
F 0 "ENC2" H 6300 7267 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 6300 7176 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 6150 7060 50  0001 C CNN
F 3 "~" H 6300 7160 50  0001 C CNN
	1    6300 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 6450 5800 6450
Wire Wire Line
	5800 6450 5800 6800
Wire Wire Line
	5800 6800 6000 6800
Wire Wire Line
	5650 6900 6000 6900
Wire Wire Line
	6000 7000 5550 7000
Wire Wire Line
	5550 7000 5550 6850
Wire Wire Line
	5550 6850 4800 6850
Wire Wire Line
	5650 6050 4500 6050
Wire Wire Line
	5650 6050 5650 6900
$Comp
L power:+12V #PWR014
U 1 1 5C5B3EE3
P 4500 6000
F 0 "#PWR014" H 4500 5850 50  0001 C CNN
F 1 "+12V" H 4515 6173 50  0000 C CNN
F 2 "" H 4500 6000 50  0001 C CNN
F 3 "" H 4500 6000 50  0001 C CNN
	1    4500 6000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5C5B3EE9
P 4300 6000
F 0 "#PWR03" H 4300 5850 50  0001 C CNN
F 1 "+5V" H 4315 6173 50  0000 C CNN
F 2 "" H 4300 6000 50  0001 C CNN
F 3 "" H 4300 6000 50  0001 C CNN
	1    4300 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 7000 6600 7200
Wire Wire Line
	6600 7200 5450 7200
Wire Wire Line
	5450 7200 5450 7050
Wire Wire Line
	5450 7050 4800 7050
Wire Wire Line
	6600 6800 6850 6800
$Comp
L power:GND #PWR018
U 1 1 5C5B3EFB
P 6850 6800
F 0 "#PWR018" H 6850 6550 50  0001 C CNN
F 1 "GND" H 6855 6627 50  0000 C CNN
F 2 "" H 6850 6800 50  0001 C CNN
F 3 "" H 6850 6800 50  0001 C CNN
	1    6850 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 6450 3250 6450
Wire Wire Line
	4000 6850 3250 6850
Wire Wire Line
	4000 7050 3250 7050
Text GLabel 3250 6450 0    50   Input ~ 0
DT2
Text GLabel 3250 6850 0    50   Input ~ 0
CLK2
Text GLabel 3250 7050 0    50   Input ~ 0
button2
$Comp
L power:GND #PWR016
U 1 1 5C5C12EF
P 3650 6000
F 0 "#PWR016" H 3650 5750 50  0001 C CNN
F 1 "GND" H 3655 5827 50  0000 C CNN
F 2 "" H 3650 6000 50  0001 C CNN
F 3 "" H 3650 6000 50  0001 C CNN
	1    3650 6000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5C5C1356
P 4800 7550
F 0 "#PWR015" H 4800 7300 50  0001 C CNN
F 1 "GND" H 4805 7377 50  0000 C CNN
F 2 "" H 4800 7550 50  0001 C CNN
F 3 "" H 4800 7550 50  0001 C CNN
	1    4800 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 5950 3650 5950
Wire Wire Line
	3650 5950 3650 6000
Wire Wire Line
	4800 7550 4800 7450
Wire Wire Line
	4800 7450 4400 7450
NoConn ~ 2800 4750
NoConn ~ 2800 5150
NoConn ~ 3600 5150
NoConn ~ 4800 6650
NoConn ~ 4000 6650
NoConn ~ 4000 6250
NoConn ~ 4750 2600
Wire Wire Line
	4500 6050 4500 6000
Connection ~ 4500 6050
Wire Wire Line
	4300 6050 4300 6000
Wire Wire Line
	3100 4500 3100 4550
Wire Wire Line
	3300 4500 3300 4550
Connection ~ 3300 4550
$Comp
L Jumper:Jumper_3_Open JP1
U 1 1 5C6A57F1
P 6300 3900
F 0 "JP1" V 6254 3987 50  0000 L CNN
F 1 "Jumper_3_Open" V 6345 3987 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_Pad1.0x1.5mm" H 6300 3900 50  0001 C CNN
F 3 "~" H 6300 3900 50  0001 C CNN
	1    6300 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	6050 3900 6150 3900
Wire Wire Line
	6050 3000 6050 3900
Wire Wire Line
	6300 3650 6300 3500
Wire Wire Line
	6300 3500 6750 3500
Wire Wire Line
	6300 4150 9500 4150
Wire Wire Line
	9500 4150 9500 3300
Connection ~ 9500 3300
Wire Wire Line
	9500 3300 10000 3300
$Comp
L Jumper:Jumper_3_Open JP2
U 1 1 5C6B930D
P 6450 2400
F 0 "JP2" V 6404 2487 50  0000 L CNN
F 1 "Jumper_3_Open" V 6495 2487 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_Pad1.0x1.5mm" H 6450 2400 50  0001 C CNN
F 3 "~" H 6450 2400 50  0001 C CNN
	1    6450 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	6250 2700 6250 2400
Wire Wire Line
	6250 2400 6300 2400
Wire Wire Line
	6450 2150 6250 2150
Wire Wire Line
	6250 2150 6250 1800
Wire Wire Line
	6450 2650 7150 2650
Wire Wire Line
	7150 2650 7150 2300
Wire Wire Line
	7150 2300 9400 2300
Wire Wire Line
	9400 2300 9400 1600
Connection ~ 9400 1600
$Comp
L Timer:NE555 U6
U 1 1 5C6CE07D
P 7750 5300
F 0 "U6" H 7750 5878 50  0000 C CNN
F 1 "NE555" H 7750 5787 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7750 5300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ne555.pdf" H 7750 5300 50  0001 C CNN
	1    7750 5300
	1    0    0    -1  
$EndComp
$Comp
L pspice:CAP C1
U 1 1 5C6CE33E
P 6750 5550
F 0 "C1" H 6928 5596 50  0000 L CNN
F 1 "104" H 6928 5505 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.4mm_W2.1mm_P2.50mm" H 6750 5550 50  0001 C CNN
F 3 "~" H 6750 5550 50  0001 C CNN
	1    6750 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 5300 7250 5300
Wire Wire Line
	6750 5800 7750 5800
Wire Wire Line
	7750 5800 7750 5700
$Comp
L Device:R_POT RV5
U 1 1 5C6D995F
P 8950 4950
F 0 "RV5" H 8880 4904 50  0000 R CNN
F 1 "100K" H 8880 4995 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_ACP_CA6-H2,5_Horizontal" H 8950 4950 50  0001 C CNN
F 3 "~" H 8950 4950 50  0001 C CNN
	1    8950 4950
	-1   0    0    1   
$EndComp
Wire Wire Line
	7250 5100 7250 5050
Wire Wire Line
	7250 4700 8550 4700
Wire Wire Line
	8550 4700 8550 4950
Wire Wire Line
	8550 4950 8800 4950
Wire Wire Line
	8250 5300 8350 5300
Wire Wire Line
	8700 5300 8950 5300
Wire Wire Line
	8950 5300 8950 5100
Wire Wire Line
	8950 4800 9400 4800
Wire Wire Line
	9400 4800 9400 5050
Wire Wire Line
	9400 5450 8350 5450
Wire Wire Line
	8350 5450 8350 5300
Connection ~ 8350 5300
Wire Wire Line
	8350 5300 8400 5300
Wire Wire Line
	8250 5100 8250 4500
Text GLabel 9650 4500 2    50   Input ~ 0
PWM_output_to_laser
Wire Wire Line
	8250 5500 8250 5650
Wire Wire Line
	6500 6000 6500 5050
Wire Wire Line
	6500 5050 7250 5050
Connection ~ 7250 5050
Wire Wire Line
	7250 5050 7250 4700
$Comp
L power:+5V #PWR0101
U 1 1 5C72BB40
P 7750 4550
F 0 "#PWR0101" H 7750 4400 50  0001 C CNN
F 1 "+5V" H 7765 4723 50  0000 C CNN
F 2 "" H 7750 4550 50  0001 C CNN
F 3 "" H 7750 4550 50  0001 C CNN
	1    7750 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5C72BCAF
P 7750 6250
F 0 "#PWR0102" H 7750 6000 50  0001 C CNN
F 1 "GND" H 7755 6077 50  0000 C CNN
F 2 "" H 7750 6250 50  0001 C CNN
F 3 "" H 7750 6250 50  0001 C CNN
	1    7750 6250
	1    0    0    -1  
$EndComp
Connection ~ 7750 5800
Wire Wire Line
	7250 5500 7150 5500
Wire Wire Line
	7150 5500 7150 4900
Wire Wire Line
	7150 4900 7750 4900
$Comp
L pspice:CAP C2
U 1 1 5C741F2C
P 8250 5900
F 0 "C2" H 8428 5946 50  0000 L CNN
F 1 "101" H 8428 5855 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.4mm_W2.1mm_P2.50mm" H 8250 5900 50  0001 C CNN
F 3 "~" H 8250 5900 50  0001 C CNN
	1    8250 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 6000 8050 6000
Wire Wire Line
	8050 6000 8050 5650
Wire Wire Line
	8050 5650 8250 5650
Connection ~ 8250 5650
Wire Wire Line
	7750 6150 8250 6150
Wire Wire Line
	7750 5800 7750 6150
Wire Wire Line
	7750 6150 7750 6250
Connection ~ 7750 6150
Wire Wire Line
	8350 5300 8350 5050
Wire Wire Line
	8350 4750 8350 4550
Wire Wire Line
	8350 4550 7750 4550
Wire Wire Line
	7750 4550 7750 4900
Connection ~ 7750 4550
Connection ~ 7750 4900
$Comp
L Device:R_US R9
U 1 1 5C7BEAC9
P 8350 4900
F 0 "R9" H 8418 4946 50  0000 L CNN
F 1 "2K" H 8418 4855 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8390 4890 50  0001 C CNN
F 3 "~" H 8350 4900 50  0001 C CNN
	1    8350 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:D D1
U 1 1 5C7C152C
P 8550 5300
F 0 "D1" H 8550 5084 50  0000 C CNN
F 1 "D" H 8550 5175 50  0000 C CNN
F 2 "Diode_THT:D_DO-34_SOD68_P7.62mm_Horizontal" H 8550 5300 50  0001 C CNN
F 3 "~" H 8550 5300 50  0001 C CNN
	1    8550 5300
	-1   0    0    1   
$EndComp
$Comp
L Device:D D2
U 1 1 5C7C1695
P 9400 5200
F 0 "D2" V 9446 5121 50  0000 R CNN
F 1 "D" V 9355 5121 50  0000 R CNN
F 2 "Diode_THT:D_DO-34_SOD68_P7.62mm_Horizontal" H 9400 5200 50  0001 C CNN
F 3 "~" H 9400 5200 50  0001 C CNN
	1    9400 5200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9400 5450 9400 5350
$Comp
L MCU_Module:NUCLEO64-F411RE U?
U 1 1 5C7E3A39
P 1800 2750
F 0 "U?" H 1800 4928 50  0000 C CNN
F 1 "NUCLEO64-F411RE" H 1800 4837 50  0000 C CNN
F 2 "Module:ST_Morpho_Connector_144_STLink" H 2350 850 50  0001 L CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/data_brief/DM00105918.pdf" H 900 1350 50  0001 C CNN
	1    1800 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 2800 4300 1750
Wire Wire Line
	4300 1750 2900 1750
Wire Wire Line
	4200 3000 4200 1950
Wire Wire Line
	4200 1950 2900 1950
Wire Wire Line
	4200 3000 4750 3000
Wire Wire Line
	4200 3100 4200 3550
Wire Wire Line
	4200 3550 2900 3550
Wire Wire Line
	4200 3100 4750 3100
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 5C88BCFF
P 10100 1700
F 0 "J?" H 10160 1840 50  0000 L CNN
F 1 "Conn_01x03_Male" V 10251 1840 50  0000 L CNN
F 2 "" H 10100 1700 50  0001 C CNN
F 3 "~" H 10100 1700 50  0001 C CNN
	1    10100 1700
	-1   0    0    1   
$EndComp
Wire Wire Line
	9400 1600 9900 1600
Wire Wire Line
	9700 2150 9700 1700
Wire Wire Line
	9700 1700 9900 1700
Wire Wire Line
	9900 1800 9900 1950
$Comp
L power:GND #PWR?
U 1 1 5C8B78D2
P 9900 1950
F 0 "#PWR?" H 9900 1700 50  0001 C CNN
F 1 "GND" H 9905 1777 50  0000 C CNN
F 2 "" H 9900 1950 50  0001 C CNN
F 3 "" H 9900 1950 50  0001 C CNN
	1    9900 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 5C8B7E3E
P 10200 3400
F 0 "J?" H 10173 3330 50  0000 R CNN
F 1 "Conn_01x03_Male" H 10173 3421 50  0000 R CNN
F 2 "" H 10200 3400 50  0001 C CNN
F 3 "~" H 10200 3400 50  0001 C CNN
	1    10200 3400
	-1   0    0    1   
$EndComp
Wire Wire Line
	9850 3850 9850 3400
Wire Wire Line
	9850 3400 10000 3400
Wire Wire Line
	10000 3500 10000 3650
$Comp
L power:GND #PWR?
U 1 1 5C8DBD98
P 10000 3650
F 0 "#PWR?" H 10000 3400 50  0001 C CNN
F 1 "GND" H 10005 3477 50  0000 C CNN
F 2 "" H 10000 3650 50  0001 C CNN
F 3 "" H 10000 3650 50  0001 C CNN
	1    10000 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 4500 8700 4500
$Comp
L 4xxx:4081 U?
U 1 1 5C8DF4D1
P 9000 4400
F 0 "U?" H 9000 4725 50  0000 C CNN
F 1 "4081" H 9000 4634 50  0000 C CNN
F 2 "" H 9000 4400 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4073bms-81bms-82bms.pdf" H 9000 4400 50  0001 C CNN
	1    9000 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 4400 9650 4400
Wire Wire Line
	9650 4400 9650 4500
Wire Wire Line
	8700 4300 3800 4300
Wire Wire Line
	3800 4300 3800 3950
$EndSCHEMATC
