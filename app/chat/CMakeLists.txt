cmake_minimum_required(VERSION 3.10) 

# 设定工程名和版本号 
project(chat VERSION 1.0) 

# specify the C++ standard 
set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 
# set(CMAKE_C_COMPILER "/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc")
# set(CMAKE_CXX_COMPILER "/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++")

set(CMAKE_C_COMPILER "/home/hah/linux/f1c2000/buildroot-2020.02.4/output/host/bin/arm-buildroot-linux-gnueabi-gcc")
set(CMAKE_CXX_COMPILER "/home/hah/linux/f1c2000/buildroot-2020.02.4/output/host/bin/arm-buildroot-linux-gnueabi-g++")

set(CMAKE_CROSSCOMPILING TRUE)
set(CAMKE_SYSTEM_NAME Linux)

# 设置编译器搜索路径
# set(CMAKE_FIND_ROOT_PATH /opt/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabi/)
# set(CMAKE_SYSROOT /opt/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabi/)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -lm")

# # f1c200s
# set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -march=armv5te -mtune=arm926ej-s -mfloat-abi=soft")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv5te -mtune=arm926ej-s -mfloat-abi=soft")


# link_directories(/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/libs)
# include_directories(/usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/usr/include)
link_libraries(pthread)
link_libraries(c)


# 链接 curl库
link_directories(/home/hah/Downloads/curl-8.0.1/build/install/lib)
include_directories(/home/hah/Downloads/curl-8.0.1/build/install/include)
link_libraries(libcurl.a)

# 链接 openssl curl库需要
# link_directories(/home/hah/Downloads/openssl-3.1.0/build/install/lib)
# link_libraries(ssl)
# link_libraries(crypto)

# 链接 zlib curl库需要
link_directories(/home/hah/Downloads/zlib-1.2.11/build/install/lib)
link_libraries(z)


# 链接 paho mqtt
link_directories(./paho-mqtt-c-1.3.12/lib)
include_directories(./paho-mqtt-c-1.3.12/include)
link_libraries(libpaho-mqtt3c.a)

# 链接 pocketsphinx
link_directories(./pocketsphinx/lib)
include_directories(./pocketsphinx/include)
include_directories(./pocketsphinx/examples/include)
link_libraries(libpocketsphinx.a)
# link_libraries(/home/hah/Desktop/chat/pocketsphinx/lib/libm.a)

add_subdirectory(tts)
add_subdirectory(json)
add_subdirectory(asr)
add_subdirectory(src)
add_subdirectory(audiorecorder)
add_subdirectory(mqtt-client)

