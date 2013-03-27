/*#include "DynamicKeys.h"
#include "Stimulus.h"
#include "StringList.h"

namespace pE{
	
	int GetKeyID(String key){
		key.toLowerCase();

		if(key == "up")return (int)(Keyboard::Up);
		else if(key == "down")return (int)(Keyboard::Down);
		else if(key == "left")return (int)(Keyboard::Left);
		else if(key == "right")return (int)(Keyboard::Right);

		else if(key == "a")return (int)(Keyboard::A);
		else if(key == "b")return (int)(Keyboard::B);
		else if(key == "c")return (int)(Keyboard::C);
		else if(key == "d")return (int)(Keyboard::D);
		else if(key == "e")return (int)(Keyboard::E);
		else if(key == "f")return (int)(Keyboard::F);
		else if(key == "g")return (int)(Keyboard::G);
		else if(key == "h")return (int)(Keyboard::H);
		else if(key == "i")return (int)(Keyboard::I);
		else if(key == "j")return (int)(Keyboard::J);
		else if(key == "k")return (int)(Keyboard::K);
		else if(key == "l")return (int)(Keyboard::L);
		else if(key == "m")return (int)(Keyboard::M);
		else if(key == "n")return (int)(Keyboard::N);
		else if(key == "o")return (int)(Keyboard::O);
		else if(key == "p")return (int)(Keyboard::P);
		else if(key == "q")return (int)(Keyboard::Q);
		else if(key == "r")return (int)(Keyboard::R);
		else if(key == "s")return (int)(Keyboard::S);
		else if(key == "t")return (int)(Keyboard::T);
		else if(key == "u")return (int)(Keyboard::U);
		else if(key == "v")return (int)(Keyboard::V);
		else if(key == "w")return (int)(Keyboard::W);
		else if(key == "x")return (int)(Keyboard::X);
		else if(key == "y")return (int)(Keyboard::Y);
		else if(key == "z")return (int)(Keyboard::Z);

		else
			return -1;
	};

	int GetMouseID(String key){
		key.toLowerCase();

		if(key == "mouse_left")return (int)(Mouse::Left);
		if(key == "mouse_right")return (int)(Mouse::Right);	

		return -1;
	};

	int GetJoystickID(String key){
		key.toLowerCase();

		String prefix = "joy_";
		for(int i = 0; i < sf::Joystick::ButtonCount; i++){
			if(key == prefix + String::number(i))return i;
		}	

		return -1;
	};

	DynamicKeyBinding::DynamicKeyBinding(){

	};


	bool DynamicKeyBinding::LoadFromFile(String fileName){
		
		TextFileStream in(fileName, StreamMode::ReadOnly);

		if(!in.valid())
			return false;

		return LoadFromFile(in);

	};

	bool DynamicKeyBinding::LoadFromFile(TextFileStream &file){
		String str;
		String currCategory = "Default";
/*
		while(file.getLine(str)){
			
			if(str.length() == 0){
				//empty string
			}
			else if(str.at(0) == '#'){
				//comment line

			}
			else if(str.at(0) == '['){
				//category
				str.erase(str.begin());
				str.erase(str.end()-1);
				currCategory = str;
			}
			else{
				//key binding
				StringList params = str.split("=", 1);

				if(params.size() == 0){
					cout<<"Error: invalid line."<<endl;
				}
				else if(params.size() == 1){
					cout<<"Error: Missing syntax elements"<<endl;
				}
				else if(params.size() > 2){
					cout<<"Error: Invalid syntax"<<endl;
				}
				else{
					StringList keys = params[1].split(" ", 0);

					String token = params[0];					
					token.removeCharacter(' ');

					for(StringList::iterator it = keys.begin(); it != keys.end(); it++){
						int keyID = GetKeyID((*it));

						if(keyID == -1){
							//not in the keys

							keyID = GetMouseID((*it));

							if(keyID == -1){
								keyID = GetJoystickID((*it));

								if(keyID == -1){
									//joystick not either
									cout<<"Error: Unknown key/mouse/joystick."<<endl;

								}
								else{
									JoystickActions[keyID] = token;
								}

							}
							else{
								MouseActions[keyID] = token;
							}
						}
						else{
							KeyActions[keyID] = token;
						
						}
						

						
					}
					
				}
			}

			str.clear();
		}*/
/*
		return true;
	};

	String DynamicKeyBinding::GetAction(String token){
		StringID id = makeStringID(token, false);

		return "";
	};

	String DynamicKeyBinding::GetActionByEvent(Event &e){
		String resultAction;
		if(e.Type == Event::KeyPressed){
			resultAction = KeyActions[e.key.code];
		}
		else if(e.Type == Event::KeyReleased){
			resultAction = KeyActions[e.key.code] + "_END";
		}
		else if(e.Type == Event::MouseButtonPressed || e.Type == Event::MouseButtonReleased){
			//look for mouse action
			resultAction = MouseActions[e.MouseButton.Button];	
		}
		else if(e.Type == Event::JoystickButtonPressed || e.Type == Event::JoystickButtonReleased){
			resultAction = JoystickActions[e.JoystickButton.Button];
		}

		if(resultAction == "")return "NONE";
		else
			return resultAction;
	};

	String DynamicKeyBinding::GetActionByInput(int inputType, int keyIdentifier){
		return "";
	};

	bool DynamicKeyBinding::LoadCategoryFromFile(String fileName, String categoryName){
		TextFileStream in(fileName, StreamMode::ReadOnly);

		if(!in.valid())
			return false;

		return LoadCategoryFromFile(in, categoryName);
	};

	bool DynamicKeyBinding::LoadCategoryFromFile(TextFileStream &file, String categoryName){
		String str;
		String currCategory = "Default";*/
/*
		while(file.GetLine(str)){

			if(str.length() == 0){
				//empty string
			}
			else if(str.at(0) == '#'){
				//comment line

			}
			else if(str.at(0) == '['){
				//category
				str.erase(str.begin());
				str.erase(str.end()-1);
				currCategory = str;
			}
			else{
				//key binding
				StringList params = str.split("=", 1);

				if(params.size() == 0){
					cout<<"Error: invalid line."<<endl;
				}
				else if(params.size() == 1){
					cout<<"Error: Missing syntax elements"<<endl;
				}
				else if(params.size() > 2){
					cout<<"Error: Invalid syntax"<<endl;
				}
				else{
					if(currCategory != categoryName){
						//cout<<"CANT LOAD BECAUSE CATEGORY IS: "<<currCategory<<" and "<<categoryName<<endl;
						 //wont insert this one because it doesnt belong to the category
					}
					else{							
						StringList keys = params[1].split(" ", 0);

						String token = params[0];					
						token.removeCharacter(' ');

						for(StringList::iterator it = keys.begin(); it != keys.end(); it++){
							

							int keyID = GetKeyID((*it));

							if(keyID == -1){
								//not in the keys

								keyID = GetMouseID((*it));

								if(keyID == -1){
									keyID = GetJoystickID((*it));

									if(keyID == -1){
										//joystick not either
										cout<<"Error: Unknown key/mouse/joystick."<<endl;

									}
									else{
										JoystickActions[keyID] = token;
									}

								}
								else{
									MouseActions[keyID] = token;
								}
							}
							else{
								KeyActions[keyID] = token;
								//cout<<"Loaded keys for category: "<<categoryName<<endl;

							}



						}
					}

				}
			}

			str.clear();
		}*/
/*
		return true;
	};

	void DynamicKeyBinding::ClearAllBindings(){

	};
};*/