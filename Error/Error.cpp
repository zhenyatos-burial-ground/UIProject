#include "Error.h"

Error::Error(int code, std::string message)
	: code(code), message(message)
{}

Error::Error(const Error& other)
	: code(other.code), message(other.message)
{}

Error& Error::operator=(const Error& other)
{
	code = other.code;
	message = other.message;
	return *this;
}

Error::operator bool() const
{
	return code != 0;
}

std::ostream& operator<<(std::ostream& stream, const Error& error) 
{
	if (!error)
		stream << "OK";
	else
		stream << "ERROR " << error.code << ": " << error.message;
	return stream;
}