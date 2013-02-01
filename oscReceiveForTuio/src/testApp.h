#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#include "tuioCursor.h"

#include "screenBubble.h"



// listen on port 12345
#define PORT 3333
#define NUM_MSG_STRINGS 20

class testApp : public ofBaseApp {
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

	ofTrueTypeFont font;
	ofxOscReceiver receiver;

	int current_msg_string;
	string msg_strings[NUM_MSG_STRINGS];
	float timers[NUM_MSG_STRINGS];

	int mouseX, mouseY;
	string mouseButtonState;

	// added by ranjit
	typedef map<int, tuioCursor> cursorMap;
	cursorMap cursors;
	
	int lastFrame; // tuio frame number
	
	list<screenBubble> bubbles;
	void makeBubble(float, float);
	void makeBubble(float, float, float, float);
	void updateBubbles();
	void drawBubbles();
	
};
