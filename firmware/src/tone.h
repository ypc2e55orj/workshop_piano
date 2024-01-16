#ifndef TONE_H
#define TONE_H

// libc
#include <stdint.h>

enum
{
  TONE_NOTE_C,
  TONE_NOTE_D,
  TONE_NOTE_E,
  TONE_NOTE_F,
  TONE_NOTE_G,
  TONE_NOTE_A,
  TONE_NOTE_B,
  TONE_NOTE_C_H,
  TONE_NUM_NOTES
};

void Tone_Initialize(void);
void Tone_SetNotes(uint8_t notes);
void Tone_Start(void);
void Tone_Stop(void);
void Tone_Update(void);

#endif // TONE_H
