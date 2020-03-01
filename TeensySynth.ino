#include <Audio.h>
#include <EEPROM.h>
#include <MIDI.h>
#include "filter_moog.h"
#include "effect_ensemble.h"

// set SYNTH_DEBUG to enable debug logging (1=most,2=all messages)
#define SYNTH_DEBUG 1

// define MIDI channel
#define SYNTH_MIDICHANNEL 3

// inital poly mode (POLY, MONO or PORTAMENTO)
#define SYNTH_INITIALMODE POLY

// define tuning of A4 in Hz
#define SYNTH_TUNING 440

// gain at oscillator/filter input stage (1:1)
// keep low so filter does not saturate with resonance
#define GAIN_OSC 0.3

// gain in final mixer stage for polyphonic mode (4:1)
// (0.25 is the safe value but larger sounds better :) )
//#define GAIN_POLY 1.
#define GAIN_POLY 0.5

// smoothing factor for cutoff/resonance curves
// 0.09 should give nice precision for lower freqs
#define S_CURVE 0.09

// gain in final mixer stage for monophonic modes
//#define GAIN_MONO 1.
#define GAIN_MONO 0.5

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
#define CC_ENV_ATK 12
#define CC_ENV_REL 13
#define CC_FLT_FREQ 14
#define CC_FLT_RES 15
#define CC_FLT_ATT 16
#define CC_FLT_MODE 17
#define CC_POLY_MODE 18
#define CC_ENV_MODE 19
#define CC_ENV_DELAY 20
#define CC_ENV_HOLD 21
#define CC_ENV_DECAY 22
#define CC_ENV_SUSTAIN 23
#define CC_PULSE_WIDTH 24
#define CC_PB_RANGE 30
#define CC_FLT_LFO_RATE 31
#define CC_FLT_LFO_DEPTH 32
#define CC_FLT_ENV_ATK 33
#define CC_FLT_ENV_DECAY 34
#define CC_FLT_ENV_SUSTAIN 35
#define CC_FLT_ENV_REL 36
#define CC_FLT_ENV_INVERT 37
#define CC_FLT_ENV_DEPTH 38
#define CC_PITCH_LFO_RATE 39
#define CC_PITCH_LFO_DEPTH 40
#define CC_OSC1_PROGRAM 41
#define CC_OSC2_PROGRAM 42
#define CC_OSC2_OCTAVE 43
#define CC_OSC2_DETUNE 44
#define CC_OSC_BALANCE 45
#define CC_SELECT_PRESET 46
#define CC_LOAD_PRESET 47
#define CC_SAVE_PRESET 48
#define CC_CHORUS_TOGGLE 49
#define CC_PITCH_LFO_MODE 50
#define CC_FILTER_DRIVE 51
#define CC_SUSTAIN 64
#define CC_PORTAMENTO 65
#define CC_PORTAMENTO_CONTROL 84
#define CC_RESET_ALL 121
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

#define NPROGS 8
uint8_t progs[NPROGS] = {
  WAVEFORM_SINE,
  WAVEFORM_SQUARE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_TRIANGLE_VARIABLE,
  WAVEFORM_SAWTOOTH,
  WAVEFORM_PULSE,
  WAVEFORM_SAMPLE_HOLD,
  WAVEFORM_ARBITRARY,
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

float   masterVolume   = 0.8;
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

//////////////////////////////////////////////////////////////////////
// Handling of loading and saving presets
//////////////////////////////////////////////////////////////////////
inline void savePreset(uint8_t presetno){
  if (presetno <= NUM_PRESETS){
    presets[presetno] = {
      currentProgram, currentOsc2Program, polyOn, omniOn, velocityOn, channelVolume, oscBalance, panorama, pitchScale, octCorr, 
      osc2Octave, osc2Detune, filterMode, filtFreq, filtReso, filtAtt, filtDrive, fltLfoDepth, fltLfoRate, pitchLfoRate, pitchLfoDepth, pwmLfoRate, envOn,
      envDelay, envAttack, envHold, envDecay, envSustain, envRelease, fltEnvOn, fltEnvInvert, fltEnvDelay, fltEnvAttack, fltEnvHold, fltEnvDecay,
      fltEnvSustain, fltEnvRelease, fltEnvDepth, portamentoOn, portamentoTime, chorusOn 
    };
  }
  savePresetsToEeprom();  
}

inline void savePresetsToEeprom() {
    #if SYNTH_DEBUG > 0
      SYNTH_SERIAL.print ("Preset array size is ");
      SYNTH_SERIAL.println (sizeof (presets));
      SYNTH_SERIAL.println ("Saving preset data to EEPROM");
    #endif  
    EEPROM.put(1,presets);
}


inline void loadPresetsFromEeprom() {
  #if SYNTH_DEBUG > 0
  SYNTH_SERIAL.println("Loading presets from EEPROM");
  #endif  
  EEPROM.get(1, presets);
  #if SYNTH_DEBUG > 0
  SYNTH_SERIAL.println(presets[0].currentProgram);
  #endif
}

inline void loadPreset(uint8_t presetno){
  currentProgram      = presets[presetno].currentProgram;
  currentOsc2Program  = presets[presetno].currentOsc2Program;
  polyOn              = presets[presetno].polyOn;
  omniOn              = presets[presetno].omniOn;
  velocityOn          = presets[presetno].velocityOn;    
  channelVolume       = presets[presetno].channelVolume;
  oscBalance          = presets[presetno].oscBalance;
  panorama            = presets[presetno].panorama;
  pitchScale          = presets[presetno].pitchScale;
  octCorr             = presets[presetno].octCorr;
  osc2Octave          = presets[presetno].osc2Octave;
  osc2Detune          = presets[presetno].osc2Detune;

  filterMode          = presets[presetno].filterMode;
  filtFreq            = presets[presetno].filtFreq;
  filtReso            = presets[presetno].filtReso;
  filtAtt             = presets[presetno].filtAtt;
  filtDrive           = presets[presetno].filtDrive;

  // filter lfo
  fltLfoDepth         = presets[presetno].fltLfoDepth;
  fltLfoRate          = presets[presetno].fltLfoRate;

  // pitch lfo
  pitchLfoDepth       = presets[presetno].pitchLfoDepth;
  pitchLfoRate        = presets[presetno].pitchLfoRate;

  // pwm lfo
  pwmLfoRate          = presets[presetno].pwmLfoRate;

  // envelope
  envOn               = presets[presetno].envOn;
  envDelay            = presets[presetno].envDelay;
  envAttack           = presets[presetno].envAttack;
  envHold             = presets[presetno].envHold;
  envDecay            = presets[presetno].envDecay;
  envSustain          = presets[presetno].envSustain;
  envRelease          = presets[presetno].envRelease;

  // filter envelope
  fltEnvOn            = presets[presetno].fltEnvOn;
  fltEnvInvert        = presets[presetno].fltEnvInvert;
  fltEnvDelay         = presets[presetno].fltEnvDelay;
  fltEnvAttack        = presets[presetno].fltEnvAttack;
  fltEnvHold          = presets[presetno].fltEnvHold;
  fltEnvDecay         = presets[presetno].fltEnvDecay;
  fltEnvSustain       = presets[presetno].fltEnvSustain;
  fltEnvRelease       = presets[presetno].fltEnvRelease;

  // portamento
  portamentoOn        = presets[presetno].portamentoOn;
  portamentoTime      = presets[presetno].portamentoTime;

  chorusOn            = presets[presetno].chorusOn;

  updateProgram();
  updateOsc2Program();
  updatePolyMode();
  updateFilter();
  updateFilterMode();
  updateFilterLFO();
  updatePitchLFO();
  updatePwmLFO();
  updateEnvelope();
  updatePan();

  #if SYNTH_DEBUG > 0
    SYNTH_SERIAL.print ("Loaded preset ");
    SYNTH_SERIAL.println (presetno);
  #endif  

}

bool checkEeprom() {
  #if SYNTH_DEBUG > 0
    SYNTH_SERIAL.println ("Checking if eeprom contains 42 in slot 0, so we know if there is preset data");
  #endif  
  byte checkvalue = EEPROM.read(0);
  if (checkvalue == 42) {
    return true;
  } else {
    return false;
  }
}


//////////////////////////////////////////////////////////////////////
// Handling of sounding and pressed notes
//////////////////////////////////////////////////////////////////////
int8_t notesOn[NVOICES]      = { -1, -1, -1, -1, -1, -1, -1, -1, };
int8_t notesPressed[NVOICES] = { -1, -1, -1, -1, -1, -1, -1, -1, };

inline void notesReset(int8_t* notes) {
  memset(notes,-1,NVOICES*sizeof(int8_t));
}

inline void notesAdd(int8_t* notes, uint8_t note) {
  int8_t *end=notes+NVOICES;
  do {
    if(*notes == -1) {
      *notes = note;
      break;
    }
  } while (++notes < end);
}

inline int8_t notesDel(int8_t* notes, uint8_t note) {
  int8_t lastNote = -1;
  int8_t *pos=notes, *end=notes+NVOICES;
  while (++pos < end && *(pos-1) != note);
  if (pos-1 != notes) lastNote = *(pos-2);
  while (pos < end) {
    *(pos-1) = *pos;
    if (*pos++ == -1) break;
  }
  if (*(end-1)==note || pos == end)
      *(end-1) = -1;
  return lastNote;
}

inline bool notesFind(int8_t* notes, uint8_t note) {
  int8_t *end=notes+NVOICES;
  do {
    if (*notes == note) return true;
  } while (++notes < end);
  return false;
}

//////////////////////////////////////////////////////////////////////
// Parameter control functions
//////////////////////////////////////////////////////////////////////
inline void updateFilterMode() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    for (uint8_t fm=0; fm<FILTERMODE_N; ++fm) {
      if (fm == filterMode) o->mix->gain(fm,filtAtt);
      else                  o->mix->gain(fm,0);
    }
  } while (++o < end);
}

inline void updateFilter() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    o->filt->frequency(filtFreq);
    o->filt->resonance(filtReso);
    o->filt->drive(filtDrive);
  } while (++o < end);
}

inline void updateFilterEnvelope() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    o->flt_env->delay(fltEnvDelay);
    o->flt_env->attack(fltEnvAttack);
    o->flt_env->hold(fltEnvHold);
    o->flt_env->decay(fltEnvDecay);
    o->flt_env->sustain(fltEnvSustain);
    o->flt_env->release(fltEnvRelease);
  } while (++o < end);
}

inline void updateFilterLFO() {
  flt_lfo.amplitude(fltLfoDepth);
  flt_lfo.frequency(fltLfoRate);
}

inline void updatePwmLFO() {
  pwm_lfo.frequency(pwmLfoRate);
}

inline void updatePitchLFO() {
  pitch_lfo.amplitude(pitchLfoDepth);
  pitch_lfo.frequency(pitchLfoRate);
}

inline void updateEnvelope() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    o->env->delay(envDelay);
    o->env->attack(envAttack);
    o->env->hold(envHold);
    o->env->decay(envDecay);
    o->env->sustain(envSustain);
    o->env->release(envRelease);
  } while (++o < end);
}

inline void updateEnvelopeMode() {
  float env    = envOn ? 1 : 0;
  float noenv  = envOn ? 0 : 1;
  for (uint8_t i=0; i<2; ++i) {
    // env
    envmixer1.gain(i,env);
    envmixer2.gain(i,env);
    envmixer3.gain(i,env);
    envmixer4.gain(i,env);
    // no env
    envmixer1.gain(i+2,noenv);
    envmixer2.gain(i+2,noenv);
    envmixer3.gain(i+2,noenv);
    envmixer4.gain(i+2,noenv);
  }
}

inline void updateFilterEnvelopeMode() {
  if (!fltEnvOn) {
    flt_env_carrier.amplitude(0);
  } else {
    if (fltEnvInvert) {
      flt_env_carrier.amplitude(-fltEnvDepth);
    } else {
      flt_env_carrier.amplitude(fltEnvDepth);
    }
  }
}


void resetAll() {
  polyOn     = true;
  omniOn     = false;
  velocityOn = true;

  osc2Octave = 0;
  osc2Detune = 0;
  
  filterMode     = LOWPASS;
  sustainPressed = false;
  channelVolume  = 1.0;
  panorama       = 0.5;
  pitchBend      = 0;
  pitchScale     = 12./2;
  oldPitchLfoDepth = 999; //hacky way to use modwheel - set original lfo value as impossible value 999 to know we're not using the modwheel atm
  oldPitchLfoRate = 999;
  
  // filter
  filtFreq = 12000.;
  filtReso = 2;
  filtAtt  = 1.;
  filtDrive = 2;

  // filter lfo
  fltLfoDepth = 0;
  fltLfoRate = 0;

  // pitch lfo
  pitchLfoDepth = 0;
  pitchLfoRate = 6;

  // pwm lfo
  pwmLfoRate = 0.5;

  // envelope
  envOn      = true;
  envDelay   = 0;
  envAttack  = 5;
  envHold    = 0;
  envDecay   = 0;
  envSustain = 1;
  envRelease = 20;

  // filter envelope
  fltEnvOn      = true;
  fltEnvInvert  = false;
  fltEnvDelay   = 0;
  fltEnvAttack  = 5;
  fltEnvHold    = 0;
  fltEnvDecay   = 0;
  fltEnvSustain = 1;
  fltEnvRelease = envRelease;

  // portamento
  portamentoOn   = false;
  portamentoTime = 500;
  portamentoDir  = 0;
  portamentoStep = 0;
  portamentoPos  = -1;

  chorusOn = false;

  updatePolyMode();
  updateFilter();
  updateFilterMode();
  updateFilterLFO();
  updatePitchLFO();
  updatePwmLFO();
  updateEnvelope();
  updatePan();
  
}



inline void updateProgram() {
    
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    o->wf->begin(progs[currentProgram]);
  } while(++o < end);
}

inline void updateOsc2Program() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    o->wf2->begin(progs[currentOsc2Program]);
  } while(++o < end);
}

inline void updatePitch() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    if (o->note < 0) continue;
    o->wf->frequency(noteToFreq(o->note));
    o->wf2->frequency(noteToFreq(o->note + osc2Octave) + osc2Detune);
  } while(++o < end);
}

inline void updateVolume() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  float velocity;
  do {
    if (o->note < 0) continue;
    velocity = velocityOn ? o->velocity/127. : 1;
    o->wf->amplitude(velocity*channelVolume*GAIN_OSC);
    o->wf2->amplitude(velocity*channelVolume*GAIN_OSC);    
  } while(++o < end);
}

inline void updatePan() {
  float norm  = (polyOn && !portamentoOn) ? GAIN_POLY : GAIN_MONO;
  float left=norm, right=norm;
  if (panorama < 0.5) right *= 2*panorama;
  else left *= 2*(1-panorama);
  if (chorusOn) {
    left = left/2;
    right = right/2;
  }
  for (uint8_t i=0; i<4; ++i){
    mixerL.gain(i,left);
    mixerR.gain(i,right);
  }
  if (!chorusOn){
    mixerL.gain(1,0);
    mixerR.gain(1,0);
  }
}

inline void updateMasterVolume() {
  /*
  // read the volume knob
  float vol = (float) analogRead(A1) / 1280.0;
  if( fabs(vol-masterVolume) > 0.01) {
    masterVolume = vol;
    sgtl5000_1.volume(masterVolume);
#if SYNTH_DEBUG > 0
    SYNTH_SERIAL.print("Volume: ");
    SYNTH_SERIAL.println(vol);
#endif
  }
  */
}

inline void updatePolyMode() {
  allOff();
  updateEnvelopeMode();
  updatePan();
}

inline void updatePortamento()
{
  if (portamentoDir == 0) return;
  if (oscs->note < 0) {
    portamentoDir = 0;
    return;
  }
  if (portamentoDir < 0) {
    portamentoPos -= portamentoStep;
    if (portamentoPos < oscs->note) {
      portamentoPos = oscs->note;
      portamentoDir = 0;
    }
  }
  else {
    portamentoPos += portamentoStep;
    if (portamentoPos > oscs->note) {
      portamentoPos = oscs->note;
      portamentoDir = 0;
    }
  }
  oscs->wf->frequency(noteToFreq(portamentoPos));
  oscs->wf2->frequency(noteToFreq(portamentoPos + osc2Octave) + osc2Detune);
}

inline void updateOscBalance()
{
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    o->wf_sum->gain(0,1-oscBalance);
    o->wf_sum->gain(1,oscBalance);
  } while(++o < end); 
}

//////////////////////////////////////////////////////////////////////
// Oscillator control functions
//////////////////////////////////////////////////////////////////////
inline float noteToFreq(float note) {
  // Sets all notes as an offset of A4 (#69)
  //if (portamentoOn) note = portamentoPos;
  return SYNTH_TUNING*pow(2,(note - 69)/12.+pitchBend/pitchScale+octCorr);
}

inline void oscOn(Oscillator& osc, int8_t note, uint8_t velocity) {
  float v = velocityOn ? velocity/127. : 1;
  if (osc.note!=note) {
    osc.wf->frequency(noteToFreq(note));
    osc.wf2->frequency(noteToFreq(note + osc2Octave) + osc2Detune);
    notesAdd(notesOn,note);
    if (envOn && !osc.velocity) osc.env->noteOn();
    if (fltEnvOn) osc.flt_env->noteOn();
    osc.wf->amplitude(v*channelVolume*GAIN_OSC);
    osc.wf2->amplitude(v*channelVolume*GAIN_OSC);    
    osc.velocity = velocity;
    osc.note = note;
  } else if (velocity > osc.velocity) {
    osc.wf->amplitude(v*channelVolume*GAIN_OSC);
    osc.wf2->amplitude(v*channelVolume*GAIN_OSC);    
    osc.velocity = velocity;
  }
}

inline void oscOff(Oscillator& osc) {
  if (envOn) {osc.env->noteOff(); }
  else       osc.wf->amplitude(0);
  if (fltEnvOn) osc.flt_env->noteOff();
  notesDel(notesOn,osc.note);
  osc.note = -1;
  osc.velocity = 0;
}

inline void allOff() {
  Oscillator *o=oscs,*end=oscs+NVOICES;
  do {
    oscOff(*o);
    o->wf->amplitude(0);
    o->wf2->amplitude(0);
    o->env->noteOff();
    o->flt_env->noteOff();
  } while(++o < end);
  notesReset(notesOn);
}


//////////////////////////////////////////////////////////////////////
// MIDI handlers
//////////////////////////////////////////////////////////////////////
void OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (!omniOn && channel != SYNTH_MIDICHANNEL) return;

#if SYNTH_DEBUG > 1
  SYNTH_SERIAL.println("NoteOn");
#endif

  notesAdd(notesPressed,note);

  Oscillator *o=oscs;
  if (portamentoOn) {
    if (portamentoTime == 0 || portamentoPos < 0) {
      portamentoPos = note;
      portamentoDir = 0;
    } else if (portamentoPos > -1) {
      portamentoDir  = note > portamentoPos ? 1 : -1;
      portamentoStep = fabs(note-portamentoPos)/(portamentoTime);
    }
    *notesOn = -1;
    oscOn(*o, note, velocity);
  }
  else if (polyOn) {
    Oscillator *curOsc=0, *end=oscs+NVOICES;
    if (sustainPressed && notesFind(notesOn,note)) {
      do {
        if (o->note == note) {
          curOsc = o;
          break;
        }
      } while (++o < end);
    }
    for (o=oscs; o < end && !curOsc; ++o) {
      if (o->note < 0) {
        curOsc = o;
        break;
      }
    }
    if (!curOsc && *notesOn != -1) {
#if SYNTH_DEBUG > 0
      SYNTH_SERIAL.println("Stealing voice");
#endif
      curOsc = OnNoteOffReal(channel,*notesOn,velocity,true);
    }
    if (!curOsc) return;
    oscOn(*curOsc, note, velocity);
  }
  else 
  {
    *notesOn = -1;
    oscOn(*o, note, velocity);
  }

  return;
}

Oscillator* OnNoteOffReal(uint8_t channel, uint8_t note, uint8_t velocity, bool ignoreSustain) {
  if (!omniOn && channel != SYNTH_MIDICHANNEL) return 0;

#if 0 //#ifdef SYNTH_DEBUG
  SYNTH_SERIAL.println("NoteOff");
#endif
  int8_t lastNote = notesDel(notesPressed,note);
  
  if (sustainPressed && !ignoreSustain) return 0;

  Oscillator *o=oscs;
  if (portamentoOn) {
    if (o->note == note) {
      if (lastNote != -1) {
        notesDel(notesOn,note);
        if (portamentoTime == 0) {
          portamentoPos = lastNote;
          portamentoDir = 0;
        } else {
          portamentoDir = lastNote > portamentoPos? 1 : -1;
          portamentoStep = fabs(lastNote-portamentoPos)/(portamentoTime);
        }
        oscOn(*o, lastNote, velocity);
      }
      else 
      {
        oscOff(*o);
        portamentoPos = -1;
        portamentoDir = 0;
      }
    }
    if (oscs->note == note) {
      if (lastNote != -1) {
        notesDel(notesOn,o->note);
        oscOn(*o, lastNote, velocity);
      } else {
        oscOff(*o);
      }
    }
  }
  else if (polyOn) {
    Oscillator *end=oscs+NVOICES;
    do {
      if (o->note == note) break;
    } while (++o < end);
    if (o == end) return 0;
    oscOff(*o);
  } else {
    if (oscs->note == note) {
      if (lastNote != -1) {
        notesDel(notesOn,o->note);
        oscOn(*o, lastNote, velocity);
      } else {
        oscOff(*o);
      }
    }
  }
  
  return o;
}

inline void OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  OnNoteOffReal(channel,note,velocity,false);
}

void OnAfterTouchPoly(uint8_t channel, uint8_t note, uint8_t value) {
#if SYNTH_DEBUG > 0
  SYNTH_SERIAL.print("AfterTouchPoly: channel ");
  SYNTH_SERIAL.print(channel);
  SYNTH_SERIAL.print(", note ");
  SYNTH_SERIAL.print(note);
  SYNTH_SERIAL.print(", value ");
  SYNTH_SERIAL.println(value);
#endif
}

void OnControlChange(uint8_t channel, uint8_t control, uint8_t value) {
  if (!omniOn && channel != SYNTH_MIDICHANNEL) return;

  switch (control) {
  case 0: // bank select, do nothing (switch sounds via program change only)
    break;

  case CC_MODULATION:
    if (value != 0 && oldPitchLfoDepth == 999 && oldPitchLfoRate == 999) {
      oldPitchLfoDepth = pitchLfoDepth;
      oldPitchLfoRate = pitchLfoRate;
    }
      pitchLfoDepth = (0.04/(1+exp(-S_CURVE*(value-64))));
      pitchLfoRate = (10/(1+exp(-S_CURVE*(value-64))));
    if (value == 0 && oldPitchLfoDepth != 999 && oldPitchLfoRate != 999) {
      pitchLfoDepth = oldPitchLfoDepth;
      pitchLfoRate = oldPitchLfoRate;
      oldPitchLfoDepth = 999; 
      oldPitchLfoRate = 999;
    }
    updatePitchLFO();
    break;
    
  case CC_PORTAMENTO_TIME: // portamento time
  {
    float portamentoRange = portamentoStep*portamentoTime;
    portamentoTime = 10000/(1+exp(-S_CURVE*(value-64)));
    portamentoStep = portamentoRange/portamentoTime;
    break;
  }
  case CC_VOLUME: // volume
    channelVolume = value/127.;
    updateVolume();
    break;
  case CC_FIX_VOLUME: // fix volume
    switch (value) {
    case 0:
      velocityOn = false;
      break;
    case 1:
      velocityOn = true;
      break;
    default:
      velocityOn = !velocityOn;
      break;
    }
    break;
  case CC_PANORAMA: // pan
    panorama = value/127.;
    updatePan();
    break;
  case CC_ENV_ATK: // attack
    envAttack = value*2000./127.;
    updateEnvelope();
    break;
  case CC_ENV_REL: // release
    envRelease = value*2000./127.;
    updateEnvelope();
    break;
  case CC_FLT_FREQ: // filter frequency
    filtFreq = 30+(10000/(1+exp(-S_CURVE*(value-64)))); // 
    //filtFreq = value/2.5*AUDIO_SAMPLE_RATE_EXACT/127.;
    updateFilter();
    break;
  case CC_FLT_RES: // filter resonance
    filtReso = value * DIV127 * 5;
    updateFilter();
    break;
  case CC_FLT_ATT: // filter attenuation
    filtAtt = value/127.;
    updateFilterMode();
    break;
  case CC_FLT_MODE: // filter mode
    if (value < FILTERMODE_N) {
      filterMode = FilterMode_t(value);
    } else {
      filterMode = FilterMode_t((filterMode+1)%FILTERMODE_N);
    }
    updateFilterMode();
    break;
  case CC_POLY_MODE: // poly mode
    switch (value) {
    case 0:
      polyOn = true;
      portamentoOn = false;
      velocityOn = true;
      break;
    case 1:
      polyOn = false;
      portamentoOn = false;
      velocityOn = false;
      break;
    case 2:
      polyOn = false;
      portamentoOn = true;
      velocityOn = false;
      break;
    default: // cycle POLY, MONO, PORTAMENTO
    {
      bool tmp = polyOn;
      polyOn = portamentoOn;
      portamentoOn = !(tmp || portamentoOn);
      break;
    }
    }
    updatePolyMode();
    break;
  case CC_ENV_MODE: // envelope mode
    allOff();
    switch (value) {
    case 0:
      envOn = false;
      break;
    case 1:
      envOn = true;
      break;
    default:
      envOn = !envOn;
      break;
    }
    updateEnvelopeMode();
    break;
  case CC_ENV_DELAY: // delay
    envDelay = value*2000./127.;
    updateEnvelope();
    break;
  case CC_ENV_HOLD: // hold
    envHold = value*2000./127.;
    updateEnvelope();
    break;
  case CC_ENV_DECAY: // decay
    envDecay = value*2000./127.;
    updateEnvelope();
    break;
  case CC_ENV_SUSTAIN: // sustain
    envSustain = value*2000./127.;
    updateEnvelope();
    break;
  case CC_PULSE_WIDTH: // pulse width
    pwmLfoRate = (10/(1+exp(-S_CURVE*(value-64))));
    updatePwmLFO();
    break;
  case CC_PB_RANGE: // pitch range in semitones
    pitchScale = 12./value;
    break;
  case CC_SUSTAIN: // sustain/damper pedal
    if (value > 63) sustainPressed = true;
    else {
      sustainPressed = false;
      Oscillator *o=oscs, *end=oscs+NVOICES;
      do {
        if (o->note != -1 && !notesFind(notesPressed,o->note)) oscOff(*o);
      } while (++o < end);
    }
    break;
  case CC_FLT_LFO_RATE:
    fltLfoRate = (25/(1+exp(-S_CURVE*(value-64))));
    updateFilterLFO();
    break;
  case CC_FLT_LFO_DEPTH:
    fltLfoDepth = value * DIV127;
    updateFilterLFO();
    break;
  case CC_PITCH_LFO_RATE:
    pitchLfoRate = (20/(1+exp(-S_CURVE*(value-64))));
    updatePitchLFO();
    break;
  case CC_PITCH_LFO_DEPTH:
    pitchLfoDepth = (0.3/(1+exp(-S_CURVE*(value-64))));
    updatePitchLFO();
    break;
  case CC_FLT_ENV_ATK:
    fltEnvAttack = value * DIV127 * 2000; //0-1000ms
    updateFilterEnvelope();
    break;
  case CC_FLT_ENV_DECAY:
    fltEnvDecay = value * DIV127 * 2000 + 5; //5-1005ms
    updateFilterEnvelope();
    break;
  case CC_FLT_ENV_SUSTAIN:
    fltEnvSustain = value * DIV127; //0-1
    updateFilterEnvelope();
    break;
  case CC_FLT_ENV_REL:
    fltEnvRelease = value * DIV127 * 2000 +5; //5-1000ms
    updateFilterEnvelope();
    break;
  case CC_FLT_ENV_INVERT:
    fltEnvInvert = !fltEnvInvert;
    updateFilterEnvelopeMode();
    break;
  case CC_FLT_ENV_DEPTH:
    fltEnvDepth = value * DIV127;
    updateFilterEnvelopeMode();
    break;
  case CC_PORTAMENTO: // portamento on/off
    if (polyOn) break;
    if (value > 63) {
      portamentoOn = true;
      if (oscs->note != -1) portamentoPos = oscs->note;
    }
    else portamentoOn = false;
    break;
  case CC_PORTAMENTO_CONTROL: // portamento control (start note)
    portamentoPos = value;
    break;
  case CC_RESET_ALL: // controller reset
    resetAll();
    break;
  case CC_ALL_NOTES_OFF: // all notes off
    allOff();
    break;
  case CC_OMNI_OFF: // omni off
    allOff();
    omniOn = false;
    break;
  case CC_OMNI_ON: // omni on
    allOff();
    omniOn = true;
    break;
  case CC_MONO_ON: // mono
    polyOn = false;
    portamentoOn = false;
    updatePolyMode();
    break;
  case CC_POLY_ON: // poly
    polyOn = true;
    portamentoOn = false;
    updatePolyMode();
    break;
  case CC_OSC1_PROGRAM:
    if (value < NPROGS) {
      if (value != currentProgram) {
        currentProgram = value;
        updateProgram();
      }
    }
    break;
  case CC_OSC2_PROGRAM:
    if (value < NPROGS) {
      if (value != currentProgram) {
        currentOsc2Program = value;
        updateOsc2Program();
      }
    }
    break;
  case CC_OSC2_OCTAVE:
    osc2Octave = -24 + round((value * DIV127) * 48);
    updatePitch();
    break;
  case CC_OSC2_DETUNE:
    osc2Detune = (-64 + value) / 6;
    updatePitch();
    break;
  case CC_OSC_BALANCE:
    oscBalance = value * DIV127;
    updateOscBalance();
    break;
  case CC_SELECT_PRESET:
    if (value <= NUM_PRESETS){
      selectedPreset = value;  
    }
    break;
  case CC_LOAD_PRESET:
    if (selectedPreset <= NUM_PRESETS){
      loadPreset(selectedPreset);
    }
    break;
  case CC_SAVE_PRESET:
    if (selectedPreset <= NUM_PRESETS){
      savePreset(selectedPreset);
    }
    break;
  case CC_CHORUS_TOGGLE:
    if (value == 0) chorusOn = false;
    else chorusOn = true;
    updatePan();
    break;   
  case CC_FILTER_DRIVE:
    filtDrive = 1 + (value * DIV127 * 9);
    updateFilter();
  default:
#if SYNTH_DEBUG > 0
    SYNTH_SERIAL.print("Unhandled Control Change: channel ");
    SYNTH_SERIAL.print(channel);
    SYNTH_SERIAL.print(", control ");
    SYNTH_SERIAL.print(control);
    SYNTH_SERIAL.print(", value ");
    SYNTH_SERIAL.println(value);
#endif
    break;
  }    
#if 1 //0
  SYNTH_SERIAL.print("Control Change: channel ");
  SYNTH_SERIAL.print(channel);
  SYNTH_SERIAL.print(", control ");
  SYNTH_SERIAL.print(control);
  SYNTH_SERIAL.print(", value ");
  SYNTH_SERIAL.println(value);
#endif
}

void OnPitchChange(uint8_t channel, int pitch) {
  if (!omniOn && channel != SYNTH_MIDICHANNEL) return;

#if SYNTH_DEBUG > 1
  SYNTH_SERIAL.print("PitchChange: channel ");
  SYNTH_SERIAL.print(channel);
  SYNTH_SERIAL.print(", pitch ");
  SYNTH_SERIAL.println(pitch);
#endif

  if (pitch == 8192)
    pitchBend = 1;
  else
    pitchBend = 1+(pitch-8192)/8192.;

//  pitchBend = pitch/8192.;
  
  updatePitch();
}

void OnProgramChange(uint8_t channel, uint8_t program) {
}

void OnAfterTouch(uint8_t channel, uint8_t pressure) {
  if (!omniOn && channel!=SYNTH_MIDICHANNEL) return;

#if SYNTH_DEBUG > 0
  SYNTH_SERIAL.print("AfterTouch: channel ");
  SYNTH_SERIAL.print(channel);
  SYNTH_SERIAL.print(", pressure ");
  SYNTH_SERIAL.println(pressure);
#endif
}

void OnSysEx( const uint8_t *data, uint16_t length, bool complete) {
#if SYNTH_DEBUG > 0
  SYNTH_SERIAL.print("SysEx: length ");
  SYNTH_SERIAL.print(length);
  SYNTH_SERIAL.print(", complete ");
  SYNTH_SERIAL.println(complete);
#endif
}

void OnRealTimeSystem(uint8_t realtimebyte) {
#if SYNTH_DEBUG > 0
  SYNTH_SERIAL.print("RealTimeSystem: ");
  SYNTH_SERIAL.println(realtimebyte);
#endif
}

void OnTimeCodeQFrame(uint16_t data)
{
#if SYNTH_DEBUG > 0
  SYNTH_SERIAL.print("TimeCodeQuarterFrame: ");
  SYNTH_SERIAL.println(data);
#endif
}
        
//////////////////////////////////////////////////////////////////////
// Debugging functions
//////////////////////////////////////////////////////////////////////
#if SYNTH_DEBUG > 0
float   statsCpu = 0;
uint8_t statsMem = 0;

void oscDump(uint8_t idx) {
  SYNTH_SERIAL.print("Oscillator ");
  SYNTH_SERIAL.print(idx);
  oscDump(oscs[idx]);
}

void oscDump(const Oscillator& o) {
  SYNTH_SERIAL.print(" note=");
  SYNTH_SERIAL.print(o.note);
  SYNTH_SERIAL.print(", velocity=");
  SYNTH_SERIAL.println(o.velocity);  
}

inline void notesDump(int8_t* notes) {
  for (uint8_t i=0; i<NVOICES; ++i) {
    SYNTH_SERIAL.print(' ');
    SYNTH_SERIAL.print(notes[i]);
  }
  SYNTH_SERIAL.println();
}

inline void printResources( float cpu, uint8_t mem) {
  SYNTH_SERIAL.print( "CPU Usage: ");
  SYNTH_SERIAL.print(cpu);
  SYNTH_SERIAL.print( "%, Memory: ");
  SYNTH_SERIAL.println(mem);
}

void performanceCheck() {
  static unsigned long last = 0;
  unsigned long now = millis();
  if ((now-last)>1000) {
    last = now;
    float cpu = AudioProcessorUsageMax();
    uint8_t mem = AudioMemoryUsageMax();
    if( (statsMem!=mem) || fabs(statsCpu-cpu)>1) {
      printResources( cpu, mem);
    }   
    AudioProcessorUsageMaxReset();
    AudioMemoryUsageMaxReset();
    last = now;
    statsCpu = cpu;
    statsMem = mem;
  }
}

void printInfo() {
  SYNTH_SERIAL.println();
  SYNTH_SERIAL.print("Master Volume:        ");
  SYNTH_SERIAL.println(masterVolume);
  SYNTH_SERIAL.print("Current Program:      ");
  SYNTH_SERIAL.println(currentProgram);
  SYNTH_SERIAL.print("Poly On:              ");
  SYNTH_SERIAL.println(polyOn);
  SYNTH_SERIAL.print("Omni On:              ");
  SYNTH_SERIAL.println(omniOn);
  SYNTH_SERIAL.print("Velocity On:          ");
  SYNTH_SERIAL.println(velocityOn);
  SYNTH_SERIAL.println();
  SYNTH_SERIAL.print("Sustain Pressed:      ");
  SYNTH_SERIAL.println(sustainPressed);
  SYNTH_SERIAL.print("Channel Volume:       ");
  SYNTH_SERIAL.println(channelVolume);
  SYNTH_SERIAL.print("Panorama:             ");
  SYNTH_SERIAL.println(panorama);
  SYNTH_SERIAL.print("PWM Rate:             ");
  SYNTH_SERIAL.println(pwmLfoRate);
  SYNTH_SERIAL.print("Pitch Bend:           ");
  SYNTH_SERIAL.println(pitchBend);
  SYNTH_SERIAL.println();
  SYNTH_SERIAL.print("Filter Mode:          ");
  SYNTH_SERIAL.println(filterMode);
  SYNTH_SERIAL.print("Filter Frequency:     ");
  SYNTH_SERIAL.println(filtFreq);
  SYNTH_SERIAL.print("Filter Resonance:     ");
  SYNTH_SERIAL.println(filtReso);
  SYNTH_SERIAL.print("Filter Attenuation:   ");
  SYNTH_SERIAL.println(filtAtt);
  SYNTH_SERIAL.println();
  SYNTH_SERIAL.print("Envelope On:          ");
  SYNTH_SERIAL.println(envOn);
  SYNTH_SERIAL.print("Envelope Delay:       ");
  SYNTH_SERIAL.println(envDelay);
  SYNTH_SERIAL.print("Envelope Attack:      ");
  SYNTH_SERIAL.println(envAttack);
  SYNTH_SERIAL.print("Envelope Hold:        ");
  SYNTH_SERIAL.println(envHold);
  SYNTH_SERIAL.print("Envelope Decay:       ");
  SYNTH_SERIAL.println(envDecay);
  SYNTH_SERIAL.print("Envelope Sustain:     ");
  SYNTH_SERIAL.println(envSustain);
  SYNTH_SERIAL.print("Envelope Release:     ");
  SYNTH_SERIAL.println(envRelease);
  SYNTH_SERIAL.println();
  SYNTH_SERIAL.print("Portamento On:        ");
  SYNTH_SERIAL.println(portamentoOn);
  SYNTH_SERIAL.print("Portamento Time:      ");
  SYNTH_SERIAL.println(portamentoTime);
  SYNTH_SERIAL.print("Portamento Step:      ");
  SYNTH_SERIAL.println(portamentoStep);
  SYNTH_SERIAL.print("Portamento Direction: ");
  SYNTH_SERIAL.println(portamentoDir);
  SYNTH_SERIAL.print("Portamento Position:  ");
  SYNTH_SERIAL.println(portamentoPos);
}

void selectCommand(char c) {
  switch (c) {
  case '\r':
    SYNTH_SERIAL.println();
    break;
  case 'b':
    // print voice statistics
    SYNTH_SERIAL.print("Notes Pressed:");
    notesDump(notesPressed);
    SYNTH_SERIAL.print("Notes On:     ");
    notesDump(notesOn);
    break;
  case 'o':
    // print oscillator status
    for (uint8_t i=0; i<NVOICES; ++i)
        oscDump(i);
    break;
  case 's':
    // print cpu and mem usage
    printResources(statsCpu,statsMem);
    break;
  case 'r':
    // reset parameters
    resetAll();
    break;
  case 'i':
    // print info
    printInfo();
    break;
  case '\t':
    // reboot Teensy
    *(uint32_t*)0xE000ED0C = 0x5FA0004;
    break;
  case ' ':
    // send note off
    allOff();
    break;
  case 'l':
    //load preset from slot 0
    loadPreset(0);
    break;
  case 'p':
    //save preset to slot 0
    savePreset(0);
    break;
  default:
    break;
  }  
}

#endif

#include "saw.h"

//////////////////////////////////////////////////////////////////////
// setup() and loop()
//////////////////////////////////////////////////////////////////////
void setup() {
#if SYNTH_DEBUG > 0
  SYNTH_SERIAL.begin(115200);
#endif
  
  AudioMemory(AMEMORY);
  sgtl5000_1.enable();
  sgtl5000_1.volume(masterVolume);
  sgtl5000_1.lineOutLevel(29,29);
  sgtl5000_1.unmuteLineout();

  {
    Oscillator *o=oscs,*end=oscs+NVOICES;
    do {
      o->wf->arbitraryWaveform(reinterpret_cast<const int16_t*>(saw),0);
      o->wf2->arbitraryWaveform(reinterpret_cast<const int16_t*>(saw),0);
      o->flt_sum->gain(0,1);
      o->flt_sum->gain(1,1);
      o->filt->octaveControl(6);
      o->wf_sum->gain(0,0.5);
      o->wf_sum->gain(1,0.5);
    } while(++o < end);
  }
  
  resetAll();
  updateProgram();
  
  flt_env_carrier.amplitude(0);
  pwm_lfo.amplitude(0.9);

  int oscHighpass = 30;
  biquad1.setHighpass(0,oscHighpass,0.7071);
  biquad1b.setHighpass(0,oscHighpass,0.7071);
  biquad2.setHighpass(0,oscHighpass,0.7071);
  biquad2b.setHighpass(0,oscHighpass,0.7071);
  biquad3.setHighpass(0,oscHighpass,0.7071);
  biquad3b.setHighpass(0,oscHighpass,0.7071);
  biquad4.setHighpass(0,oscHighpass,0.7071);
  biquad4b.setHighpass(0,oscHighpass,0.7071);
  biquad5.setHighpass(0,oscHighpass,0.7071);
  biquad5b.setHighpass(0,oscHighpass,0.7071);
  biquad6.setHighpass(0,oscHighpass,0.7071);
  biquad6b.setHighpass(0,oscHighpass,0.7071);
  biquad7.setHighpass(0,oscHighpass,0.7071);
  biquad7b.setHighpass(0,oscHighpass,0.7071);
  biquad8.setHighpass(0,oscHighpass,0.7071);
  biquad8b.setHighpass(0,oscHighpass,0.7071); 
  
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleVelocityChange(OnAfterTouchPoly);
  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandlePitchChange(OnPitchChange);
  usbMIDI.setHandleProgramChange(OnProgramChange);
  usbMIDI.setHandleAfterTouch(OnAfterTouch);
  usbMIDI.setHandleSysEx(OnSysEx);
  //usbMIDI.setHandleRealTimeSystem(OnRealTimeSystem);
  //usbMIDI.setHandleTimeCodeQuarterFrame(OnTimeCodeQFrame);
if (SERIALMIDI) {
  MIDI.begin(SYNTH_MIDICHANNEL);
  MIDI.setHandleNoteOff(OnNoteOff);
  MIDI.setHandleNoteOn(OnNoteOn);
  MIDI.setHandleAfterTouchPoly(OnAfterTouchPoly);
  MIDI.setHandleControlChange(OnControlChange);
  MIDI.setHandlePitchBend(OnPitchChange);
  MIDI.setHandleProgramChange(OnProgramChange);
  MIDI.setHandleAfterTouchChannel(OnAfterTouch);
  // the following functions need a different callback signature but they are
  // not used anyways, so...
  //MIDI.setHandleSystemExclusive(OnSysEx);
  //MIDI.setHandleTimeCodeQuarterFrame(OnTimeCodeQFrame);
}

  delay(1000);

#if SYNTH_DEBUG > 0
  SYNTH_SERIAL.println();
  SYNTH_SERIAL.println("TeensySynth v0.1");
#ifdef USB_MIDI
  SYNTH_SERIAL.println("USB_MIDI enabled");
#else
  SYNTH_SERIAL.println("UART_MIDI enabled");
#endif // USB_MIDI
#endif // SYNTH_DEBUG

  //initialize default presets
  for (int presetno=0; presetno < NUM_PRESETS; presetno++){
    presets[presetno] = {
      currentProgram, currentOsc2Program, polyOn, omniOn, velocityOn, channelVolume, oscBalance, panorama, pitchScale, octCorr, 
      osc2Octave, osc2Detune, filterMode, filtFreq, filtReso, filtAtt, filtDrive, fltLfoDepth, fltLfoRate, pitchLfoRate, pitchLfoDepth, pwmLfoRate, envOn,
      envDelay, envAttack, envHold, envDecay, envSustain, envRelease, fltEnvOn, fltEnvInvert, fltEnvDelay, fltEnvAttack, fltEnvHold, fltEnvDecay,
      fltEnvSustain, fltEnvRelease, fltEnvDepth, portamentoOn, portamentoTime
    };
  }

  if (!checkEeprom() || FORCE_INITIALIZE_PRESETS) { 
    #if SYNTH_DEBUG > 0
      SYNTH_SERIAL.println ("No preset data found, saving initial presets to EEPROM");
    #endif
    EEPROM.put(1,presets);
    EEPROM.write(0,42); //just a number so we know that our preset data is there
    #if SYNTH_DEBUG > 0
      SYNTH_SERIAL.println ("Save complete");
    #endif

  } else {
    #if SYNTH_DEBUG > 0
      SYNTH_SERIAL.println ("Preset data found from EEPROM, loading it");
    #endif
    loadPresetsFromEeprom();    
    #if SYNTH_DEBUG > 0
      SYNTH_SERIAL.println ("Load complete");
    #endif
    loadPreset(0);
  }

}

void loop() {
#ifdef USB_MIDI
  usbMIDI.read();
#endif
if (SERIALMIDI) MIDI.read();

  updateMasterVolume();
  updatePortamento();  

#if SYNTH_DEBUG > 0
  performanceCheck();
  while (SYNTH_SERIAL.available())
    selectCommand(SYNTH_SERIAL.read());
#endif
}
