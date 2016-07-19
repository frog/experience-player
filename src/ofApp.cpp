#include "ofApp.h"
#include "frogUtils.h"

using namespace std;

//----------------------- Constants ------------------------

//static const std::string ofApp::Interaction_Mode_Names[] = { "attract", "engage", "inform" };

//--------------------------------------------------------------
void ofApp::setup(){
    ofLog(OF_LOG_NOTICE, "ofApp::setup");
    
    // setup the modes will abstract this to a plist
    this->Interaction_Mode.push_back("attract");
    this->Interaction_Mode.push_back("engage");
    this->Interaction_Mode.push_back("inform");
    
    
    mode = this->Interaction_Mode[0];
    
    ofBackground(255,255,255);
    ofSetVerticalSync(true);
    movie.load("movies/attract.mov");
    movie.setLoopState(OF_LOOP_NORMAL);
    playMovie();
}

//--------------------------------------------------------------
void ofApp::update(){
    movie.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetHexColor(0xFFFFFF);
    movie.draw(0,0);
    ofSetHexColor(0x000000);
    ofPixels & pixels = movie.getPixels();
    
    int vidWidth = pixels.getWidth();
    int vidHeight = pixels.getHeight();
    int nChannels = pixels.getNumChannels();
    
    if(movie.getIsMovieDone()){
        ofSetHexColor(0xFF0000);
        ofDrawBitmapString("end of attract movie",20,440);
    }

}

//----------------------- MOVIE CONTROL ------------------------

void ofApp::switchMovie(string newMode) {
    movie.load("movies/" + newMode + ".mov");
    movie.play();
}

//---------------------- TRANSPORT CONTROL ---------------------

void ofApp::playMovie() {
    ofLog(OF_LOG_NOTICE, "PLAY");
    movie.play();
    status = STATUS_PLAYING;
}

void ofApp::stopMovie() {
    ofLog(OF_LOG_NOTICE, "STOP");
    movie.stop();
    status = STATUS_STOPPED;
}

void ofApp::pauseMovie() {
    ofLog(OF_LOG_NOTICE, "PAUSE");
    movie.setPaused(true);
    status = STATUS_STOPPED;
}

void ofApp::restartMovie() {
    ofLog(OF_LOG_NOTICE, "RESTART");
    movie.setPaused(true);
    status = STATUS_STOPPED;
}

void ofApp::prevMovie() {
    
    int nextMode;
    int pos = frogUtils::getVectorValuePosition(this->Interaction_Mode, mode);
    
    if ( pos > 0 ) {
        ofLog(OF_LOG_NOTICE, "ONE LOWER");
        nextMode = pos - 1;
    } else {
        ofLog(OF_LOG_NOTICE, "LAST ONE");
        nextMode = (this->Interaction_Mode.size() - 1);
    }
    
    mode = this->Interaction_Mode[nextMode];
    
    switchMovie( this->Interaction_Mode[nextMode] );
    
}

void ofApp::nextMovie() {
    
    int nextMode;
    int pos = frogUtils::getVectorValuePosition(this->Interaction_Mode, mode);
    
    if ( pos < (this->Interaction_Mode.size() - 1) ) {
        ofLog(OF_LOG_NOTICE, "LESS THAN");
        nextMode = pos + 1;
    } else {
        ofLog(OF_LOG_NOTICE, "GREATER THAN");
        nextMode = 0;
    }
    
    mode = this->Interaction_Mode[nextMode];
    
    switchMovie( this->Interaction_Mode[nextMode] );

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
    } else if (key == 44) {
        prevMovie();
    } else if (key == 46) {
        nextMovie();
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
