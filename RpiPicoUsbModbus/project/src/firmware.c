// include config file

#include "../inc/conf.h"

// prototype functions
void init(const uint led_used);
void printErrorInfo(ModbusErrorInfo err);
void printAndSendFrameResponse(ModbusErrorInfo err, const ModbusSlave *slave);
void determinFunctionCodeError (char *responseLib);
const uint8_t getGpioType(const uint16_t pin);

// callback prototypes
ModbusError registerCallback(const ModbusSlave *slaveID,const ModbusRegisterCallbackArgs *args,ModbusRegisterCallbackResult *result);
ModbusError exceptionCallback(const ModbusSlave *slave,  uint8_t function, ModbusExceptionCode code);


int main() {

    int i_get=0;
    uint8_t receiveBuffer[255];
    uint8_t single;
    
    stdio_init_all();
    uart_init(UART_ID, BAUDRATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    ModbusSlave slave;
    ModbusErrorInfo error;


    debug("begining of program..\r\n");


    error = modbusSlaveInit(&slave, registerCallback, exceptionCallback, modbusDefaultAllocator, modbusSlaveDefaultFunctions, modbusSlaveDefaultFunctionCount);
    if(!modbusIsOk(error))
        debug("modbusSlaveInit() failed!\n\r");


    single = getchar();
    while(1){
        
        i_get=0;
        debug("Reading hex data from stdin...\n\r");
        while ((single = getchar()) != EOF) {
            // debug("inside.\r\n"); 
            // debug("processing \r\n");
            receiveBuffer[i_get] = single;
            error = modbusParseRequestRTU(&slave, 0x01, receiveBuffer, i_get+1);
            if(modbusIsOk(error)){
               // debug("break\r\n");
                break;
                i_get=0;
            }/*else{
                debug("checking the data... \r\n");
                char strDebug[250];
                sprintf(strDebug, "value of i %d, value of single %.2X value of buffer %.2X value of modbus check %d \r\n", i_get, single, receiveBuffer[i_get], modbusIsOk(error));
                debug(strDebug);
                debug("test \r\n");
            }*/
            i_get++;
        }

        printErrorInfo(error);
        if(modbusIsOk(error)){
            printAndSendFrameResponse(error, &slave);
        }
    }

      return 0;
}


void printAndSendFrameResponse(ModbusErrorInfo err , const ModbusSlave *slave){

    for(int i = 0; i<modbusSlaveGetResponseLength(slave); i++) {
        printf("%c", modbusSlaveGetResponse(slave)[i]);
    }
}


/*
* goes in this callback when a frame is received
*/
ModbusError registerCallback(const ModbusSlave *slaveID,const ModbusRegisterCallbackArgs *args,ModbusRegisterCallbackResult *result){
        
    int dir;
    bool pulls;

    gpio_init(GPIO_0);
    gpio_set_dir(GPIO_0, GPIO_IN);
    gpio_pull_up(GPIO_0);
    
    gpio_init(GPIO_1);
    gpio_set_dir(GPIO_1, GPIO_OUT);
    gpio_put(GPIO_1, 0);

    gpio_init(GPIO_2);
    gpio_set_dir(GPIO_2, GPIO_IN);
    gpio_pull_down(GPIO_2);

    gpio_init(GPIO_3);
    gpio_set_dir(GPIO_3, GPIO_OUT);
    gpio_put(GPIO_3, 1);

    gpio_init(GPIO_6);
    gpio_set_dir(GPIO_6, GPIO_IN);
    gpio_pull_up(GPIO_6);

    gpio_init(GPIO_7);
    gpio_set_dir(GPIO_7, GPIO_OUT);
    gpio_put(GPIO_7, 0);

    gpio_init(GPIO_8);
    gpio_set_dir(GPIO_8, GPIO_OUT);
    gpio_put(GPIO_8, 0);
    
    gpio_init(GPIO_9);
    gpio_set_dir(GPIO_9, GPIO_IN);
    gpio_pull_down(GPIO_9);

    gpio_init(GPIO_10);
    gpio_set_dir(GPIO_10, GPIO_OUT);
    gpio_put(GPIO_10, 1);
    
    gpio_init(GPIO_11);
    gpio_set_dir(GPIO_11, GPIO_IN);
    gpio_pull_up(GPIO_11);

    gpio_init(GPIO_12);
    gpio_set_dir(GPIO_12, GPIO_OUT);
    gpio_put(GPIO_12, 0);

    gpio_init(GPIO_13);
    gpio_set_dir(GPIO_13, GPIO_IN);
    gpio_pull_down(GPIO_13);
   
    gpio_init(GPIO_14);
    gpio_set_dir(GPIO_14, GPIO_OUT);
    gpio_put(GPIO_14, 1);
     
    gpio_init(GPIO_15);
    gpio_set_dir(GPIO_15, GPIO_IN);
    gpio_pull_up(GPIO_15);
    
    gpio_init(GPIO_16);
    gpio_set_dir(GPIO_16, GPIO_OUT);
    gpio_put(GPIO_16, 0);

    gpio_init(GPIO_17);
    gpio_set_dir(GPIO_17, GPIO_IN);
    gpio_pull_down(GPIO_17);

    gpio_init(GPIO_18);
    gpio_set_dir(GPIO_18, GPIO_OUT);
    gpio_put(GPIO_18, 1);

    gpio_init(GPIO_19);
    gpio_set_dir(GPIO_19, GPIO_IN);
    gpio_pull_up(GPIO_19);

    gpio_init(GPIO_20);
    gpio_set_dir(GPIO_20, GPIO_OUT);
    gpio_put(GPIO_20, 0);

    gpio_init(GPIO_21);
    gpio_set_dir(GPIO_21, GPIO_IN);
    gpio_pull_down(GPIO_21);

    gpio_init(GPIO_22);
    gpio_set_dir(GPIO_22, GPIO_OUT);
    gpio_put(GPIO_22, 1);
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    gpio_init(GPIO_26);
    gpio_set_dir(GPIO_26, GPIO_IN);
    gpio_pull_up(GPIO_26);
    
    gpio_init(GPIO_27);
    gpio_set_dir(GPIO_27, GPIO_OUT);
    gpio_put(GPIO_27, 1);

    gpio_init(GPIO_28);
    gpio_set_dir(GPIO_28, GPIO_IN);
    gpio_pull_down(GPIO_28);


    char str[1024];
    sprintf(str,"Register query:\r\ntquery: %s\r\n type: %s\r\n  @: %d\r\nvalue: %c\r\n  fun: %d\r\n",
        modbusRegisterQueryStr(args->query),
        modbusDataTypeStr(args->type),
		args->index,
		args->value,
		args->function
	);
    debug(str);

    debug("inside callback\n\r");
    switch (args->query)
    {
        // R/W access check
        case MODBUS_REGQ_R_CHECK:
        case MODBUS_REGQ_W_CHECK:
            result->exceptionCode = args->index < REG_COUNT ? MODBUS_EXCEP_NONE : MODBUS_EXCEP_ILLEGAL_ADDRESS;
            break;
 
        // Read register        
        case MODBUS_REGQ_R:
            switch (args->type)
            {
                case MODBUS_HOLDING_REGISTER: 
                    switch (args->index) // get data from HOLDING REGISTERS
                    {
                        // get PZA! address 0 and 1
                        case 0:
                            result->value = 'PZ'; break;                    
                        case 1: 
                           result->value = 'A!' ; break; 
                        case 2: result->value = 0x01; break; // get mode
                        case 3: result->value = 0x1A; break; // get number of I/O
                        // get more info about I/O's (Input, output, pull up, pull down)
                        case 10 + GPIO_0:
                            dir = gpio_get_dir(GPIO_0);
                            pulls = gpio_is_pulled_up(GPIO_0);
                            if(dir == GPIO_IN){
                                if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                    result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_1 :
                            dir = gpio_get_dir(GPIO_1);
                            pulls = gpio_is_pulled_up(GPIO_1);
                            if(dir == GPIO_IN){
                                if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                                
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_2 : 
                            dir = gpio_get_dir(GPIO_2);
                            pulls = gpio_is_pulled_up(GPIO_2);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_3 : 
                            dir = gpio_get_dir(GPIO_3);
                            pulls = gpio_is_pulled_up(GPIO_3);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_6: 
                            dir = gpio_get_dir(GPIO_6);
                            pulls = gpio_is_pulled_up(GPIO_6);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_7 : 
                            dir = gpio_get_dir(GPIO_7);
                            pulls = gpio_is_pulled_up(GPIO_7);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_8 : 
                            dir = gpio_get_dir(GPIO_8);
                            pulls = gpio_is_pulled_up(GPIO_8);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_9 : 
                            dir = gpio_get_dir(GPIO_9);
                            pulls = gpio_is_pulled_up(GPIO_9);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_10 : 
                            dir = gpio_get_dir(GPIO_10);
                            pulls = gpio_is_pulled_up(GPIO_10);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_11 : 
                            dir = gpio_get_dir(GPIO_11);
                            pulls = gpio_is_pulled_up(GPIO_11);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_12 : 
                            dir = gpio_get_dir(GPIO_12);
                            pulls = gpio_is_pulled_up(GPIO_12);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_13 : 
                            dir = gpio_get_dir(GPIO_13);
                            pulls = gpio_is_pulled_up(GPIO_13);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_14 : 
                            dir = gpio_get_dir(GPIO_14);
                            pulls = gpio_is_pulled_up(GPIO_14);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_15 : 
                            dir = gpio_get_dir(GPIO_15);
                            pulls = gpio_is_pulled_up(GPIO_15);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_16 : 
                            dir = gpio_get_dir(GPIO_16);
                            pulls = gpio_is_pulled_up(GPIO_16);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_17 : 
                            dir = gpio_get_dir(GPIO_17);
                            pulls = gpio_is_pulled_up(GPIO_17);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_18 : 
                            dir = gpio_get_dir(GPIO_18);
                            pulls = gpio_is_pulled_up(GPIO_18);
                            if(dir == GPIO_IN){
                                if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                    result->value=0x02; break;
                                } else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                        case 10 + GPIO_19 : 
                            dir = gpio_get_dir(GPIO_19);
                            pulls = gpio_is_pulled_up(GPIO_19);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                            case 10 + GPIO_20 : 
                            dir = gpio_get_dir(GPIO_20);
                            pulls = gpio_is_pulled_up(GPIO_20);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                            case 10 + GPIO_21 : 
                            dir = gpio_get_dir(GPIO_21);
                            pulls = gpio_is_pulled_up(GPIO_21);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                            case 10 + GPIO_22 : 
                            dir = gpio_get_dir(GPIO_22);
                            pulls = gpio_is_pulled_up(GPIO_22);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                            case 10 + LED_PIN : 
                            dir = gpio_get_dir(LED_PIN);
                            pulls = gpio_is_pulled_up(LED_PIN);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                            case 10 + GPIO_26 : 
                            dir = gpio_get_dir(GPIO_26);
                            pulls = gpio_is_pulled_up(GPIO_26);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                            case 10 + GPIO_27 : 
                            dir = gpio_get_dir(GPIO_27);
                            pulls = gpio_is_pulled_up(GPIO_27);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            }
                            case 10 + GPIO_28 : 
                            dir = gpio_get_dir(GPIO_28);
                            pulls = gpio_is_pulled_up(GPIO_28);
                            if(dir == GPIO_IN){
                            if(pulls){
                                    result->value=0x01; break;
                                } else if(!pulls){
                                   result->value=0x02; break;
                                }else{
                                    result->value=0x03; break;
                                }
                            } else if(dir == GPIO_OUT){
                                result->value=0x00; break;
                            } 
                    }
                    break;
                case MODBUS_INPUT_REGISTER:   result->value = inputRegisters[args->index]; break;
                //case MODBUS_COIL:             result->value = modbusMaskRead(coils, args->index); break;
                case MODBUS_COIL:
                debug("inside coil case\r\n");
                char str1[100];
                sprintf(str1, "GPIO number %d\r\n", args->index);
                debug(str1);
                    switch (args->index) // get value of GPIO's 
                    {
                        case 0: result->value = gpio_get(GPIO_0); break;
                        case 1: result->value = gpio_get(GPIO_1); break; 
                        case 2: result->value = gpio_get(GPIO_2); break; 
                        case 3: result->value = gpio_get(GPIO_3); break;
                        case 6: result->value = gpio_get(GPIO_6); break;  
                        case 7: result->value = gpio_get(GPIO_7); break; 
                        case 8: result->value = gpio_get(GPIO_8); break; 
                        case 9: result->value = gpio_get(GPIO_9); break; 
                        case 10: result->value = gpio_get(GPIO_10); break; 
                        case 11: result->value = gpio_get(GPIO_11); break; 
                        case 12: result->value = gpio_get(GPIO_12); break; 
                        case 13: result->value = gpio_get(GPIO_13); break; 
                        case 14: result->value = gpio_get(GPIO_14); break; 
                        case 15: result->value = gpio_get(GPIO_15); break; 
                        case 16: result->value = gpio_get(GPIO_16); break; 
                        case 17: result->value = gpio_get(GPIO_17); break; 
                        case 18: result->value = gpio_get(GPIO_18); break; 
                        case 19: result->value = gpio_get(GPIO_19); break; 
                        case 20: result->value = gpio_get(GPIO_20); break; 
                        case 21: result->value = gpio_get(GPIO_21); break; 
                        case 22: result->value = gpio_get(GPIO_22); break; 
                        case 26: result->value = gpio_get(GPIO_26); break; 
                        case 27: result->value = gpio_get(GPIO_27); break; 
                        case 28: result->value = gpio_get(GPIO_28); break;
                        default:
                            debug("problem with address\r\n"); 
                    }
                    break;
                 case MODBUS_DISCRETE_INPUT:   result->value = modbusMaskRead(discreteInputs, args->index); break;
            }
            break;
 
        // Write register
        case MODBUS_REGQ_W:
            switch (args->type)
            {
                case MODBUS_HOLDING_REGISTER: registers[args->index] = args->value; break;
                case MODBUS_COIL:             modbusMaskWrite(coils, args->index, args->value); break;
                default:                      break;
            }
            break;
    }
    return MODBUS_OK;

}
	

ModbusError exceptionCallback(const ModbusSlave *slave,  uint8_t function, ModbusExceptionCode code){
    char exceptionInfo[15];
    debug("in error register callback\r\n");
    debug(modbusExceptionCodeStr(code)); // send the error cause to the debug
	return MODBUS_OK;

}

/*
* check if modbus is initialized
*/
void printErrorInfo(ModbusErrorInfo err)
{
	if (modbusIsOk(err)){
		debug("FRAME IS SEND TO THE LIB \r\n");
  
    }else{
        debug("THERE IS A PROBLEM WITH THE INIT OF\r\n");
		debug(modbusErrorSourceStr(modbusGetErrorSource(err)));
		debug(modbusErrorStr(modbusGetErrorCode(err)));
    }
}

