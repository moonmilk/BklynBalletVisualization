/*
 *  tuioCursor.h
 *  oscReceiveForTuio
 *
 *  Created by Ranjit Bhatnagar on 1/30/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

class tuioCursor {
public:
	int s;			// sequence #
	float x, y;		// position
	float dx, dy;	// movement
	float m;		// acceleration
	
	// not from message packet
	int age;		// # of frames since last updated
	
};
