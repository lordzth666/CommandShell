#!./csh
echo "[Test 09]: test input redirect"
cat test/benchmark.py 
echo "[Info]Testing test/benchmark.py as argument:"
./test-bin/test_echo test/benchmark.py
# Should print the content of benchmark.py
echo "[Info]Testing test/benchmark.py as redirected input:"
./test-bin/test_echo <test/benchmark.py
# Should print the content of benchmark.py
echo "[Info]Testing commandShell.txt as argument:"
./test-bin/stat_output commandShell.txt
# Should print the number of lines of commandShell.txt
echo "[Info]Testing commandShell.txt as redirected input:"
./test-bin/stat_output <commandShell.txt 
# Should print the number of lines of commandShell.txt
echo "[Info]Testing program caffe0 with redirected input/bad format:"
caffe0 <            test/numeric_test.txt
# Should print same result as caffe0_test in 01_test_command.sh
echo "[Info]Corner case: bad file descriptor"
cat <
# Should report an error saying that file is not found
cat <unknown.txt
# Should report an error saying that file is not found
