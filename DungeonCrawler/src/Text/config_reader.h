#ifndef RETRO3D_CONFIGREADER_H
#define RETRO3D_CONFIGREADER_H

/*=============================================================================================
Config reader class.

Used for reading config files.
Config files can contain sections, and variables.

Example: (from GameConfig.ini)
[camera]
fov:90

Usage: Call ReadFile(filepath), and then access the variables by calling GetString/GetInt/GetFloat.
You may leave the section empty.

==============================================================================================*/

#include <string>
#include <unordered_map>

namespace Retro3D
{
	class ConfigReader
	{
	private:
		/** All variables, ordered by section. */
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>> mSectionVarMap;
	
	public:
		/** Loads the config file at the specified location. */
		bool ReadFile(const char* arg_filepath);

		/** Gets all variables in the specified section. */
		std::unordered_map<std::string, std::string> GetSectionAsMap(const char* arg_section);

		/**
		* Gets the string value of the specified variable
		* @param  arg_section  The section of the variables. 
		* @param  arg_variables  The name of the variable.
		* @return The string value of the variales.
		*/
		bool GetString(const char* arg_section, const char* arg_variable, std::string& out_value) const;
		
		/**
		* Gets the int value of the specified variable
		* @param  arg_section  The section of the variables.
		* @param  arg_variables  The name of the variable.
		* @return The int value of the variales.
		*/
		bool GetInt(const char* arg_section, const char* arg_variable, int& out_value) const;
		
		/**
		* Gets the float value of the specified variable
		* @param  arg_section  The section of the variables.
		* @param  arg_variables  The name of the variable.
		* @return The float value of the variales.
		*/
		bool GetFloat(const char* arg_section, const char* arg_variable, float& out_value) const;


		// std::string versions (used by ChaiScript)
		bool GetString_string(const std::string& arg_section, const std::string& arg_variable, std::string& out_value) const { return GetString(arg_section.c_str(), arg_variable.c_str(), out_value); }
		bool GetInt_string(const std::string& arg_section, const std::string& arg_variable, int& out_value) const { return GetInt(arg_section.c_str(), arg_variable.c_str(), out_value); }
		bool GetFloat_string(const std::string& arg_section, const std::string& arg_variable, float& out_value) const { return GetFloat(arg_section.c_str(), arg_variable.c_str(), out_value); }

	};
}

#endif

