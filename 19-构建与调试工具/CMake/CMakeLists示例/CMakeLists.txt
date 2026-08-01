

###################################################
##################### 基本语法 #####################
###################################################

# 指定cmake的最低版本要求
cmake_minimum_required(VERSION <version>)
# 用例:
cmake_minimum_required(VERSION 3.10)

# 定义项目的名称和使用的编程语言
project(<project_name> [<language>...])
# 用例:
project(MyProject CXX)

# 指定要生成的可执行文件和其源文件
add_executable(<target> <sorce_files>...)
# 用例:
add_executable(MyExecutable main.cpp other_file.cpp)

# 创建一个库（静态库或动态库）及其源文件
add_library(<target> <source_files>...)
# 用例:
add_library(MyLibrary STATIC library.cpp)

# 链接目标文件与其他库
target_link_libraries(<target> <libraries>...)
# 用例:
target_link_libraries(MyExecutable MyLibrary)

# 添加头文件搜索路径
include_directories(<dirs>...)
# 用例:
include_directories(${PROJECT_SOURCE_DIR}/include)

# 设置变量的值
set(<variable> <values>...)
# 用例:
set(CMAKE_CXX_STANDARD 11)

# 为指定目标设置包含目录（编译时搜索头文件路径）
target_include_directories(TARGET target_name
    [BEFORE | AFTER]
    [SYSTEM] [PUBLIC | PRIVATE | INTERFACE]
    [items1...])
# 用例:
target_include_directories(MyExecutable PRIVATE ${PROJECT_SOURCE_DIR}/include)

# 安装规则
install(TARGETS target1 [target2 ...]
        [RUNTIME DESTINATION dir] # 指定可执行文件的安装目录
        [LIBRARY DESTINATION dir] # 指定共享库的安装目录
        [ARCHIVE DESTINATION dir] # 指定静态库的安装目录
        [INCLUDES DESTINATION [dir ...]] # 指定安装头文件的目录
        [PRIVATE_HEADER DESTINATION dir] # 指定安装私有头文件的目录
        [PUBLIC_HEADER DESTINATION dir]) # 指定安装公共头文件的目录
# --- DESTINATION 目的地
# --- target1 target2 准备安装的源文件或目录
# --- dir 目标目录
# --- TARGET 安装库文件或可执行文件
# --- DIRECTORY 安装目录
# --- FILES 安装配置文件
# 用例:
install(TARGET MyExecutable RUNTIME DESTINATION bin)

# 条件语句（if, elseif, else, endif）
if(expression)
    #Commands
elseif(expression)
    #Commands
else()
    #Commands
endif()
# 用例:
if(CMKAE_BUILD_TYPE STREQUAL "Debug")
    message("Debug build")
endif()
# --- STREQUAL 判断是否相等
# 不等于如下:
if(NOT CMKAE_BUILD_TYPE STREQUAL "Debug")
    message("Debug build error")
endif()

# 自定义命令（add_custom_command 命令）
add_custom_command(
        TARGET target
        PRE_BUILD | PRE_LINK | POST_BUILD
        COMMAND command1 [ARGS] [WORKING_DIRECTORY dir]
        [COMMAND command2 [ARGS]]
        [DEPENDS [depend1 [depend2 ...]]]
        [COMMENT comment]
        [VERBATIM])
# --- TARGET target 为哪个构建目标添加自定义命令
# --- PRE_BUILD: 在目标构建之前执行命令
# --- PRE_LINK: 在目标链接之前执行命令
# --- POST_BUILD: 在目标构建之后执行命令
# --- command1: 运行的命令
# 用例:
add_custom_command(TRAGET MyExecutable POST_BUILD COMMAND ${CMAKE_COMMAND} -E echo "Build completed")

# 定义一个自定义的构建目标,增加一个没有输出的目标，使得它总是被构建
add_custom_command(<target name> ...)
# 用例:
add_custom_target(clean_target COMMAND make clean)
# --- clean_target 自定义目标名称
# --- COMMAND make clean 指定了当这个目标被构建时要执行的命令

# 添加一个依赖关系到指定目标，意味着在构建指定的目标之前，不许先构建其依赖的目标
add_dependencies(<target> <custom target>)
# --- target 主目标
# --- custom target 被添加到主目标的依赖
# 用例:
add_dependencies(log clean_target)


###################################################
#################### 变量和缓存 #####################
###################################################

# 定义变量
set(MT_VAR "Hello World")
# 使用变量
message(STATUS "Variable MY_VAR is ${MT_VAR}")

# 缓存变量
set(MY_CACHE_VAR "DefaultValue" CACHE STRING "A cache variable")
message(STATUS "Cache variable MY_CACHE_VAR is ${MY_CACHE_VAR}")


###################################################
#################### 查找库和包 #####################
###################################################

# 基本用法:
find_package(Boost REQUIRED)
# 指定版本:
find_package(Boost 1.70 REQUIRED)
# 查找库并指定路径
set(CMAKE_PREFI_PATH /path/to/)
find_package(OpenCV REQUIRED PATHS /path/to/opencv)
# 使用查找到的库
target_link_libraries(MyExecutable Boost::Boost)
# 设置包含目录和链接目录
# 编译时头文件目录和库目录
include_directories(${Boost_INCLUDE_DIRS})
# 链接时头文件目录和库目录
link_directories(${Boost_LIBRARY_DIRS})

###################################################
################# 添加编译链接选项 ##################
###################################################

#*************** 适用于设置任何属性 ******************
# 设置编译选项
set_target_properties(MyExecutable PROPERTIES COMPILES_OPTIONS "-Wall")
# 设置链接选项
set_target_properties(MyExecutable PROPERTIES LINK_FLAGS "-L/path/to/lib")

#*************** 专门设置编译链接属性 *****************
# 设置编译选项
target_compile_options(MyExecutable PRIVATE -Wall -Waxtra)
# 设置链接选项
target_link_options(MyExecutable PRIVATE -L/path/to/lib)

###################################################
################ 使用自定义cmake脚本 ################
###################################################

include(${CMAKE_SOURCE_DIR}/config.cmake)