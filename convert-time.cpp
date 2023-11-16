/**************************************************************
 * convert-time
 * 
 * Takes a comma-separated value file output by find_tags_unifile from the
 * sensorgnome project and replaces the Unix time in seconds with 
 * human-readable ascii time.
 * 
 * The output should be redirected to a file if it needs to be saved.
 * 
 * Usage: $convert-time <comma_separated_output_from_find_tags_unifile>
***************************************************************/

#include <iostream>
#include <assert.h>
#include <fstream>
#include <ctime>

std::fstream infile; // The stream that we use to open the file

int main(int argc, char *argv[]) {
    std::string str_line; //The parsed out Unix time
    std::string header_string; //The header, taken off the top
    
    //string is converted to time in seconds 
    //(rounding off fraction of seconds because not needed for this application)
    long int time_seconds; 

    // open input csv
    infile.open(argv[1]); // Opens file stream from existing file

    std::getline(infile, header_string); //Take header off
    std::cout << header_string << "\n"; //Output header

    //Now that the header has been taken care of go through each line to parse out Unix time
    for (std::string line; std::getline(infile, line);){

        //Add section for parsing comma-separated line for time field.
        std::size_t firstComma = line.find_first_of(','); //Find first comma
        std::size_t secondComma = line.find_first_of(',', firstComma + 1); //Find second comma
        str_line = line.substr(firstComma + 1, secondComma - firstComma - 1); //String between is our Unix time in seconds since 1970-01-01

        //std::cout << str_line << "\n";

        // convert time
        time_seconds = std::stoi(str_line); //Convert the string to an integer (even though it is a double)

        std::time_t time_object(time_seconds); //Convert to object of type time_t for localtime()

        std::tm *tm_ptr = std::localtime(&time_object); //pointer to tm object
        std::string ascii_time = std::asctime(tm_ptr); // Converts to human-readable date

        //asctime() appends a newline apparently so remove it
        if (!ascii_time.empty() && ascii_time[ascii_time.length() - 1] == '\n')
        {
            ascii_time.erase(ascii_time.length() - 1);
        }

        //Replace UNix time with converted time in the comma-separated line
        line.replace(firstComma + 1, str_line.length(), ascii_time); // This should do the trick

        //Output line
        std::cout << line << "\n";
        }
    return (0);
}