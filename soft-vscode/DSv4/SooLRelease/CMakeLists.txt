cmake_minimum_required(VERSION 3.22)


if(NOT ENV{sool_ROOT})
    set(ENV{sool_ROOT} ${CMAKE_CURRENT_SOURCE_DIR})    
endif()

list(APPEND CMAKE_MESSAGE_CONTEXT "sool")
message(STATUS "Loaded SooL release from $ENV{sool_ROOT}")

set(sool_INCDIR
$ENV{sool_ROOT}/core
$ENV{sool_ROOT}/core/include
$ENV{sool_ROOT}/core/system/include
PARENT_SCOPE
)

set(sool_SRC 
# $ENV{sool_ROOT}/core/system/src/system_stm32f0xx.cpp
# $ENV{sool_ROOT}/core/system/src/system_stm32f3xx.cpp
# $ENV{sool_ROOT}/core/system/src/system_stm32f4xx.cpp
# $ENV{sool_ROOT}/core/system/src/system_stm32f7xx.cpp
# $ENV{sool_ROOT}/core/system/src/system_stm32h7xx.cpp
$ENV{sool_ROOT}/core/system/src/system_stm32l4xx.cpp
PARENT_SCOPE)

function(sool_require_peripheral peripherals)
set(root $ENV{sool_ROOT})
set(src "")
 foreach(periph ${ARGV})
    if(NOT EXISTS ${root}/core/include/${periph}.h)
        message(SEND_ERROR "Requested non-available peripheral ${periph} from SooL install. (looked up as ${root}/core/include/${periph}.h)")
    else()
        message(STATUS "Adds requested SooL peripheral ${periph}")
        if(EXISTS ${root}/core/src/${periph}.cpp)
            message(VERBOSE "    C++ File found for ${periph}")
            set(src ${src} ${root}/core/src/${periph}.cpp)
        endif()
    endif()
 endforeach()

 set(sool_SRC ${sool_SRC} ${src} PARENT_SCOPE)
endfunction()


function(sool_require_module modules)
set(root $ENV{sool_ROOT})
set(inc "")
set(src "")
 foreach(mod ${ARGV})
    if(NOT EXISTS ${root}/modules/${mod})
        message(SEND_ERROR "Requested non-available module ${mod} from SooL install.")
    else()
        message(STATUS "Adds requested SooL module ${mod} ")
        if(EXISTS ${root}/modules/${mod}/include)
            message(VERBOSE "    Include dir found for ${mod}")
            set(inc ${inc} ${root}/modules/${mod}/include)
        endif()
        if(EXISTS ${root}/modules/${mod}/src)
        message(VERBOSE "    C++ Files found for ${mod}")
        file(GLOB_RECURSE mod_sources LIST_DIRECTORIES false ${root}/modules/${mod}/src/*.cpp)
            set(src ${src} ${mod_sources})
            unset(mod_sources)
        endif()
    endif()
 endforeach()

 set(sool_SRC ${sool_SRC} ${src} PARENT_SCOPE)
 set(sool_INCDIR ${sool_INCDIR} ${inc} PARENT_SCOPE)
endfunction()

list(POP_BACK CMAKE_MESSAGE_CONTEXT)