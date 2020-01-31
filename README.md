## TeensySynth - a polyphonic MIDI synthesizer for Teensy 3.x

This is laamaa's fork of [jmechnich's](https://github.com/jmechnich/TeensySynth/) TeensySynth polyphonic MIDI synthesizer.

Pros:
* Second oscillator for all voices
* Pitch LFO
* Filter LFO
* Filter Envelope
* PWM
* TouchOSC layout for MIDI control

Cons:
* Only 7 voice polyphony to ensure functionality with Teensy 3.2 / 3.1 (96mhz overclock)

---

### Features
* 8-voice polyphony
* 7 waveforms: sine, square, triangle, sawtooth, reverse sawtooth, pulse, sample & hold
* filter and amplitube envelope per voice
* MONO and POLY mode
* Portamento
* MIDI via USB or serial pins

### Supported MIDI controls
* Channel volume
* Channel pan
* Sustain pedal
* Envelope controls
* Filter controls
* Effect controls
* Portamento controls

For details refer to [controls.txt](https://raw.githubusercontent.com/jmechnich/TeensySynth/master/controls.txt).

### Wishlist
 * Arpeggiator
 * Filter LFO/envelope
 * Modulation
 * improve filter / implement proper gain attenuation

### Useful links
* [Teensy Audio Library](http://www.pjrc.com/teensy/td_libs_Audio.html)
* [Audio System Design Tool for Teensy Audio Library](http://www.pjrc.com/teensy/gui/)
* [MIDI controller number](http://www.indiana.edu/~emusic/cntrlnumb.html)
