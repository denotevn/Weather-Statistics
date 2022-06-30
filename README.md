## Weather - Statistics
## Problem 

> You get data sets for 4 years 2012, 2013, 2014, 2015. Within each dataset is information about date, time, air temperature, barometric pressure, dew point, relative humidity, direction wind, ....

## Soltion 
1. Load data and use std::map<time_t, double> to store time and data of atmospheric pressure
2. Look for the lowest barometric pressure during the beginning and the end. Then calculate the time difference and barometric pressure difference. Calculate the coefficient according to the algorithm you want. Here I want to determine the weather depends on the atmospheric pressure. It's all in the computeCoeff function.
3. If the calculated coefficient is greater than 0, it is sunny. Less than zero, it might rain. Output information to the screen
4. ***Idea:*** You can choose to add more components to calculate your coefficients.


### How to istallation and test:
1. clone the repository
2. Any C++ compiler Eg. clang or use an online IDE like replit
3. Build using the build command pertaining to the said compiler. Eg. clang: "clang++ -std=c++17 *.cpp -o WeatherStatistics
and then Run ./WeatherStatistics"

**Input test data**
>   For the date: yyyy_mm_dd
>   for the time: hh:mm:ss

### Necessary knowledge
1. Read data from multiple files in C++
2. String processing in C++, converting strings to numbers
3. Basic time handling in C++