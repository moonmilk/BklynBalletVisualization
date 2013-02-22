/*
 *  tuioVisBase.cpp
 *  bbVisuals
 *
 *  Created by Ranjit Bhatnagar on 2/21/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "tuioVisBase.h"


void init() {
}
void quit() {
}
void update() {
}
void draw() {
}


void tuioVisBase::addLinearCallback(string address) {
	linearCallbacks.insert(address);
}
void tuioVisBase::removeLinearCallback(string address) {
	linearCallbacks.erase(address);
}
void tuioVisBase::addColorCallback(string address){
	colorCallbacks.insert(address);
}
void tuioVisBase::removeColorCallback(string address) {
	colorCallbacks.erase(address);
}


bool tuioVisBase::handleMessage(ofxOscMessage m) {
	string address = m.getAddress();
	
	// special cases first:
	if (address=="/tuio/2dcur" && m.getNumArgs()==7 && m.getArgType(0)==OFXOSC_TYPE_STRING && m.getArgAsString(0)=="set") {
		tuioCursor tc;
		
		tc.s = m.getArgAsInt32(1);
		tc.x = m.getArgAsFloat(2);
		tc.y = m.getArgAsFloat(3);
		tc.dx = m.getArgAsFloat(4);
		tc.dy = m.getArgAsFloat(5);
		tc.m = m.getArgAsFloat(6);
		tc.age = 0;
		
		return cursorCallback(tc);
	}
	
	else if (address=="/tuio/2Dcur" && m.getNumArgs()==2 && m.getArgType(0)==OFXOSC_TYPE_STRING && m.getArgAsString(0)=="fseq") {
		return frameCallback(m.getArgAsInt32(1));
	}
	
	else if (linearCallbacks.find(address) != linearCallbacks.end() && m.getNumArgs()==1) {
		return linearCallback(address, m.getArgAsFloat(0));
	}
	
	else if (colorCallbacks.find(address) != colorCallbacks.end() && m.getNumArgs()==3) {
		return colorCallback(address, m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
	}
	
	// message not handled:
	else return false;
}



bool tuioVisBase::cursorCallback(tuioCursor tc) {
}
bool tuioVisBase::frameCallback(int frameID){
}

bool tuioVisBase::linearCallback(string address, float a) {
}
bool tuioVisBase::colorCallback(string address, float r, float g, float b){
}

