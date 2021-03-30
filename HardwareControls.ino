/* Knob layout */
enum {
  CTL_OSC1,    CTL_OSC2,     CTL_PWM,          CTL_PORTA,     CTL_VOL,
  CTL_OSC_BAL, CTL_OSC2_OCT, CTL_OSC2_FT,      CTL_LFO1_RATE, CTL_LFO1_DEPTH, //CHORUS SWITCH
  CTL_AMP_ATK, CTL_AMP_DEC,  CTL_AMP_SUS,      CTL_AMP_REL,   CTL_LFO2_RATE,  CTL_LFO2_DEPTH,
  CTL_FLT_CUT, CTL_FLT_RES,  CTL_FLTENV_DEPTH, CTL_FLT_SUS,   CTL_FLT_DEC,    CTL_FLT_ATK, //whoops, the multiplexer pins were in reverse order. fix it in the software as usual.
  CTL_MODE, CTL_CHORUS
};

int muxChannel[16][4]={
  {0,0,0,0}, //channel 0
  {1,0,0,0}, //channel 1
  {0,1,0,0}, //channel 2
  {1,1,0,0}, //channel 3
  {0,0,1,0}, //channel 4
  {1,0,1,0}, //channel 5
  {0,1,1,0}, //channel 6
  {1,1,1,0}, //channel 7
  {0,0,0,1}, //channel 8
  {1,0,0,1}, //channel 9
  {0,1,0,1}, //channel 10
  {1,1,0,1}, //channel 11
  {0,0,1,1}, //channel 12
  {1,0,1,1}, //channel 13
  {0,1,1,1}, //channel 14
  {1,1,1,1} //channel 15
};
 
int controlPin[4] = {2,3,4,5};

int currentCtlValue[24] = {0};
uint8_t potThreshold[22] = {10}; //thresholds for pot value changes before actually doing anything, helps tackle noisy pots.

int readMux(int ch)
{
  if (ch > 15) {
    for (int i=0; i<4; i++) {
      digitalWrite(controlPin[i],muxChannel[ch-16][i]);    
    }
    delayMicroseconds(5);
    return analogRead(16);
  } else {
    for (int i=0; i<4; i++) {
      digitalWrite(controlPin[i],muxChannel[ch][i]);    
    }
    delayMicroseconds(5);
    return analogRead(14);
  }
}

void updateSynthControl(int ctl, int value){
  switch (ctl) {
    case CTL_OSC1:
    {
      uint8_t newpgm = round((value+1)/(1024/(NPROGS-1)));     
      if (newpgm < NPROGS && newpgm != currentProgram) {
          currentProgram = newpgm;
          updateProgram();
      }
    }
      break;
    case CTL_OSC2:
    {
      uint8_t newpgm = round((value+1)/(1024/(NPROGS-1)));     
      if (newpgm < NPROGS && newpgm != currentOsc2Program) {
          currentOsc2Program = newpgm;
          updateOsc2Program();
      }
    }
      break;
    case CTL_PWM:
      pwmLfoRate = 10 * value / 1023.;
      updatePwmLFO();  
      break;
    case CTL_PORTA:
    {
      float portamentoRange = portamentoStep*portamentoTime;
      portamentoTime = powf((value/101.53),3);
      portamentoStep = portamentoRange/portamentoTime;    
    }
      break;
    case CTL_VOL:
      channelVolume = value/1023.;
      updateVolume();    
      break;
    case CTL_OSC_BAL:
      oscBalance = value/1023.;
      updateOscBalance();    
      break;
    case CTL_OSC2_OCT:
      osc2Octave = -12 + round((value/1024.) * 24);
      updatePitch();    
      break;
    case CTL_OSC2_FT:
      osc2Detune =  value / 6 / 8;
      updatePitch();    
      break;
    case CTL_LFO1_RATE:
      pitchLfoRate = 20*(powf((value/101.53),3)/1023.);
      updatePitchLFO();    
      break;
    case CTL_LFO1_DEPTH:
      pitchLfoDepth = 0.3*(powf((value/101.53),3)/1023.);
      updatePitchLFO();    
      break;
    case CTL_AMP_ATK:
      envAttack = powf((value/101.53),3);
      updateEnvelope();
      break;
    case CTL_AMP_DEC:
      envDecay = powf((value/101.53),3);
      updateEnvelope();    
      break;
    case CTL_FLT_ATK:
      fltEnvAttack = 2*powf((value/101.53),3);
      updateFilterEnvelope();    
      break;
    case CTL_FLT_DEC:
      fltEnvDecay = powf((value/101.53),3);
      updateFilterEnvelope();    
      break;
    case CTL_LFO2_RATE:
      fltLfoRate = 25*(powf((value/101.53),3)/1023.);
      updateFilterLFO();    
      break;
    case CTL_LFO2_DEPTH:
      fltLfoDepth = powf((value/101.53),3)/1023.;
      updateFilterLFO();    
      break;
    case CTL_AMP_SUS:
      envSustain = value/1023.;
      updateEnvelope();    
      break;
    case CTL_AMP_REL:
      envRelease = powf((value/101.53),3);
      updateEnvelope();    
      break;
    case CTL_FLT_SUS:
      fltEnvSustain = value / 1023.; //0-1
      updateFilterEnvelope();    
      break;
    case CTL_FLTENV_DEPTH:
      fltEnvDepth = value / 1023.;
      updateFilterEnvelopeMode();    
      break;
    case CTL_FLT_CUT:
      filtFreq = 80+12*powf((value/101.53),3);
      updateFilter();
      break;
    case CTL_FLT_RES:
      filtReso = (value / 1024.) * 1.2;
      updateFilter();
      break;
    case CTL_MODE:
      switch (value) {
        case 0:
          polyOn = true;
          portamentoOn = false;
          velocityOn = true;
          break;
        case 1:
          polyOn = false;
          portamentoOn = true;
          velocityOn = false;
          break;
      }
      updatePolyMode();          
      break;
    case CTL_CHORUS:
      if (value == 0) chorusOn = false;
      else chorusOn = true;
      updatePan();    
      break;
  }
}

void checkHwControlValues(uint8_t update)
{
  for (int i=0; i<22; i++) {
    int ctlValue = readMux(i);
    if (ctlValue < 15) ctlValue = 0;
    if ((ctlValue == 1023 && currentCtlValue[i] != 1023) || ctlValue > currentCtlValue[i]+potThreshold[i] || ctlValue < currentCtlValue[i]-potThreshold[i]) {
      #if SYNTH_DEBUG > 1
        SYNTH_SERIAL.print("Pot update, num: ");
        SYNTH_SERIAL.print(i);
        SYNTH_SERIAL.print(", value: ");
        SYNTH_SERIAL.print(ctlValue);
        SYNTH_SERIAL.print(" currentvalue: ");
        SYNTH_SERIAL.print(currentCtlValue[i]);
        SYNTH_SERIAL.print(" pot threshold: ");
        SYNTH_SERIAL.println(potThreshold[i]);
      #endif
      if (update == 1) {
        if (ctlValue < currentCtlValue[i]+50 && ctlValue > currentCtlValue[i]-50) {
          currentCtlValue[i] = ctlValue;
          updateSynthControl(i, ctlValue);
        }
      } else currentCtlValue[i] = ctlValue;
    }
  }
  for (int i=22; i<24; i++) {
    int ctlValue = (i == 22) ? !digitalRead(9) : digitalRead(17); //wires on switch in pin9 are inverted...
    if (ctlValue != currentCtlValue[i]) {
      #if SYNTH_DEBUG > 1
        SYNTH_SERIAL.print("SW update, num: ");
        SYNTH_SERIAL.print(i);
        SYNTH_SERIAL.print(", value: ");
        SYNTH_SERIAL.println(ctlValue);
      #endif
      currentCtlValue[i] = ctlValue;
      if (update == 1) updateSynthControl(i, ctlValue);
    }
  }
}

void setupMux()
{
  memset(potThreshold,8,sizeof(potThreshold)); //initialize pot threshold array
  potThreshold[4] = 12; //pot 4 seems to be very noisy
}
