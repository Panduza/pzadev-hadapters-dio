# verify PICO_SDK_PATH is not set

This may take some time..

export "PICO_SDK_PATH"="" -> not set SDK path

echo "$PICO_SDK_PATH" -> check it's not set

# build and run project

mkdir build

cd build

cmake ..

make

cp file_name.uf2 /media/user_name/RPI-RP2/


# Notes

GPIO's 4 and 5 not used due to conflit probability with the uart line


# PIN configuration

| GPIO | value | description |  returned value |
|----- |-------|-------------|-----------------|
|  0   |   1    |      input pull up       |      0x1           | 
|  1   |   0    |    output         |   0x0              |
|  2   |   0    |   input pull down          |    0x2             |
|  3   |  1     |    output         |     0x0            | 
|  6   |   1    |    input pull up         |    0x1             |
|  7   |   0    |    output         |   0x0              |
|  8   |   0   |      output       |    0x0             | 
|  9   |   0    |     input pull down        |     0x2            |
|  10   |  1     |    output         |      0x0           |
|  11   |   1    |    input pull up         |    0x1             | 
|  12  |   0    |    output         |    0x0             |
|  13   |  0     |    input pull down         |    0x2             |
|  14   |  1     |   output          |        0x0         | 
|  15   |  1     |   input pull up          |  0x1               |
|  16   |  0     |   output          |      0x0           |
|  17   |  0     |   input pull down          |   0x2              | 
|  18   |  1     |   output          |      0x0           |
|  19   |  1     |   input pull up          |  0x1               |
|  20   |  0     |   output          |     0x0            | 
|  21   |  0     |   input pull down          |  0x2               |
|  22   |  1     |    output         |     0x0            |
|  25 (INTERNAL LED)  | 1     |    output         |   0x0             | 
|  26   |     1  |   input pull up          |      0x1           |
|  27   |   1    |   output          |    0x0             |
|  28   |   0    |     output        |     0x0            | 



# note

In code, data is visible in the logs of python script (master.py).

Value 1 is represented by true and 0 by false


# Environment requirements

Please make sure you have the following packages :

cmake : sudo apt install cmake
pymodbus : pip3 install pymodbus
(recommended) minicom : sudo apt install minicom
