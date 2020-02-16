## TeensySynth - a polyphonic MIDI synthesizer for Teensy 4.0

This is laamaa's fork of [jmechnich's](https://github.com/jmechnich/TeensySynth/) TeensySynth polyphonic MIDI synthesizer.

Development currently done for Teensy 4.0, lighter 3.2 compatible code can be found in a separate branch.

Requirements:
* Teensy 4.0 or something as powerful
* Quarterturn's Teensy Ensemble Chorus effect: https://github.com/quarterturn/teensy3-ensemble-chorus

Additions to the original:
* Presets
* Second oscillator for all voices
* Pitch LFO
* Filter LFO
* Filter Envelope
* PWM
* Warm ensemble chorus by [Quarterturn](https://github.com/quarterturn/teensy3-ensemble-chorus)
* TouchOSC layout for MIDI control

Things worse than in the original:
* Requires more power
* Nice code was turned into a mess
* Documentation is horribly out of date since I change stuff all the time

---

## Original readme:

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
