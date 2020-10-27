#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"

int main(int argc, char** argv) {
    std::ifstream file;
    //file.open("/home/bibi/Desktop/Programm/Semestr_2_C++/2nd_Course/ParaCL/Test/FileTests/test4.cl");
    file.open(argv[1]);
    std::string code, line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            code += line + '\n';
        }
    }
    //std::cout << code;
    parser::Parser_t pars{code};
    pars.Run();
}
