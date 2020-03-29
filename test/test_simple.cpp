#include "log.h"
#include <map>
#include <string>

std::map<std::string, void *> mapLogNode;

void saveNode(char * tag, void * logNode) {
  if (mapLogNode.count(tag) > 0) {
    // already exist then add suffix
    mapLogNode[std::string(tag) + "(" + std::to_string(mapLogNode.count(tag)) + ")"] = logNode;
  } else {
    mapLogNode[std::string(tag)] = logNode;
  }
}

#define LOG_REGISTER_(tag1)					\
  LOG_REGISTER(tag1); saveNode(tag1, _defaultLogCategory);	\
  LOG_DISLAY_TREE();

#define LOG_REGISTER__(tag1, tag2)					\
  LOG_REGISTER(tag1, tag2); saveNode(tag2, _defaultLogCategory);	\
  LOG_DISLAY_TREE();

#define LOG_REGISTER___(tag1, tag2, tag3)				\
  LOG_REGISTER(tag1, tag2, tag3); saveNode(tag3, _defaultLogCategory);	\
  LOG_DISLAY_TREE();

#define GET_LOG_LEVEL(tag)						\
  printf ("\n => %s:%d", tag, LogFacade::inst().getLogLevel((LogNode *) mapLogNode[std::string(tag)]));

int main(int argc, char *argv[]) {

  { LOG_REGISTER_  ("Main");};
  { LOG_REGISTER__ ("Main","module1"); };
  { LOG_REGISTER___("Main","module1","submodule1"); };  
  { LOG_REGISTER__ ("Main","module2"); }; 
  { LOG_REGISTER___("Main","module2","submodule1"); }; 

  GET_LOG_LEVEL("Main");
  GET_LOG_LEVEL("module1");
  GET_LOG_LEVEL("submodule1");
  GET_LOG_LEVEL("submodule1(1)");

  // bug!
  // => create new node (ok) but change all node with same name regardless the parent !
  //    (this could be a greate feature with syntaxe like this "*.module1:0" )
  LOG_CONFIGURE("module1:0");
  
  //LOG_CONFIGURE("Main.module1:0");
  GET_LOG_LEVEL("module1");
  GET_LOG_LEVEL("submodule1");

  /// test configure level
  LogFacade::inst().configureLevelNew("submodule1");
  LogFacade::inst().configureLevelNew(LOG_ROOT_NAME);
  
  return 0;
}

