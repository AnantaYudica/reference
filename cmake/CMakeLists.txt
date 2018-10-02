cmake_minimum_required (VERSION 3.7.2)

add_compile_options(-std=c++11)

project(source)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BASIC_ENABLE_TEST "basic enable test" ON)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/source CACHE PATH "..." FORCE)
endif()

include(ExternalProject)

ExternalProject_Add(basic 
    SOURCE_DIR ${PROJECT_BINARY_DIR}/../libs/basic/cmake
    CMAKE_ARGS 
        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
    TEST_BEFORE_INSTALL ${BASIC_ENABLE_TEST})

include_directories (${PROJECT_SOURCE_DIR}/../include)

function(setSourceGroup strSourceGroup strDir)
    file(GLOB listFiles "${strDir}/*")
    foreach(it ${listFiles})
        get_filename_component(nameFile ${it} NAME)
        get_filename_component(extFile ${it} EXT)
        if(IS_DIRECTORY ${it})  
            setSourceGroup("${strSourceGroup}\\${nameFile}"
                "${strDir}/${nameFile}")
        elseif("${extFile}" MATCHES "\\.h")
            source_group(${strSourceGroup} FILES ${it})
        endif()
    endforeach()
endfunction(setSourceGroup)

function(UpperName strInput strOutput)
    string(LENGTH ${strInput} strLength)
    math(EXPR strLength "${strLength}-1")
    string(SUBSTRING ${strInput} 0 1 firstName)
    string(TOUPPER ${firstName} firstName)
    string(SUBSTRING ${strInput} 1 ${strLength} nextName)
    set(${strOutput} "${firstName}${nextName}" PARENT_SCOPE)
endfunction(UpperName)

function(addTestExecutable strTarget strFolder strDir listOther)
    file(GLOB listFiles "${strDir}/*")
    foreach(it ${listFiles})
        get_filename_component(nameFile ${it} NAME_WE)
        get_filename_component(extFile ${it} EXT)
        if(IS_DIRECTORY ${it})  
            UpperName(${nameFile} upperNameFile)
            addTestExecutable("${strTarget}${upperNameFile}" "${strFolder}//${nameFile}" 
                "${strDir}/${nameFile}" "${listOther}")
        elseif("${extFile}" MATCHES "\\.main\\.cpp")
            UpperName(${nameFile} upperNameFile)
            add_executable("${strTarget}${upperNameFile}" ${it} ${listOther})
            target_link_libraries("${strTarget}${upperNameFile}" source)
            target_include_directories("${strTarget}${upperNameFile}" PUBLIC
                $<BUILD_INTERFACE:${CMAKE_INSTALL_PREFIX}/basic/include>
                $<INSTALL_INTERFACE:include>)
            set_property(TARGET "${strTarget}${upperNameFile}" PROPERTY FOLDER ${strFolder})
            add_test(NAME "${strTarget}${upperNameFile}" COMMAND ${strTarget}${upperNameFile})
        endif()
    endforeach()
endfunction(addTestExecutable)

file(GLOB_RECURSE LIST_INCLUDE "${PROJECT_SOURCE_DIR}/../include/*")
file(GLOB_RECURSE LIST_SRC "${PROJECT_SOURCE_DIR}/../src/*")

setSourceGroup("Header Files" "${PROJECT_SOURCE_DIR}/../include")
setSourceGroup("Source Files" "${PROJECT_SOURCE_DIR}/../src")

enable_testing()
add_library(source STATIC ${LIST_INCLUDE} ${LIST_SRC})

target_include_directories(source PUBLIC
  $<BUILD_INTERFACE:${CMAKE_INSTALL_PREFIX}/basic/include>
  $<INSTALL_INTERFACE:include>)
add_dependencies(source basic)
addTestExecutable("Test" "test" "${PROJECT_SOURCE_DIR}/../test" "${LIST_INCLUDE}")
