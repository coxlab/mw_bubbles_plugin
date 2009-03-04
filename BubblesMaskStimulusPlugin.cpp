/*
 *  BubblesMaskStimulusPlugins.cpp
 *  BubblesMaskStimulusPlugins
 *
 *  Created by bkennedy on 8/14/08.
 *  Copyright 2009 The President and Fellows of Harvard College. All rights reserved.
 *
 */

#include "BubblesMaskStimulusPlugin.h"
#include "BubblesMaskStimulusFactory.h"
#include "MonkeyWorksCore/ComponentFactory.h"
using namespace mw;

Plugin *getPlugin(){
    return new BubblesMaskStimulusPlugin();
}


void BubblesMaskStimulusPlugin::registerComponents(shared_ptr<mw::ComponentRegistry> registry) {
	registry->registerFactory(std::string("stimulus/bubbles_mask"),
							  (ComponentFactory *)(new BubblesMaskStimulusFactory()));
}
