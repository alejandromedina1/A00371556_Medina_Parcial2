// C++ code
//
const int BTN_PIN = 2;
const int BUZZ_PIN = 3;
const int myLEDs [5] = {4, 5, 6, 7, 8};
const int HUM_SENSOR_PIN = A0;

bool alertState = false;

int humidityValue = 0;
int mappedHumidityValue = 0;

void setup()
{
  pinMode(BTN_PIN, INPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  
  for(int i = 0; i < 5; i++){
  pinMode(myLEDs[i], OUTPUT);
  }
  
  pinMode(HUM_SENSOR_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  humidityMeter();
  Serial.println(humidityValue);
  dryAlert();
  overDriedAlert();
  turnOffAlert();
}

void humidityMeter(){
  humidityValue = analogRead(HUM_SENSOR_PIN);
  mappedHumidityValue = map(humidityValue, 0, 142, 0, 4);
  
  for(int i = 0; i < 5; i++){
    
  if (mappedHumidityValue >= i) {
  digitalWrite(myLEDs[i], HIGH);
  } else {
  digitalWrite(myLEDs[i], LOW);
  }
  } 
}

void dryAlert() {
  if (mappedHumidityValue == 0) {
  tone(BUZZ_PIN, 5000, 1000);
    delay(2000);
  }else {
    noTone(BUZZ_PIN);
  }
}

void overDriedAlert(){
  if (mappedHumidityValue == 4) {
  alertState = true;
  }else{
  alertState = false;
  }
  
  if(alertState) {
  tone(BUZZ_PIN, 5000, 1000);
  } else {
  noTone(BUZZ_PIN);
  }
}

void turnOffAlert(){
  if(alertState && digitalRead(BTN_PIN) == true){
    alertState = false;
    delay(5000);
  }
}
