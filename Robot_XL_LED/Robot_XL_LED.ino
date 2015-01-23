/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
/* Dynamixel ID defines */
#define RPETAL_ID 1
#define LPETAL_ID 2

/* Control table defines */
#define GOAL_SPEED 32
#define GOAL_POSITION 30

int NaturalSpeed = 100;  // as botany

double DxSpeed = 300;
int SpeedID = 'a';

int ASpeed = 400;
int BSpeed = 300;
int CSpeed = 200;
int DSpeed = 100;

Dynamixel Dxl(DXL_BUS_SERIAL1);

void setup() {
  SerialUSB.begin();
  SerialUSB.attachInterrupt(usbInterrupt);
  Serial3.begin(96000);  // for send data to 2nd // or 128000
  
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);
  Dxl.jointMode(RPETAL_ID); //jointMode() is to use position mode
  Dxl.jointMode(LPETAL_ID);
  
  // Initial position
  Dxl.setPosition(RPETAL_ID, 390, 300);
  Dxl.setPosition(LPETAL_ID, 365, 300);
  delay(1000);// it has more delay time for slow movement
}

void loop() {  
  /*ID 1 dynamixel moves to position 0 with velocity 100 */
  //Dxl.setPosition(RPETAL_ID, 525, 100);
  //Dxl.setPosition(LPETAL_ID, 500, 100);
  //delay(2000);// it has more delay time for slow movement
  /*ID 1 dynamixel moves to position 500 with velocity 300 */
  //Dxl.setPosition(RPETAL_ID, 390, 100);
  //Dxl.setPosition(LPETAL_ID, 365, 100);
  //delay(2000);            
  if(SpeedID == 'a') {
    Dxl.setPosition(RPETAL_ID, 525, ASpeed);
    Dxl.setPosition(LPETAL_ID, 500, ASpeed);
    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(5000);          // Wait for 0.1 second
    Dxl.setPosition(RPETAL_ID, 390, ASpeed);
    Dxl.setPosition(LPETAL_ID, 365, ASpeed);
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(5000);          // Wait for 0.1 second
  }
  if(SpeedID == 'b') {
    Dxl.setPosition(RPETAL_ID, 525, BSpeed);
    Dxl.setPosition(LPETAL_ID, 500, BSpeed);
    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(10000);          // Wait for 0.1 second
    Dxl.setPosition(RPETAL_ID, 390, BSpeed);
    Dxl.setPosition(LPETAL_ID, 365, BSpeed);
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(10000);          // Wait for 0.1 second
  }
  if(SpeedID == 'c') {
    Dxl.setPosition(RPETAL_ID, 525, CSpeed);
    Dxl.setPosition(LPETAL_ID, 500, CSpeed);
    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(15000);          // Wait for 0.1 second
    Dxl.setPosition(RPETAL_ID, 390, CSpeed);
    Dxl.setPosition(LPETAL_ID, 365, CSpeed);
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(15000);          // Wait for 0.1 second
  }
  if(SpeedID == 'd') {
    Dxl.setPosition(RPETAL_ID, 525, DSpeed);
    Dxl.setPosition(LPETAL_ID, 500, DSpeed);
    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(20000);          // Wait for 0.1 second
    Dxl.setPosition(RPETAL_ID, 390, DSpeed);
    Dxl.setPosition(LPETAL_ID, 365, DSpeed);
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(20000);          // Wait for 0.1 second
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
