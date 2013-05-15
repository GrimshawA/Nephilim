#include "Nephilim/Localization.h"

#ifdef NEPHILIM_WINDOWS
#include <windows.h>
#endif

#include <iostream>

NEPHILIM_NS_BEGIN


LocalizationUnit::LocalizationUnit() :
	m_currentLanguage("en-US")
{
	m_table["pt-PT"]["[START]"] = "Arrancar";
	m_table["en-US"]["[START]"] = "Launch";

	m_table["pt-PT"]["[INCREASE]"] = "Aumentar";
	m_table["en-US"]["[INCREASE]"] = "Increase";
}

String LocalizationUnit::getString(const String& token)
{
	if(m_table.find(m_currentLanguage) != m_table.end())
	{
		Dictionary::iterator it = m_table[m_currentLanguage].find(token);
		if(it != m_table[m_currentLanguage].end())
		{
			return (*it).second;
		}
		else return "";
	}
	else return "";
}



/*


/// Creates an empty resource tracker, by default the language is en-US
Localization::Localization(){

};

/// Make sure everything is unloaded
Localization::~Localization(){

};

/// Sets the language as the one detected in the underlying OS
void Localization::autoDetectLanguage(){

};

/// Set the language to fetch resources
/// It absolutely should be a token such as en-GB, or other defined in the ISO's \see getSystemLanguage()
void Localization::setLanguage(const String &language){

};

/// Returns the currently set language
String Localization::getLanguage(){
	return "not done";
};

/// Set the default language.
/// Only works if the different languages all have the same number of resources.
/// This happens to protect from changing the default language when there are resources that are not defined in all languages.
bool Localization::setDefaultLanguage(const String &language){
	return false;
};

/// Returns the current default language - "en-US" by default.
String Localization::getDefaultLanguage(){
	return "not done";
};

/// Unloads all resources
void Localization::unloadAll(){

};

/// Unloads all resources of a language
void Localization::unloadLanguage(const String &language){

};

/// Unloads all resources from a language, that have a definition in the other language.
/// This is a very specific function, that should be used as follows:
/// User changes language -> load new language resources -> unloadLanguageSpecial("en-US", "pt-PT") -> done
/// This way you ensure to unload unneeded resources, while keeping the ones that are not defined in the new language
void Localization::unloadLanguageSpecial(const String &unloadLang, const String &newLang){

};

/// Loads the default language from the file
/// Works in one of the two ways:
/// - Finds the language specifier of getDefaultLanguage()
/// - Finds unspecified tokens
bool Localization::loadDefaultFromFile(const String &fileName){
	return false;
};

/// Loads all languages found in the file
bool Localization::loadFromFile(const String &fileName){
	return false;

};

/// Loads resources of a specified language from the file.
bool Localization::loadLanguageFromFile(const String &fileName, const String &language){
	return false;

};

/// Loads languages from a custom script type
/// If byteCode is true, the script is loaded as compiled, else, it is interpreted
/// This notation allows to define a global variable, whether the game scripts are compiled or not,
/// and make the correct loading without changing code, only the variable.
bool Localization::loadFromLocalizationScript(const String &fileName, bool byteCode){
	return true;
};

/// Returns a string with the underlying system language currently set.
/// The result is a string in the format of <lang>-<REGION>
/// Where lang is a lowercase ISO 639 language code
/// And REGION is uppercase ISO 3166-1 country/region identifier
String Localization::getSystemLanguage(){
	String result = "not implemented";

#ifdef NEPHILIM_WINDOWS

	wchar_t str[LOCALE_NAME_MAX_LENGTH];
	GetSystemDefaultLocaleName((LPWSTR)&str, LOCALE_NAME_MAX_LENGTH);
	result.fromWide(static_cast<std::wstring>( str ) );
#endif

	return result;
};

/// Same as getSystemLanguage(), but for the operative system current user.
String Localization::getUserLanguage(){
	String result = "not implemented";

#ifdef NEPHILIM_WINDOWS
	wchar_t str[LOCALE_NAME_MAX_LENGTH];
	GetUserDefaultLocaleName((LPWSTR)&str, LOCALE_NAME_MAX_LENGTH);
	result.fromWide(static_cast<std::wstring>( str ) );
#endif

	return result;
};
*/
NEPHILIM_NS_END
