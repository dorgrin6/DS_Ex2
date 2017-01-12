#include "LeafNode.h"
#include "Node.h"
#include "InternalNode.h"

LeafNode* Node::asLeaf(){
	return static_cast<LeafNode*>(this);
}

InternalNode* Node::asInternal(){
	return static_cast<InternalNode*>(this);
}
