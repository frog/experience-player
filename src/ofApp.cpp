#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofLog(OF_LOG_NOTICE, "ofApp::setup");
    
    mode = MODE_ATTRACT;
    
    ofBackground(255,255,255);
    ofSetVerticalSync(true);
    attractMovie.load("movies/attract.mov");
    attractMovie.setLoopState(OF_LOOP_NORMAL);
    currentMovie = attractMovie;
    playMovie();
}

//--------------------------------------------------------------
void ofApp::update(){
    currentMovie.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xFFFFFF);
    currentMovie.draw(0,0);
    ofSetHexColor(0x000000);
    ofPixels & pixels = attractMovie.getPixels();
    
    int vidWidth = pixels.getWidth();
    int vidHeight = pixels.getHeight();
    int nChannels = pixels.getNumChannels();
    
    if(currentMovie.getIsMovieDone()){
        ofSetHexColor(0xFF0000);
        ofDrawBitmapString("end of attract movie",20,440);
    }

}

//---------------------- TRANSPORT CONTROL ---------------------

void ofApp::switchMovie(Interaction_Mode newMode) {
    currentMovie.load("mov");
}

//---------------------- TRANSPORT CONTROL ---------------------

void ofApp::playMovie() {
    ofLog(OF_LOG_NOTICE, "PLAY");
    currentMovie.play();
    status = STATUS_PLAYING;
}

void ofApp::stopMovie() {
    ofLog(OF_LOG_NOTICE, "STOP");
    currentMovie.stop();
    status = STATUS_STOPPED;
}

void ofApp::pauseMovie() {
    ofLog(OF_LOG_NOTICE, "PAUSE");
    currentMovie.setPaused(true);
    status = STATUS_STOPPED;
}

void ofApp::restartMovie() {
    ofLog(OF_LOG_NOTICE, "RESTART");
    currentMovie.setPaused(true);
    status = STATUS_STOPPED;
}

void ofApp::toggleTransport() {
    if (status == STATUS_PLAYING) {
        pauseMovie();
    } else {
        playMovie();
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofLog(OF_LOG_NOTICE, "KEY INTERACTION " + ofToString(key));
    if (key == 32) {
        toggleTransport();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
