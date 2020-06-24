#ifndef TEENSYSYNTH_H
#define TEENSYSNTH_H

// set SYNTH_DEBUG to enable debug logging (1=most,2=all messages)
#define SYNTH_DEBUG 0

// define MIDI channel
#define SYNTH_MIDICHANNEL 7

// inital poly mode (POLY, MONO or PORTAMENTO)
#define SYNTH_INITIALMODE POLY

// define tuning of A4 in Hz
#define SYNTH_TUNING 440

// gain at oscillator/filter input stage (1:1)
// keep low so filter does not saturate with resonance
#define GAIN_OSC 0.08

// gain in final mixer stage for polyphonic mode (4:1)
// (0.25 is the safe value but larger sounds better :) )
#define GAIN_POLY 0.3

// smoothing factor for cutoff/resonance curves
// 0.09 should give nice precision for lower freqs
#define S_CURVE 0.09

// gain in final mixer stage for monophonic modes
#define GAIN_MONO 0.3

//amount of presets to store in eprom
#define NUM_PRESETS 10

//overwrite eeprom with initial data
#define FORCE_INITIALIZE_PRESETS false

// audio memory
#define AMEMORY 35

#define SYNTH_SERIAL Serial

// whether to enable uart midi
#define SERIALMIDI true

// MIDI CC numbers
#define CC_MODULATION 1
#define CC_PORTAMENTO_TIME 5
#define CC_VOLUME 7
#define CC_FIX_VOLUME 9
#define CC_PANORAMA 10
#define CC_ENV_ATK 73
#define CC_ENV_REL 72
#define CC_FLT_FREQ 74
#define CC_FLT_RES 71
#define CC_FLT_ATT 16
#define CC_POLY_MODE 18
#define CC_ENV_MODE 19
#define CC_ENV_DELAY 20
#define CC_ENV_HOLD 21
#define CC_ENV_DECAY 75
#define CC_ENV_SUSTAIN 76
#define CC_PULSE_WIDTH 14
#define CC_PB_RANGE 25
#define CC_FLT_LFO_RATE 12
#define CC_FLT_LFO_DEPTH 13
#define CC_FLT_ENV_ATK 77
#define CC_FLT_ENV_DECAY 78
#define CC_FLT_ENV_SUSTAIN 79
#define CC_FLT_ENV_DEPTH 70
#define CC_PITCH_LFO_RATE 22
#define CC_PITCH_LFO_DEPTH 23
#define CC_PITCH_LFO_MODE 24
#define CC_OSC1_PROGRAM 26
#define CC_OSC2_PROGRAM 27
#define CC_OSC2_OCTAVE 28
#define CC_OSC2_DETUNE 94
#define CC_OSC_BALANCE 29
#define CC_SELECT_PRESET 30
#define CC_LOAD_PRESET 85
#define CC_SAVE_PRESET 86
#define CC_CHORUS_TOGGLE 93
#define CC_FILTER_DRIVE 87
#define CC_SUSTAIN 64
#define CC_PORTAMENTO 65
#define CC_PORTAMENTO_CONTROL 84
#define CC_ALL_NOTES_OFF 123
#define CC_OMNI_OFF 124
#define CC_OMNI_ON 125
#define CC_MONO_ON 126
#define CC_POLY_ON 127

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

//////////////////////////////////////////////////////////////////////
// Data types and lookup tables
//////////////////////////////////////////////////////////////////////

struct Oscillator {
  AudioSynthWaveformModulated* wf;
  AudioSynthWaveformModulated* wf2;
  AudioMixer4*                 wf_sum;
  //AudioFilterStateVariable*    filt;
  AudioFilterMoog*    filt;
  AudioMixer4*                 mix;
  AudioMixer4*                 flt_sum;
  AudioEffectEnvelope*         env;
  AudioEffectEnvelope*         flt_env;
  int8_t  note;
  uint8_t velocity;
};

// synth architecture in separate file
#include "SynthArch.h"

#define NVOICES 8
Oscillator oscs[NVOICES] = {
  { &waveform1, &waveform1b, &waveform_sum_1, &filter1, &mixer1, &flt_sum_1, &envelope1, &flt_env_1, -1, 0 },
  { &waveform2, &waveform2b, &waveform_sum_2, &filter2, &mixer2, &flt_sum_2, &envelope2, &flt_env_2, -1, 0 },
  { &waveform3, &waveform3b, &waveform_sum_3, &filter3, &mixer3, &flt_sum_3, &envelope3, &flt_env_3, -1, 0 },
  { &waveform4, &waveform4b, &waveform_sum_4, &filter4, &mixer4, &flt_sum_4, &envelope4, &flt_env_4, -1, 0 },
  { &waveform5, &waveform5b, &waveform_sum_5, &filter5, &mixer5, &flt_sum_5, &envelope5, &flt_env_5, -1, 0 },
  { &waveform6, &waveform6b, &waveform_sum_6, &filter6, &mixer6, &flt_sum_6, &envelope6, &flt_env_6, -1, 0 },
  { &waveform7, &waveform7b, &waveform_sum_7, &filter7, &mixer7, &flt_sum_7, &envelope7, &flt_env_7, -1, 0 },
  { &waveform8, &waveform8b, &waveform_sum_8, &filter8, &mixer8, &flt_sum_8, &envelope8, &flt_env_8, -1, 0 },
};

#define NPROGS 7
uint8_t progs[NPROGS] = {
  WAVEFORM_SAWTOOTH,
  WAVEFORM_SINE,
  WAVEFORM_SQUARE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_TRIANGLE_VARIABLE,
  WAVEFORM_PULSE,
  WAVEFORM_SAMPLE_HOLD,
//  WAVEFORM_ARBITRARY,
};

enum FilterMode_t {
  LOWPASS,
  BANDPASS,
  HIGHPASS,
  FILTEROFF,
  FILTERMODE_N,
};

struct Preset {
  uint8_t currentProgram;
  uint8_t currentOsc2Program;
  
  bool  polyOn;
  bool  omniOn;
  bool  velocityOn;
  
  float channelVolume;
  float oscBalance; // 0-1
  float panorama;
  float pitchScale;
  int   octCorr;
  int   osc2Octave;
  int   osc2Detune;
  
  // filter
  FilterMode_t filterMode;
  float filtFreq; // 20-AUDIO_SAMPLE_RATE_EXACT/2.5
  float filtReso; // 0.9-5.0
  float filtAtt;  // 0-1
  float filtDrive;
  
  // filter lfo
  float  fltLfoDepth;
  float  fltLfoRate;
  
  // pitch lfo
  float pitchLfoRate;
  float pitchLfoDepth;
  
  // pwm lfo
  float pwmLfoRate;
  
  // envelope
  bool  envOn;
  float envDelay;
  float envAttack;
  float envHold;
  float envDecay;
  float envSustain;
  float envRelease;
  
  // filter envelope
  bool  fltEnvOn;
  bool  fltEnvInvert;
  float fltEnvDelay;
  float fltEnvAttack;  
  float fltEnvHold;    
  float fltEnvDecay;   
  float fltEnvSustain; 
  float fltEnvRelease; 
  float fltEnvDepth;   
  
  // portamento
  bool     portamentoOn;
  uint16_t portamentoTime;

  bool chorusOn;
};

//////////////////////////////////////////////////////////////////////
// Global variables
//////////////////////////////////////////////////////////////////////
const float DIV127 = (1.0 / 127.0);

float   masterVolume   = 1;
uint8_t currentProgram = WAVEFORM_PULSE;
uint8_t currentOsc2Program = WAVEFORM_TRIANGLE;

bool  polyOn;
bool  omniOn;
bool  velocityOn;

bool  pwmDirection;

bool  sustainPressed;
float channelVolume;
float oscBalance; // 0-1
float panorama;
float pitchBend;  // -1/+1 oct
float pitchScale;
int   octCorr;
int   osc2Octave;
int   osc2Detune;
float   oldPitchLfoDepth;
float   oldPitchLfoRate;

// filter
FilterMode_t filterMode;
float filtFreq; // 20-AUDIO_SAMPLE_RATE_EXACT/2.5
float filtReso; // 0.9-5.0
float filtAtt;  // 0-1
float filtDrive;

// filter lfo
float  fltLfoDepth;
float  fltLfoRate;

// pitch lfo
float pitchLfoRate;
float pitchLfoDepth;

// pwm lfo
float pwmLfoRate;

// envelope
bool  envOn;
float envDelay;   // 0-200
float envAttack;  // 0-200
float envHold;    // 0-200
float envDecay;   // 0-200
float envSustain; // 0-1
float envRelease; // 0-200

// filter envelope
bool  fltEnvOn;
bool  fltEnvInvert;
float fltEnvDelay;   // 0-200
float fltEnvAttack;  // 0-200
float fltEnvHold;    // 0-200
float fltEnvDecay;   // 0-200
float fltEnvSustain; // 0-1
float fltEnvRelease; // 0-200
float fltEnvDepth;   // 0-1

// portamento
bool     portamentoOn;
uint16_t portamentoTime;
int8_t   portamentoDir;
float    portamentoStep;
float    portamentoPos;

bool chorusOn;

//preset related
uint8_t selectedPreset;

//allocate memory for presets
Preset presets[NUM_PRESETS];
#endif
