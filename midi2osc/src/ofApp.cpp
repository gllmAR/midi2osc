#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    if(debug){ofSetLogLevel(OF_LOG_VERBOSE);}
    
    midiIn.listPorts();
#ifdef TARGET_LINUX_ARM
    midiIn.openPort("MIDI Mix 20:0");
#else
    midiIn.openPort("MIDI Mix");
#endif
    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
    if(debug){ midiIn.setVerbose(true);}
    ofSetFrameRate(1);
    osc_sender.setup(HOST, PORT);
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
            
        case 46:
            m.setAddress("/oscillo/audio_io/player/file_index");
            m.addIntArg(ofMap(msg.value,0,127,0,9));
            break;
        case 47:
            m.setAddress("/oscillo/audio_io/player/position");
            m.addFloatArg(ofMap(msg.value,0,127,0,1));
            break;
        case 48:
            m.setAddress("/oscillo/interact/speed_trim");
            m.addFloatArg(ofMap(msg.value,0,127,0,2));
            break;
        case 49:
            m.setAddress("/oscillo/audio_io/player/speed");
            m.addFloatArg(ofMap(msg.value,0,127,-2,2));
            break;
            
        case 50:
            m.setAddress("/oscillo/feedback/x");
            m.addFloatArg(ofMap(msg.value,0,127,0.96,1.04));
            break;
        case 51:
            m.setAddress("/oscillo/feedback/y");
            m.addFloatArg(ofMap(msg.value,0,127,0.96,1.04));
            break;
        case 52:
            m.setAddress("/oscillo/feedback/scale");
            m.addFloatArg(ofMap(msg.value,0,127,0.5,1.5));
            break;
        case 53:
            m.setAddress("/oscillo/feedback/ammount");
            m.addFloatArg(ofMap(msg.value,0,127,0.80,1));
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
        case 62:
            m.setAddress("/oscillo/audio_io/device/master_vol");
            m.addFloatArg(ofMap(msg.value,0,127,0,1.2));
            break;
            
        default:
            if(debug){cout<<"cc not mapped"<<endl;}
            break;
    }
    
    //manage note in
    
    if (int(msg.bytes[0])==144) //parse note on (144)
    {
        switch (msg.pitch)
        {
            case 1:
                m.setAddress("/oscillo/audio_io/input/mute");
                audio_io_input_mute=!audio_io_input_mute;
                m.addBoolArg(audio_io_input_mute);
                break;
            case 4:
                m.setAddress("/oscillo/graphe/input/active");
                graphe_input_active=!graphe_input_active;
                m.addBoolArg(graphe_input_active);
                break;
            case 7:
                m.setAddress("/oscillo/audio_io/player/enable");
                audio_io_player_enable=!audio_io_player_enable;
                m.addBoolArg(audio_io_player_enable);
                break;
            case 10:
                m.setAddress("/oscillo/graphe/player/active");
                graphe_player_active=!graphe_player_active;
                m.addBoolArg(graphe_player_active);
                break;
            case 13:
                m.setAddress("/oscillo/interact/speed/interact_enable");
                interact_speed_enable=!interact_speed_enable;
                m.addBoolArg(interact_speed_enable);
                break;
            case 16:
                m.setAddress("/oscillo/feedback/enable");
                feedback_enable=!feedback_enable;
                m.addBoolArg(feedback_enable);
                break;
            case 27:
                m.setAddress("/oscillo/audio_io/device/reset_audio");
                m.addBoolArg(1);
                break;
                
            default:
                if(debug){cout<<"pitch not mapped"<<endl;}
                break;
                
        }
    }
    osc_sender.sendMessage(m);
}

