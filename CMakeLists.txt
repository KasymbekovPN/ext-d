cmake_minimum_required(VERSION 3.9)

project(ext-d VERSION 0.3.7)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

option(DEPR_STR_CVT_OPTION_EN "Enable deprecation string convert" ON)
option(TASK_0_3_6__1 "Enable" ON)
option(TASK_0_3_7__1 "Enable" ON)

configure_file(
        "${PROJECT_SOURCE_DIR}/config.h.in"
        "${PROJECT_SOURCE_DIR}/config.h"
		@ONLY)

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
#                tokenHandler.hpp
#                tokenHandler.cpp
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
                wfileHandler.hpp
                wfileHandler.cpp
                parted_line.hpp
                parted_line.cpp
                part_pline.hpp
                part_pline.cpp
                token_path.hpp
                token_path.cpp
                )