#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
/************************************************************************
* N.Kozak // Lviv'2024-2025 // example syntax analysis by boost::spirit *
*                              file: one_file__x86_Debug.cpp            *
*                                                (0.04v/draft version ) *
*************************************************************************/
#include "stdio.h"
#include <iostream>
#include <sstream>  // for std::ostringstream
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp> //

//#define DEBUG__IF_ERROR

#define RERUN_MODE

#define DEFAULT_INPUT_FILE "../base_test_programs_2025/file1.k03"

#define MAX_TEXT_SIZE 8192

namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

#define SAME_RULE(RULE) ((RULE) | (RULE))

template <typename Iterator>
struct cwsyntax : qi::grammar<Iterator> {
    cwsyntax(std::ostringstream& error_stream) : cwsyntax::base_type(program_rule), error_stream_(error_stream) {
#include "..\\variant_specification\\EBNF_N1.h"
    }
    std::ostringstream& error_stream_;

    qi::rule<Iterator> NONTERMINALS, TOKENS, WHITESPACES;
#undef NONTERMINALS
#undef TOKENS
#undef WHITESPACES
};

template <typename Iterator>
struct cwgrammar : qi::grammar<Iterator> {
    cwgrammar(std::ostringstream& error_stream) : cwgrammar::base_type(program_rule), error_stream_(error_stream) {
#include "..\\variant_specification\\EBNF_N2.h"
    }
    std::ostringstream& error_stream_;

    qi::rule<Iterator> NONTERMINALS, TOKENS, WHITESPACES;
#undef NONTERMINALS
#undef TOKENS
#undef WHITESPACES
};

static size_t loadSource(char** text, char* fileName) {
    if (!fileName) {
        printf("No input file name\r\n");
        return 0;
    }

    FILE* file = fopen(fileName, "rb");

    if (file == 0) {
        printf("File not loaded\r\n");
        return 0;
    }

    fseek(file, 0, 2);
    long fileSize_ = ftell(file);
    if (fileSize_ >= 8192) {
        printf("the file(%ld bytes) is larger than %d bytes\r\n", fileSize_, 8192);
        fclose(file);
        exit(2);

    }
    size_t fileSize = fileSize_;
    rewind(file);

    if (!text) {
        printf("Load source error\r\n");
        return 0;
    }
    *text = (char*)malloc(sizeof(char) * (fileSize + 1));
    if (*text == 0) {
        fputs("Memory error", (__acrt_iob_func(2)));
        fclose(file);
        exit(2);

    }

    size_t result = fread(*text, sizeof(char), fileSize, file);
    if (result != fileSize) {
        fputs("Reading error", (__acrt_iob_func(2)));
        fclose(file);
        exit(3);

    }
    (*text)[fileSize] = '\0';

    fclose(file);

    return fileSize;
}

#define MAX_LEXEM_SIZE 1024
static int commentRemover(char* text, const char* openStrSpc, const char* closeStrSpc) {
    bool eofAlternativeCloseStrSpcType = false;
    bool explicitCloseStrSpc = true;
    if (!strcmp(closeStrSpc, "\n")) {
        eofAlternativeCloseStrSpcType = true;
        explicitCloseStrSpc = false;
    }

    unsigned int commentSpace = 0;

    unsigned int textLength = strlen(text);               // strnlen(text, MAX_TEXT_SIZE);
    unsigned int openStrSpcLength = strlen(openStrSpc);   // strnlen(openStrSpc, MAX_TEXT_SIZE);
    unsigned int closeStrSpcLength = strlen(closeStrSpc); // strnlen(closeStrSpc, MAX_TEXT_SIZE);
    if (!closeStrSpcLength) {
        return -1; // no set closeStrSpc
    }
    unsigned char oneLevelComment = 0;
    if (!strncmp(openStrSpc, closeStrSpc, MAX_LEXEM_SIZE)) {
        oneLevelComment = 1;
    }

    for (unsigned int index = 0; index < textLength; ++index) {
        if (!strncmp(text + index, closeStrSpc, closeStrSpcLength) && (explicitCloseStrSpc || commentSpace)) {
            if (commentSpace == 1 && explicitCloseStrSpc) {
                for (unsigned int index2 = 0; index2 < closeStrSpcLength; ++index2) {
                    text[index + index2] = ' ';
                }
            }
            else if (commentSpace == 1 && !explicitCloseStrSpc) {
                index += closeStrSpcLength - 1;
            }
            oneLevelComment ? commentSpace = !commentSpace : commentSpace = 0;
        }
        else if (!strncmp(text + index, openStrSpc, openStrSpcLength)) {
            oneLevelComment ? commentSpace = !commentSpace : commentSpace = 1;
        }

        if (commentSpace && text[index] != ' ' && text[index] != '\t' && text[index] != '\r' && text[index] != '\n') {
            text[index] = ' ';
        }

    }

    if (commentSpace && !eofAlternativeCloseStrSpcType) {
        return -1;
    }

    return 0;
}

#include <fstream>

int main_spirit(int argc, char* argv[]) {
    char* text_;
    char fileName[128] = DEFAULT_INPUT_FILE;
    char choice[2] = { fileName[0], fileName[1] };
    system("CLS");
    std::cout << "Enter file name(Enter \"" << choice[0] << "\" to use default \"" DEFAULT_INPUT_FILE "\"):";
    std::cin >> fileName;
    if (fileName[0] == choice[0] && fileName[1] == '\0') {
        fileName[1] = choice[1];
    }
    size_t sourceSize = loadSource(&text_, fileName);
    if (!sourceSize) {
#ifdef RERUN_MODE
        (void)getchar();
        printf("\nEnter 'y' to rerun program action(to pass action enter other key): ");
        char valueByGetChar = getchar();
        if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
            system((std::string("\"") + argv[0] + "\"").c_str());
        }
        return 0;
#else
        printf("Press Enter to exit . . .");
        (void)getchar();
        return 0;
#endif
    }
    printf("Original source:\r\n");
    printf("-------------------------------------------------------------------\r\n");
    printf("%s\r\n", text_);
    printf("-------------------------------------------------------------------\r\n\r\n");
    int commentRemoverResult = commentRemover(text_, COMMENT_BEGIN_STR, COMMENT_END_STR);
    if (commentRemoverResult) {
        printf("Comment remover return %d\r\n", commentRemoverResult);
        printf("Press Enter to exit . . .");
        (void)getchar();
        return 0;
    }
    printf("Source after comment removing:\r\n");
    printf("-------------------------------------------------------------------\r\n");
    printf("%s\r\n", text_);
    printf("-------------------------------------------------------------------\r\n\r\n");

    std::string text(text_);

    typedef std::string     str_t;
    typedef str_t::iterator str_t_it;

    std::ostringstream error_stream;
    cwsyntax<str_t_it> cwg1(error_stream);
    cwgrammar<str_t_it> cwg2(error_stream);

    str_t_it begin = text.begin(), end = text.end();
    if (!qi::parse(begin, end, cwg1)) {
        std::cout << "\nEBNF N1: Parsing failed!\n";
        std::cout << "EBNF N1: Error message: " << error_stream.str();
    }
    else if (begin != end) {
        std::cout << "\nEBNF N1: Unknown fragment ofter successs parse at: \"" << str_t(begin, end) << "\"\n";
    }
    else {
        std::cout << "\nEBNF N1: Parsing success!\n";
    }

    begin = text.begin(), end = text.end();
    if (!qi::parse(begin, end, cwg2)) {
        std::cout << "\nEBNF N2: Parsing failed!\n";
        std::cout << "EBNF N2: Error message: " << error_stream.str();
    }
    else if (begin != end) {
        std::cout << "\nEBNF N2: Unknown fragment ofter successs parse at: \"" << str_t(begin, end) << "\"\n";
    }
    else {
        std::cout << "\nEBNF N2: Parsing success!\n";
    }

    free(text_);

    (void)getchar();

#ifdef RERUN_MODE
    printf("\nEnter 'y' to rerun program action(to pass action enter other key): ");
    char valueByGetChar = getchar();
    if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
        system((std::string("\"") + argv[0] + "\"").c_str());
    }
#endif

    return 0;
}