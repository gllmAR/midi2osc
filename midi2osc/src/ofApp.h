#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxOsc.h"


#define HOST "localhost"
#define PORT 9000

class ofApp : public ofBaseApp, public ofxMidiListener {
    
public:
    
    void setup();

    void exit();
    
    bool debug = 0;
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
    
    ofxOscSender osc_sender;
    
    bool audio_io_input_mute = 0;
    bool graphe_input_active = 0;
    bool audio_io_player_enable=0;
    bool graphe_player_active=0;
    bool interact_interact_enable=0;
    bool feedback_enable=0;
};
