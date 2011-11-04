#import "multicursor.hh"

#include <vector>
#include <deque>

bool range::isValid() {
	return location >= 0 && length >= 0;
}

// Difference between these two is that hasIndex always returns false for a zero length range, whereas containsIndex treats it as a 1-length range
bool range::hasIndex(int64_t i) {
	return isValid() && i >= location && length > 0 && i < location + length;
}
bool range::containsIndex(int64_t i) {
	return isValid() && i >= location && (i < location + length || length == 0);
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
	return ranges.size == 1 || focused_range_index != -1
}

bool context::isValid() {
	// All ranges must be contained within [0, document_length), and must not overlap. 0-length ranges must not 'coincide' with other ranges.
	
	int64_t lastIndex = -1;
	bool lastWasDegenerate = false;
	for (std::vector<range>::iterator it = ranges.begin(), et = ranges.end(); it != et; ++it) {
		if (!it->isValid() || it->lastIndex() > document_length)
			return false;
		bool isExceptional = lastWasDegenerate && it->isDegenerate();
		if (!isExceptional && it->containsIndex(lastIndex))
			return false;
		lastIndex = it->lastIndex();
		lastWasDegenerate = it->isDegenerate();
	}
	
	return true;
}

range context::rangeAtIndex(int64_t index) {
	if (index )
}

int64_t context::indexForRange(range rng) {
	
}

int64_t context::primaryRangeIndex() {
	return focused_range_index < 0 ? 0 : focused_range_index;
}

range context::primaryRange() {
	return focused_range_index < 0 ? ranges[0] : ranges[focused_range_index];
}

bool context::addRange(int64_t rng) {
	
	std::vector<range> before = ranges;
	ranges.push_back(rng);
	if (!isValid())
		ranges = before;
	
	return isValid();
}
bool context::deleteRange(range rng) {
  
  return true;
}
bool context::deleteRanges(std::vector<range> rngs) {
	bool flag = false;
	for (std::vector<range> it = rgns.begin() , et = rgns.end() ; it != et ; ++it)
	flag = true && deleteRange(*it);
	
	return flag;
}

bool context::focus(range rng) {
	for ( std::vector<range>::iterator it = ranges.begin() , et = ranges.end() ; it != et ; ++it)
	  if (it == rng) { focused_range_index = it - ranges.begin()
	                 ; return true }
	
	return false;
}
bool context::unfocus() {
	if (focused_range_index == -1) return false;
	
	focused_range_index = -1;
	return true;
}

void context::decohere() {
	// Discard everything but the primary range
	range primary = primaryRange();
	ranges.erase(ranges.begin(), ranges.end());
	ranges.push_back(primary);
	focused_range_index = -1;
}

bool context::performAction(range (^callback)(range rng, bool* shouldDelete)) {
	
	
	
}
