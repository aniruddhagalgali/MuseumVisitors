#pragma once

#include <chrono>
#include <regex>
#include <vector>

using namespace std;

/**
* Analyzes visitor traffic using primitive arrays.\n
* After constructing the VisitorCounterMap, invoke the getTimeSlotWithMaxVistors() method to get the analysis
*/
class VisitorCounterArray
{
private:
	static const char inOutTimeDelimiter = ',';
	static const char hhMMDelim = ':';
	int visitorsInMinute[1440] = { 0 };
	void analyzeLogLine(const string& vistorEntryLogLine);
public:
	/**
	* Creates a VisitorCounterArray
	*
	* @param[in] entryLogFilePath Path to the log file to be analyzed .\n
	* The log file should have list of entry logs in the form  HH:MM,HH:MM
	*
	* @throw std::string ErrorMessage if file cannot be opened or format does not match
	*/
	VisitorCounterArray(const string& entryLogFilePath);

	/**
	* Returns the time slot which had maximum visitors in the format \n
	* **HH:MM-HH:MM;n** \n
	* First HH:MM is the start time\n
	* Second HH:MM is the end time\n
	* n is the number of visitors in that time
	*/
	string getTimeSlotWithMaxVistors();
};