/*
 *  screenItem.h
 *  oscReceiveForTuio
 *
 *  Created by Ranjit Bhatnagar on 1/30/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _SCREENITEM_H
#define _SCREENITEM_H

#include "ofMain.h"

class screenItem {
public:
	screenItem(float, float);

	float x, y;
	float dx, dy;
	double age;
    unsigned long long birth;
	bool update();
	void draw();
};

#endif