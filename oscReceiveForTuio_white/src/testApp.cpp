#include "testApp.h"


#define randf(LO, HI) (LO + (float)rand()/((float)RAND_MAX/(HI-LO)))


//--------------------------------------------------------------
void testApp::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	current_msg_string = 0;
	mouseX = 0;
	mouseY = 0;
	mouseButtonState = "";

	ofBackground(0,0,0);

	ofEnableAlphaBlending();
	ofSetFullscreen(true);
	ofSetFrameRate(30);


	lastFrame = 0;
}

//--------------------------------------------------------------
void testApp::update(){

	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

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

			msg_string += ofToString(tc.s) + ": " + ofToString((int)(1024*tc.x)) + ", " + ofToString((int)(768*tc.y));

			msg_strings[current_msg_string] = msg_string;
			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
            //if(randf(0,1) < 0.50){
                makeBubble(tc.x, tc.y, tc.dx, tc.dy);
            //}
		}

		else if (m.getAddress() == "/tuio/2Dcur" && m.getNumArgs()==2 && m.getArgType(0)==OFXOSC_TYPE_STRING && m.getArgAsString(0)=="fseq"){
			lastFrame = m.getArgAsInt32(1);

			msg_strings[current_msg_string] = "FRAME " + ofToString(lastFrame);



			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
		}

		else{
			// unrecognized message: display on the bottom of the screen
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for(int i = 0; i < m.getNumArgs(); i++){
				// get the argument type
				msg_string += m.getArgTypeName(i);
				msg_string += ":";
				// display the argument - make sure we get the right type
				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
					msg_string += ofToString(m.getArgAsInt32(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
					msg_string += ofToString(m.getArgAsFloat(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
					msg_string += m.getArgAsString(i);
				}
				else{
					msg_string += "unknown";
				}
				msg_string += " ";
			}
			// add to the list of strings to display
			msg_strings[current_msg_string] = msg_string;
			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
		}


	}

	updateBubbles();
}



void testApp::makeBubble(float x, float y){
	screenBubble b(x * ofGetWindowWidth(), y * ofGetWindowHeight());
	bubbles.push_back(b);
}

void testApp::makeBubble(float x, float y, float dx, float dy){
	screenBubble b(x * ofGetWindowWidth(), y * ofGetWindowHeight(), dx * ofGetWindowWidth(), dy * ofGetWindowHeight());
	bubbles.push_back(b);
}


void testApp::updateBubbles()
{
	list<screenBubble>::iterator i;
	for (i=bubbles.begin(); i != bubbles.end(); ++i)
	{
		if (! i->update())
            i=bubbles.erase(i);
	}



}


//--------------------------------------------------------------
void testApp::draw(){

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

void testApp::drawBubbles()
{
	list<screenBubble>::iterator i;
	for (i=bubbles.begin(); i != bubbles.end(); ++i)
	{
		i->draw();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

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

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
