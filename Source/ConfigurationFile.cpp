#ifndef MINIMAL_BUILD

#include "Nephilim/ConfigurationFile.h"
#include "Nephilim/TextFileStream.h"
#include "Nephilim/Strings.h"

namespace pE{
	ConfigurationFileCategory::ConfigurationFileCategory(String Category){
		CategoryName = Category;
	};

	void ConfigurationFileCategory::Insert(String Identifier, String Content){
		for(unsigned int i = 0; i < Configs.size(); i++){

			if(Configs[i].first == Identifier){
				Configs[i].second = Content;
				return;
			}
		}

		//didnt found, create
		Configs.push_back(make_pair(Identifier, Content));
	};
	void ConfigurationFileCategory::Remove(String Identifier){
		for(unsigned int i = 0; i < Configs.size(); i++){
			if(Configs[i].first == Identifier){
				Configs.erase(Configs.begin() + i);
			}
		}	
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////

	ConfigurationFile::ConfigurationFile(){
		InsertCategory("Default");

	};

	bool ConfigurationFile::SaveToFile(String File){
		TextStream out(File, StreamMode::WriteOnly);
		if(!out.valid()){
			//failed to load for writing
			return false;
		}

		out<<"#ParabolaContent=\"ConfigurationFile\"\n";

		for(unsigned int i = 0; i < Categories.size(); i++){
			//iterate categories to write, dont write empty ones
			if(Categories[i].Configs.size() == 0)
				continue;
			else{
				//the category header!
				out << String("\n[") + Categories[i].CategoryName + "]\n";

				for(unsigned int j = 0; j < Categories[i].Configs.size(); j++){
					out << String(Categories[i].Configs[j].first);
					out << "=";
					out << String(Categories[i].Configs[j].second);
					out << "\n";
				}
			}
		}
		return true; //sucess write
	};

	bool ConfigurationFile::LoadFromFile(String File){
		/*TextFileStream in(File, StreamMode::ReadOnly);
		if(!in.valid()){
			//failed to open file for reading
			return false;
		}

	
		String LastCategory = "Default";
		String Line;
		while(in.GetLine(Line)){
			//parse the lines
			if(Line[0] == '#'){
				//Do nothing, no interest in the line
			}
			else if(Line[0] == '['){
				//its a category
				Line.erase(Line.begin());
				Line.erase(Line.end()-1);

				InsertCategory(Line);
				LastCategory = Line;
			}
			else{
				//its a config
				StringList Cnfg = String::Split(Line, "=", 1);
				if(Cnfg.size() < 2){
					//Invalid parameter, its not like a=b
				}
				else{
					InsertConfig(Cnfg[0], Cnfg[1], LastCategory);
				}
			}
			Line.clear();
		};
*/
		return true;
	};

	void ConfigurationFile::InsertCategory(String Category){
		for(unsigned int i = 0; i < Categories.size(); i++){
			if(Categories[i].CategoryName == Category){
				return; //return because the category already exists
			}
		}

		//insert
		Categories.push_back(ConfigurationFileCategory(Category));
	};

	void ConfigurationFile::RemoveCategory(String Category){
		for(unsigned int i = 0; i < Categories.size(); i++){
			if(Categories[i].CategoryName == Category){
				//found the category, eliminate
				Categories.erase(Categories.begin() + i);
			}
		}
	};

	bool ConfigurationFile::GetBoolean(String Category, String Identifier){
		for(unsigned int i = 0; i < Categories.size(); i++){
			if(Categories[i].CategoryName == Category){
				//Found category
				for(unsigned int j = 0; j < Categories[i].Configs.size(); j++){
					//Found identifier
					if(Categories[i].Configs[j].first == Identifier){
						if(Categories[i].Configs[j].second == "true"){
							return true;
						}
						else{
							return false;
						}
					}
				}
			}
		}
		return false;
	};

	String ConfigurationFile::GetString(String Category, String Identifier){
		for(unsigned int i = 0; i < Categories.size(); i++){
			if(Categories[i].CategoryName == Category){
				//Found category
				for(unsigned int j = 0; j < Categories[i].Configs.size(); j++){
					//Found identifier
					if(Categories[i].Configs[j].first == Identifier){
						return Categories[i].Configs[j].second;
					}
				}
			}
		}
		return "";
	};
	int ConfigurationFile::GetInteger(String Category, String Identifier){
		for(unsigned int i = 0; i < Categories.size(); i++){
			if(Categories[i].CategoryName == Category){
				//Found category
				for(unsigned int j = 0; j < Categories[i].Configs.size(); j++){
					//Found identifier
					if(Categories[i].Configs[j].first == Identifier){
						return atoi(Categories[i].Configs[j].second.c_str() );
					}
				}
			}
		}
		return 0;
	};
	double ConfigurationFile::GetFloat(String Category, String Identifier){
		for(unsigned int i = 0; i < Categories.size(); i++){
			if(Categories[i].CategoryName == Category){
				//Found category
				for(unsigned int j = 0; j < Categories[i].Configs.size(); j++){
					//Found identifier
					if(Categories[i].Configs[j].first == Identifier){
						return atof(Categories[i].Configs[j].second.c_str() );
					}
				}
			}
		}
		return 0.f;
	};

	void ConfigurationFile::InsertConfig(String Identifier, String Content, String Category){
		for(unsigned int i = 0; i < Categories.size(); i++){
			if(Categories[i].CategoryName == Category){
				//Found the right category to insert
				Categories[i].Insert(Identifier, Content);
			}
		}
	};

	void ConfigurationFile::RemoveConfig(String Identifier, String Category){
		for(unsigned int i = 0; i < Categories.size(); i++){
			if(Categories[i].CategoryName == Category){
				//Found the right category to insert
				Categories[i].Remove(Identifier);
			}
		}
	};

	///////////////////////////////////////////////////PARABOLA CONFIG///////////////////////////////////////////
	ParabolaConfig::ParabolaConfig() : ConfigurationFile() {
		//Load defaults
		
		InsertCategory("Engine");
		InsertCategory("Perception");


		//Engine settings
		InsertConfig("EngineKeys", "true", "Engine");
		InsertConfig("SourceBox", "true", "Engine");

		//Perception settings
		InsertConfig("Resolution", "1024x768x32", "Perception");
		InsertConfig("Title", "Parabola Engine", "Perception");

		InsertConfig("Fullscreen", "false", "Perception");
		InsertConfig("Borders", "true", "Perception");
		InsertConfig("Resize", "true", "Perception");
		InsertConfig("Buttons", "true", "Perception");

		InsertConfig("Antialiasing", "0", "Perception");
		InsertConfig("StencilBuffer", "8", "Perception");
		InsertConfig("DepthBuffer", "24", "Perception");
		
		

	}
};

#endif