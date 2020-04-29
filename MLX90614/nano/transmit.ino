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

MCP_CAN CAN(10);
byte data[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup()
{
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN Initialization Failed, you failure");
        Serial.println("Trying again because you suck so hard...");
        delay(2000);
    }
    Serial.println("CAN Shield Initialized");
}

// Try to initialize CAN at 500k
void loop()
{
    // TODO: Actually read sensor data
    for (byte val = 0; val <=247; val++) {
        data[0] = val;
        data[1] = val + 1;
        data[2] = val + 2;
        data[3] = val + 3;
        data[4] = val + 4;
        data[5] = val + 5;
        data[6] = val + 6;
        data[7]= val + 7;

        // CAN.sendMsgBuf(msg ID, standard frame, # of data bytes, data array)
        CAN.sendMsgBuf(0x01, 0, 8, data);
        delay(500);
    }
}