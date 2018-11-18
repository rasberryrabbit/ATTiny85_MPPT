EESchema Schematic File Version 4
LIBS:ATTiny85-mppt-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Simple MPPT with ATTiny85"
Date "2018-11-17"
Rev "1.6"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Q_NMOS_GDS Q1
U 1 1 55C339A5
P 8500 5400
F 0 "Q1" H 8750 5300 50  0000 R CNN
F 1 "BUK9511-55A127" H 8700 5100 50  0000 R CNN
F 2 "TO_SOT_Packages_THT-2:TO-220_Neutral123_Vertical" H 8700 5500 29  0001 C CNN
F 3 "" H 8500 5400 60  0000 C CNN
	1    8500 5400
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 55C33F64
P 7050 4250
F 0 "R4" V 7130 4250 50  0000 C CNN
F 1 "100k" V 7050 4250 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 6980 4250 30  0001 C CNN
F 3 "" H 7050 4250 30  0000 C CNN
	1    7050 4250
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 55C34015
P 6900 5300
F 0 "R3" V 6980 5300 50  0000 C CNN
F 1 "10k" V 6900 5300 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 6830 5300 30  0001 C CNN
F 3 "" H 6900 5300 30  0000 C CNN
	1    6900 5300
	1    0    0    -1  
$EndComp
$Comp
L 12f675-mppt-rescue:LM358N-RESCUE-12f675-mppt U2
U 2 1 55C3383E
P 7500 4850
F 0 "U2" H 7450 5050 60  0000 L CNN
F 1 "LM358N" H 7450 4600 60  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 7500 4850 60  0001 C CNN
F 3 "" H 7500 4850 60  0000 C CNN
	2    7500 4850
	1    0    0    -1  
$EndComp
$Comp
L 12f675-mppt-rescue:INDUCTOR L1
U 1 1 55C35536
P 9050 2200
F 0 "L1" V 9000 2200 50  0000 C CNN
F 1 "330uH" V 9150 2200 50  0000 C CNN
F 2 "Inductors_THT:L_Toroid_Vertical_L33.0mm_W17.8mm_P12.70mm_Pulse_KM-5" H 9050 2200 60  0001 C CNN
F 3 "" H 9050 2200 60  0000 C CNN
	1    9050 2200
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_Schottky D1
U 1 1 55C35659
P 8100 2200
F 0 "D1" H 8150 2100 50  0000 C CNN
F 1 "1N5822A" H 8050 2000 50  0000 C CNN
F 2 "Diodes_THT:D_DO-201AD_P15.24mm_Horizontal" H 8100 2200 60  0001 C CNN
F 3 "" H 8100 2200 60  0000 C CNN
	1    8100 2200
	-1   0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D2
U 1 1 55C356EB
P 8400 2700
F 0 "D2" V 8400 2850 50  0000 C CNN
F 1 "1N5822A" V 8500 2900 50  0000 C CNN
F 2 "Diodes_THT:D_DO-201AD_P15.24mm_Horizontal" H 8400 2700 60  0001 C CNN
F 3 "" H 8400 2700 60  0000 C CNN
	1    8400 2700
	0    -1   1    0   
$EndComp
$Comp
L Device:CP C1
U 1 1 55C3588B
P 9500 2500
F 0 "C1" H 9525 2600 50  0000 L CNN
F 1 "100u" H 9525 2400 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D12.5mm_P5.00mm" H 9538 2350 30  0001 C CNN
F 3 "" H 9500 2500 60  0000 C CNN
	1    9500 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_EBC Q4
U 1 1 55C35D82
P 6500 2900
F 0 "Q4" H 6800 2800 50  0000 R CNN
F 1 "2N2222A" H 7000 2950 50  0000 R CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Wide" H 6700 3000 29  0001 C CNN
F 3 "" H 6500 2900 60  0000 C CNN
	1    6500 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 55C35FB2
P 7050 2750
F 0 "C2" H 7075 2850 50  0000 L CNN
F 1 "22uF 50v" H 7075 2650 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D12.5mm_P5.00mm" H 7088 2600 30  0001 C CNN
F 3 "" H 7050 2750 60  0000 C CNN
	1    7050 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:D D3
U 1 1 55C36E30
P 5550 2350
F 0 "D3" H 5550 2450 50  0000 C CNN
F 1 "1N4148" H 5550 2250 50  0000 C CNN
F 2 "Diodes_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5550 2350 60  0001 C CNN
F 3 "" H 5550 2350 60  0000 C CNN
	1    5550 2350
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 55C376F8
P 5450 2850
F 0 "R10" V 5530 2850 50  0000 C CNN
F 1 "1k" V 5450 2850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 5380 2850 30  0001 C CNN
F 3 "" H 5450 2850 30  0000 C CNN
	1    5450 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 55C3A8B1
P 1850 3200
F 0 "R5" V 1930 3200 50  0000 C CNN
F 1 "300k" V 1850 3200 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 1780 3200 30  0001 C CNN
F 3 "" H 1850 3200 30  0000 C CNN
	1    1850 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 55C3B177
P 4550 4400
F 0 "R8" V 4630 4400 50  0000 C CNN
F 1 "100k" V 4550 4400 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 4480 4400 30  0001 C CNN
F 3 "" H 4550 4400 30  0000 C CNN
	1    4550 4400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R6
U 1 1 55C3BCB8
P 4900 4900
F 0 "R6" V 4980 4900 50  0000 C CNN
F 1 "1k" V 4900 4900 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 4830 4900 30  0001 C CNN
F 3 "" H 4900 4900 30  0000 C CNN
	1    4900 4900
	-1   0    0    1   
$EndComp
$Comp
L 12f675-mppt-rescue:LED D4
U 1 1 55C3BFD1
P 4900 5350
F 0 "D4" H 4900 5450 50  0000 C CNN
F 1 "LED" H 4900 5250 50  0000 C CNN
F 2 "LEDs:LED_D4.0mm" H 4900 5350 60  0001 C CNN
F 3 "" H 4900 5350 60  0000 C CNN
	1    4900 5350
	0    -1   -1   0   
$EndComp
$Comp
L Device:D D5
U 1 1 55C3D464
P 2250 2900
F 0 "D5" H 2250 3000 50  0000 C CNN
F 1 "1N4007" H 2250 2800 50  0000 C CNN
F 2 "Diodes_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2250 2900 60  0001 C CNN
F 3 "" H 2250 2900 60  0000 C CNN
	1    2250 2900
	0    1    -1   0   
$EndComp
$Comp
L Device:C C4
U 1 1 55C3DB01
P 3750 3700
F 0 "C4" H 3775 3800 50  0000 L CNN
F 1 "0.1u" H 3775 3600 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D12.5mm_W5.0mm_P7.50mm" H 3788 3550 30  0001 C CNN
F 3 "" H 3750 3700 60  0000 C CNN
	1    3750 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C3
U 1 1 55C3DBAA
P 3100 3700
F 0 "C3" H 3125 3800 50  0000 L CNN
F 1 "100u" H 3125 3600 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D12.5mm_P5.00mm" H 3138 3550 30  0001 C CNN
F 3 "" H 3100 3700 60  0000 C CNN
	1    3100 3700
	1    0    0    -1  
$EndComp
Text Label 5400 2350 2    60   ~ 0
BootStrap
Text Label 7050 3600 2    60   ~ 0
PV-Current
Text Label 4200 4400 2    60   ~ 0
PV-Voltage
Text Notes 8900 5200 2    60   ~ 0
Heat Sink
$Comp
L Device:R R11
U 1 1 55C4C21C
P 7300 3600
F 0 "R11" V 7380 3600 50  0000 C CNN
F 1 "100k" V 7300 3600 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 7230 3600 30  0001 C CNN
F 3 "" H 7300 3600 30  0000 C CNN
	1    7300 3600
	0    1    1    0   
$EndComp
$Comp
L Device:R R12
U 1 1 55C48C57
P 1850 4050
F 0 "R12" V 1930 4050 50  0000 C CNN
F 1 "47k" V 1850 4050 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 1780 4050 30  0001 C CNN
F 3 "" H 1850 4050 30  0000 C CNN
	1    1850 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 55CA080E
P 6700 5300
F 0 "R2" V 6780 5300 50  0000 C CNN
F 1 "100k" V 6700 5300 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 6630 5300 30  0001 C CNN
F 3 "" H 6700 5300 30  0000 C CNN
	1    6700 5300
	-1   0    0    1   
$EndComp
$Comp
L Device:R R13
U 1 1 55CA08C8
P 7050 3950
F 0 "R13" V 7130 3950 50  0000 C CNN
F 1 "10k" V 7050 3950 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 6980 3950 30  0001 C CNN
F 3 "" H 7050 3950 30  0000 C CNN
	1    7050 3950
	0    1    1    0   
$EndComp
Text Notes 1400 3650 0    60   ~ 0
Max 25V
$Comp
L 12f675-mppt-rescue:LED D9
U 1 1 55CCC105
P 5650 5350
F 0 "D9" H 5650 5450 50  0000 C CNN
F 1 "LED" H 5650 5250 50  0000 C CNN
F 2 "LEDs:LED_D4.0mm" H 5650 5350 60  0001 C CNN
F 3 "" H 5650 5350 60  0000 C CNN
	1    5650 5350
	0    -1   -1   0   
$EndComp
$Comp
L 12f675-mppt-rescue:LED D8
U 1 1 55CCC217
P 5650 4850
F 0 "D8" H 5650 4950 50  0000 C CNN
F 1 "LED" H 5650 4750 50  0000 C CNN
F 2 "LEDs:LED_D4.0mm" H 5650 4850 60  0001 C CNN
F 3 "" H 5650 4850 60  0000 C CNN
	1    5650 4850
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R14
U 1 1 55CCC2B4
P 5650 4200
F 0 "R14" V 5730 4200 50  0000 C CNN
F 1 "4.7k" V 5650 4200 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 5580 4200 30  0001 C CNN
F 3 "" H 5650 4200 30  0000 C CNN
	1    5650 4200
	1    0    0    -1  
$EndComp
Text Label 5500 3450 0    60   ~ 0
3.6v
$Comp
L Device:CP C5
U 1 1 55CDDBD9
P 6200 4900
F 0 "C5" H 6225 5000 50  0000 L CNN
F 1 "10u" H 6225 4800 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D12.5mm_P5.00mm" H 6238 4750 30  0001 C CNN
F 3 "" H 6200 4900 60  0000 C CNN
	1    6200 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C6
U 1 1 55D02AF9
P 5200 5150
F 0 "C6" H 5100 5400 50  0000 L CNN
F 1 "10u" H 5000 5300 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D12.5mm_P5.00mm" H 5238 5000 30  0001 C CNN
F 3 "" H 5200 5150 60  0000 C CNN
	1    5200 5150
	1    0    0    -1  
$EndComp
Text Label 8550 6000 0    60   ~ 0
3.6v
$Comp
L 12f675-mppt-rescue:LM358N-RESCUE-12f675-mppt U2
U 1 1 56E669E2
P 8850 4350
F 0 "U2" H 8800 4550 60  0000 L CNN
F 1 "LM358N" H 8800 4100 60  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 8850 4350 60  0001 C CNN
F 3 "" H 8850 4350 60  0000 C CNN
	1    8850 4350
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 56E67518
P 9200 4850
F 0 "R1" V 9280 4850 50  0000 C CNN
F 1 "2.2k" V 9200 4850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 9130 4850 50  0001 C CNN
F 3 "" H 9200 4850 50  0000 C CNN
	1    9200 4850
	0    1    1    0   
$EndComp
$Comp
L Device:R R15
U 1 1 56E68956
P 9650 4300
F 0 "R15" V 9730 4300 50  0000 C CNN
F 1 "10k" V 9650 4300 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 9580 4300 50  0001 C CNN
F 3 "" H 9650 4300 50  0000 C CNN
	1    9650 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	2150 4000 2650 4000
Wire Wire Line
	2650 3700 2650 4000
Connection ~ 2650 4000
Wire Wire Line
	7400 5600 7400 5250
Wire Wire Line
	3500 2350 3500 3400
Connection ~ 3500 3400
Wire Wire Line
	6900 5450 6900 5600
Connection ~ 6900 5600
Wire Wire Line
	7200 4250 8000 4250
Wire Wire Line
	7000 4950 6900 4950
Wire Wire Line
	6900 4250 6900 4950
Connection ~ 6900 4950
Wire Wire Line
	6700 4750 7000 4750
Wire Wire Line
	8400 2850 8400 3050
Wire Wire Line
	8400 3050 8700 3050
Wire Wire Line
	8250 2200 8400 2200
Wire Wire Line
	8400 2200 8400 2550
Connection ~ 8400 2200
Wire Wire Line
	9350 2200 9500 2200
Wire Wire Line
	9500 2200 9500 2350
Connection ~ 7750 2200
Wire Wire Line
	5400 2350 3500 2350
Connection ~ 2250 2200
Connection ~ 2650 5600
Connection ~ 1850 2200
Wire Wire Line
	1850 3050 1850 2200
Wire Wire Line
	1850 3350 1850 3500
Wire Wire Line
	2100 3500 1850 3500
Connection ~ 1850 3500
Wire Wire Line
	4900 5550 4900 5600
Connection ~ 4900 5600
Wire Wire Line
	4900 5150 4900 5050
Wire Wire Line
	2250 3050 2250 3400
Wire Wire Line
	2250 2750 2250 2200
Wire Wire Line
	3100 3850 3100 4000
Connection ~ 3100 4000
Wire Wire Line
	3100 3550 3100 3400
Connection ~ 3100 3400
Wire Wire Line
	3750 3850 3750 4000
Connection ~ 3750 4000
Wire Wire Line
	3750 3550 3750 3400
Connection ~ 3750 3400
Wire Wire Line
	7050 2350 7050 2600
Connection ~ 7400 5600
Connection ~ 7400 4450
Wire Wire Line
	9500 3050 9500 2650
Connection ~ 8400 3050
Connection ~ 9500 3050
Connection ~ 9500 2200
Wire Notes Line
	6050 5850 9800 5850
Wire Wire Line
	1850 4200 1850 5600
Wire Wire Line
	6700 3950 6700 4750
Wire Wire Line
	6700 5450 6700 5600
Connection ~ 6700 5600
Wire Wire Line
	6700 3950 6900 3950
Connection ~ 6700 4750
Wire Wire Line
	7200 3950 8400 3950
Connection ~ 8400 3950
Wire Wire Line
	5650 4350 5650 4500
Wire Wire Line
	5650 5050 5650 5150
Wire Wire Line
	5650 5550 5650 5600
Connection ~ 5650 5600
Wire Wire Line
	5650 4050 6000 4050
Wire Wire Line
	6200 5050 6200 5600
Connection ~ 6200 5600
Wire Wire Line
	6200 4750 6200 3600
Connection ~ 6200 3600
Wire Notes Line
	6050 3500 6050 5850
Wire Notes Line
	6050 3500 6500 3500
Wire Notes Line
	6500 3500 6700 3750
Wire Notes Line
	6700 3750 9800 3750
Wire Wire Line
	3500 6100 8150 6100
Wire Wire Line
	8150 6100 8150 4450
Wire Wire Line
	4900 4300 4900 4750
Wire Wire Line
	5200 5300 5200 5600
Connection ~ 5200 5600
Wire Wire Line
	2100 3500 2100 4400
Wire Wire Line
	2100 4400 4400 4400
Wire Wire Line
	4700 4400 5200 4400
Wire Wire Line
	5200 5000 5200 4400
Connection ~ 5200 4400
Wire Wire Line
	5650 4500 5500 4500
Connection ~ 5650 4500
Wire Wire Line
	6000 4050 6000 4450
Wire Wire Line
	8850 5400 8700 5400
Wire Wire Line
	5500 6000 8850 6000
Wire Wire Line
	8850 6000 8850 5400
Connection ~ 5500 4500
Wire Wire Line
	6000 4450 7400 4450
Wire Wire Line
	9450 5600 8400 5600
Wire Wire Line
	8000 4250 8000 4850
Wire Wire Line
	8000 4850 8750 4850
Wire Wire Line
	8850 3850 8850 3600
Wire Wire Line
	7450 3600 8850 3600
Wire Wire Line
	9450 4450 9450 4850
Connection ~ 8400 5600
Wire Wire Line
	9050 4850 8950 4850
Wire Wire Line
	9450 4450 9250 4450
Connection ~ 9450 4850
Connection ~ 8150 4450
Wire Wire Line
	9650 5100 9650 4450
Wire Wire Line
	9650 3600 9650 4150
Connection ~ 8850 3600
Wire Notes Line
	9800 3750 9800 5850
Wire Wire Line
	9350 4850 9450 4850
Wire Wire Line
	9650 5100 8950 5100
Wire Wire Line
	8950 5100 8950 4850
$Comp
L Device:CP C7
U 1 1 56E7CE1F
P 3300 2750
F 0 "C7" H 3325 2850 50  0000 L CNN
F 1 "47u" H 3325 2650 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D12.5mm_P5.00mm" H 3338 2600 30  0001 C CNN
F 3 "" H 3300 2750 60  0000 C CNN
	1    3300 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2600 3300 2200
Connection ~ 3300 2200
Wire Wire Line
	2150 4000 2150 3100
Wire Wire Line
	2150 3100 3300 3100
Wire Wire Line
	3300 3100 3300 2900
$Comp
L Device:R R16
U 1 1 56ECB4B6
P 3900 5000
F 0 "R16" V 3980 5000 50  0000 C CNN
F 1 "10k" V 3900 5000 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 3830 5000 50  0001 C CNN
F 3 "" H 3900 5000 50  0000 C CNN
	1    3900 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	3750 5000 3500 5000
Connection ~ 3500 5000
Wire Wire Line
	4150 4650 4150 5000
Wire Wire Line
	4150 5000 4050 5000
$Comp
L 12f675-mppt-rescue:SW_PUSH SW1
U 1 1 56ECBA1E
P 3100 4650
F 0 "SW1" H 3250 4760 50  0000 C CNN
F 1 "Write OP-AMP DIFF" H 3100 4570 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 3100 4650 50  0001 C CNN
F 3 "" H 3100 4650 50  0000 C CNN
	1    3100 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 4650 2650 4650
Connection ~ 2650 4650
Wire Wire Line
	2650 4000 3100 4000
Wire Wire Line
	2650 4000 2650 4650
Wire Wire Line
	3500 3400 3750 3400
Wire Wire Line
	3500 3400 3500 5000
Wire Wire Line
	6900 5600 6700 5600
Wire Wire Line
	6900 4950 6900 5150
Wire Wire Line
	8400 2200 8700 2200
Wire Wire Line
	7750 2200 7950 2200
Wire Wire Line
	2250 2200 2500 2200
Wire Wire Line
	2650 5600 1850 5600
Wire Wire Line
	1850 2200 2250 2200
Wire Wire Line
	1850 3500 1850 3900
Wire Wire Line
	4900 5600 2650 5600
Wire Wire Line
	3100 4000 3750 4000
Wire Wire Line
	3100 3400 3500 3400
Wire Wire Line
	7400 5600 6900 5600
Wire Wire Line
	7400 4450 8150 4450
Wire Wire Line
	8400 3050 8400 3950
Wire Wire Line
	9500 3050 10000 3050
Wire Wire Line
	9500 2200 10000 2200
Wire Wire Line
	6700 4750 6700 5150
Wire Wire Line
	8400 3950 8400 5200
Wire Wire Line
	6200 3600 7150 3600
Wire Wire Line
	5200 5600 4900 5600
Wire Wire Line
	5200 4400 5300 4400
Wire Wire Line
	5650 4500 5650 4650
Wire Wire Line
	5500 4500 5500 6000
Wire Wire Line
	8400 5600 7400 5600
Wire Wire Line
	9450 4850 9450 5600
Wire Wire Line
	8150 4450 8450 4450
Wire Wire Line
	8850 3600 9650 3600
Wire Wire Line
	3300 2200 3000 2200
Wire Wire Line
	3500 5000 3500 6100
Wire Wire Line
	4150 4650 3400 4650
Wire Wire Line
	2650 4650 2650 5600
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20PU U3
U 1 1 5BC87E53
P 4450 3400
F 0 "U3" H 3920 3446 50  0000 R CNN
F 1 "ATtiny85-20PU" H 3900 3650 50  0000 R CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 4450 3400 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 4450 3400 50  0001 C CNN
	1    4450 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 4000 4450 4000
Wire Wire Line
	3750 3400 3750 2650
Wire Wire Line
	3750 2650 4450 2650
Wire Wire Line
	4450 2650 4450 2800
Wire Wire Line
	5400 3600 6200 3600
Wire Wire Line
	5300 3500 5050 3500
Wire Wire Line
	4150 4200 4150 4650
Connection ~ 4150 4650
Wire Wire Line
	4900 4300 5200 4300
Wire Wire Line
	5200 4300 5200 3400
Wire Wire Line
	5200 3400 5050 3400
Wire Wire Line
	5650 5600 5900 5600
Wire Wire Line
	5500 3100 5500 4500
Wire Wire Line
	5050 3100 5500 3100
Wire Wire Line
	5050 3600 5100 3600
Wire Wire Line
	5100 3600 5100 4200
Wire Wire Line
	4150 4200 5100 4200
Wire Wire Line
	5300 3500 5300 4400
$Comp
L Regulator_Linear:LM7805_TO220 U1
U 1 1 5BD8D22E
P 2650 3400
F 0 "U1" H 2650 3642 50  0000 C CNN
F 1 "LM7805_TO220" H 2650 3551 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 2650 3625 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 2650 3350 50  0001 C CNN
	1    2650 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 3400 3100 3400
Wire Wire Line
	2350 3400 2250 3400
Wire Wire Line
	5050 3200 5300 3200
Wire Wire Line
	5050 3300 5400 3300
Wire Wire Line
	5400 3300 5400 3600
$Comp
L Device:D_Schottky D6
U 1 1 5BCAD4DB
P 2850 2200
F 0 "D6" H 2900 2100 50  0000 C CNN
F 1 "1N5822A" H 2800 2000 50  0000 C CNN
F 2 "Diodes_THT:D_DO-201AD_P15.24mm_Horizontal" H 2850 2200 60  0001 C CNN
F 3 "" H 2850 2200 60  0000 C CNN
	1    2850 2200
	-1   0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D7
U 1 1 5BCAE8F6
P 2850 1800
F 0 "D7" H 2900 1700 50  0000 C CNN
F 1 "1N5822A" H 2800 1600 50  0000 C CNN
F 2 "Diodes_THT:D_DO-201AD_P15.24mm_Horizontal" H 2850 1800 60  0001 C CNN
F 3 "" H 2850 1800 60  0000 C CNN
	1    2850 1800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2700 1800 2500 1800
Wire Wire Line
	2500 1800 2500 2200
Connection ~ 2500 2200
Wire Wire Line
	2500 2200 2700 2200
Wire Wire Line
	3000 1800 3300 1800
Wire Wire Line
	3300 1800 3300 2200
$Comp
L Device:D_Schottky D10
U 1 1 5BCCACA5
P 8100 1850
F 0 "D10" H 8150 1750 50  0000 C CNN
F 1 "1N5822A" H 8050 1650 50  0000 C CNN
F 2 "Diodes_THT:D_DO-201AD_P15.24mm_Horizontal" H 8100 1850 60  0001 C CNN
F 3 "" H 8100 1850 60  0000 C CNN
	1    8100 1850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7950 1850 7750 1850
Wire Wire Line
	7750 1850 7750 2200
Wire Wire Line
	8250 1850 8400 1850
Wire Wire Line
	8400 1850 8400 2200
$Comp
L Device:D_Schottky D11
U 1 1 5BCE12E7
P 8700 2700
F 0 "D11" V 8700 2550 50  0000 C CNN
F 1 "1N5822A" V 8800 2450 50  0000 C CNN
F 2 "Diodes_THT:D_DO-201AD_P15.24mm_Horizontal" H 8700 2700 60  0001 C CNN
F 3 "" H 8700 2700 60  0000 C CNN
	1    8700 2700
	0    -1   1    0   
$EndComp
Connection ~ 8700 2200
Wire Wire Line
	8700 2200 8750 2200
Connection ~ 8700 3050
Wire Wire Line
	8700 3050 9500 3050
$Comp
L 12f675-mppt-rescue:INDUCTOR L2
U 1 1 5BCF09F4
P 9050 1850
F 0 "L2" V 9000 1850 50  0000 C CNN
F 1 "330uH" V 9150 1850 50  0000 C CNN
F 2 "Inductors_THT:L_Toroid_Vertical_L33.0mm_W17.8mm_P12.70mm_Pulse_KM-5" H 9050 1850 60  0001 C CNN
F 3 "" H 9050 1850 60  0000 C CNN
	1    9050 1850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8750 1850 8700 1850
Wire Wire Line
	8700 1850 8700 2200
Wire Wire Line
	9350 1850 9500 1850
Wire Wire Line
	9500 1850 9500 2200
Wire Notes Line
	2400 2050 3400 2050
Wire Notes Line
	3400 2050 3400 1650
Wire Notes Line
	3400 1650 2400 1650
Wire Notes Line
	2400 1650 2400 2050
Wire Notes Line
	7700 2100 8500 2100
Wire Notes Line
	8500 2100 8500 1650
Wire Notes Line
	8500 1650 7700 1650
Wire Notes Line
	7700 1650 7700 2100
Wire Notes Line
	8650 2000 9600 2000
Wire Notes Line
	9600 2000 9600 1600
Wire Notes Line
	9600 1600 8650 1600
Wire Notes Line
	8650 1600 8650 2000
Wire Notes Line
	8550 2350 8550 2900
Wire Notes Line
	8550 2900 9200 2900
Wire Notes Line
	9200 2900 9200 2350
Wire Notes Line
	9200 2350 8550 2350
Text Notes 9200 3750 0    50   ~ 0
45x (6A)
Text Notes 3100 1650 0    50   ~ 0
100W
Text Notes 8150 1650 0    50   ~ 0
100W
Text Notes 9300 1600 0    50   ~ 0
100W
Text Notes 8800 2350 0    50   ~ 0
100W
$Comp
L Connector:Conn_01x01_Male J1
U 1 1 5BD97287
P 1150 950
F 0 "J1" V 1210 990 50  0000 L CNN
F 1 "S+" V 1301 990 50  0000 L CNN
F 2 "Connectors:1pin" H 1150 950 50  0001 C CNN
F 3 "~" H 1150 950 50  0001 C CNN
	1    1150 950 
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J2
U 1 1 5BD97502
P 1950 950
F 0 "J2" V 2010 990 50  0000 L CNN
F 1 "S-" V 2101 990 50  0000 L CNN
F 2 "Connectors:1pin" H 1950 950 50  0001 C CNN
F 3 "~" H 1950 950 50  0001 C CNN
	1    1950 950 
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J3
U 1 1 5BD9774E
P 9050 1000
F 0 "J3" V 9110 1040 50  0000 L CNN
F 1 "O+" V 8950 1000 50  0000 L CNN
F 2 "Connectors:1pin" H 9050 1000 50  0001 C CNN
F 3 "~" H 9050 1000 50  0001 C CNN
	1    9050 1000
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J4
U 1 1 5BD9781C
P 9900 1000
F 0 "J4" V 9960 1040 50  0000 L CNN
F 1 "O-" V 9800 1000 50  0000 L CNN
F 2 "Connectors:1pin" H 9900 1000 50  0001 C CNN
F 3 "~" H 9900 1000 50  0001 C CNN
	1    9900 1000
	0    1    1    0   
$EndComp
$Comp
L power:+24V #PWR02
U 1 1 5BD97B51
P 1200 1900
F 0 "#PWR02" H 1200 1750 50  0001 C CNN
F 1 "+24V" H 1215 2073 50  0000 C CNN
F 2 "" H 1200 1900 50  0001 C CNN
F 3 "" H 1200 1900 50  0001 C CNN
	1    1200 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 2200 1200 1900
Wire Wire Line
	1200 2200 1850 2200
$Comp
L power:+24V #PWR01
U 1 1 5BDA0204
P 950 1150
F 0 "#PWR01" H 950 1000 50  0001 C CNN
F 1 "+24V" H 965 1323 50  0000 C CNN
F 2 "" H 950 1150 50  0001 C CNN
F 3 "" H 950 1150 50  0001 C CNN
	1    950  1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  1150 950  1250
Wire Wire Line
	950  1250 1150 1250
Wire Wire Line
	1150 1250 1150 1150
$Comp
L power:GND #PWR04
U 1 1 5BDA8F5A
P 2200 1200
F 0 "#PWR04" H 2200 950 50  0001 C CNN
F 1 "GND" H 2205 1027 50  0000 C CNN
F 2 "" H 2200 1200 50  0001 C CNN
F 3 "" H 2200 1200 50  0001 C CNN
	1    2200 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1150 1950 1200
Wire Wire Line
	1950 1200 2200 1200
$Comp
L power:GND #PWR03
U 1 1 5BDB22B1
P 1250 5800
F 0 "#PWR03" H 1250 5550 50  0001 C CNN
F 1 "GND" H 1255 5627 50  0000 C CNN
F 2 "" H 1250 5800 50  0001 C CNN
F 3 "" H 1250 5800 50  0001 C CNN
	1    1250 5800
	1    0    0    -1  
$EndComp
$Comp
L power:PRI_HI #PWR05
U 1 1 5BDB29AF
P 8850 1200
F 0 "#PWR05" H 8850 1050 50  0001 C CNN
F 1 "PRI_HI" H 8867 1373 50  0000 C CNN
F 2 "" H 8850 1200 50  0001 C CNN
F 3 "" H 8850 1200 50  0001 C CNN
	1    8850 1200
	1    0    0    -1  
$EndComp
$Comp
L power:PRI_LO #PWR08
U 1 1 5BDB2A67
P 10100 1200
F 0 "#PWR08" H 10100 1050 50  0001 C CNN
F 1 "PRI_LO" H 10117 1373 50  0000 C CNN
F 2 "" H 10100 1200 50  0001 C CNN
F 3 "" H 10100 1200 50  0001 C CNN
	1    10100 1200
	1    0    0    -1  
$EndComp
$Comp
L power:PRI_HI #PWR06
U 1 1 5BDB2AD7
P 10000 2200
F 0 "#PWR06" H 10000 2050 50  0001 C CNN
F 1 "PRI_HI" H 10017 2373 50  0000 C CNN
F 2 "" H 10000 2200 50  0001 C CNN
F 3 "" H 10000 2200 50  0001 C CNN
	1    10000 2200
	1    0    0    -1  
$EndComp
$Comp
L power:PRI_LO #PWR07
U 1 1 5BDB2B40
P 10000 3050
F 0 "#PWR07" H 10000 2900 50  0001 C CNN
F 1 "PRI_LO" H 10017 3223 50  0000 C CNN
F 2 "" H 10000 3050 50  0001 C CNN
F 3 "" H 10000 3050 50  0001 C CNN
	1    10000 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 1200 8850 1250
Wire Wire Line
	8850 1250 9050 1250
Wire Wire Line
	9050 1250 9050 1200
Wire Wire Line
	9900 1200 9900 1250
Wire Wire Line
	9900 1250 10100 1250
Wire Wire Line
	10100 1250 10100 1200
Wire Wire Line
	1250 5800 1250 5600
Wire Wire Line
	1250 5600 1850 5600
Connection ~ 1850 5600
Wire Wire Line
	8700 2200 8700 2550
Wire Wire Line
	8700 2850 8700 3050
Text Notes 5850 6250 0    50   ~ 0
Q1 = IRLZ44NPBF ->
Text Notes 6750 6250 0    50   ~ 0
3.6{Aref}/(35*10-3{rds}*6{current})=17.14/10{U2B}=1.74-1
Text Notes 6750 6350 0    50   ~ 0
R15 = 2.2k{R1} * 0.74 = 2.97k
Text Notes 8150 6350 0    50   ~ 0
or
Text Notes 8400 6350 0    50   ~ 0
R1 = 10k{R15}/0.74 = 13.51k{12k}
Text Notes 2000 6250 0    50   ~ 0
Q1 = BUK9511-55A127 ->
Text Notes 3150 6250 0    50   ~ 0
3.6{Aref}/(11*10-3{rds}*6{current}=54.54/10{U2B}=5.45-1
Text Notes 3150 6350 0    50   ~ 0
R1 = 10k{R15}/4.45 = 2.24k{2.2k}
Text Notes 6200 6450 0    50   ~ 0
40milli Ohm, R15 = 2.2k{R1} * (1.5-1) = 1.1{best, 1k} or R1 = 10k{R15} / (1.5-1) = 20k(22k)
Text Notes 2000 6450 0    50   ~ 0
Q1 rds <= 55milli Ohm. If bigger, R2/R3 and R4/R13 must change.
$Comp
L Device:R R7
U 1 1 5BDAFBE4
P 6150 2750
F 0 "R7" V 6230 2750 50  0000 C CNN
F 1 "1k" V 6150 2750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 6080 2750 30  0001 C CNN
F 3 "" H 6150 2750 30  0000 C CNN
	1    6150 2750
	0    1    1    0   
$EndComp
Text Label 5300 2700 0    50   ~ 0
~PWM
Wire Wire Line
	7750 2200 7750 2650
Wire Wire Line
	7750 2950 7050 2950
Wire Wire Line
	7050 2950 7050 2900
Wire Wire Line
	5200 5600 5400 5600
Wire Wire Line
	6200 5600 6700 5600
Wire Wire Line
	5900 3200 5900 3450
Wire Wire Line
	5900 3450 5750 3450
Wire Wire Line
	5750 3450 5750 3800
Wire Wire Line
	5750 3800 5400 3800
Wire Wire Line
	5400 3800 5400 5600
Connection ~ 5400 5600
Wire Wire Line
	5400 5600 5650 5600
$Comp
L Device:R R9
U 1 1 5BDD9D33
P 5900 2600
F 0 "R9" V 5980 2600 50  0000 C CNN
F 1 "10k" V 5900 2600 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 5830 2600 30  0001 C CNN
F 3 "" H 5900 2600 30  0000 C CNN
	1    5900 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	5700 2350 5900 2350
Wire Wire Line
	5900 2750 5900 2800
Wire Wire Line
	5900 2350 5900 2450
Connection ~ 5900 2350
Wire Wire Line
	5900 2350 6600 2350
Wire Wire Line
	6000 2750 5900 2750
Connection ~ 5900 2750
Wire Wire Line
	6300 2750 6300 2900
$Comp
L Device:Q_PNP_EBC Q5
U 1 1 5BE09576
P 6500 3300
F 0 "Q5" H 6691 3254 50  0000 L CNN
F 1 "2N2907A" H 6691 3345 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Wide" H 6700 3400 50  0001 C CNN
F 3 "~" H 6500 3300 50  0001 C CNN
	1    6500 3300
	1    0    0    1   
$EndComp
Wire Wire Line
	6300 3300 6300 2900
Connection ~ 6300 2900
Wire Wire Line
	6600 3500 7750 3500
Wire Wire Line
	7750 3500 7750 2950
Connection ~ 7750 2950
Wire Wire Line
	7250 2500 7250 2650
Wire Wire Line
	6600 2350 6600 2700
Connection ~ 6600 2350
Wire Wire Line
	6600 2350 7050 2350
$Comp
L Device:Q_NMOS_GDS Q2
U 1 1 5BDC3BBC
P 7250 2300
F 0 "Q2" V 7593 2300 50  0000 C CNN
F 1 "BUK9511-55A127" V 7502 2300 50  0000 C CNN
F 2 "TO_SOT_Packages_THT-2:TO-220_Neutral123_Vertical" H 7450 2400 50  0001 C CNN
F 3 "~" H 7250 2300 50  0001 C CNN
	1    7250 2300
	0    -1   -1   0   
$EndComp
$Comp
L Device:Q_NPN_EBC Q3
U 1 1 5BD9A966
P 5800 3000
F 0 "Q3" H 6100 2900 50  0000 R CNN
F 1 "2N2222A" H 6300 3050 50  0000 R CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Wide" H 6000 3100 29  0001 C CNN
F 3 "" H 5800 3000 60  0000 C CNN
	1    5800 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3200 5300 2700
Wire Wire Line
	5300 2700 5450 2700
Wire Wire Line
	5450 3000 5600 3000
$Comp
L Device:CP C8
U 1 1 5BE62CB0
P 5900 4900
F 0 "C8" H 5925 5000 50  0000 L CNN
F 1 "10u" H 5925 4800 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D12.5mm_P5.00mm" H 5938 4750 30  0001 C CNN
F 3 "" H 5900 4900 60  0000 C CNN
	1    5900 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4750 5900 4500
Wire Wire Line
	5900 4500 5650 4500
Wire Wire Line
	5900 5050 5900 5600
Connection ~ 5900 5600
Wire Wire Line
	5900 5600 6200 5600
$Comp
L Device:D_Zener D12
U 1 1 5BEB0C16
P 7500 2650
F 0 "D12" H 7500 2866 50  0000 C CNN
F 1 "Optinal Zenner" H 7500 2775 50  0000 C CNN
F 2 "Diodes_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 7500 2650 50  0001 C CNN
F 3 "~" H 7500 2650 50  0001 C CNN
	1    7500 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2650 7750 2650
Connection ~ 7750 2650
Wire Wire Line
	7750 2650 7750 2950
Wire Wire Line
	7350 2650 7250 2650
Connection ~ 7250 2650
Wire Wire Line
	7250 2650 7250 3100
Wire Wire Line
	3300 2200 7050 2200
Wire Wire Line
	7450 2200 7750 2200
$Comp
L Device:R R17
U 1 1 5BF0956D
P 6950 3100
F 0 "R17" V 7030 3100 50  0000 C CNN
F 1 "1k" V 6950 3100 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P2.54mm_Vertical" V 6880 3100 30  0001 C CNN
F 3 "" H 6950 3100 30  0000 C CNN
	1    6950 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	7250 3100 7100 3100
Wire Wire Line
	6800 3100 6600 3100
Connection ~ 6600 3100
$EndSCHEMATC
