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

#define LEDPort PORTB           // Arduino pin 13 is bit 5 of port B
#define LEDBit 5                // Constant for bit 5
#define DelayTime (uint32_t)((Clock_MHz * MilliSec / 5))  // set to any rate desired
#define MilliSec 1000000

#define Clock_MHz 16
int arpeggiator = 0;

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
  Serial.begin(9600);
}

void loop() {
  int tempo = Esplora.readSlider();
  
  //melody(tempo);

  //drumLoop();

  //getMic(tempo);

  // turn this into inline assembly
  int arpInc = 20;
  if (arpeggiator < (4*arpInc))
  {
    arpeggiator += arpInc;
  }
  if (arpeggiator >= (4*arpInc))
  {
    arpeggiator = 0;
  }

  asm volatile(
    " addLoop: "
    " mov r16, %[var1] \n\t"
    " add r16, %[var1] \n\t"
    " mov %[var2], r16 \n\t" 
    : [var2] "=d" (var2) // output variables
    : [var1] "d" (var1) // input variables
    : "r16" // clobbers
  );

delay(1000);
  Serial.print(var2);
  
  /*
   asm volatile (
     " mainLoop: "                         // move DelayTime to registers
     "    mov r16, %D2  \n\t"              // LSB of DelayTime
     "    mov r17, %C2  \n\t"              // A2, B2, C2, D2 each is 8 bits
     "    mov r18, %B2  \n\t"
     "    mov r19, %A2  \n\t"              // MSB of DelayTime
     "    mov r20, %D2  \n\t"
     "    mov r21, %C2  \n\t"
     "    mov r22, %B2  \n\t"
     "    mov r23, %A2  \n\t"
     "    sbi %[port], %[ledbit] \n\t"     // set I/O bit (turn LED on)
     " onLoop: "
     "    subi r23, 1  \n\t"		   // subtract constant from register
     "    sbci r22, 0  \n\t"		   // subtract with carry constant from register
     "    sbci r21, 0  \n\t"
     "    sbci r20, 0  \n\t"
     "    brcc onLoop  \n\t"               // branch if carry cleared
     "    cbi  %[port], %[ledbit] \n\t"    // clear I/O bit (turn LED off)
     " offLoop:"
     "    subi r19, 1  \n\t"
     "    sbci r18, 0  \n\t"
     "    sbci r17, 0  \n\t"
     "    sbci r16, 0  \n\t"
     "    brcc offLoop \n\t"
     :                                     // no output variables
     : [port] "n" (_SFR_IO_ADDR(LEDPort)), // input variables
       [ledbit] "n" (LEDBit),              // n: integer with known value
       "d" (DelayTime)                     // d: greater than r15
     : "r16","r17","r18","r19","r20","r21","r22","r23"  // clobbers
     );
     */

  bassLine(arpeggiator);

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
