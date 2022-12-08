/*
  Music Box
  using Arduino Esplora
  by Pat Fagan
  with help from Brian Hall

  Original musical slider and microphone examples provided by
  Enrico Gueli & Tom Igoe
  
*/

#include <Esplora.h>

uint8_t arpeggiatorInput = 1;
uint8_t arpeggiatorOutput = 3;
uint8_t arpInc = 1;
uint8_t arpMax = 4*arpInc;
uint8_t zero = 0;

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

  // adjust slider to change tempo (left for slower, right for faster)
  int tempo = Esplora.readSlider();
  delay(tempo);
  
  // calls the melody function, which uses the joystick to play notes
  melody();

  // calls the drum loop function, which uses the top button to play a drum loop
  drumLoop();

  // calls the get mic function, which plays sound back when it reads sound
  getMic();

  arpeggiatorInput = arpeggiatorOutput; // ready input data for inline assembly (set to previous output)

  asm volatile(
    " arpLoop: " // tag for the assembly code section
    " add %[arpeggiatorInput], %[arpInc] \n\t" // increment arpeggiator by arpInc
    " cp %[arpMax], %[arpeggiatorInput] \n\t" // compare arpeggiator with max arpeggiator
    " brsh endLoop \n\t" // branch if same or higher
    " mov %[arpeggiatorInput], %[zero] \n\t" // resetting arpeggiator
    " endLoop: " // point for branch to jump to if skipping the arp reset
    " mov %[arpeggiatorOutput], %[arpeggiatorInput] \n\t" // set output to same as input
    : [arpeggiatorOutput] "=d" (arpeggiatorOutput) // output variables
    : [arpInc] "d" (arpInc), [arpMax] "d" (arpMax), [zero] "d" (zero), [arpeggiatorInput] "d" (arpeggiatorInput) // input variables
    : 
  );

  // calls the bass line function, which uses the left, right, and bottom buttons to play arpeggiated notes
  bassLine(arpeggiatorOutput);

}

// click joystick and move around to play notes
void melody()
{
  int xValue = Esplora.readJoystickX(); // read the joystick's X axis
  int yValue = Esplora.readJoystickY(); // read the joystick's Y axis

  int joystickClick = Esplora.readJoystickSwitch(); // read the joystick button

  // if the joystick button is pressed, play notes based on the joystick position
  if (joystickClick == 0)
  {
    Esplora.tone(note[xValue + yValue]);
  }
  else
  {
    Esplora.noTone();
  }
}

// hold left, right, and up buttons to play arpeggiators
void bassLine(int arpeggiator)
{
  if (Esplora.readButton(SWITCH_DOWN) == LOW) {
    Esplora.tone(note[arpeggiator]);
  }
  else if (Esplora.readButton(SWITCH_LEFT) == LOW) {
    Esplora.tone(note[arpeggiator / 2]);
  }
  else if (Esplora.readButton(SWITCH_RIGHT) == LOW) {
    Esplora.tone(note[arpeggiator * 2]);
  }
  else
  {
    Esplora.noTone();
  }
}

// hold up botton to play a drum loop
void drumLoop()
{
  if (Esplora.readButton(SWITCH_UP) == LOW) {
    Esplora.tone(note[2]);
  }
  else
  {
    Esplora.noTone();
  }
}

// output sound based on mic input
void getMic()
{
  int loudness = Esplora.readMicrophone(); // read mic frequency
  int soundDeadZone = 1; // set mic dead zone

  Esplora.writeGreen(loudness); // light up LED based on the mic frequency

  // play sound if mic reads a loud enough sound
  if (loudness > soundDeadZone)
  {
    Esplora.tone(note[loudness]);
  }
  else
  {
    Esplora.noTone();
  }
}
