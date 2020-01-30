#ifndef SYNTHARCH_H
#define SYNTHARCH_H

#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       pitch_lfo;      //xy=66,411
AudioSynthWaveform       pwm_lfo;        //xy=66,460
AudioSynthWaveformModulated waveform1;      //xy=272,195
AudioSynthWaveformModulated waveform1b;     //xy=272,220
AudioSynthWaveformModulated waveform2;      //xy=272,270
AudioSynthWaveformModulated waveform2b;     //xy=272,295
AudioSynthWaveformModulated waveform3;      //xy=272,345
AudioSynthWaveformModulated waveform3b;     //xy=272,370
AudioSynthWaveformModulated waveform4;      //xy=272,420
AudioSynthWaveformModulated waveform4b;     //xy=272,445
AudioSynthWaveformModulated waveform5;      //xy=272,495
AudioSynthWaveformModulated waveform5b;     //xy=272,520
AudioSynthWaveformModulated waveform6;      //xy=272,570
AudioSynthWaveformModulated waveform6b;     //xy=272,595
AudioSynthWaveformModulated waveform7;      //xy=272,645
AudioSynthWaveformModulated waveform7b;     //xy=272,670
AudioSynthWaveformModulated waveform8;      //xy=272,720
AudioSynthWaveformModulated waveform8b;     //xy=272,745
AudioFilterBiquad        biquad7;        //xy=429,643
AudioFilterBiquad        biquad7b;       //xy=429,676
AudioFilterBiquad        biquad8;        //xy=429,721
AudioFilterBiquad        biquad8b;       //xy=429,754
AudioFilterBiquad        biquad1;        //xy=435,191
AudioFilterBiquad        biquad5;        //xy=434,493
AudioFilterBiquad        biquad2;        //xy=435,270
AudioFilterBiquad        biquad5b;       //xy=434,524
AudioFilterBiquad        biquad6;        //xy=434,571
AudioFilterBiquad        biquad3;        //xy=435,349
AudioFilterBiquad        biquad6b;       //xy=434,602
AudioFilterBiquad        biquad4;        //xy=435,427
AudioFilterBiquad        biquad1b;       //xy=436,225
AudioFilterBiquad        biquad3b;       //xy=436,381
AudioFilterBiquad        biquad4b;       //xy=436,459
AudioFilterBiquad        biquad2b;       //xy=437,304
AudioMixer4              waveform_sum_8; //xy=618,747
AudioMixer4              waveform_sum_7; //xy=620,676
AudioMixer4              waveform_sum_6; //xy=622,597
AudioMixer4              waveform_sum_5; //xy=625,517
AudioMixer4              waveform_sum_4; //xy=626,444
AudioMixer4              waveform_sum_2; //xy=627,289
AudioMixer4              waveform_sum_3; //xy=627,371
AudioMixer4              waveform_sum_1; //xy=628,217
AudioSynthWaveformDc     flt_env_carrier; //xy=790,481
AudioEffectEnvelope      flt_env_7;      //xy=939,686
AudioEffectEnvelope      flt_env_4;      //xy=940,449
AudioEffectEnvelope      flt_env_6;      //xy=940,601
AudioEffectEnvelope      flt_env_1;      //xy=942,220
AudioEffectEnvelope      flt_env_5;      //xy=941,523
AudioEffectEnvelope      flt_env_3;      //xy=943,379
AudioEffectEnvelope      flt_env_8;      //xy=942,762
AudioEffectEnvelope      flt_env_2;      //xy=948,294
AudioSynthWaveform       flt_lfo;        //xy=1064,483
AudioMixer4              flt_sum_1;      //xy=1236,220
AudioMixer4              flt_sum_2;      //xy=1236,298
AudioMixer4              flt_sum_3;      //xy=1238,370
AudioMixer4              flt_sum_4;      //xy=1239,451
AudioMixer4              flt_sum_6;      //xy=1239,605
AudioMixer4              flt_sum_5;      //xy=1242,523
AudioMixer4              flt_sum_7;      //xy=1242,685
AudioMixer4              flt_sum_8;      //xy=1243,765
AudioFilterStateVariable filter1;        //xy=1385,221
AudioFilterStateVariable filter2;        //xy=1388,300
AudioFilterStateVariable filter3;        //xy=1390,375
AudioFilterStateVariable filter4;        //xy=1390,454
AudioFilterStateVariable filter5;        //xy=1391,523
AudioFilterStateVariable filter6;        //xy=1392,604
AudioFilterStateVariable filter7;        //xy=1393,689
AudioFilterStateVariable filter8;        //xy=1403,761
AudioMixer4              mixer1;         //xy=1561,246
AudioMixer4              mixer2;         //xy=1561,306
AudioMixer4              mixer3;         //xy=1561,366
AudioMixer4              mixer4;         //xy=1561,426
AudioMixer4              mixer5;         //xy=1561,486
AudioMixer4              mixer6;         //xy=1561,546
AudioMixer4              mixer7;         //xy=1561,606
AudioMixer4              mixer8;         //xy=1561,666
AudioEffectEnvelope      envelope1;      //xy=1761,246
AudioEffectEnvelope      envelope2;      //xy=1761,306
AudioEffectEnvelope      envelope3;      //xy=1761,366
AudioEffectEnvelope      envelope4;      //xy=1761,426
AudioEffectEnvelope      envelope5;      //xy=1761,486
AudioEffectEnvelope      envelope6;      //xy=1761,546
AudioEffectEnvelope      envelope7;      //xy=1761,606
AudioEffectEnvelope      envelope8;      //xy=1761,666
AudioMixer4              envmixer1;      //xy=2021,276
AudioMixer4              envmixer2;      //xy=2021,396
AudioMixer4              envmixer3;      //xy=2021,516
AudioMixer4              envmixer4;      //xy=2021,636
AudioMixer4              mixerL;         //xy=2281,336
AudioMixer4              mixerR;         //xy=2281,576
AudioOutputI2S           i2s1;           //xy=2571,456
AudioConnection          patchCord1(pitch_lfo, 0, waveform1, 0);
AudioConnection          patchCord2(pitch_lfo, 0, waveform2, 0);
AudioConnection          patchCord3(pitch_lfo, 0, waveform3, 0);
AudioConnection          patchCord4(pitch_lfo, 0, waveform4, 0);
AudioConnection          patchCord5(pitch_lfo, 0, waveform5, 0);
AudioConnection          patchCord6(pitch_lfo, 0, waveform6, 0);
AudioConnection          patchCord7(pitch_lfo, 0, waveform7, 0);
AudioConnection          patchCord8(pitch_lfo, 0, waveform8, 0);
AudioConnection          patchCord9(pitch_lfo, 0, waveform1b, 0);
AudioConnection          patchCord10(pitch_lfo, 0, waveform2b, 0);
AudioConnection          patchCord11(pitch_lfo, 0, waveform3b, 0);
AudioConnection          patchCord12(pitch_lfo, 0, waveform4b, 0);
AudioConnection          patchCord13(pitch_lfo, 0, waveform5b, 0);
AudioConnection          patchCord14(pitch_lfo, 0, waveform6b, 0);
AudioConnection          patchCord15(pitch_lfo, 0, waveform7b, 0);
AudioConnection          patchCord16(pitch_lfo, 0, waveform8b, 0);
AudioConnection          patchCord17(pwm_lfo, 0, waveform1, 1);
AudioConnection          patchCord18(pwm_lfo, 0, waveform2, 1);
AudioConnection          patchCord19(pwm_lfo, 0, waveform3, 1);
AudioConnection          patchCord20(pwm_lfo, 0, waveform4, 1);
AudioConnection          patchCord21(pwm_lfo, 0, waveform5, 1);
AudioConnection          patchCord22(pwm_lfo, 0, waveform6, 1);
AudioConnection          patchCord23(pwm_lfo, 0, waveform7, 1);
AudioConnection          patchCord24(pwm_lfo, 0, waveform8, 1);
AudioConnection          patchCord25(pwm_lfo, 0, waveform1b, 1);
AudioConnection          patchCord26(pwm_lfo, 0, waveform2b, 1);
AudioConnection          patchCord27(pwm_lfo, 0, waveform3b, 1);
AudioConnection          patchCord28(pwm_lfo, 0, waveform4b, 1);
AudioConnection          patchCord29(pwm_lfo, 0, waveform5b, 1);
AudioConnection          patchCord30(pwm_lfo, 0, waveform6b, 1);
AudioConnection          patchCord31(pwm_lfo, 0, waveform7b, 1);
AudioConnection          patchCord32(pwm_lfo, 0, waveform8b, 1);
AudioConnection          patchCord33(waveform1, biquad1);
AudioConnection          patchCord34(waveform1b, biquad1b);
AudioConnection          patchCord35(waveform2, biquad2);
AudioConnection          patchCord36(waveform2b, biquad2b);
AudioConnection          patchCord37(waveform3, biquad3);
AudioConnection          patchCord38(waveform3b, biquad3b);
AudioConnection          patchCord39(waveform4, biquad4);
AudioConnection          patchCord40(waveform4b, biquad4b);
AudioConnection          patchCord41(waveform5, biquad5);
AudioConnection          patchCord42(waveform5b, biquad5b);
AudioConnection          patchCord43(waveform6, biquad6);
AudioConnection          patchCord44(waveform6b, biquad6b);
AudioConnection          patchCord45(waveform7, biquad7);
AudioConnection          patchCord46(waveform7b, biquad7b);
AudioConnection          patchCord47(waveform8, biquad8);
AudioConnection          patchCord48(waveform8b, biquad8b);
AudioConnection          patchCord49(biquad7, 0, waveform_sum_7, 0);
AudioConnection          patchCord50(biquad7b, 0, waveform_sum_7, 1);
AudioConnection          patchCord51(biquad8, 0, waveform_sum_8, 0);
AudioConnection          patchCord52(biquad8b, 0, waveform_sum_8, 1);
AudioConnection          patchCord53(biquad1, 0, waveform_sum_1, 0);
AudioConnection          patchCord54(biquad5, 0, waveform_sum_5, 0);
AudioConnection          patchCord55(biquad2, 0, waveform_sum_2, 0);
AudioConnection          patchCord56(biquad5b, 0, waveform_sum_5, 1);
AudioConnection          patchCord57(biquad6, 0, waveform_sum_6, 0);
AudioConnection          patchCord58(biquad3, 0, waveform_sum_3, 0);
AudioConnection          patchCord59(biquad6b, 0, waveform_sum_6, 1);
AudioConnection          patchCord60(biquad4, 0, waveform_sum_4, 0);
AudioConnection          patchCord61(biquad1b, 0, waveform_sum_1, 1);
AudioConnection          patchCord62(biquad3b, 0, waveform_sum_3, 1);
AudioConnection          patchCord63(biquad4b, 0, waveform_sum_4, 1);
AudioConnection          patchCord64(biquad2b, 0, waveform_sum_2, 1);
AudioConnection          patchCord65(waveform_sum_8, 0, filter8, 0);
AudioConnection          patchCord66(waveform_sum_8, 0, mixer8, 3);
AudioConnection          patchCord67(waveform_sum_7, 0, filter7, 0);
AudioConnection          patchCord68(waveform_sum_7, 0, mixer7, 3);
AudioConnection          patchCord69(waveform_sum_6, 0, filter6, 0);
AudioConnection          patchCord70(waveform_sum_6, 0, mixer6, 3);
AudioConnection          patchCord71(waveform_sum_5, 0, filter5, 0);
AudioConnection          patchCord72(waveform_sum_5, 0, mixer5, 3);
AudioConnection          patchCord73(waveform_sum_4, 0, filter4, 0);
AudioConnection          patchCord74(waveform_sum_4, 0, mixer4, 3);
AudioConnection          patchCord75(waveform_sum_2, 0, filter2, 0);
AudioConnection          patchCord76(waveform_sum_2, 0, mixer2, 3);
AudioConnection          patchCord77(waveform_sum_3, 0, filter3, 0);
AudioConnection          patchCord78(waveform_sum_3, 0, mixer3, 3);
AudioConnection          patchCord79(waveform_sum_1, 0, filter1, 0);
AudioConnection          patchCord80(waveform_sum_1, 0, mixer1, 3);
AudioConnection          patchCord81(flt_env_carrier, flt_env_1);
AudioConnection          patchCord82(flt_env_carrier, flt_env_2);
AudioConnection          patchCord83(flt_env_carrier, flt_env_3);
AudioConnection          patchCord84(flt_env_carrier, flt_env_4);
AudioConnection          patchCord85(flt_env_carrier, flt_env_5);
AudioConnection          patchCord86(flt_env_carrier, flt_env_6);
AudioConnection          patchCord87(flt_env_carrier, flt_env_7);
AudioConnection          patchCord88(flt_env_carrier, flt_env_8);
AudioConnection          patchCord89(flt_env_7, 0, flt_sum_7, 0);
AudioConnection          patchCord90(flt_env_4, 0, flt_sum_4, 0);
AudioConnection          patchCord91(flt_env_6, 0, flt_sum_6, 0);
AudioConnection          patchCord92(flt_env_1, 0, flt_sum_1, 0);
AudioConnection          patchCord93(flt_env_5, 0, flt_sum_5, 0);
AudioConnection          patchCord94(flt_env_3, 0, flt_sum_3, 0);
AudioConnection          patchCord95(flt_env_8, 0, flt_sum_8, 0);
AudioConnection          patchCord96(flt_env_2, 0, flt_sum_2, 0);
AudioConnection          patchCord97(flt_lfo, 0, flt_sum_1, 1);
AudioConnection          patchCord98(flt_lfo, 0, flt_sum_2, 1);
AudioConnection          patchCord99(flt_lfo, 0, flt_sum_3, 1);
AudioConnection          patchCord100(flt_lfo, 0, flt_sum_4, 1);
AudioConnection          patchCord101(flt_lfo, 0, flt_sum_5, 1);
AudioConnection          patchCord102(flt_lfo, 0, flt_sum_6, 1);
AudioConnection          patchCord103(flt_lfo, 0, flt_sum_7, 1);
AudioConnection          patchCord104(flt_lfo, 0, flt_sum_8, 1);
AudioConnection          patchCord105(flt_sum_1, 0, filter1, 1);
AudioConnection          patchCord106(flt_sum_2, 0, filter2, 1);
AudioConnection          patchCord107(flt_sum_3, 0, filter3, 1);
AudioConnection          patchCord108(flt_sum_4, 0, filter4, 1);
AudioConnection          patchCord109(flt_sum_6, 0, filter6, 1);
AudioConnection          patchCord110(flt_sum_5, 0, filter5, 1);
AudioConnection          patchCord111(flt_sum_7, 0, filter7, 1);
AudioConnection          patchCord112(flt_sum_8, 0, filter8, 1);
AudioConnection          patchCord113(filter1, 0, mixer1, 0);
AudioConnection          patchCord114(filter1, 1, mixer1, 1);
AudioConnection          patchCord115(filter1, 2, mixer1, 2);
AudioConnection          patchCord116(filter2, 0, mixer2, 0);
AudioConnection          patchCord117(filter2, 1, mixer2, 1);
AudioConnection          patchCord118(filter2, 2, mixer2, 2);
AudioConnection          patchCord119(filter3, 0, mixer3, 0);
AudioConnection          patchCord120(filter3, 1, mixer3, 1);
AudioConnection          patchCord121(filter3, 2, mixer3, 2);
AudioConnection          patchCord122(filter4, 0, mixer4, 0);
AudioConnection          patchCord123(filter4, 1, mixer4, 1);
AudioConnection          patchCord124(filter4, 2, mixer4, 2);
AudioConnection          patchCord125(filter5, 0, mixer5, 0);
AudioConnection          patchCord126(filter5, 1, mixer5, 1);
AudioConnection          patchCord127(filter5, 2, mixer5, 2);
AudioConnection          patchCord128(filter6, 0, mixer6, 0);
AudioConnection          patchCord129(filter6, 1, mixer6, 1);
AudioConnection          patchCord130(filter6, 2, mixer6, 2);
AudioConnection          patchCord131(filter7, 0, mixer7, 0);
AudioConnection          patchCord132(filter7, 1, mixer7, 1);
AudioConnection          patchCord133(filter7, 2, mixer7, 2);
AudioConnection          patchCord134(filter8, 0, mixer8, 0);
AudioConnection          patchCord135(filter8, 1, mixer8, 1);
AudioConnection          patchCord136(filter8, 2, mixer8, 2);
AudioConnection          patchCord137(mixer1, envelope1);
AudioConnection          patchCord138(mixer1, 0, envmixer1, 2);
AudioConnection          patchCord139(mixer2, envelope2);
AudioConnection          patchCord140(mixer2, 0, envmixer1, 3);
AudioConnection          patchCord141(mixer3, envelope3);
AudioConnection          patchCord142(mixer3, 0, envmixer2, 2);
AudioConnection          patchCord143(mixer4, envelope4);
AudioConnection          patchCord144(mixer4, 0, envmixer2, 3);
AudioConnection          patchCord145(mixer5, envelope5);
AudioConnection          patchCord146(mixer5, 0, envmixer3, 2);
AudioConnection          patchCord147(mixer6, envelope6);
AudioConnection          patchCord148(mixer6, 0, envmixer3, 3);
AudioConnection          patchCord149(mixer7, envelope7);
AudioConnection          patchCord150(mixer7, 0, envmixer4, 2);
AudioConnection          patchCord151(mixer8, envelope8);
AudioConnection          patchCord152(mixer8, 0, envmixer4, 3);
AudioConnection          patchCord153(envelope1, 0, envmixer1, 0);
AudioConnection          patchCord154(envelope2, 0, envmixer1, 1);
AudioConnection          patchCord155(envelope3, 0, envmixer2, 0);
AudioConnection          patchCord156(envelope4, 0, envmixer2, 1);
AudioConnection          patchCord157(envelope5, 0, envmixer3, 0);
AudioConnection          patchCord158(envelope6, 0, envmixer3, 1);
AudioConnection          patchCord159(envelope7, 0, envmixer4, 0);
AudioConnection          patchCord160(envelope8, 0, envmixer4, 1);
AudioConnection          patchCord161(envmixer1, 0, mixerL, 0);
AudioConnection          patchCord162(envmixer1, 0, mixerR, 0);
AudioConnection          patchCord163(envmixer2, 0, mixerL, 1);
AudioConnection          patchCord164(envmixer2, 0, mixerR, 1);
AudioConnection          patchCord165(envmixer3, 0, mixerL, 2);
AudioConnection          patchCord166(envmixer3, 0, mixerR, 2);
AudioConnection          patchCord167(envmixer4, 0, mixerL, 3);
AudioConnection          patchCord168(envmixer4, 0, mixerR, 3);
AudioConnection          patchCord169(mixerL, 0, i2s1, 0);
AudioConnection          patchCord170(mixerR, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=592,140
// GUItool: end automatically generated code





#endif
