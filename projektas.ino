const int buttonCount = 8;
const int buttonPins[buttonCount] = {2, 3, 4, 5, 6, 7, 8, 9};
bool buttonState[buttonCount];
bool lastButtonState[buttonCount];
unsigned long lastDebounceTime[buttonCount];
unsigned long debounceDelay = 50;
const int mygtukoPin = 9;  
const int isejimoPin = 10;  
int ankstesneReiksme = 0;  
int dabartineReiksme = 0;  
void setup() {
  Serial.begin(9600);
   pinMode(9, INPUT);
 pinMode(10, OUTPUT);
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT);
    lastDebounceTime[i] = 0;
  }
}
void loop() {
    digitalWrite(10,HIGH);
  for (int i = 0; i < buttonCount; i++) {
    int reading = digitalRead(buttonPins[i]);
    if (reading != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
    }
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (reading != buttonState[i]) {
        buttonState[i] = reading;
        if (buttonState[i] == LOW) {
          if (i == 0) {            
            Serial.write('A');
          } else if (i == 1) {
            Serial.write('B');
          } else if (i == 2) {
            Serial.write('C');
          } else if (i == 3) {
            Serial.write('D');
          } else if (i == 4) {
            Serial.write('E');
          } else if (i == 5) {
            Serial.write('F');
          } else if (i == 6) {
            Serial.write('G');
          } else if (i == 7) {
            Serial.write('H');
          }         
        }
      }
    }
    lastButtonState[i] = reading;
  }
  
}
