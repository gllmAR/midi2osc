#include "ofApp.h"

//--------------------------------------------------------------
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetVerticalSync(true);
    ofBackground(255, 255, 255);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // print input ports to console
    midiIn.listPorts(); // via instance
    //ofxMidiIn::listPorts(); // via static as well
    
    // open port by number (you may need to change this)
    midiIn.openPort("MIDI Mix");
    //midiIn.openPort("IAC Pure Data In");	// by name
    //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
    
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    midiIn.ignoreTypes(false, false, false);
    
    // add ofApp as a listener
    midiIn.addListener(this);
    
    // print received messages to the console
    midiIn.setVerbose(true);
    
    osc_sender.setup(HOST, PORT);
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(0);
    
    // draw the last recieved message contents to the screen
    text << "Received: " << ofxMidiMessage::getStatusString(midiMessage.status);
    ofDrawBitmapString(text.str(), 20, 20);
    text.str(""); // clear
    
    text << "channel: " << midiMessage.channel;
    ofDrawBitmapString(text.str(), 20, 34);
    text.str(""); // clear
    
    text << "pitch: " << midiMessage.pitch;
    ofDrawBitmapString(text.str(), 20, 48);
    text.str(""); // clear
    ofDrawRectangle(20, 58, ofMap(midiMessage.pitch, 0, 127, 0, ofGetWidth()-40), 20);
    
    text << "velocity: " << midiMessage.velocity;
    ofDrawBitmapString(text.str(), 20, 96);
    text.str(""); // clear
    ofDrawRectangle(20, 105, ofMap(midiMessage.velocity, 0, 127, 0, ofGetWidth()-40), 20);
    
    text << "control: " << midiMessage.control;
    ofDrawBitmapString(text.str(), 20, 144);
    text.str(""); // clear
    ofDrawRectangle(20, 154, ofMap(midiMessage.control, 0, 127, 0, ofGetWidth()-40), 20);
    
    text << "value: " << midiMessage.value;
    ofDrawBitmapString(text.str(), 20, 192);
    text.str(""); // clear
    if(midiMessage.status == MIDI_PITCH_BEND) {
        ofDrawRectangle(20, 202, ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, ofGetWidth()-40), 20);
    }
    else {
        ofDrawRectangle(20, 202, ofMap(midiMessage.value, 0, 127, 0, ofGetWidth()-40), 20);
    }
    
    text << "delta: " << midiMessage.deltatime;
    ofDrawBitmapString(text.str(), 20, 240);
    text.str(""); // clear
}

//--------------------------------------------------------------
void ofApp::exit() {
    
    // clean up
    midiIn.closePort();
    midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    ofxOscMessage m;
    // make a copy of the latest message
    midiMessage = msg;
    bool send_flag=1;
    //manage Ctl
    switch (msg.control)
    {
        case 16:
            m.setAddress("/oscillo/graphe/input/buffer_history");
            m.addIntArg(ofMap(msg.value,0,127,513,4096));
            break;
        case 17:
            m.setAddress("/oscillo/graphe/input/mesh_width_z");
            m.addFloatArg(ofMap(msg.value,0,127,-1,1));
            break;
        case 18:
            m.setAddress("/oscillo/audio_io/input/pan");
            m.addFloatArg(ofMap(msg.value,0,127,-1,1));
            break;
        case 19:
            m.setAddress("/oscillo/audio_io/input/volume");
            m.addFloatArg(ofMap(msg.value,0,127,0,1.2));
            break;
        case 20:
            m.setAddress("/oscillo/graphe/input/saturation");
            m.addFloatArg(ofMap(msg.value,0,127,0,255));
            break;
        case 21:
            m.setAddress("/oscillo/graphe/input/hue");
            m.addFloatArg(ofMap(msg.value,0,127,0,255));
            break;
        case 22:
            m.setAddress("/oscillo/graphe/input/brightness");
            m.addFloatArg(ofMap(msg.value,0,127,0,255));
            break;
        case 23:
            m.setAddress("/oscillo/graphe/input/shape_scale");
            m.addFloatArg(ofMap(msg.value,0,127,0,0.25));
            break;
        case 24:
            m.setAddress("/oscillo/graphe/player/buffer_history");
            m.addIntArg(ofMap(msg.value,0,127,513,4096));
            break;
        case 25:
            m.setAddress("/oscillo/graphe/player/mesh_width_z");
            m.addFloatArg(ofMap(msg.value,0,127,-1,1));
            break;
        case 26:
            m.setAddress("/oscillo/audio_io/player/pan");
            m.addFloatArg(ofMap(msg.value,0,127,-1,1));
            break;
        case 27:
            m.setAddress("/oscillo/audio_io/player/volume");
            m.addFloatArg(ofMap(msg.value,0,127,0,1.2));
            break;
        case 28:
            m.setAddress("/oscillo/graphe/player/saturation");
            m.addFloatArg(ofMap(msg.value,0,127,0,255));
            break;
        case 29:
            m.setAddress("/oscillo/graphe/player/hue");
            m.addFloatArg(ofMap(msg.value,0,127,0,255));
            break;
        case 30:
            m.setAddress("/oscillo/graphe/player/brightness");
            m.addFloatArg(ofMap(msg.value,0,127,0,255));
            break;
        case 31:
            m.setAddress("/oscillo/graphe/player/shape_scale");
            m.addFloatArg(ofMap(msg.value,0,127,0,0.25));
            break;
        case 54:
            m.setAddress("/oscillo/graphe/output/buffer_history");
            m.addIntArg(ofMap(msg.value,0,127,513,4096));
            break;
        case 55:
            m.setAddress("/oscillo/graphe/output/mesh_width_z");
            m.addFloatArg(ofMap(msg.value,0,127,-1,1));
            break;
        case 56:
            m.setAddress("/oscillo/audio_io/output/pan");
            m.addFloatArg(ofMap(msg.value,0,127,-1,1));
            break;
        case 57:
            m.setAddress("/oscillo/audio_io/output/volume");
            m.addFloatArg(ofMap(msg.value,0,127,0,1.2));
            break;
        case 58:
            m.setAddress("/oscillo/graphe/output/saturation");
            m.addFloatArg(ofMap(msg.value,0,127,0,255));
            break;
        case 59:
            m.setAddress("/oscillo/graphe/output/hue");
            m.addFloatArg(ofMap(msg.value,0,127,0,255));
            break;
        case 60:
            m.setAddress("/oscillo/graphe/output/brightness");
            m.addFloatArg(ofMap(msg.value,0,127,0,255));
            break;
        case 61:
            m.setAddress("/oscillo/graphe/output/shape_scale");
            m.addFloatArg(ofMap(msg.value,0,127,0,0.25));
            break;
        default:
            cout<<"not mapped"<<endl;
            send_flag=0;
            break;

    }
    // potentiellement buggy car double envoie
    if(send_flag){osc_sender.sendMessage(m);}

    cout<<"stuuuuu "<<msg.control<< " "<< msg.value<<endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    switch(key) {
        case 'l':
            midiIn.listPorts();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased() {
}
