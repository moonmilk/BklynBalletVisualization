#pragma once
#include "TuioApp.h"
#include "oscReceiver.h"
#include "DelaunayVisualization/DelaunayVisualization.h"
#include "FluidVisualization/FluidVisualization.h"
#include "CrossVisualization/CrossVisualization.h"
#include "ParticleVisualization/ParticleVisualization.h"

#include <vector>
#include <map>
typedef vector<TuioApp *>::iterator visIterator;

class ShowRunner : public TuioApp{
	public:
		ShowRunner():receiver(this){}
		void setup();
        void reset();
		void update();
		void draw();
        void updateTuioPoints(cursorMap input_tuioCursors);
        void handleOscMessage(ofxOscMessage m);

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
        oscReceiver receiver;

        //curtain settings
        int curtainAlpha;
        int curtainX;
        int curtainY;
        //tuio settings
        float tuioYScale;
        float tuioXScale;
        float tuioYPos;
        float tuioXPos;
        bool tuioInvertY;
        bool tuioInvertX;
        bool tuioInhibit;

        void oscTuioDispatch(ofxOscMessage m);
        void oscCurtainDispatch(ofxOscMessage m);
};
