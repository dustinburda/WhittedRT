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

    std::string value_;
    std::vector<XMLNodePtr> children_;

    std::optional<std::string> ChildValue(std::string_view tag) const;
    const XMLNode* ChildNode(std::string_view tag) const;
};

class XMLParser {
public:
    static XMLParser& GetInstance();

    XMLNodePtr Parse(std::string src);
private:
    explicit XMLParser();

    std::optional<char> Peek();
    std::optional<std::string> PeekAhead(int n);
    std::optional<char> Consume();

    void ConsumeWhitespace();

    std::string ConsumeAlphabetic();
    int ConsumeNumeric();
    std::string ConsumeAlphaNumeric();
    std::string ConsumeUntilChar(char token);
    std::string ConsumeUntilString(std::string token);

    std::unordered_map<std::string, std::string> ParseAttributes();

    XMLNodePtr ParseNode();
    std::vector<XMLNodePtr> ParseChildren();

private:
    std::string src_;
    std::size_t pos_;
};


#endif //WHITTED_XMLPARSER_H
