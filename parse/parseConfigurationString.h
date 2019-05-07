#ifndef PARSECONFIGURATIONSTRING_H
#define PARSECONFIGURATIONSTRING_H

#define GET_FIRST_NAME_STR(configStr, firstName) {                      \
    ConfigStringParsed parsed;                                          \
    int localIndex = 0;                                                 \
    getFirstName(configStr, localIndex, parsed);                        \
    strncpy(firstName, configStr, parsed.firstNameSize); \
    firstName[parsed.firstNameSize] = '\0';                             \
  }

#define GET_FIRST_NAME(configStr, parsed) &configStr[parsed.firstNameIndex]
#define GET_LEVEL(configStr, parsed) &configStr[parsed.levelIndex]

struct ConfigStringParsed {
  int firstNameIndex;
  int firstNameSize;
  int levelIndex;
  bool isLastName;
};

void getFirstName(const char * configureString, int &index, ConfigStringParsed &parsed);

#endif /* PARSECONFIGURATIONSTRING_H */
