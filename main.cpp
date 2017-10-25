
#include "config.h"

#include <iostream>

const char g_project_version[] = {
#ifdef PROJECT_VERSION
    PROJECT_VERSION
#else   
    "<unknow version>"
#endif
};

int main(int argc, char** argv){

    std::cout << g_project_version << std::endl;

    if (argc > 0) {
        
        for(int i = 0; i < argc; ++i){
            std::cout << argv[i] << std::endl;
        }
    }

    return 0;
}