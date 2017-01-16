#include "InternalNode.h"

void InternalNode::replaceChild(Child toDelete, Child toReplace) {
	if (toDelete == Left && toReplace == Mid) {
		left = mid;
		min1 = min2;
		replaceChild(Mid, Empty);
	}
	else if (toDelete == Mid && toReplace == Left) {
		mid = left;
		min2 = min1;
		replaceChild(Left, Empty);
	}
	else if (toDelete == Mid && toReplace == Right) {
		mid = right;
		min2 = min3;
		replaceChild(Right, Empty);
	}
	else if (toDelete == Right && toReplace == Mid) {
		right = mid;
		min3 = min2;
		replaceChild(Mid, Empty);
	}
	else if (toDelete == Left && toReplace == Empty) {
		left = nullptr;
		min1 = emptyKey;
	}
	else if (toDelete == Mid && toReplace == Empty) {
		mid = nullptr;
		min2 = emptyKey;
	}
	else if (toDelete == Right && toReplace == Empty) {
		right = nullptr;
		min3 = emptyKey;
	}
}//replaceChild