#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxDelaunay.h"
#include "ofxOsc.h"

#include "tuioCursor.h"

#define PORT 3333

// should points collapse towards center of mass, or remain static?
#define COLLAPSING 1

#include <tr1/unordered_map>


class testApp : public ofBaseApp{
	private:
		ofxDelaunay triangulator;

	public:
		void setup();
		void exit();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
		ofxOscReceiver receiver;

	typedef tr1::unordered_map<int, tuioCursor> cursorMap;
		cursorMap cursors;
	
		int lastFrame;
};

#endif
