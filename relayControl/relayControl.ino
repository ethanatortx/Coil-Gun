int photoResVolt[8];
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

  for(int i = 0; i < 8; ++i)
  { photoResVolt[i] = analogRead(i+1);
    photoResVolt[i] -= photoResVolt[i] * thresholdSens; }
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < 8; ++i)
  {
    if(analogRead(i+1) < photoResVolt[i] && digitalRead(i+1) != HIGH){
      digitalWrite(i+1, HIGH);
      Serial.println("Coil ");
      Serial.print(i+1);
      Serial.print(" active");
    }
    else if(digitalRead(i+1) == HIGH)
      digitalWrite(i+1, LOW);
  }
}

