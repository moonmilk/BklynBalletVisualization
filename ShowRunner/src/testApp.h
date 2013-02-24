#pragma once

#include "ofMain.h"
#include "TuioApp.h"
#include "tuioCursor.h"
#include "ofxOsc.h"

#include "DelaunayVisualization/DelaunayVisualization.h"
#include "FluidVisualization/FluidVisualization.h"
#include "CrossVisualization/CrossVisualization.h"
#include "ParticleVisualization/ParticleVisualization.h"

#include <vector>
#include <map>

#define PORT 3333

class testApp : public ofBaseApp{
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
    private:
        vector<TuioApp *> Visuals;
        int visualIndex;
        map<int,tuioCursor> cursors;
        int lastFrame;
        ofxOscReceiver receiver;
        int frame_stale;
        int prevFrame;
};
