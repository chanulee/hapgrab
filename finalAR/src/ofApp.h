#pragma once

#include "ofMain.h"
#include "ofxSimpleSerial.h"
#include "ofUtils.h"
#include <vector>

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
    
        void onNewMessage(string & message);
    
        ofxSimpleSerial serial;
        string message;

    string aXS;
    string aYS;
    string aZS;
    string gyroXS;
    string gyroYS;
    string gyroZS;

    string flexS;
        
    float xVal;
    float yVal;
    float zVal;
    float gyroX;
    float gyroY;
    float gyroZ;
    int flex;
    
    ofVec3f gyroVec;

    string str0;

    int cX=0;
    int cY=0;
    
    ofEasyCam cam;
     
    vector<glm::vec3> base_location_list;
    vector<ofColor> base_color_list;

    vector<vector<glm::vec3>> log_list;
    vector<ofColor> color_list;
    vector<float> life_list;
    
    float rotate;
    
//    ofxPanel gui;
    ofParameter <int> uiAmount;
    ofParameter <ofVec3f> uiPower;
//    ofParameter <float> uiRadius;
    ofParameter <ofVec2f> uiPosition;
    
};
