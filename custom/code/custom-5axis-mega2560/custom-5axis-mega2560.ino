// 
// www.lebois-racing.fr/en
// 아두이노 메가(Mega) 전용 - 레지스터 직접 구동 코드
// 5축(5 actuators) 제어를 위한 최적화 버전
// Simhub / FlyPT와 호환

// 핀 할당 (직접 포트 조작을 위한 Mega 핀아웃)
// 방향 핀 (DIR)은 PORTA 사용
#define DirPin1   22 // PORTA 비트 0 (PA0)
#define DirPin2   23 // PORTA 비트 1 (PA1)
#define DirPin3   24 // PORTA 비트 2 (PA2)
#define DirPin4   25 // PORTA 비트 3 (PA3)
#define DirPin5   26 // PORTA 비트 4 (PA4)

// 스텝 핀 (STEP)은 PORTC 사용
#define StepPin1  30 // PORTC 비트 7 (PC7)
#define StepPin2  31 // PORTC 비트 6 (PC6)
#define StepPin3  32 // PORTC 비트 5 (PC5)
#define StepPin4  33 // PORTC 비트 4 (PC4)
#define StepPin5  34 // PORTC 비트 3 (PC3)

#define RelayPin  A0 // 릴레이를 통해 파워서플라이(PSU)를 제어합니다.

#define pulseDelay 2      // 액추에이터 속도 설정. 낮을수록 빠릅니다. (2 미만 금지)
#define directionDelay 4

byte buffer           = 0 ;
byte buffercount      = 0 ;
byte commandbuffer[10] = {0}; // 5개 모터 * 2바이트/모터 = 10바이트
unsigned m1Target = 0,   m2Target = 0,   m3Target = 0,   m4Target = 0,   m5Target = 0;
unsigned m1Position = 0, m2Position = 0, m3Position = 0, m4Position = 0, m5Position = 0;
// PORTC의 해당 스텝 비트 위치에 맞게 펄스 값 정의
byte pulseM1 = B10000000, pulseM2 = B01000000, pulseM3 = B00100000, pulseM4 = B00010000, pulseM5 = B00001000;
int  dir1 = -1, dir2 = -1, dir3 = -1, dir4 = -1, dir5 = -1;
byte dirChange = 0;
bool noData = true;
bool servoEnabled = false;

void setup() {
  Serial.begin(921600);    // FlyPT와의 통신 속도

  // 릴레이 핀 설정 및 비활성화
  pinMode(RelayPin, OUTPUT);
  disableServo();

  // 1. 방향 핀(Direction pins) 설정: PORTA (Mega 핀 D22-D26)
  DDRA = DDRA | B00011111;  // PA0-PA4 (비트 0~4)를 OUTPUT으로 설정.
  PORTA |= B00011111;      // PA0-PA4를 HIGH로 설정합니다. (초기 방향)

  // 2. 스텝 핀(Step pins) 설정: PORTC (Mega 핀 D30-D34)
  DDRC = DDRC | B11111000;  // PC3-PC7 (비트 3~7)을 OUTPUT으로 설정합니다.
}

void loop() {
  SerialReader();
  moveMotor();
}

void SerialReader() {       
  while (Serial.available())
  {
    if (buffercount == 0)
    {
      buffer = Serial.read();
      if (buffer != 'T') { 
        if(buffer =='A'){enableServo();}
        if(buffer =='C'){disableServo();}     
                      
        buffercount = 0;
      } else {
        buffercount = 1;
      }
    }
    else
    {
      buffer = Serial.read();
      commandbuffer[buffercount-1] = buffer; 
      buffercount++;
      if (buffercount >= 11) { // 1 마커 + 5 모터 * 2바이트/모터 = 총 11바이트
          m1Target = ((uint16_t)commandbuffer[0] << 8) | commandbuffer[1];
          m2Target = ((uint16_t)commandbuffer[2] << 8) | commandbuffer[3];
          m3Target = ((uint16_t)commandbuffer[4] << 8) | commandbuffer[5];
          m4Target = ((uint16_t)commandbuffer[6] << 8) | commandbuffer[7];
          m5Target = ((uint16_t)commandbuffer[8] << 8) | commandbuffer[9];
          buffercount = 0;
        break;
      }
    }
  }
}

void moveMotor() {
  directionManager(); 
  singleStep();
}

void directionManager() { 
// PORTA는 DirPin1 (PA0)부터 DirPin5 (PA4)까지 제어합니다.

  // M1 (PA0 - Bit 0)
  if ((m1Target > m1Position) && (dir1 == -1)) {
    PORTA &= B11111110; // PA0를 LOW로 설정
    dir1 = 1;
    dirChange = 1;
  }
  if ((m1Target < m1Position ) && (dir1 == 1)) {
    PORTA |= B00000001; // PA0를 HIGH로 설정
    dir1 = -1;
    dirChange = 1;
  }

  // M2 (PA1 - Bit 1)
  if ((m2Target > m2Position) && (dir2 == -1)) {
    PORTA &= B11111101; // PA1를 LOW로 설정
    dir2 = 1;
    dirChange = 1;
  }
  if ((m2Target < m2Position ) && (dir2 == 1)) {
    PORTA |= B00000010; // PA1를 HIGH로 설정
    dir2 = -1;
    dirChange = 1;
  }

  // M3 (PA2 - Bit 2)
  if ((m3Target > m3Position) && (dir3 == -1)) {
    PORTA &= B11111011; // PA2를 LOW로 설정
    dir3 = 1;
    dirChange = 1;
  }
  if ((m3Target < m3Position ) && (dir3 == 1)) {
    PORTA |= B00000100; // PA2를 HIGH로 설정
    dir3 = -1;
    dirChange = 1;
  }

  // M4 (PA3 - Bit 3)
  if ((m4Target > m4Position) && (dir4 == -1)) {
    PORTA &= B11110111; // PA3를 LOW로 설정
    dir4 = 1;
    dirChange = 1;
  }
  if ((m4Target < m4Position ) && (dir4 == 1)) {
    PORTA |= B00001000; // PA3를 HIGH로 설정
    dir4 = -1;
    dirChange = 1;
  }
  
  // M5 (PA4 - Bit 4)
  if ((m5Target > m5Position) && (dir5 == -1)) {
    PORTA &= B11101111; // PA4를 LOW로 설정
    dir5 = 1;
    dirChange = 1;
  }
  if ((m5Target < m5Position ) && (dir5 == 1)) {
    PORTA |= B00010000; // PA4를 HIGH로 설정
    dir5 = -1;
    dirChange = 1;
  }
  
  if (dirChange == 1) {
    delayMicroseconds(directionDelay);
    dirChange = 0;
  }
}

void singleStep() {
  // 펄스는 StepPin1 (PC7)부터 StepPin5 (PC3)까지입니다.
  byte activePulses = 0;
  
  if (m1Target != m1Position) {
    activePulses |= pulseM1; // PC7
    m1Position += dir1;
  }
  
  if (m2Target != m2Position) {
    activePulses |= pulseM2; // PC6
    m2Position += dir2;
  }
    
  if (m3Target != m3Position) {
    activePulses |= pulseM3; // PC5
    m3Position += dir3;
  }

  if (m4Target != m4Position) {
    activePulses |= pulseM4; // PC4
    m4Position += dir4;
  }
  
  if (m5Target != m5Position) {
    activePulses |= pulseM5; // PC3
    m5Position += dir5;
  }
    
  if(activePulses == 0){return;}

  // 1. HIGH 펄스를 발생시킵니다. (5개 펄스 동시 발생)
  PORTC |= activePulses; 
  delayMicroseconds(pulseDelay);

  // 2. 펄스를 CLEAR (LOW) 합니다. (5개 펄스 동시 초기화)
  PORTC &= B00000111; 
}

void enableServo(){
    digitalWrite(RelayPin, LOW);
    servoEnabled=true;
}
void disableServo(){
    digitalWrite(RelayPin, HIGH);
    servoEnabled=false;
}