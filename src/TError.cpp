#include "TError.h"


TError::TError(char* error,
	char* function,
	char* file,
	int line)
{
	err = move(error);
	func = move(function);
	fil = move(file);
	lin = line;
	//std::cout << "\nError: " << er << "Function: " << func << "File: " << fi <<"Line:"<<line<< endl;
}

TError::TError(const char* error, const char* function, const char* file, int line)
{
	err = move(error);
	func = move(function);
	fil = move(file);
	lin = line;
	//td::cout << "\nError: " << err << "Function: " << func << "File: " << fil <<"Line:"<<line<< endl;
}

void TError::what()
{
	std::cout << "\nError: " << err << "Function: " << func << "File: " << fil << "Line:" << lin << std::endl;
}

