#ifndef CONFIGURATIONFILE_H
#define CONFIGURATIONFILE_H

#include "Platform.h"
#include <vector>
#include <iostream>
#include "Strings.h"
using namespace std;

namespace pE{

	class ConfigurationFile;

	/**
		\class ConfigurationFileCategory class.
		\brief Internal class used by ConfigurationFile class.

		Not meant to be used individualy.
	*/
	class PARABOLA_API ConfigurationFileCategory{
	public:

		/**
			\brief Constructs the category

			@param Category The name of this category
		*/
		ConfigurationFileCategory(String Category);

		/**
			\brief Inserts a new language item in this category
			
			@param Identifier The setting token
			@param Content The setting content String

		*/
		void Insert(String Identifier, String Content);

		/**
			\brief Removes the setting from the category

			@param Identifier The setting token
		*/
		void Remove(String Identifier);


	private:
		vector<pair<String, String> > Configs;
		String CategoryName;

		friend class ConfigurationFile;
	};


	/**
		\class ConfigurationFile class.
		\brief A class to handle configuration files in the style of the popular .ini files.

		This class is very simple to use, you can think of it as a recipe you can edit.
		You insert/remove configurations and categories and you have the "recipe".

		After you have a recipe, you can write it to a file using SaveToFile function.
		Using the same recipe, you can read it back from a file using LoadFromFile function.

		Notice: In case of doubt, remember you cannot load a configuration file without this recipe ready.

		To construct one recipe you could do something like this:
		\code
			ConfigurationFile myIni;
			myIni.InsertCategory("myCategory");
			myIni.InsertConfig("mySetting", "myDefaultValue", "myCategory");
		\endcode
		
		Then, you could save this configuration as i said previously and then read it back in.

		
		Now, to save you from the hassle of having that code hanging loose, i suggest the following method for a clean solution.
		You would inherit ConfigurationFile and set its "recipe" in the constructor, just like i do in ParabolaConfig for Parabola.ini.
		\code
			ParabolaConfig::ParabolaConfig() : ConfigurationFile()
			{
				InsertCategory("Engine");
				InsertCategory("Perception");

				InsertConfig("EngineKeys", "true", "Engine");

				InsertConfig("Title", "Title", "Perception");

				//...
			};
		\endcode

		Like that, its really easy to load and save your configurations.

		See the functions documentation for more information.
	*/
	class PARABOLA_API ConfigurationFile{
	public:
		/**
			\brief Constructs the default ConfigurationFile.

			Should be called from the inherited classes, but not essential.
		*/
		ConfigurationFile();

		/**
			\brief Saves the configuration to File

			This function saves the current configurations and categories into File in a proper structure.
			Empty categories are not saved.

			@param File The name of the target file. Created if not exists.

			\return False if something failed when saving.
		*/
		bool SaveToFile(String File);

		/**
			\brief Loads configurations from File to memory.

			This function will load the configurations from the file and store them in the structure for further use.
			
			The settings of the configuration will only be read for the settings that exist in the structure.

			@param File The name of the target file.
			\return False if something failed when loading.
		*/
		bool LoadFromFile(String File);

		/**
			\brief Inserts a new category in the ConfigurationFile.

			Simply, a new empty category is created, so that more settings can be stored on it later.

			@param Category Name of the wanted Category.
		*/
		void InsertCategory(String Category);

		/**
			\brief Removes the Category from the structures. 

			The configurations under the removed category won't be erased.
			In practic use, due to the nature of this class, this function is not supposed to be used, at least in common cases.

			@param Category Name of the Category to be removed.
		*/
		void RemoveCategory(String Category);

		/**
			\brief Gets a ConfigurationFile setting as a boolean ( true or false )

			@param Category The category the token lies within.
			@param Identifier The token of the setting
			\return True or False accordingly to the content of the config.
		*/
		bool GetBoolean(String Category, String Identifier);

		/**
			\brief Gets a ConfigurationFile setting as a String ( equal as in the file )

			@param Category The category the token lies within.
			@param Identifier The token of the setting
			\return Content of the token as a String.
		*/
		String GetString(String Category, String Identifier);

		/**
			\brief Gets a ConfigurationFile setting as an integer

			@param Category The category the token lies within.
			@param Identifier The token of the setting
			\return Content of the token as an integer.
		*/
		int GetInteger(String Category, String Identifier);

		/**
			\brief Gets a ConfigurationFile setting as a float

			@param Category The category the token lies within.
			@param Identifier The token of the setting
			\return Content of the token as a floating-point number.
		*/
		double GetFloat(String Category, String Identifier);

		/**
			\brief Inserts/Changes a new setting to the configuration file.

			If the setting doesn't exist, it is created, else , the content is changed.

			@param Identifier Token of the setting to insert/change.
			@param Content The new content of the setting
			@param Category Category to insert/change the setting under.
		*/
		void InsertConfig(String Identifier, String Content, String Category = "Default");

		/**
			\brief Removes a setting from the ConfigurationFile

			@param Identifier Token of the setting to remove.
			@param Category Category where the token to erase is.
		*/
		void RemoveConfig(String Identifier, String Category = "Default");

	protected:
		vector<ConfigurationFileCategory> Categories;
	};

	/**
		\class ParabolaConfig class
		\brief Parabola.ini ConfigurationFile.

		This class handles the configuration file for ParabolaEngine.

		It has the categories and items in Parabola.ini.
	*/
	class ParabolaConfig: public ConfigurationFile{
	public:
		/**
			\brief Constructs ParabolaConfig with the engine settings.
		*/
		ParabolaConfig();
	};

};

#endif
