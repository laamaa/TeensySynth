#ifndef SYNTHARCH_H
#define SYNTHARCH_H

#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       pitch_lfo;      //xy=65,355
AudioSynthWaveform       pwm_lfo;        //xy=65,404
AudioSynthWaveformModulated waveform1;      //xy=271,139
AudioSynthWaveformModulated waveform1b;     //xy=271,164
AudioSynthWaveformModulated waveform2;      //xy=271,214
AudioSynthWaveformModulated waveform2b;     //xy=271,239
AudioSynthWaveformModulated waveform3;      //xy=271,289
AudioSynthWaveformModulated waveform3b;     //xy=271,314
AudioSynthWaveformModulated waveform4;      //xy=271,364
AudioSynthWaveformModulated waveform4b;     //xy=271,389
AudioSynthWaveformModulated waveform5;      //xy=271,439
AudioSynthWaveformModulated waveform5b;     //xy=271,464
AudioSynthWaveformModulated waveform6;      //xy=271,514
AudioSynthWaveformModulated waveform6b;     //xy=271,539
AudioSynthWaveformModulated waveform7;      //xy=271,589
AudioSynthWaveformModulated waveform7b;     //xy=271,614
AudioSynthWaveformModulated waveform8;      //xy=271,674
AudioSynthWaveformModulated waveform8b;     //xy=271,699
AudioFilterBiquad        biquad7;        //xy=436,586
AudioFilterBiquad        biquad1;        //xy=438,132
AudioFilterBiquad        biquad5;        //xy=437,434
AudioFilterBiquad        biquad2;        //xy=438,211
AudioFilterBiquad        biquad5b;       //xy=437,465
AudioFilterBiquad        biquad6;        //xy=437,512
AudioFilterBiquad        biquad3;        //xy=438,290
AudioFilterBiquad        biquad6b;       //xy=437,543
AudioFilterBiquad        biquad4;        //xy=438,368
AudioFilterBiquad        biquad1b;       //xy=439,166
AudioFilterBiquad        biquad8;        //xy=437,669
AudioFilterBiquad        biquad3b;       //xy=439,322
AudioFilterBiquad        biquad4b;       //xy=439,400
AudioFilterBiquad        biquad2b;       //xy=440,245
AudioFilterBiquad        biquad7b;       //xy=439,618
AudioFilterBiquad        biquad8b;       //xy=441,699
AudioMixer4              waveform_sum_6; //xy=621,541
AudioMixer4              waveform_sum_7; //xy=621,604
AudioMixer4              waveform_sum_8; //xy=621,684
AudioMixer4              waveform_sum_5; //xy=624,461
AudioMixer4              waveform_sum_4; //xy=625,388
AudioMixer4              waveform_sum_2; //xy=626,233
AudioMixer4              waveform_sum_3; //xy=626,315
AudioMixer4              waveform_sum_1; //xy=627,161
AudioSynthWaveformDc     flt_env_carrier; //xy=785,425
AudioEffectEnvelope      flt_env_7;      //xy=938,610
AudioEffectEnvelope      flt_env_4;      //xy=939,393
AudioEffectEnvelope      flt_env_6;      //xy=939,545
AudioEffectEnvelope      flt_env_1;      //xy=941,164
AudioEffectEnvelope      flt_env_5;      //xy=940,467
AudioEffectEnvelope      flt_env_3;      //xy=942,323
AudioEffectEnvelope      flt_env_8;      //xy=942,686
AudioEffectEnvelope      flt_env_2;      //xy=947,238
AudioSynthWaveform       flt_lfo;        //xy=1063,427
AudioMixer4              flt_sum_1;      //xy=1235,164
AudioMixer4              flt_sum_2;      //xy=1235,242
AudioMixer4              flt_sum_3;      //xy=1237,314
AudioMixer4              flt_sum_4;      //xy=1238,395
AudioMixer4              flt_sum_6;      //xy=1238,549
AudioMixer4              flt_sum_7;      //xy=1238,623
AudioMixer4              flt_sum_8;      //xy=1240,696
AudioMixer4              flt_sum_5;      //xy=1241,467
AudioFilterStateVariable filter1;        //xy=1384,165
AudioFilterStateVariable filter2;        //xy=1387,244
AudioFilterStateVariable filter3;        //xy=1389,319
AudioFilterStateVariable filter4;        //xy=1389,398
AudioFilterStateVariable filter5;        //xy=1390,467
AudioFilterStateVariable filter6;        //xy=1391,548
AudioFilterStateVariable filter7;        //xy=1393,621
AudioFilterStateVariable filter8;        //xy=1396,695
AudioMixer4              mixer2;         //xy=1560,250
AudioMixer4              mixer3;         //xy=1560,320
AudioMixer4              mixer1;         //xy=1561,169
AudioMixer4              mixer5;         //xy=1560,466
AudioMixer4              mixer7;         //xy=1560,617
AudioMixer4              mixer4;         //xy=1561,398
AudioMixer4              mixer8;         //xy=1560,695
AudioMixer4              mixer6;         //xy=1561,547
AudioEffectEnvelope      envelope1;      //xy=1760,190
AudioEffectEnvelope      envelope8;      //xy=1758,695
AudioEffectEnvelope      envelope2;      //xy=1760,250
AudioEffectEnvelope      envelope3;      //xy=1760,323
AudioEffectEnvelope      envelope7;      //xy=1759,622
AudioEffectEnvelope      envelope5;      //xy=1761,467
AudioEffectEnvelope      envelope4;      //xy=1762,391
AudioEffectEnvelope      envelope6;      //xy=1762,545
AudioMixer4              envmixer1;      //xy=2020,220
AudioMixer4              envmixer2;      //xy=2020,340
AudioMixer4              envmixer3;      //xy=2020,460
AudioMixer4              envmixer4;      //xy=2025,595
AudioMixer4              env_sum;
AudioMixer4              mix_fx;
AudioMixer4              mixerL;         //xy=2280,280
AudioMixer4              mixerR;         //xy=2283,485
AudioEffectEnsemble      ensemble;
AudioOutputI2S           i2s1;           //xy=2761,355
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
AudioConnection          patchCord13(pitch_lfo, 0, waveform7, 0);
AudioConnection          patchCord14(pitch_lfo, 0, waveform7b, 0);
AudioConnection          patchCord15(pitch_lfo, 0, waveform8, 0);
AudioConnection          patchCord16(pitch_lfo, 0, waveform8b, 0);
AudioConnection          patchCord17(pwm_lfo, 0, waveform1, 1);
AudioConnection          patchCord18(pwm_lfo, 0, waveform2, 1);
AudioConnection          patchCord19(pwm_lfo, 0, waveform3, 1);
AudioConnection          patchCord20(pwm_lfo, 0, waveform4, 1);
AudioConnection          patchCord21(pwm_lfo, 0, waveform5, 1);
AudioConnection          patchCord22(pwm_lfo, 0, waveform6, 1);
AudioConnection          patchCord23(pwm_lfo, 0, waveform1b, 1);
AudioConnection          patchCord24(pwm_lfo, 0, waveform2b, 1);
AudioConnection          patchCord25(pwm_lfo, 0, waveform3b, 1);
AudioConnection          patchCord26(pwm_lfo, 0, waveform4b, 1);
AudioConnection          patchCord27(pwm_lfo, 0, waveform5b, 1);
AudioConnection          patchCord28(pwm_lfo, 0, waveform6b, 1);
AudioConnection          patchCord29(pwm_lfo, 0, waveform7, 1);
AudioConnection          patchCord30(pwm_lfo, 0, waveform7b, 1);
AudioConnection          patchCord31(pwm_lfo, 0, waveform8b, 1);
AudioConnection          patchCord32(waveform1, biquad1);
AudioConnection          patchCord33(waveform1b, biquad1b);
AudioConnection          patchCord34(waveform2, biquad2);
AudioConnection          patchCord35(waveform2b, biquad2b);
AudioConnection          patchCord36(waveform3, biquad3);
AudioConnection          patchCord37(waveform3b, biquad3b);
AudioConnection          patchCord38(waveform4, biquad4);
AudioConnection          patchCord39(waveform4b, biquad4b);
AudioConnection          patchCord40(waveform5, biquad5);
AudioConnection          patchCord41(waveform5b, biquad5b);
AudioConnection          patchCord42(waveform6, biquad6);
AudioConnection          patchCord43(waveform6b, biquad6b);
AudioConnection          patchCord44(waveform7, biquad7);
AudioConnection          patchCord45(waveform7b, biquad7b);
AudioConnection          patchCord46(waveform8, biquad8);
AudioConnection          patchCord47(waveform8b, biquad8b);
AudioConnection          patchCord48(biquad7, 0, waveform_sum_7, 0);
AudioConnection          patchCord49(biquad1, 0, waveform_sum_1, 0);
AudioConnection          patchCord50(biquad5, 0, waveform_sum_5, 0);
AudioConnection          patchCord51(biquad2, 0, waveform_sum_2, 0);
AudioConnection          patchCord52(biquad5b, 0, waveform_sum_5, 1);
AudioConnection          patchCord53(biquad6, 0, waveform_sum_6, 0);
AudioConnection          patchCord54(biquad3, 0, waveform_sum_3, 0);
AudioConnection          patchCord55(biquad6b, 0, waveform_sum_6, 1);
AudioConnection          patchCord56(biquad4, 0, waveform_sum_4, 0);
AudioConnection          patchCord57(biquad1b, 0, waveform_sum_1, 1);
AudioConnection          patchCord58(biquad8, 0, waveform_sum_8, 0);
AudioConnection          patchCord59(biquad3b, 0, waveform_sum_3, 1);
AudioConnection          patchCord60(biquad4b, 0, waveform_sum_4, 1);
AudioConnection          patchCord61(biquad2b, 0, waveform_sum_2, 1);
AudioConnection          patchCord62(biquad7b, 0, waveform_sum_7, 1);
AudioConnection          patchCord63(biquad8b, 0, waveform_sum_8, 1);
AudioConnection          patchCord64(waveform_sum_6, 0, filter6, 0);
AudioConnection          patchCord65(waveform_sum_6, 0, mixer6, 3);
AudioConnection          patchCord66(waveform_sum_7, 0, filter7, 0);
AudioConnection          patchCord67(waveform_sum_8, 0, filter8, 0);
AudioConnection          patchCord68(waveform_sum_5, 0, filter5, 0);
AudioConnection          patchCord69(waveform_sum_5, 0, mixer5, 3);
AudioConnection          patchCord70(waveform_sum_4, 0, filter4, 0);
AudioConnection          patchCord71(waveform_sum_4, 0, mixer4, 3);
AudioConnection          patchCord72(waveform_sum_2, 0, filter2, 0);
AudioConnection          patchCord73(waveform_sum_2, 0, mixer2, 3);
AudioConnection          patchCord74(waveform_sum_3, 0, filter3, 0);
AudioConnection          patchCord75(waveform_sum_3, 0, mixer3, 3);
AudioConnection          patchCord76(waveform_sum_1, 0, filter1, 0);
AudioConnection          patchCord77(waveform_sum_1, 0, mixer1, 3);
AudioConnection          patchCord78(flt_env_carrier, flt_env_1);
AudioConnection          patchCord79(flt_env_carrier, flt_env_2);
AudioConnection          patchCord80(flt_env_carrier, flt_env_3);
AudioConnection          patchCord81(flt_env_carrier, flt_env_4);
AudioConnection          patchCord82(flt_env_carrier, flt_env_5);
AudioConnection          patchCord83(flt_env_carrier, flt_env_6);
AudioConnection          patchCord84(flt_env_carrier, flt_env_7);
AudioConnection          patchCord85(flt_env_carrier, flt_env_8);
AudioConnection          patchCord86(flt_env_7, 0, flt_sum_7, 0);
AudioConnection          patchCord87(flt_env_4, 0, flt_sum_4, 0);
AudioConnection          patchCord88(flt_env_6, 0, flt_sum_6, 0);
AudioConnection          patchCord89(flt_env_1, 0, flt_sum_1, 0);
AudioConnection          patchCord90(flt_env_5, 0, flt_sum_5, 0);
AudioConnection          patchCord91(flt_env_3, 0, flt_sum_3, 0);
AudioConnection          patchCord92(flt_env_8, 0, flt_sum_8, 0);
AudioConnection          patchCord93(flt_env_2, 0, flt_sum_2, 0);
AudioConnection          patchCord94(flt_lfo, 0, flt_sum_1, 1);
AudioConnection          patchCord95(flt_lfo, 0, flt_sum_2, 1);
AudioConnection          patchCord96(flt_lfo, 0, flt_sum_3, 1);
AudioConnection          patchCord97(flt_lfo, 0, flt_sum_4, 1);
AudioConnection          patchCord98(flt_lfo, 0, flt_sum_5, 1);
AudioConnection          patchCord99(flt_lfo, 0, flt_sum_6, 1);
AudioConnection          patchCord100(flt_lfo, 0, flt_sum_7, 1);
AudioConnection          patchCord101(flt_lfo, 0, flt_sum_8, 1);
AudioConnection          patchCord102(flt_sum_1, 0, filter1, 1);
AudioConnection          patchCord103(flt_sum_2, 0, filter2, 1);
AudioConnection          patchCord104(flt_sum_3, 0, filter3, 1);
AudioConnection          patchCord105(flt_sum_4, 0, filter4, 1);
AudioConnection          patchCord106(flt_sum_6, 0, filter6, 1);
AudioConnection          patchCord107(flt_sum_7, 0, filter7, 1);
AudioConnection          patchCord108(flt_sum_8, 0, filter8, 1);
AudioConnection          patchCord109(flt_sum_5, 0, filter5, 1);
AudioConnection          patchCord110(filter1, 0, mixer1, 0);
AudioConnection          patchCord111(filter1, 1, mixer1, 1);
AudioConnection          patchCord112(filter1, 2, mixer1, 2);
AudioConnection          patchCord113(filter2, 0, mixer2, 0);
AudioConnection          patchCord114(filter2, 1, mixer2, 1);
AudioConnection          patchCord115(filter2, 2, mixer2, 2);
AudioConnection          patchCord116(filter3, 0, mixer3, 0);
AudioConnection          patchCord117(filter3, 1, mixer3, 1);
AudioConnection          patchCord118(filter3, 2, mixer3, 2);
AudioConnection          patchCord119(filter4, 0, mixer4, 0);
AudioConnection          patchCord120(filter4, 1, mixer4, 1);
AudioConnection          patchCord121(filter4, 2, mixer4, 2);
AudioConnection          patchCord122(filter5, 0, mixer5, 0);
AudioConnection          patchCord123(filter5, 1, mixer5, 1);
AudioConnection          patchCord124(filter5, 2, mixer5, 2);
AudioConnection          patchCord125(filter6, 0, mixer6, 0);
AudioConnection          patchCord126(filter6, 1, mixer6, 1);
AudioConnection          patchCord127(filter6, 2, mixer6, 2);
AudioConnection          patchCord128(filter7, 0, mixer7, 0);
AudioConnection          patchCord129(filter7, 1, mixer7, 1);
AudioConnection          patchCord130(filter7, 2, mixer7, 2);
AudioConnection          patchCord131(filter8, 0, mixer8, 0);
AudioConnection          patchCord132(filter8, 1, mixer8, 1);
AudioConnection          patchCord133(filter8, 2, mixer8, 2);
AudioConnection          patchCord134(mixer2, envelope2);
AudioConnection          patchCord135(mixer2, 0, envmixer1, 3);
AudioConnection          patchCord136(mixer3, envelope3);
AudioConnection          patchCord137(mixer3, 0, envmixer2, 2);
AudioConnection          patchCord138(mixer1, envelope1);
AudioConnection          patchCord139(mixer1, 0, envmixer1, 2);
AudioConnection          patchCord140(mixer5, envelope5);
AudioConnection          patchCord141(mixer5, 0, envmixer3, 2);
AudioConnection          patchCord142(mixer7, 0, envmixer4, 2);
AudioConnection          patchCord143(mixer7, envelope7);
AudioConnection          patchCord144(mixer4, envelope4);
AudioConnection          patchCord145(mixer4, 0, envmixer2, 3);
AudioConnection          patchCord146(mixer8, 0, envmixer4, 3);
AudioConnection          patchCord147(mixer8, envelope8);
AudioConnection          patchCord148(mixer6, envelope6);
AudioConnection          patchCord149(mixer6, 0, envmixer3, 3);
AudioConnection          patchCord150(envelope1, 0, envmixer1, 0);
AudioConnection          patchCord151(envelope8, 0, envmixer4, 1);
AudioConnection          patchCord152(envelope2, 0, envmixer1, 1);
AudioConnection          patchCord153(envelope3, 0, envmixer2, 0);
AudioConnection          patchCord154(envelope7, 0, envmixer4, 0);
AudioConnection          patchCord155(envelope5, 0, envmixer3, 0);
AudioConnection          patchCord156(envelope4, 0, envmixer2, 1);
AudioConnection          patchCord157(envelope6, 0, envmixer3, 1);
AudioConnection          patchCord158(envmixer1, 0, env_sum, 0);
AudioConnection          patchCord159(envmixer2, 0, env_sum, 1);
AudioConnection          patchCord160(envmixer3, 0, env_sum, 2);
AudioConnection          patchCord161(envmixer4, 0, env_sum, 3);

AudioConnection          patchCord162(env_sum, 0, ensemble, 0);
AudioConnection          patchCord163(ensemble,0,mixerL,1); 
AudioConnection          patchCord164(ensemble,1,mixerR,1);

AudioConnection          patchCord165(env_sum, 0, mixerL, 0);
AudioConnection          patchCord166(env_sum, 0, mixerR, 0);



AudioConnection          patchCord167(mixerL, 0, i2s1, 0);
AudioConnection          patchCord168(mixerR, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=591,84
// GUItool: end automatically generated code









#endif
