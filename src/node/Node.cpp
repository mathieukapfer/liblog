#include "Node.h"
#include "NodeVisitorI.h"
#include <stddef.h>

#include "log_for_logger.h"

ENABLE_LOG(INFO);

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


bool Node::acceptAll(NodeVisitorI &visitor) {
  bool ret = false;
  ret |= visitor.visit(this);
  if (_firstChild != NULL) {
    visitor.newChild();
    ret |= _firstChild->acceptAll(visitor);
  }
  if (_nextSibling != NULL) {
    visitor.newSibling();
    ret |= _nextSibling->acceptAll(visitor);
  }
  LOG_DEBUG("ret:%d",ret);
  return ret;
}

bool Node::acceptAllChildren(NodeVisitorI &visitor) {
  bool ret = false;
  ret |= visitor.visit(this);
  if (_firstChild != NULL) {
    visitor.newChild();
    // accept all node of each children
    ret | _firstChild->acceptAll(visitor);
  }
  LOG_DEBUG("ret:%d",ret);
  return ret;
}

Node * Node::acceptFirstSibling(NodeVisitor2I &visitor) {
  Node * ret = NULL;
  ret = visitor.visit(this);
  if (_nextSibling != NULL && ret == NULL) {
    LOG_DEBUG("search next sibling")
    ret = _nextSibling->acceptFirstSibling(visitor);
  }
  LOG_DEBUG("ret:%d",ret);
  return ret;
}
