#include <EasyScheduler.h>
#include "pitches.h"

#define melodyPin 10

int photo_sensor_value = 0;
int step_count = 0;
int DO = 1; //Pin for Digital Output - DO
int DA = A1; // Pin for Analog Output - AO
int threshold = 50; //Set minimum threshold for LED lit
int sound_sensor_value = 0;

// create Task
Schedular Task1;
Schedular Task2;
Schedular Task3;

// Jingle Bells Song

int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

int tempo[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};

// We wish you a merry Christmas Song

int wish_melody[] = {
  NOTE_B3,
  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_E4,
  NOTE_F4
};

int wish_tempo[] = {
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
};

// Santa Claus is coming to town Song

int santa_melody[] = {
  NOTE_G4,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
  NOTE_D4, NOTE_F4, NOTE_B3,
  NOTE_C4
};

int santa_tempo[] = {
  8,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 2,
  4, 4, 4, 4,
  4, 2, 4,
  1
};

int button = 0;
int button1 = 11;
int button2 = 12;
int button3 = 13;


void setup() {
  //set up pin as input for Photoresister sensor
  pinMode(A0, INPUT);

  //set up pin as input for Stepper Motor
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);


  Serial.begin(9600); //Enable Serial Communication

  //seting up pins as outputs for LEDs
  for (int i = 6; i <= 9; i++)
    pinMode(i, OUTPUT);

  //seting up pins as inputs and output for Sound
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(10, OUTPUT); // Buzzer

  Task1.start(); // start Task
  Task2.start();
  Task3.start();
}

void loop() {
//  button = random(1,3);
//
//  switch (button) {
//    case 0:
//    while(button == 1) {
//      digitalWrite(button1, HIGH);
//      sing(1);
//      break;
//    }
//
//    case 1:
//    while(button == 2) {
//      digitalWrite(button2, HIGH);
//      sing(2);
//      break;
//    }
//
//    case 2:
//    while(button == 3) {
//      digitalWrite(button3, HIGH);
//      sing(3);
//      break;
//    }
//  }
  button1 = digitalRead(11);
  button2 = digitalRead(12);
  button3 = digitalRead(13);
  if (button1 == HIGH) {
    sing(1);
  } else if (button2 == HIGH) {
    sing(2);
  } else if (button3 == HIGH) {
    sing(3);
  }
  Task1.check(photo_value, 1000);
  Task2.check(sound, 5000);
  Task3.check(sing, 12000);
  Task1.timesToRun = 2;
  Task2.timesToRun = 1;
  Task3.timesToRun = 1;
}

void photo_value() {
  photo_sensor_value = analogRead(A0);
    Serial.println(photo_sensor_value);
    delay(1000);

  if(photo_sensor_value < 990)
  {

    for (int j = 0; j < 500; j++) {
      OneStep(false);
      delay(5);
    }
    for (int j = 0; j < 500; j++) {
      OneStep(true);
      delay(5);
    }
  }
}

void sound() {
  sound_sensor_value = analogRead(DA);  //Read the analog value
  Serial.print("Analog: ");
  Serial.print(sound_sensor_value);  //Print the analog value
  Serial.print("  ");
  Serial.print("Digital: ");
  Serial.println(digitalRead(DO));  //Print the digital value
  if (sound_sensor_value >= threshold) { //Compare analog value with threshold
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);

  }
  else {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
}


void OneStep(bool drt) {
  if (drt) {
    switch (step_count) {
      case 0:
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        break;

      case 1:
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        break;

      case 2:
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        break;

      case 3:
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        break;
    }
  }
  else {
    switch (step_count) {
      case 0:
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        break;

      case 1:
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        break;

      case 2:
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        break;

      case 3:
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
    }
  }
  //incrementing step_count value
  step_count++;
  //if it is bigger than should set it to 0
  if (step_count > 3) {
    step_count = 0;
  }
  //delay when change the speed (for this motor 0.002 second is the smallest)
  //    delay(2);
}

int song = 0;

void sing(int s) {  
  // iterate over the notes of the melody:
  song = s;
  if (song == 3) {
    Serial.println(" 'We wish you a Merry Christmas'");
    int size = sizeof(wish_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / wish_tempo[thisNote];

      buzz(melodyPin, wish_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }
  } else if (song == 2) {
    Serial.println(" 'Santa Claus is coming to town'");
    int size = sizeof(santa_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 900 / santa_tempo[thisNote];

      buzz(melodyPin, santa_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }
  } else {

    Serial.println(" 'Jingle Bells'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];

      buzz(melodyPin, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }
  }
}


void buzz(int targetPin, long frequency, long length) {
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  
}
