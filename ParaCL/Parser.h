#pragma once

#include "Lexer.h"

namespace parser {
    class Node_t {
    public:
        virtual void Print (std::ostream& os) = 0;
        virtual ~Node_t() = default;
    public:
        Node_t* left_{};
        Node_t* right_{};
    };

    class SentenceN_t final: public Node_t {
    public:
        SentenceN_t(size_t sNum) : sentNum_(sNum) {}
        void Print (std::ostream& os) override;

        ~SentenceN_t() override {}
    private:
        size_t sentNum_;
    };

    class CommandN_t final : public Node_t {
    public:
        CommandN_t(lexer::Lexem_t* command) : comm_{static_cast<lexer::Command_t*>(command)} {}
        void Print (std::ostream& os) override {comm_->Print(os);}

        ~CommandN_t() override {comm_ = nullptr;}
    private:
        lexer::Command_t* comm_;
    };

    class NumberN_t final : public Node_t {
    public:
        NumberN_t(lexer::Lexem_t* num) : num_{static_cast<lexer::Number_t*>(num)} {}
        void Print (std::ostream& os) override {num_->Print(os);}

        ~NumberN_t() override {num_ = nullptr;}
    private:
        lexer::Number_t* num_;
    };

    class VariableN_t final : public Node_t {
    public:
        VariableN_t (lexer::Lexem_t* var) : var_(static_cast<lexer::Variable_t*>(var)) {}
        void Print (std::ostream& os) override {var_->Print(os);}

        ~VariableN_t() override {var_ = nullptr;}
    private:
        lexer::Variable_t* var_;
    };

    class OperationN_t final : public Node_t {
    public:
        OperationN_t(lexer::Lexem_t* op) : op_{static_cast<lexer::Operation_t*>(op)} {}
        void Print (std::ostream& os) override {op_->Print(os);}

        ~OperationN_t() override {op_ = nullptr;}
    private:
        lexer::Operation_t* op_;
    };

    class ComparisonN_t final : public Node_t {
    public:
        ComparisonN_t(lexer::Lexem_t* cs) : cs_{static_cast<lexer::ComparSign_t*>(cs)} {}
        void Print (std::ostream& os) override { cs_->Print(os);}

        ~ComparisonN_t() override {cs_ = nullptr;}
    private:
        lexer::ComparSign_t* cs_;
    };

//--------------------------------------------------------------------------------------------------------------------

    class Parser_t {
    public:
        Parser_t(std::string& code);

        void Print_Syntax_Tree(std::ostream& os, Node_t* top);
        void Print_Syntax_Tree(std::ostream& os) {Print_Syntax_Tree(os, top_);}

        void Run(); //TODO::

        ~Parser_t();
    private:
        Node_t* Insert_Sentence(size_t& index);
        Node_t* Insert_Command(size_t& index);
        Node_t* Insert_Comparison(size_t& index);
        Node_t* Insert_Expression(size_t& index);
        Node_t* Insert_Multiplication(size_t& index);
        Node_t* Insert_Term(size_t& index);

        void Delete_Node(Node_t* node);

    private:
        Node_t* top_;
        lexer::LexArray_t lexArray_;
    };

}