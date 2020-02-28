///////////////////////////////////////////////////////////////////////////////
// File: main.cpp
// Date: 15.10.2019
// Revision: 1.1
// Author: Christian Steinbrecher
// Description: Takes a file and puts it into a c++ header-file
///////////////////////////////////////////////////////////////////////////////

#include "File.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;

int main(int const argc, char const ** argv)
{
	if (argc <= 1)
	{
		cout << "Usage: [Filename]" << endl;
		return 1;
	}

	try {
		auto const file = readFile(argv[1]);
		
		string filename = argv[1];
		filename[(filename.find('.'))] = '_';	// replace point

		ofstream out(filename + ".h");

		auto const pos = filename.find_last_of('/');
		auto const name = filename.substr(pos+1);


		if (!out.is_open()) {
			throw std::runtime_error("failed to create file!");
		}

		// calculate time
		auto const now = std::chrono::system_clock::now();
		std::time_t const now_time = std::chrono::system_clock::to_time_t(now);

		out << "///////////////////////////////////////////////////////////////////////////////" << endl;
		out << "// File: " << name + ".h" << endl;
		std::time_t result = std::time(nullptr);
		char str[128];
		ctime_s(str, sizeof(str), &result);
		out << "// Date: " << str;
		out << "// Author: FileToHeader" << endl;
		out << "// Description: Autogenerated header including the file " << name << endl;
		out << "///////////////////////////////////////////////////////////////////////////////" << endl;
		out << endl;
		out << "#pragma once" << endl;
		out << endl;
		out << "#include<vector>" << endl;
		out << endl;
		out << "std::vector<char> const " << name << " = { " << endl;

		size_t i = 0;
		while(i < file.size())
		{
			//out << "  ";
			for (size_t j = 0; j < 16 && i < file.size(); ++j)
			{
				out << setw(4) << static_cast<int>(file[i]) ;
				if (i != file.size() - 1)
				{
					out << ",";
				}

				++i;
			}

			//out << " //";

			//for (size_t j = 0; j < 16 && i < file.size(); ++j)
			//{
			//	out << " " << file[i];

			//	++i;
			//}

			out << endl;
		}

		out << "};" << endl;

		out.close();
	}
	catch (exception const& e)
	{
		cout << "Exception: " << e.what() << endl;
		return 1;
	}

	return 0;
}