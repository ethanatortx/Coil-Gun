int photoResVoltageTotal, photoResVoltageCurrent, photoResVoltageThreshold, cPin = 1;
const double thresholdSens = 0.5;

void setup() {
  // 8 output pins to control relay switching
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  // activate serial for debug read out
  Serial.begin(9600);

  photoResVoltageTotal = analogRead(1); // read in total voltage from photo resistors
  photoResVoltageThreshold = photoResVoltageTotal - (photoResVoltageTotal * thresholdSens); // store threshold voltage
}

// detect and cycle relay up one if payload has moved forwards
void cycleUp(int a, int b)
{
  if( a < b ) // power current interval if there is a payload in the system
  {
    digitalWrite(cPin, HIGH);
  }
  else if (digitalRead(cPin) == HIGH) // toggle off power if payload is past current interval
  {
    digitalWrite(cPin, LOW);
    ++cPin; // increment interval position
  }
}

void loop() {
  // read current voltage
  photoResVoltageCurrent = analogRead(1);
  
  cycleUp(photoResVoltageCurrent, photoResVoltageThreshold);

  // sample delay
  delay(10);
}
