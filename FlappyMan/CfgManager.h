#pragma once

#include <stdio.h>
#include <windows.h>
#include <cstring>

namespace cfg

{

	class Config

	{
	
	public :

		Config (const char * filename);

		~Config ();

		std::string getStrSetting (std::string index);
		double      getNumSetting (std::string index);

	private : 

		const char * filename_;

		FILE * file_;

	};

	//---------------------------------------------------

	Config::Config (const char * filename) :

		filename_ (filename),

		file_ (nullptr)

	{
	
		errno_t err = fopen_s (&file_, filename_, "r");

		if (err)

		{
		
			wchar_t message [512] = L"";

			wsprintf (message, L"Config error with opening file:\n"
			                   L"%s", _wcserror (err));

			MessageBox (nullptr, message, L"Gonfig error", MB_ICONERROR | MB_OK);

			abort ();

		}

	}

	//---------------------------------------------------

	Config::~Config ()

	{

		errno_t err = fclose (file_);

		if (err)

		{
		
			wchar_t message [512] = L"";

			wsprintf (message, L"Config error with closing file:\n"
			                   L"%s", _wcserror (err));

			MessageBox (nullptr, message, L"Gonfig error", MB_ICONERROR | MB_OK);

			abort ();

		}

	}

	//---------------------------------------------------

	std::string Config::getStrSetting (std::string index)

	{
	
		std::string str ("");

		const char * c = nullptr;

		char line [512] = "";

		while (fgets (line, 512, file_))

		{
		
			//printf ("Line '%s'", line);

			if ((c = strstr (line, index.c_str ())) != nullptr)

			{
			
				const char * begin = (c + index.length () + 1);

				size_t length = 0;

				for (length; begin [length] != '\n'; length++);

				str.insert (0, begin, length);

				break;

			}

		}

		if (!c)

		{
		
			printf ("Failed to find '%s' in '%s'\n", index.c_str (), filename_);
		
		}

		return str;

	}

	//---------------------------------------------------

	double Config::getNumSetting (std::string index)

	{
	
		std::string str = getStrSetting (index);

		double num = stod (str);

		return num;

	}

}