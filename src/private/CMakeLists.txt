add_library(zutils zutils.cpp)
target_link_libraries(zutils)

add_library(z_asm asm.cpp)
target_link_libraries(z_asm)

add_library(z_dism dism.cpp)
target_link_libraries(z_dism)
