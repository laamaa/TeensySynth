#ifndef SYNTHARCH_H
#define SYNTHARCH_H

#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       pitch_lfo;      //xy=1023.3333129882812,541
AudioSynthWaveform       pwm_lfo;        //xy=1023.3333129882812,590
AudioSynthWaveformModulated waveform1;      //xy=1229.3333129882812,325
AudioSynthWaveformModulated waveform1b;     //xy=1229.3333129882812,350
AudioSynthWaveformModulated waveform2;      //xy=1229.3333129882812,400
AudioSynthWaveformModulated waveform2b;     //xy=1229.3333129882812,425
AudioSynthWaveformModulated waveform3;      //xy=1229.3333129882812,475
AudioSynthWaveformModulated waveform3b;     //xy=1229.3333129882812,500
AudioSynthWaveformModulated waveform4;      //xy=1229.3333129882812,550
AudioSynthWaveformModulated waveform4b;     //xy=1229.3333129882812,575
AudioSynthWaveformModulated waveform5;      //xy=1229.3333129882812,625
AudioSynthWaveformModulated waveform5b;     //xy=1229.3333129882812,650
AudioSynthWaveformModulated waveform6;      //xy=1229.3333129882812,700
AudioSynthWaveformModulated waveform6b;     //xy=1229.3333129882812,725
AudioSynthWaveformModulated waveform7;      //xy=1229.3333129882812,775
AudioSynthWaveformModulated waveform7b;     //xy=1229.3333129882812,800
AudioFilterBiquad        biquad7;        //xy=429,643
AudioFilterBiquad        biquad7b;       //xy=429,676
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
AudioMixer4              waveform_sum_7; //xy=1577.3333129882812,806
AudioMixer4              waveform_sum_6; //xy=1579.3333129882812,727
AudioMixer4              waveform_sum_5; //xy=1582.3333129882812,647
AudioMixer4              waveform_sum_4; //xy=1583.3333129882812,574
AudioMixer4              waveform_sum_2; //xy=1584.3333129882812,419
AudioMixer4              waveform_sum_3; //xy=1584.3333129882812,501
AudioMixer4              waveform_sum_1; //xy=1585.3333129882812,347
AudioSynthWaveformDc     flt_env_carrier; //xy=1747.3333129882812,611
AudioEffectEnvelope      flt_env_7;      //xy=1896.3333129882812,816
AudioEffectEnvelope      flt_env_4;      //xy=1897.3333129882812,579
AudioEffectEnvelope      flt_env_6;      //xy=1897.3333129882812,731
AudioEffectEnvelope      flt_env_1;      //xy=1899.3333129882812,350
AudioEffectEnvelope      flt_env_5;      //xy=1898.3333129882812,653
AudioEffectEnvelope      flt_env_3;      //xy=1900.3333129882812,509
AudioEffectEnvelope      flt_env_2;      //xy=1905.3333129882812,424
AudioSynthWaveform       flt_lfo;        //xy=2021.3333129882812,613
AudioMixer4              flt_sum_1;      //xy=2193.3333129882812,350
AudioMixer4              flt_sum_2;      //xy=2193.3333129882812,428
AudioMixer4              flt_sum_3;      //xy=2195.3333129882812,500
AudioMixer4              flt_sum_4;      //xy=2196.3333129882812,581
AudioMixer4              flt_sum_6;      //xy=2196.3333129882812,735
AudioMixer4              flt_sum_5;      //xy=2199.3333129882812,653
AudioMixer4              flt_sum_7;      //xy=2199.3333129882812,815
AudioFilterStateVariable filter1;        //xy=2342.3333129882812,351
AudioFilterStateVariable filter2;        //xy=2345.3333129882812,430
AudioFilterStateVariable filter3;        //xy=2347.3333129882812,505
AudioFilterStateVariable filter4;        //xy=2347.3333129882812,584
AudioFilterStateVariable filter5;        //xy=2348.3333129882812,653
AudioFilterStateVariable filter6;        //xy=2349.3333129882812,734
AudioFilterStateVariable filter7;        //xy=2350.3333129882812,819
AudioMixer4              mixer1;         //xy=2518.3333129882812,376
AudioMixer4              mixer2;         //xy=2518.3333129882812,436
AudioMixer4              mixer3;         //xy=2518.3333129882812,496
AudioMixer4              mixer4;         //xy=2518.3333129882812,556
AudioMixer4              mixer5;         //xy=2518.3333129882812,616
AudioMixer4              mixer6;         //xy=2518.3333129882812,676
AudioMixer4              mixer7;         //xy=2518.3333129882812,736
AudioEffectEnvelope      envelope1;      //xy=2718.3333129882812,376
AudioEffectEnvelope      envelope2;      //xy=2718.3333129882812,436
AudioEffectEnvelope      envelope3;      //xy=2718.3333129882812,496
AudioEffectEnvelope      envelope4;      //xy=2718.3333129882812,556
AudioEffectEnvelope      envelope5;      //xy=2718.3333129882812,616
AudioEffectEnvelope      envelope6;      //xy=2718.3333129882812,676
AudioEffectEnvelope      envelope7;      //xy=2718.3333129882812,736
AudioMixer4              envmixer1;      //xy=2978.3333129882812,406
AudioMixer4              envmixer2;      //xy=2978.3333129882812,526
AudioMixer4              envmixer3;      //xy=2978.3333129882812,646
AudioMixer4              envmixer4;      //xy=2978.3333129882812,766
AudioMixer4              mixerL;         //xy=3238.3333129882812,466
AudioMixer4              mixerR;         //xy=3238.3333129882812,706
AudioOutputI2S           i2s1;           //xy=3528.3333129882812,586
AudioConnection          patchCord1(pitch_lfo, 0, waveform1, 0);
AudioConnection          patchCord2(pitch_lfo, 0, waveform2, 0);
AudioConnection          patchCord3(pitch_lfo, 0, waveform3, 0);
AudioConnection          patchCord4(pitch_lfo, 0, waveform4, 0);
AudioConnection          patchCord5(pitch_lfo, 0, waveform5, 0);
AudioConnection          patchCord6(pitch_lfo, 0, waveform6, 0);
AudioConnection          patchCord7(pitch_lfo, 0, waveform7, 0);
AudioConnection          patchCord9(pitch_lfo, 0, waveform1b, 0);
AudioConnection          patchCord10(pitch_lfo, 0, waveform2b, 0);
AudioConnection          patchCord11(pitch_lfo, 0, waveform3b, 0);
AudioConnection          patchCord12(pitch_lfo, 0, waveform4b, 0);
AudioConnection          patchCord13(pitch_lfo, 0, waveform5b, 0);
AudioConnection          patchCord14(pitch_lfo, 0, waveform6b, 0);
AudioConnection          patchCord15(pitch_lfo, 0, waveform7b, 0);
AudioConnection          patchCord17(pwm_lfo, 0, waveform1, 1);
AudioConnection          patchCord18(pwm_lfo, 0, waveform2, 1);
AudioConnection          patchCord19(pwm_lfo, 0, waveform3, 1);
AudioConnection          patchCord20(pwm_lfo, 0, waveform4, 1);
AudioConnection          patchCord21(pwm_lfo, 0, waveform5, 1);
AudioConnection          patchCord22(pwm_lfo, 0, waveform6, 1);
AudioConnection          patchCord23(pwm_lfo, 0, waveform7, 1);
AudioConnection          patchCord25(pwm_lfo, 0, waveform1b, 1);
AudioConnection          patchCord26(pwm_lfo, 0, waveform2b, 1);
AudioConnection          patchCord27(pwm_lfo, 0, waveform3b, 1);
AudioConnection          patchCord28(pwm_lfo, 0, waveform4b, 1);
AudioConnection          patchCord29(pwm_lfo, 0, waveform5b, 1);
AudioConnection          patchCord30(pwm_lfo, 0, waveform6b, 1);
AudioConnection          patchCord31(pwm_lfo, 0, waveform7b, 1);
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
AudioConnection          patchCord49(biquad7, 0, waveform_sum_7, 0);
AudioConnection          patchCord50(biquad7b, 0, waveform_sum_7, 1);
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
AudioConnection          patchCord89(flt_env_7, 0, flt_sum_7, 0);
AudioConnection          patchCord90(flt_env_4, 0, flt_sum_4, 0);
AudioConnection          patchCord91(flt_env_6, 0, flt_sum_6, 0);
AudioConnection          patchCord92(flt_env_1, 0, flt_sum_1, 0);
AudioConnection          patchCord93(flt_env_5, 0, flt_sum_5, 0);
AudioConnection          patchCord94(flt_env_3, 0, flt_sum_3, 0);
AudioConnection          patchCord96(flt_env_2, 0, flt_sum_2, 0);
AudioConnection          patchCord97(flt_lfo, 0, flt_sum_1, 1);
AudioConnection          patchCord98(flt_lfo, 0, flt_sum_2, 1);
AudioConnection          patchCord99(flt_lfo, 0, flt_sum_3, 1);
AudioConnection          patchCord100(flt_lfo, 0, flt_sum_4, 1);
AudioConnection          patchCord101(flt_lfo, 0, flt_sum_5, 1);
AudioConnection          patchCord102(flt_lfo, 0, flt_sum_6, 1);
AudioConnection          patchCord103(flt_lfo, 0, flt_sum_7, 1);
AudioConnection          patchCord105(flt_sum_1, 0, filter1, 1);
AudioConnection          patchCord106(flt_sum_2, 0, filter2, 1);
AudioConnection          patchCord107(flt_sum_3, 0, filter3, 1);
AudioConnection          patchCord108(flt_sum_4, 0, filter4, 1);
AudioConnection          patchCord109(flt_sum_6, 0, filter6, 1);
AudioConnection          patchCord110(flt_sum_5, 0, filter5, 1);
AudioConnection          patchCord111(flt_sum_7, 0, filter7, 1);
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
AudioConnection          patchCord153(envelope1, 0, envmixer1, 0);
AudioConnection          patchCord154(envelope2, 0, envmixer1, 1);
AudioConnection          patchCord155(envelope3, 0, envmixer2, 0);
AudioConnection          patchCord156(envelope4, 0, envmixer2, 1);
AudioConnection          patchCord157(envelope5, 0, envmixer3, 0);
AudioConnection          patchCord158(envelope6, 0, envmixer3, 1);
AudioConnection          patchCord159(envelope7, 0, envmixer4, 0);
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
AudioControlSGTL5000     sgtl5000_1;     //xy=1549.3333129882812,270
// GUItool: end automatically generated code






#endif
