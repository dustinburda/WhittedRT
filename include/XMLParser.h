//
// Created by Dustin on 4/26/25.
//

#ifndef WHITTED_XMLPARSER_H
#define WHITTED_XMLPARSER_H

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
 * This is a naive and feature deficient XML Parser
 *
 * No Error Checking
 * Balanced tags only
 * No text content
 * */

class XMLParser {
public:
    static XMLParser& GetInstance();

    XMLNodePtr Parse(std::string src);
private:
    explicit XMLParser();

    std::optional<char> Peek();
    std::optional<std::string> PeekAhead(int n);
    std::optional<char> Consume();

    static bool IsWhitespace(char c);
    void ConsumeWhitespace();

    std::string ConsumeAlphabetic();
    int ConsumeNumeric();
    std::string ConsumeAlphaNumeric();
    std::string ConsumeUntilToken(char c);

    std::unordered_map<std::string, std::string> ParseAttributes();

    XMLNodePtr ParseNode();
    std::vector<XMLNodePtr> ParseChildren();

private:
    std::string src_;
    std::size_t pos_;
};


#endif //WHITTED_XMLPARSER_H
