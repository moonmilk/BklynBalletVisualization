/*
 *  screenItem.cpp
 *  oscReceiveForTuio
 *
 *  Created by Ranjit Bhatnagar on 1/30/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#include "screenItem.h"
screenItem::screenItem(float _x, float _y) {
	birth=ofGetElapsedTimeMicros();
	age = 0.0;
	x = _x;
	y = _y;
	dx = 0;
	dy = 0;
}

bool screenItem::update() {
	unsigned long long now;
	now=ofGetElapsedTimeMicros();

	age=((double)(now-birth)/1000000.0);
}
