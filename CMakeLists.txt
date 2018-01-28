cmake_minimum_required(VERSION 3.10)

project(ext-d VERSION 0.2.4)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

configure_file(config.h.in config.h)

add_executable(ext-d 
                main.cpp 
                config.h.in 
                fileHandler.h 
                fileHandler.cpp
                configHandler.h
                configHandler.cpp
                target.h
                target.cpp
                stringHandler.h
                stringHandler.cpp
                consoleCmdHandler.h
                consoleCmdHandler.cpp
                fileTree.h
                fileTree.cpp
                errorStatus.h
                errorStatus.cpp
                dom.hpp
                dom.cpp
                tokenGenerator.hpp
                tokenGenerator.cpp
                c_base_token.hpp
                c_base_token.cpp
                c_def_var_token.hpp
                c_def_var_token.cpp
                c_enum_token.hpp
                c_enum_token.cpp
                c_macro_token.hpp
                c_macro_token.cpp
                c_struct_token.hpp
                c_struct_token.cpp
                c_func_decl.hpp
                c_func_decl.cpp
                c_func_def.hpp
                c_func_def.cpp
                tokenHandler.hpp
                tokenHandler.cpp
                rstHandler.hpp
                rstHandler.cpp
                jsonBase.hpp
                jsonBase.cpp
                jsonNumber.hpp
                jsonNumber.cpp
                jsonObject.hpp
                jsonObject.cpp
                jsonSimple.hpp
                jsonSimple.cpp
                jsonString.hpp
                jsonString.cpp
                jsonArray.hpp
                jsonArray.cpp
                )