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
