#ifndef SYNTHARCH_H
#define SYNTHARCH_H

#include <Audio.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   pitch_lfo;          //xy=127,468
AudioSynthWaveformSine   pwm_lfo;          //xy=127,517
AudioSynthWaveformSine   flt_lfo;        //xy=128,422
AudioSynthWaveformDc     flt_env_carrier; //xy=146,374
AudioSynthWaveformModulated waveform1;      //xy=429,139
AudioSynthWaveformModulated waveform2;      //xy=431,270
AudioSynthWaveformModulated waveform3;      //xy=433,365
AudioSynthWaveformModulated waveform4;      //xy=444,459
AudioSynthWaveformModulated waveform5;      //xy=461,541
AudioSynthWaveformModulated waveform7;      //xy=461,719
AudioSynthWaveformModulated waveform6;      //xy=462,622
AudioSynthWaveformModulated waveform8;      //xy=464,811
AudioEffectEnvelope      flt_env_8;      //xy=489,853
AudioEffectEnvelope      flt_env_4;      //xy=491,498
AudioEffectEnvelope      flt_env_6;      //xy=491,662
AudioEffectEnvelope      flt_env_7;      //xy=494,756
AudioEffectEnvelope      flt_env_5;      //xy=495,581
AudioEffectEnvelope      flt_env_1;      //xy=497,185
AudioEffectEnvelope      flt_env_3;      //xy=502,407
AudioEffectEnvelope      flt_env_2;      //xy=506,310
AudioMixer4              flt_sum_1;      //xy=651,169
AudioMixer4              flt_sum_2;      //xy=651,287
AudioMixer4              flt_sum_3;      //xy=649,837
AudioMixer4              flt_sum_4;      //xy=651,482
AudioMixer4              flt_sum_5;      //xy=651,646
AudioMixer4              flt_sum_6;      //xy=655,387
AudioMixer4              flt_sum_7;      //xy=654,740
AudioMixer4              flt_sum_8;      //xy=655,565
AudioFilterStateVariable filter7;        //xy=791,739
AudioFilterStateVariable filter8;        //xy=791,809
AudioFilterStateVariable filter6;        //xy=792,643
AudioFilterStateVariable filter5;        //xy=795,565
AudioFilterStateVariable filter4;        //xy=798,483
AudioFilterStateVariable filter2;        //xy=799,289
AudioFilterStateVariable filter3;        //xy=801,385
AudioFilterStateVariable filter1;        //xy=802,166
AudioMixer4              mixer1;         //xy=979,220
AudioMixer4              mixer2;         //xy=979,280
AudioMixer4              mixer3;         //xy=979,340
AudioMixer4              mixer4;         //xy=979,400
AudioMixer4              mixer5;         //xy=979,460
AudioMixer4              mixer6;         //xy=979,520
AudioMixer4              mixer7;         //xy=979,580
AudioMixer4              mixer8;         //xy=979,640
AudioEffectEnvelope      envelope1;      //xy=1179,220
AudioEffectEnvelope      envelope2;      //xy=1179,280
AudioEffectEnvelope      envelope3;      //xy=1179,340
AudioEffectEnvelope      envelope4;      //xy=1179,400
AudioEffectEnvelope      envelope5;      //xy=1179,460
AudioEffectEnvelope      envelope6;      //xy=1179,520
AudioEffectEnvelope      envelope7;      //xy=1179,580
AudioEffectEnvelope      envelope8;      //xy=1179,640
AudioMixer4              envmixer1;      //xy=1439,250
AudioMixer4              envmixer2;      //xy=1439,370
AudioMixer4              envmixer3;      //xy=1439,490
AudioMixer4              envmixer4;      //xy=1439,610
AudioMixer4              mixerL;         //xy=1699,310
AudioMixer4              mixerR;         //xy=1699,550
AudioEffectFlange        flangerL;       //xy=1839,310
AudioEffectFlange        flangerR;       //xy=1839,550
AudioOutputI2S           i2s1;           //xy=1989,430
AudioConnection          patchCord1(pitch_lfo, 0, waveform1, 0);
AudioConnection          patchCord2(pitch_lfo, 0, waveform2, 0);
AudioConnection          patchCord3(pitch_lfo, 0, waveform3, 0);
AudioConnection          patchCord4(pitch_lfo, 0, waveform4, 0);
AudioConnection          patchCord5(pitch_lfo, 0, waveform5, 0);
AudioConnection          patchCord6(pitch_lfo, 0, waveform6, 0);
AudioConnection          patchCord7(pitch_lfo, 0, waveform7, 0);
AudioConnection          patchCord8(pitch_lfo, 0, waveform8, 0);
AudioConnection          patchCord9(pwm_lfo, 0, waveform1, 1);
AudioConnection          patchCord10(pwm_lfo, 0, waveform2, 1);
AudioConnection          patchCord11(pwm_lfo, 0, waveform3, 1);
AudioConnection          patchCord12(pwm_lfo, 0, waveform4, 1);
AudioConnection          patchCord13(pwm_lfo, 0, waveform5, 1);
AudioConnection          patchCord14(pwm_lfo, 0, waveform6, 1);
AudioConnection          patchCord15(pwm_lfo, 0, waveform7, 1);
AudioConnection          patchCord16(pwm_lfo, 0, waveform8, 1);
AudioConnection          patchCord17(flt_lfo, 0, flt_sum_1, 1);
AudioConnection          patchCord18(flt_lfo, 0, flt_sum_2, 1);
AudioConnection          patchCord19(flt_lfo, 0, flt_sum_3, 1);
AudioConnection          patchCord20(flt_lfo, 0, flt_sum_4, 1);
AudioConnection          patchCord21(flt_lfo, 0, flt_sum_5, 1);
AudioConnection          patchCord22(flt_lfo, 0, flt_sum_6, 1);
AudioConnection          patchCord23(flt_lfo, 0, flt_sum_7, 1);
AudioConnection          patchCord24(flt_lfo, 0, flt_sum_8, 1);
AudioConnection          patchCord25(flt_env_carrier, flt_env_1);
AudioConnection          patchCord26(flt_env_carrier, flt_env_2);
AudioConnection          patchCord27(flt_env_carrier, flt_env_3);
AudioConnection          patchCord28(flt_env_carrier, flt_env_4);
AudioConnection          patchCord29(flt_env_carrier, flt_env_5);
AudioConnection          patchCord30(flt_env_carrier, flt_env_6);
AudioConnection          patchCord31(flt_env_carrier, flt_env_7);
AudioConnection          patchCord32(flt_env_carrier, flt_env_8);
AudioConnection          patchCord33(waveform1, 0, filter1, 0);
AudioConnection          patchCord34(waveform1, 0, mixer1, 3);
AudioConnection          patchCord35(waveform2, 0, filter2, 0);
AudioConnection          patchCord36(waveform2, 0, mixer2, 3);
AudioConnection          patchCord37(waveform3, 0, filter3, 0);
AudioConnection          patchCord38(waveform3, 0, mixer3, 3);
AudioConnection          patchCord39(waveform4, 0, filter4, 0);
AudioConnection          patchCord40(waveform4, 0, mixer4, 3);
AudioConnection          patchCord41(waveform5, 0, filter5, 0);
AudioConnection          patchCord42(waveform5, 0, mixer5, 3);
AudioConnection          patchCord43(waveform7, 0, filter7, 0);
AudioConnection          patchCord44(waveform7, 0, mixer7, 3);
AudioConnection          patchCord45(waveform6, 0, filter6, 0);
AudioConnection          patchCord46(waveform6, 0, mixer6, 3);
AudioConnection          patchCord47(waveform8, 0, filter8, 0);
AudioConnection          patchCord48(waveform8, 0, mixer8, 3);
AudioConnection          patchCord49(flt_env_8, 0, flt_sum_8, 0);
AudioConnection          patchCord50(flt_env_4, 0, flt_sum_4, 0);
AudioConnection          patchCord51(flt_env_6, 0, flt_sum_6, 0);
AudioConnection          patchCord52(flt_env_7, 0, flt_sum_7, 0);
AudioConnection          patchCord53(flt_env_5, 0, flt_sum_5, 0);
AudioConnection          patchCord54(flt_env_1, 0, flt_sum_1, 0);
AudioConnection          patchCord55(flt_env_3, 0, flt_sum_3, 0);
AudioConnection          patchCord56(flt_env_2, 0, flt_sum_2, 0);
AudioConnection          patchCord57(flt_sum_1, 0, filter1, 1);
AudioConnection          patchCord58(flt_sum_2, 0, filter2, 1);
AudioConnection          patchCord59(flt_sum_3, 0, filter3, 1);
AudioConnection          patchCord60(flt_sum_4, 0, filter4, 1);
AudioConnection          patchCord61(flt_sum_5, 0, filter5, 1);
AudioConnection          patchCord62(flt_sum_6, 0, filter6, 1);
AudioConnection          patchCord63(flt_sum_7, 0, filter7, 1);
AudioConnection          patchCord64(flt_sum_8, 0, filter8, 1);
AudioConnection          patchCord65(filter7, 0, mixer7, 0);
AudioConnection          patchCord66(filter7, 1, mixer7, 1);
AudioConnection          patchCord67(filter7, 2, mixer7, 2);
AudioConnection          patchCord68(filter8, 0, mixer8, 0);
AudioConnection          patchCord69(filter8, 1, mixer8, 1);
AudioConnection          patchCord70(filter8, 2, mixer8, 2);
AudioConnection          patchCord71(filter6, 0, mixer6, 0);
AudioConnection          patchCord72(filter6, 1, mixer6, 1);
AudioConnection          patchCord73(filter6, 2, mixer6, 2);
AudioConnection          patchCord74(filter5, 0, mixer5, 0);
AudioConnection          patchCord75(filter5, 1, mixer5, 1);
AudioConnection          patchCord76(filter5, 2, mixer5, 2);
AudioConnection          patchCord77(filter4, 0, mixer4, 0);
AudioConnection          patchCord78(filter4, 1, mixer4, 1);
AudioConnection          patchCord79(filter4, 2, mixer4, 2);
AudioConnection          patchCord80(filter2, 0, mixer2, 0);
AudioConnection          patchCord81(filter2, 1, mixer2, 1);
AudioConnection          patchCord82(filter2, 2, mixer2, 2);
AudioConnection          patchCord83(filter3, 0, mixer3, 0);
AudioConnection          patchCord84(filter3, 1, mixer3, 1);
AudioConnection          patchCord85(filter3, 2, mixer3, 2);
AudioConnection          patchCord86(filter1, 0, mixer1, 0);
AudioConnection          patchCord87(filter1, 1, mixer1, 1);
AudioConnection          patchCord88(filter1, 2, mixer1, 2);
AudioConnection          patchCord89(mixer1, envelope1);
AudioConnection          patchCord90(mixer1, 0, envmixer1, 2);
AudioConnection          patchCord91(mixer2, envelope2);
AudioConnection          patchCord92(mixer2, 0, envmixer1, 3);
AudioConnection          patchCord93(mixer3, envelope3);
AudioConnection          patchCord94(mixer3, 0, envmixer2, 2);
AudioConnection          patchCord95(mixer4, envelope4);
AudioConnection          patchCord96(mixer4, 0, envmixer2, 3);
AudioConnection          patchCord97(mixer5, envelope5);
AudioConnection          patchCord98(mixer5, 0, envmixer3, 2);
AudioConnection          patchCord99(mixer6, envelope6);
AudioConnection          patchCord100(mixer6, 0, envmixer3, 3);
AudioConnection          patchCord101(mixer7, envelope7);
AudioConnection          patchCord102(mixer7, 0, envmixer4, 2);
AudioConnection          patchCord103(mixer8, envelope8);
AudioConnection          patchCord104(mixer8, 0, envmixer4, 3);
AudioConnection          patchCord105(envelope1, 0, envmixer1, 0);
AudioConnection          patchCord106(envelope2, 0, envmixer1, 1);
AudioConnection          patchCord107(envelope3, 0, envmixer2, 0);
AudioConnection          patchCord108(envelope4, 0, envmixer2, 1);
AudioConnection          patchCord109(envelope5, 0, envmixer3, 0);
AudioConnection          patchCord110(envelope6, 0, envmixer3, 1);
AudioConnection          patchCord111(envelope7, 0, envmixer4, 0);
AudioConnection          patchCord112(envelope8, 0, envmixer4, 1);
AudioConnection          patchCord113(envmixer1, 0, mixerL, 0);
AudioConnection          patchCord114(envmixer1, 0, mixerR, 0);
AudioConnection          patchCord115(envmixer2, 0, mixerL, 1);
AudioConnection          patchCord116(envmixer2, 0, mixerR, 1);
AudioConnection          patchCord117(envmixer3, 0, mixerL, 2);
AudioConnection          patchCord118(envmixer3, 0, mixerR, 2);
AudioConnection          patchCord119(envmixer4, 0, mixerL, 3);
AudioConnection          patchCord120(envmixer4, 0, mixerR, 3);
AudioConnection          patchCord121(mixerL, flangerL);
AudioConnection          patchCord122(mixerR, flangerR);
AudioConnection          patchCord123(flangerL, 0, i2s1, 0);
AudioConnection          patchCord124(flangerR, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=496,33
// GUItool: end automatically generated code




#endif
