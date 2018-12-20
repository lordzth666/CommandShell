#!./csh
echo "[Test 08: test inc command]"
echo "[Info]Testing inc with a string:"
set a "hello"
inc a
echo $a
# Should print 1
echo "[Info]Testing inc with a float:"
set b 1.3
inc b
echo $b
# Should print 2
echo "[Info]Testing consecutive inc with a negative float:"
set c -2.9999
inc c
inc c
inc c
inc c
echo $c
# Should print 2
echo "[Info]Testing consecutive inc with an unset variable:"
set d
inc d
echo $d
# Should print 1
echo "[Info]Testing consecutive inc with an undefined variable:"
echo $e
# Should print ""
inc e
echo $e
# Should print 1
echo "[Info]Testing inc and watch the value change in env:"
export e
env
inc e
env
# Should see e value changes as is in bash
