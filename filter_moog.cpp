/* Audio Library for Teensy 3.X
 * Copyright (c) 2014, Paul Stoffregen, paul@pjrc.com
 *
 * Development of this audio library was funded by PJRC.COM, LLC by sales of
 * Teensy and Audio Adaptor boards.  Please support PJRC's efforts to develop
 * open source software by purchasing Teensy or other PJRC products.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "filter_moog.h"
#include "utility/dspinst.h"
#include "arm_math.h"

void AudioFilterMoog::update_fixed(const int16_t *in,int16_t *lp)
{
    const float MAX_INT = 32678.0;
 	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
 		float cs = (float)in[i];
		cs=cs/MAX_INT;
		cs = tanhf(cs * driv);
		y_a = y_a + g * (tanhf(cs - q * ((y_d_1 + y_d)/2) - tanhf(y_a)));
		y_b = y_b + g * (tanhf(y_a) - tanhf(y_b));
		y_c = y_c + g * (tanhf(y_b) - tanhf(y_c));
		y_d_1 = y_d;
		y_d = y_d + g * (tanhf(y_c) - tanhf(y_d));
		cs=(y_d<-1?-1:y_d>1?0.999:y_d)*MAX_INT;
		lp[i]  = (int16_t)cs;
	}
}


void AudioFilterMoog::update_variable(const int16_t *in,const int16_t *ctl, int16_t *lp)
{
    const float MAX_INT = 32678.0;
 	float cs = (float)ctl[0];
	cs=cs/MAX_INT;
	float nf=basef*(exp2f(cs*oct));
//	Serial.println(nf);
	frequency(nf,false);
	update_fixed(in,lp)	;
}


void AudioFilterMoog::update(void)
{
	audio_block_t *input_block=NULL, *control_block=NULL;
	audio_block_t *lowpass_block=NULL;

	input_block = receiveReadOnly(0);
	control_block = receiveReadOnly(1);
	if (!input_block) {
		if (control_block) release(control_block);
		return;
	}
	lowpass_block = allocate();
	if (!lowpass_block) {
		release(input_block);
		if (control_block) release(control_block);
		return;
	}

	if (control_block) {
		update_variable(input_block->data, control_block->data, lowpass_block->data);
		release(control_block);
	} else {
		update_fixed(input_block->data, lowpass_block->data);
	}
	release(input_block);
	transmit(lowpass_block, 0);
	release(lowpass_block);
	return;
}


