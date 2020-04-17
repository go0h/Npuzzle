cmake_minimum_required(VERSION 3.13)
project(Npuzzle VERSION 0.1 LANGUAGES C CXX)

# добавляем поддержку C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(include)

set(SOURCE_DIR src)

set(SOURCE
	${SOURCE_DIR}/Main.cpp
	${SOURCE_DIR}/Node.cpp
	${SOURCE_DIR}/NodeUtils.cpp
	${SOURCE_DIR}/NodeOperators.cpp
	${SOURCE_DIR}/PuzzExcept.cpp
	${SOURCE_DIR}/ReadPuzzle.cpp
	${SOURCE_DIR}/NodeHeuristic.cpp
	${SOURCE_DIR}/NodeMove.cpp
	${SOURCE_DIR}/ASearchOptimal.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})


# Включаем поддержку тестирования
enable_testing()

# Добавляем тесты
set(BAD_TEST_DIR ../tests/bad)
set(BAD_TEST_FILES bad_comm_1 bad_comm_2
	bad_order empty less_colums less_rows
	no_side one_line only_comment same_fields)

set(TEST_DIR ../tests)
set(TEST_FILES big_100 big_1000 f4_1 f4_2 f4_3 f4_4)

foreach(test IN LISTS BAD_TEST_FILES)
	add_test(${test} ${PROJECT_NAME} ${BAD_TEST_DIR}/${test})
	set_tests_properties(${test} PROPERTIES
	PASS_REGULAR_EXPRESSION "Error")
endforeach()

foreach(test IN LISTS TEST_FILES)
	add_test(${test} ${PROJECT_NAME} ${TEST_DIR}/${test})
	set_tests_properties(${test} PROPERTIES
	FAIL_REGULAR_EXPRESSION "Error")
endforeach()
