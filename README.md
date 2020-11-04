# Put hierarchical log in your application

## 1) Usage
Put in your code,
  * the include
  
```C
            #include "log.h"
```
             
  * a call of the macro below to register a name - optionaly linked to a parent - for any section of code  
```C  
            LOG_REGISTER("section_name");
            {
              LOG_REGISTER("parent_name", "section_name");
            }
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
              LOG_REGISTER("Main");                    //<---------- Create a sub category 'Main'
              LOG_DEBUG("Hello - in main %d",i);       //<---------- Log as DEBUG level
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
On linux: timestamp in sec (precision 0,1ms)
```
 0000.7289 AuthentConfig.cpp:0022:       [<NOTIC>] [AuthentConfig] registerModbusIndex() ENTER:
 0000.7290 MaintenanceDb.cpp:0025:       [<NOTIC>] [MaintenanceDb] registerModbusIndex() ENTER:
 0000.7291 AuthentDb.cpp:0054:           [<NOTIC>] [authen.Db]     registerModbusIndex() ENTER:
 0000.7292 IoCpwIpc.cpp:0040:            [<NOTIC>] [iocpw.ipc]     registerSharedIndex() ENTER:
 0000.7293 IoCpwIpc.cpp:0059:            [<NOTIC>] [iocpw.ipc]     registerModbusIndex() ENTER:
```

On FreerRTOS: timestamp = nb tick
```
  87770 IoCpwConversion_EvState.cpp:0163:[<DEBUG>] [cpwio.evstate] noise:0, max:210, { 0, 0, 0, 0, 0, 0, 210,  }
  87770 IoCpwConversion_EvState.cpp:0167:[<DEBUG>] [cpwio.evstate] EV state: EV_STATE_A_Cpw_Plus12(2) cycle rate:100
```

On linux by syslog (tail -f /var/log/syslog):
```
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: CpwDb.cpp:0135:               [<NOTIC>] [cpw.db]        EVState   : EV_STATE_A_Cpw_Plus12(2)
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: ChargeCycle.cpp:0131:         [<NOTIC>] [ChargeCycle]   smState   : ChargingProcedure::Stop
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: ChargeCycle.cpp:0131:         [<NOTIC>] [ChargeCycle]   smState   : EndingProcedure::Start
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: SharedMemory.cpp:0094:        [<NOTIC>] [IPC]           W:SHARED_INDEX_SetCpwIsReady               0 (size:1) @index:11 (offset:44)
 Oct 21 04:46:33 rzn1-evlink-ep1 evse[256]: SharedMemory.cpp:0094:        [<NOTIC>] [IPC]           W:SHARED_INDEX_HMI_API_BLINK               0 (size:1) @index:163 (offset:824)
           log_test.c:0068:         [DEBUG] [Main]                Hello - in main
           log_test.c:0069:         [INFO ] [Main][Section]       Hello - inside section
```
