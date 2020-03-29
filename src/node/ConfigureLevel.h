#ifndef CONFIGURELEVEL_H
#define CONFIGURELEVEL_H

#include "NodeVisitorI.h"
//#include "LogNodeVisitorI.h"
#include "LogNode.h"

class ConfigureLevel {
 public:
  ConfigureLevel();
  virtual ~ConfigureLevel();

  // visitor to search a node with same name
  class SearchNodeWithName : public NodeVisitor2I {
  public:
    SearchNodeWithName(const char* nameToSearch):
      _nameToSearch(nameToSearch)
      {}
   
    /// return itself if has the name to search
    Node * visit(Node *node)  {
      return static_cast<LogNode *>(node)->hasSameName(_nameToSearch)?node:NULL;
    }

    const char* _nameToSearch;
    
  };

};



#endif /* CONFIGURELEVEL_H */
