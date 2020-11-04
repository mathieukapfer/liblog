# Put hierarchical log in your application

## 1) Usage
Put in your code,
  * the include
  
```C
            #include "log.h"
```
             
  * call the macro to register a name - optionaly linked to a parent - for any section of code  
```C  
            LOG_REGISTER("section_name");
            LOG_REGISTER("parent_name", "section_name");
```

  * add log like this: `LOG_{level} ( {params} )`   
    * where `{level}` is: `NONE EMERG FATAL CRIT ERROR WARN NOTIC INFO DEBUG TRACE`
    * and `{param}` is variadic list of parameters like **printf()**
  
Sample:

```C  
            #include "log.h"
            LOG_REGISTER("MainFile");                  //<---------- Create a category for the entire file

            int main(int argc, char *argv[]) {
              int i = 123;
              LOG_REGISTER("Main %d",i);               //<---------- Create a sub category 'Main'
              LOG_DEBUG("Hello - in main");            //<---------- Log as DEBUG level
                {
                  LOG_REGISTER("Main","Section");      //<---------- Create a sub sub category 'SectionOfMain'
                  LOG_INFO("Hello - inside section");  //<---------- Log as INFO level
                }
              }
```       

##  2) Provide log specification    
###   2.1) By 'log.cfg' file (in same place as bin)
Here after is a "log.cfg" sample

```shell  
              # Both level format are supported:
              # Level as str: NONE EMERG FATAL CRIT ERROR WARN NOTIC INFO DEBUG TRACE
              # Level as int: 0,   1,    2,    3,   4,    5,   6,    7,   8,    9

              # put your default level below

              GLOBAL:NOTICE      #  globally by name
              GLOBAL:6           #  globally by int
              Main.Section:INFO  #  on a section by name
              Main.Section:4     #  on a section by int
```

###   2.2) By code 
If you do not have file system, you can setup log level by insert macro in you code : `LOG_CONFIGURE({path},{level})` 
```C              
              void main() {
              LOG_CONFIGURE("Main:2");
              LOG_CONFIGURE("Main.SectionOfMain:3");
              ...
```

###   In both cases, here is log level meaning:
```C
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
```

##  3) Get log when you application is running
```bash
           log_test.c:0068:         [DEBUG] [Main]                Hello - in main
           log_test.c:0069:         [INFO ] [Main][Section]       Hello - inside section
```
