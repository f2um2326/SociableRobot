/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
/* Dynamixel ID defines */
#define BASE_ID 1
#define PEDUNCLE_ID 17  // 花柄
#define RACHIS_ID 4    // 花軸

/* Control table defines */
#define GOAL_SPEED 32
#define GOAL_POSITION 30

#define NATURAL_SPEED 100  // as botany

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
  //Dxl.setPosition(BASE_ID, 150, 300);
  //Dxl.setPosition(PEDUNCLE_ID, 0, 300);
  //Dxl.setPosition(RACHIS_ID, 512, 300);
  //delay(1000);// it has more delay time for slow movement
}

void loop() {  
  /* hide */
  //Dxl.setPosition(BASE_ID, 300, NATURAL_SPEED);
  //Dxl.setPosition(PEDUNCLE_ID, 412, NATURAL_SPEED);
  //Dxl.setPosition(RACHIS_ID, 300, NATURAL_SPEED);
  //delay(2000);
  
  /* see */
  //Dxl.setPosition(BASE_ID, 0, NATURAL_SPEED);
  //Dxl.setPosition(PEDUNCLE_ID, 512, NATURAL_SPEED);
  //Dxl.setPosition(RACHIS_ID, 0, NATURAL_SPEED);
  //delay(2000);// it has more delay time for slow movement
  
  if(SpeedID == 'a') {
    digitalWrite(BOARD_LED_PIN, HIGH); // set to as HIGH LED is turn-off
    delay(100);          // Wait for 0.1 second
    digitalWrite(BOARD_LED_PIN, LOW);  // set to as LOW LED is turn-on
    delay(100);          // Wait for 0.1 second
  }
  if(SpeedID == 'b') {
    digitalWrite(BOARD_LED_PIN, HIGH); // set to as HIGH LED is turn-off
    delay(500);          // Wait for 0.1 second
    digitalWrite(BOARD_LED_PIN, LOW);  // set to as LOW LED is turn-on
    delay(500);          // Wait for 0.1 second
  }
  if(SpeedID == 'c') {
    digitalWrite(BOARD_LED_PIN, HIGH); // set to as HIGH LED is turn-off
    delay(1000);          // Wait for 0.1 second
    digitalWrite(BOARD_LED_PIN, LOW);  // set to as LOW LED is turn-on
    delay(1000);          // Wait for 0.1 second
  }
  if(SpeedID == 'd') {
    digitalWrite(BOARD_LED_PIN, HIGH); // set to as HIGH LED is turn-off
    delay(1500);          // Wait for 0.1 second
    digitalWrite(BOARD_LED_PIN, LOW);  // set to as LOW LED is turn-on
    delay(1500);          // Wait for 0.1 second
  }
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
