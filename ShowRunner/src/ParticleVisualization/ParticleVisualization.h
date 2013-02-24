#pragma once

#include "ofMain.h"
#include "TuioApp.h"
#include "screenBubble.h"


class ParticleVisualization : public TuioApp {
public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	
	list<screenBubble> bubbles;
	void makeBubble(float, float);
	void makeBubble(float, float, float, float);
	void updateBubbles();
	void drawBubbles();
	
};
