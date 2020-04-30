/*
Receive Node for CAN bus architecture done on Arduino Mega.

TODO:
-Figure out dropped frames, something to do with termination resistor?

https://protosupplies.com/product/mcp2515-can-bus-interface-module/
*/

#include <SPI.h>
#include <mcp_can.h>

MCP_CAN CAN(10);

unsigned char len = 0; // length of received buffer
unsigned char buf[8]; // 8 byte buffer
unsigned int canID; // CAN Message ID
double tempFactor = 0.02;

// Try to initialize CAN at 500k
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

void loop()
{
    if (CAN.checkReceive() == 3) { // 3 Means CAN_MSGAVAIL
        CAN.readMsgBuf(&len, buf); // len: data length, buf: data buffer
        canID = CAN.getCanId();

        Serial.print("CAN ID: ");
        Serial.print(canID, HEX);

        Serial.print("  Data Length: ");
        Serial.print(len);
        Serial.print("  ");

        // Print the data one byte at a time
        for (int i = 0; i<len; i++) {
            Serial.print(int(buf[i]));
            if(i<(len-1)) Serial.print(",");
        }
        Serial.println();

        double tempData = 0x0000; // zero out the data
        tempData = (double)(((buf[2] & 0x007F) << 8) + buf[1]);
        tempData = (tempData * tempFactor) - 0.01;
        float celcius = tempData - 273.15;
        Serial.print("Celcius Default: ");
        Serial.println(celcius);
    }
    else {
        // Serial.println("No Message");
        // delay(10000);
    }
}