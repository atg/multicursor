#include <vector>
#include <deque>

namespace multicursor {

struct range {
    int64_t location;
    int64_t length;
    
    bool isValid();
}

class context {
    
    std::vector<range> ranges;
    
};

}
