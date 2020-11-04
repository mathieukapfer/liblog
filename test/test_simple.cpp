#include "log.h"
#include "log_conf.h"
#include <map>
#include <string>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING
#include "doctest.h"


std::map<std::string, void *> mapLogNode;

void saveNode(const char * tag, void * logNode) {
  if (mapLogNode.count(tag) > 0) {
    // already exist then add suffix
    mapLogNode[std::string(tag) + "(" + std::to_string(mapLogNode.count(tag)) + ")"] = logNode;
  } else {
    mapLogNode[std::string(tag)] = logNode;
  }
}

LOG_REGISTER("TestSimple");

#define TEST_STRING "%s, %d, %f","this is a test", 999, 1.234
#define LOG_TEST                                \
  LOG_TRACE(TEST_STRING)                        \
  LOG_DEBUG (TEST_STRING)                       \
  LOG_INFO (TEST_STRING)                        \
  LOG_NOTICE (TEST_STRING)                      \
  LOG_WARNING (TEST_STRING)                     \
  LOG_ERROR (TEST_STRING)                       \
  LOG_CRITICAL (TEST_STRING)                    \
  LOG_FATAL (TEST_STRING)                       \
  LOG_EMERGENCY (TEST_STRING)                   \

#define LOG_REGISTER_(tag1)                                 \
  LOG_REGISTER(tag1); saveNode(tag1, _defaultLogCategory);	\
  LOG_DISLAY_TREE(); LOG_TEST; 

#define LOG_REGISTER__(tag1, tag2)                                \
  LOG_REGISTER(tag1, tag2); saveNode(tag2, _defaultLogCategory);	\
  LOG_DISLAY_TREE(); LOG_TEST; 

#define LOG_REGISTER___(tag1, tag2, tag3)                               \
  LOG_REGISTER(tag1, tag2, tag3); saveNode(tag3, _defaultLogCategory);	\
  LOG_DISLAY_TREE(); LOG_TEST; 

int GET_LOG_LEVEL(const char *tag) {
  int ret = (LogFacade::inst().getLogLevel((LogNode *) mapLogNode[std::string(tag)]));
  printf ("\n => %s:%d", tag, ret);
  return ret;
}

#define PRINT_LOG_LEVEL(tag)                          \
  printf ("\n => %s:%d", tag, GET_LOG_LEVEL(tag)  );

#define TEST_LOG_SPEC(str) \
  LOG_EMERGENCY("*** test configuration string: %s",str);                 \
  LogFacade::inst().configureLevel(str);  \
  LOG_DISLAY_TREE();

#define LOG_CONFIGURE_(x) \
  DOCTEST_MESSAGE(x); \
  LOG_CONFIGURE(x)


TEST_SUITE("Test configuration") {
  TEST_CASE(" configuration by file") {
    LOG_DISLAY_TREE();
        
    {LOG_REGISTER_ ("Main")};
    {LOG_REGISTER__("Main","MyClass1")};
    {LOG_REGISTER__("Main","MyClass2")};
    {LOG_REGISTER__("Main","MyClass3")};
    {LOG_REGISTER___("Main","MyClass1","section1")};
    {LOG_REGISTER___("Main","MyClass2","section2")};
    {LOG_REGISTER___("Main","MyClass3","section3")};
      
    CHECK(GET_LOG_LEVEL("Main") == 2);
    CHECK(GET_LOG_LEVEL("MyClass1") == 3);
    CHECK(GET_LOG_LEVEL("MyClass2") == 4);
    CHECK(GET_LOG_LEVEL("MyClass3") == 5);

    // test inheritage from parent
    CHECK(GET_LOG_LEVEL("section1") == 3);
    CHECK(GET_LOG_LEVEL("section2") == 4);
    CHECK(GET_LOG_LEVEL("section3") == 5);

    LogFacade::inst().printTable();
  }
  
  TEST_CASE(" configuration by ") {

    // start with no log
    LOG_CONFIGURE_("GLOBAL:0");

    // build log tree for test
    { LOG_REGISTER_  ("Cat1");};
    { LOG_REGISTER__ ("Cat1","module0");};
    { LOG_REGISTER_  ("Cat2"); };
    { LOG_REGISTER__ ("Cat2","module1"); };
    { LOG_REGISTER___("Cat2","module1","submodule1"); };  
    { LOG_REGISTER__ ("Cat2","module2"); }; 
    { LOG_REGISTER___("Cat2","module2","submodule1"); }; 
    
    // test inheritage global level
    CHECK(GET_LOG_LEVEL("Cat1") == 0);
    CHECK(GET_LOG_LEVEL("module0") == 0);
    CHECK(GET_LOG_LEVEL("Cat2") == 0);
    CHECK(GET_LOG_LEVEL("module1") == 0) ;
    CHECK(GET_LOG_LEVEL("submodule1") == 0) ;  
    CHECK(GET_LOG_LEVEL("module2") == 0) ; 
    CHECK(GET_LOG_LEVEL("submodule1(1)") == 0) ; 

    // test configure Cat1
    LOG_CONFIGURE_("Cat1:1");
    CHECK(GET_LOG_LEVEL("Cat1") == 1);     
    CHECK(GET_LOG_LEVEL("module0") == 1); 
    CHECK(GET_LOG_LEVEL("Cat2") == 0);
    CHECK(GET_LOG_LEVEL("module1") == 0) ;
    CHECK(GET_LOG_LEVEL("submodule1") == 0) ;  
    CHECK(GET_LOG_LEVEL("module2") == 0) ; 
    CHECK(GET_LOG_LEVEL("submodule1(1)") == 0) ; 

    // test configure Cat2
    LOG_CONFIGURE_("Cat2:2");
    CHECK(GET_LOG_LEVEL("Cat1") == 1);   
    CHECK(GET_LOG_LEVEL("module0") == 1); 
    CHECK(GET_LOG_LEVEL("Cat2") == 2);
    CHECK(GET_LOG_LEVEL("module1") == 2) ;
    CHECK(GET_LOG_LEVEL("submodule1") == 2) ;  
    CHECK(GET_LOG_LEVEL("module2") == 2) ; 
    CHECK(GET_LOG_LEVEL("submodule1(1)") == 2) ; 

    // inhertage 
    { LOG_REGISTER___("module1","submodule2","subsub"); }; 
    CHECK(GET_LOG_LEVEL("subsub") == 2); 

    //
    LOG_CONFIGURE_("Cat2.module1:3");
    CHECK(GET_LOG_LEVEL("Cat1") == 1);   
    CHECK(GET_LOG_LEVEL("module0") == 1); 
    CHECK(GET_LOG_LEVEL("Cat2") == 2);
    CHECK(GET_LOG_LEVEL("module1") == 3) ;
    CHECK(GET_LOG_LEVEL("submodule1") == 3) ;  
    CHECK(GET_LOG_LEVEL("subsub") == 3) ;  
    CHECK(GET_LOG_LEVEL("module2") == 2) ; 
    CHECK(GET_LOG_LEVEL("submodule1(1)") == 2) ; 
    LOG_DISLAY_TREE();
   

    /// test configure level
    TEST_LOG_SPEC("GLOBAL:1");

    TEST_LOG_SPEC("GLOBAL:2");

    TEST_LOG_SPEC("aaa:7");

    TEST_LOG_SPEC("a.b.c.d.e:3");

    TEST_LOG_SPEC("GLOBAL:1");

    TEST_LOG_SPEC("GLOBAL.Cat1:2");

    TEST_LOG_SPEC("GLOBAL.Cat:3");

    TEST_LOG_SPEC("GLOBAL.Cat.module2:4");

    TEST_LOG_SPEC("GLOBAL.Cat.module2.submodule1:5");

    LogFacade::inst().printTable();

  }
}
