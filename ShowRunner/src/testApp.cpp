#include "testApp.h"
#define NUM_VISUALS 4
//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0, 0, 0);
    ofHideCursor();
    ofSetFullscreen(true);
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    frame_stale=0;
    prevFrame=0;
    lastFrame=0;


    TuioApp *fluid = new FluidVisualization();
    TuioApp *cross = new CrossVisualization();
    TuioApp *delaunay = new DelaunayVisualization();
    TuioApp *particle = new ParticleVisualization();
    
    Visuals.push_back(fluid);
    Visuals.push_back(cross);
    Visuals.push_back(delaunay);
    Visuals.push_back(particle);

    visualIndex=0;
    receiver.setup(PORT);
    Visuals[0]->setup();
    Visuals[1]->setup();
    Visuals[2]->setup();
    Visuals[3]->setup();
}

//--------------------------------------------------------------
void testApp::update(){
	// check for waiting messages
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
			if(lastFrame != m.getArgAsInt32(1)){
                vector<map<int,tuioCursor>::iterator> stale_cursors;
                for(map<int,tuioCursor>::iterator cursor=cursors.begin();cursor!=cursors.end();++cursor){
                    tuioCursor *tc=&(cursor->second);
                    if (++tc->age > 5){
                        stale_cursors.push_back(cursor);
                    }
                }
                for(vector<map<int,tuioCursor>::iterator>::iterator stale = stale_cursors.begin();stale != stale_cursors.end();++stale){
                    cursors.erase(*stale);
                }
                Visuals[visualIndex]->updateTuioPoints(cursors);
                lastFrame=m.getArgAsInt32(1);
			}

		}
	}
    if (prevFrame == lastFrame){
        frame_stale++;
        if (frame_stale >= 5){
            cursors.clear();
            Visuals[visualIndex]->updateTuioPoints(cursors);
        }
    } else {
        frame_stale=0;
        prevFrame=lastFrame;
    }

    Visuals[visualIndex]->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    Visuals[visualIndex]->draw();
    ofPushStyle();
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(0,0,0,128);
    ofRect(0,0,ofGetViewportWidth(),ofGetViewportHeight());
    ofPopStyle();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key){
        case '+':
            visualIndex=(visualIndex+1)% NUM_VISUALS;
            ofEnableAlphaBlending();
            ofEnableSmoothing();
            break;
        case '-':
            visualIndex=(visualIndex-1);
            if (visualIndex < 0){
                visualIndex=NUM_VISUALS-1;
            }
            ofEnableAlphaBlending();
            ofEnableSmoothing();
            break;
        default:
            Visuals[visualIndex]->keyPressed(key);
        }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    Visuals[visualIndex]->keyReleased(key);
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
