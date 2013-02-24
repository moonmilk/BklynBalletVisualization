/*
 *  screenBubble.h
 *  oscReceiveForTuio
 *
 *  Created by Ranjit Bhatnagar on 1/30/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "screenItem.h"
#include "ofMain.h"

class screenBubble: screenItem
{
public:
	screenBubble(float, float);
	screenBubble(float, float, float, float);

	float radius;
	bool flingable;


	bool update();
	void draw();

	void colorTemp(int k, int &r, int &g, int &b);
};

