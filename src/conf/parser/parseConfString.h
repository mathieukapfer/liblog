#ifndef PARSECONFIGURATIONSTRING_H
#define PARSECONFIGURATIONSTRING_H


// helper to use result of parsing
#define GET_FIRST_NAME(configStr, parsed) &configStr[parsed.firstNameIndex]
#define GET_LEVEL(configStr, parsed) &configStr[parsed.levelIndex]

/* structure to store offset and size */
struct ConfigStringParsed {
  int firstNameIndex;
  int firstNameSize;
  int levelIndex;
  bool isLastName;
};

/*
   Parse the configuration string at current position
   NOTE: this functon do no allocation but only compute offset and size
         use helper macro above to work with parsed srtucture.
*/
/**
 * Parse the configuration string at current position
 *
 * @param configureString in : the string to parse
 * @param index           in : the current position in string to start the parsing
 * @param parsed          out:
 * @return value             : is last name
 */
bool getFirstName(const char * configureString, int &index, ConfigStringParsed &parsed);

/*
   copy the first category name of configureString into buf and return it
   NOTE: the called should allocated the buf
*/
char *getFirstNameStr(const char * configureString, char *buf);

bool getFirstNameStr_(const char *configStr , char *firstName, int &level, int &currentIndex);

bool isFirstName_RootName(const char *configStr);


#endif /* PARSECONFIGURATIONSTRING_H */
