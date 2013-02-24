#include "CrossVisualization.h"




//--------------------------------------------------------------
void CrossVisualization::setup(){

}

//--------------------------------------------------------------
void CrossVisualization::update(){


    for (cursorMap::iterator i = cursors.begin(); i != cursors.end(); ++i) {
        tuioCursor tc = (i->second);
        makeCross(tc.x, tc.y, tc.dx, tc.dy);
    }
	updateCrosses();
}



void CrossVisualization::makeCross(float x, float y){
	screenCross b(x * ofGetWindowWidth(), y * ofGetWindowHeight());
	crosses.push_back(b);
}

void CrossVisualization::makeCross(float x, float y, float dx, float dy){
	screenCross b(x * ofGetWindowWidth(), y * ofGetWindowHeight(), dx * ofGetWindowWidth(), dy * ofGetWindowHeight());
	crosses.push_back(b);
}


void CrossVisualization::updateCrosses()
{
	list<screenCross>::iterator i;
	for (i=crosses.begin(); i != crosses.end(); ++i)
	{
		if (! i->update())
            i=crosses.erase(i);
	}



}


//--------------------------------------------------------------
void CrossVisualization::draw(){

	/*
	string buf;
	buf = "listening for osc messages on port" + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);

	// draw mouse state
	buf = "mouse: " + ofToString(mouseX, 4) +  " " + ofToString(mouseY, 4);
	ofDrawBitmapString(buf, 430, 20);
	ofDrawBitmapString(mouseButtonState, 580, 20);

	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
	}
	 */
	ofEnableSmoothing();
	ofBackground(0,0,0);
	drawCrosses();

}

void CrossVisualization::drawCrosses()
{
	list<screenCross>::iterator i;
	for (i=crosses.begin(); i != crosses.end(); ++i)
	{
		i->draw();
	}
}

//--------------------------------------------------------------
void CrossVisualization::keyPressed(int key){

}

//--------------------------------------------------------------
void CrossVisualization::keyReleased(int key){

}

//--------------------------------------------------------------
void CrossVisualization::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void CrossVisualization::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void CrossVisualization::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void CrossVisualization::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void CrossVisualization::windowResized(int w, int h){

}

//--------------------------------------------------------------
void CrossVisualization::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void CrossVisualization::dragEvent(ofDragInfo dragInfo){

}
