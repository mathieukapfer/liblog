#ifndef NODEVISITOR_H
#define NODEVISITOR_H

#include "Node.h"

class NodeVisitorI {
 public:
  NodeVisitorI() {};
  virtual ~NodeVisitorI() {};

  virtual bool visit(Node *node) = 0;

  virtual void newSibling() = 0;
  virtual void newChild() = 0;
};


#endif /* NODEVISITOR_H */
