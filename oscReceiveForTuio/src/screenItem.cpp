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
	age = 0;
	x = _x;
	y = _y;
	dx = 0;
	dy = 0;
}

bool screenItem::update() {	
	age++;
}