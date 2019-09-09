
# define compiler & option **ONLY** in standalone mode
# (else, keep option of parent module)
if(STANDALONE_MODE)

  if(CROSS_COMPILE_M3)

    # Clear Yocto setup (done for A7!)
    unset(CMAKE_CXX_FLAGS)
    unset(CXXFLAGS)
    unset(LDFLAGS)
    unset(CMAKE_CXX_COMPILER_ARG1)

    # define flags for m3
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++11")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -fno-exceptions -fno-use-cxa-atexit -fno-threadsafe-statics -fpermissive -fno-unwind-tables  -D GCC_ARMCM3  -D inline=" )
  endif()

  # enable C++11
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnuc11")

  # enable debug
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -g")

endif()
