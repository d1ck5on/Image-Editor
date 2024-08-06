add_library(Format BinaryReader.cpp BMP.cpp ImageFormat.cpp BinaryWriter.cpp)

target_include_directories(Format
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )

target_link_libraries(Format Image)