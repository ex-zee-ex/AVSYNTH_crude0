/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxMidi for documentation
 *
 */
#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

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
	
	ofxMidiIn midiIn;
	std::vector<ofxMidiMessage> midiMessages;
	std::size_t maxMessages = 10; //< max number of messages to keep track of
    
    
    void audioOut(ofSoundBuffer & buffer);
    
    
    ofSoundStream soundStream;
    
    float 	pan;
    int		sampleRate;
    bool 	bNoise;
    float 	volume;
    
    vector <float> lAudio;
    vector <float> rAudio;
    
    //------------------- for the simple sine wave synthesis
    float 	targetFrequency;
    float 	phase;
    float 	phaseAdder;
    float 	phaseAdderTarget;
    
    
    float osc(float arg,int oct,int coarse,int shape,float amp);
    float quantize(float signal, int amount);
    float env(float attack,float decay);
    
    
    //shaderstuffss
    ofShader shaderBlurY;
    ofShader shaderBlurX;
    
    ofFbo fboBlurOnePass;
    ofFbo fboBlurTwoPass;
    ofFbo fbo_feedback;
    
    ofImage image;
    ofVec2f sineWave(int i,float rate,float amp);
    
};