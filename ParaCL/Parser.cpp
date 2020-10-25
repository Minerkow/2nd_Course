#include "Parser.h"

namespace parser {

    Parser_t::Parser_t(lexer::LexArray_t& lexArray) : lexArray_(lexArray), top_(0){
        size_t index = 0;
        top_ = Insert_Sentence((index));
    }

    Node_t *Parser_t::Insert_Sentence(size_t &index) {
        Node_t* node = new SentenceN_t{0};
        Node_t* top = node;
        size_t num = 1;
        while (index < lexArray_.Size() - 1 &&
               lexArray_.FigurBrace(index) != lexer::Brace_t::RFIGURBRAC)
        {
            node->left_ = Insert_Command(index);
            if (lexArray_.IsEndCommand(index) &&
                lexArray_.FigurBrace(index) != lexer::Brace_t::RFIGURBRAC) {
                std::cerr << "\nExpected '}': line = "
                          << lexArray_[index]->Line() << "\n";
                exit(EXIT_FAILURE);
            }
            index++;
            node->left_ = new SentenceN_t{num++};
            node = node->right_;
        }
        return top;
    }

    Node_t *Parser_t::Insert_Command(size_t &index) {
        Node_t* node = nullptr;
        Node_t* comm_left = Insert_Comparison(index);
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
        
    }


}