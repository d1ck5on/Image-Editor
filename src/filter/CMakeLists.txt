add_library(Filter 
                    CompositeFilter.cpp 
                    ChannelWiseFilter.cpp 
                    NegativeFilter.cpp
                    ConvolutionFilter.cpp
                    CropFilter.cpp
                    GrayscaleFilter.cpp
                    SharpeningFilter.cpp
                    ThresholdFilter.cpp
                    EdgeDetectionFilter.cpp)

target_link_libraries(Filter 
                        Image)

target_include_directories(Filter
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )