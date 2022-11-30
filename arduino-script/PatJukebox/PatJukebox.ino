/*
  Esplora Music

  This sketch turns the Esplora in a simple musical instrument.
  Press the Switch 1 and move the slider to see how it works.

  Created on 22 november 2012
  By Enrico Gueli <enrico.gueli@gmail.com>
  modified 22 Dec 2012
  by Tom Igoe
*/


#include <Esplora.h>

// add inputs for all buttons
// add percussion loops
// use slider to switch chord key 
// use buttons to play notes in key
// receive mic input (and add reverb to it)

int arpeggiator = 0;

// these are the frequencies for the notes from middle C
// to one octave above middle C:
const int note[] = {
  262, // C
  277, // C#
  294, // D
  311, // D#
  330, // E
  349, // F
  370, // F#
  392, // G
  415, // G#
  440, // A
  466, // A#
  494, // B
  523  // C next octave
};

void setup() {
}

void loop() {

  int tempo = Esplora.readSlider();
  
  //melody(tempo);

  drumLoop();

  getMic(tempo);

  //bassLine(arpeggiator);

  int arpInc = 10;
  if (arpeggiator < (4*arpInc))
  {
    arpeggiator += arpInc;
  }
  if (arpeggiator >= (4*arpInc))
  {
    arpeggiator = 0;
  }

}

void melody(int tempo)
{
  delay(tempo);

  int xValue = Esplora.readJoystickX();        // read the joystick's X position

  int yValue = Esplora.readJoystickY();        // read the joystick's Y position

  if (xValue != 0 || yValue != 0)
  {
    byte melodyNote = map(xValue, 0, yValue, 0, 13); 
    // play the note corresponding to the slider's position:
    Esplora.tone(note[melodyNote]);
  }
  else
  {
    Esplora.noTone();
  }
}

// use slider to control pitch of bass line
void bassLine(int arpeggiator)
{
  int slider = Esplora.readSlider();

  if (slider > 0)
  {
    // use map() to map the slider's range to the
    // range of notes you have:
    byte thisNote = map((slider - 60) + arpeggiator, 0, 1023, 0, 255);
    // play the note corresponding to the slider's position:
    //Esplora.tone(note[thisNote]);
  }
  else
  {
    Esplora.noTone();
  }

}

void drumLoop()
{
  // click joystick to clear drum loop
  float loopDuration = 4.0f;
  
  // mess w values later to make each drum diff
  byte upNote = map(0, 0, 1023, 0, 13);
  byte leftNote = map(50, 0, 1023, 0, 13);
  byte rightNote = map(75, 0, 1023, 0, 13);
  byte downNote = map(100, 0, 1023, 0, 13);

  #pragma region AddDrumsToLoop
  // press buttons to add drums to loop
  if (Esplora.readButton(SWITCH_UP) == LOW) {
    Esplora.tone(note[upNote]);
  }
  else if (Esplora.readButton(SWITCH_LEFT) == LOW) {
    Esplora.tone(note[leftNote]);
  }
  else if (Esplora.readButton(SWITCH_RIGHT) == LOW) {
    Esplora.tone(note[rightNote]);
  }
  else if (Esplora.readButton(SWITCH_DOWN) == LOW) {
    Esplora.tone(note[downNote]);
  }
  #pragma endregion AddDrumsToLoop

  int joystickClick = Esplora.readJoystickSwitch();   

}

void getMic(int tempo)
{
  delay(tempo);

  // read mic sound
  int loudness = Esplora.readMicrophone();
  int soundDeadZone = 1;

  // map the sound level to a brightness level for the LED:
  int brightness = map(loudness, 0, 1023, 0, 255);
  // write the brightness to the green LED:
  Esplora.writeGreen(brightness);

  // print the microphone levels and the LED levels (to see what's going on):
  Serial.print("sound level: " + loudness);
  Serial.print(" Green brightness: " + brightness); // frequency of mic sound

  // play sound if mic reads a loud enough sound
  if (loudness > soundDeadZone)
  {
    byte voiceBack = map(brightness, 0, 1023, 0, 13);
    Esplora.tone(note[voiceBack]);
  }
  else
  {
    Esplora.noTone();
  }

}
