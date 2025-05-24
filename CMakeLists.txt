cmake_minimum_required(VERSION 3.10)

project(SatSolverAI CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

add_executable(sat_solver_ai ${SOURCES})

target_include_directories(sat_solver_ai PUBLIC ${INCLUDE_DIR})

# CTest için testleri etkinleştir
enable_testing()

set(TEST_DIR test)
set(SAT_SOLVER_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/sat_solver_ai) # Çalıştırılabilir dosya build klasöründe

file(GLOB_RECURSE TEST_FILES "${TEST_DIR}/*.cnf")

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    add_test(
        NAME ${TEST_NAME}
        COMMAND ${SAT_SOLVER_EXECUTABLE} ${TEST_FILE}
    )
endforeach()