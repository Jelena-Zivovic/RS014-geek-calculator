#ifndef HELP_FILE_HPP
#define HELP_FILE_HPP

#include <iostream>
#include <fstream>
#include <cstdio>

class Help_File {
public:
    Help_File();

    ~Help_File();

    void write(const std::string& text);

    FILE *get_FILE() const;

private:
    std::ofstream m_file;
    FILE *m_file_star;
    const char* filename = "input.txt";
};

#endif
