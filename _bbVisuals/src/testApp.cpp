#include "testApp.h"




//--------------------------------------------------------------
void testApp::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	ofBackground(0,0,0);

	ofEnableAlphaBlending();
	//ofSetFullscreen(true);
	ofSetFrameRate(30);


	visualizationContainer.init();

	visualizationContainer.visualizations.push_back(pv);
}

//--------------------------------------------------------------
void testApp::update(){

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		ofxOscMessage m;
		receiver.getNextMessage(&m);
		visualizationContainer.handleMessage(m);

	}
	
	visualizationContainer.update();
	

}



//--------------------------------------------------------------
void testApp::draw(){
	visualizationContainer.draw();

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
