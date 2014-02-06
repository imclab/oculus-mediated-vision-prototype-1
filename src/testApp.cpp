#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //CHECK ALL SHADER PERMISSIONS BEFORE RELEASING
    
    camWidth = 800;
    camHeight = 640;
    
    for(int i = 0; i < 2; i++)
    {
        vidGrabber[i].setDeviceID(i);
        vidGrabber[i].setDesiredFrameRate(60);
        
        vidGrabber[i].initGrabber(camWidth, camHeight);
        
        tex[i].setTextureWrap(GL_REPEAT, GL_REPEAT);
        tex[i].allocate(camHeight,camWidth,GL_RGB,GL_RGBA);
        tbIm[i].allocate(camHeight,camWidth,OF_IMAGE_COLOR_ALPHA);
    }
    
    hmdWarpShader.load("Shaders/HmdWarpExp");
    hmdWarpShader2.load("Shaders/HmdWarpPost");
    
    shaderSwap = true;
}

//--------------------------------------------------------------
void testApp::update(){
    for(int i = 0; i < 2; i++)
    {
        vidGrabber[i].update();
        
        if (vidGrabber[i].isFrameNew())
        {
            for(int j = 0; j < camHeight; j++)
            {
                for(int k = 0; k < camWidth; k++)
                {
                    
                    tbIm[i].setColor(j,k,vidGrabber[i].getPixelsRef().getColor(k, j));
                    
                }
            }
        }
        tbIm[i].reloadTexture();
       // tex[i] = tbIm[i].getTextureReference();
        
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofEnableNormalizedTexCoords(); //This lets you do 0-1 range instead of 0-640 (in pixels)
    
    //vidGrabber_[0].draw(0, 0);
    
    
    ///oculus----------------------------
    float K0 = 1.0f;
    float K1 = 0.22f;
    float K2 = 0.24f;
    float K3 = 0.0f;
    
    float _x = 0.0f;
    float _y = 0.0f;
    float _w = 1.0f;
    float _h = 1.0f;
    
    float as = 1280/800;
	
	float DistortionXCenterOffset = -0.25f;
    DistortionXCenterOffset = 0.0f;
    
    
    if(shaderSwap && tbIm[0].bAllocated()){
     
        tex[0].bind();
 
        hmdWarpShader.begin();
         hmdWarpShader.setUniformTexture("tex", tex[0], 0);
         hmdWarpShader.setUniform2f("LensCenter", _x + (0+ DistortionXCenterOffset * 0.5f)*0.5f, _y + _h*0.5f );
         hmdWarpShader.setUniform2f("ScreenCenter", _x + _w*1.0f, _y + _h*1.0f );
         hmdWarpShader.setUniform2f("Scale", (_w/1.0f) * 1.0f, (_h/1.0f) * 1.0f * as );
         hmdWarpShader.setUniform2f("ScaleIn", (1.0f/_w), (1.0f/_h) / as );
         hmdWarpShader.setUniform4f("HmdWarpParam", K0, K1, K2, K3 );
         
  
        ofPushMatrix();
        ofTranslate(0,0);
        glBegin(GL_QUADS);
        glTexCoord2f(1,1); glVertex3f(0,0,0);
        glTexCoord2f(0,1); glVertex3f(640,0,0);
        glTexCoord2f(0,0); glVertex3f(640,800,0);
        glTexCoord2f(1,0); glVertex3f(0,800,0);
        glEnd();
        ofPopMatrix();
        hmdWarpShader.end();
        tex[0].unbind();
    
        // -----------
        
         tex[1].bind();
 
         hmdWarpShader.begin();
         hmdWarpShader.setUniformTexture("tex", tex[1], 0);
         hmdWarpShader.setUniform2f("LensCenter", _x + (+ DistortionXCenterOffset * 0.5f)*0.5f, _y + _h*0.5f );
         hmdWarpShader.setUniform2f("ScreenCenter", _x + _w*1.0f, _y + _h*1.0f );
         hmdWarpShader.setUniform2f("Scale", (_w/1.0f) * 1.0f, (_h/1.0f) * 1.0f * as );
         hmdWarpShader.setUniform2f("ScaleIn", (1.0f/_w), (1.0f/_h) / as );
         hmdWarpShader.setUniform4f("HmdWarpParam", K0, K1, K2, K3 );
 
         
         ofPushMatrix();
         ofTranslate(0,0);
         glBegin(GL_QUADS);
         glTexCoord2f(1,1); glVertex3f(640,0,0);
         glTexCoord2f(0,1); glVertex3f(1280,0,0);
         glTexCoord2f(0,0); glVertex3f(1280,800,0);
         glTexCoord2f(1,0); glVertex3f(640,800,0);
         glEnd();
         ofPopMatrix();
         hmdWarpShader.end();
         tex[1].unbind();
        
    }
    else{
        
        tex[0].bind();
        
        hmdWarpShader2.begin();
        hmdWarpShader2.setUniformTexture("tex", tex[0], 0);
        hmdWarpShader2.setUniform2f("LensCenter", _x + (0+ DistortionXCenterOffset * 0.5f)*0.5f, _y + _h*0.5f );
        hmdWarpShader2.setUniform2f("ScreenCenter", _x + _w*1.0f, _y + _h*1.0f );
        hmdWarpShader2.setUniform2f("Scale", (_w/1.0f) * 1.0f, (_h/1.0f) * 1.0f * as );
        hmdWarpShader2.setUniform2f("ScaleIn", (1.0f/_w), (1.0f/_h) / as );
        hmdWarpShader2.setUniform4f("HmdWarpParam", K0, K1, K2, K3 );
        
        
        ofPushMatrix();
        ofTranslate(0,0);
        glBegin(GL_QUADS);
        glTexCoord2f(1,1); glVertex3f(0,0,0);
        glTexCoord2f(0,1); glVertex3f(640,0,0);
        glTexCoord2f(0,0); glVertex3f(640,800,0);
        glTexCoord2f(1,0); glVertex3f(0,800,0);
        glEnd();
        ofPopMatrix();
        hmdWarpShader2.end();
        tex[0].unbind();
        
        // -----------
        
        tex[1].bind();
        
        hmdWarpShader2.begin();
        hmdWarpShader2.setUniformTexture("tex", tex[1], 0);
        hmdWarpShader2.setUniform2f("LensCenter", _x + (+ DistortionXCenterOffset * 0.5f)*0.5f, _y + _h*0.5f );
        hmdWarpShader2.setUniform2f("ScreenCenter", _x + _w*1.0f, _y + _h*1.0f );
        hmdWarpShader2.setUniform2f("Scale", (_w/1.0f) * 1.0f, (_h/1.0f) * 1.0f * as );
        hmdWarpShader2.setUniform2f("ScaleIn", (1.0f/_w), (1.0f/_h) / as );
        hmdWarpShader2.setUniform4f("HmdWarpParam", K0, K1, K2, K3 );
        
        
        ofPushMatrix();
        ofTranslate(0,0);
        glBegin(GL_QUADS);
        glTexCoord2f(1,1); glVertex3f(640,0,0);
        glTexCoord2f(0,1); glVertex3f(1280,0,0);
        glTexCoord2f(0,0); glVertex3f(1280,800,0);
        glTexCoord2f(1,0); glVertex3f(640,800,0);
        glEnd();
        ofPopMatrix();
        hmdWarpShader2.end();
        tex[1].unbind();
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if( key == 'f' )
	{
		ofToggleFullscreen();
	}
    
    if( key == 's' )
	{
		shaderSwap = !shaderSwap;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}
