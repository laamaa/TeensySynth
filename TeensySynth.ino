#include <Audio.h>
#include <EEPROM.h>
#include <MIDI.h>
#include "effect_ensemble.h"

//Defines and global variables moved to a separate file
#include "TeensySynth.h" 

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
    o->filt->inputDrive(filtDrive);
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
  filtDrive = 1.;

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
  //float norm  = (polyOn && !portamentoOn) ? GAIN_POLY : GAIN_MONO;
  float norm  = (polyOn) ? GAIN_POLY : GAIN_MONO;
  float left=norm, right=norm;
  if (panorama < 0.5) right *= 2*panorama;
  else left *= 2*(1-panorama);
/*  if (chorusOn) {
    left = left/2;
    right = right/2;
  } */
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

//Midi handlers moved to a separate file, see MidiHandlers.ino
        
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

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT); 
  pinMode(5,OUTPUT);

  /*Initialize hw controls*/
  setupMux();
  checkHwControlValues(0);
  
  AudioMemory(AMEMORY);
  sgtl5000_1.enable();
  sgtl5000_1.volume(masterVolume);
  sgtl5000_1.lineOutLevel(13,13);
  sgtl5000_1.unmuteLineout();
  sgtl5000_1.audioPostProcessorEnable();
  sgtl5000_1.autoVolumeControl(1,1,1,0,18,6);
  sgtl5000_1.autoVolumeEnable();
  

  {
    Oscillator *o=oscs,*end=oscs+NVOICES;
    do {
      o->wf->arbitraryWaveform(reinterpret_cast<const int16_t*>(saw),0);
      o->wf2->arbitraryWaveform(reinterpret_cast<const int16_t*>(saw),0);
      o->flt_sum->gain(0,1);
      o->flt_sum->gain(1,1);
      o->filt->octaveControl(6);
      o->filt->interpolationMethod(LADDER_FILTER_INTERPOLATION_FIR_POLY);
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

  const int choruslowpass=12000;
  enbiquadpre.setLowpass(0,choruslowpass,0.7071);
  enbiquad1.setLowpass(0,choruslowpass,0.7071); 
  enbiquad2.setLowpass(0,choruslowpass,0.7071);
 
  
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

  

#if SYNTH_DEBUG > 0
  delay(1000);
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
    loadPreset(1);
  }

}

void loop() {
#ifdef USB_MIDI
  usbMIDI.read();
#endif
if (SERIALMIDI) MIDI.read();

  updateMasterVolume();
  updatePortamento();
  checkHwControlValues(1);

#if SYNTH_DEBUG > 0
  performanceCheck();
  while (SYNTH_SERIAL.available())
    selectCommand(SYNTH_SERIAL.read());
#endif
}
