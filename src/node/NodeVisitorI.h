#ifndef NODEVISITORI_H
#define NODEVISITORI_H

#include "Node.h"

/// visitor that return bool
class NodeVisitorI {
 public:

  // mandatory visitor
  virtual bool visit(Node *node) = 0;

  // optional visitor prcessing
  virtual void newSibling() {};
  virtual void newChild() {};
};

/// visitor that return Node pointer
class NodeVisitor2I {
 public:

  // mandatory visitor
  virtual Node * visit(Node *node) = 0;

};


#endif
