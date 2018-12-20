#!./csh
echo "[Test 06 Test export and env command]"
echo "[Info]Print the current Environment variables:"
env
# Should print all the existent environment variables
echo "[Info]Testing with normal export operation:"
set TEST_NAME EXPORT_TEST
set TEST_PLUS ${TEST_NAME}/PLUS
echo ${TEST_PLUS}
# Should print "EXPORT_TEST/PLUS"
echo "[Info]Before export:"
env
# Should print all the environment variables without $TEST_FPLUS, $TEST_PLUS
export TEST_FPLUS
export TEST_PLUS
echo "[Info]After export:"
env
# Should print all the environment variables with $TEST_PLUS
echo "[Info]Testing with setting an existent variable:"
set TEST_PLUS "hello"
echo "[Info]Before export:"
env
# Should see value changed to "hello"
export TEST_PLUS
echo "[Info]After export:"
env
# Should see the same result
