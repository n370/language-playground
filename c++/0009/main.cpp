#include <iostream>
#include <fstream>
#include <string>

int main()
{
    const char* filename = "input.txt";

    std::string line;

    std::ofstream writable (filename, std::ios::app);

    if (writable.is_open())
    {
        writable << "\nI am adding a line.\n";
        writable << "I am adding another line\n";
        writable.close();
    }
    else
    {
        std::cout << "Unable to open file for writing";
    }

    std::ifstream readable (filename);

    if (readable.is_open())
    {
        while ( std::getline(readable, line) )
        {
            std::cout << line << "\n";
        }
        readable.close();
    }
    else
    {
        std::cout << "Unable to open file for reading";
    }

    return 0;
}
