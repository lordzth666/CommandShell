#!./csh
echo "[Test 12: and beyond...]"
echo "[Info]Testing echo a string with space:" 
set a hello world
echo $a
echo $a | ./test-bin/test_length
# Should print 11

echo "[Info]Testing run with a non-existent .sh file"
run unknown.sh
# Should print error message: file not found.

cd $PROJECT_ROOT
echo "[Info]Testing entering a linked folder"
cd test-bin
pwd
# Should see "/home/tz86/ece551/mp_miniproject/test_examples/test-bin"  instead of "/home/tz86/ece551/mp_miniproject/test-bin"
cd ..
pwd
# Should see "/home/tz86/ece551/mp_miniproject/test_examples"
cd ..
pwd
# Should see "/home/tz86/ece551/mp_miniproject"
cd $PROJECT_ROOT

echo "[Info]Testing bad comment descriptor..."
# --------------------------------------------------
                   # a bad comment descriptor"
# Should raise no error
# --------------------------------------------------

echo "[Info]Printing author..."
echo THZHANG
# You have better not run this case unless you must
# Destructive case
# ------------------------------------
#echo "[Info]Running another Cshell"
#csh
# ------------------------------------
# Should see error message followed by "PROGRAM KILLED BY SIGNAL 6"
# This is because we cannot fetch environment variables in the newly-created csh
