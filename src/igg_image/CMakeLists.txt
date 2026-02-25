#################### Import the 'io_tools' library here ########################
find_library(IOTOOLS_LIB_PATH 
             NAMES libio_tools.so
             PATHS "${PROJECT_SOURCE_DIR}/lib"
             NO_DEFAULT_PATH)
#################### Create a library 'image' below this line ##################
add_library(Image image.cpp)

if(IOTOOLS_LIB_PATH )
    target_link_libraries(Image PRIVATE ${IOTOOLS_LIB_PATH})
else()
    message(FATAL_ERROR "io_tools library not found in lib/ directory!")
endif()