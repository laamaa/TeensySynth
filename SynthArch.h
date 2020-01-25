#ifndef SYNTHARCH_H
#define SYNTHARCH_H

#include <Audio.h>

// Audio architecture generated with
// http://www.pjrc.com/teensy/gui/

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc1;            //xy=155,364
AudioEffectEnvelope      flt_envelope;   //xy=313,364
AudioSynthWaveformSine   flt_lfo;        //xy=328,412
AudioEffectMultiply      multiply1;      //xy=490,390
AudioSynthWaveform       waveform1;      //xy=642,218
AudioSynthWaveform       waveform2;      //xy=642,278
AudioSynthWaveform       waveform3;      //xy=642,338
AudioSynthWaveform       waveform4;      //xy=642,398
AudioSynthWaveform       waveform5;      //xy=642,458
AudioSynthWaveform       waveform6;      //xy=642,518
AudioSynthWaveform       waveform7;      //xy=642,578
AudioSynthWaveform       waveform8;      //xy=642,638
AudioFilterStateVariable filter1;        //xy=822,218
AudioFilterStateVariable filter2;        //xy=822,278
AudioFilterStateVariable filter3;        //xy=822,338
AudioFilterStateVariable filter4;        //xy=822,398
AudioFilterStateVariable filter5;        //xy=822,458
AudioFilterStateVariable filter6;        //xy=822,518
AudioFilterStateVariable filter7;        //xy=822,578
AudioFilterStateVariable filter8;        //xy=822,638
AudioMixer4              mixer1;         //xy=1002,218
AudioMixer4              mixer2;         //xy=1002,278
AudioMixer4              mixer3;         //xy=1002,338
AudioMixer4              mixer4;         //xy=1002,398
AudioMixer4              mixer5;         //xy=1002,458
AudioMixer4              mixer6;         //xy=1002,518
AudioMixer4              mixer7;         //xy=1002,578
AudioMixer4              mixer8;         //xy=1002,638
AudioEffectEnvelope      envelope1;      //xy=1202,218
AudioEffectEnvelope      envelope2;      //xy=1202,278
AudioEffectEnvelope      envelope3;      //xy=1202,338
AudioEffectEnvelope      envelope4;      //xy=1202,398
AudioEffectEnvelope      envelope5;      //xy=1202,458
AudioEffectEnvelope      envelope6;      //xy=1202,518
AudioEffectEnvelope      envelope7;      //xy=1202,578
AudioEffectEnvelope      envelope8;      //xy=1202,638
AudioMixer4              envmixer1;      //xy=1462,248
AudioMixer4              envmixer2;      //xy=1462,368
AudioMixer4              envmixer3;      //xy=1462,488
AudioMixer4              envmixer4;      //xy=1462,608
AudioMixer4              mixerL;         //xy=1722,308
AudioMixer4              mixerR;         //xy=1722,548
AudioEffectFlange        flangerL;       //xy=1862,308
AudioEffectFlange        flangerR;       //xy=1862,548
AudioOutputI2S           i2s1;           //xy=2012,428
AudioConnection          patchCord1(dc1, flt_envelope);
AudioConnection          patchCord2(flt_envelope, 0, multiply1, 0);
AudioConnection          patchCord3(flt_lfo, 0, multiply1, 1);
AudioConnection          patchCord4(multiply1, 0, filter1, 1);
AudioConnection          patchCord5(multiply1, 0, filter2, 1);
AudioConnection          patchCord6(multiply1, 0, filter3, 1);
AudioConnection          patchCord7(multiply1, 0, filter4, 1);
AudioConnection          patchCord8(multiply1, 0, filter5, 1);
AudioConnection          patchCord9(multiply1, 0, filter6, 1);
AudioConnection          patchCord10(multiply1, 0, filter7, 1);
AudioConnection          patchCord11(multiply1, 0, filter8, 1);
AudioConnection          patchCord12(waveform1, 0, filter1, 0);
AudioConnection          patchCord13(waveform1, 0, mixer1, 3);
AudioConnection          patchCord14(waveform2, 0, filter2, 0);
AudioConnection          patchCord15(waveform2, 0, mixer2, 3);
AudioConnection          patchCord16(waveform3, 0, filter3, 0);
AudioConnection          patchCord17(waveform3, 0, mixer3, 3);
AudioConnection          patchCord18(waveform4, 0, filter4, 0);
AudioConnection          patchCord19(waveform4, 0, mixer4, 3);
AudioConnection          patchCord20(waveform5, 0, filter5, 0);
AudioConnection          patchCord21(waveform5, 0, mixer5, 3);
AudioConnection          patchCord22(waveform6, 0, filter6, 0);
AudioConnection          patchCord23(waveform6, 0, mixer6, 3);
AudioConnection          patchCord24(waveform7, 0, filter7, 0);
AudioConnection          patchCord25(waveform7, 0, mixer7, 3);
AudioConnection          patchCord26(waveform8, 0, filter8, 0);
AudioConnection          patchCord27(waveform8, 0, mixer8, 3);
AudioConnection          patchCord28(filter1, 0, mixer1, 0);
AudioConnection          patchCord29(filter1, 1, mixer1, 1);
AudioConnection          patchCord30(filter1, 2, mixer1, 2);
AudioConnection          patchCord31(filter2, 0, mixer2, 0);
AudioConnection          patchCord32(filter2, 1, mixer2, 1);
AudioConnection          patchCord33(filter2, 2, mixer2, 2);
AudioConnection          patchCord34(filter3, 0, mixer3, 0);
AudioConnection          patchCord35(filter3, 1, mixer3, 1);
AudioConnection          patchCord36(filter3, 2, mixer3, 2);
AudioConnection          patchCord37(filter4, 0, mixer4, 0);
AudioConnection          patchCord38(filter4, 1, mixer4, 1);
AudioConnection          patchCord39(filter4, 2, mixer4, 2);
AudioConnection          patchCord40(filter5, 0, mixer5, 0);
AudioConnection          patchCord41(filter5, 1, mixer5, 1);
AudioConnection          patchCord42(filter5, 2, mixer5, 2);
AudioConnection          patchCord43(filter6, 0, mixer6, 0);
AudioConnection          patchCord44(filter6, 1, mixer6, 1);
AudioConnection          patchCord45(filter6, 2, mixer6, 2);
AudioConnection          patchCord46(filter7, 0, mixer7, 0);
AudioConnection          patchCord47(filter7, 1, mixer7, 1);
AudioConnection          patchCord48(filter7, 2, mixer7, 2);
AudioConnection          patchCord49(filter8, 0, mixer8, 0);
AudioConnection          patchCord50(filter8, 1, mixer8, 1);
AudioConnection          patchCord51(filter8, 2, mixer8, 2);
AudioConnection          patchCord52(mixer1, envelope1);
AudioConnection          patchCord53(mixer1, 0, envmixer1, 2);
AudioConnection          patchCord54(mixer2, envelope2);
AudioConnection          patchCord55(mixer2, 0, envmixer1, 3);
AudioConnection          patchCord56(mixer3, envelope3);
AudioConnection          patchCord57(mixer3, 0, envmixer2, 2);
AudioConnection          patchCord58(mixer4, envelope4);
AudioConnection          patchCord59(mixer4, 0, envmixer2, 3);
AudioConnection          patchCord60(mixer5, envelope5);
AudioConnection          patchCord61(mixer5, 0, envmixer3, 2);
AudioConnection          patchCord62(mixer6, envelope6);
AudioConnection          patchCord63(mixer6, 0, envmixer3, 3);
AudioConnection          patchCord64(mixer7, envelope7);
AudioConnection          patchCord65(mixer7, 0, envmixer4, 2);
AudioConnection          patchCord66(mixer8, envelope8);
AudioConnection          patchCord67(mixer8, 0, envmixer4, 3);
AudioConnection          patchCord68(envelope1, 0, envmixer1, 0);
AudioConnection          patchCord69(envelope2, 0, envmixer1, 1);
AudioConnection          patchCord70(envelope3, 0, envmixer2, 0);
AudioConnection          patchCord71(envelope4, 0, envmixer2, 1);
AudioConnection          patchCord72(envelope5, 0, envmixer3, 0);
AudioConnection          patchCord73(envelope6, 0, envmixer3, 1);
AudioConnection          patchCord74(envelope7, 0, envmixer4, 0);
AudioConnection          patchCord75(envelope8, 0, envmixer4, 1);
AudioConnection          patchCord76(envmixer1, 0, mixerL, 0);
AudioConnection          patchCord77(envmixer1, 0, mixerR, 0);
AudioConnection          patchCord78(envmixer2, 0, mixerL, 1);
AudioConnection          patchCord79(envmixer2, 0, mixerR, 1);
AudioConnection          patchCord80(envmixer3, 0, mixerL, 2);
AudioConnection          patchCord81(envmixer3, 0, mixerR, 2);
AudioConnection          patchCord82(envmixer4, 0, mixerL, 3);
AudioConnection          patchCord83(envmixer4, 0, mixerR, 3);
AudioConnection          patchCord84(mixerL, flangerL);
AudioConnection          patchCord85(mixerR, flangerR);
AudioConnection          patchCord86(flangerL, 0, i2s1, 0);
AudioConnection          patchCord87(flangerR, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=642,98
// GUItool: end automatically generated code


#endif
