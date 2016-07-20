#include "ofApp.h"
#include "frogUtils.h"


using namespace std;

//----------------------- Constants ------------------------

//static const std::string ofApp::Interaction_Mode_Names[] = { "attract", "engage", "inform" };

ofApp::ofApp(){
    
}

ofApp::~ofApp(){

}


//--------------------------------------------------------------
void ofApp::setup(){
    ofLog(OF_LOG_NOTICE, "ofApp::setup");
    
    TiXmlDocument doc( "/Users/sonny.king/Files/_projects/frogPlayer/bin/data/frogPlayerSettings.xml" );
    bool loaded = doc.LoadFile();
    
    if (loaded) {
        ofLog(OF_LOG_NOTICE, "SETTINGS LOADED");
        
        TiXmlHandle docHandle(&doc);
        TiXmlElement* movie = docHandle.FirstChild( "settings" ).FirstChild( "movies" ).FirstChild( "movie" ).ToElement();
        
        for( movie; movie; movie=movie->NextSiblingElement() ) {
            ofLog(OF_LOG_NOTICE, "READ MOVIE: " + ofToString(movie->GetText()));
            this->Interaction_Mode.push_back(ofToString(movie->GetText()));
        }
        
    } else {
        ofLog(OF_LOG_NOTICE, "SETTINGS FAILED TO LOAD");
    }
    
    mode = this->Interaction_Mode[0];
    
    ofBackground(255,255,255);
    ofSetVerticalSync(true);
    
    movie.setLoopState(OF_LOOP_NORMAL);
    switchMovie(this->Interaction_Mode[0]);
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
    
    int prevMovie;
    int pos = frogUtils::getVectorValuePosition(this->Interaction_Mode, mode);
    
    if ( pos > 0 ) {
        ofLog(OF_LOG_NOTICE, "ONE LOWER");
        prevMovie = pos - 1;
    } else {
        ofLog(OF_LOG_NOTICE, "LAST ONE");
        prevMovie = ( this->Interaction_Mode.size() - 1 );
    }
    
    mode = this->Interaction_Mode[prevMovie];
    
    switchMovie( this->Interaction_Mode[prevMovie] );
    
}

void ofApp::nextMovie() {
    
    int nextMovie;
    int pos = frogUtils::getVectorValuePosition(this->Interaction_Mode, mode);
    
    if ( pos < (this->Interaction_Mode.size() - 1) ) {
        ofLog(OF_LOG_NOTICE, "LESS THAN");
        nextMovie = pos + 1;
    } else {
        ofLog(OF_LOG_NOTICE, "GREATER THAN");
        nextMovie = 0;
    }
    
    mode = this->Interaction_Mode[nextMovie];
    
    switchMovie( this->Interaction_Mode[nextMovie] );

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
