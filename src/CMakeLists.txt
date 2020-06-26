add_executable(TinyAssemblyInterpreter main.c)

add_library(ASM_INT STATIC asm_int.c)
add_library(VECTOR SHARED vector/vector.c)
add_library(MAP SHARED map/map.c)
add_library(PARSER STATIC parser/parser.c)
add_library(EXECUTE STATIC execute/execute.c)

target_link_libraries(PARSER LINK_PUBLIC VECTOR MAP)
target_link_libraries(EXECUTE LINK_PUBLIC VECTOR)
target_link_libraries(ASM_INT LINK_PUBLIC VECTOR PARSER EXECUTE)
target_link_libraries(TinyAssemblyInterpreter LINK_PUBLIC VECTOR ASM_INT)