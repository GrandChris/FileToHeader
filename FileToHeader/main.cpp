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

		if (!out.is_open()) {
			throw std::runtime_error("failed to create file!");
		}

		out << "///////////////////////////////////////////////////////////////////////////////" << endl;
		out << "// File: " << filename + ".h" << endl;
		std::time_t result = std::time(nullptr);
		char str[26];		;
		out << "// Date: " << ctime_s(str, sizeof(str), &result) << endl;
		out << "// Author: FileToHeader" << endl;
		out << "// Description: Autogenerated header including the file " << argv[1] << endl;
		out << "///////////////////////////////////////////////////////////////////////////////" << endl;
		out << endl;
		out << "#include<vector>" << endl;
		out << endl;
		out << "std::vector<char> const " << filename << " = { " << endl;

		size_t i = 0;
		while(i < file.size())
		{
			out << "  ";
			for (size_t j = 0; j < 15 && i < file.size(); ++j)
			{
				out << setw(3) << static_cast<int>(file[i]) ;
				if (i != file.size() - 1)
				{
					out << ", ";
				}

				++i;
			}

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