set( SRC "BlockToMatrixUtils.c"
         "BlockToVectorUtils.c"
         "MatrixUtils.c"
         "VectorUtils.c"
         "algorithms.c"
)

add_library(mvoputils STATIC ${SRC})
target_include_directories(mvoputils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(mvoputils PUBLIC c_std_11)
target_link_libraries(mvoputils PRIVATE m)
