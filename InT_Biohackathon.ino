
// pin for the buzzer
const int buzzerPin = 10;


// pin for the LDR sensor
const int ldrSensorPin = A0;


// threshold value for disturbance detection, 200 is an arbituary value!!
const int disturbanceThreshold = 200;


// variables to track disturbances
int disturbanceCount = 0;
int hourCount = 0;


// variables for controlling sound playback
bool playingSound = false;
unsigned long soundStart = 0;


// variables for timing
const int hoursInNight = 8;
const int nights = 5;
const unsigned long hourDuration = 3600000; // 1 hour in milliseconds



void setup() {
  pinMode(buzzerPin, OUTPUT);
}


// will run continuously
void loop() {

  // detects and track sleep disturbances
  if (detectDisturbance()) {
    disturbanceCount++;


    // checks if more than 2 disturbances occurred within same hour
    if (disturbanceCount > 4 && !playingSound) {
      // Start playing sound
      playingSound = true;
      soundStart = millis();
      playSound();
    }
  }


  // check if time to stop playing sound
  if (playingSound && (millis() - soundStart >= hoursToMillis(hoursInNight))) {
    stopSound();
    disturbanceCount = 0; // resets disturbance count
    hourCount++;


    // checks if 5 nights have passed
    if (hourCount >= nights * hoursInNight) {
      // program complete


      while (true) {
        // does nothing
      }
    }
  }
}


// function detects sleep disturbances
bool detectDisturbance() {


  // reads the sensor value
  int sensorValue = analogRead(ldrSensorPin);


  // checks if the sensor value exceeds the disturbance threshold
  if (sensorValue > disturbanceThreshold) {
    return true;  // when disturbance detected
    } 
  

  else {
    return false; // when no disturbance detected
    }
}



// function to play 40 Hz sound
void playSound() {
  tone(buzzerPin, 40); 
}


// function to stop playing sound
void stopSound() {
  noTone(buzzerPin);
}


// helper function to convert hours to milliseconds
unsigned long hoursToMillis(int hours) {
  return hours * hourDuration;
  }














