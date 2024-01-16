#include "tone.h"

// libc
#include <stdint.h>
#include <stdbool.h>

// project
#include "pwm.h"

// defines
#define TONE_NUM_SINE_SAMPLES 0x3FF
#define TONE_NUM_SAME_TIME 4

// types
struct Tone
{
  uint8_t skipNum[TONE_NUM_SAME_TIME];
  uint16_t sineIndex[TONE_NUM_SAME_TIME];
};

// variables
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
  for (uint8_t n = 0; n < TONE_NUM_NOTES; n++)
  {
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

void Tone_Update()
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
