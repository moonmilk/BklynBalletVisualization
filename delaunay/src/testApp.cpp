#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	receiver.setup(PORT);

	//ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	ofEnableAlphaBlending();
	ofSetFullscreen(true);
	ofSetFrameRate(30);
	
}


//--------------------------------------------------------------
void testApp::exit(){
}

//--------------------------------------------------------------
void testApp::update(){
	triangulator.reset();
	/*
	triangulator.addPoint(0,0, 0);
	triangulator.addPoint(ofGetViewportWidth(), 0, 0);
	triangulator.addPoint(0, ofGetViewportHeight(), 0);
	triangulator.addPoint(ofGetViewportWidth(), ofGetViewportHeight(), 0);
	*/
	
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
		
		if (m.getAddress() == "/tuio/2Dcur" && m.getNumArgs()==7 && m.getArgType(0)==OFXOSC_TYPE_STRING && m.getArgAsString(0)=="set"){
			tuioCursor tc;
			
			tc.s = m.getArgAsInt32(1);
			tc.x = m.getArgAsFloat(2);
			tc.y = m.getArgAsFloat(3);
			tc.dx = m.getArgAsFloat(4);
			tc.dy = m.getArgAsFloat(5);
			tc.m = m.getArgAsFloat(6);
			tc.age = 0;
			
			string msg_string;
			
			if (cursors.find(tc.s)==cursors.end()) msg_string += "NEW ";
			cursors[tc.s] = tc;
			
		}
		
		else if (m.getAddress() == "/tuio/2Dcur" && m.getNumArgs()==2 && m.getArgType(0)==OFXOSC_TYPE_STRING && m.getArgAsString(0)=="fseq"){
			lastFrame = m.getArgAsInt32(1);
			
		}
	}
		
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
				if (tc->age==3) {
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
void testApp::draw(){
	ofBackground(0,0,0);
	ofSetColor(80,80,80);
	ofNoFill(); 
	triangulator.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

