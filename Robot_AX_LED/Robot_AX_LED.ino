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

int NaturalSpeed = 100;  // as botany

int ASpeed = 400;
int BSpeed = 300;
int CSpeed = 200;
int DSpeed = 100;

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
  Dxl.setPosition(BASE_ID, 150, 300);
  Dxl.setPosition(PEDUNCLE_ID, 0, 300);
  Dxl.setPosition(RACHIS_ID, 512, 300);
  delay(1000);// it has more delay time for slow movement
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
    Dxl.setPosition(BASE_ID, 300, ASpeed);
    Dxl.setPosition(PEDUNCLE_ID, 412, ASpeed);
    Dxl.setPosition(RACHIS_ID, 300, ASpeed);
    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(5000);
  
    Dxl.setPosition(BASE_ID, 0, ASpeed);
    Dxl.setPosition(PEDUNCLE_ID, 512, ASpeed);
    Dxl.setPosition(RACHIS_ID, 0, ASpeed);
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(5000);// it has more delay time for slow movement
  }
  if(SpeedID == 'b') {
    Dxl.setPosition(BASE_ID, 300, BSpeed);
    Dxl.setPosition(PEDUNCLE_ID, 412, BSpeed);
    Dxl.setPosition(RACHIS_ID, 300, BSpeed);
    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(10000);
  
    Dxl.setPosition(BASE_ID, 0, BSpeed);
    Dxl.setPosition(PEDUNCLE_ID, 512, BSpeed);
    Dxl.setPosition(RACHIS_ID, 0, BSpeed);
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(10000);// it has more delay time for slow movement
  }
  if(SpeedID == 'c') {
    Dxl.setPosition(BASE_ID, 300, CSpeed);
    Dxl.setPosition(PEDUNCLE_ID, 412, CSpeed);
    Dxl.setPosition(RACHIS_ID, 300, CSpeed);
    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(15000);
  
    Dxl.setPosition(BASE_ID, 0, CSpeed);
    Dxl.setPosition(PEDUNCLE_ID, 512, CSpeed);
    Dxl.setPosition(RACHIS_ID, 0, CSpeed);
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(15000);// it has more delay time for slow movement
  }
  if(SpeedID == 'd') {
    Dxl.setPosition(BASE_ID, 300, DSpeed);
    Dxl.setPosition(PEDUNCLE_ID, 412, DSpeed);
    Dxl.setPosition(RACHIS_ID, 300, DSpeed);
    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(20000);
  
    Dxl.setPosition(BASE_ID, 0, DSpeed);
    Dxl.setPosition(PEDUNCLE_ID, 512, DSpeed);
    Dxl.setPosition(RACHIS_ID, 0, DSpeed);
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(20000);// it has more delay time for slow movement
  }
}

void usbInterrupt(byte* buffer, byte nCount){
  SpeedID = (int)buffer[0];
  if( 'a' <= SpeedID && SpeedID == 'd' ) {
    NaturalSpeed = ((int)buffer[1]-48) * 1000;
    NaturalSpeed += ((int)buffer[2]-48) * 100;
    NaturalSpeed += ((int)buffer[3]-48) * 10;
    NaturalSpeed += ((int)buffer[4]-48);
  } 
}
