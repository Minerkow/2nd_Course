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
        NumberN_t(lexer::Lexem_t* num) : num_{dynamic_cast<lexer::Number_t*>(num)} {}
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
        OperationN_t(lexer::Lexem_t* op) : op_{dynamic_cast<lexer::Operation_t*>(op)} {}
    private:
        lexer::Operation_t* op_;
    };

    class ComparisonN_t: public Node_t {
    public:
        ComparisonN_t(lexer::Lexem_t* cs) : cs_{dynamic_cast<lexer::ComparSign_t*>(cs)} {}
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
        Node_t* Insert_Comparison(size_t& index);
        Node_t* Insert_Expression(size_t& index);
        Node_t* Insert_Multiplication(size_t& index);
        Node_t* Insert_Term(size_t& index); 

    private:
        Node_t* top_;
        lexer::LexArray_t lexArray_;
    };

}