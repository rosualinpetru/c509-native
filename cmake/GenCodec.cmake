function(generate_cddl_codec CDDL_FILE_PATH)
    set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/gen)

    set(ZCBOR_DIR ${CMAKE_SOURCE_DIR}/external/zcbor)

    if(NOT EXISTS ${ZCBOR_DIR}/zcbor/zcbor.py)
        message(FATAL_ERROR "Script zcbor.py not found. Make sure to add the submodule.")
    endif()

    set(REQUIREMENTS_FILE ${ZCBOR_DIR}/scripts/requirements-base.txt)

    find_package(Python3 3 REQUIRED COMPONENTS Interpreter)
    if(NOT Python3_FOUND)
        message(FATAL_ERROR "Python3 is required for code generation but was not found.")
    endif()

    set(VENV_DIR ${CMAKE_BINARY_DIR}/venv)
    set(VENV_PYTHON ${VENV_DIR}/bin/python)
    set(VENV_PIP ${VENV_DIR}/bin/pip)

    if(NOT EXISTS ${VENV_DIR}/pyvenv.cfg)
        execute_process(
            COMMAND ${Python3_EXECUTABLE} -m venv ${VENV_DIR}
            RESULT_VARIABLE VENV_CREATION_RESULT
            OUTPUT_QUIET
            ERROR_QUIET
        )

        if(NOT VENV_CREATION_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to create virtual environment.")
        endif()
    endif()

    execute_process(
        COMMAND ${VENV_PYTHON} -m pip install --upgrade pip
        RESULT_VARIABLE PIP_UPGRADE_RESULT
        OUTPUT_QUIET
        ERROR_QUIET
    )

    if(NOT PIP_UPGRADE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to upgrade pip for codec generation.")
    endif()

    execute_process(
        COMMAND ${VENV_PIP} install -r ${REQUIREMENTS_FILE}
        RESULT_VARIABLE REQUIREMENTS_INSTALL_RESULT
        OUTPUT_QUIET
        ERROR_QUIET
    )

    if(NOT REQUIREMENTS_INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to install python codec generation requirements.")
    endif()

    set(ZCBOR_COMMAND
        ${VENV_PYTHON} ${ZCBOR_DIR}/zcbor/zcbor.py code
        --decode --encode
        -c ${CDDL_FILE_PATH}
        --oc ${OUTPUT_DIR}/src/gen.c
        --oh ${OUTPUT_DIR}/include/gen.h
        --output-cmake ${OUTPUT_DIR}/cmake/gen.cmake
        --git-sha-header
        --time-header
        -t All
        --dq 1024
    )

    execute_process(COMMAND ${CMAKE_COMMAND} -E remove_directory ${OUTPUT_DIR})
    execute_process(
        COMMAND ${ZCBOR_COMMAND}
        RESULT_VARIABLE CODEC_GEN_RESULT
    )

    if(NOT CODEC_GEN_RESULT EQUAL 0)
        message(FATAL_ERROR "Error while generating codecs.")
    endif()
endfunction(generate_cddl_codec)



