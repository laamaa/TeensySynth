#ifndef SYNTHARCH_H
#define SYNTHARCH_H

#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   flt_lfo;          //xy=151,420
AudioSynthWaveformDc     flt_env_carrier;            //xy=169,372
AudioSynthWaveform       waveform1;      //xy=452.75,137.5
AudioSynthWaveform       waveform2;      //xy=454,268.0000305175781
AudioSynthWaveform       waveform3;      //xy=456.25,363.5000305175781
AudioSynthWaveform       waveform4;      //xy=467.25,457.5
AudioSynthWaveform       waveform5;      //xy=484.25,539
AudioSynthWaveform       waveform7;      //xy=484.75,717.0000610351562
AudioSynthWaveform       waveform6;      //xy=485.75,620
AudioSynthWaveform       waveform8;      //xy=487.75,809.75
AudioEffectEnvelope      flt_env_1;      //xy=520,183
AudioEffectEnvelope      flt_env_2;     //xy=529,308
AudioEffectEnvelope      flt_env_3;     //xy=525,405
AudioEffectEnvelope      flt_env_4;     //xy=514,496
AudioEffectEnvelope      flt_env_5;      //xy=518,579
AudioEffectEnvelope      flt_env_6;      //xy=514,660
AudioEffectEnvelope      flt_env_7;      //xy=517,754
AudioEffectEnvelope      flt_env_8;      //xy=512,851
AudioMixer4      flt_sum_1;      //xy=674,167
AudioMixer4      flt_sum_2;      //xy=674,285
AudioMixer4      flt_sum_3;      //xy=672,835
AudioMixer4      flt_sum_4;      //xy=674,480
AudioMixer4      flt_sum_5;      //xy=674,644
AudioMixer4      flt_sum_6;      //xy=678,385
AudioMixer4      flt_sum_7;      //xy=677,738
AudioMixer4      flt_sum_8;      //xy=678,563
AudioFilterStateVariable filter7;        //xy=814,737
AudioFilterStateVariable filter8;        //xy=814,807
AudioFilterStateVariable filter6;        //xy=815,641
AudioFilterStateVariable filter5;        //xy=818,563
AudioFilterStateVariable filter4;        //xy=821,481
AudioFilterStateVariable filter2;        //xy=822,287
AudioFilterStateVariable filter3;        //xy=824,383
AudioFilterStateVariable filter1;        //xy=825,164
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
AudioConnection          patchCord1(flt_lfo, 0, flt_sum_1, 1);
AudioConnection          patchCord2(flt_lfo, 0, flt_sum_2, 1);
AudioConnection          patchCord3(flt_lfo, 0, flt_sum_3, 1);
AudioConnection          patchCord4(flt_lfo, 0, flt_sum_4, 1);
AudioConnection          patchCord5(flt_lfo, 0, flt_sum_5, 1);
AudioConnection          patchCord6(flt_lfo, 0, flt_sum_6, 1);
AudioConnection          patchCord7(flt_lfo, 0, flt_sum_7, 1);
AudioConnection          patchCord8(flt_lfo, 0, flt_sum_8, 1);
/* AudioConnection          patchCord1(flt_lfo, 0, filter1, 1);
AudioConnection          patchCord2(flt_lfo, 0, filter2, 1);
AudioConnection          patchCord3(flt_lfo, 0, filter3, 1);
AudioConnection          patchCord4(flt_lfo, 0, filter4, 1);
AudioConnection          patchCord5(flt_lfo, 0, filter5, 1);
AudioConnection          patchCord6(flt_lfo, 0, filter6, 1);
AudioConnection          patchCord7(flt_lfo, 0, filter7, 1);
AudioConnection          patchCord8(flt_lfo, 0, filter8, 1); */
AudioConnection          patchCord9(flt_env_carrier, flt_env_1);
AudioConnection          patchCord10(flt_env_carrier, flt_env_2);
AudioConnection          patchCord11(flt_env_carrier, flt_env_3);
AudioConnection          patchCord12(flt_env_carrier, flt_env_4);
AudioConnection          patchCord13(flt_env_carrier, flt_env_5);
AudioConnection          patchCord14(flt_env_carrier, flt_env_6);
AudioConnection          patchCord15(flt_env_carrier, flt_env_7);
AudioConnection          patchCord16(flt_env_carrier, flt_env_8);
AudioConnection          patchCord17(waveform1, 0, filter1, 0);
AudioConnection          patchCord18(waveform1, 0, mixer1, 3);
AudioConnection          patchCord19(waveform2, 0, filter2, 0);
AudioConnection          patchCord20(waveform2, 0, mixer2, 3);
AudioConnection          patchCord21(waveform3, 0, filter3, 0);
AudioConnection          patchCord22(waveform3, 0, mixer3, 3);
AudioConnection          patchCord23(waveform4, 0, filter4, 0);
AudioConnection          patchCord24(waveform4, 0, mixer4, 3);
AudioConnection          patchCord25(waveform5, 0, filter5, 0);
AudioConnection          patchCord26(waveform5, 0, mixer5, 3);
AudioConnection          patchCord27(waveform7, 0, filter7, 0);
AudioConnection          patchCord28(waveform7, 0, mixer7, 3);
AudioConnection          patchCord29(waveform6, 0, filter6, 0);
AudioConnection          patchCord30(waveform6, 0, mixer6, 3);
AudioConnection          patchCord31(waveform8, 0, filter8, 0);
AudioConnection          patchCord32(waveform8, 0, mixer8, 3);
AudioConnection          patchCord33(flt_env_8, 0, flt_sum_8, 0);
AudioConnection          patchCord34(flt_env_4, 0, flt_sum_4, 0);
AudioConnection          patchCord35(flt_env_6, 0, flt_sum_6, 0);
AudioConnection          patchCord36(flt_env_7, 0, flt_sum_7, 0);
AudioConnection          patchCord37(flt_env_5, 0, flt_sum_5, 0);
AudioConnection          patchCord38(flt_env_1, 0, flt_sum_1, 0);
AudioConnection          patchCord39(flt_env_3, 0, flt_sum_3, 0);
AudioConnection          patchCord40(flt_env_2, 0, flt_sum_2, 0);
AudioConnection          patchCord41(flt_sum_1, 0, filter1, 1);
AudioConnection          patchCord42(flt_sum_2, 0, filter2, 1);
AudioConnection          patchCord43(flt_sum_8, 0, filter8, 1);
AudioConnection          patchCord44(flt_sum_4, 0, filter4, 1);
AudioConnection          patchCord45(flt_sum_6, 0, filter6, 1);
AudioConnection          patchCord46(flt_sum_3, 0, filter3, 1);
AudioConnection          patchCord47(flt_sum_7, 0, filter7, 1);
AudioConnection          patchCord48(flt_sum_5, 0, filter5, 1);
AudioConnection          patchCord49(filter7, 0, mixer7, 0);
AudioConnection          patchCord50(filter7, 1, mixer7, 1);
AudioConnection          patchCord51(filter7, 2, mixer7, 2);
AudioConnection          patchCord52(filter8, 0, mixer8, 0);
AudioConnection          patchCord53(filter8, 1, mixer8, 1);
AudioConnection          patchCord54(filter8, 2, mixer8, 2);
AudioConnection          patchCord55(filter6, 0, mixer6, 0);
AudioConnection          patchCord56(filter6, 1, mixer6, 1);
AudioConnection          patchCord57(filter6, 2, mixer6, 2);
AudioConnection          patchCord58(filter5, 0, mixer5, 0);
AudioConnection          patchCord59(filter5, 1, mixer5, 1);
AudioConnection          patchCord60(filter5, 2, mixer5, 2);
AudioConnection          patchCord61(filter4, 0, mixer4, 0);
AudioConnection          patchCord62(filter4, 1, mixer4, 1);
AudioConnection          patchCord63(filter4, 2, mixer4, 2);
AudioConnection          patchCord64(filter2, 0, mixer2, 0);
AudioConnection          patchCord65(filter2, 1, mixer2, 1);
AudioConnection          patchCord66(filter2, 2, mixer2, 2);
AudioConnection          patchCord67(filter3, 0, mixer3, 0);
AudioConnection          patchCord68(filter3, 1, mixer3, 1);
AudioConnection          patchCord69(filter3, 2, mixer3, 2);
AudioConnection          patchCord70(filter1, 0, mixer1, 0);
AudioConnection          patchCord71(filter1, 1, mixer1, 1);
AudioConnection          patchCord72(filter1, 2, mixer1, 2);
AudioConnection          patchCord73(mixer1, envelope1);
AudioConnection          patchCord74(mixer1, 0, envmixer1, 2);
AudioConnection          patchCord75(mixer2, envelope2);
AudioConnection          patchCord76(mixer2, 0, envmixer1, 3);
AudioConnection          patchCord77(mixer3, envelope3);
AudioConnection          patchCord78(mixer3, 0, envmixer2, 2);
AudioConnection          patchCord79(mixer4, envelope4);
AudioConnection          patchCord80(mixer4, 0, envmixer2, 3);
AudioConnection          patchCord81(mixer5, envelope5);
AudioConnection          patchCord82(mixer5, 0, envmixer3, 2);
AudioConnection          patchCord83(mixer6, envelope6);
AudioConnection          patchCord84(mixer6, 0, envmixer3, 3);
AudioConnection          patchCord85(mixer7, envelope7);
AudioConnection          patchCord86(mixer7, 0, envmixer4, 2);
AudioConnection          patchCord87(mixer8, envelope8);
AudioConnection          patchCord88(mixer8, 0, envmixer4, 3);
AudioConnection          patchCord89(envelope1, 0, envmixer1, 0);
AudioConnection          patchCord90(envelope2, 0, envmixer1, 1);
AudioConnection          patchCord91(envelope3, 0, envmixer2, 0);
AudioConnection          patchCord92(envelope4, 0, envmixer2, 1);
AudioConnection          patchCord93(envelope5, 0, envmixer3, 0);
AudioConnection          patchCord94(envelope6, 0, envmixer3, 1);
AudioConnection          patchCord95(envelope7, 0, envmixer4, 0);
AudioConnection          patchCord96(envelope8, 0, envmixer4, 1);
AudioConnection          patchCord97(envmixer1, 0, mixerL, 0);
AudioConnection          patchCord98(envmixer1, 0, mixerR, 0);
AudioConnection          patchCord99(envmixer2, 0, mixerL, 1);
AudioConnection          patchCord100(envmixer2, 0, mixerR, 1);
AudioConnection          patchCord101(envmixer3, 0, mixerL, 2);
AudioConnection          patchCord102(envmixer3, 0, mixerR, 2);
AudioConnection          patchCord103(envmixer4, 0, mixerL, 3);
AudioConnection          patchCord104(envmixer4, 0, mixerR, 3);
AudioConnection          patchCord105(mixerL, flangerL);
AudioConnection          patchCord106(mixerR, flangerR);
AudioConnection          patchCord107(flangerL, 0, i2s1, 0);
AudioConnection          patchCord108(flangerR, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=519,31
// GUItool: end automatically generated code



#endif
