#pragma once

#include "ofMain.h"

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
    
        void playMovie();
        void stopMovie();
        void pauseMovie();
        void restartMovie();
        void toggleTransport();
    
        ofVideoPlayer 		attractMovie;
        ofVideoPlayer 		engageMovie;
        ofVideoPlayer 		informMovie;
        ofVideoPlayer 		currentMovie;
    
        enum Transport_Status {
            STATUS_PLAYING,
            STATUS_STOPPED
        };
    
        Transport_Status status;
    
        enum Interaction_Mode {
            MODE_ATTRACT,
            MODE_ENGAGE,
            MODE_INFORM
        };
    
        Interaction_Mode mode;
    
        void switchMovie(Interaction_Mode newMode);
		
};
