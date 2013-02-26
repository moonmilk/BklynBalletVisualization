#ifndef _DELAUNAYVISUALIZATION_H
#define _DELAUNAYVISUALIZATION_H

#include "ofMain.h"
#include "ofxDelaunay.h"
#include "ofxOsc.h"

#include "TuioApp.h"

#define PORT 3333

// should points collapse towards center of mass, or remain static?
#define COLLAPSING 1

#include <tr1/unordered_map>


class DelaunayVisualization : public TuioApp{
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
        void updateTuioPoints(cursorMap input_tuioCursors);
        void handleOscMessage(ofxOscMessage m);
        int colorH;
        int colorS;
        int colorB;

};

#endif
