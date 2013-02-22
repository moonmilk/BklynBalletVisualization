/*
 *  tuioVisContainer.cpp
 *  bbVisuals
 *
 *  Created by Ranjit Bhatnagar on 2/21/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "tuioVisContainer.h"


void tuioVisContainer::init() {
	
	currentVisualization = -1; // none
	ofEnableAlphaBlending();
	
	// OSC message: /stage/fade [0.-1.] -- fade to black (at 0)
	
	addLinearCallback("/stage/fade");
}

void tuioVisContainer::quit() {
	
}

bool tuioVisContainer::handleMessage(ofxOscMessage m) {
	// if no current vis or current vis doesn't want this message, handle it myself
	if (currentVisualization < 0 || ! visualizations[currentVisualization].handleMessage(m)) {
		tuioVisBase::handleMessage(m);
	}
}

bool tuioVisContainer::cursorCallback(tuioCursor tc) {
	
}
bool tuioVisContainer::frameCallback(int f) {
	
}


bool tuioVisContainer::linearCallback(string address, float t) {
	if (address=="/stage/fade") return this->stageFade(t);
	
	else return false;
}

bool tuioVisContainer::colorCallback(string address, float r, float g, float b) {
	
	return false;
}



bool tuioVisContainer::stageFade(float alpha) {
	stageFadeAlpha = alpha;
	return true;
}

void tuioVisContainer::update() {
	if (currentVisualization >= 0) visualizations[currentVisualization].update();
}

void tuioVisContainer::draw() {
	if (currentVisualization >= 0) visualizations[currentVisualization].draw();
	
	// draw the fade curtain, if any
	if (stageFadeAlpha < 1.0) {
		ofSetColor(0, 0, 0, 255*(1.0 - stageFadeAlpha));
		ofRect(0, 0, ofGetViewportWidth(), ofGetViewportHeight());
	}
}