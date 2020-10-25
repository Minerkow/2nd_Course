#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <cmath>

namespace lexer {
    class Number_t;
    class Operation_t;
    class ComparSign_t;
    class Brace_t;
    class Command_t;

    class Lexem_t {
    public:
        enum KindLexem_t { POISON, NUMBER, OPERATION,
                           COMPAR_SIGN, BRACE, COMMAND,
                           VARIABLE};

        Lexem_t(size_t line, KindLexem_t kindLex) : line_(line),
                                                     kindLexem_(kindLex){}
        size_t Line() const {return line_;}
        KindLexem_t KindLexem() {return kindLexem_;}

        virtual std::ostream& Print(std::ostream& os) = 0;

    protected:
        size_t line_;
        KindLexem_t kindLexem_;
    };

    class Lexer_t {
    public:
        Lexer_t(const std::string& code);

        friend std::ostream& operator<<(std::ostream& os, Lexer_t& lexer);

        ~Lexer_t();
    private:
        std::vector<Lexem_t*> lexArray_;
        //std::unordered_map<std::string, int> variables_;
    };

    class Number_t : public Lexem_t {
    public:
        Number_t( size_t line, int number) : number_{number}, Lexem_t{line, NUMBER}{}

        operator Lexem_t*() {return dynamic_cast<Lexem_t*>(this);}
        std::ostream& Print(std::ostream& os) override;
    private:
        int number_;
    };

    class Operation_t : public Lexem_t {
    public:
        enum Kind_t { POISON,ADD, SUB, MUL, DIV};

        Operation_t(size_t line, char sym);

        operator Lexem_t*() {return dynamic_cast<Lexem_t*>(this);}
        std::ostream& Print(std::ostream& os) override;
    private:
        Kind_t kind_;
    };

    class ComparSign_t : public Lexem_t {
    public:
        enum Kind_t { POISON, NOT, EQUAL, NOT_EQUAL, GREATER, LESS, EQ_OR_GR, EQ_OR_LESS};

        ComparSign_t(size_t line, std::string &sign);

        operator Lexem_t*() {return dynamic_cast<Lexem_t*>(this);}
        std::ostream& Print(std::ostream& os) override;
    private:
        Kind_t kind_;
    };

    class Brace_t : public Lexem_t {
    public:
        enum Kind_t { POISON, LBRAC , RBRAC, LFIGURBRAC, RFIGURBRAC};

        Brace_t(size_t line, char sym);

        operator Lexem_t*() {return dynamic_cast<Lexem_t*>(this);}
        std::ostream& Print(std::ostream& os) override;
    private:
        Kind_t kind_;
    };

    class Command_t : public Lexem_t {
    public:
        enum Kind_t { POISON, PRINT, INPUT, ASSIGN, END_COMMAND, IF, WHILE};

        Command_t(size_t line, char sym);
        Command_t(size_t line, std::string& command);

        operator Lexem_t*() {return dynamic_cast<Lexem_t*>(this);}
        std::ostream& Print(std::ostream& os) override;
    private:
        Kind_t kind_;
    };

    class Variable_t : public Lexem_t {
    public:
        Variable_t( size_t line, std::string& name) : name_(name),
                                                  Lexem_t(line, VARIABLE){}
        operator Lexem_t*() {return dynamic_cast<Lexem_t*>(this);}
        std::ostream& Print(std::ostream& os) override;
    private:
        std::string name_;
    };

    bool IsOperation(char sym);
    bool IsComparSign(char sym);
    bool IsBrace(char sym);
    bool IsSpecialCharacters(char sym);
    bool IsCommand(const std::string& word);
}