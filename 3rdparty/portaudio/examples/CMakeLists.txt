# Example projects

MACRO(ADD_EXAMPLE appl_name)
<<<<<<< HEAD
   ADD_EXECUTABLE(${appl_name} "${appl_name}.c")
   TARGET_LINK_LIBRARIES(${appl_name} portaudio_static)
   SET_TARGET_PROPERTIES(${appl_name}
      PROPERTIES
      FOLDER "Examples C"
   )
ENDMACRO(ADD_EXAMPLE)

MACRO(ADD_EXAMPLE_CPP appl_name)
   ADD_EXECUTABLE(${appl_name} "${appl_name}.cpp")
   TARGET_LINK_LIBRARIES(${appl_name} portaudio_static)
   SET_TARGET_PROPERTIES(${appl_name}
      PROPERTIES
      FOLDER "Examples C++"
   )
=======
  ADD_EXECUTABLE(${appl_name} "${appl_name}.c")
  TARGET_LINK_LIBRARIES(${appl_name} portaudio_static)
  SET_TARGET_PROPERTIES(${appl_name} PROPERTIES FOLDER "Examples C")
  IF(WIN32)
    SET_PROPERTY(TARGET ${appl_name} APPEND_STRING PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS)
  ENDIF()
ENDMACRO(ADD_EXAMPLE)

MACRO(ADD_EXAMPLE_CPP appl_name)
  ADD_EXECUTABLE(${appl_name} "${appl_name}.cpp")
  TARGET_LINK_LIBRARIES(${appl_name} portaudio_static)
  SET_TARGET_PROPERTIES(${appl_name} PROPERTIES FOLDER "Examples C++")
  IF(WIN32)
    SET_PROPERTY(TARGET ${appl_name} APPEND_STRING PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS)
  ENDIF()
>>>>>>> upstream/master
ENDMACRO(ADD_EXAMPLE_CPP)

ADD_EXAMPLE(pa_devs)
ADD_EXAMPLE(pa_fuzz)
<<<<<<< HEAD
ADD_EXAMPLE(paex_mono_asio_channel_select)
ADD_EXAMPLE(paex_ocean_shore)
=======
IF(PA_USE_ASIO AND WIN32)
  ADD_EXAMPLE(paex_mono_asio_channel_select)
ENDIF()
ADD_EXAMPLE(paex_ocean_shore)
TARGET_INCLUDE_DIRECTORIES(paex_ocean_shore PRIVATE ../src/common)
>>>>>>> upstream/master
ADD_EXAMPLE(paex_pink)
ADD_EXAMPLE(paex_read_write_wire)
ADD_EXAMPLE(paex_record)
ADD_EXAMPLE(paex_record_file)
<<<<<<< HEAD
ADD_EXAMPLE(paex_saw)
ADD_EXAMPLE(paex_sine)
ADD_EXAMPLE_CPP(paex_sine_c++)
ADD_EXAMPLE(paex_wmme_ac3)
ADD_EXAMPLE(paex_wmme_surround)
=======
TARGET_INCLUDE_DIRECTORIES(paex_record_file PRIVATE ../src/common)
ADD_EXAMPLE(paex_saw)
ADD_EXAMPLE(paex_sine)
ADD_EXAMPLE_CPP(paex_sine_c++)
IF(PA_USE_WMME AND WIN32)
  ADD_EXAMPLE(paex_wmme_ac3)
  ADD_EXAMPLE(paex_wmme_surround)
ENDIF()
>>>>>>> upstream/master
ADD_EXAMPLE(paex_write_sine)
ADD_EXAMPLE(paex_write_sine_nonint)
