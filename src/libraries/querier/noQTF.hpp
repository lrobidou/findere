#include <bf/all.hpp>

namespace noQTF {
std::vector<bool> query(bf::bloom_filter* filter, const std::string& s, const unsigned int& k);
}  // namespace noQTF