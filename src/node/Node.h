#ifndef NODE_H
#define NODE_H

#include <stddef.h>

class NodeVisitorI;

class Node {
 public:

  Node():_parent(NULL), _firstChild(NULL), _nextSibling(NULL)
    {};
  explicit Node(Node *p_parent);
  virtual ~Node() {};

  //
  void addChild(Node *child);

  //
  bool accept(NodeVisitorI &visitor);

  //
  Node *getParent() { return _parent;};

 private:
  Node *_parent;
  Node *_firstChild, *_nextSibling;
};

#endif /* NODE_H */
