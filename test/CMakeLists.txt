

enable_testing()

add_executable(testVecteur TestVecteur.cxx)
target_link_libraries(testVecteur particules gtest_main)

add_executable(testCellule TestCellule.cxx)
target_link_libraries(testCellule particules gtest_main)

add_executable(testInteractionFaible testInteractionFaible.cxx)
target_link_libraries(testInteractionFaible particules)

add_executable(testUnivers TestUnivers.cxx)
target_link_libraries(testUnivers particules gtest_main)

add_executable(haley Haley.cxx)
target_link_libraries(haley particules)

add_executable(testParticule TestParticule.cxx)
target_link_libraries(testParticule particules gtest_main)

include(GoogleTest)

gtest_discover_tests(testVecteur)
gtest_discover_tests(testCellule)
gtest_discover_tests(testParticule)
gtest_discover_tests(testUnivers)
