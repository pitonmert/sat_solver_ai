# CMake'in ihtiyaç duyduğu minimum versiyonu belirtir.
cmake_minimum_required(VERSION 3.10)

# Projenizin adını ve kullanılacak dili (C++) belirtir.
project(SatSolverAI CXX)

# C++ standardını C++20 olarak ayarlar ve bunun zorunlu olduğunu belirtir.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Kaynak (source) dosyalarının ve başlık (include) dosyalarının bulunduğu dizinleri tanımlarız.
set(SOURCE_DIR src)
set(INCLUDE_DIR include)

# 'src' dizini altındaki tüm .cpp dosyalarını otomatik olarak bulur ve SOURCES değişkenine atar.
# Bu, her yeni .cpp dosyası eklediğinizde CMakeLists.txt'i güncellemenize gerek kalmamasını sağlar.
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

# Bulunan tüm kaynak dosyalarını kullanarak "sat_solver_ai" adında bir çalıştırılabilir dosya oluşturur.
add_executable(sat_solver_ai ${SOURCES})

# "sat_solver_ai" çalıştırılabilir dosyasının başlık dosyalarını hangi dizinde arayacağını belirtiriz.
# PUBLIC, bu kütüphaneyi kullanan diğer modüllerin de bu başlık dizinini görmesi gerektiği anlamına gelir.
target_include_directories(sat_solver_ai PUBLIC ${INCLUDE_DIR})

# Çalıştırılabilir dosyanın (sat_solver_ai.exe) oluşturulduktan sonra hangi dizine kopyalanacağını ayarlarız.
# CMAKE_SOURCE_DIR, projenizin ana dizinini temsil eder. Böylece 'out' klasörüne kaydolur.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

# Testleri etkinleştirir.
enable_testing()

# Test dosyalarının bulunduğu dizin (projenizin köküne göre)
set(TEST_DIR test)

# Testlerin yürütülebilir dosyasının yolu
set(SAT_SOLVER_EXECUTABLE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sat_solver_ai)

# Her bir .cnf dosyası için ayrı bir test oluşturma
file(GLOB_RECURSE TEST_FILES "${TEST_DIR}/*.cnf")

foreach(TEST_FILE ${TEST_FILES})
    # Test adını dosya adından alır (örneğin: simple_sat.cnf -> simple_sat)
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE) # NAME_WE uzantısız dosya adını verir

    # add_test komutu ile CTest için yeni bir test tanımlarız.
    # COMMAND: Çalıştırılacak komut (bizim sat çözücümüz)
    # ARGS: Komuta geçilecek argümanlar (test dosyasının yolu)
    add_test(
        NAME ${TEST_NAME}
        COMMAND ${SAT_SOLVER_EXECUTABLE} ${TEST_FILE}
    )
endforeach()