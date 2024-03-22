#include "Logger.hxx"
#include <fstream>

using namespace std;
shared_ptr<Logger> Logger::loggerInstance;

/*! \fn string getFormattedTimestamp()
	\brief Gets the current time formatted for logging.
*/
string getFormattedTimestamp() {
    auto now = chrono::system_clock::now();
    return format("{0:%F_%T}", now);
}

std::shared_ptr<Logger> Logger::getLogger() {
	if (loggerInstance == nullptr) {
		loggerInstance = std::shared_ptr<Logger>(new Logger());
	}
	return loggerInstance;
}


void Logger::setLogLevel(LogLevel logLevel)
{
	this->logLevel = logLevel;
}

void Logger::log(LogLevel messageLevel, string codeFile, int codeLine, string message) {
	if (messageLevel >= logLevel) {
		string logType;
		//Set Log Level Name
		switch (messageLevel) {
		case LogLevel::TRACE:
			logType = "TRACE: ";
			break;
		case LogLevel::DEBUG:
			logType = "DEBUG: ";
			break;
		case LogLevel::INFO:
			logType = "INFO: ";
			break;
		case LogLevel::WARN:
			logType = "WARN: ";
			break;
		case LogLevel::ERROR:
			logType = "ERROR: ";
			break;
		case LogLevel::CRITICAL:
			logType = "CRITICAL: ";
			break;
		default:
			logType = "NONE: ";
			break;
		}
		codeFile += " : " + to_string(codeLine) + " : ";
		message = getFormattedTimestamp() + ":" + logType + codeFile + message;
		logMessage(message);
	}
}

/**
 * Print the message to cout
 * @param message : string message
 * @return void
 */
void Logger::logMessage(const string& message) {
	cout << message << endl;
}