SET(K3D_PYTHON_FOUND 0)

IF(APPLE)
	FIND_PROGRAM(PYTHON_EXECUTABLE
		NAMES python
		)

	IF(PYTHON_EXECUTABLE)
		EXECUTE_PROCESS(
			COMMAND ${PYTHON_EXECUTABLE} -c "import sys; sys.stdout.write(sys.prefix + '/include/python' + sys.version[:3])"
			OUTPUT_VARIABLE PYTHON_INCLUDE_PATH
			)
		EXECUTE_PROCESS(
			COMMAND ${PYTHON_EXECUTABLE} -c "import sys; sys.stdout.write(sys.exec_prefix + '/Python')"
			OUTPUT_VARIABLE PYTHON_LIBRARY
			)

		SET(K3D_PYTHON_INCLUDE_PATH
			${PYTHON_INCLUDE_PATH} CACHE PATH "Path to the directory containg Python header files."
			)

		SET(K3D_PYTHON_LIBRARY
			${PYTHON_LIBRARY} CACHE FILEPATH "Path to the Python link library."
			)

		MARK_AS_ADVANCED(K3D_PYTHON_INCLUDE_PATH)
		MARK_AS_ADVANCED(K3D_PYTHON_LIBRARY)
		MARK_AS_ADVANCED(PYTHON_EXECUTABLE)

		IF(K3D_PYTHON_INCLUDE_PATH AND K3D_PYTHON_LIBRARY)
			SET(K3D_PYTHON_INCLUDE_DIRS
				${K3D_PYTHON_INCLUDE_PATH}
				)

			SET(K3D_PYTHON_LIBS
				${K3D_PYTHON_LIBRARY}
				)

			SET(K3D_PYTHON_FOUND 1)
		ENDIF()
	ENDIF()
ELSE(APPLE)
	INCLUDE(FindPythonInterp)
	INCLUDE(FindPythonLibs)

	IF(PYTHONINTERP_FOUND AND PYTHONLIBS_FOUND)
		SET(K3D_PYTHON_INCLUDE_DIRS
			${PYTHON_INCLUDE_PATH}
			)

		SET(K3D_PYTHON_LIBS
			${PYTHON_LIBRARY}
			)

		MARK_AS_ADVANCED(PYTHON_INCLUDE_PATH)
		MARK_AS_ADVANCED(PYTHON_LIBRARY)
		MARK_AS_ADVANCED(PYTHON_DEBUG_LIBRARIES)
		MARK_AS_ADVANCED(PY_MODULES_LIST)
		MARK_AS_ADVANCED(PY_STATIC_MODULES_LIST)

		SET(K3D_PYTHON_FOUND 1)
	ENDIF()
ENDIF(APPLE)

