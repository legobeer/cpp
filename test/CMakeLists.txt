add_executable(testVecteur TestVecteur.cxx)
target_link_libraries(testVecteur particules)

add_executable(testUnivers TestUnivers.cxx)
target_link_libraries(testUnivers particules)

add_executable(haley Haley.cxx)
target_link_libraries(haley particules)

add_executable(testParticule TestParticule.cxx)
target_link_libraries(testParticule particules)