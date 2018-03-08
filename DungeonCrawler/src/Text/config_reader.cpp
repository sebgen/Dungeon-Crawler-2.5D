#include "config_reader.h"

#include <fstream>
#include <sstream>
#include "Misc/st_assert.h"
#include "string_helper.h"

namespace Retro3D
{
	ConfigReader::ConfigReader()
	{
		mFilePath = "";
	}

	bool ConfigReader::ReadFile(std::string arg_filepath, bool arg_create)
	{
		std::ifstream configFile(arg_filepath);
		if (!configFile.is_open())
		{
			if (arg_create)
			{
				std::ofstream outFile(arg_filepath);
				outFile.close();
				configFile = std::ifstream(arg_filepath);
				if (!configFile.is_open())
					return false;
			}
			else
			{
				return false;
			}
		}

		mSectionVarMap.clear();

		mFilePath = arg_filepath;

		/**
		* Parse config file.
		*/
		std::string currLine;
		std::string currSection;
		while (std::getline(configFile, currLine))
		{
			const char* cstrPtr = currLine.c_str();
			const size_t& len = currLine.size();
			size_t iLeft = 0;
			size_t iRight = 0;
			bool isSection = false;
			bool isVariableAssignment = false;
			std::string currVarName;
			while (iRight < len)
			{
				const char* currChar = cstrPtr + iRight;
				if (isSection)
				{
					if (*currChar == ']')
					{
						currSection = currLine.substr(iLeft, iRight - iLeft);
						break;
					}
				}
				else
				{
					if (*currChar == '[')
					{
						isSection = true;
						iLeft = iRight + 1;
					}
					if (*currChar == ':')
					{
						isVariableAssignment = true;
						currVarName = currLine.substr(iLeft, iRight - iLeft);
						iLeft = iRight + 1;
					}
					if (*currChar == '\n' || *currChar == '\r') // TODO: don't use std::getline()
					{
						break;
					}
				}

				iRight++;
			}
			iRight--; // TODO: if end of line, iRight will need to be incremented

			if (isVariableAssignment && iLeft < iRight)
			{
				std::string varValue = currLine.substr(iLeft, 1 + iRight - iLeft);
				mSectionVarMap[currSection][currVarName] = varValue;
			}
		}
		configFile.close();
		return true;
	}

	std::unordered_map<std::string, std::string> ConfigReader::GetSectionAsMap(const char* arg_section)
	{
		auto sectionIter = mSectionVarMap.find(arg_section);
		if (sectionIter != mSectionVarMap.end())
			return (*sectionIter).second;
		else
			return std::unordered_map<std::string, std::string>();
	}

	bool ConfigReader::GetString(const std::string& arg_section, const std::string& arg_variable, std::string& out_value) const
	{
		auto sectionIter = mSectionVarMap.find(arg_section);
		if (sectionIter != mSectionVarMap.end())
		{
			auto varIter = (*sectionIter).second.find(arg_variable);
			if (varIter != (*sectionIter).second.end())
			{
				out_value = (*varIter).second;
				return true;
			}
		}
		return false;
	}

	bool ConfigReader::GetInt(const std::string& arg_section, const std::string& arg_variable, int& out_value) const
	{
		auto sectionIter = mSectionVarMap.find(arg_section);
		if (sectionIter != mSectionVarMap.end())
		{
			auto varIter = (*sectionIter).second.find(arg_variable);
			if (varIter != (*sectionIter).second.end())
			{
				const std::string& varStr = (*varIter).second;
				return StringHelper::ToInt(varStr.c_str(), out_value);
			}
		}
		return false;
	}

	bool ConfigReader::GetFloat(const std::string& arg_section, const std::string& arg_variable, float& out_value) const
	{
		auto sectionIter = mSectionVarMap.find(arg_section);
		if (sectionIter != mSectionVarMap.end())
		{
			auto varIter = (*sectionIter).second.find(arg_variable);
			if (varIter != (*sectionIter).second.end())
			{
				const std::string& varStr = (*varIter).second;
				return StringHelper::ToFloat(varStr.c_str(), out_value);
			}
		}
		return false;
	}

	void ConfigReader::SetString(const std::string& arg_section, const std::string& arg_variable, const std::string& arg_value)
	{
		auto sectionIter = mSectionVarMap.find(arg_section);
		if (sectionIter == mSectionVarMap.end())
		{
			mSectionVarMap[arg_section] = std::unordered_map<std::string, std::string>();
		}
		std::unordered_map<std::string, std::string>& varMap = mSectionVarMap[arg_section];
		varMap[arg_variable] = arg_value;
	}

	void ConfigReader::SetFloat(const std::string& arg_section, const std::string& arg_variable, const float arg_value)
	{
		SetString(arg_section, arg_variable, std::to_string(arg_value));
	}

	void ConfigReader::SetInt(const std::string& arg_section, const std::string& arg_variable, const int arg_value)
	{
		SetString(arg_section, arg_variable, std::to_string(arg_value));
	}

	void ConfigReader::Save()
	{
		std::ofstream outFile(mFilePath);
		if (!outFile.is_open())
		{
			LOG_ERROR() << "Failed to create file: " << mFilePath;
			return;
		}

		for (const auto& sectionPair : mSectionVarMap)
		{
			const std::string& sectionName = sectionPair.first;
			const std::unordered_map<std::string, std::string>& sectionMap = sectionPair.second;

			outFile << "[" << sectionName.c_str() << "]" << "\n";

			for (const auto& varPair : sectionMap)
			{
				const std::string& varName = varPair.first;
				const std::string& varValue = varPair.second;

				outFile << varName.c_str() << ":" << varValue << "\n";
			}
		}

		outFile.close();
	}

	void ConfigReader::SaveToFile(std::string arg_filepath)
	{
		mFilePath = arg_filepath;
		Save();
	}

}
