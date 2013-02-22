/*
 *  particleVis.h
 *  bbVisuals
 *
 *  Created by Ranjit Bhatnagar on 2/21/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#include "tuioVisBase.h";


class particleVis : public tuioVisBase {

public:
	// override:
	void init();
	// quit();
	//update();
	//draw();
	// bool handleMessage();
	

protected:
	// override:
	bool cursorCallback(tuioCursor);
						
	// fresh:
	bool newCursor(tuioCursor);
};