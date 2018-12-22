#!./csh
echo "[Test 02: Test path]"
echo "[Info]Testing default ls..."
ls
# Backup
echo "[Info]Showing current PATH variable:"
echo $PATH
# Testing with ls1
echo "[Info]Adding a spurious path to the prior of PATH:"
set PATH ./test/ls_project/ls1:$PATH
export PATH
echo $PATH
# should see $PROJECT_ROOT/test/ls_project/ls1 at the head of $PATH
echo "[Info]Testing ls..."
ls
# should call $PROJECT_ROOT/test/ls_project/ls1/ls and print the corresponding message
# Testing with ls
echo "[Info]Adding a spurious path to the prior of PATH:"
set PATH ./test/ls_project/ls2:$PATH
export PATH
echo $PATH
# should see $PROJECT_ROOT/test/ls_project/ls2 at the head of $PATH
echo "[Info]Testing ls..."
ls
# should call $PROJECT_ROOT/test/ls_project/ls2/ls and print the corresponding message
# Testing with ls3
echo "[Info]Adding a spurious path to the priority of PATH:"
set PATH ./test/ls_project/ls3:$PATH
export PATH
echo $PATH
# should see $PROJECT_ROOT/test/ls_project/ls3 at the head of $PATH
echo "[Info]Testing ls..."
ls
# should call $PROJECT_ROOT/test/ls_project/ls3/ls and print the corresponding message
# Testing with ls4
echo "[Info]Adding a spurious path to the prior of PATH:"
set PATH ./test/ls_project/ls4:$PATH
export PATH
echo $PATH
# should see $PROJECT_ROOT/test/ls_project/ls4 at the head of $PATH
echo "[Info]Testing ls..."
ls
# should call $PROJECT_ROOT/test/ls_project/ls4/ls and print the corresponding message
# Testing with ls5
echo "[Info]Adding a spurious path to the prior of PATH:"
set PATH ./test/ls_project/ls5:$PATH
export PATH
echo $PATH
# should see $PROJECT_ROOT/test/ls_project/ls5 at the head of $PATH
echo "[Info]Testing ls..."
ls
# should call $PROJECT_ROOT/test/ls_project/ls5/ls and print the corresponding message
echo $PATH
# should see $PATH unchanged

# Recover the original PATH
set PATH $PATH
