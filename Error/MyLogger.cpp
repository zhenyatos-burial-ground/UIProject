#include "ILogger.h"
#include <set>
#include <string>
#include <fstream>

namespace {
	class MyLogger;

	MyLogger* logger = nullptr;

	class MyLogger : public ILogger
	{
	private:
		std::set<void*> clients;
		std::string fileName = "log.txt";
		std::ofstream out;

		MyLogger() = default;

	protected:
		void writeCode(RESULT_CODE rc)
		{
			switch (rc)
			{
			case RESULT_CODE::BAD_REFERENCE:
				out << " BAD_REFERENCE\n";
				break;
			case RESULT_CODE::CALCULATION_ERROR:
				out << " CALCULATION_ERROR\n";
				break;
			case RESULT_CODE::DIVISION_BY_ZERO:
				out << " DIVISION_BY_ZERO\n";
				break;
			case RESULT_CODE::FILE_ERROR:
				out << " FILE_ERROR\n";
				break;
			case RESULT_CODE::MULTIPLE_DEFINITION:
				out << " MULTIPLE_DEFINITION\n";
				break;
			case RESULT_CODE::NAN_VALUE:
				out << " NAN_VALUE\n";
				break;
			case RESULT_CODE::NOT_FOUND:
				out << " NOT_FOUND\n";
				break;
			case RESULT_CODE::OUT_OF_BOUNDS:
				out << " OUT_OF_BOUNDS\n";
				break;
			case RESULT_CODE::OUT_OF_MEMORY:
				out << " OUT_OF_MEMORY\n";
				break;
			case RESULT_CODE::SUCCESS:
				out << "\n";
				break;
			case RESULT_CODE::WRONG_ARGUMENT:
				out << " WRONG_ARGUMENT\n";
				break;
			case RESULT_CODE::WRONG_DIM:
				out << " WRONG_DIM\n";
				break;
			}
		}

	public:
		static MyLogger* createLogger(void* pClient)
		{
			if (logger == nullptr)
				logger = new MyLogger();

			if (pClient != nullptr)
				logger->clients.insert(pClient);

			return logger;
		}

		void destroyLogger(void* pClient) override
		{
			if (pClient != nullptr)
				clients.erase(clients.find(pClient));

			if (clients.empty())
			{
				delete logger;
				logger = nullptr;
			}
		}

		void log(char const* pMsg, RESULT_CODE err) override
		{
			if (pMsg != nullptr)
			{
				if (!out.is_open())
				{
					out.open(fileName, std::ofstream::out);
					if (!out.is_open())
						return;
				}
				out << pMsg << "\n";
			}
		}

		RESULT_CODE setLogFile(char const* pLogFile) override
		{
			if (pLogFile == nullptr)
				return RESULT_CODE::BAD_REFERENCE;

			if (out.is_open())
				return RESULT_CODE::MULTIPLE_DEFINITION;

			out.open(pLogFile, std::ofstream::out);

			if (!out.is_open())
				return RESULT_CODE::FILE_ERROR;

			return RESULT_CODE::SUCCESS;
		}

		~MyLogger()
		{
			if (out.is_open())
				out.close();
		}
	};
}


ILogger* ILogger::createLogger(void* pClient)
{
	return MyLogger::createLogger(pClient);
}


ILogger::~ILogger()
{}