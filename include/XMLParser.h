//
// Created by Dustin on 4/26/25.
//

#ifndef WHITTED_XMLPARSER_H
#define WHITTED_XMLPARSER_H

#include <filesystem>
#include <fstream>
#include <memory>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <vector>

struct XMLNode; // Forward declare XMLNode for XMLNodePtr alias
using XMLNodePtr = std::unique_ptr<XMLNode>;

struct XMLNode {
    std::unordered_map<std::string, std::string> attributes_;
    std::string tag_;
    std::vector<XMLNodePtr> children_;
};


/*
 * This is a naive and feature deficient XML Parser with no error checking
 * :P
 * */

class XMLParser {
public:
    explicit XMLParser(std::string src);
    explicit XMLParser(std::filesystem::path path);

    XMLNodePtr Parse();
private:
    std::optional<char> Peek();
    std::optional<char> Consume();

    static bool IsWhitespace(char c);
    void ConsumeWhitespace();

    std::string ConsumeAlphabetic();

    int ConsumeNumeric();

    std::string ConsumeAlphaNumeric();


    XMLNodePtr ParseNode();
    std::vector<XMLNodePtr> ParseChildren();

    std::string src_;
    std::size_t pos_;
};


#endif //WHITTED_XMLPARSER_H
