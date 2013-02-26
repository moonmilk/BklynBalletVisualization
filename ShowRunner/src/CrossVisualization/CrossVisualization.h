#pragma once

#include "ofMain.h"

#include "TuioApp.h"

#include "screenCross.h"



class CrossVisualization : public TuioApp {
public:

	void setup();
	void update();
	void draw();
    void reset();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    void handleOscMessage(ofxOscMessage m);

	list<screenCross> crosses;
	void makeCross(float, float);
	void makeCross(float, float, float, float);
	void updateCrosses();
	void drawCrosses();
    int xalpha;
    int yalpha;
    int colorH;
    int colorS;
    int colorB;
};
