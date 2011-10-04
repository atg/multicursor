#include <vector>
#include <deque>
#include <cstdint>

namespace multicursor {

struct range {
    int64_t location;
    int64_t length;
    
    bool isValid(); // Are location and length both non-negative?
    bool hasIndex(int64_t); // Does it contain this index?
    
    int64_t max(); // length + location
    int64_t lastIndex(); // max() - 1 unless the range is 0-length
    
    bool isDegenerate(); // Is the length 0?
    
    range truncateToFitLength(int64_t documentLength); // truncate this range so that it fits in documentLength. First try to make the length smaller, then try to make the location smaller and the length 0.
};

class context {
public:
    
    // Contains 1 or more ranges. Must never be empty
    std::vector<range> ranges;
    int64_t focused_range_index; // is -1 if there is no currently focused range
    int64_t document_length;
    
    
    context(std::vector<range> _ranges) : ranges(_ranges) { };
    
    // A "coherent" context has only 1 range (or is focused on a particular range)
    bool isCoherent();
    
    // Does |ranges| break any laws. All ranges must be contained within [0, document_length), and must not overlap. 0-length ranges must not 'coincide' with other ranges.
    bool isValid();


// Atomic operations
// Guaranteed not to leave the context in an invalid state.
    bool addRange(int64_t rng);
    bool deleteRange(range rng);
    bool deleteRanges(std
    
    bool focus(range rng);
    bool unfocus();
};

}
