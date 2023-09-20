

enable_testing()

add_executable(testVecteur TestVecteur.cxx)
target_link_libraries(testVecteur particules gtest_main)

add_executable(testCellule TestCellule.cxx)
target_link_libraries(testCellule particules gtest_main)

add_executable(testUnivers TestUnivers.cxx)
target_link_libraries(testUnivers particules gtest_main)

add_executable(haley Haley.cxx)
target_link_libraries(haley particules)

add_executable(testParticule TestParticule.cxx)
target_link_libraries(testParticule particules gtest_main)

add_executable(demoCollision DemoCollision.cxx)
target_link_libraries(demoCollision particules)

add_executable(performanceTest PerformanceTest.cxx)
target_link_libraries(performanceTest particules)

add_executable(testCollection TestCollection.cxx)
target_link_libraries(testCollection particules)

add_executable(testEuler TestEuler.cxx)
target_link_libraries(testEuler particules)

add_executable(trace trace.cxx)

add_executable(testAbsorption TestAbsorption.cxx)
target_link_libraries(testAbsorption particules)


add_executable(testPeriodique TestPeriodique.cxx)
target_link_libraries(testPeriodique particules)


add_executable(testRelflexion TestReflexion.cxx)
target_link_libraries(testRelflexion particules)
add_executable(testEnergieCinetique TestEnergieCinetique.cxx)
target_link_libraries(testEnergieCinetique particules)
add_executable(testVTKFile TestVTKFile.cxx)
target_link_libraries(testVTKFile particules)



include(GoogleTest)

gtest_discover_tests(testVecteur)
gtest_discover_tests(testCellule)
gtest_discover_tests(testParticule)
gtest_discover_tests(testUnivers)
