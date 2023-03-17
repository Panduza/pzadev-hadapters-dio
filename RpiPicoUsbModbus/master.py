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


print("\033[92m-------------------getting PZA----------------------\033[0m")
getMagic = master.read_holding_registers(0, 2, SLAVE_ADRESS)
print(getMagic.__dict__)
print("\033[92m-------------------getting mode----------------------\033[0m")
getMode = master.read_holding_registers(2, 1, SLAVE_ADRESS)
print(f"\033[92m there are in mode {getMode.registers[0]}, in I/O mode \033[0m")
print("\033[92m-------------------getting number of I/O----------------------\033[0m")
getIO = master.read_holding_registers(3, 1, SLAVE_ADRESS)
print(f"\033[92m there are {getIO.registers[0]} I/O's \033[0m")




print("\033[92m-------------------GET THE TYPES----------------------\033[0m")

# GPIO 0 to 3
for i in range(4):
    print(f"\033[92m-------------------getting type GPIO {i} ----------------------\033[0m")
    getType0 = master.read_holding_registers(10+i, 1, SLAVE_ADRESS)
    print("\033[92m value of register \033[0m",getType0.registers)
    if getType0.registers[0] == 0:
        print("\033[92m the I/O is a output \033[0m")
    elif getType0.registers[0]  == 1:
        print("\033[92m the I/O is a input pull up \033[0m")
    else:
        print("\033[92m the I/O is a input pull down \033[0m")

# GPIO 6 to 22
for i in range(17):
    print(f"\033[92m-------------------getting type GPIO {i+6} ----------------------\033[0m")
    getType0 = master.read_holding_registers(16+i, 1, SLAVE_ADRESS)
    print("\033[92m value of register \033[0m",getType0.registers)
    if getType0.registers[0]  == 0:
        print("\033[92m the I/O is a output \033[0m")
    elif getType0.registers[0]  == 1:
        print("\033[92m the I/O is a input pull up \033[0m")
    else:
        print("\033[92m the I/O is a input pull down \033[0m")

# GPIO 25 to 27
for i in range(3):
    print(f"\033[92m-------------------getting type GPIO {i+25} ----------------------\033[0m")
    getType0 = master.read_holding_registers(35+i, 1, SLAVE_ADRESS)
    print("\033[92m value of register \033[0m",getType0.registers)
    if getType0.registers[0]  == 0:
        print("\033[92m the I/O is a output \033[0m")
    elif getType0.registers[0]  == 1:
        print("\033[92m the I/O is a input pull up \033[0m")
    else:
        print("\033[92m the I/O is a input pull down \033[0m")


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