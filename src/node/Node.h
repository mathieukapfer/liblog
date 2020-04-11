#ifndef NODE_H
#define NODE_H

#include <stddef.h>

class NodeVisitorI;
class NodeVisitor2I;

class Node {
 public:

  Node():_parent(NULL), _firstChild(NULL), _nextSibling(NULL)
    {};
  explicit Node(Node *p_parent);
  virtual ~Node() {};

  // build
  virtual void addChild(Node *child);

  // visit
  virtual bool acceptAll(NodeVisitorI &visitor);
  virtual bool acceptChildOnly(NodeVisitorI &visitor);

  // search
  virtual Node *acceptFirstSibling(NodeVisitor2I &visitor);

  // read
  virtual Node *getParent() { return _parent;};

    // read
  virtual Node *getFirstChild() { return _firstChild;};

 protected:

  Node *_parent;
  Node *_firstChild, *_nextSibling;
};

#endif /* NODE_H */






