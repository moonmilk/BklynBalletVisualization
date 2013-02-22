/*
 *  tuioVisBase.h
 *  bbVisuals
 *
 *  Created by Ranjit Bhatnagar on 2/21/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "ofxOsc.h"
#include "tuioCursor.h"

#include <set>
using std::set;



class tuioVisBase {
public:

	virtual void init();
	virtual void quit();
	
	// send each message to handleMessage; will return false if it doesn't want it
	virtual bool handleMessage(ofxOscMessage m);
	
	// simulation and graphics:
	virtual void update();
	virtual void draw();

	
protected:
	// add 1-float messages to linearCallbacks, 3-float messages to colorCallbacks
	set<string> linearCallbacks;
	set<string> colorCallbacks;

	virtual bool cursorCallback(tuioCursor tc);
	virtual bool frameCallback(int frameID);
	
	virtual bool linearCallback(string address, float a);
	virtual bool colorCallback(string address, float r, float g, float b);
	
	/*
	// set callbacks - special cases for TUIO:
	void setCursorCallback(cursorCallbackFunction f);
	void removeCursorCallback();
	
	void setFrameCallback(frameCallbackFunction f);
	void removeFrameCallback();
	*/
	
	// set callbacks - generic cases: address is the OSC address
	void addLinearCallback(string address); // OSC message should have one float arg
	void removeLinearCallback(string address);
	void addColorCallback(string address); // three float args
	void removeColorCallback(string address);

};
