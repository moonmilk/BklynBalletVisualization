/*
 *  screenItem.h
 *  oscReceiveForTuio
 *
 *  Created by Ranjit Bhatnagar on 1/30/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

class screenItem {
public:
	screenItem(float, float);
	
	float x, y;
	float dx, dy;
	int age;
	
	bool update();
	void draw();
};