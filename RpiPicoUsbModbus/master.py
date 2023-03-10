from pymodbus.client import ModbusSerialClient
from pymodbus.transaction import ModbusRtuFramer
import time
import logging

FORMAT = ('%(message)-15s')
logging.basicConfig(format=FORMAT)
log = logging.getLogger()
log.setLevel(logging.DEBUG)


master = ModbusSerialClient(framer=ModbusRtuFramer, port = '/dev/ttyACM0', stopbits=1, bytesize=8, parity='N', baudrate=115200)
SLAVE_ID = 0x01



connexion = master.connect()
print(master)
# print("\033[92m-------------------client connected----------------------\033[0m")


# print("\033[92m-------------------getting PZA----------------------\033[0m")
# getMagic = master.read_holding_registers(0, 2, SLAVE_ID)
# print(getMagic.__dict__)
# print("\033[92m-------------------getting mode----------------------\033[0m")
# getMode = master.read_holding_registers(2, 1, SLAVE_ID)
# print(getMode.__dict__)
# print("\033[92m-------------------getting number of I/O----------------------\033[0m")
# getIO = master.read_holding_registers(3, 1, SLAVE_ID)
# print(getIO.__dict__)


print("\033[92m-------------------GET THE TYPES----------------------\033[0m")

# GPIO 0 to 3
for i in range(4):
    print(f"\033[92m-------------------getting type GPIO {i} ----------------------\033[0m")
    getType0 = master.read_holding_registers(10+i, 1, SLAVE_ID)
    print("\033[92m value of register \033[0m",getType0.registers)

# GPIO 6 to 22
for i in range(17):
    print(f"\033[92m-------------------getting type GPIO {i+6} ----------------------\033[0m")
    getType6 = master.read_holding_registers(16+i, 1, SLAVE_ID)
    print("\033[92m value of register \033[0m",getType6.registers)

# GPIO 25 to 28
for i in range(4):
    print(f"\033[92m-------------------getting type GPIO {i+25} ----------------------\033[0m")
    getType6 = master.read_holding_registers(35+i, 1, SLAVE_ID)
    print("\033[92m value of register \033[0m",getType6.registers)


# print("\033[92m-------------------READ COILS !!!!!!----------------------\033[0m")

# GPIO 0 to 3
for i in range(4):
    print(f"\033[92m-------------------I/O {i}----------------------\033[0m")
    getIO_0 = master.read_coils(i, 1, SLAVE_ID)
    print("\033[92m value of coil \033[0m", getIO_0.bits[0])

# GPIO 6 to to 22
for i in range(17):
    print(f"\033[92m-------------------I/O {i+6}----------------------\033[0m")
    getIO_0 = master.read_coils(i+6, 1, SLAVE_ID)
    print("\033[92m value of coil \033[0m", getIO_0.bits[0])


# GPIO 25 to 28
for i in range(4):
    print(f"\033[92m-------------------I/O {i+25}----------------------\033[0m")
    getIO_0 = master.read_coils(i+25, 1, SLAVE_ID)
    print("\033[92m value of coil \033[0m", getIO_0.bits[0])
