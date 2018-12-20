#!./csh
echo "[Test 04: test escape character]"
echo "[Info]Testing simple argument counter:"
./test-bin/test_argcnt 0 1 2
# Should print 3
echo "[Info]Testing argument counter with \\  between parameters:"
./test-bin/test_argcnt 0\ 1 2
# Should print 2 because \ is a escape space
echo "[Info]Testing argument counter with no parameters but spaces:"
./test-bin/test_argcnt                              
# Shoule print 0
echo "[Info]Testing argument counter with \\  and \\t mixed between parameters:"
./test-bin/test_argcnt 0 \ \t1\t2
# Should print 2 because there is a real space between 0 and 1, and \t between 1 and 2
echo "[Info]Testing argument counter with various parameters:"
./test-bin/test_argcnt 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
# Should print 21
echo "[Info]Testing argument counter with white spaces and \\t only:"
./test-bin/test_argcnt                   \t                \t
# Should print 2 because there are 2 \t escape characters.
echo "[Info]Testing argument counter with white spaces and parameters"
./test-bin/test_argcnt             1              2 3 4\ 5\ 
# Should print 4
echo "[Info]Testing argument counter with quotation marks"
./test-bin/test_argcnt             '1              2 3 4\ 5\'
# Should print 1
./test-bin/test_argcnt             "1              2 3 4\ 5\""
# Should print 1
