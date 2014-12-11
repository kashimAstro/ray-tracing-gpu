#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "ofxGui.h"

class xApp : public ofBaseApp {
	public:
		ofxPanel gui;
		ofParameter<ofVec3f> color1;
		ofParameter<ofVec3f> color2;
		ofParameter<float>     radius1;
		ofParameter<float>     radius2;
		ofParameter<float>     intLight;
		ofParameter<ofVec2f>   speLight;
		ofParameter<ofVec3f>   colLight;
		ofParameter<float>     ambient;
		ofParameter<ofVec3f>   posSphere1;
		ofParameter<ofVec3f>   posSphere2;

		ofFbo fbo;
		int w,h;
		ofShader trace;

		void setup(){
			ofSetFrameRate(150);
			trace.load("ray");
			w=ofGetScreenWidth();
			h=ofGetScreenHeight();
			fbo.allocate(w,h);
			fbo.begin();
			ofClear(0,0,0,0);
			fbo.end();
			gui.setup();
			gui.add(color1.set("color sphere 1", ofVec3f(0.),ofVec3f(0.),ofVec3f(1.) ));
			gui.add(color2.set("color sphere 2", ofVec3f(0.),ofVec3f(0.),ofVec3f(1.) ));
			gui.add(radius1.set("radius sphere 1", .6,.0,10. ));
			gui.add(radius2.set("radius sphere 2", .6,.0,10. ));
			gui.add(intLight.set("intensity light",.4,.0,5.  ));
			gui.add(speLight.set("specular light", ofVec2f(1.,50.), ofVec2f(0.,0.), ofVec2f(100.,100.) ));
			gui.add(colLight.set("color light", ofVec3f(0.),ofVec3f(0.),ofVec3f(1.) ));
			gui.add(ambient.set("ambient light", .2,.0,1. ));

			gui.add(posSphere1.set("position sphere 1", ofVec3f(.75,.1,1.),ofVec3f(-5.,-5.,-5.),ofVec3f(5.,5.,5.) ));
			gui.add(posSphere2.set("position sphere 2", ofVec3f(-.75,.1,2.25),ofVec3f(-5.,-5.,-5.),ofVec3f(5.,5.,5.) ));
		}

		void update(){
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
		}

		void draw(){
			ofBackgroundGradient(255,0);

			trace.begin();

			trace.setUniform1f("u_aspect_ratio",w/h);

			trace.setUniform3f("sphere_position_0",posSphere1->x, posSphere1->y, posSphere1->z);
			trace.setUniform1f("sphere_radius_0",radius1);
			trace.setUniform3f("sphere_color_0",color1->x,color1->y,color1->z);

			trace.setUniform3f("sphere_position_1",posSphere2->x, posSphere2->y, posSphere2->z);
			trace.setUniform1f("sphere_radius_1",radius2);
			trace.setUniform3f("sphere_color_1", color2->x,color2->y,color2->z);

			trace.setUniform3f("plane_position",0., -.5, 0.);
			trace.setUniform3f("plane_normal",0.,1.,0.043);

			trace.setUniform1f("light_intensity",intLight);
			trace.setUniform2f("light_specular",speLight->x,speLight->y);
			trace.setUniform3f("light_position",5.,5.,-5.);
			trace.setUniform3f("light_color",colLight->x,colLight->y,colLight->z);
			trace.setUniform1f("ambient",ambient);
			trace.setUniform3f("O", 0., 0., -1.);

			fbo.draw(-100,-100);

			trace.end();		
			gui.draw();
		}

		void keyPressed(int key){
			if(key == 'f')
				ofToggleFullscreen();
		}
};

int main( ){
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 800,600, OF_WINDOW);
	ofRunApp(new xApp());

}
