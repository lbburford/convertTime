/* Practice working with classes.
This is an attempt to answer exercise 14-4 in Practical C++ Programming 

It gives a shell of a class and asks for the definition of member functions
for handling lines in a file. 

I chose to create an instance of the class though I suppose one could do it with static functions too.

I am not sure that I did this the way it was intended but it seems to work anyway and was somewhat simple*/

#include <iostream>
#include <assert.h>
#include <fstream>

std::fstream infile; //The stream that we use to open the file

/* Class definition:
I added the private members line_position and char_position as well as a constructor that takes a string 
that is the file name. */
class line_number { 
    private:
        int line_position; //the current line
        int char_position; //the number of chars up to the beginning of the line
    public:
        line_number(std::string file_name); //Constructor takes a filename of a text file with multiple lines
        void goto_line(int line); //sets the position of the line in the input file
        int get_current_line(); //returns the current line number of the input file
        long int get_char_pos(); //return character position of line (number of chars before the beginning of the line)
};

line_number::line_number(std::string file_name) {
    infile.open(file_name); //Opens file stream from existing file
    if (infile.fail()) //Tests for failure of opening file
    {
        std::cerr << "Unable to open " << file_name << "\n";
        exit(8);
    }
    char_position = 0; //Init char position
    line_position = 0; //Init line position
}

void line_number::goto_line(int line) {
    std::string str_line;

    assert(line >= 0); //Make sure that we weren't passed a bad number

    /* Loop until the end of the file or the line position is found.
    If the end of the file is reached the line_position remains the last line. */
    while(std::getline(infile, str_line)) { 
        if(line == line_position) //Ends loop if line position has been reached
            return;

        //std::cout << "Line length: " << str_line.length() << "\n";

        /* If line position has not been reached the characters are added to the counter 
        before going on to the next line */
        char_position += str_line.length(); 
        ++line_position; //Before going to the next line of the file, iterate the line position holder
    }
    std::cout << "The end of the file was reached and the line_position was set at " << line_position << "\n";
}

int line_number::get_current_line() {
    return (line_position); //Private member
}

long int line_number::get_char_pos() {
    return (char_position); //Private member
}

int main() {
    line_number ln("input.txt"); //Instantiate an object called ln

    ln.goto_line(55); //Set line

    std::cout << "Current line position: " << ln.get_current_line() << "\n"; //Output current line
    std::cout << "Character position of line: " << ln.get_char_pos() << "\n"; //Output the number of characters before beginning of line

    ln.goto_line(68); // Set line

    std::cout << "Current line position: " << ln.get_current_line() << "\n";  // Output current line
    std::cout << "Character position of line: " << ln.get_char_pos() << "\n"; // Output the number of characters before beginning

    return (0);
}