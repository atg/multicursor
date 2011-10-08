#import "multicursor.hh"

#include <vector>
#include <deque>

bool range::isValid() {
	return location >= 0 && length >= 0;
}

bool range::hasIndex(int64_t i) {
	return isValid() && i >= location && i < location + length;
}

int64_t range::max() {
	return location + length;
}

int64_t range::lastIndex() {
	return length != 0 ? max() : location;
}

bool range::isDegenerate() {
	return length == 0;
}

range range::truncateToFitLength(int64_t documentLength) {
	range r = *this;
	if (!r.isValid()) {
		if (r.location < 0) {
			r.location = 0;
			if (r.length >= 0)
				r.length -= r.location;
		}
		if (!r.isValid()) {
			r.length = 0;
		}
		if (!r.isValid()) {
			r.location = 0;
		}
	}
	
	if (r.max() > documentLength) {
		if (r.location > documentLength) {
			r.location = documentLength;
			r.length = 0;
		}
		else {
			r.length = documentLength - r.location;
		}
	}
	
	return r;
}

bool range::indexesIntersect(range rng) {
	if (rng.length == 0 || length == 0)
		return false;
	return rng.hasIndex(lastIndex()) || rng.hasIndex(location);
}

//
// context
//
bool context::isCoherent() {
  
}

bool context::isValid() {
  
}

range context::rangeAtIndex(int64_t index) {
  if (index )
}

int64_t context::indexForRange(range rng) {
  
}

range context::primaryRange() {
  return (focused_range_index) < 0 ? ranges[0] : ranges[focused_range_index];
}

bool context::addRange(int64_t rng) {

}
bool context::deleteRange(range rng) {
  
}
bool context::deleteRanges(std::vector<range> rngs) {
  
}

bool context::focus(range rng) {
  
}
bool context::unfocus() {
  focused_range_index = -1;
}

bool context::performAction(range (^callback)(range rng, bool* shouldDelete)) {
  
}
