# CMake generated Testfile for 
# Source directory: /Users/pitonmert/Documents/sat_solver_ai
# Build directory: /Users/pitonmert/Documents/sat_solver_ai/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(empty_clauses "/Users/pitonmert/Documents/sat_solver_ai/build/sat_solver_ai" "/Users/pitonmert/Documents/sat_solver_ai/test/empty_clauses.cnf")
set_tests_properties(empty_clauses PROPERTIES  _BACKTRACE_TRIPLES "/Users/pitonmert/Documents/sat_solver_ai/CMakeLists.txt;28;add_test;/Users/pitonmert/Documents/sat_solver_ai/CMakeLists.txt;0;")
add_test(hard_unsat "/Users/pitonmert/Documents/sat_solver_ai/build/sat_solver_ai" "/Users/pitonmert/Documents/sat_solver_ai/test/hard_unsat.cnf")
set_tests_properties(hard_unsat PROPERTIES  _BACKTRACE_TRIPLES "/Users/pitonmert/Documents/sat_solver_ai/CMakeLists.txt;28;add_test;/Users/pitonmert/Documents/sat_solver_ai/CMakeLists.txt;0;")
add_test(medium_sat "/Users/pitonmert/Documents/sat_solver_ai/build/sat_solver_ai" "/Users/pitonmert/Documents/sat_solver_ai/test/medium_sat.cnf")
set_tests_properties(medium_sat PROPERTIES  _BACKTRACE_TRIPLES "/Users/pitonmert/Documents/sat_solver_ai/CMakeLists.txt;28;add_test;/Users/pitonmert/Documents/sat_solver_ai/CMakeLists.txt;0;")
add_test(simple_sat "/Users/pitonmert/Documents/sat_solver_ai/build/sat_solver_ai" "/Users/pitonmert/Documents/sat_solver_ai/test/simple_sat.cnf")
set_tests_properties(simple_sat PROPERTIES  _BACKTRACE_TRIPLES "/Users/pitonmert/Documents/sat_solver_ai/CMakeLists.txt;28;add_test;/Users/pitonmert/Documents/sat_solver_ai/CMakeLists.txt;0;")
add_test(simple_unsat "/Users/pitonmert/Documents/sat_solver_ai/build/sat_solver_ai" "/Users/pitonmert/Documents/sat_solver_ai/test/simple_unsat.cnf")
set_tests_properties(simple_unsat PROPERTIES  _BACKTRACE_TRIPLES "/Users/pitonmert/Documents/sat_solver_ai/CMakeLists.txt;28;add_test;/Users/pitonmert/Documents/sat_solver_ai/CMakeLists.txt;0;")
