#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <cmath>

namespace lexer {
    class Lexem_t {
    public:
        Lexem_t(size_t line) : line_(line) {}
        size_t Line() const {return line_;}
    private:
        size_t line_;
    };

    class Lexer_t {
    public:
        Lexer_t(const std::string& code);
    private:
        std::vector<Lexem_t> lexArray_;
        std::unordered_map<std::string, int> variables_;
    };

    class Number_t : public Lexem_t {
    public:
        Number_t( size_t line, int number) : number_{number}, Lexem_t{line}{}
    private:
        int number_;
    };

    class Operation_t : public Lexem_t {
    public:
        enum Kind_t {ADD, SUB, MUL, DIV};

        Operation_t(size_t line, char sym);
    private:
        Kind_t kind_;
    };

    class ComparSign_t : public Lexem_t {
    public:
        enum Kind_t {NOT, EQUAL, NOT_EQUAL, GREATER, LESS, EQ_OR_GR, EQ_OR_LESS};
        ComparSign_t(size_t line, std::string &sign);
    private:
        Kind_t kind_;
    };

    class Brace_t : public Lexem_t {
    public:
        enum Kind_t {LBRAC , RBRAC, LFIGURBRAC, RFIGURBRAC};
        Brace_t(size_t line, char sym);
    private:
        Kind_t kind_;
    };

    class Command_t : public Lexem_t {
    public:
        enum Kind_t {PRINT, INPUT, ASSIGN, END_COMMAND, IF, WHILE};
        Command_t(size_t line, char sym);
        Command_t(size_t line, std::string& command);
    private:
        Kind_t kind_;
    };

    bool IsOperation(char sym);
    bool IsComparSign(char sym);
    bool IsBrace(char sym);
    bool IsSpecialCharacters(char sym);
    bool IsCommand(const std::string& word);
}