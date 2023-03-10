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
|  0   |       |             |                 | 
|  1   |       |             |                 |
|  2   |       |             |                 |
|  3   |       |             |                 | 
|  6   |       |             |                 |
|  7   |       |             |                 |
|  8   |       |             |                 | 
|  9   |       |             |                 |
|  10   |       |             |                 |
|  11   |       |             |                 | 
|  12  |       |             |                 |
|  13   |       |             |                 |
|  14   |       |             |                 | 
|  15   |       |             |                 |
|  16   |       |             |                 |
|  17   |       |             |                 | 
|  18   |       |             |                 |
|  19   |       |             |                 |
|  20   |       |             |                 | 
|  21   |       |             |                 |
|  22   |       |             |                 |
|  25   |       |             |                 | 
|  26   |       |             |                 |
|  27   |       |             |                 |
|  28   |       |             |                 | 

