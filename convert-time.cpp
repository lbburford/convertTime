#include <iostream>
#include <assert.h>
#include <fstream>
#include <ctime>

std::fstream infile; // The stream that we use to open the file

int main(int argc, char *argv[]) {
    std::string str_line;
    std::string time_string;
    std::string header_string;

    long int time_seconds;

    // open input csv
    infile.open(argv[1]); // Opens file stream from existing file

    std::getline(infile, header_string);
    std::cout << header_string;

    //get line
    for (std::string line; std::getline(infile, line);){

        /****************
         * Add section for parsing comma-separated line for time field.
         * 
        *****************/

        // convert time
        time_seconds = std::stoi(str_line); //Convert the string to an integer (even though it is a double)

        std::time_t time_object(time_seconds); //Convert to object of type time_t for localtime()

        std::tm *tm_ptr = std::localtime(&time_object); //pointer to tm object
        std::string ascii_time = std::asctime(tm_ptr); // Converts to human-readable date
    
        // write to file or console new converted time in the comma-separated line
        std::cout << "Timestamp: " << ascii_time << "\n";
    
    }
    return (0);
}