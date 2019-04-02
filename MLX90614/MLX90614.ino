#include <i2cmaster.h>


void setup() {
  Serial.begin(9600);
  Serial.println("Setup...");

  i2c_init(); //Initialise the i2c bus
  PORTC = (1 << PORTC4) | (1 << PORTC5);//enable pullups
}

void loop() {
  int dev_A = 0x2B << 1;
  int data_low = 0;
  int data_high = 0;
  int pec = 0;

  i2c_start_wait(dev_A + I2C_WRITE);
  i2c_write(0x07);

  // read
  i2c_rep_start(dev_A + I2C_READ);
  data_low = i2c_readAck(); //Read 1 byte and then send ack
  data_high = i2c_readAck(); //Read 1 byte and then send ack
  pec = i2c_readNak();
  i2c_stop();

  //This converts high and low bytes together and processes temperature, MSB is a error bit and is ignored for temps
  double tempFactor = 0.02; // 0.02 degrees per LSB (measurement resolution of the MLX90614)
  double tempData_A = 0x0000; // zero out the data
  int frac; // data past the decimal point

  // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
  tempData_A = (double)(((data_high & 0x007F) << 8) + data_low);
  tempData_A = (tempData_A * tempFactor) - 0.01;

  int dev = 0x55 << 1;

  i2c_start_wait(dev + I2C_WRITE);
  i2c_write(0x07);

  i2c_rep_start(dev + I2C_READ);
  data_low = i2c_readAck(); //Read 1 byte and then send ack
  data_high = i2c_readAck(); //Read 1 byte and then send ack
  pec = i2c_readNak();
  i2c_stop();

  double tempData = 0x0000; // zero out the data
  tempData = (double)(((data_high & 0x007F) << 8) + data_low);
  tempData = (tempData * tempFactor) - 0.01;

  float celcius = tempData - 273.15;
  float celcius_A = tempData_A - 273.15;

  Serial.print("Celcius Default: ");
  Serial.println(celcius);

  Serial.print("Celcius A: ");
  Serial.println(celcius_A);

  delay(1000); // wait a second before printing again
}
