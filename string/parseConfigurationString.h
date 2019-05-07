#ifndef PARSECONFIGURATIONSTRING_H
#define PARSECONFIGURATIONSTRING_H

struct ConfigStringParsed {
  int firstNameIndex;
  int firstNameSize;
  int levelIndex;
  bool isLastName;
};

void getFirstName(const char * configureString, int &index, ConfigStringParsed &parsed);

#endif /* PARSECONFIGURATIONSTRING_H */
