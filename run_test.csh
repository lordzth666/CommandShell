#!./csh
set CSHRC .cshrc
source $CSHRC
run ./test/01_test_command.sh
source $CSHRC
run ./test/02_test_path.sh
source $CSHRC
run ./test/03_test_echo.sh
source $CSHRC
run ./test/04_test_escape.sh
source $CSHRC
run ./test/05_test_set.sh
source $CSHRC
run ./test/06_test_export.sh
source $CSHRC
run ./test/07_test_cd.sh
source $CSHRC
run ./test/08_test_inc.sh
source $CSHRC
run ./test/09_test_iredirect.sh
source $CSHRC
run ./test/10_test_oredirect.sh
source $CSHRC
run ./test/11_test_pipe.sh
source $CSHRC
run ./test/12_test_misc.sh
echo "Done."
