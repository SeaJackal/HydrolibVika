set(LIBRARY_NAME HydrolibFixedPoint)

add_library(${LIBRARY_NAME} INTERFACE)

target_include_directories(${LIBRARY_NAME} INTERFACE include)

include(${HYDROLIB_ROOT_DIR}/cmake/HydrolibGTest.cmake)
hydrolib_add_tests_for_target(${LIBRARY_NAME})

option(BUILD_BENCHMARKS "Build arithmetic benchmarks" OFF)

if(BUILD_BENCHMARKS)
    find_package(benchmark CONFIG REQUIRED)

    add_executable(BenchmarkFixedPoint
        benchmarks/benchmark_fixed_point_shift.cpp
    )

    target_link_libraries(BenchmarkFixedPoint PRIVATE
        ${LIBRARY_NAME}
        benchmark::benchmark
    )

    target_compile_options(BenchmarkFixedPoint PRIVATE -Wall -Wextra -Wpedantic -Wc++20-compat
            -Wno-format-security -Woverloaded-virtual -Wsuggest-override -fno-exceptions -fno-rtti)
endif()
