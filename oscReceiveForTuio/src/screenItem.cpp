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
	clock_gettime(CLOCK_REALTIME,&birth);
	age = 0.0;
	x = _x;
	y = _y;
	dx = 0;
	dy = 0;
}

bool screenItem::update() {
	timespec now;
	clock_gettime(CLOCK_REALTIME,&now);

	age=now.tv_sec-birth.tv_sec;
	age=age + ((double)(now.tv_nsec-birth.tv_nsec)/1000000000.0);
}
