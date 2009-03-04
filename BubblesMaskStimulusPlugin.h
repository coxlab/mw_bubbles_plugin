/*
 *  BubblesMaskStimulusPlugins.h
 *  BubblesMaskStimulusPlugins
 *
 *  Created by bkennedy on 8/14/08.
 *  Copyright 2009 The President and Fellows of Harvard College. All rights reserved.
 *
 */

#include <MonkeyWorksCore/Plugin.h>
using namespace mw;

extern "C"{
    Plugin *getPlugin();
}

class BubblesMaskStimulusPlugin : public Plugin {
    
	virtual void registerComponents(shared_ptr<mw::ComponentRegistry> registry);	
};
