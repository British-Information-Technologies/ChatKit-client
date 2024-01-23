#include <fmt/core.h>

#include "view/style/string-modifiers.h"

namespace view {
inline std::string SpanWithSize(int size, const std::string& text) {
    return fmt::format("<span size='{}pt'>{}</span>", size, StripAngleBrackets(text));
}
} // namespace view