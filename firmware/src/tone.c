#include "tone.h"

// libc
#include <stdint.h>
#include <stdbool.h>

// project
#include "pwm.h"

#define TONE_NUM_SINE_SAMPLES 0x3FF

struct Tone
{
  uint8_t skipNum[TONE_NUM_SAME_TIME];
  uint16_t sineIndex[TONE_NUM_SAME_TIME];
};

static const uint16_t sineSamples[TONE_NUM_SINE_SAMPLES + 1] = {
#include "sine.inc"
};
static const uint8_t sineSkipCount[TONE_NUM_NOTES] = {23, 26, 29, 31, 34, 38, 43, 46};
static struct Tone tone = {0};

void Tone_Initialize()
{
  Pwm_Initialize();
}

void Tone_SetNotes(uint8_t notes)
{
  uint8_t noteNum = 0;

  for (uint8_t n = 0; n < TONE_NUM_NOTES && noteNum < TONE_NUM_SAME_TIME; n++)
  {
    if ((notes >> n) & 0x01)
    {
      tone.skipNum[noteNum] = sineSkipCount[n];
      noteNum++;
    }
  }
  for (; noteNum < TONE_NUM_SAME_TIME; noteNum++)
  {
    tone.skipNum[noteNum] = 0;
    tone.sineIndex[noteNum] = sineSamples[0];
  }
}

void Tone_Start()
{
  Pwm_Start();
}

void Tone_Stop()
{
  Pwm_Stop();
}

inline void Tone_Update()
{
  uint16_t pwmDuty = 0;

  pwmDuty += sineSamples[tone.sineIndex[0]];
  pwmDuty += sineSamples[tone.sineIndex[1]];
  pwmDuty += sineSamples[tone.sineIndex[2]];
  pwmDuty += sineSamples[tone.sineIndex[3]];

  tone.sineIndex[0] = (tone.sineIndex[0] + tone.skipNum[0]) & TONE_NUM_SINE_SAMPLES;
  tone.sineIndex[1] = (tone.sineIndex[1] + tone.skipNum[1]) & TONE_NUM_SINE_SAMPLES;
  tone.sineIndex[2] = (tone.sineIndex[2] + tone.skipNum[2]) & TONE_NUM_SINE_SAMPLES;
  tone.sineIndex[3] = (tone.sineIndex[3] + tone.skipNum[3]) & TONE_NUM_SINE_SAMPLES;

  pwmDuty /= 4;

  Pwm_SetDuty(pwmDuty);
}
