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

LOG_REGISTER("TestSimple");

#define TEST_STRING "%s, %d, %f","this is a test", 999, 1.234
#define LOG_TEST                   \
  LOG_TRACE(TEST_STRING)                      \
  LOG_DEBUG (TEST_STRING)                       \
  LOG_INFO (TEST_STRING)                        \
  LOG_NOTICE (TEST_STRING)                      \
  LOG_WARNING (TEST_STRING)                     \
  LOG_ERROR (TEST_STRING)                       \
  LOG_CRITICAL (TEST_STRING)                    \
  LOG_FATAL (TEST_STRING)                       \
  LOG_EMERGENCY (TEST_STRING)                   \

#define LOG_REGISTER_(tag1)					\
  LOG_REGISTER(tag1); saveNode(tag1, _defaultLogCategory);	\
  LOG_DISLAY_TREE(); LOG_TEST; 

#define LOG_REGISTER__(tag1, tag2)					\
  LOG_REGISTER(tag1, tag2); saveNode(tag2, _defaultLogCategory);	\
  LOG_DISLAY_TREE(); LOG_TEST; 

#define LOG_REGISTER___(tag1, tag2, tag3)				\
  LOG_REGISTER(tag1, tag2, tag3); saveNode(tag3, _defaultLogCategory);	\
  LOG_DISLAY_TREE(); LOG_TEST; 

#define GET_LOG_LEVEL(tag)						\
  printf ("\n => %s:%d", tag, LogFacade::inst().getLogLevel((LogNode *) mapLogNode[std::string(tag)]));

#define TEST_CONFIGURATON_STRING(str) \
  LOG_EMERGENCY("*** test configuration string: %s",str);                 \
  LogFacade::inst().configureLevelNew(str);  \
  LOG_DISLAY_TREE();

int main(int argc, char *argv[]) {

  { LOG_REGISTER_  ("Main1");};
  { LOG_REGISTER__ ("Main1","module0");};
  { LOG_REGISTER_  ("Main2");};
  { LOG_REGISTER_  ("Main3");};
  { LOG_REGISTER_  ("Main");};
  { LOG_REGISTER__ ("Main","module1"); };
  { LOG_REGISTER___("Main","module1","submodule1"); };  
  { LOG_REGISTER__ ("Main","module2"); }; 
  { LOG_REGISTER___("Main","module2","submodule1"); }; 
  { LOG_REGISTER___("submodule1","a","b"); }; 

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
  TEST_CONFIGURATON_STRING("GLOBAL:1");

  TEST_CONFIGURATON_STRING("GLOBAL:2");

  TEST_CONFIGURATON_STRING("aaa:7");

  TEST_CONFIGURATON_STRING("a.b.c.d.e:2");
  
  TEST_CONFIGURATON_STRING("GLOBAL:1");

  TEST_CONFIGURATON_STRING("GLOBAL.Main1:2");

  TEST_CONFIGURATON_STRING("GLOBAL.Main:3");

  TEST_CONFIGURATON_STRING("GLOBAL.Main.module2:4");

  TEST_CONFIGURATON_STRING("GLOBAL.Main.module2.submodule1:5");
  
  return 0;
}





