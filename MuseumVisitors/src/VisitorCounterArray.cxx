#include "Logger.hxx"
#include "VisitorCounterArray.hxx"

#include <fstream>

using namespace std;

static const regex logEntryRegex("^(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9],(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$");

static string convert_to_HHMM(int totalMinutes) {
	// Handle negative total minutes
	if (totalMinutes < 0) {
		return "Invalid time (negative minutes)";
	}

	int hours = totalMinutes / 60;
	int minutes = totalMinutes % 60;

	// Ensure two-digit format for hours and minutes (using setw)
	stringstream ss;
	ss << setw(2) << setfill('0') << hours << ":" << setw(2) << setfill('0') << minutes;

	return ss.str();
}

void VisitorCounterArray::analyzeLogLine(const string& vistorEntry)
{
	size_t inOutDelimPos = vistorEntry.find(inOutTimeDelimiter);
	string inTime = vistorEntry.substr(0, inOutDelimPos);
	string outTime = vistorEntry.substr(inOutDelimPos + 1);
	string visitorsInAndOutTime;

	// Calculate the in-time in minutes since 00:00
	size_t minuteDelimPos = inTime.find(hhMMDelim);
	string hourIn = inTime.substr(0, minuteDelimPos);
	string minuteIn = inTime.substr(minuteDelimPos + 1);
	int timeIn = stoi(hourIn) * 60 + stoi(minuteIn);

	// Calculate the out-time in minutes since 00:00
	minuteDelimPos = outTime.find(hhMMDelim);
	string hourOut = outTime.substr(0, minuteDelimPos);
	string minuteOut = outTime.substr(minuteDelimPos + 1);
	int timeOut = stoi(hourOut) * 60 + stoi(minuteOut);

	// Increment the count of all the minutes between 
	// in-time and out-time (both inclusive)
	for (int i = timeIn; i <= timeOut; i++)
	{
		visitorsInMinute[i]++;
	}
}


VisitorCounterArray::VisitorCounterArray(const string& entryLogFilePath)
{
	ifstream entryLogFile;
	entryLogFile.open(entryLogFilePath, ios::in);
	if (entryLogFile.is_open())
	{
		string logEntry;
		while (getline(entryLogFile, logEntry))
		{
			if (regex_match(logEntry, logEntryRegex))
			{
				analyzeLogLine(logEntry);
			}
			else
			{
				entryLogFile.close();
				throw logEntry + " does not match HH:MM,HH:MM format";
			}
		}
	}
	else
	{
		throw "Cannot open " + entryLogFilePath;
	}
	entryLogFile.close();
}

string VisitorCounterArray::getTimeSlotWithMaxVistors()
{
	Logger::getLogger()->log(LogLevel::TRACE, __FILE__, __LINE__, "BEGIN:VisitorCounterArray::getTimeSlotWithMaxVistors");
	auto started = chrono::high_resolution_clock::now();

	int maxVisitors = 0;
	int maxVisitorsStartTime = 0;
	int maxVisitorsEndTime = 0;
	for (int i = 0; i < 1440; i++)
	{
		if (visitorsInMinute[i] > maxVisitors)
		{
			maxVisitors = visitorsInMinute[i];
			maxVisitorsStartTime = i;
			maxVisitorsEndTime = i;
		}
		if (visitorsInMinute[i] == maxVisitors)
		{
			maxVisitorsEndTime = i;
		}
	}
	stringstream ssReturnValue;
	ssReturnValue << convert_to_HHMM(maxVisitorsStartTime) << "-" << convert_to_HHMM(maxVisitorsEndTime) << ";" << maxVisitors;
	
	auto done = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(done - started);
	stringstream ss;
	ss << "END:VisitorCounterArray::getTimeSlotWithMaxVistors:Time taken in nanoseconds:" << duration.count();
	string logMsg = ss.str();
	Logger::getLogger()->log(LogLevel::TRACE, __FILE__, __LINE__, logMsg);

	return ssReturnValue.str();
}