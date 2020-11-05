![](hierachical_stone.png?raw=true)
# C/C++ Hierarchical Logger

## 1) Usage
  * include the header

```C
  #include "log.h"
```

  * name your blocks of code thanks to macro below
```C
  LOG_REGISTER("section_name");
```

  * you may link a section to his parent i.e. create a sub section
```C
  LOG_REGISTER("parent_name", "section_name");
```

  * then, the code is ready to be logged thanks to: `LOG_{level} ( {params} )`
    * where `{level}` is: `NONE EMERG FATAL CRIT ERROR WARN NOTIC INFO DEBUG TRACE`
    * and `{param}` is variadic list of parameters like **printf()**

### Full Sample:

```C
#include "log.h"
LOG_REGISTER("File"); //<-- Create a default category for the entire file

void aFunction() {LOG_ENTER();}

int main(int argc, char *argv[]) {
  int i = 123;
  aFunction();
  LOG_REGISTER("File", "Main");              //<-- Create a sub category 'Main' of 'File'
  LOG_INFO("Hello from main %d", i);         //<-- Log as INFO
  {
    LOG_REGISTER("File", "Main", "Section"); //<-- Create a sub category 'Section' of 'Main'
    LOG_TRACE("Hello from nested section");  //<-- Log as TRACE
  }
}
```
That produce:
```
 0000.0000 sample.cpp:0004:   [DEBUG] [File]               ENTER: aFunction()
 0000.0000 sample.cpp:0010:   [INFO ] [File.Main]          Hello from main 123
 0000.0000 sample.cpp:0013:   [TRACE] [File.Main.Section]  Hello from nested section
```

NOTES:
  - __A good usage hierarchical logs tree is one that reflect your directory tree and files organisation.__
  - this hierarchical log tree will help you to set a given level for the a given section of code, including all its subsections, thanks to log specification.

##  2) Provide log specification
###   2.1) By 'log.cfg' file
Here after is a `log.cfg` sample that sould be put in same place as the executable. Then is will be parsed at startup.

```shell
              # Both level format are supported:
              # Level as str: NONE EMERG FATAL CRIT ERROR WARN NOTIC INFO DEBUG TRACE
              # Level as int: 0,   1,    2,    3,   4,    5,   6,    7,   8,    9

              # set your level filter

              GLOBAL:NOTICE            #  Default log for the entire program
              GLOBAL:6                 #  Same as above with 'int' syntaxe
              File:INFO                #  More log for 'File' :until INFO
              File.Main:DEBUG          #  More log for 'Main' :until DEBUG
              File.Main.Section:TRACE  #  Get all log for 'Section' (TRACE is the max level)

```
Each line is executed once by once. Then the first line `GLOBAL:NOTICE` set the default log level (special name `GLOBAL` is the root of the node tree). Then, the second line `File:DEBUG` increase the log level for `File` and all its sections i.e. `File.Main` and `File.Main.Section`. At least, the last line `File.Main.Section:TRACE` increase again the log for the deeper block of code `Section`

####   Display log spec
Add the code below to print the log spec of your program. It can be used as `log.cfg` template.
<table>
<tr><td>
<div markdown="1">

```C++
#include "log_conf.h"

int main(int argc, char *argv[]) {
...
  LOG_DISLAY_TREE();
...
}

```
</div></td>
<td><div markdown="1">

```
*Display spec:
 GLOBAL                   :TRACE(9)
 File                     :TRACE(9)
 File.Main                :TRACE(9)
 File.Main.Section        :TRACE(9)
 SYSLOG_MAX_LEVEL         :TRACE(9)
*
```

</div></tr></table>

Note:
  - only the known sections (section that has been run) are display when `LOG_DISLAY_TREE()` is called.
  - if you have section declared in your `log.cfg` but not yet run in your code, it will appears with `// prealloacted`
  - on linux, a section `SYSLOG_MAX_LEVEL` appear to define an addition filter before put log in syslog buffer

###   2.2) By code
If you do not have file system, you can setup log level by insert macro in you code : `LOG_CONFIGURE({path},{level})`
```C
              void main() {
              LOG_CONFIGURE("Main:2");
              LOG_CONFIGURE("Main.Section:3");
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

##  3) Log output
On linux: timestamp in sec (precision 0,1ms)
```
 0000.7289 AuthentConfig.cpp:0022:       [<NOTIC>] [AuthentConfig] ENTER: registerModbusIndex()
 0000.7290 MaintenanceDb.cpp:0025:       [<NOTIC>] [MaintenanceDb] ENTER: registerModbusIndex()
 0000.7291 AuthentDb.cpp:0054:           [<NOTIC>] [authen.Db]     ENTER: registerModbusIndex()
 0000.7292 IoCpwIpc.cpp:0040:            [<NOTIC>] [iocpw.ipc]     ENTER: registerSharedIndex()
 0000.7293 IoCpwIpc.cpp:0059:            [<NOTIC>] [iocpw.ipc]     ENTER: registerModbusIndex()
```

On FreerRTOS: timestamp = nb ticks
```
  87770 IoCpwConversion_EvState.cpp:0163:[<DEBUG>] [cpwio.evstate] noise:0, max:210, { 0, 0, 0, 0, 0, 0, 210,  }
  87770 IoCpwConversion_EvState.cpp:0167:[<DEBUG>] [cpwio.evstate] EV state: EV_STATE_A_Cpw_Plus12(2) cycle rate:100
```

On linux by syslog (`tail -f /var/log/syslog`):
```
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: CpwDb.cpp:0135:               [<NOTIC>] [cpw.db]        EVState   : EV_STATE_A_Cpw_Plus12(2)
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: ChargeCycle.cpp:0131:         [<NOTIC>] [ChargeCycle]   smState   : ChargingProcedure::Stop
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: ChargeCycle.cpp:0131:         [<NOTIC>] [ChargeCycle]   smState   : EndingProcedure::Start
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: SharedMemory.cpp:0094:        [<NOTIC>] [IPC]           W:SHARED_INDEX_SetCpwIsReady               0 (size:1) @index:11 (offset:44)
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: SharedMemory.cpp:0094:        [<NOTIC>] [IPC]           W:SHARED_INDEX_HMI_API_BLINK               0 (size:1) @index:163 (offset:824)
```

##  4) Additional filter for syslog
You can filter the maximum log level sent to syslog deamon with `SYSLOG_MAX_LEVEL`
Be carefull to put this "log spec" after `GLOBAL`, otherwise it will be overwrited:
```shell
 GLOBAL                   : NOTICE   # apply NOTICE level as default (including SYSLOG_MAX_LEVEL)
 SYSLOG_MAX_LEVEL         : INFO     # change max level for syslog to INFO
 MAIN                     : DEBUG    # more log for MAIN section (apply on stdout, but not syslog)
```
