#include "Parser.h"

namespace parser {

    Parser_t::Parser_t(std::string& code) : lexArray_(code), top_(nullptr) {
        size_t index = 0;
        top_ = Insert_Sentence((index));
    }

    Node_t *Parser_t::Insert_Sentence(size_t &index) {
        Node_t *node = new SentenceN_t{0};
        Node_t *top = node;
        size_t num = 1;
        while (index < lexArray_.Size() - 1 &&
               lexArray_.FigurBrace(index) != lexer::Brace_t::RFIGURBRAC) {
            node->left_ = Insert_Command(index);
            if (!lexArray_.IsEndCommand(index) &&
                lexArray_.FigurBrace(index) != lexer::Brace_t::RFIGURBRAC) {
                std::cerr << "\nExpected '}': line -"
                          << lexArray_[index]->Line() << std::endl;
                exit(EXIT_FAILURE);
            }
            index++;
            node->right_ = new SentenceN_t{num++};
            node = node->right_;
        }
        return top;
    }

    Node_t *Parser_t::Insert_Command(size_t &index) {
        Node_t *node = nullptr;
        Node_t *comm_left = Insert_Comparison(index);
        if (lexArray_.IsEndCommand(index)) {
            return comm_left;
        }
        node = new CommandN_t{lexArray_[index]};
        switch (lexArray_.Command(index)) {
            case lexer::Command_t::PRINT:
                index++;
                node->left_ = Insert_Comparison(index);
                if (node->left_ == nullptr) {
                    std::cerr << "Waiting expresion, line -" << lexArray_[index]->Line();
                    exit(EXIT_FAILURE);
                }
                break;
            case lexer::Command_t::ASSIGN:
                index++;
                node->left_ = comm_left;
                if (node->left_ == nullptr) {
                    std::cerr << "Waiting variable, line -" << lexArray_[index]->Line();
                    exit(EXIT_FAILURE);
                }
                node->right_ = Insert_Comparison(index);
                if (node->right_ == nullptr) {
                    std::cerr << "Waiting expresion, line -" << lexArray_[index]->Line();
                    exit(EXIT_FAILURE);
                }
                break;
            default: //IF or WHILE
                index++;
                node->left_ = Insert_Comparison(index);
                if (lexArray_.FigurBrace(index) != lexer::Brace_t::LFIGURBRAC) {
                    std::cerr << "Waiting figure brace - '{', line -" << lexArray_[index]->Line();
                    exit(EXIT_FAILURE);
                }
                index++;
                if (lexArray_.FigurBrace(index) == lexer::Brace_t::LFIGURBRAC) {
                    std::cerr << "Too many brace - '{', line -" << lexArray_[index]->Line();
                    exit(EXIT_FAILURE);
                }
                node->right_ = Insert_Sentence(index);
                if (lexArray_.FigurBrace(index) != lexer::Brace_t::RFIGURBRAC) {
                    std::cerr << "Waiting figure brace - '}', line -" << lexArray_[index]->Line();
                    exit(EXIT_FAILURE);
                }
        }

        comm_left = node;
        return comm_left;
    }

    Node_t *Parser_t::Insert_Comparison(size_t &index) {
        Node_t *node = nullptr;
        Node_t *comp_left = Insert_Expression(index);
        if (lexArray_.IsEndCommand(index)) {
            return comp_left;
        }
        while (lexArray_.IsComparison(index)) {
            if (lexArray_.IsEndCommand(index)) {
                return comp_left;
            }
            node = new ComparisonN_t{lexArray_[index]};
            if (lexArray_.ComparSign(index) == lexer::ComparSign_t::NOT) {
                index++;
                node->left_ = Insert_Expression(index);
                node->right_ = nullptr;
                comp_left = node;
            } else {
                index++;
                node->left_ = comp_left;
                if (node->left_ == nullptr) {
                    std::cerr << "Waiting expresion , line -" << lexArray_[index]->Line();
                    exit(EXIT_FAILURE);
                }
                node->right_ = Insert_Expression(index);
                if (node->right_ == nullptr) {
                    std::cerr << "Waiting expresion , line -" << lexArray_[index]->Line();
                    exit(EXIT_FAILURE);
                }
                comp_left = node;
            }
        }
        return comp_left;
    }

    Node_t *Parser_t::Insert_Expression(size_t &index) {
        Node_t *node = nullptr;
        Node_t *expr_left = Insert_Multiplication(index);
        if (lexArray_.IsEndCommand(index)) {
            return expr_left;
        }

        while (lexArray_.IsAddSub(index)) {
            if (lexArray_.IsEndCommand(index)) {
                return expr_left;
            }
            node = new OperationN_t{lexArray_[index]};
            index++;
            if (lexArray_[index]->KindLexem() != lexer::Lexem_t::NUMBER &&
                lexArray_[index]->KindLexem() != lexer::Lexem_t::BRACE &&
                lexArray_[index]->KindLexem() != lexer::Lexem_t::VARIABLE) {
                std::cerr << "Expected expression, line -" << lexArray_[index]->Line();
                exit(EXIT_FAILURE);
            }
            node->left_ = expr_left;
            node->right_ = Insert_Multiplication(index);
            expr_left = node;
        }
        return expr_left;
    }

    Node_t *Parser_t::Insert_Multiplication(size_t &index) {
        Node_t *node = nullptr;
        Node_t *mult_left = Insert_Term(index);

        while (lexArray_.IsMulDiv(index)) {
            node = new OperationN_t{lexArray_[index]};
            index++;
            if (lexArray_[index]->KindLexem() != lexer::Lexem_t::NUMBER &&
                lexArray_[index]->KindLexem() != lexer::Lexem_t::BRACE &&
                lexArray_[index]->KindLexem() != lexer::Lexem_t::VARIABLE) {
                std::cerr << "Expected expression, line -" << lexArray_[index]->Line();
                exit(EXIT_FAILURE);
            }
            node->left_ = mult_left;
            node->right_ = Insert_Term(index);
            mult_left = node;
        }
        return mult_left;
    }

    Node_t *Parser_t::Insert_Term(size_t &index) {
        Node_t *node = nullptr;
        if (lexArray_.IsTerm(index)) {
            if (lexArray_.IsInput(index)) {
                node = new CommandN_t{lexArray_[index]};
            }
            if (lexArray_.IsNumber(index)) {
                node = new NumberN_t{lexArray_[index]};
            }
            if (lexArray_.IsVariable(index)) {
                node = new VariableN_t(lexArray_[index]);
            }

            if (lexArray_.IsNumber(index + 1)) {
                std::cerr << "Two numbers in a row, line -" << lexArray_[index]->Line();
            }
            index++;
            return node;
        }

        if (lexArray_.Brace(index) == lexer::Brace_t::LBRAC) {
            index++;
            if (lexArray_.Brace(index) == lexer::Brace_t::RBRAC) {
                std::cerr << "Extra brace, line -" << lexArray_[index]->Line();
                exit(EXIT_FAILURE);
            }
            node = Insert_Comparison(index);
            if (lexArray_.Brace(index) != lexer::Brace_t::RBRAC) {
                std::cerr << "Expected brace, line -" << lexArray_[index]->Line();
                exit(EXIT_FAILURE);
            }
            index++;
            return node;
        }
        return nullptr;
    }

    void Parser_t::Print_Syntax_Tree(std::ostream &os, Node_t *top) {
        if (top == nullptr) {
            std::cerr << "Error: top is null" << std::endl;
            return;
        }
        if (top->left_ == nullptr && top->right_ == nullptr)
            return;

        top->Print(os);

        if (top->left_ == nullptr) {
            std::cout << "NULL" << std::endl;
            return;
        }

        top->left_->Print(os);

        if (top->right_ == nullptr) {
            std::cout << "NULL" << std::endl;
            return;
        }
        top->right_->Print(os);

        std::cout << std::endl;

        Print_Syntax_Tree(os, top->left_);
        Print_Syntax_Tree(os, top->right_);
    }

    void SentenceN_t::Print(std::ostream &os) {
        os << "SENTENCE #" << sentNum_ << " ";
    }

    Parser_t::~Parser_t() {
        Delete_Node(top_);
    }

    void Parser_t::Delete_Node(Node_t *node) {
        if (node == nullptr)
            return;
        Delete_Node(node->left_);
        Delete_Node(node->right_);
        delete node;
    }
}