# verify PICO_SDK_PATH is not set

This may take some time..

export "PICO_SDK_PATH"="" -> not set SDK path

echo "$PICO_SDK_PATH" -> check it's not set

# build and run project

mkdir build

cd build

cmake ../project

make

cp file_name.uf2 /media/user_name/RPI-RP2/


# Notes

GPIO's 4 and 5 not used due to conflit probability with the uart line


# PIN configuration

| GPIO | Description       |
| ---- | ----------------- |
| 0    | input pull down   |
| 1    | input pull down   |
| 2    | input pull down   |
| 3    | input pull down   |
| 4    | not an IO         |
| 5    | not an IO         |
| 6    | input pull down   |
| 7    | input pull down   |
| 8    | input pull down   |
| 9    | input pull down   |
| 10   | input pull down   |
| 11   | input pull down   |
| 12   | input pull down   |
| 13   | input pull down   |
| 14   | input pull down   |
| 15   | input pull down   |
| 16   | input pull down   |
| 17   | input pull down   |
| 18   | input pull down   |
| 19   | input pull down   |
| 20   | input pull down   |
| 21   | input pull down   |
| 22   | input pull down   |
| 23   | not an IO         |
| 24   | not an IO         |
| 25   | INTERNAL LED      |
| 26   | input pull down   |
| 27   | input pull down   |

# MODBUS HOLDING REGISTER AFFECTATION
Register Initial value	Description
0	        PZ	
1	        A!	
2	        0x01	
3	        24	        Number of GPIO configured
4	        N/A	N/A
5	        N/A	N/A
6	        N/A	N/A
7	        N/A	N/A
8	        N/A	N/A
9	        N/A	N/A
10	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
11	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
12	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
13	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
14	        0xFF    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
15	        0xFF    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
16	        0x02       	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
17	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
18      	0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
19	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
20	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
21	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
22	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
23	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
24	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
25	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
26	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
27	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
28	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
29	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
30	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
31	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
32	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
33	        0xFF    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
34	        0xFF    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
35	        0xFF    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
36	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
37	        0x02    	IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF)
38	        N/A     	N/A
39	        N/A     	N/A
40	        0x00    	Value of GPIO_0 if in IN mode
41	        0x00    	Value of GPIO_1 if in IN mode
42	        0x00    	Value of GPIO_2 if in IN mode
43	        0x00    	Value of GPIO_3 if in IN mode
44	        0xFF    	Value of GPIO_4 if in IN mode
45	        0xFF    	Value of GPIO_5 if in IN mode
46	        0x00    	Value of GPIO_6 if in IN mode
47	        0x00    	Value of GPIO_7 if in IN mode
48	        0x00    	Value of GPIO_8 if in IN mode
49	        0x00    	Value of GPIO_9 if in IN mode
50	        0x00    	Value of GPIO_10 if in IN mode
51	        0x00    	Value of GPIO_11 if in IN mode
52	        0x00    	Value of GPIO_12 if in IN mode
53	        0x00    	Value of GPIO_13 if in IN mode
54	        0x00    	Value of GPIO_14 if in IN mode
55	        0x00    	Value of GPIO_15 if in IN mode
56	        0x00    	Value of GPIO_16 if in IN mode
57	        0x00    	Value of GPIO_17 if in IN mode
58	        0x00    	Value of GPIO_18 if in IN mode
59	        0x00    	Value of GPIO_19 if in IN mode
60	        0x00    	Value of GPIO_20 if in IN mode
61	        0x00    	Value of GPIO_21 if in IN mode
62	        0x00    	Value of GPIO_22 if in IN mode
63	        0xFF    	Value of GPIO_23 if in IN mode
64	        0xFF    	Value of GPIO_24 if in IN mode
65	        0xFF    	Value of GPIO_25 if in IN mode
66	        0x00    	Value of GPIO_26 if in IN mode
67	        0x00    	Value of GPIO_27 if in IN mode
68	        N/A     	N/A
69	        N/A     	N/A
70	        0xFF       	Value of GPIO_0 if in OUT mode
71	        0xFF    	Value of GPIO_1 if in OUT mode
72	        0xFF    	Value of GPIO_2 if in OUT mode
73	        0xFF    	Value of GPIO_3 if in OUT mode
74	        0xFF    	Value of GPIO_4 if in OUT mode
75  	    0xFF	    Value of GPIO_5 if in OUT mode
76	        0xFF    	Value of GPIO_6 if in OUT mode
77	        0xFF    	Value of GPIO_7 if in OUT mode
78	        0xFF    	Value of GPIO_8 if in OUT mode
79	        0xFF    	Value of GPIO_9 if in OUT mode
80	        0xFF    	Value of GPIO_10 if in OUT mode
81	        0xFF    	Value of GPIO_11 if in OUT mode
82	        0xFF    	Value of GPIO_12 if in OUT mode
83	        0xFF    	Value of GPIO_13 if in OUT mode
84	        0xFF    	Value of GPIO_14 if in OUT mode
85	        0xFF    	Value of GPIO_15 if in OUT mode
86	        0xFF    	Value of GPIO_16 if in OUT mode
87  	    0xFF    	Value of GPIO_17 if in OUT mode
88	        0xFF    	Value of GPIO_18 if in OUT mode
89	        0xFF    	Value of GPIO_19 if in OUT mode
90	        0xFF    	Value of GPIO_20 if in OUT mode
91	        0xFF    	Value of GPIO_21 if in OUT mode
92      	0xFF	    Value of GPIO_22 if in OUT mode
93	        0xFF    	Value of GPIO_23 if in OUT mode
94	        0xFF    	Value of GPIO_24 if in OUT mode
95	        1       	Value of GPIO_25 if in OUT mode
96	        0xFF    	Value of GPIO_26 if in OUT mode
97	        0xFF    	Value of GPIO_27 if in OUT mode


# note

In code, data is visible in the logs of python script (master.py).

Value 1 is represented by true and 0 by false


# Environment requirements

Please make sure you have the following packages :

cmake : sudo apt install cmake
pymodbus : pip3 install pymodbus
(recommended) minicom : sudo apt install minicom

Test screens in test.md file
