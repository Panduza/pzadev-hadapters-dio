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

# CONGIRURATION
## PIN configuration

| GPIO | Description     |
| ---- | --------------- |
| 0    | input pull down |
| 1    | input pull down |
| 2    | input pull down |
| 3    | input pull down |
| 4    | not an IO       |
| 5    | not an IO       |
| 6    | input pull down |
| 7    | input pull down |
| 8    | input pull down |
| 9    | input pull down |
| 10   | input pull down |
| 11   | input pull down |
| 12   | input pull down |
| 13   | input pull down |
| 14   | input pull down |
| 15   | input pull down |
| 16   | input pull down |
| 17   | input pull down |
| 18   | input pull down |
| 19   | input pull down |
| 20   | input pull down |
| 21   | input pull down |
| 22   | input pull down |
| 23   | not an IO       |
| 24   | not an IO       |
| 25   | INTERNAL LED    |
| 26   | input pull down |
| 27   | input pull down |

## MODBUS HOLDING REGISTER AFFECTATION
| Register | Initial value | Description                                                            |
| :------: | :-----------: | :--------------------------------------------------------------------- |
|    0     |      PZ       |                                                                        |
|    1     |      A!       |                                                                        |
|    2     |     0x01      |                                                                        |
|    3     |      24       | Number of GPIO configured                                              |
|    4     |      N/A      |                                                                        |
|    5     |      N/A      |                                                                        |
|    6     |      N/A      |                                                                        |
|    7     |      N/A      |                                                                        |
|    8     |      N/A      |                                                                        |
|    9     |      N/A      |                                                                        |
|    10    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    11    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    12    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    13    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    14    |     0xFF      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    15    |     0xFF      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    16    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    17    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    18    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    19    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    20    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    21    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    22    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    23    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    24    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    25    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    26    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    27    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    28    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    29    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    30    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    31    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    32    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    33    |     0xFF      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    34    |     0xFF      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    35    |     0xFF      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    36    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    37    |     0x02      | IN_pull_up(0x01) or IN_pull_down(0x02) or OUT(0xFF) or not an IO(0xFF) |
|    38    |      N/A      |                                                                        |

## COIL AFFECTATION
| COIL | Bit | Default value | Description      |
| :--: | :-: | :-----------: | :--------------- |
|  0   |  0  |       0       | Value of GPIO_0  |
|      |  1  |       0       | Value of GPIO_1  |
|      |  2  |       0       | Value of GPIO_2  |
|      |  3  |       0       | Value of GPIO_3  |
|      |  4  |       0       | Value of GPIO_4  |
|      |  5  |       0       | Value of GPIO_5  |
|      |  6  |       0       | Value of GPIO_6  |
|      |  7  |       0       | Value of GPIO_7  |
|  1   |  0  |       0       | Value of GPIO_8  |
|      |  1  |       0       | Value of GPIO_9  |
|      |  2  |       0       | Value of GPIO_10 |
|      |  3  |       0       | Value of GPIO_11 |
|      |  4  |       0       | Value of GPIO_12 |
|      |  5  |       0       | Value of GPIO_13 |
|      |  6  |       0       | Value of GPIO_14 |
|      |  7  |       0       | Value of GPIO_15 |
|  2   |  0  |       0       | Value of GPIO_16 |
|      |  1  |       0       | Value of GPIO_17 |
|      |  2  |       0       | Value of GPIO_18 |
|      |  3  |       0       | Value of GPIO_19 |
|      |  4  |       0       | Value of GPIO_20 |
|      |  5  |       0       | Value of GPIO_21 |
|      |  6  |       0       | Value of GPIO_22 |
|      |  7  |       0       | Value of GPIO_23 |
|  3   |  0  |       0       | Value of GPIO_24 |
|      |  1  |       1       | Value of GPIO_25 |
|      |  2  |       0       | Value of GPIO_26 |
|      |  3  |       0       | Value of GPIO_27 |
|      |  4  |       0       | N/A              |
|      |  5  |       0       | N/A              |
|      |  6  |       0       | N/A              |
|      |  7  |       1       | N/A              |

# note

In code, data is visible in the logs of python script (master.py).

Value 1 is represented by true and 0 by false


# Environment requirements

Please make sure you have the following packages :

cmake : sudo apt install cmake
pymodbus : pip3 install pymodbus
(recommended) minicom : sudo apt install minicom

Test screens in test.md file
