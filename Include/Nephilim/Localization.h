#ifndef PARABOLA_LOCALIZATION_H
#define PARABOLA_LOCALIZATION_H

#include "Platform.h"
#include "Strings.h"
#include "NameGenerator.h"
#include "Signals.h"

#include <map>

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Core
	\class Localization
	\brief Can hold, load and translate tokens into localized strings

	Localized strings support arguments, in the form of {0} (or {n}),
	those strings need to be fed with content to replace those arguments.

	You must always specify a default language, by default it is en-US.
	By omission, resources are loaded into the en-US language. 

	The default language must contain ALL the tokens and cannot be unloaded unless the Localization object is reset completely.

	There are two ways to use this system.

	Loading everything:
	- Load your Localization object with all languages at once
	- Simply request resources, they will be given to you in the language selected
	- If a resource doesn't exist in that language, you get the default language one.
	- When user changes language, it will work immediately.

    Loading by need:
	- Load your Localization object with the selected language, could be auto detected
	- When the user changes language, you unload the current resources that don't belong to the default language.
	- Then, you load the resources of the selected language
	- Use normally.
*/
/*class PARABOLA_API Localization{
public:
	/// Creates an empty resource tracker, by default the language is en-US
	Localization();

	/// Make sure everything is unloaded
	virtual ~Localization();

	/// Fired when the language is changed, but before the getLanguage() changes.
	sigc::signal<void, String, Localization*> onLanguageChanged;

	/// Sets the language as the one detected in the underlying OS
	void autoDetectLanguage();

	/// Set the language to fetch resources
	/// It absolutely should be a token such as en-GB, or other defined in the ISO's \see getSystemLanguage()
	void setLanguage(const String &language);

	/// Returns the currently set language
	String getLanguage();

	/// Set the default language.
	/// Only works if the different languages all have the same number of resources.
	/// This happens to protect from changing the default language when there are resources that are not defined in all languages.
	bool setDefaultLanguage(const String &language);

	/// Returns the current default language - "en-US" by default.
	String getDefaultLanguage();

	/// Unloads all resources
	void unloadAll();

	/// Unloads all resources of a language
	void unloadLanguage(const String &language);

	/// Unloads all resources from a language, that have a definition in the other language.
	/// This is a very specific function, that should be used as follows:
	/// User changes language -> load new language resources -> unloadLanguageSpecial("en-US", "pt-PT") -> done
	/// This way you ensure to unload unneeded resources, while keeping the ones that are not defined in the new language
	void unloadLanguageSpecial(const String &unloadLang, const String &newLang);

	/// Loads the default language from the file
	/// Works in one of the two ways:
	/// - Finds the language specifier of getDefaultLanguage()
	/// - Finds unspecified tokens
	bool loadDefaultFromFile(const String &fileName);

	/// Loads all languages found in the file
	bool loadFromFile(const String &fileName);

	/// Loads resources of a specified language from the file.
	bool loadLanguageFromFile(const String &fileName, const String &language);

	/// Loads languages from a custom script type
	/// If byteCode is true, the script is loaded as compiled, else, it is interpreted
	/// This notation allows to define a global variable, whether the game scripts are compiled or not,
	/// and make the correct loading without changing code, only the variable.
	bool loadFromLocalizationScript(const String &fileName, bool byteCode = false);

	/// Returns a string with the underlying system language currently set.
	/// The result is a string in the format of <lang>-<REGION>
	/// Where lang is a lowercase ISO 639 language code
	/// And REGION is uppercase ISO 3166-1 country/region identifier
	static String getSystemLanguage();

	/// Same as getSystemLanguage(), but for the operative system current user.
	static String getUserLanguage();

private:
	String myCurrentLanguage;
	/// The locked language - it contains all resources
	/// One cannot unload the default language resources, but replace them.
	String myDefaultLanguage;
};
*/
class PARABOLA_API LocalizationUnit
{
public:
	LocalizationUnit();

	String getString(const String& token);

	typedef std::map<String, String> Dictionary;
	std::map<String, Dictionary> m_table;
	String m_currentLanguage;
};

PARABOLA_NAMESPACE_END
#endif