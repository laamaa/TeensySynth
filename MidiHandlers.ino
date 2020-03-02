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
    envSustain = value/127.;
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
