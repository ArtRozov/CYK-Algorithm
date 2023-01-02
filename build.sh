mkdir cmake_build
cd cmake_build || return
cmake ..
cmake --build .
cd ../bin
./Test
./FormalPrac2
cd ..
lcov -t /cmake_build/CMakeFiles/FormalPrac2.dir/"main.cpp" -o main.info -c -d .
genhtml -o report main.info
lcov -t /cmake_build/CMakeFiles/CYK_Parser.dir/src/"CYK_Parser.cpp" -o cyk.info -c -d .
genhtml -o report cyk.info
lcov -t /cmake_build/CMakeFiles/Grammar.dir/src/"Grammar.cpp" -o grammar.info -c -d .
genhtml -o report grammar.info
lcov -t /cmake_build/CMakeFiles/States.dir/src/"States.cpp" -o states.info -c -d .
genhtml -o report states.info
