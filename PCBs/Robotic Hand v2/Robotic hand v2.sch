EESchema Schematic File Version 4
LIBS:Robotic hand v2-cache
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
Wire Notes Line
	4450 3100 5700 3100
Wire Notes Line
	5700 4150 4450 4150
Text Notes 4500 4100 0    50   ~ 0
Servo Driver
Text Label 5350 3425 2    50   ~ 0
GND
Text Label 4625 3525 2    50   ~ 0
OE
Text Label 5350 3625 2    50   ~ 0
SCL
Text Label 5350 3725 2    50   ~ 0
SDA
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5E947210
P 4775 3525
F 0 "JP1" H 4775 3730 50  0000 C CNN
F 1 "Enable OE" H 4775 3639 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 4775 3525 50  0001 C CNN
F 3 "~" H 4775 3525 50  0001 C CNN
	1    4775 3525
	1    0    0    -1  
$EndComp
Text Label 4125 4000 0    50   ~ 0
SCL
Text Label 4125 3900 0    50   ~ 0
SDA
Text Label 3125 3900 2    50   ~ 0
OE
Wire Wire Line
	3625 4500 3675 4500
Connection ~ 3675 4500
Wire Wire Line
	3675 4500 3725 4500
$Comp
L power:GND #PWR01
U 1 1 5E951582
P 3675 4600
F 0 "#PWR01" H 3675 4350 50  0001 C CNN
F 1 "GND" H 3680 4427 50  0000 C CNN
F 2 "" H 3675 4600 50  0001 C CNN
F 3 "" H 3675 4600 50  0001 C CNN
	1    3675 4600
	1    0    0    -1  
$EndComp
Text Label 3675 4600 0    50   ~ 0
GND
Wire Wire Line
	4925 3525 5350 3525
$Comp
L Connector_Generic:Conn_02x04_Odd_Even U3
U 1 1 5E9563F5
P 5175 2625
F 0 "U3" H 5300 2300 50  0000 L CNN
F 1 "Nrf24l01" H 5275 2225 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x04_P2.54mm_Vertical" H 5175 2625 50  0001 C CNN
F 3 "~" H 5175 2625 50  0001 C CNN
	1    5175 2625
	1    0    0    -1  
$EndComp
Text Label 5475 2625 0    50   ~ 0
CSN
Text Label 4975 2625 2    50   ~ 0
CE
Text Label 5475 2725 0    50   ~ 0
MOSI
Text Label 4975 2725 2    50   ~ 0
SCK
Text Label 4975 2825 2    50   ~ 0
MISO
Text Label 4975 2525 2    50   ~ 0
GND
Text Label 5475 2525 0    50   ~ 0
3v3
Text Label 3125 4000 2    50   ~ 0
MOSI
Text Label 3125 4100 2    50   ~ 0
MISO
Text Label 3125 4200 2    50   ~ 0
SCK
Text Label 5350 4600 2    50   ~ 0
GND
Text Label 3125 2900 2    50   ~ 0
Tx
Text Label 3125 3000 2    50   ~ 0
Rx
Wire Notes Line
	4450 2250 4450 4125
Text Notes 4475 3075 0    50   ~ 0
Reciever
Text Notes 4475 4950 0    50   ~ 0
BLE Bluetooth
Wire Wire Line
	3675 4500 3675 4600
Wire Notes Line
	2775 2250 5700 2250
Wire Notes Line
	2775 5000 5700 5000
Text Notes 2825 4950 0    50   ~ 0
Arduino Nano
NoConn ~ 4125 2900
NoConn ~ 4125 3000
NoConn ~ 4125 3300
NoConn ~ 4125 3800
Wire Notes Line
	2775 1525 5700 1525
Wire Notes Line
	5700 1525 5700 5725
Wire Notes Line
	2775 1525 2775 5725
Text Notes 3325 1850 0    50   ~ 0
+
Text Label 3900 2050 0    50   ~ 0
GND
Wire Wire Line
	3900 1700 3900 1850
$Comp
L Device:R R1
U 1 1 5E97A008
P 4050 1850
F 0 "R1" V 3843 1850 50  0000 C CNN
F 1 "470Ω" V 3934 1850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3980 1850 50  0001 C CNN
F 3 "~" H 4050 1850 50  0001 C CNN
	1    4050 1850
	0    1    1    0   
$EndComp
$Comp
L Device:LED D1
U 1 1 5E97ADC7
P 4350 1850
F 0 "D1" H 4343 1595 50  0000 C CNN
F 1 "PWR LED" H 4343 1686 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 4350 1850 50  0001 C CNN
F 3 "~" H 4350 1850 50  0001 C CNN
	1    4350 1850
	-1   0    0    1   
$EndComp
Wire Wire Line
	4500 1850 4550 1850
Text Label 4550 1850 0    50   ~ 0
GND
Text Notes 4325 2200 0    50   ~ 0
Power In
$Comp
L Robotic-hand-v2-rescue:LD1117V33-dk_PMIC-Voltage-Regulators-Linear U6
U 1 1 5E99C15D
P 5200 1875
F 0 "U6" H 4950 2150 60  0000 C CNN
F 1 "LD1117 - 3.3v" H 5200 2056 60  0000 C CNN
F 2 "digikey-footprints:SOT-223" H 5400 2075 60  0001 L CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/99/3b/7d/91/91/51/4b/be/CD00000544.pdf/files/CD00000544.pdf/jcr:content/translations/en.CD00000544.pdf" H 5400 2175 60  0001 L CNN
F 4 "497-1491-5-ND" H 5400 2275 60  0001 L CNN "Digi-Key_PN"
F 5 "LD1117V33" H 5400 2375 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 5400 2475 60  0001 L CNN "Category"
F 7 "PMIC - Voltage Regulators - Linear" H 5400 2575 60  0001 L CNN "Family"
F 8 "http://www.st.com/content/ccc/resource/technical/document/datasheet/99/3b/7d/91/91/51/4b/be/CD00000544.pdf/files/CD00000544.pdf/jcr:content/translations/en.CD00000544.pdf" H 5400 2675 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/stmicroelectronics/LD1117V33/497-1491-5-ND/586012" H 5400 2775 60  0001 L CNN "DK_Detail_Page"
F 10 "IC REG LINEAR 3.3V 800MA TO220AB" H 5400 2875 60  0001 L CNN "Description"
F 11 "STMicroelectronics" H 5400 2975 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5400 3075 60  0001 L CNN "Status"
	1    5200 1875
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2050 3900 2050
Connection ~ 3900 1850
Wire Notes Line
	4725 1525 4725 2250
Text Label 5500 2175 0    50   ~ 0
GND
NoConn ~ 3725 2500
Text Label 5500 1875 0    50   ~ 0
3v3
$Comp
L Device:C C1
U 1 1 5E9AEC39
P 4900 2025
F 0 "C1" H 4750 1950 50  0000 L CNN
F 1 "10uF" H 4750 1875 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4938 1875 50  0001 C CNN
F 3 "~" H 4900 2025 50  0001 C CNN
	1    4900 2025
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E9AFBCC
P 5500 2025
F 0 "C2" H 5615 2071 50  0000 L CNN
F 1 "10uF" H 5625 2000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5538 1875 50  0001 C CNN
F 3 "~" H 5500 2025 50  0001 C CNN
	1    5500 2025
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 2175 5200 2175
Connection ~ 5200 2175
Wire Wire Line
	5200 2175 5500 2175
Text Notes 5125 1625 0    50   ~ 0
3.3v Regulator
Text Label 3125 3500 2    50   ~ 0
CE
Text Label 3125 3600 2    50   ~ 0
CSN
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5E9B4CF0
P 3675 4600
F 0 "#FLG0102" H 3675 4675 50  0001 C CNN
F 1 "PWR_FLAG" V 3675 4727 50  0000 L CNN
F 2 "" H 3675 4600 50  0001 C CNN
F 3 "~" H 3675 4600 50  0001 C CNN
	1    3675 4600
	0    -1   -1   0   
$EndComp
Connection ~ 3675 4600
Wire Notes Line
	5700 5725 2775 5725
$Comp
L Device:Rotary_Encoder_Switch SW2
U 1 1 5E9C062D
P 3475 5450
F 0 "SW2" H 3475 5817 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 3475 5726 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 3325 5610 50  0001 C CNN
F 3 "~" H 3475 5710 50  0001 C CNN
	1    3475 5450
	1    0    0    -1  
$EndComp
Text Label 3175 5350 2    50   ~ 0
EncoderA
Text Label 3175 5550 2    50   ~ 0
EncoderB
Text Label 3775 5550 0    50   ~ 0
GND
Text Label 3125 3100 2    50   ~ 0
EncoderA
Text Label 3125 3300 2    50   ~ 0
EncoderB
Text Label 3775 5350 0    50   ~ 0
Sw
Text Label 3125 3400 2    50   ~ 0
Sw
$Comp
L Connector:Conn_01x04_Male U5
U 1 1 5E9C6952
P 5600 5400
F 0 "U5" H 5825 5725 50  0000 R CNN
F 1 "I2C LCD" H 5825 5625 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5600 5400 50  0001 C CNN
F 3 "~" H 5600 5400 50  0001 C CNN
	1    5600 5400
	-1   0    0    -1  
$EndComp
Text Label 5400 5400 2    50   ~ 0
GND
Text Label 5400 5500 2    50   ~ 0
SCL
Text Label 5400 5600 2    50   ~ 0
SDA
Text Notes 5250 5700 0    50   ~ 0
LCD Screen
$Comp
L Switch:SW_DIP_x01 SW1
U 1 1 5E97770E
P 3600 1850
F 0 "SW1" H 3600 2117 50  0000 C CNN
F 1 "PWR" H 3600 2026 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 3600 1850 50  0001 C CNN
F 3 "~" H 3600 1850 50  0001 C CNN
	1    3600 1850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Female U2
U 1 1 5E941577
P 5550 3625
F 0 "U2" H 4925 3525 50  0000 L CNN
F 1 "PCA9685" H 4925 3450 50  0000 L CNN
F 2 "Josh's Library:PCA9685" H 5550 3625 50  0001 C CNN
F 3 "~" H 5550 3625 50  0001 C CNN
	1    5550 3625
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Female U4
U 1 1 5E95E8AA
P 5550 4600
F 0 "U4" H 5425 4975 50  0000 L CNN
F 1 "HM-10" H 5425 4900 50  0000 L CNN
F 2 "Josh's Library:HM-10" H 5550 4600 50  0001 C CNN
F 3 "~" H 5550 4600 50  0001 C CNN
	1    5550 4600
	1    0    0    -1  
$EndComp
Text Notes 2825 5700 0    50   ~ 0
Encoder\n
$Comp
L Connector:Barrel_Jack J1
U 1 1 5E974F59
P 3000 1950
F 0 "J1" H 3057 2275 50  0000 C CNN
F 1 "Barrel_Jack" H 3057 2184 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 3050 1910 50  0001 C CNN
F 3 "~" H 3050 1910 50  0001 C CNN
	1    3000 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:D D2
U 1 1 5EC49AA4
P 3675 2350
F 0 "D2" H 3675 2566 50  0000 C CNN
F 1 "D" H 3675 2475 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3675 2350 50  0001 C CNN
F 3 "~" H 3675 2350 50  0001 C CNN
	1    3675 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3525 2350 3525 2375
Text Label 3825 2350 0    50   ~ 0
5v
Text Label 5350 3825 2    50   ~ 0
5v
Text Label 5350 4500 2    50   ~ 0
5v
Text Label 5400 5300 2    50   ~ 0
5v
Text Label 3175 5450 2    50   ~ 0
5v
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5EC64254
P 3525 2375
F 0 "#FLG0103" H 3525 2450 50  0001 C CNN
F 1 "PWR_FLAG" V 3525 2502 50  0000 L CNN
F 2 "" H 3525 2375 50  0001 C CNN
F 3 "~" H 3525 2375 50  0001 C CNN
	1    3525 2375
	0    -1   -1   0   
$EndComp
Connection ~ 3525 2375
Wire Wire Line
	3525 2375 3525 2500
Wire Wire Line
	3825 2350 3825 2500
Text Label 3125 3200 2    50   ~ 0
IRQ
Text Label 5475 2825 0    50   ~ 0
IRQ
$Comp
L Jumper:SolderJumper_3_Bridged12 JP3-TX1
U 1 1 5EC6AEAA
P 4925 4250
F 0 "JP3-TX1" H 4925 4455 50  0000 C CNN
F 1 "Tx" H 4925 4364 50  0000 C CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_RoundedPad1.0x1.5mm" H 4925 4250 50  0001 C CNN
F 3 "~" H 4925 4250 50  0001 C CNN
	1    4925 4250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5350 4700 4925 4700
Wire Wire Line
	4925 4700 4925 4400
Wire Wire Line
	5350 4800 4750 4800
Wire Wire Line
	4750 4800 4750 4575
Text Label 5125 4250 0    50   ~ 0
BTX
Text Label 4600 4375 2    50   ~ 0
BRX
Text Label 4725 4250 2    50   ~ 0
Tx
Text Label 4600 4775 2    50   ~ 0
Rx
Text Label 3125 3800 2    50   ~ 0
BRX
Text Label 3125 3700 2    50   ~ 0
BTX
Text Label 5350 4900 2    50   ~ 0
Brk
$Comp
L MCU_Module:Arduino_Nano_v3.x U1
U 1 1 5E93DDE8
P 3625 3500
F 0 "U1" V 3525 3150 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" V 3625 3450 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 3775 2550 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 3625 2500 50  0001 C CNN
	1    3625 3500
	1    0    0    -1  
$EndComp
Text Label 5350 4400 2    50   ~ 0
State
Text Label 4125 4100 0    50   ~ 0
State
Text Label 4125 4200 0    50   ~ 0
Brk
$Comp
L Jumper:SolderJumper_3_Bridged12 JP2-RX1
U 1 1 5EC67A68
P 4600 4575
F 0 "JP2-RX1" V 4554 4643 50  0000 L CNN
F 1 "Rx" V 4645 4643 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_RoundedPad1.0x1.5mm" H 4600 4575 50  0001 C CNN
F 3 "~" H 4600 4575 50  0001 C CNN
	1    4600 4575
	0    -1   1    0   
$EndComp
Text Label 3900 1700 0    50   ~ 0
5v
Text Label 5350 3925 2    50   ~ 0
5v
Text Label 4125 3500 0    50   ~ 0
Red
Text Label 4125 3600 0    50   ~ 0
Green
Text Label 4125 3700 0    50   ~ 0
Blue
$Comp
L Robotic-hand-v2-rescue:LED_RGB-freetronics_schematic LED1
U 1 1 5EAD22AC
P 4675 5300
F 0 "LED1" H 4675 5515 50  0000 C CNN
F 1 "LED_RGB" H 4675 5424 50  0000 C CNN
F 2 "Josh's Library:RGB LED" H 4575 5650 60  0001 C CNN
F 3 "" H 4675 5300 60  0000 C CNN
	1    4675 5300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5EAD610D
P 4325 5300
F 0 "R2" V 4118 5300 50  0000 C CNN
F 1 "180Ω" V 4209 5300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4255 5300 50  0001 C CNN
F 3 "~" H 4325 5300 50  0001 C CNN
	1    4325 5300
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 5EAD67E9
P 4325 5450
F 0 "R3" V 4118 5450 50  0000 C CNN
F 1 "120Ω" V 4209 5450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4255 5450 50  0001 C CNN
F 3 "~" H 4325 5450 50  0001 C CNN
	1    4325 5450
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 5EAD6C2F
P 4325 5600
F 0 "R4" V 4118 5600 50  0000 C CNN
F 1 "120Ω" V 4209 5600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4255 5600 50  0001 C CNN
F 3 "~" H 4325 5600 50  0001 C CNN
	1    4325 5600
	0    1    1    0   
$EndComp
Connection ~ 4875 5450
Wire Wire Line
	4875 5450 4875 5600
Wire Wire Line
	4875 5450 5000 5450
Text Label 5000 5450 0    50   ~ 0
GND
Text Label 4175 5300 2    50   ~ 0
Red
Text Label 4175 5450 2    50   ~ 0
Green
Text Label 4175 5600 2    50   ~ 0
Blue
Wire Wire Line
	4875 5300 4875 5450
Text Label 4900 1875 2    50   ~ 0
5v
Wire Notes Line
	4450 4150 4450 5000
Wire Notes Line
	5175 5000 5175 5725
Wire Notes Line
	3950 5725 3950 5000
$EndSCHEMATC
