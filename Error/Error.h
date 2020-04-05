#include <string>
#include <ostream>

class Error 
{
private:
	int code;
	std::string message;

protected:
	Error(int code, std::string message);

public:
	Error(const Error& other);
	Error& operator=(const Error& other);
	~Error() = default;

	friend std::ostream& operator<<(std::ostream& stream, const Error& error);

	operator bool() const;
};