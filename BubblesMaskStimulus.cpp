/*
 *  BubblesMaskStimulus.cpp
 *  MonkeyWorksCore
 *
 *  Created by davidcox on 2/27/09.
 *  Copyright 2009 The President and Fellows of Harvard College. All rights reserved.
 *
 */

#include "BubblesMaskStimulus.h"
#include <boost/regex.hpp>
using namespace mw;


BubblesMaskStimulus::BubblesMaskStimulus(std::string _tag,
                                         std::string mask_filename,
                    shared_ptr<Variable> _xoffset, 
                    shared_ptr<Variable> _yoffset, 
                    shared_ptr<Variable> _xscale,
                    shared_ptr<Variable> _yscale,
                    shared_ptr<Variable> _rot,
                    shared_ptr<Variable> _alpha,
                    shared_ptr<Variable> _mask_xoffset,
                    shared_ptr<Variable> _mask_yoffset,
                    shared_ptr<Variable> _mask_xscale,
                    shared_ptr<Variable> _mask_yscale,
                    shared_ptr<Variable> _r,
                    shared_ptr<Variable> _g,
                    shared_ptr<Variable> _b) : 
                                BasicTransformStimulus(_tag, 
                                                       _xoffset, 
                                                       _yoffset, 
                                                       _xscale,
                                                       _yscale,
                                                       _rot,
                                                       _alpha) {
    

    shared_ptr<Variable> a_zero(new ConstantVariable(0.0));
    shared_ptr<Variable> a_one(new ConstantVariable(1.0)); 
                                    
    mask_image_stimulus = shared_ptr<ImageStimulus>(new ImageStimulus(mask_filename,
                                                                      mask_filename, 
                                                                      _mask_xoffset, 
                                                                      _mask_yoffset, 
                                                                      _mask_xscale, 
                                                                      _mask_yscale,
                                                                      a_zero,
                                                                      a_one));

    r = _r;
    g = _g;
    b = _b;
}



BubblesMaskStimulus::BubblesMaskStimulus(std::string _tag,
                                         shared_ptr<Variable> _xoffset, 
                                         shared_ptr<Variable> _yoffset, 
                                         shared_ptr<Variable> _xscale,
                                         shared_ptr<Variable> _yscale,
                                         shared_ptr<Variable> _rot,
                                         shared_ptr<Variable> _alpha,
                                         shared_ptr<ImageStimulus> _mask_image_stimulus,
                                         shared_ptr<Variable> _r,
                                         shared_ptr<Variable> _g,
                                         shared_ptr<Variable> _b) : 
                                BasicTransformStimulus(_tag, 
                                                      _xoffset, 
                                                      _yoffset, 
                                                      _xscale,
                                                      _yscale,
                                                      _rot,
                                                      _alpha) {
    mask_image_stimulus = _mask_image_stimulus;
    r = _r;
    g = _g;
    b = _b;
}


BubblesMaskStimulus::BubblesMaskStimulus(const BubblesMaskStimulus &tocopy) :
                    BasicTransformStimulus((const BasicTransformStimulus &)tocopy){

    mask_image_stimulus = tocopy.mask_image_stimulus;
}

BubblesMaskStimulus::~BubblesMaskStimulus(){ }

Stimulus * BubblesMaskStimulus::frozenClone(){
    shared_ptr<Variable> x_clone(xoffset->frozenClone());
	shared_ptr<Variable> y_clone(yoffset->frozenClone());
	shared_ptr<Variable> xs_clone(xscale->frozenClone());
	shared_ptr<Variable> ys_clone(yscale->frozenClone());
    shared_ptr<Variable> rot_clone(rotation->frozenClone());
	shared_ptr<Variable> alpha_clone(alpha_multiplier->frozenClone());	
	shared_ptr<Variable> r_clone(r->frozenClone());
	shared_ptr<Variable> g_clone(g->frozenClone());
	shared_ptr<Variable> b_clone(b->frozenClone());
	
    shared_ptr<ImageStimulus> mask_image_clone((ImageStimulus *)mask_image_stimulus->frozenClone());
    
	BubblesMaskStimulus *clone = new BubblesMaskStimulus(tag,
                                                         x_clone,
                                                         y_clone,
                                                         xs_clone,
                                                         ys_clone,
                                                         rot_clone,
                                                         alpha_clone,
                                                         mask_image_clone,
                                                         r_clone,
                                                         g_clone,
                                                         b_clone);
	clone->setIsFrozen(true);
	
	return clone;
}


void BubblesMaskStimulus::load(StimulusDisplay *display){
    if(mask_image_stimulus != NULL){
        mask_image_stimulus->load(display);
    } else {
        throw SimpleException("Invalid mask image in Bubbles Mask Stimulus");
    }
}

void BubblesMaskStimulus::draw(StimulusDisplay *display){
    mask_image_stimulus->draw(display);
    BasicTransformStimulus::draw(display);
}

void BubblesMaskStimulus::drawInUnitSquare(StimulusDisplay *display){
    // draw a square with an appropriately-sized cut-out for the mask image to show through
    
    // First, we need to compute the dimensions of the hole, transformed to the unit square
    // xa and xb will be the x bounds (left, right)
    // ya and yb will be the y bounds (bottom, top)
    
    mask_xoffset = mask_image_stimulus->getXOffset();
    mask_yoffset = mask_image_stimulus->getYOffset();
    mask_xscale = mask_image_stimulus->getXScale();
    mask_yscale = mask_image_stimulus->getYScale();
    
    double mask_xoffset_d = (double)mask_xoffset->getValue();
    double mask_xscale_d = (double)mask_xscale->getValue();
    double xoffset_d = (double)xoffset->getValue();
    double xscale_d = (double)xscale->getValue();
    double mask_yoffset_d = (double)mask_yoffset->getValue();
    double mask_yscale_d = (double)mask_yscale->getValue();
    double yoffset_d = (double)yoffset->getValue();
    double yscale_d = (double)yscale->getValue();
    
    
    
    double xa = ((mask_xoffset_d - xoffset_d) / xscale_d) + 0.5 - (mask_xscale_d/2.0)/xscale_d;
    double xb = ((mask_xoffset_d - xoffset_d) / xscale_d) + 0.5 + (mask_xscale_d/2.0)/xscale_d;
    double ya = ((mask_yoffset_d - yoffset_d) / yscale_d) + 0.5 - (mask_yscale_d/2)/yscale_d;
    double yb = ((mask_yoffset_d - yoffset_d) / yscale_d) + 0.5 + (mask_yscale_d/2)/yscale_d;

    
    if(r == NULL || g == NULL || b == NULL ){
		merror(M_DISPLAY_MESSAGE_DOMAIN,
			   "NULL color variable in BubblesMaskStimulus.");
	}
	
	
    // get current values in these variables.
	GLfloat _r = (float)(*r);
	GLfloat _g = (float)(*g);
	GLfloat _b = (float)(*b);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
	
	glBegin(GL_QUADS);
	glColor4f(_r, _g, _b, * alpha_multiplier);
	
    // Left blocker
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(xa, 1.0, 0.0);
    glVertex3f(xa, 0.0, 0.0);

    // Right blocker
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(xb, 1.0, 0.0);
    glVertex3f(xb, 0.0, 0.0);
    
	
    // Top blocker
    glVertex3f(xa, 1.0, 0.0);
    glVertex3f(xb, 1.0, 0.0);
    glVertex3f(xb, yb, 0.0);
    glVertex3f(xa, yb, 0.0);
    
    // Bottom blocker
    glVertex3f(xa, 0.0, 0.0);
    glVertex3f(xb, 0.0, 0.0);
    glVertex3f(xb, ya, 0.0);
    glVertex3f(xa, ya, 0.0);

    glEnd();
        
	glDisable(GL_BLEND);
    
    //last_r = _r;
//    last_g = _g;
//    last_b = _b;
}

Data BubblesMaskStimulus::getCurrentAnnounceDrawData(){

    // TODO: correct data
    Data announce_data(BasicTransformStimulus::getCurrentAnnounceDrawData());
    announce_data.addElement(STIM_TYPE,"bubbles_mask");
    
    return (announce_data);
}


