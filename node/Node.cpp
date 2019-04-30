#include "Node.h"
#include "NodeVisitorI.h"
#include <stddef.h>

Node::Node(Node *p_parent):
  _parent(p_parent) {

  if (_parent != NULL) {
    _parent->addChild(this);
  }
}

void Node::addChild(Node *child) {
    // add first child
    if (_firstChild == NULL) {
      _firstChild = child;
    } else {
      // add sibling
      Node *lastSibling = _firstChild;
      while (lastSibling->_nextSibling != NULL) {
        lastSibling = lastSibling->_nextSibling;
      }
      lastSibling->_nextSibling = child;
    }
  }


void Node::accept(NodeVisitorI &visitor) {
  visitor.visit(this);
  if (_firstChild != NULL) {
    visitor.newChild();
    _firstChild->accept(visitor);
  }
  if (_nextSibling != NULL) {
    visitor.newSibling();
    _nextSibling->accept(visitor);
  }
}
