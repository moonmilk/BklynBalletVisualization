/*
 *  tuioVisContainer.h
 *  bbVisuals
 *
 *  Created by Ranjit Bhatnagar on 2/21/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "tuioVisBase.h";

class tuioVisContainer : public tuioVisBase {
public:
	vector<tuioVisBase> visualizations;
	int currentVisualization;
	
	// override
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void quit();
	virtual bool handleMessage(ofxOscMessage m);
	virtual bool cursorCallback(tuioCursor tc);
	virtual bool frameCallback(int f);
	virtual bool linearCallback(string address, float a);
	virtual bool colorCallback(string address, float r, float g, float b);
	
protected:
	virtual bool stageFade(float alpha);
	float stageFadeAlpha;
};