# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\srgui_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\srgui_autogen.dir\\ParseCache.txt"
  "srgui_autogen"
  )
endif()
