macro(generate_clang_complete)
  message(STATUS "Generarating ${CMAKE_SOURCE_DIR}/.clang_complete")

  set(CLANG_COMPLETE ${CMAKE_SOURCE_DIR}/.clang_complete)

  get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
  file(WRITE ${CLANG_COMPLETE} "")
  foreach(dir IN LISTS dirs)
    file(APPEND ${CLANG_COMPLETE} "-I${dir}\n")
  endforeach()

  separate_arguments(flags UNIX_COMMAND "${CMAKE_CXX_FLAGS}")
  separate_arguments(cflags UNIX_COMMAND "${CMAKE_C_FLAGS}")
  list(APPEND flags ${cflags})
  list(REMOVE_DUPLICATES flags)
  list(FILTER flags EXCLUDE REGEX [[^-W]])
  foreach(flag IN LISTS flags)
    file(APPEND ${CLANG_COMPLETE} "${flag}\n")
  endforeach()
endmacro()
