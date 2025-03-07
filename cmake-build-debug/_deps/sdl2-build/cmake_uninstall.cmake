if (NOT EXISTS "/Users/easn/Library/CloudStorage/OneDrive-個人/catmario/cmake-build-debug/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"/Users/easn/Library/CloudStorage/OneDrive-個人/catmario/cmake-build-debug/install_manifest.txt\"")
endif(NOT EXISTS "/Users/easn/Library/CloudStorage/OneDrive-個人/catmario/cmake-build-debug/install_manifest.txt")

file(READ "/Users/easn/Library/CloudStorage/OneDrive-個人/catmario/cmake-build-debug/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach(file)

