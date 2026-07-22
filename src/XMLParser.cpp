//
// Created by Dustin on 4/26/25.
//

#include "../include/XMLParser.h"

static bool IsWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static std::string Trim(std::string s) {
    while (IsWhitespace(s.back()))
        s.pop_back();

    return s;
}

std::optional<std::string> XMLNode::ChildValue(std::string_view tag) const {
    for (auto& child : children_) {
        if (tag == child->tag_)
            return child->value_;
    }

    return std::nullopt;
}
const XMLNode* XMLNode::ChildNode(std::string_view tag) const {
    for (auto& child : children_) {
        if (tag == child->tag_)
            return child.get();
    }

    return nullptr;
}


XMLParser& XMLParser::GetInstance() {
    static XMLParser parser;

    return parser;
}

XMLParser::XMLParser() : src_{""}, pos_{0} {}

XMLNodePtr XMLParser::Parse(std::string src) {
    src_ = src;
    pos_ = 0;
    auto root_node = ParseNode();
    return root_node;
}

std::optional<char> XMLParser::Peek() {
    if (pos_ >= src_.size())
        return std::nullopt;

    return src_[pos_];
}

std::optional<std::string> XMLParser::PeekAhead(int n) {
    int amount_left = std::max(std::min(n, static_cast<int>(src_.size() - pos_)), 0);

    if (amount_left == 0)
        return std::nullopt;

    return src_.substr(pos_, amount_left);
}

std::optional<char> XMLParser::Consume() {
    if (pos_ >= src_.size())
        return std::nullopt;

    auto next_char = src_[pos_];
    pos_++;

    return next_char;
}

void XMLParser::ConsumeWhitespace() {
    while (Peek().has_value() && IsWhitespace(Peek().value()))
        pos_++;
}

std::string XMLParser::ConsumeAlphabetic() {
    std::string s;
    while (Peek().has_value() && std::isalpha(Peek().value()))
        s.push_back(Consume().value());
    return s;
}

int XMLParser::ConsumeNumeric() {
    std::string s;
    while (Peek().has_value() && std::isdigit(Peek().value()))
        s.push_back(Consume().value());
    return std::stoi(s);
}

std::string XMLParser::ConsumeAlphaNumeric() {
    std::string s;
    while (Peek().has_value() && std::isalnum(Peek().value()))
        s.push_back(Consume().value());
    return s;
}

std::string XMLParser::ConsumeUntilChar(char token) {
    std::string s;
    while (Peek().has_value() && Peek().value() != token) {
        s.push_back(Consume().value());
    }

    return s;
}

std::string XMLParser::ConsumeUntilString(std::string token) {
    std::string s;

    int token_size = token.size();
    while (PeekAhead(token_size).has_value() && PeekAhead(token_size) != token) {
        s.push_back(Consume().value());
    }

    return s;
}

std::unordered_map<std::string, std::string> XMLParser::ParseAttributes() {
    std::unordered_map<std::string, std::string> attributes;

    while ((Peek().has_value() && Peek() != '>') && (PeekAhead(2).has_value() && PeekAhead(2).value() != "/>")) {
        ConsumeWhitespace();
        auto attribute = ConsumeUntilChar('=');
        Consume(); // =
        Consume(); // '
        auto value = ConsumeUntilChar('\"');
        Consume(); //'
        attributes[attribute] = value;
    }

    return attributes;
}

XMLNodePtr XMLParser::ParseNode() {
    ConsumeWhitespace();

    auto node = std::make_unique<XMLNode>();

    Consume(); // <
    ConsumeWhitespace();

    node->tag_ = ConsumeAlphaNumeric();
    ConsumeWhitespace();

    node->attributes_ = ParseAttributes();
    ConsumeWhitespace();

    if (PeekAhead(2).has_value() && PeekAhead(2).value() == "/>") {
        // Self closing tag

        Consume(); // /
        Consume(); // >

        return node;
    }


    ConsumeUntilChar('>');
    Consume(); // >
    ConsumeWhitespace();

    if (Peek() == '<')
        node->children_ = ParseChildren();
    else {
        auto raw_value = ConsumeUntilString("</");
        node->value_ = Trim(raw_value);

        // NOTE WE STRIP WHITESPACE OFF THE NODE VALUE

        ConsumeWhitespace();
    }

    ConsumeWhitespace();
    Consume(); // <
    Consume(); // /
    ConsumeUntilChar('>'); // tagname
    Consume(); // >


    return node;
}

std::vector<XMLNodePtr> XMLParser::ParseChildren() {
    std::vector<XMLNodePtr> children;
    ConsumeWhitespace();
    while(PeekAhead(2).has_value() && PeekAhead(2).value() != "</") {
        ConsumeWhitespace();
        children.push_back(ParseNode());
        ConsumeWhitespace();
    }

    return children;
}