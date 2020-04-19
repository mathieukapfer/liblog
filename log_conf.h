#include "LogFacade.h"

/* for usage without file system */
/* define log level - BY CODE - see note 2) above */
#define LOG_CONFIGURE(conf)  LogFacade::inst().configureLevel(conf);

/* for support */
/* display log level tree */
#define LOG_DISLAY_TREE() LogFacade::inst().displayLevelTree();

/* for fifo instread of stdio */
#define LOG_REGISTER_FIFO(fifo) LogFacade::inst().registerFifo(fifo);

/* provide at complation time the memory addr where the configuration file will be copied
 * (this is use for instance to share the conf from A7[Linux] to M3[Freertos] in LCES2 platform)
 */
#ifdef ENABLE_COPY_CONF_TO_MEM
#define LOG_REGISTER_MEM_CONF_ADDR(addr) LogFacade::inst().registerMemConfAddr(addr)
#endif
