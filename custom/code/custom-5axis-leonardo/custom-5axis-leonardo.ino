#define StepPin1  8
#define StepPin2  9
#define StepPin3  10
#define StepPin4  11
#define StepPin5  12

#define DirPin1   4
#define DirPin2   5
#define DirPin3   6
#define DirPin4   7
#define DirPin5   3

#define RelayPin  A0

#define pulseDelay 2
#define directionDelay 4

byte buffer = 0;
byte buffercount = 0;
byte commandbuffer[10] = {0};

unsigned m1Target = 0, m2Target = 0, m3Target = 0, m4Target = 0, m5Target = 0;
unsigned m1Position = 0, m2Position = 0, m3Position = 0, m4Position = 0, m5Position = 0;

int dir1 = -1, dir2 = -1, dir3 = -1, dir4 = -1, dir5 = -1;
byte dirChange = 0;
bool servoEnabled = false;

void setup() {
  Serial.begin(921600);

  pinMode(RelayPin, OUTPUT);
  disableServo();

  pinMode(StepPin1, OUTPUT);
  pinMode(StepPin2, OUTPUT);
  pinMode(StepPin3, OUTPUT);
  pinMode(StepPin4, OUTPUT);
  pinMode(StepPin5, OUTPUT);

  pinMode(DirPin1, OUTPUT);
  pinMode(DirPin2, OUTPUT);
  pinMode(DirPin3, OUTPUT);
  pinMode(DirPin4, OUTPUT);
  pinMode(DirPin5, OUTPUT);

  digitalWrite(DirPin1, HIGH);
  digitalWrite(DirPin2, HIGH);
  digitalWrite(DirPin3, HIGH);
  digitalWrite(DirPin4, HIGH);
  digitalWrite(DirPin5, HIGH);
}

void loop() {
  SerialReader();
  moveMotor();
}

void SerialReader() {
  while (Serial.available()) {
    if (buffercount == 0) {
      buffer = Serial.read();
      if (buffer != 'T') {
        if (buffer == 'A') { enableServo(); }
        if (buffer == 'C') { disableServo(); }
        buffercount = 0;
      } else {
        buffercount = 1;
      }
    } else {
      buffer = Serial.read();
      commandbuffer[buffercount - 1] = buffer;
      buffercount++;
      if (buffercount >= 11) {
        m1Target = commandbuffer[0] * 256 + commandbuffer[1];
        m2Target = commandbuffer[2] * 256 + commandbuffer[3];
        m3Target = commandbuffer[4] * 256 + commandbuffer[5];
        m4Target = commandbuffer[6] * 256 + commandbuffer[7];
        m5Target = commandbuffer[8] * 256 + commandbuffer[9];
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
  if ((m1Target > m1Position) && (dir1 == -1)) {
    PORTD &= ~(1 << 4);
    dir1 = 1;
    dirChange = 1;
  }
  if ((m1Target < m1Position) && (dir1 == 1)) {
    PORTD |= (1 << 4);
    dir1 = -1;
    dirChange = 1;
  }

  if ((m2Target > m2Position) && (dir2 == -1)) {
    PORTC &= ~(1 << 6);
    dir2 = 1;
    dirChange = 1;
  }
  if ((m2Target < m2Position) && (dir2 == 1)) {
    PORTC |= (1 << 6);
    dir2 = -1;
    dirChange = 1;
  }

  if ((m3Target > m3Position) && (dir3 == -1)) {
    PORTD &= ~(1 << 7);
    dir3 = 1;
    dirChange = 1;
  }
  if ((m3Target < m3Position) && (dir3 == 1)) {
    PORTD |= (1 << 7);
    dir3 = -1;
    dirChange = 1;
  }

  if ((m4Target > m4Position) && (dir4 == -1)) {
    PORTE &= ~(1 << 6);
    dir4 = 1;
    dirChange = 1;
  }
  if ((m4Target < m4Position) && (dir4 == 1)) {
    PORTE |= (1 << 6);
    dir4 = -1;
    dirChange = 1;
  }

  if ((m5Target > m5Position) && (dir5 == -1)) {
    PORTD &= ~(1 << 0);
    dir5 = 1;
    dirChange = 1;
  }
  if ((m5Target < m5Position) && (dir5 == 1)) {
    PORTD |= (1 << 0);
    dir5 = -1;
    dirChange = 1;
  }

  if (dirChange == 1) {
    delayMicroseconds(directionDelay);
    dirChange = 0;
  }
}

void singleStep() {
  byte portbPulse = 0;
  byte portdPulse = 0;

  if (m1Target != m1Position) {
    portbPulse |= (1 << 4);
    m1Position += dir1;
  }
  if (m2Target != m2Position) {
    portbPulse |= (1 << 5);
    m2Position += dir2;
  }
  if (m3Target != m3Position) {
    portbPulse |= (1 << 6);
    m3Position += dir3;
  }
  if (m4Target != m4Position) {
    portbPulse |= (1 << 7);
    m4Position += dir4;
  }
  if (m5Target != m5Position) {
    portdPulse |= (1 << 6);
    m5Position += dir5;
  }

  if (portbPulse == 0 && portdPulse == 0) return;

  if (portbPulse) PORTB |= portbPulse;
  if (portdPulse) PORTD |= portdPulse;

  delayMicroseconds(pulseDelay);

  if (portbPulse) PORTB &= ~(0xF0);
  if (portdPulse) PORTD &= ~(1 << 6);
}

void enableServo() {
  digitalWrite(RelayPin, LOW);
  servoEnabled = true;
}

void disableServo() {
  digitalWrite(RelayPin, HIGH);
  servoEnabled = false;
}
