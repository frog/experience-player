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
 
    int baud = 9600;
    sensorStatus = "idle";
    sensorStatusChange = false;

    //TODO - change the port to the arduino one
    // from your terminal run: ll /dev/tty.*
    serial.setup("/dev/tty.usbserial-AD026B1Q", baud);
    serial.flush();
    cout << "SERIAL AVAILABLE?: " << serial.available() << "\n";    
    cout << "TIME: " << ofGetElapsedTimeMillis() << "\n";  

    #ifdef TARGET_OSX
        ofLog(OF_LOG_NOTICE, "SET APPLICATION PATH");
        // Get the absolute location of the executable file in the bundle.
        CFBundleRef appBundle     = CFBundleGetMainBundle();
        CFURLRef	executableURL = CFBundleCopyExecutableURL(appBundle);
        char execFile[4096];
        if (CFURLGetFileSystemRepresentation(executableURL, TRUE, (UInt8 *)execFile, 4096))
        {
            // Strip out the filename to just get the path
            string strExecFile = execFile;
            int found = strExecFile.find_last_of("/");
            string strPath = strExecFile.substr(0, found);
            
            ofLog(OF_LOG_NOTICE, "NEW APPLICATION PATH" + strPath);
            
            // Change the working directory to that of the executable
            if(-1 == chdir(strPath.c_str())) {
                ofLog(OF_LOG_ERROR, "Unable to change working directory to executable's directory.");
            }
        }
        else {
            ofLog(OF_LOG_ERROR, "Unable to identify executable's directory.");
        }  
        CFRelease(executableURL);  
    #endif
    
    
    
    TiXmlDocument doc( "../../../data/frogPlayerSettings.xml" );
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
    
    // movie.setLoopState(OF_LOOP_NONE);
    switchMovie(this->Interaction_Mode[0]);
    movie.setLoopState(OF_LOOP_NORMAL);
}


bool finishedReading = true;

//--------------------------------------------------------------
void ofApp::update(){
    movie.update();

    if ( serial.available() > 3 && finishedReading ) {
        cout << "SERIAL AVAILABLE: " << "\n";  
        finishedReading = false;
        readArduinoSerial();
    }
}

void ofApp::readArduinoSerial(){   
    static string str;
    stringstream ss;
    char ch;
    int ttl = 1000;

    while ((ch=serial.readByte())>0 && ttl>0 && ch!='\n') {
        ss << ch;
    }

    str+=ss.str();

    if (ch == '\n') {

        string tmp=str;
        str="";

        int idling = tmp.find("idle");
        int passing = tmp.find("passing");
        int dwelling = tmp.find("dwell");

        // cout << "STRING: " << tmp <<"\n";
        if ( idling >= 0 ) {
            if ( sensorStatus != "idle" ) {
                sensorStatusChange = true;
                sensorStatus = "idle";
            }
            // cout << "IDLING " << idling <<"\n";
        }

        if ( passing >= 0 ) {
            if ( sensorStatus != "passing" ) {
                sensorStatusChange = true;
                sensorStatus = "passing";
            }
            // cout << "PASSING " << passing <<"\n";
        }

        if ( dwelling >= 0 ) {
            if ( sensorStatus != "dwell" ) {
                sensorStatusChange = true;
                sensorStatus = "dwell";
            }
            // cout << "DWELLING " << dwelling <<"\n";
        }
    }

    finishedReading = true;
}


void ofApp::sensorVideoSwitch(){


    cout << "----------- \n";
    cout << "SVS - SENSOR: " << sensorStatus << " - VECTOR: "<< mode << " - INDEX " << frogUtils::getVectorValuePosition(this->Interaction_Mode, mode) << "\n";
    // cout << "VECTOR INDEX " << frogUtils::getVectorValuePosition(this->Interaction_Mode, mode) << "\n";

    if ( sensorStatus == "idle" ) {
        // cout << "SVS IF IDLE \n";
        movie.setLoopState(OF_LOOP_NORMAL);
        // if movie 0 do nothing
        // if movie is 1 or 2 > go back to 0 and turn repeat on
        if ( frogUtils::getVectorValuePosition(this->Interaction_Mode, mode) == 1 ) {
            // cout << "SVS IF IDLE 1 \n"; 
            prevMovie();
            // switchMovie( this->Interaction_Mode[0]);  
        } else if ( frogUtils::getVectorValuePosition(this->Interaction_Mode, mode) == 2 ) {
            // cout << "SVS IF IDLE 2 \n"; 
            nextMovie();
        }

    } else if ( sensorStatus == "dwell" ) {
        // cout << "SVS IF DWELL " << sensorStatus << "\n";
        // turn of repeat
        // if movie 0 go to 1
        // if movie 1 go to 2

        if ( frogUtils::getVectorValuePosition(this->Interaction_Mode, mode) == 0 ) {
            // cout << "SVS IF DWELL 0 \n";
            nextMovie();
            // movie.setLoopState(OF_LOOP_NONE);
        } else if ( frogUtils::getVectorValuePosition(this->Interaction_Mode, mode) == 1 ) {
            // cout << "SVS IF DWELL 1 \n";
            // nextMovie();
            // movie.setLoopState(OF_LOOP_NONE);
        } else if ( frogUtils::getVectorValuePosition(this->Interaction_Mode, mode) == 2 ) {
            // cout << "SVS IF DWELL 2 \n";
            // prevMovie();
            // movie.setLoopState(OF_LOOP_NONE);
        }

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofRectangle screenRect(0, 0, ofGetWidth(), ofGetHeight());
    ofRectangle videoRect(0, 0, movie.getWidth(), movie.getHeight());
    ofRectangle videoFullscreenRect = videoRect;
    videoFullscreenRect.scaleTo(screenRect, OF_ASPECT_RATIO_KEEP_BY_EXPANDING);
    
    movie.draw(videoFullscreenRect);


    if ( sensorStatusChange ) {
        sensorStatusChange = false;
        sensorVideoSwitch();
    }

    // cout << "SENSOR Mode " << sensorStatus << "\n";
    // cout << "VECTOR Mode " << mode << "\n";
    // cout << "VECTOR VALUE POSITION " << frogUtils::getVectorValuePosition(this->Interaction_Mode, mode) << "\n";

    if(movie.getIsMovieDone()){
        // cout << "MOVIE IS DONE " << sensorStatus << "\n";
        // check which mode player is on
        // if it is on mode 'engage' index 1
        // move back to 'attract' index 0
        if ( sensorStatus == "dwell" ) {
            // cout << "SVS IF DWELL " << sensorStatus << "\n";
            if ( frogUtils::getVectorValuePosition(this->Interaction_Mode, mode) == 0 ) {
                cout << "GIMD 0 \n";
                // cout << "SVS IF DWELL 0 \n";
                nextMovie();
                // movie.setLoopState(OF_LOOP_NONE);
            } else if ( frogUtils::getVectorValuePosition(this->Interaction_Mode, mode) == 1 ) {
                cout << "GIMD 1 \n";
                // nextMovie();
                // movie.setLoopState(OF_LOOP_NONE);
            } else if ( frogUtils::getVectorValuePosition(this->Interaction_Mode, mode) == 2 ) {
                cout << "GIMD 2 \n";
                // prevMovie();
                // movie.setLoopState(OF_LOOP_NONE);
            }

        }
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
    //space bar
    if (key == 32) {
        toggleTransport();
    //, character
    } else if (key == 44) {
        prevMovie();
    //. character    
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
