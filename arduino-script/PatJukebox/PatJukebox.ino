/*
  Music Box
  using Arduino Esplora

  Original musical slider example provided by
  Enrico Gueli & Tom Igoe
*/

#include <Esplora.h>

// add inputs for all buttons
// add percussion loops
// use slider to switch chord key 
// use buttons to play notes in key
// receive mic input (and add reverb to it)

uint8_t arpeggiatorInput = 1;
uint8_t arpeggiatorOutput = 3;
uint8_t arpInc = 1;
uint8_t arpMax = 4*arpInc;
uint8_t zero = 0;

uint8_t var1 = 2;
uint8_t var2 = 0;

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
  Serial.begin(9600); // set up debug console
}

void loop() {
  int tempo = Esplora.readSlider();
  
  //melody(tempo);

  //drumLoop();

  //getMic(tempo);

  arpeggiatorInput = arpeggiatorOutput;

  //Serial.print(arpeggiatorInput);
  asm volatile(
    " arpLoop: "
    " add %[arpeggiatorInput], %[arpInc] \n\t" // increment arpeggiator by arpInc
    " cp %[arpMax], %[arpeggiatorInput] \n\t" // compare arpeggiator with max arpeggiator
    " brsh endLoop \n\t" // branch if same or higher
    " mov %[arpeggiatorInput], %[zero] \n\t" // resetting arpeggiator
    " endLoop: " // point for branch to jump to if skipping the arp reset
    " mov %[arpeggiatorOutput], %[arpeggiatorInput] \n\t" // set output to same as input
    : [arpeggiatorOutput] "=d" (arpeggiatorOutput) // output variables
    : [arpInc] "d" (arpInc), [arpMax] "d" (arpMax), [zero] "d" (zero), [arpeggiatorInput] "d" (arpeggiatorInput) // input variables
    : "r16"
  );

  /*
  asm volatile(
    " addLoop: "
    " mov r16, %[var1] \n\t"
    " add r16, %[var1] \n\t"
    " mov %[var2], r16 \n\t" 
    : [var2] "=d" (var2) // output variables
    : [var1] "d" (var1) // input variables
    : "r16" // clobbers
  );
  */

  delay(500);
  Serial.print(arpeggiatorOutput);
  delay(500);

  bassLine(arpeggiatorOutput);

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
