/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
/* Dynamixel ID defines */
#define BASE_ID 16
#define PEDUNCLE_ID 17  // 花柄
#define RACHIS_ID 4    // 花軸

/* Control table defines */
#define GOAL_SPEED 32
#define GOAL_POSITION 30

#define NATURAL_SPEED 1  // as botany

double DxSpeed = 300;
int SpeedID = 'a';

Dynamixel Dxl(DXL_BUS_SERIAL1);

void setup() {
  SerialUSB.begin();
  SerialUSB.attachInterrupt(usbInterrupt);
  Serial3.begin(96000);  // for send data to 2nd // or 128000
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);
  Dxl.jointMode(BASE_ID); //jointMode() is to use position mode
  Dxl.jointMode(PEDUNCLE_ID);
  Dxl.jointMode(RACHIS_ID);
  
  // Initial position
  Dxl.setPosition(BASE_ID, 200, 20);  //150
  Dxl.setPosition(PEDUNCLE_ID, 462, 20);  //0
  Dxl.setPosition(RACHIS_ID, 400, 20);  //512
  delay(5000);// it has more delay time for slow movement
}

void loop() {  
  /* hide */
  Dxl.setPosition(BASE_ID, 50, NATURAL_SPEED);
  Dxl.setPosition(PEDUNCLE_ID, 100, NATURAL_SPEED);
  Dxl.setPosition(RACHIS_ID, 512, NATURAL_SPEED);
  delay(20000);
}

void usbInterrupt(byte* buffer, byte nCount){
  SpeedID = (int)buffer[0];
  if( 'a' <= SpeedID && SpeedID == 'd' ) {
    DxSpeed = ((int)buffer[1]-48) * 1000;
    DxSpeed += ((int)buffer[2]-48) * 100;
    DxSpeed += ((int)buffer[3]-48) * 10;
    DxSpeed += ((int)buffer[4]-48);
  } 
}
