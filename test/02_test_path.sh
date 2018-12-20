#./csh
echo "[Test 02: Test path]"
echo "[Info]Testing default ls..."
ls
# Backup
echo "[Info]Showing current ece551path variable:"
echo $ECE551PATH
# Testing with ls1
echo "[Info]Adding a spurious path to the prior of ECE551PATH:"
set ECE551PATH /home/tz86/ece551/mp_miniproject/test/ls_project/ls1:$ECE551PATH
export ECE551PATH
echo $ECE551PATH
# should see $PROJECT_ROOT/test/ls_project/ls1 at the head of $ECE551PATH
echo "[Info]Testing ls..."
ls
# should call $PROJECT_ROOT/test/ls_project/ls1/ls and print the corresponding message
# Testing with ls
echo "[Info]Adding a spurious path to the prior of ECE551PATH:"
set ECE551PATH /home/tz86/ece551/mp_miniproject/test/ls_project/ls2:$ECE551PATH
export ECE551PATH
echo $ECE551PATH
# should see $PROJECT_ROOT/test/ls_project/ls2 at the head of $ECE551PATH
echo "[Info]Testing ls..."
ls
# should call $PROJECT_ROOT/test/ls_project/ls2/ls and print the corresponding message
# Testing with ls3
echo "[Info]Adding a spurious path to the priority of ECE551PATH:"
set ECE551PATH /home/tz86/ece551/mp_miniproject/test/ls_project/ls3:$ECE551PATH
export ECE551PATH
echo $ECE551PATH
# should see $PROJECT_ROOT/test/ls_project/ls3 at the head of $ECE551PATH
echo "[Info]Testing ls..."
ls
# should call $PROJECT_ROOT/test/ls_project/ls3/ls and print the corresponding message
# Testing with ls4
echo "[Info]Adding a spurious path to the prior of ECE551PATH:"
set ECE551PATH /home/tz86/ece551/mp_miniproject/test/ls_project/ls4:$ECE551PATH
export ECE551PATH
echo $ECE551PATH
# should see $PROJECT_ROOT/test/ls_project/ls4 at the head of $ECE551PATH
echo "[Info]Testing ls..."
ls
# should call $PROJECT_ROOT/test/ls_project/ls4/ls and print the corresponding message
# Testing with ls5
echo "[Info]Adding a spurious path to the prior of ECE551PATH:"
set ECE551PATH /home/tz86/ece551/mp_miniproject/test/ls_project/ls5:$ECE551PATH
export ECE551PATH
echo $ECE551PATH
# should see $PROJECT_ROOT/test/ls_project/ls5 at the head of $ECE551PATH
echo "[Info]Testing ls..."
ls
# should call $PROJECT_ROOT/test/ls_project/ls5/ls and print the corresponding message
echo $PATH
# should see $PATH unchanged

# Recover the original ECE551PATH
set ECE551PATH $PATH
