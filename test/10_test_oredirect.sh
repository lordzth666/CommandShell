#!./csh
echo "[Test 10: test output redirect]"
set test_cnt 5
set tmp_file tmp/test_output.tmp
echo "[Info]Testing random generator..."
echo "[Info]Output to stdout:"
./test-bin/random_generator $test_cnt
# Should print 5 random numbers on the screen
echo "[Info]Output to $tmp_file"
./test-bin/random_generator $test_cnt >$tmp_file
echo "[Info]Checking output..."
cat $tmp_file
# Should read 5 random numbers from the tmp file
echo "[Info]Testing range generator..."
echo "[Info]Output to stdout:"
./test-bin/range_generator $test_cnt
# Should print 0-4 consequently to output
echo "[Info]Output to $tmp_file"
./test-bin/range_generator $test_cnt >$tmp_file
echo "[Info]Checking output..."
cat $tmp_file
# Should see 0-4 consequently
echo "[Info]Testing append with random generator..."
./test-bin/random_generator $test_cnt >>$tmp_file
echo "[Info]Checking output..."
cat $tmp_file
# Should see 0-4 consequently and 5 random numbers follow
echo "[Info]Testing error redirection with random generator..."
./test-bin/random_generator 2>$tmp_file
echo "[Info]Checking output..."
cat $tmp_file
# Should see error message of ./test-bin/random_generator
echo "[Info]Testing output under error condition with random generator..."
./test-bin/random_generator >$tmp_file
echo "[Info]Checking output..."
cat $tmp_file
# Should see nothing
echo "[Info]Testing output redirection with another format..."
ls >     $tmp_file
cat $tmp_file
# Should see file list as well
echo "[Info]Testing stdout redirection with bad output file descriptor..."
cat >
# Should see an error message saying bad format
echo "[Info]Testing stderr redirection with bad output file descriptor..."
cat 2>
# Should see an error message saying bad format

rm -rf $tmp_file
