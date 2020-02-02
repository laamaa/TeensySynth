#ifndef SYNTHARCH_H
#define SYNTHARCH_H

#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       pitch_lfo;      //xy=56.5,451
AudioSynthWaveform       pwm_lfo;        //xy=56.5,500
AudioSynthWaveformModulated waveform1;      //xy=262.5,235
AudioSynthWaveformModulated waveform1b;     //xy=262.5,260
AudioSynthWaveformModulated waveform2;      //xy=262.5,310
AudioSynthWaveformModulated waveform2b;     //xy=262.5,335
AudioSynthWaveformModulated waveform3;      //xy=262.5,385
AudioSynthWaveformModulated waveform3b;     //xy=262.5,410
AudioSynthWaveformModulated waveform4;      //xy=262.5,460
AudioSynthWaveformModulated waveform4b;     //xy=262.5,485
AudioSynthWaveformModulated waveform5;      //xy=262.5,535
AudioSynthWaveformModulated waveform5b;     //xy=262.5,560
AudioSynthWaveformModulated waveform6;      //xy=262.5,610
AudioSynthWaveformModulated waveform6b;     //xy=262.5,635
AudioFilterBiquad        biquad1;        //xy=429.5,228
AudioFilterBiquad        biquad5;        //xy=428.5,530
AudioFilterBiquad        biquad2;        //xy=429.5,307
AudioFilterBiquad        biquad5b;       //xy=428.5,561
AudioFilterBiquad        biquad6;        //xy=428.5,608
AudioFilterBiquad        biquad3;        //xy=429.5,386
AudioFilterBiquad        biquad6b;       //xy=428.5,639
AudioFilterBiquad        biquad4;        //xy=429.5,464
AudioFilterBiquad        biquad1b;       //xy=430.5,262
AudioFilterBiquad        biquad3b;       //xy=430.5,418
AudioFilterBiquad        biquad4b;       //xy=430.5,496
AudioFilterBiquad        biquad2b;       //xy=431.5,341
AudioMixer4              waveform_sum_6; //xy=612.5,637
AudioMixer4              waveform_sum_5; //xy=615.5,557
AudioMixer4              waveform_sum_4; //xy=616.5,484
AudioMixer4              waveform_sum_2; //xy=617.5,329
AudioMixer4              waveform_sum_3; //xy=617.5,411
AudioMixer4              waveform_sum_1; //xy=618.5,257
AudioSynthWaveformDc     flt_env_carrier; //xy=780.5,521
AudioEffectEnvelope      flt_env_4;      //xy=930.5,489
AudioEffectEnvelope      flt_env_6;      //xy=930.5,641
AudioEffectEnvelope      flt_env_1;      //xy=932.5,260
AudioEffectEnvelope      flt_env_5;      //xy=931.5,563
AudioEffectEnvelope      flt_env_3;      //xy=933.5,419
AudioEffectEnvelope      flt_env_2;      //xy=938.5,334
AudioSynthWaveform       flt_lfo;        //xy=1054.5,523
AudioMixer4              flt_sum_1;      //xy=1226.5,260
AudioMixer4              flt_sum_2;      //xy=1226.5,338
AudioMixer4              flt_sum_3;      //xy=1228.5,410
AudioMixer4              flt_sum_4;      //xy=1229.5,491
AudioMixer4              flt_sum_6;      //xy=1229.5,645
AudioMixer4              flt_sum_5;      //xy=1232.5,563
AudioFilterStateVariable filter1;        //xy=1375.5,261
AudioFilterStateVariable filter2;        //xy=1378.5,340
AudioFilterStateVariable filter3;        //xy=1380.5,415
AudioFilterStateVariable filter4;        //xy=1380.5,494
AudioFilterStateVariable filter5;        //xy=1381.5,563
AudioFilterStateVariable filter6;        //xy=1382.5,644
AudioMixer4              mixer1;         //xy=1551.5,286
AudioMixer4              mixer2;         //xy=1551.5,346
AudioMixer4              mixer3;         //xy=1551.5,406
AudioMixer4              mixer4;         //xy=1551.5,466
AudioMixer4              mixer5;         //xy=1551.5,526
AudioMixer4              mixer6;         //xy=1551.5,586
AudioEffectEnvelope      envelope1;      //xy=1751.5,286
AudioEffectEnvelope      envelope2;      //xy=1751.5,346
AudioEffectEnvelope      envelope3;      //xy=1751.5,406
AudioEffectEnvelope      envelope4;      //xy=1751.5,466
AudioEffectEnvelope      envelope5;      //xy=1751.5,526
AudioEffectEnvelope      envelope6;      //xy=1751.5,586
AudioMixer4              envmixer1;      //xy=2011.5,316
AudioMixer4              envmixer2;      //xy=2011.5,436
AudioMixer4              envmixer3;      //xy=2011.5,556
AudioMixer4              mixerL;         //xy=2271.5,376
AudioMixer4              mixerR;         //xy=2274.0001220703125,581.0000610351562
AudioOutputI2S           i2s1;           //xy=2752.7501220703125,451
AudioConnection          patchCord1(pitch_lfo, 0, waveform1, 0);
AudioConnection          patchCord2(pitch_lfo, 0, waveform2, 0);
AudioConnection          patchCord3(pitch_lfo, 0, waveform3, 0);
AudioConnection          patchCord4(pitch_lfo, 0, waveform4, 0);
AudioConnection          patchCord5(pitch_lfo, 0, waveform5, 0);
AudioConnection          patchCord6(pitch_lfo, 0, waveform6, 0);
AudioConnection          patchCord7(pitch_lfo, 0, waveform1b, 0);
AudioConnection          patchCord8(pitch_lfo, 0, waveform2b, 0);
AudioConnection          patchCord9(pitch_lfo, 0, waveform3b, 0);
AudioConnection          patchCord10(pitch_lfo, 0, waveform4b, 0);
AudioConnection          patchCord11(pitch_lfo, 0, waveform5b, 0);
AudioConnection          patchCord12(pitch_lfo, 0, waveform6b, 0);
AudioConnection          patchCord13(pwm_lfo, 0, waveform1, 1);
AudioConnection          patchCord14(pwm_lfo, 0, waveform2, 1);
AudioConnection          patchCord15(pwm_lfo, 0, waveform3, 1);
AudioConnection          patchCord16(pwm_lfo, 0, waveform4, 1);
AudioConnection          patchCord17(pwm_lfo, 0, waveform5, 1);
AudioConnection          patchCord18(pwm_lfo, 0, waveform6, 1);
AudioConnection          patchCord19(pwm_lfo, 0, waveform1b, 1);
AudioConnection          patchCord20(pwm_lfo, 0, waveform2b, 1);
AudioConnection          patchCord21(pwm_lfo, 0, waveform3b, 1);
AudioConnection          patchCord22(pwm_lfo, 0, waveform4b, 1);
AudioConnection          patchCord23(pwm_lfo, 0, waveform5b, 1);
AudioConnection          patchCord24(pwm_lfo, 0, waveform6b, 1);
AudioConnection          patchCord25(waveform1, biquad1);
AudioConnection          patchCord26(waveform1b, biquad1b);
AudioConnection          patchCord27(waveform2, biquad2);
AudioConnection          patchCord28(waveform2b, biquad2b);
AudioConnection          patchCord29(waveform3, biquad3);
AudioConnection          patchCord30(waveform3b, biquad3b);
AudioConnection          patchCord31(waveform4, biquad4);
AudioConnection          patchCord32(waveform4b, biquad4b);
AudioConnection          patchCord33(waveform5, biquad5);
AudioConnection          patchCord34(waveform5b, biquad5b);
AudioConnection          patchCord35(waveform6, biquad6);
AudioConnection          patchCord36(waveform6b, biquad6b);
AudioConnection          patchCord37(biquad1, 0, waveform_sum_1, 0);
AudioConnection          patchCord38(biquad5, 0, waveform_sum_5, 0);
AudioConnection          patchCord39(biquad2, 0, waveform_sum_2, 0);
AudioConnection          patchCord40(biquad5b, 0, waveform_sum_5, 1);
AudioConnection          patchCord41(biquad6, 0, waveform_sum_6, 0);
AudioConnection          patchCord42(biquad3, 0, waveform_sum_3, 0);
AudioConnection          patchCord43(biquad6b, 0, waveform_sum_6, 1);
AudioConnection          patchCord44(biquad4, 0, waveform_sum_4, 0);
AudioConnection          patchCord45(biquad1b, 0, waveform_sum_1, 1);
AudioConnection          patchCord46(biquad3b, 0, waveform_sum_3, 1);
AudioConnection          patchCord47(biquad4b, 0, waveform_sum_4, 1);
AudioConnection          patchCord48(biquad2b, 0, waveform_sum_2, 1);
AudioConnection          patchCord49(waveform_sum_6, 0, filter6, 0);
AudioConnection          patchCord50(waveform_sum_6, 0, mixer6, 3);
AudioConnection          patchCord51(waveform_sum_5, 0, filter5, 0);
AudioConnection          patchCord52(waveform_sum_5, 0, mixer5, 3);
AudioConnection          patchCord53(waveform_sum_4, 0, filter4, 0);
AudioConnection          patchCord54(waveform_sum_4, 0, mixer4, 3);
AudioConnection          patchCord55(waveform_sum_2, 0, filter2, 0);
AudioConnection          patchCord56(waveform_sum_2, 0, mixer2, 3);
AudioConnection          patchCord57(waveform_sum_3, 0, filter3, 0);
AudioConnection          patchCord58(waveform_sum_3, 0, mixer3, 3);
AudioConnection          patchCord59(waveform_sum_1, 0, filter1, 0);
AudioConnection          patchCord60(waveform_sum_1, 0, mixer1, 3);
AudioConnection          patchCord61(flt_env_carrier, flt_env_1);
AudioConnection          patchCord62(flt_env_carrier, flt_env_2);
AudioConnection          patchCord63(flt_env_carrier, flt_env_3);
AudioConnection          patchCord64(flt_env_carrier, flt_env_4);
AudioConnection          patchCord65(flt_env_carrier, flt_env_5);
AudioConnection          patchCord66(flt_env_carrier, flt_env_6);
AudioConnection          patchCord67(flt_env_4, 0, flt_sum_4, 0);
AudioConnection          patchCord68(flt_env_6, 0, flt_sum_6, 0);
AudioConnection          patchCord69(flt_env_1, 0, flt_sum_1, 0);
AudioConnection          patchCord70(flt_env_5, 0, flt_sum_5, 0);
AudioConnection          patchCord71(flt_env_3, 0, flt_sum_3, 0);
AudioConnection          patchCord72(flt_env_2, 0, flt_sum_2, 0);
AudioConnection          patchCord73(flt_lfo, 0, flt_sum_1, 1);
AudioConnection          patchCord74(flt_lfo, 0, flt_sum_2, 1);
AudioConnection          patchCord75(flt_lfo, 0, flt_sum_3, 1);
AudioConnection          patchCord76(flt_lfo, 0, flt_sum_4, 1);
AudioConnection          patchCord77(flt_lfo, 0, flt_sum_5, 1);
AudioConnection          patchCord78(flt_lfo, 0, flt_sum_6, 1);
AudioConnection          patchCord79(flt_sum_1, 0, filter1, 1);
AudioConnection          patchCord80(flt_sum_2, 0, filter2, 1);
AudioConnection          patchCord81(flt_sum_3, 0, filter3, 1);
AudioConnection          patchCord82(flt_sum_4, 0, filter4, 1);
AudioConnection          patchCord83(flt_sum_6, 0, filter6, 1);
AudioConnection          patchCord84(flt_sum_5, 0, filter5, 1);
AudioConnection          patchCord85(filter1, 0, mixer1, 0);
AudioConnection          patchCord86(filter1, 1, mixer1, 1);
AudioConnection          patchCord87(filter1, 2, mixer1, 2);
AudioConnection          patchCord88(filter2, 0, mixer2, 0);
AudioConnection          patchCord89(filter2, 1, mixer2, 1);
AudioConnection          patchCord90(filter2, 2, mixer2, 2);
AudioConnection          patchCord91(filter3, 0, mixer3, 0);
AudioConnection          patchCord92(filter3, 1, mixer3, 1);
AudioConnection          patchCord93(filter3, 2, mixer3, 2);
AudioConnection          patchCord94(filter4, 0, mixer4, 0);
AudioConnection          patchCord95(filter4, 1, mixer4, 1);
AudioConnection          patchCord96(filter4, 2, mixer4, 2);
AudioConnection          patchCord97(filter5, 0, mixer5, 0);
AudioConnection          patchCord98(filter5, 1, mixer5, 1);
AudioConnection          patchCord99(filter5, 2, mixer5, 2);
AudioConnection          patchCord100(filter6, 0, mixer6, 0);
AudioConnection          patchCord101(filter6, 1, mixer6, 1);
AudioConnection          patchCord102(filter6, 2, mixer6, 2);
AudioConnection          patchCord103(mixer1, envelope1);
AudioConnection          patchCord104(mixer1, 0, envmixer1, 2);
AudioConnection          patchCord105(mixer2, envelope2);
AudioConnection          patchCord106(mixer2, 0, envmixer1, 3);
AudioConnection          patchCord107(mixer3, envelope3);
AudioConnection          patchCord108(mixer3, 0, envmixer2, 2);
AudioConnection          patchCord109(mixer4, envelope4);
AudioConnection          patchCord110(mixer4, 0, envmixer2, 3);
AudioConnection          patchCord111(mixer5, envelope5);
AudioConnection          patchCord112(mixer5, 0, envmixer3, 2);
AudioConnection          patchCord113(mixer6, envelope6);
AudioConnection          patchCord114(mixer6, 0, envmixer3, 3);
AudioConnection          patchCord115(envelope1, 0, envmixer1, 0);
AudioConnection          patchCord116(envelope2, 0, envmixer1, 1);
AudioConnection          patchCord117(envelope3, 0, envmixer2, 0);
AudioConnection          patchCord118(envelope4, 0, envmixer2, 1);
AudioConnection          patchCord119(envelope5, 0, envmixer3, 0);
AudioConnection          patchCord120(envelope6, 0, envmixer3, 1);
AudioConnection          patchCord121(envmixer1, 0, mixerL, 0);
AudioConnection          patchCord122(envmixer1, 0, mixerR, 0);
AudioConnection          patchCord123(envmixer2, 0, mixerL, 1);
AudioConnection          patchCord124(envmixer2, 0, mixerR, 1);
AudioConnection          patchCord125(envmixer3, 0, mixerL, 2);
AudioConnection          patchCord126(envmixer3, 0, mixerR, 2);
AudioConnection          patchCord127(mixerL, 0, i2s1, 0);
AudioConnection          patchCord129(mixerR, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=582.5,180
// GUItool: end automatically generated code







#endif
