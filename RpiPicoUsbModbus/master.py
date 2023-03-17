from pymodbus.client import ModbusSerialClient
from pymodbus.transaction import ModbusRtuFramer
import logging

FORMAT = ('%(message)-15s')
logging.basicConfig(format=FORMAT)
log = logging.getLogger()
log.setLevel(logging.WARNING)


master = ModbusSerialClient(framer=ModbusRtuFramer, port = '/dev/ttyACM0', stopbits=1, bytesize=8, parity='N', baudrate=115200)
SLAVE_ADRESS = 0x01 


connexion = master.connect()
print(master)
# print("\033[92m-------------------client connected----------------------\033[0m")


# print("\033[92m-------------------getting PZA----------------------\033[0m")
# getMagic = master.read_holding_registers(0, 2, SLAVE_ADRESS)
# print(getMagic.__dict__)
# print("\033[92m-------------------getting mode----------------------\033[0m")
# getMode = master.read_holding_registers(2, 1, SLAVE_ADRESS)
# print(f"\033[92m there are in mode {getMode.registers[0]}, in I/O mode \033[0m")
# print("\033[92m-------------------getting number of I/O----------------------\033[0m")
# getIO = master.read_holding_registers(3, 1, SLAVE_ADRESS)
# print(f"\033[92m there are {getIO.registers[0]} I/O's \033[0m")




# print("\033[92m-------------------GET THE TYPES----------------------\033[0m")

# # GPIO 0 to 3
# for i in range(4):
#     print(f"\033[92m-------------------getting type GPIO {i} ----------------------\033[0m")
#     getType0 = master.read_holding_registers(10+i, 1, SLAVE_ADRESS)
#     print("\033[92m value of register \033[0m",getType0.registers)
#     if getType0.registers[0] == 0:
#         print("\033[92m the I/O is a output \033[0m")
#     elif getType0.registers[0]  == 1:
#         print("\033[92m the I/O is a input pull up \033[0m")
#     else:
#         print("\033[92m the I/O is a input pull down \033[0m")

# # GPIO 6 to 22
# for i in range(17):
#     print(f"\033[92m-------------------getting type GPIO {i+6} ----------------------\033[0m")
#     getType0 = master.read_holding_registers(16+i, 1, SLAVE_ADRESS)
#     print("\033[92m value of register \033[0m",getType0.registers)
#     if getType0.registers[0]  == 0:
#         print("\033[92m the I/O is a output \033[0m")
#     elif getType0.registers[0]  == 1:
#         print("\033[92m the I/O is a input pull up \033[0m")
#     else:
#         print("\033[92m the I/O is a input pull down \033[0m")

# # GPIO 25 to 27
# for i in range(3):
#     print(f"\033[92m-------------------getting type GPIO {i+25} ----------------------\033[0m")
#     getType0 = master.read_holding_registers(35+i, 1, SLAVE_ADRESS)
#     print("\033[92m value of register \033[0m",getType0.registers)
#     if getType0.registers[0]  == 0:
#         print("\033[92m the I/O is a output \033[0m")
#     elif getType0.registers[0]  == 1:
#         print("\033[92m the I/O is a input pull up \033[0m")
#     else:
#         print("\033[92m the I/O is a input pull down \033[0m")


# print("\033[92m-------------------READ COILS !!!!!!----------------------\033[0m")

# # GPIO 0 to 3
# for i in range(4):
#     print(f"\033[92m-------------------I/O {i}----------------------\033[0m")
#     getIO_0 = master.read_coils(i, 1, SLAVE_ADRESS)
#     print("\033[91m DEBUG \033[0m", getIO_0.__dict__)
#     if getIO_0.bits[0] == False:
#         print("\033[92m value of coil is 0 \033[0m")
#     else:
#         print("\033[92m value of coil is 1 \033[0m")

# # GPIO 6 to to 22
# for i in range(17):
#     print(f"\033[92m-------------------I/O {i+6}----------------------\033[0m")
#     getIO_0 = master.read_coils(i+6, 1, SLAVE_ADRESS)
#     print("\033[91m DEBUG \033[0m", getIO_0.__dict__)
#     if getIO_0.bits[0] == False:
#         print("\033[92m value of coil is 0 \033[0m")
#     else:
#         print("\033[92m value of coil is 1 \033[0m")


# # GPIO 25 to 28
# for i in range(4):
#     print(f"\033[92m-------------------I/O {i+25}----------------------\033[0m")
#     getIO_0 = master.read_coils(i+25, 1, SLAVE_ADRESS)
#     print("\033[91m DEBUG \033[0m", getIO_0.__dict__)
#     if getIO_0.bits[0] == False:
#         print("\033[92m value of coil is 0 \033[0m")
#     else:
#         print("\033[92m value of coil is 1 \033[0m")

# print("\033[92m-------------------WRITE HOLDING REGISTERS !!!!!!----------------------\033[0m")
# getWOK = master.write_registers(100, 0x06, SLAVE_ADRESS)
# print("getWOK = ", getWOK)
# getROK = master.read_holding_registers(100, 1, SLAVE_ADRESS)
# print("getROK = ", getROK)
# print("Value of register = ", getROK.registers[0])

# print("\033[92m-------------------READ HOLDING REGISTERS !!!!!!----------------------\033[0m")
# for i in range(70,97):
#     getROK = master.read_holding_registers(i, 1, SLAVE_ADRESS)
#     # print("\n\rgetROK = ", getROK)
#     print("Value of register[", i, "] = ", getROK.registers[0])

print("-------------------GET THE TYPES----------------------")

# GPIO 0 to 28
for i in range(27):
    # print(f"-------------------getting type GPIO {i} ----------------------")
    getType0 = master.read_holding_registers(10+i, 1, SLAVE_ADRESS)
    # print(" value of register ",getType0.registers)
    if getType0.registers[0] == 0:
        print("The I/O ", i, " is an output ")
    elif getType0.registers[0]  == 1:
        print("The I/O ",i," is a input pull up ")
    elif getType0.registers[0]  == 2:
        print("The I/O ",i," is a input pull down ")
    elif getType0.registers[0]  == 255:
        print("The register : ", i, " does not correspond to an I/O ")
        
NUMBER_OF_IO = 28
print("-------------------READ INPUT STATE----------------------")
INPUT_OFFSET = 40
for i in range(INPUT_OFFSET,INPUT_OFFSET+NUMBER_OF_IO):
    getROK = master.read_holding_registers(i, 1, SLAVE_ADRESS)
    # print("\n\rgetROK = ", getROK)
    # print("Value of register[", i, "] = ", getROK.registers[0])
    if (getROK.registers[0] != 0 and getROK.registers[0] != 1) :
        print("The register : ", i-INPUT_OFFSET, " is not an Input ")
    else:
        print("State of the Input ", i-INPUT_OFFSET, " = ", getROK.registers[0])
        
print("-------------------READ OUTPUT STATE----------------------")
OUTPUT_OFFSET = 70
for i in range(OUTPUT_OFFSET,OUTPUT_OFFSET+NUMBER_OF_IO):
    getROK = master.read_holding_registers(i, 1, SLAVE_ADRESS)
    # print("\n\rgetROK = ", getROK)
    # print("Value of register[", i, "] = ", getROK.registers[0])
    if (getROK.registers[0] != 0 and getROK.registers[0] != 1) :
        print("The register : ", i-OUTPUT_OFFSET, " is not an Output ")
        if (i==25+OUTPUT_OFFSET):
            print(getROK.registers[0])
    else:
        print("State of the Output ", i-OUTPUT_OFFSET, " = ", getROK.registers[0])