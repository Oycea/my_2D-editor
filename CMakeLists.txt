cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(2D_editor)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "-g")

add_executable(2D_editor src/main.cpp
						 src/Ishape.hpp
						 src/point/point.cpp 
						 src/point/point.hpp
						 src/segment/segment.cpp
						 src/segment/segment.hpp
						 src/triangle/triangle.cpp
						 src/triangle/triangle.hpp
						 src/quadrangle/quadrangle.cpp
						 src/quadrangle/quadrangle.hpp
						 src/ellipse/ellipse.cpp
						 src/ellipse/ellipse.hpp
						 src/data_structures/dllist.hpp
						 src/data_structures/stack.hpp
						 src/data_check/data_check.cpp
						 src/data_check/data_check.hpp
						 src/menu/menu.cpp
						 src/menu/menu.hpp)

add_executable(2D_editor_test src/data_structures_test/main_test.cpp
							  src/data_structures/dllist.hpp
							  src/data_structures_test/test.cpp
							  src/data_structures_test/test.hpp)

if(APPLE)
	target_link_libraries(2D_editor "-framework OpenGL" "-framework GLUT")
	target_compile_options(2D_editor PRIVATE -Wall)
	target_compile_options(2D_editor_test PRIVATE -Wall)
endif()

if (UNIX)
	find_package(OpenGL REQUIRED)
	find_package(GLUT REQUIRED)
	include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
	target_link_libraries(2D_editor ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
endif()
