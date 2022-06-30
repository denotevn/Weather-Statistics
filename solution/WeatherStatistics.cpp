/**
 * WeatherStatistics.cpp by Olivia Stone for Code Clinic: C++
 **/

#include "WeatherStatistics.hpp"

using namespace std;

WeatherStatistics::WeatherStatistics()
{
   loadData();
}

bool WeatherStatistics::isValidDateTime(string date, string time)
{
    time_t dateTime = convertDateTime(date, time);
    
    if (dateTime < 0)
    {
        return false; // failure to parse date/time
    }

    if ((dateTime < getFirstDateTime()) || (dateTime > getLastDateTime()))
    {
        cerr << "ERROR: " << date << " " << time << " is outside available data range" << endl;
        return false;
    }

    return true;
}

double WeatherStatistics::computeCoeff(string startDate, string startTime,
	                                   string endDate, string endTime)
{
    time_t startDateTime = convertDateTime(startDate, startTime);
    time_t endDateTime = convertDateTime(endDate, endTime);

    if (endDateTime < startDateTime)
    {
        cerr << "ERROR: The start date/time must occur before the end date/time" << endl;
        exit(1);
    }

    // find iterators based on input range
    map<time_t, double>::iterator startTimePressure;
    map<time_t, double>::iterator endTimePressure;
    startTimePressure = timeToPressure_.lower_bound(startDateTime);
    endTimePressure = timeToPressure_.lower_bound(endDateTime);

    // Extract time and timeToPressure values
    double timeDiff = endTimePressure->first - startTimePressure->first;
    double pressureDiff = endTimePressure->second - startTimePressure->second;

    // calculate and return slope
    return (pressureDiff) / (timeDiff);
}

void WeatherStatistics::loadData() 
{
    for (int year = 2012; year <= 2015; year++)
    {
        ostringstream fileNameStream;
        fileNameStream << RESOURCE_PATH << "Environmental_Data_Deep_Moor_" << year << ".txt";

        string fileName = fileNameStream.str(); // get/set content (public member function)
        cout << "Loading " << fileName << endl;

        fstream dataFileStream;
        dataFileStream.open(fileName);

        string line;
        getline(dataFileStream, line); // discard top line with headers
        while (getline(dataFileStream, line))
        {
            string date, time;
            double Air_Temp, Barometric_Press, Dew_Point, Relative_Humidity,Wind_Dir, Wind_Gust, Wind_Speed;
            istringstream buffer(line); // dung de convert chuoi sang so theo thu tu casc cot

            buffer >> date >> time >> Air_Temp >> Barometric_Press >> Dew_Point >> Relative_Humidity >> Wind_Dir >> Wind_Gust >> Wind_Speed;
            time_t dateTime = convertDateTime(date, time);
            timeToPressure_[dateTime] = Barometric_Press;
        }

        dataFileStream.close();
    }
}

time_t WeatherStatistics::getFirstDateTime()
{
    return timeToPressure_.begin()->first; 
}

time_t WeatherStatistics::getLastDateTime()
{
    return timeToPressure_.rbegin()->first;
}

time_t WeatherStatistics::convertDateTime(string date, string time)
{
    // parse values from date string
    // work with date
    int yyyy, mon, dd = 0;
    if (sscanf(date.c_str(), "%d_%d_%d", &yyyy, &mon, &dd) != 3) // sscanf if true return number of element
                                                                // in this case return 3 if true
    {
        cerr << "ERROR: Failed to parse date string " << date << endl;
        return -1;
    }

    // parse values from time string
    int hh, mm, ss = 0;
    if (sscanf(time.c_str(), "%d:%d:%d", &hh, &mm, &ss) != 3) 
    {
        cerr << "ERROR: Failed to parse time string " << date << endl;
        return -2;
    }
    
    struct tm dateTime = {};
    dateTime.tm_year = yyyy - 1900; // years since 1900 yyyy
    dateTime.tm_mon = mon - 1;      // months since January
    dateTime.tm_mday = dd;          // day of the month
    dateTime.tm_hour = hh;          // hours since midnight
    dateTime.tm_min = mm;           // minutes after the hour
    dateTime.tm_sec = ss;           // seconds after the minute

    // return a time_t value representing seconds since 1970
    return mktime(&dateTime);
}
/* MKTIME()
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
 
int main()
{
    setenv("TZ", "/usr/share/zoneinfo/America/Los_Angeles", 1); // POSIX-specific
 
    std::tm tm{};  // zero initialise
    tm.tm_year = 2020-1900; // 2020
    tm.tm_mon = 2-1; // February
    tm.tm_mday = 15; // 15th
    tm.tm_hour = 10;
    tm.tm_min = 15;
    tm.tm_isdst = 0; // Not daylight saving
    std::time_t t = std::mktime(&tm); 
    std::tm local = *std::localtime(&t);
 
    std::cout << "local: " << std::put_time(&local, "%c %Z") << '\n';
}
*/

