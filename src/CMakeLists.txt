MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

foreach(project ${SUBDIRS})
	message("subdir: ${project}")
	file(GLOB
		${project}-sources
		RELATIVE
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}/${project}/*
	)
	message("${project} sources: ${${project}-sources}")
	add_executable( ${project} "${${project}-sources}" )
	add_dependencies( ${project} game )
	target_link_libraries( ${project} ${GAME_LIBS} )
endforeach()
