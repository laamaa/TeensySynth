

#ifndef filter_moog_h_
#define filter_moog_h_

#include "Arduino.h"
#include "AudioStream.h"

class AudioFilterMoog: public AudioStream
{
	float g;
	float q;
	float driv;
	float oct;
	float basef;
	
	float y_a;
	float y_b;
	float y_c;
	float y_d;
	float y_d_1;
public:
	AudioFilterMoog() : AudioStream(2, inputQueueArray) {
		frequency(1000);
		resonance(1);
		drive(1);
		octaveControl(1);
		y_a = 0;
		y_b = 0;
		y_c = 0;
		y_d = 0;
		y_d_1 = 0;
	}
	void resonance(float qi) {
		if (qi < 0.7) qi = 0.7;
		else if (qi > 5.0) qi = 5.0;
		q=qi;
	}
	void drive(float d) {
		if (d > 10.0f) d = 10.0f;
		if (d < 0.1f) d = 0.1f;
		driv = d;
	}
	void octaveControl(float n) {
		if (n < 0.0) n = 0.0;
		else if (n > 6.9999) n = 6.9999;
		oct=n;
	}
	void frequency(float freq,bool setf=true) {
		if (freq < 20.0) freq = 20.0;
		else if (freq > AUDIO_SAMPLE_RATE_EXACT/2.5) freq = AUDIO_SAMPLE_RATE_EXACT/2.5;
	    g = 1 - expf(-2 * tanf(2 * M_PI * freq/(2 * AUDIO_SAMPLE_RATE_EXACT)));
		if(setf)
			basef=freq;
	}

	virtual void update(void);
private:
	void update_fixed(const int16_t *in,int16_t *lp);
	void update_variable(const int16_t *in, const int16_t *ctl,	int16_t *lp);
	audio_block_t *inputQueueArray[2];
};

#endif
