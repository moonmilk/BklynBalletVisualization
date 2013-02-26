/*
 *  screenCross.h
 *  oscReceiveForTuio
 *
 *  Created by Ranjit Bhatnagar on 1/30/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "screenItem.h"
#include "ofMain.h"

class screenCross: screenItem
{
public:
	screenCross(float, float);
	screenCross(float, float, float, float);

	float radius;
	bool flingable;
	float tilt;
	float margin;


	bool update();
	void draw();
	void colorTemp(int k, int &r, int &g, int &b);
    int xalpha;
    int yalpha;
    int colorH;
    int colorS;
    int colorB;
};

