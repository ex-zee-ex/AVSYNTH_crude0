
#include "ofApp.h"


#include <iostream>

float ff=1.01;
float xw=1.01;
float yw=1.01;
float jj=1.01;
float kk=1.01;
float ll=.05;




//midicontrols
//maybe make these chars instead?  check the bit depth to see if there will be a lot of
//data loss
float c1=1;
float c2=1;
float c3=1;
float c4=1;
float c5=1;
float c6=1;
float c7=1;
float c8=1;
float c9=1;
float c10=1;
float c11=1;



//keyboard controls
//probbly shift all of these to a gui
float ss=1;
float dd=1;

float gg=1;
float hh=0;

float pp=1;
float ii=.01;


Boolean env_switch=0;
Boolean sw1=0;
Boolean sw2=0;
Boolean lineswitch=0;

float out_env=0;




float theta=0;



//cellular automata feedback arrays
//float pix0[256][256];
//float pix1[256][256];

//array to keep track of vectorscope visualization
//float pixxx[256][256];


//data for pitches
float frequency=0;
int N=0;
int FN=0;
float velocity=0;


float delay[44100];



//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofBackground(0);
	//ofSetLogLevel(OF_LOG_VERBOSE);
	
    
    /**MIDIBIX***/
    
	// print input ports to console
	midiIn.listInPorts();
	
	// open port by number (you may need to change this)
	midiIn.openPort(0);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add ofApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(true);
    
    /*******/
    
    
    /**audiobiz***/
    
    
    
    
    int bufferSize		= 512;
    sampleRate 			= 44100;
    phase 				= 0;
    phaseAdder 			= 0.0f;
    phaseAdderTarget 	= 0.0f;
    volume				= 0.1f;
    bNoise 				= false;
    
    lAudio.assign(bufferSize, 0.0);
    rAudio.assign(bufferSize, 0.0);
    
    soundStream.printDeviceList();
    
    ofSoundStreamSettings settings;
    
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    
    
    
    /**shaderobiz***/
    
#ifdef TARGET_OPENGLES
    shaderBlurX.load("shadersES2/shaderBlurX");
    shaderBlurY.load("shadersES2/shaderBlurY");
#else
    if(ofIsGLProgrammableRenderer()){
        shaderBlurX.load("shadersGL3/shaderBlurX");
        shaderBlurY.load("shadersGL3/shaderBlurY");
    }else{
        shaderBlurX.load("shadersGL2/shaderBlurX");
        shaderBlurY.load("shadersGL2/shaderBlurY");
    }
#endif
    
  //  image.load("img.png");
    
    fboBlurOnePass.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    fboBlurTwoPass.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    fbo_feedback.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    
    
    // fbo_feedback.begin();
    // image.draw(0, 0);
    // fbo_feedback.end();
    
    fbo_feedback.begin();
    
    ofClear(0,0,0,255);
    
    fbo_feedback.end();
    
    fboBlurTwoPass.begin();
    ofClear(0,0,0,255);
    fboBlurTwoPass.end();
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
    
  
    
    
    
    
/*midimessagesbiz**/
    
    
    
    
 
	for(unsigned int i = 0; i < midiMessages.size(); ++i) {

		ofxMidiMessage &message = midiMessages[i];
        
   
        
        
      

        if(message.status==MIDI_NOTE_ON){env_switch=1;}
        if(message.status==MIDI_NOTE_OFF){env_switch=0;}
        
      
     	//cout << "envcount="<< envcount<< endl;

		if(message.status < MIDI_SYSEX) {
			//text << "chan: " << message.channel;
			if(message.status == MIDI_CONTROL_CHANGE) {
              //  cout << "message.control"<< message.control<< endl;
               //  cout << "message.value"<< message.value<< endl;
                
                //is like maudio oxygen one
                /*
                if(message.control==7){
                    c1=(message.value-63)/63.0;
                
                }
                
                if(message.control==94){
                    c2=(message.value-63)/63.00000;
                    
                }
                
                if(message.control==95){
                    c3=(message.value-63)/63.00000;
                    
                }
                
                if(message.control==96){
                    c4=(message.value-63)/63.00000;
                    
                }
                
                if(message.control==97){
                    c5=(message.value-63)/63.00000;
                    
                }
                if(message.control==20){
                    c6=(message.value-63)/63.00000;
                    
                }
                
                if(message.control==73){
                    c10=(message.value-63)/63.00000;
                    
                }
                if(message.control==21){
                    c7=(message.value-63)/63.00000;
                    
                }
                if(message.control==22){
                    c8=(message.value)/127.00000;
                    
                }
                if(message.control==23){
                    c8=(message.value)/127.00000;
                    
                }
                */
                
                
                if(message.control==20){
                    c1=(message.value-63.0)/63.0;
                    
                }
                
                if(message.control==21){
                    c2=(message.value-63.0)/63.0;
                    
                }
                
                if(message.control==22){
                    c3=(message.value-63.0)/63.00;
                    
                }
                
                if(message.control==23){
                    c4=(message.value-63)/63.00;
                    
                }
                
                if(message.control==24){
                    c5=(message.value-63)/63.00;
                    
                }
                if(message.control==25){
                    c6=(message.value-63.0)/63.0;
                    
                }
                
                
                if(message.control==26){
                    c7=(message.value-63.0)/63.0;
                    
                }
                if(message.control==27){
                    c8=(message.value-63.0)/63.0;
                    
                }
                
                //text << "\tctl: " << message.control;
				//ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
				//	ofMap(message.control, 0, 127, 0, ofGetWidth()*0.2), 10);
			}
			else if(message.status == MIDI_PITCH_BEND) {
				//text << "\tval: " << message.value;
				//ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
					//ofMap(message.value, 0, MIDI_MAX_BEND, 0, ofGetWidth()*0.2), 10);
			}
			else {
				//text << "\tpitch: " << message.pitch;
				//ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
					//ofMap(message.pitch, 0, 127, 0, ofGetWidth()*0.2), 10);
              
                
                N= message.pitch;
                FN=N-69;
                frequency=pow(2.0,FN/12.0)*440;
                velocity =message.velocity/127.0;//normalized
                
         
             				////text << "\tvel: " << message.velocity;
				//ofDrawRectangle(x + (ofGetWidth()*0.2 * 2), y + 12,
					//ofMap(message.velocity, 0, 127, 0, ofGetWidth()*0.2), 10);
			}
			//text << " "; // pad for delta print
		}//

		
	}
   /******* endmidimessagesbiz*********/
   
    
    
   
    /***AUDIODRAWBIXZ******/
    
    theta+=.005;
    
   
    
    
    /*
    
    // draw the left channel:
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(32, 10, 0);
    
    ofSetColor(0);
    //ofDrawBitmapString("Left Channel", 4, 18);
    ofNoFill();
    ofSetLineWidth(5);
    //	ofDrawRectangle(0, 0, 900, 200);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);
    
    ofBeginShape();
    for (unsigned int i = 0; i < lAudio.size(); i++){
        float x =  ofMap(i, 0, lAudio.size(), 0, 900, true);
        ofVertex(x, 100 -lAudio[i]*180.0f);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
    
    
    
    //draw lissajou	ofPushStyle();
    ofPushMatrix();
   // ofTranslate(512, 512, 0);
    
    //ofSetColor(225);
    //ofDrawBitmapString("lissajou", 4, 18);
    
    ofSetLineWidth(3);
    //ofDrawRectangle(0, 0, 900, 200);
    
   
    
    
    
    
        int cs=5;

    
    for (unsigned int i = 0; i < rAudio.size()*2/cs; i++){
         //cout << "rAudio.size()="<< rAudio.size()<< endl;
        
        
        
        //transcode step 1
          //thi bit is calculating the vectorscope positions based on the audiobuffer data
        //left channel mapped to x, right cahnnel mapped to y
        float x =  4*(lAudio[i*cs/2]*180.0f);
        float y = 4*(rAudio[i*cs/2]*180.0f);
        
        
        //rotate the points at a speed reative to frequency)
        x=x*(cos(frequency*theta/100)-sin(frequency*theta/100));
        y=y*(sin(frequency*theta/100)+cos(frequency*theta/100));
        
        //shift the points to visual center of screen
        x=x+512;
        y=y+512;
        
        
        
  
        int pix_x=ofMap(x,0,1024,0,253)-24;
        int pix_y=ofMap(y,0,1024,0,253)-24;
        
        
   
        
        
        pixxx[pix_x][pix_y]=255;
        
        for(int j=0;j<rAudio.size()*2/cs;j++){
            int xx=i*cs;
            int yy=j*cs;
            float b=pix0[i][j];
            
          
            
            //this version is toroidal universe
            //int up=(j-1)%(rAudio.size()*2/cs);
            //int down=(j+1)%(rAudio.size()*2/cs);
            //int left=(i-1)%(rAudio.size()*2/cs);
           // int right=(i+1)%(rAudio.size()*2/cs);
            
            //thisversion is not wrapping around
            int up=ofClamp(j-1,0,rAudio.size()*2/cs);
            int down=ofClamp(j+1,0,rAudio.size()*2/cs);
            int left=ofClamp(i-1,0,rAudio.size()*2/cs);
            int right=ofClamp(i+1,0,rAudio.size()*2/cs);

            
            
            float b_u=pix0[i][up];
            float b_ul=pix0[left][up];
            float b_ur=pix0[right][up];
            float b_d=pix0[i][down];
            float b_dl=pix0[left][down];
            float b_dr=pix0[right][down];
            float b_r=pix0[right][j];
            float b_l=pix0[left][j];

            
            //RULLEES
            
            //rugruless!!
            
            
            //float rug=(b_u+b_d+b_ul+b_ur+b_r+b_l+b_dr+b_dl)/8.0;
            //rug=rug+c1;
            //b=((1-c2)*b+(2*c2)*rug);
            
            
            //discrete reaction diffusion experients
            
            float r_d=(1-4*c1-4*c4)*(b)+c1*(b_u+b_d+b_l+b_dr)+c4*(b_ul+b_ur+b_dr+b_dl)+c2*b*sin(theta/1.0*b/255)+.01*c7*(b*b*b);
            
            b=(1-2*c5-2*c6)*r_d+8*b*c5*((xx-512)/512)+8*b*c6*((yy-512)/512);
            //b=r_d;
            
            if(b<pixxx[i][j]){
                b=pixxx[i][j];
                
            }
            if(b>=pix0[i][j]){b=b*(1-c3/4.0);}
            
            
            //heres where we do some stuffs to overflow
          
            
            
            if(sw2==0) {
            if(b<-100*c9){
             b=0;
            }
            }//endifsw2
            
            if(sw2==1){
            
                b=abs(b);
            }
            
            
            
           // if(b>1000){
             //   b=255;}
            
            
          //  b=abs(b);
            
            //if(b<0){
              //  b=255-abs(b);
               //b=abs(b);
           // }
            
            if(sw1==1){
                b=fmod(b,255);
            }//ifsw1
            
            if(sw1==0){
            
            if(b>255*(1+10*c8)){
                b=255;
                
            }
            }//ifsw1
            
            
            
            ofColor c;
            float hue=0;
            float sat=255;
            float alph=0;
            
            hue=fmod(abs(c10*b),255);
            alph=b*.8;
            
            
            
            c.setHsb(hue,sat,b,alph);
            
            ofSetColor(c);
            ofFill();
      
            ofDrawRectangle(xx,yy,cs,cs);
            
            
            //fill up the other array with the feedback value
            pix1[i][j]=b;
            
        
        }//endjfor
    }//endifor

    
    //tbhis is where we swap arrays so that feedbac happens
    
    for(int i=0;i<256;i++){
        for(int j=0;j<256;j++){
            // pixxx[i][j]=0;
            pix0[i][j]=pix1[i][j];
        }//endjfor
    }//endifor
    
    
    
    //pixxx is the array that stores the values of vectorscope this clears them every so often
    
    
    for(int i=0;i<256;i++){
        for(int j=0;j<256;j++){
            pixxx[i][j]*=.99;
            
        }//endjfor
    }//endifor
    
    
    
    */
    
    
    
    
    
    //shader biz
    
    float blurx =c7;
    float blury = c6;
    
    
    fboBlurTwoPass.begin();
    
    shaderBlurY.begin();
    shaderBlurY.setUniform1f("blurAmnty", blury*jj);
    shaderBlurY.setUniform1f("ff", ff*c1);
    shaderBlurY.setUniform1f("yw", yw*c2);
    shaderBlurY.setUniform1f("blurAmntx", blurx*kk);
    shaderBlurY.setUniform1f("xw", xw*c3);
    
    shaderBlurY.setUniform1f("rw", 2*c4);
    shaderBlurY.setUniform1f("gw", 2*c5);
    shaderBlurY.setUniform1f("bw", 2*c8);
    
    shaderBlurY.setUniform1f("ll", ll);
    
    shaderBlurY.setUniform1f("time", ofGetElapsedTimef());
    
    
    fbo_feedback.draw(0,0);
    
    shaderBlurY.end();
    
    fboBlurTwoPass.end();
    
    //----------------------------------------------------------
    
    
    /*this part gets drawn to screen*/
    ofSetColor(ofColor::white);
    fboBlurTwoPass.draw(0, 0);
    
    
    //this part draws the lines that connect the dots
    
    
    
    ofBeginShape();
    
    for (unsigned int i = 0; i < rAudio.size(); i++){
        //cout << "rAudio.size()="<< rAudio.size()<< endl;
        float x =  5*(lAudio[i]*180.0f)+ofGetWidth()/2.0;
        float y = 5*(rAudio[i]*180.0f)+ofGetHeight()/2.0;
        //  float z=10;
        //ofVertex(x, 100 -rAudio[i]*180.0f);
        
        
        
        ofColor c;
        float hue=127;//*(1-.25*(lAudio[i])),255);
        float sat=127;
        float bright=127;//*(1-(lAudio[i]+rAudio[i]));
        c.setHsb(hue,sat, bright);
        
        ofSetLineWidth(5);
        ofNoFill();
        ofSetColor(c);
        ofVertex(x,y);
        
    }//endifor
    ofEndShape(false);
    
    
    
    
    
    
    /*this part getsdrawn to the feedback buffer*/
    
    fbo_feedback.begin();
    fboBlurTwoPass.draw(0, 0);
   
    
    
    //this part draws the lines that connect the dots
    
    
    
    ofBeginShape();
    
    for (unsigned int i = 0; i < rAudio.size(); i++){
        //cout << "rAudio.size()="<< rAudio.size()<< endl;
        float x =  5*(lAudio[i]*180.0f)+ofGetWidth()/2.0;
        float y = 5*(rAudio[i]*180.0f)+ofGetHeight()/2.0;
        //  float z=10;
        //ofVertex(x, 100 -rAudio[i]*180.0f);
        
        
        
        ofColor c;
        float hue=127;//fmod(240*(1-.25*(lAudio[i])),255);
        float sat=127;
        float bright=127;//*(1-(lAudio[i]+rAudio[i]));
        c.setHsb(hue,sat, bright);
        
        ofSetLineWidth(5);
        ofNoFill();
        ofSetColor(c);
        ofVertex(x,y);
        
    }//endifor
    ofEndShape(false);
    
    
    
    fbo_feedback.end();
    
    
    
    ofSetHexColor(0xFFFFFF);
    ofDrawBitmapString("ff: "+ofToString(ff*c1)
                       +" yw: "+ofToString(yw*c2) +" xw: "+ofToString(xw*c3) +" ll: "+ofToString(ll),
                       10, ofGetHeight()-5 );
    
    


























    
  
   // ofPopMatrix();
   // ofPopStyle();
    
    
    
    
    
    
   
    /*
    
    //rightchanel
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(32, 748, 0);
    
    ofSetColor(225);
    // ofDrawBitmapString("Right Channel", 4, 18);
    
    ofSetLineWidth(1);
    //ofDrawRectangle(0, 0, 900, 200);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);
    
    ofBeginShape();
    for (unsigned int i = 0; i < rAudio.size(); i++){
        float x =  ofMap(i, 0, rAudio.size(), 0, 900, true);
        ofVertex(x, 100 -rAudio[i]*180.0f);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
    */
    
    
    
    
    /*
    ofSetColor(225);
    string reportString = "volume: ("+ofToString(volume, 2)+") modify with -/+ keys\npan: ("+ofToString(pan, 2)+") modify with mouse x\nsynthesis: ";
    if( !bNoise ){
        reportString += "sine wave (" + ofToString(targetFrequency, 2) + "hz) modify with mouse y";
    }else{
        reportString += "noise";
    }
    ofDrawBitmapString(reportString, 32, 579);
     
     
     */
/********endaudiodrawbiz****/
   
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer & buffer){
    

    // cout <<" c1="<<c1<< endl;
    
    pan = 0.5f;
    float leftScale = 1 - pan;
    float rightScale = pan;
    
   
    
    if ( bNoise == true){
        // ---------------------- noise --------------
        for (size_t i = 0; i < buffer.getNumFrames(); i++){
            lAudio[i] = buffer[i*buffer.getNumChannels()    ] = ofRandom(0, 1) * volume * leftScale;
            rAudio[i] = buffer[i*buffer.getNumChannels() + 1] = ofRandom(0, 1) * volume * rightScale;
        }
    } else {
        
        
        //this is to keep phase from just incrementing absurdly
        //for some reaason if the mod is just twopi then it restarts phase in rythmic glitchy bits
        //maybe i can turn this on and off or swtich values?
        phase=fmod(phase,4*TWO_PI);
        phaseAdderTarget=(frequency/10000.0 ) * TWO_PI;
        
        
        phaseAdder = 0.5f * phaseAdder + 0.5f *phaseAdderTarget;
        for (size_t i = 0; i < buffer.getNumFrames(); i++){
            phase += phaseAdder;
           float  phase_r=phase+TWO_PI*(sin(theta));
            
            /*basic waveforms*/
            
            /*samplel and sampler are what get fed into the buffer at the end*/
            float samplel=0;
            float sampler=0;
            
            
         
            
            //experimentalwaves
            
            
            //logwave!
           // samplel=log(abs(sine_l*(1+ff)+1))-1;
           // sampler=log(abs(sine_r*(1+ff)+1))-1;
            
            
            //squrtsine
           // samplel=sqrt(abs(sine_l*(1+ff)+1))-1;
           // sampler=sqrt(abs(sine_r*(1+ff)+1))-1;

            
            
            //i want like a wavier square
            
            //float ee=.72*sin(theta/3.0);
            // float ee=0;
            //float  pulsew_l=ofSign(sine_l+ee)*.75+.25*sine_l;
          //  float pulsew_r=ofSign(sine_r+ee)*.75+.25*sine_r;
            
           // samplel=pow(pulsew_l,3);
           // sampler=pow(pulsew_r,3);
            
            
            
            
            
            /***interpolate between waves**/
          
            
           // float ww=sin(theta/2.0);
          //  float interp_l=(ww*sine_l+(1-ww)*pulse_l)/2.0;
          //  float interp_r=(ww*sine_r+(1-ww)*pulse_r)/2.0;
            
          //  samplel=interp_l;
           // sampler=interp_r;
            
            
          
            
            
           //samplel=tan_l*tan_l*tan_l;
           //sampler=tan_r*tan_r*tan_r;
            
            
            
            
     
            
            
            
            
            
            /*frequencymod*/
          //  float fm_l=sin(phase*sin(ff*phase));
           // float fm_r=sin(phase_r*sin(ff*phase_r));
            
            
            
            /*fphasemod*/
            //float phm_l=sin(phase+sin(int(kk)*ff*phase));
           // float phm_r=sin(phase_r+sin(int(kk)*ff*phase_r));
            
            // samplel=fm_l;
           // sampler=fm_r;
            
            
            /**ringmod**/
            
            //samplel=interp_l*phm_l;
          // sampler=interp_r*phm_r;
            
            
            /**ampmod**/
            
            
            //the divide by 2 and plus .5 is transforming the bipolar modulator into a unipolar modulator
            
            // samplel=pulse_l*(tri_l/2+.5);
            // sampler=pulse_r*(tri_r/2+.5);
            
            
            
            
            
            /**wavesubtract**/
            
           // float subtract_l=(sine_l-saw_l)/2.0+1/2;
           //  float subtract_r=(sine_r-saw_r)/2.0+1/2;
            
          //  samplel=subtract_l;
           // sampler=subtract_r;
            
            /**addwaves**/
            
          //  float add_l=(saw_l+pulse_l)/2.0;
          //  float add_r=(saw_r+pulse_r)/2.0;
            
           // samplel=add_l;
           //  sampler=add_r;

            
            /**foldover**/
            
            
           // samplel=sine_l;
           // sampler=sine_r;
            
            /*
            
            if(samplel>1){
                samplel=1-fmod(samplel,1);
            
            }
            if(samplel<-1){
                samplel=fmod(abs(samplel),1)-1;
                
            }
            
            if(sampler>1){
                sampler=1-fmod(sampler,1);
                
            }
            if(sampler<-1){
                sampler=fmod(abs(sampler),1)-1;
                
            }
            */
            
            
            
         /**clammpp_clipp**/
           
     
            
            //smoothe the ringmodding maybe?
            
           // samplel=samplel*samplel*samplel;
            //sampler=sampler*sampler*sampler;
            
            
            
            /**phasemodulation**/
           // samplel=sin(ss*phase+sampler);
           // sampler=sin(dd*phase+samplel);
            
            /*quantise*/
            //samplel=int(samplel*ff);
            //sampler=int(sampler*gg);
            
            
            
            
           // int x1=int(gg*samplel);
           // int x2=int(gg*sampler);
            
           // samplel=x1/gg;
           // sampler=x2/gg;
            
            
            /**chebeyshev_polynomials**/
            /* T_k+1(x)=2*x*T_k(x)-T_k-1(x)*/
            
           // float xl=samplel;
          //  float xr=sampler;
            
            /*
            
            //T_2//
            float T_2l=2*xl*xl-1;
            float T_2r=2*xr*xr-1;
            
            //T_3//
            float T_3l=4*pow(xl,3)-3*xl;
            float T_3r=4*pow(xr,3)-3*xr;
            
            //T_4//
            float T_4l=8*pow(xl,4)-8*pow(xl,2)+1;
            float T_4r=8*pow(xr,4)-8*pow(xl,2)+1;

            
            samplel=(T_4l+T_3l+T_2l+xl)/4.0;
            sampler=(T_4r+T_3r+T_2r+xr)/4.0;
            */
            
            
            
            /**feedingchebyshevstochebyshevs**/
            //T_2//
           // float T_2l=2*xl*xl-1;
           // float T_2r=2*xr*xr-1;
            
            //T_3//
          //  float T_3l=4*pow(T_2l,3)-3*T_2l;
          //  float T_3r=4*pow(T_2r,3)-3*T_2r;
            
            //T_4//
          ////  float T_4l=8*pow(T_3l,4)-8*pow(T_3l,2)+1;
          //  float T_4r=8*pow(T_3r,4)-8*pow(T_3r,2)+1;
            
            
            //samplel=(T_4l);
           // sampler=(T_4r);
            
            
            
       
            
            
            
            volume=out_env;
            
            // volume = MAX(volume, 0);
            //volume = MIN(volume, 1);
            
            int d=(i-int(ss))%buffer.size()/2;
            
            samplel=(lAudio[d]*dd+samplel)/2;
            sampler=(rAudio[d]*dd+sampler)/2;
            
            
            
            
            

           

            
            
            
            //osc(float arg,int oct,int coarse, int shape,float amp)
            
            
            float pm_l=0.0;
            float pm_r=0.0;
            float lfo=abs(osc(theta,1,1,0,1));
            float lfo2=abs(osc(theta*4.0,1,1,0,1));
            pm_l=osc(phase,5*lfo2,1,0,lfo);
            pm_r=osc(phase_r,5*lfo2,1,0,lfo);
            samplel=osc(phase+pm_l,1,1,0,1);
           sampler=osc(phase_r+pm_r,1,1,0,1);
            
            
           
            //internal phase modulation feedback loop
            
            /*
            int total=abs(ll);
            
            //if total goes above 400 theres some sort of stream over/underflow detection glitch
            for(unsigned int e=0;e<total;e++){
                samplel=osc(phase+samplel,1,1,0);
                sampler=osc(phase+sampler,1,1,0);
            
            }//endefor
            */
            
            
                      
            samplel=ofClamp(samplel,-1,1);
            sampler=ofClamp(sampler,-1,1);
            
          
            
            
            
            
            
            
            if(env_switch==1){
                if(out_env<1){
                   // out_env=ofLerp(out_env,1,0.001);
                    
                    /**this is a nice slow envelop i should probably re wrrite it in like logarithmic tho
                     out_env+=.00001; **/
                    
                    
                    out_env+=.00005;
                }
            }
            
            
             if(env_switch==0){
              
                     if(out_env>0){
                         // out_env=ofLerp(out_env,0,.05);
                
                         out_env-=.00001;
                     }
                 
             }
            
            
            out_env=ofClamp(out_env,0,1);
            
            samplel=out_env*samplel;
            sampler=out_env*sampler;
            
            
            
            
            
            
            lAudio[i] = buffer[i*buffer.getNumChannels()    ] = samplel * velocity * leftScale;
            rAudio[i] = buffer[i*buffer.getNumChannels() + 1] = sampler * velocity * rightScale;
            
            
            
            
            /**delay experiment**/
            
           // int d=(i-int(ss))%buffer.size();
          //  lAudio[i]=(lAudio[i]+lAudio[d])/2.0;
          //  rAudio[i]=(rAudio[i]+rAudio[d])/2.0;
            
            
         
            
            /**lerpingexperiment**/

            /*
            if(i>0){
            if(abs(lAudio[i]-lAudio[i-1])>.05){
                lAudio[i]=ofLerp(lAudio[i-1],lAudio[i],.5);
            }//endifabsl
                
                if(abs(rAudio[i]-rAudio[i-1])>.25){
                    rAudio[i]=ofLerp(rAudio[i-1],rAudio[i],.5);
                }//endifabs

            }//endifi
            */
           
        }
    }
    
}

//--------------------------------------------------------------
//--------------------------------------------------------------
float ofApp::osc(float arg,int oct,int coarse, int shape,float amp) {
    
    float sine=sin(oct*arg*(13-coarse)/12.0);
    
    switch(shape){
        case 0:{//sine wave
            return amp*sine;
        }//endcase0
            
        case 1:{//square wave
            return amp*ofSign(sine);
            // pulse_r=ofSign(sine_r+ee);
            break;
        }//endcase1
        case 2:{//tanwave
            return amp*ofClamp(ss*tan(arg/2.0),-1,1);
            break;
        }//endcase2
            
        case 3:{//parabola
            return amp*(sin(oct*arg/2.0*(13-coarse)/12.0)*sin(oct*arg/2.0*(13-coarse)/12.0)*2-1);
            break;
        }//endcase3
            
        case 4:{//sqrtwave
            return amp*sqrt(abs(sine*(1+ff)+1))-1;;
            break;
        }//endcase3
            
            
            
            
    }//endswitch
    
    
    
    
}//endosc

float ofApp:: quantize(float signal, int amount){
    
    
    //float q=16*sin(theta);
    
    float q=amount;
    
    if(q<2&&q>=0){q=2;}
    if(q>-2&&q<0){q=-2;}
    
    
    
    int quant=int(pow(signal*ff,3)*q);
    
    return quant/q;
}//endquant

//--------------------------------------------------------------
void ofApp::exit() {
	
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

	// add the latest message to the message queue
	midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while(midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

    
    
    if(key=='1'){
        
        fbo_feedback.begin();
        
        ofClear(0,0,0,255);
        
        fbo_feedback.end();
        
        fboBlurTwoPass.begin();
        ofClear(0,0,0,255);
        fboBlurTwoPass.end();
    }
    //if(key=='q'){sw1==0;}
    
    if(key=='s'){ss+=0.001;}
    if(key=='x'){ss-=0.001;}
    
    if(key=='d'){dd+=0.01;}
    if(key=='c'){dd-=0.01;}
    
    if(key=='f'){ff+=0.1;}
    if(key=='v'){ff-=0.1;}
    
    if(key=='g'){xw+=0.01;}
    if(key=='b'){xw-=0.01;}
    if(key=='h'){yw+=0.01;}
    if(key=='n'){yw-=0.01;}
    
    
    if(key=='j'){jj+=0.1;}
    if(key=='m'){jj-=0.1;}
    if(key=='k'){kk+=0.1;}
    if(key==','){kk-=0.1;}
    
    if(key=='l'){ll+=0.01;}
    if(key=='.'){ll-=0.01;}
    
    
    
    
    
    
    
    /*
    if(key=='s'){ss+=.1;cout << "ss="<< ss<< endl;}
    if(key=='x'){ss-=.1;cout << "ss="<< ss<< endl;}
    
    if(key=='d'){dd+=.1;}
    if(key=='c'){dd-=.1;}
    
    if(key=='f'){ff+=.01;cout << "ff="<< ff<< endl;}
    if(key=='v'){ff-=.01;cout << "ff="<< ff<< endl;}
    
    
    if(key=='g'){gg+=.1;}
    if(key=='b'){gg-=.1;}
    if(key=='h'){hh+=.1;}
    if(key=='n'){hh-=.1;}
    
    if(key=='k'){kk+=.1;}
    if(key==','){kk-=.1;}
    
    if(key=='p'){pp+=.01;}
    if(key=='['){pp-=.01;}
    if(key=='i'){ii+=.1;}
    if(key=='o'){ii-=.1;}
    
    
    if(key=='1'){sw1=1;}
    if(key=='q'){sw1=0;}
    if(key=='2'){sw2=1;}
    if(key=='w'){sw2=0;}
    
    if(key=='l'){ll+=1; cout << "ll="<< ll<< endl;}
    if(key=='.'){ll-=1; cout << "ll="<< ll<< endl;}
     
     */
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
   
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    int width = ofGetWidth();
    pan = (float)x / (float)width;
    float height = (float)ofGetHeight();
    float heightPct = ((height-y) / height);
    targetFrequency = 2000.0f * heightPct;
    phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;
}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    int width = ofGetWidth();
    pan = (float)x / (float)width;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased() {
}



//--------------------------------------------------------------




//--------------------------------------------------------------


