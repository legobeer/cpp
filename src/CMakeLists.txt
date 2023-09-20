add_library(particules Particule.cxx Vecteur.cxx Univers.cxx Euler.cxx Cellule.cxx)

find_package(TBB REQUIRED)
find_package(OpenMP REQUIRED)
target_compile_options(particules PUBLIC ${OpenMP_CXX_FLAGS})
target_link_libraries(particules PRIVATE TBB::tbb PUBLIC ${OpenMP_CXX_FLAGS})