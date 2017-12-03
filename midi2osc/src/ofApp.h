#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxOsc.h"


#define HOST "localhost"
#define PORT 9000

class ofApp : public ofBaseApp, public ofxMidiListener {
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased();
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    stringstream text;
    
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
    
    ofxOscSender osc_sender;

};
