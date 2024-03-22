// MuseumVisitors.cpp : Defines the entry point for the application.
//

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Logger.hxx"
#include "VisitorCounterArray.hxx"
#include "VisitorCounterMap.hxx"


using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		// Using VisitorCounterArray
		{ 
			auto started = chrono::high_resolution_clock::now();
			Logger::getLogger()->setLogLevel(LogLevel::TRACE);
			Logger::getLogger()->log(LogLevel::TRACE, __FILE__, __LINE__, "BEGIN:MuseumVisitors::main");
			if (argc < 2)
			{
				string errorMsg = "Visitor Entry Log Filepath missing in command line arguments";
				throw errorMsg;
			}
			string visitorsFilePath = argv[1];
			unique_ptr<VisitorCounterArray> museumVisitorTracker(new VisitorCounterArray(visitorsFilePath));
			string output = museumVisitorTracker->getTimeSlotWithMaxVistors();
			cout << "**** The museum has maximum visitors between *** " << output << endl;

			auto done = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::nanoseconds>(done - started);
			stringstream ss;
			ss << "END:MuseumVisitors::main:Time taken in nanoseconds:" << duration.count();
			string logMsg = ss.str();
			Logger::getLogger()->log(LogLevel::TRACE, __FILE__, __LINE__, logMsg);
		}
		// Using VisitorCounterMap
		{ 
			auto started = chrono::high_resolution_clock::now();
			Logger::getLogger()->setLogLevel(LogLevel::TRACE);
			Logger::getLogger()->log(LogLevel::TRACE, __FILE__, __LINE__, "BEGIN:MuseumVisitors::main");
			if (argc < 2)
			{
				string errorMsg = "Visitor Entry Log Filepath missing in command line arguments";
				throw errorMsg;
			}
			string visitorsFilePath = argv[1];
			unique_ptr<VisitorCounterMap> museumVisitorTracker(new VisitorCounterMap(visitorsFilePath));
			string output = museumVisitorTracker->getTimeSlotWithMaxVistors();
			cout << "**** The museum has maximum visitors between *** " << output << endl;

			auto done = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::nanoseconds>(done - started);
			stringstream ss;
			ss << "END:MuseumVisitors::main:Time taken in nanoseconds:" << duration.count();
			string logMsg = ss.str();
			Logger::getLogger()->log(LogLevel::TRACE, __FILE__, __LINE__, logMsg);
		}
 	}
	catch (string error)
	{
		cout << "Caught: " << error << endl;
	}
	
	return 0;
}
