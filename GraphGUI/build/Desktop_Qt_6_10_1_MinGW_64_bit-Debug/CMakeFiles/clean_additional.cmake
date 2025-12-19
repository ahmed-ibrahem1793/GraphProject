# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\GraphGUI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GraphGUI_autogen.dir\\ParseCache.txt"
  "GraphGUI_autogen"
  )
endif()
