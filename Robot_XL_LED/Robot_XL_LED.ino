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
  Dxl.jointMode(RPETAL_ID); //jointMode() is to use position mode
  Dxl.jointMode(LPETAL_ID);
  
  // Initial position
  //Dxl.setPosition(RPETAL_ID, 390, 300);
  //Dxl.setPosition(LPETAL_ID, 365, 300);
  //delay(1000);// it has more delay time for slow movement
}

void loop() {  
  /*ID 1 dynamixel moves to position 0 with velocity 100 */
  //Dxl.setPosition(RPETAL_ID, 525, 100);
  //Dxl.setPosition(RPETAL_ID, 500, 100);
  //delay(2000);// it has more delay time for slow movement
  /*ID 1 dynamixel moves to position 500 with velocity 300 */
  //Dxl.setPosition(RPETAL_ID, 390, 100);
  //Dxl.setPosition(RPETAL_ID, 365, 100);
  //delay(2000);            
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
