#include "DelaunayVisualization.h"

//--------------------------------------------------------------
void DelaunayVisualization::setup(){


	//ofSetFrameRate(60);


}


//--------------------------------------------------------------
void DelaunayVisualization::exit(){
}

//--------------------------------------------------------------
void DelaunayVisualization::updateTuioPoints(cursorMap input_tuioCursors){
    for(cursorMap::iterator cursor=input_tuioCursors.begin();cursor!=input_tuioCursors.end();++cursor){
        int idx=cursor->first;
        tuioCursor tc=cursor->second;
        if(tc.age <= 1){
            cursors[idx]=tc;
        }
    }
}
void DelaunayVisualization::update(){
	triangulator.reset();
	/*
	triangulator.addPoint(0,0, 0);
	triangulator.addPoint(ofGetViewportWidth(), 0, 0);
	triangulator.addPoint(0, ofGetViewportHeight(), 0);
	triangulator.addPoint(ofGetViewportWidth(), ofGetViewportHeight(), 0);
	*/


	vector<int> reaper;

	ofPoint centerOfMass;
	float totalWeight = 0;

	for (cursorMap::iterator i = cursors.begin(); i != cursors.end(); ++i) {
		tuioCursor *tc = &(i->second);
		float weight = (150 - tc->age); // fresh points weigh 3 times more than oldest ones
		totalWeight += weight;

		centerOfMass.x += tc->x * weight;
		centerOfMass.y += tc->y * weight;
	}
	centerOfMass.x /= totalWeight; //cursors.size();
	centerOfMass.y /= totalWeight; //cursors.size();

	for (cursorMap::iterator i = cursors.begin(); i != cursors.end(); ++i) {
		tuioCursor *tc = &(i->second);
		if (++tc->age < 100) {
			if (COLLAPSING) {
				triangulator.addPoint(tc->x * ofGetViewportWidth(), tc->y * ofGetViewportHeight(), 0);
				if (tc->age<=3) {
					tc->dx = 0;
					tc->dy = 0;
				}
				if (tc->age > 3) {
					tc->x += tc->dx;
					tc->y += tc->dy;
					tc->dx += (tc->x > centerOfMass.x) ? -0.00003 : 0.00003;
					tc->dy += (tc->y > centerOfMass.y) ? -0.00003 : 0.00003;

					// friction
					//float v = sqrt(tc->dx*tc->dx + tc->dy*tc->dy);


				}
			}
		}
		else {
			reaper.push_back(i->first);
		}
	}

	for (vector<int>::iterator i = reaper.begin(); i != reaper.end(); ++i) {
		cursors.erase(*i);
	}

	// triangulator.addPoint(tc.x * ofGetViewportWidth(), tc.y * ofGetViewportHeight(), 0);
	triangulator.triangulate();
}

//--------------------------------------------------------------
void DelaunayVisualization::draw(){
	ofBackground(0,0,0);
	ofSetColor(80,80,80);
	ofNoFill();
	triangulator.draw();
}

//--------------------------------------------------------------
void DelaunayVisualization::keyPressed(int key){

}

//--------------------------------------------------------------
void DelaunayVisualization::keyReleased(int key){

}

//--------------------------------------------------------------
void DelaunayVisualization::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void DelaunayVisualization::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void DelaunayVisualization::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void DelaunayVisualization::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void DelaunayVisualization::windowResized(int w, int h){

}

