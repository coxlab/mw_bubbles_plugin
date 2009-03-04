/*
 *  BubblesMaskStimulus.h
 *  MonkeyWorksCore
 *
 *  Created by davidcox on 2/27/09.
 *  Copyright 2009 The President and Fellows of Harvard College. All rights reserved.
 *
 */

#ifndef BUBBLES_STIMULUS_H
#define BUBBLES_STIMULUS_H

#include "MonkeyWorksCore/StandardStimuli.h"
#include <string>
using namespace mw;

class BubblesMaskStimulus : public BasicTransformStimulus {
protected:
    
    shared_ptr<ImageStimulus> mask_image_stimulus; 
    shared_ptr<Variable> mask_xoffset, mask_yoffset, mask_xscale, mask_yscale;
    shared_ptr<Variable> r, g, b;
    
public:
	BubblesMaskStimulus(std::string _tag,
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
                        shared_ptr<Variable> _b);
    
    BubblesMaskStimulus(std::string _tag,
                        shared_ptr<Variable> _xoffset, 
                        shared_ptr<Variable> _yoffset, 
                        shared_ptr<Variable> _xscale,
                        shared_ptr<Variable> _yscale,
                        shared_ptr<Variable> _rot,
                        shared_ptr<Variable> _alpha,
                        shared_ptr<ImageStimulus> _mask_image,
                        shared_ptr<Variable> _r,
                        shared_ptr<Variable> _g,
                        shared_ptr<Variable> _b);
    
	BubblesMaskStimulus(const BubblesMaskStimulus &tocopy);
	~BubblesMaskStimulus();
	virtual Stimulus * frozenClone();
	
    virtual void load(StimulusDisplay *display);
    virtual void draw(StimulusDisplay *display);
	virtual void drawInUnitSquare(StimulusDisplay *display);
	virtual Data getCurrentAnnounceDrawData();
};

#endif 
