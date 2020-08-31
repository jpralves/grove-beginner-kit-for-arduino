
#define tempo_startrekintro 225
const char melody_startrekintro[] PROGMEM = {
  // Star Trek Intro
  // Score available at https://musescore.com/user/10768291/scores/4594271

  _D4, -8, _G4, 16, _C5, -4,
  _B4, 8, _G4, -16, _E4, -16, _A4, -16,
  _D5, 2
};

void playMelody(int tempo, const char * melody, int melody_size) {
//  int tempo = pgm_read_word(&tempoList[melodyIndex]);
  //const char* melody = (char *) pgm_read_word(melodypos);
  //int melody_size = pgm_read_word(&melodyListSizes[melodyIndex]);
  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int wholenote = (60000 * 4) / tempo;
  char divider = 0;
  int noteDuration = 0;
  int noteIndex;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < melody_size; thisNote += 2) {
    // calculates the duration of each note
    //divider = pgm_read_word_near(melody+thisNote + 1);
    noteIndex = pgm_read_byte_near(melody + thisNote);
    divider = pgm_read_byte_near(melody + thisNote + 1);
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    if (digitalRead(buttonPin) == HIGH)
      break;
  
    tone(buzzerPin, pgm_read_word_near(notes+noteIndex), noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzerPin);
  }
}

void buzzerShow() {
  playMelody(tempo_startrekintro, melody_startrekintro, sizeof(melody_startrekintro));
}
