function(add_git_submodule REL_DIR)
    set(FULL_DIR ${CMAKE_SOURCE_DIR}/${REL_DIR})

    if(NOT EXISTS ${FULL_DIR}/CMakeLists.txt)
        find_package(Git REQUIRED)

        if(NOT Git_FOUND)
            message(FATAL_ERROR "Git required for adding sumodule but was not found.")
        endif()

        execute_process(COMMAND ${GIT_EXECUTABLE}
            submodule update --init --recursive -- ${REL_DIR}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
    else()
        add_subdirectory(${FULL_DIR})
    endif()
endfunction(add_git_submodule)
