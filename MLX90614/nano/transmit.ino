/*
Transmit node transmit data from nano to mega.

TODO:
- Read sensor data
- Read data from three sensors
- Send sensor data 
https://protosupplies.com/product/mcp2515-can-bus-interface-module/
*/

#include <SPI.h>
#include <mcp_can.h>
#include <i2cmaster.h>

MCP_CAN CAN(10);
byte data[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup()
{
    Serial.begin(115200);
    Serial.println("Setup...");

    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN Initialization Failed, you failure");
        Serial.println("Trying again because you suck so hard...");
        delay(2000);
    }
    Serial.println("CAN Shield Initialized");

    i2c_init();
    PORTC = (1 << PORTC4) | (1 << PORTC5);
    Serial.println("i2c Initialized");
}

// Try to initialize CAN at 500k
void loop()
{
    int data_low = 0;
    int data_high = 0;
    int pec = 0;

    int dev = 0x4A << 1; // address location
    i2c_start_wait(dev + I2C_WRITE);
    i2c_write(0x07); // RAM location of Tobj1

    i2c_rep_start(dev + I2C_READ);
    data_low = i2c_readAck();
    data_high = i2c_readAck();
    pec = i2c_readNak();
    i2c_stop();

    // TODO: Actually read sensor data
    data[0] = (byte)dev;
    data[1] = (byte)data_low;
    data[2] = (byte)data_high;
    data[3] = (byte)pec;
    data[4] = 0x00;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x00;

    // CAN.sendMsgBuf(msg ID, standard frame, # of data bytes, data array)
    CAN.sendMsgBuf(0x01, 0, 8, data);
    delay(500);
}