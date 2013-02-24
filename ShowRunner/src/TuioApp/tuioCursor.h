/*
 *  tuioCursor.h
 *  oscReceiveForTuio
 *
 *  Created by Ranjit Bhatnagar on 1/30/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __TUIOCURSOR_H__
#define __TUIOCURSOR_H__

class tuioCursor {
    public:
    bool operator<(tuioCursor a);
    bool operator>(tuioCursor a);
    bool operator==(tuioCursor a);
    bool operator!=(tuioCursor a);
	int s;			// sequence #
	float x, y;		// position
	float dx, dy;	// movement
	float m;		// acceleration

	// not from message packet
	int age;		// # of frames since last updated

};

#endif //__TUIOCURSOR_H__
