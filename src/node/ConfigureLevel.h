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
    /// const
    SearchNodeWithName(const char* nameToSearch): _nameToSearch(nameToSearch) {}
   
    /// return itself if has the name to search
    Node * visit(Node *node);
   private:
    const char* _nameToSearch;    
  };

  // visitor to set level
  class SetLevel : public NodeVisitorI {
   public:
    /// const
    SetLevel(int level): _level(level) {}
   
    /// return allway true
    bool visit(Node *node);
   private:
    const int _level;
  };

};



#endif /* CONFIGURELEVEL_H */
