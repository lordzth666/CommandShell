#!./csh
echo "[Test 07: test cd command]"
echo "[Info]Testing normal change directory operation:"
pwd
# Should print "/home/tz86/ece551/mp_miniproject"
cd ..
cd ..
pwd
# Should print "/home/tz86"
echo "[Info]Testing cd to an unknown area:"
cd unknown_area
# Should print "no such file or directory"
echo "[Info]PROJECT_ROOT:" $PROJECT_ROOT
echo "[Info]Change to PROJECT_ROOT:"
cd $PROJECT_ROOT
pwd
# Should print "/home/tz86/ece551/mp_miniproject"
echo "[Info]Testing with consecutive command:"
cd ../../../
pwd
# Should print "/home"
cd ../../../../../../../home
pwd
# Should print "/home"
cd /
pwd
# Should print "/"
echo "[Info]Testing with absolute path"
cd /usr/local/
pwd
# Should print "/usr/local"
echo "[Info]Testing with special empty cd, consecutive ./:"
cd ~/ece551
pwd
# Should print "/home/tz86/ece551"
cd
pwd
# Should print "/home/tz86"
cd .
pwd
# Should print "/home/tz86"
cd ./././././
pwd
# Should print "/home/tz86"
echo "[Info]Testing with absolute + relative path definition"
cd /usr/local/bin/..
pwd
# Should print "/usr/local"
