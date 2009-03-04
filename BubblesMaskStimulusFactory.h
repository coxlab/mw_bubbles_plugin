/*
 *  BubblesMaskStimulusFactory.h
 *  MonkeyWorksCore
 *
 *  Created by davidcox on 2/27/09.
 *  Copyright 2009 The President and Fellows of Harvard College. All rights reserved.
 *
 */


#ifndef BUBBLES_STIMULUS_FACTORY_H
#define BUBBLES_STIMULUS_FACTORY_H

#include "MonkeyWorksCore/ComponentFactory.h"
using namespace mw;

class BubblesMaskStimulusFactory : public ComponentFactory {
	virtual shared_ptr<mw::Component> createObject(std::map<std::string, std::string> parameters,
                                                   mw::ComponentRegistry *reg);
};

#endif
