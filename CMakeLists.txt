cmake_minimum_required(VERSION 3.9)

project(ext-d VERSION 0.4.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

option(DEPR_STR_CVT_OPTION_EN "Enable deprecation string convert" ON)

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
                tokens/c_base_token.hpp
                tokens/c_base_token.cpp
                tokens/c_def_var_token.hpp
                tokens/c_def_var_token.cpp
                tokens/c_enum_token.hpp
                tokens/c_enum_token.cpp
                tokens/c_macro_token.hpp
                tokens/c_macro_token.cpp
                tokens/c_struct_token.hpp
                tokens/c_struct_token.cpp
                tokens/c_func_decl.hpp
                tokens/c_func_decl.cpp
                tokens/c_func_def.hpp
                tokens/c_func_def.cpp
#                tokenHandler.hpp
#                tokenHandler.cpp
                json/jsonBase.hpp
                json/jsonBase.cpp
                json/jsonNumber.hpp
                json/jsonNumber.cpp
                json/jsonObject.hpp
                json/jsonObject.cpp
                json/jsonSimple.hpp
                json/jsonSimple.cpp
                json/jsonString.hpp
                json/jsonString.cpp
                json/jsonArray.hpp
                json/jsonArray.cpp
                wfileHandler.hpp
                wfileHandler.cpp
                parted_line.hpp
                parted_line.cpp
                part_pline.hpp
                part_pline.cpp
                token_path.hpp
                token_path.cpp
                )
