#ifndef PARSECONFIGURATIONSTRING_H
#define PARSECONFIGURATIONSTRING_H


/*
 'Cat' means log category

  This is the string separte by dot in configure string

  example:

              "category = 1",
              "category.subcategory = 1"
              "category.subcategory.anotherSubCategory = 1"
*/

#include "log_const.h"

class LogSpecParser {
 public:
  LogSpecParser(const char *configureString):
    _configStr(configureString),
    _levelStr(NULL),
    _currentIndex(0)
    {}
  
  virtual ~LogSpecParser() {};

  /// parse and return the first category name
  bool getFirstCatStr(char **cat);

  /// parse and return the next category name
  bool getNextCatStr(char **cat);

  /// get log level as int
  int getLevel();

  /// special helper 
  bool isStartingWithRoot();

 private:
  
/* structure to store offset and size */
struct ConfigStringParsed {
  int firstCatIndex;
  int firstCatSize;
  int levelIndex;
  bool isLastCat;
};

  bool parseAtPos(int pos, ConfigStringParsed &parsed);
  
  char _buf[LOG_CATEGORY_NAME_SIZE_MAX];

  const char *_configStr;
  const char *_levelStr;
  
  int  _currentIndex;
  
};


#endif /* PARSECONFIGURATIONSTRING_H */
