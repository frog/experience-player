#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

using namespace std;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    private:
        void playMovie();
        void stopMovie();
        void pauseMovie();
        void nextMovie();
        void prevMovie();
        void restartMovie();
        void toggleTransport();
        
        ofVideoPlayer 		movie;

        enum Transport_Status {
            STATUS_PLAYING,
            STATUS_STOPPED
        };
        
        Transport_Status status;
    
        vector<string> Interaction_Mode;
    
        string mode;
    
        void switchMovie(string newMode);
    
    
};
