#ifndef PARABOLA_DYNAMICKEY_H
#define PARABOLA_DYNAMICKEY_H

#include "Platform.h"
#include "Signals.h"
#include "Strings.h"
#include <map>
#include <vector>

PARABOLA_NAMESPACE_BEGIN

class TextStream;

typedef vector<unsigned long> KeyList;
typedef map<StringID, KeyList> BindList;

/**
	\ingroup Core
	\class DynamicKeyBind
	\brief Efficient conversion of input to named actions

	Allows to map a key to multiple actions.

	It is very efficient when feeding keys/events to obtain the actions.
	You can also acquire keys assigned to the actions, but this is not
	what the system is better at, during gameplay.


*/
class PARABOLA_API DynamicKeyBind{
public:
		DynamicKeyBind();

		/*

		bool LoadFromFile(String fileName);
		bool LoadFromFile(TextFileStream &file);

		bool LoadCategoryFromFile(String fileName, String categoryName);
		bool LoadCategoryFromFile(TextFileStream &file, String categoryName);

		String GetAction(String token);
		String GetActionByInput(int inputType, int keyIdentifier);	
		String GetActionByEvent(Event &e);

		void ClearAllBindings();

		sigc::signal<void, String> OnActionTriggered;

	private:
		class GenericInput{
		public:

		};

		typedef vector<GenericInput> KeyList;

		map<int, String> KeyActions;
		map<int, String> MouseActions;
		map<int, String> JoystickActions;

		///Associate a StringID with a few keys
		map<StringID, KeyList> Actions;
		map<StringID, String> ActionNames;
	
	};*/
PARABOLA_NAMESPACE_END
#endif