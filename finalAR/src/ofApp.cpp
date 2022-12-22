#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    cam.setDistance(200);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    if(!serial.setup("/dev/cu.sunnyAlpha", 9600)) {
         // log and error and leave
         ofLogError() << "could not open serial port - listing serial devices";
         serial.listDevices();
         OF_EXIT_APP(0);
    }
    
    ofSetWindowTitle("chanu final project");
    ofSetLineWidth(2);
    ofSetCircleResolution(128);
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0);
    ofNoFill();
    ofEnableDepthTest();
    ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

    ofColor color;
    vector<int> hex_list = { 0xf72585, 0xb5179e, 0x7209b7, 0x480ca8, 0x3f37c9, 0x4cc9f0 };

    for (auto hex : hex_list) {

        color.setHex(hex);
        this->base_color_list.push_back(color);
    }

    auto ico_sphere = ofIcoSpherePrimitive(300, 7);
    for (auto& vertex : ico_sphere.getMeshPtr()->getVertices()) {

        this->base_location_list.push_back(vertex);
    }

    
    serial.startContinuousRead();
    ofAddListener(serial.NEW_MESSAGE,this,&ofApp::onNewMessage);
    
    message = "";
}

void ofApp::onNewMessage(string & message)
{
    cout << "onNewMessage, message: " << message << "\n";
    
    vector<string> input = ofSplitString(message, ",");
    
    
    if(input.size() >= 7)
    {
        aXS = input.at(0);
        aYS = input.at(1);
        aZS = input.at(2);
        gyroXS = input.at(3);
        gyroYS = input.at(4);
        gyroZS = input.at(5);
        flexS = input.at(6);
        
        xVal= ofToFloat(aXS)* 10;
        yVal= ofToFloat(aYS) * 10;
        zVal = ofToFloat(aZS) * 10;
        gyroX = ofToFloat(gyroXS);
        gyroY = ofToFloat(gyroYS);
        gyroZ = ofToFloat(gyroZS);
        
        gyroVec.set(gyroX,gyroY,-gyroZ);
        
        flex= ofToInt(flexS);


    }
}

//--------------------------------------------------------------
void ofApp::update(){
//    cout << xVS << endl; //test
//    cout << yVS << endl; //test
//    cout << aS << endl; //test
//    vDiff = vPoint-vUnit;
    
//    str0 = "d:" + ofToString(vDiff.x) +","+ ofToString(vDiff.y);
//    cout << str0 << endl; // output the sensorValue
    
    
    int radius = 5;
    while (this->log_list.size() < 8000) {

        int font_location_index = ofRandom(this->base_location_list.size());
        vector<glm::vec3> log;
        log.push_back(this->base_location_list[font_location_index]);
        this->log_list.push_back(log);
        this->color_list.push_back(this->base_color_list[(int)ofRandom(this->base_color_list.size())]);
        this->life_list.push_back(ofRandom(10, 60));
    }

    for (int i = this->log_list.size() - 1; i >= 0; i--) {

        this->life_list[i] -= 1;
        if (this->life_list[i] < 0) {

            this->log_list.erase(this->log_list.begin() + i);
            this->color_list.erase(this->color_list.begin() + i);
            this->life_list.erase(this->life_list.begin() + i);

            continue;
        }

        auto deg = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.004, ofGetFrameNum() * 0.00003)), 0, 1, -360, 360);
        auto theta = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.004, (ofGetFrameNum() + 10000) * 0.00003)), 0, 1, -360, 360);
        this->log_list[i].push_back(this->log_list[i].back() + glm::vec3(radius * cos(deg * DEG_TO_RAD) * sin(theta * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD) * sin(theta * DEG_TO_RAD), radius * cos(theta * DEG_TO_RAD)));
        while (this->log_list[i].size() > 100) {

            this->log_list[i].erase(this->log_list[i].begin());
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    this->cam.begin();
    
    
    
    if(flex>90){
        
        cam.move(gyroVec);
        
        ofRotateXDeg(-xVal);
        ofRotateYDeg(-yVal);
        ofRotateZDeg(-zVal);
        
    }
    
    for (int i = 0; i < this->log_list.size(); i++) {

        ofSetColor(this->color_list[i]);

        if (this->life_list[i] > 30) {

            ofSetLineWidth(1.5);
        }
        else {
            ofSetLineWidth(ofMap(this->life_list[i], 0, 30, 0, 1.5));
        }

        ofSetColor(ofColor(this->color_list[i], 200));

        ofBeginShape();
        ofVertices(this->log_list[i]);
        ofEndShape();
    }

    this->cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
