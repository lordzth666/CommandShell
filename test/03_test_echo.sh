#!/home/tz86/ece551/mp_miniproject/csh
echo "[Test 03: test echo]"
echo "[Info]Testing with a normal string:"
echo "Hello world!"
# Should print "Hello world!"
echo "[Info]Testing with a string with \\t in it:"
echo "Hello\tworld"
# Should print "Hello	world"
echo "[Info]Testing with non-escape case:"
echo '$HOME'
# Should print '$HOME'
echo "[Info]Testing with a string with \\\  in it:"
echo hello\ world
# Should print "hello world"
echo "[Info]Testing with a string with \\b in it:"
echo hello\bworld
# Should print "hellworld" due to the characteristics of \b
echo "[Info]Testing with a string which has multiple lines:"
echo 'hell
o
 
wo
rld'
# Should print "hello world"
echo "[Info]Testing with quotes combined:"
echo "\\aaccb\bd\'"
# should print \aaccd'
echo "\""
# should print "
echo "\\"
# should print \
echo "\\\""
# should print \"
echo "\\\'"
# should print \'
echo "a\ a"
# should print 'a a'
echo "a\                a"
# should print 'a                a'
echo a                  a
# should print a a
echo "\\""\\"
# should print \\
echo '\\''\\'
# should print \\\\
