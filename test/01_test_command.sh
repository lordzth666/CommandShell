#./csh
echo "[Test 01: test command]"
# These are usual commands and should produce output as expected in shell.
echo "[Info]Testing with command export:"
export
# Should see environment variables
echo "[Info]Testing with command ls:"
ls
# Should see files and folders
echo "[Info]Testing with command /bin/ls:"
/bin/ls
# Should see the same results
echo "[Info]Testing with command fc:(redirected to $PROJECT_ROOT/tool-bin/fc)"
fc
# Should see exit code 1 because of bad usage
echo "[Info]Testing with ./test-bin/hello_world:"
./test-bin/hello_world
# Should see "hello world"
# should produce exit code 0, suppressed with FLAG -DSPREDUND
echo "[Info]Testing with a program which has segmentation fault:"
./test-bin/seg_fault
# should produce killed by 11 for SEG_FAULT
echo "[Info]Testing with an unknown command:"
./unknown
# should print "./unknown: command not found."
unknown
# should print "unknown: command not found."
echo "[Info]Testing with a prebuilt program using alias:"
echo "[Test: Easter egg]"
caffe0_test
# should perform integral on f(x,y) = x*2+y with step=0.001, x in range(-1,1),
# y in range(4,5) using the pre-built executable.
