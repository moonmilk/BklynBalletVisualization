/*
 *  particleVis.cpp
 *  bbVisuals
 *
 *  Created by Ranjit Bhatnagar on 2/21/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "particleVis.h"


void particleVis::init() {
	tuioVisBase::init();
}


bool particleVis::cursorCallback(tuioCursor tc) {
	this->newCursor(tc);
}

bool particleVis::newCursor(tuioCursor tc) {
	ofSetColor(255,255,255);
	ofFill();
	ofCircle(tc.x, tc.y, 10);
	
	return true;
}
