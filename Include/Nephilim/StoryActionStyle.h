#ifndef PARABOLA_STORYACTIONSTYLE_H
#define PARABOLA_STORYACTIONSTYLE_H

#include "Platform.h"
#include "StringList.h"
#include <map>
#include <iostream>

PARABOLA_NAMESPACE_BEGIN

	/**
		\class StoryActionStyle
		\brief Represents the set of parameters an action is configured with.
	*/
	class PARABOLA_API StoryActionStyle{
	public:
		StoryActionStyle(){

		}
		StoryActionStyle(String style_parameters){
			StringList list = style_parameters.split(" ");

			for(unsigned int i = 0; i < list.size(); i++){
				//now extract the token and the params
				String token = list[i];
				StringList params;
			
				if(token.find_first_of('[') != token.npos){
					//there are parameters
					String res;
					size_t k = token.find_first_of('[') + 1;
					size_t l = token.find_last_of(']');

					res.insert(0, token, k, l-k);

					StringList paramList = res.split(",");
					for(unsigned int j = 0; j < paramList.size(); j++){
						params.push_back(paramList[j]);
					}

					token.erase(token.begin() + token.find_first_of('['), token.end());
				}

				std::cout<<"STYLE SHEET PROPERTY: "<<token<<" = "<<params.join(";")<<std::endl;
				stylesheet[token] = params;
			}
		}

		bool isSet(String param){
			if(stylesheet.find(param) == stylesheet.end())return false;
			else return true;
		}

		StringList getParam(String param){
			StringList out;
			if(stylesheet.find(param) != stylesheet.end()){
				out = stylesheet[param];
			}
			return out;
		}

		std::map<String, StringList> stylesheet;
	};

PARABOLA_NAMESPACE_END
#endif