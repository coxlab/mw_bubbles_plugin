/*
 *  BubblesMaskStimulusFactory.cpp
 *  MonkeyWorksCore
 *
 *  Created by davidcox on 2/27/09.
 *  Copyright 2009 The President and Fellows of Harvard College. All rights reserved.
 *
 */

#include "BubblesMaskStimulusFactory.h"
#include "BubblesMaskStimulus.h"
#include <boost/regex.hpp>
#include "MonkeyWorksCore/ComponentRegistry.h"
#include "MonkeyWorksCore/ParsedColorTrio.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
using namespace mw;

shared_ptr<mw::Component> BubblesMaskStimulusFactory::createObject(std::map<std::string, std::string> parameters,
                                                               mw::ComponentRegistry *reg) {
	REQUIRE_ATTRIBUTES(parameters, 
					   "tag", 
                       "path",
					   "x_size", 
					   "y_size", 
					   "x_position", 
					   "y_position", 
					   
                       "mask_x_size", 
					   "mask_y_size", 
					   "mask_x_position", 
					   "mask_y_position",
                       
                       "rotation", 
					   "color"
					   );
	
    
    namespace bf = boost::filesystem;
    
	std::string tagname(parameters.find("tag")->second);
    
    bf::path mask_image_path = reg->getPath(parameters["working_path"], parameters["path"]);
    if(!bf::exists(mask_image_path)) {
		throw InvalidReferenceException(parameters.find("reference_id")->second, "path", parameters.find("path")->second);
	}
	
	if(bf::is_directory(mask_image_path)) {
		throw InvalidReferenceException(parameters.find("reference_id")->second, "path", parameters.find("path")->second);
	}
	
    
	shared_ptr<Variable> x_size = reg->getVariable(parameters.find("x_size")->second);	
	shared_ptr<Variable> y_size = reg->getVariable(parameters.find("y_size")->second);	
	shared_ptr<Variable> x_position = reg->getVariable(parameters.find("x_position")->second);	
	shared_ptr<Variable> y_position = reg->getVariable(parameters.find("y_position")->second);	
	shared_ptr<Variable> rotation = reg->getVariable(parameters.find("rotation")->second);	
	shared_ptr<Variable> alpha_multiplier = reg->getVariable(parameters["alpha_multiplier"], "1");
    
	shared_ptr<Variable> mask_x_size = reg->getVariable(parameters.find("mask_x_size")->second);	
	shared_ptr<Variable> mask_y_size = reg->getVariable(parameters.find("mask_y_size")->second);	
	shared_ptr<Variable> mask_x_position = reg->getVariable(parameters.find("mask_x_position")->second);	
	shared_ptr<Variable> mask_y_position = reg->getVariable(parameters.find("mask_y_position")->second);	
    
	
	ParsedColorTrio pct(reg,parameters.find("color")->second);
	shared_ptr<Variable> r = pct.getR();	
	shared_ptr<Variable> g = pct.getG();	
	shared_ptr<Variable> b = pct.getB();	
	
	
	
	
	checkAttribute(x_size, parameters.find("reference_id")->second, "x_size", parameters.find("x_size")->second);                                                  
	checkAttribute(y_size, parameters.find("reference_id")->second, "y_size", parameters.find("y_size")->second);                                                  
	checkAttribute(x_position, parameters.find("reference_id")->second, "x_position", parameters.find("x_position")->second);                                      
	checkAttribute(y_position, parameters.find("reference_id")->second, "y_position", parameters.find("y_position")->second);                                      
	checkAttribute(rotation, parameters.find("reference_id")->second, "rotation", parameters.find("rotation")->second);                                            
	checkAttribute(alpha_multiplier, parameters.find("reference_id")->second, "alpha_multiplier", parameters.find("alpha_multiplier")->second);                    

	if(GlobalCurrentExperiment == 0) {
		throw SimpleException("no experiment currently defined");		
	}
	
	shared_ptr<StimulusDisplay> defaultDisplay = GlobalCurrentExperiment->getStimulusDisplay();
	if(defaultDisplay == 0) {
		throw SimpleException("no stimulusDisplay in current experiment");
	}
	
	
	shared_ptr <BubblesMaskStimulus> new_bubble_stimulus = shared_ptr<BubblesMaskStimulus>(new BubblesMaskStimulus(tagname, 
                                                                                                       mask_image_path.string(),
																									   x_position,
																									   y_position,
																									   x_size,
																									   y_size,
																									   rotation,
																									   alpha_multiplier,
                                                                                                       mask_x_position,
                                                                                                       mask_y_position,
                                                                                                       mask_x_size,
                                                                                                       mask_y_size,
                                                                                                       r,
																									   g,
																									   b));
	
	
	
	new_bubble_stimulus->load(defaultDisplay.get());
	shared_ptr <StimulusNode> thisStimNode = shared_ptr<StimulusNode>(new StimulusNode(new_bubble_stimulus));
	reg->registerStimulusNode(tagname, thisStimNode);
	
	return new_bubble_stimulus;
}

