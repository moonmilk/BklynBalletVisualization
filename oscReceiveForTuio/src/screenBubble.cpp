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

#define fade (-0.004)
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
	
	return (age < 1000); 
}

void screenBubble::draw()
{	
	ofFill();
	ofCircle(x, y, radius*exp(fade*age));
}