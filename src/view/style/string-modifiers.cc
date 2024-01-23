#include "string-modifiers.h"

#include <string>

const std::string view::StripAngleBrackets(const std::string& text) {
    return StripTrailingAngleBrackets(StripLeadingAngleBrackets(text));
}

const std::string view::StripLeadingAngleBrackets(const std::string& text) {
    if (text[0] == '<') {
        return text.substr(1);
    }

    return text;
}

const std::string view::StripTrailingAngleBrackets(const std::string& text) {
    int size = text.size();

    if (text[size - 1] == '>') {
        return text.substr(0, size - 1);
    }

    return text;
}