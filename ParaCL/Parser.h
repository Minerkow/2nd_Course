#pragma once

#include "Lexer.h"

namespace parser {
    class Node_t {
    public:
        Node_t* left_;
        Node_t* right_;
    };

    class SentenceN_t : public Node_t {
    public:
        SentenceN_t(size_t sNum) : sentNum_(sNum) {}
    private:
        size_t sentNum_;
    };

    class CommandN_t : public Node_t {
    public:
        CommandN_t(lexer::Lexem_t* command) : comm_{dynamic_cast<lexer::Command_t*>(command)} {}
    private:
        lexer::Command_t* comm_;
    };

    class NumberN_t : public Node_t {
    public:
    private:
        lexer::Number_t* num_;
    };

    class Variable_t : public Node_t {
    public:
    private:
        lexer::Variable_t* var_;
    };

    class OperationN_t : public Node_t {
    public:
    private:
        lexer::Operation_t* op_;
    };

    class ComparisonN_t: public Node_t {
    public:
    private:
        lexer::ComparSign_t* cs_;
    };

//--------------------------------------------------------------------------------------------------------------------

    class Parser_t {
    public:
        explicit Parser_t(lexer::LexArray_t& lexArray);

        void Run(); //TODO::

    private:
        Node_t* Insert_Sentence(size_t& index);
        Node_t* Insert_Command(size_t& index);
        Node_t* Insert_Comparison(size_t& index); //TODO::
    private:
        Node_t* top_;
        lexer::LexArray_t lexArray_;
    };

}