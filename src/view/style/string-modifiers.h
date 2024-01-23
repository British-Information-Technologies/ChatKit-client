#ifndef VIEW_STYLE_STRING_MODIFIERS_H_
#define VIEW_STYLE_STRING_MODIFIERS_H_

#include <string>

namespace view {
const std::string StripAngleBrackets(const std::string& text);

const std::string StripLeadingAngleBrackets(const std::string& text);

const std::string StripTrailingAngleBrackets(const std::string& text);
} // namespace view

#endif