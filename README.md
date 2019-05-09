# Log your application

## 1) In your code,
        - include "log.h"
        - call one macro 'LOG_REGISTER(<path>)' by section of code

       Now you can log with level of priority

        - LOG_<level>(<param>)
             - <level>:  NONE EMERG FATAL CRIT ERROR WARN NOTIC INFO DEBUG TRACE
             - <param>:  like printf()
    ----------------------------------------------------------------------------

      #include "log.h"
      LOG_REGISTER("MainFile");                <---------- Create a category for the entire file

      int main(int argc, char *argv[]) {
        LOG_REGISTER("Main");                  <---------- Create a sub category 'Main'
        LOG_DEBUG("Hello - in main");          <---------- Log as DEBUG level
          {
            LOG_REGISTER("Main","Section");        <------ Create a sub sub category 'SectionOfMain'
            LOG_INFO("Hello - inside section");    <------ Log as INFO level
          }
        }

       NOTE: LOG_<level>() is like printf() format

##  2) Provide log specification
    -----------------------------------------------------------------------------
###   2.1) By 'log.cnf' file (in same place as bin)

              # Both level format are supported:
              # Level as str: NONE EMERG FATAL CRIT ERROR WARN NOTIC INFO DEBUG TRACE
              # Level as int: 0,   1,    2,    3,   4,    5,   6,    7,   8,    9

              # put your default level below

              GLOBAL:NOTICE      #  globally by name
              GLOBAL:6           #  globally by int
              Main.Section:INFO  #  on a section by name
              Main.Section:4     #  on a section by int

###   2.2) Without file system use in your code 'LOG_CONFIGURE(<path>,<level>)' macro

              LOG_CONFIGURE("Main:2");
              LOG_CONFIGURE("Main.SectionOfMain:3");

###   In both case, here is log level meaning:

              TRACE          9  ==> higher verbose level
              DEBUG          8
              INFO           7
              NOTICE         6
              WARNING        5
              ERROR          4
              CRITICAL       3
              FATAL          2
              EMERGENCY      1  ==> lower verbose level
              NONE           0  ==> no log

##  3) Get log when you application is running
    -----------------------------------------------------------------------------

log_test.c:0068:         [NOTIC] [Main]                main():Hello - in main: !!!!!
log_test.c:0069:         [NOTIC] [Main]                main():Hello - in main: 999
