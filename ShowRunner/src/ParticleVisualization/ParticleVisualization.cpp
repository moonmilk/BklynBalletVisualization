#include "ParticleVisualization.h"

//--------------------------------------------------------------
void ParticleVisualization::setup(){
}

//--------------------------------------------------------------
void ParticleVisualization::update(){

    for (cursorMap::iterator i = cursors.begin(); i != cursors.end(); ++i) {
        tuioCursor tc = (i->second);
        makeBubble(tc.x, tc.y, tc.dx, tc.dy);
    }
	updateBubbles();
}



void ParticleVisualization::makeBubble(float x, float y){
	screenBubble b(x * ofGetWindowWidth(), y * ofGetWindowHeight());
	bubbles.push_back(b);
}

void ParticleVisualization::makeBubble(float x, float y, float dx, float dy){
	screenBubble b(x * ofGetWindowWidth(), y * ofGetWindowHeight(), dx * ofGetWindowWidth(), dy * ofGetWindowHeight());
	bubbles.push_back(b);
}


void ParticleVisualization::updateBubbles()
{
	list<screenBubble>::iterator i;
	for (i=bubbles.begin(); i != bubbles.end(); ++i)
	{
		if (! i->update())
            i=bubbles.erase(i);
	}



}


//--------------------------------------------------------------
void ParticleVisualization::draw(){

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

	ofBackground(0,0,0);
	drawBubbles();
}

void ParticleVisualization::drawBubbles()
{
	list<screenBubble>::iterator i;
	for (i=bubbles.begin(); i != bubbles.end(); ++i)
	{
		i->draw();
	}
}

//--------------------------------------------------------------
void ParticleVisualization::keyPressed(int key){

}

//--------------------------------------------------------------
void ParticleVisualization::keyReleased(int key){

}

//--------------------------------------------------------------
void ParticleVisualization::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ParticleVisualization::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ParticleVisualization::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ParticleVisualization::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ParticleVisualization::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ParticleVisualization::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ParticleVisualization::dragEvent(ofDragInfo dragInfo){

}
