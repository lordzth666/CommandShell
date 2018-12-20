#!./csh
echo "[Test 05: test set command]"
echo "[Info]Testing with normal set opearion:"
cd ~
set a "aaa"
set      b "bbb"
echo $a
# Should print "aaa"
echo      $b
# Should print "bbb"
echo "[Info]Testing with escape character in variable name:"
set a_c "ccc"
set a_d "ddd"
echo $ac
# Should print ""
echo $a_c
# Should print "ccc"
echo $a \ d
# Should print "aaa  d"
echo $a\ d
# Should print ""
echo "[Info]Testing with space in value:"
set a hello world
echo $a
# Should print "hello world"
echo "[Info]Testing with existing environment variables:"
set hpd $AUTHOR
echo $hpd
# Should print "$AUTHOR" in .cshrc, thus should print "THZHANG" by default
set fwd $HOME/ece551/
cd $fwd/mp_miniproject
pwd
# Should print /home/tz86/ece551/mp_miniproject
set var1 a
set var2 b
echo "[Info]Testing weird combinations:"
echo $var1$var2
# Should print ab
echo $var1-$var2
# Should print a+b
echo $var1-$var2
# Should print a+b
echo $var1:$var2
# Should print a:b
echo "[Info]Testing invalid variable name:"
set 1var1 a
# Should report error
set -var2 b
# Should report error
