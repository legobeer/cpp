add_test( UniversTest.Constructor /home/antonin/cpp/build/test/testUnivers [==[--gtest_filter=UniversTest.Constructor]==] --gtest_also_run_disabled_tests)
set_tests_properties( UniversTest.Constructor PROPERTIES WORKING_DIRECTORY /home/antonin/cpp/build/test)
add_test( UniversTest.StromerVerlet /home/antonin/cpp/build/test/testUnivers [==[--gtest_filter=UniversTest.StromerVerlet]==] --gtest_also_run_disabled_tests)
set_tests_properties( UniversTest.StromerVerlet PROPERTIES WORKING_DIRECTORY /home/antonin/cpp/build/test)
add_test( UniversTest.addParticuleTest /home/antonin/cpp/build/test/testUnivers [==[--gtest_filter=UniversTest.addParticuleTest]==] --gtest_also_run_disabled_tests)
set_tests_properties( UniversTest.addParticuleTest PROPERTIES WORKING_DIRECTORY /home/antonin/cpp/build/test)
set( testUnivers_TESTS UniversTest.Constructor UniversTest.StromerVerlet UniversTest.addParticuleTest)
