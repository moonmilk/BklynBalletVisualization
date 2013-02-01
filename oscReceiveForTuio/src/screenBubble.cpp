/*
 *  screenBubble.cpp
 *  oscReceiveForTuio
 *
 *  Created by Ranjit Bhatnagar on 1/30/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#include "math.h"

#include "screenBubble.h"

#define randf(LO, HI) (LO + (float)rand()/((float)RAND_MAX/(HI-LO)))

#define fade (-0.003)
#define gravity (-0.0001)


screenBubble::screenBubble(float _x, float _y) : screenItem(_x, _y) {
	radius = randf(4,16);
	dx = randf(-0.1,0.1);
	dy = randf(-0.02,0.02);
	flingable = (randf(0,1)<0.5);
}

screenBubble::screenBubble(float _x, float _y, float _dx, float _dy) : screenItem(_x, _y) {
	radius = randf(4,16);
	flingable = (randf(0,1)<0.5);
	if (flingable) {
		dx = _dx * 0.0015;
		dy = _dy * 0.0015;
	}
	else {
		dx = randf(-0.1,0.1);
		dy = randf(-0.02,0.02);
	}
}

// update returns false if it's time to die
bool screenBubble::update()
{
	screenItem::update();
	
	x += dx;
	y += dy;	
	if (age > 200) dy += gravity;
	
	return (age < 2000); 
}

void screenBubble::draw()
{	
	int r,g,b;
	colorTemp(9000 * exp(fade*age), r, g, b);
	
	ofSetColor(r, g, b, 255*exp(fade*age));
	ofFill();
	ofCircle(x, y, radius*exp(fade*age));
}

void screenBubble::colorTemp(int k, int &r, int &g, int &b)
{
	// color temp converter from http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/
	// works for 1000 to 40000 K, white point at about 6500-6600K
	double tmpCalc;
	
	if (k < 1000) k = 1000;
	else if (k > 40000) k = 40000;
	k /= 100;
	
	if (k <= 66) r = 255;
	else {
		tmpCalc = k - 60;
		tmpCalc = 329.698727446 * pow(tmpCalc, -0.1332047592);
		r = tmpCalc;
		if (r < 0) r = 0;
		else if (r > 255) r = 255;
	}
	
	if (k <= 66) {
		tmpCalc = k;
		tmpCalc = 99.4708025861 * log(tmpCalc) - 161.1195681661;
	}
	else {
		tmpCalc = k - 60;
		tmpCalc = 288.1221695283 * pow(tmpCalc, -0.0755148492);
	}
	g = tmpCalc;
	if (g < 0) g = 0;
	else if (g > 255) g = 255;
	
	if (k >= 66) {
		b = 255;
	}
	else if (k <= 19) {
		b = 0;
	}
	else {
		tmpCalc = k - 10;
		tmpCalc = 138.5177312231 * log(tmpCalc) - 305.0447927307;
		b = tmpCalc;
		if (b < 0) b = 0;
		else if (b > 255) b = 255;
	}
		
}