#!./csh
echo "[Test 11: test pipe]"
cd ~
echo "[Info]Testing ls with grep..."
ls | grep a
# Should see "workspace" if nothing else is created
echo "[Info]Adding a piped grep pattern..."
ls | grep a | grep b
# Should see nothing if nothing else is created, program exits with exitcode 1.
echo "[Info]Adding another grep pattern..."
ls | grep a | grep c
# Should see "workspace" if nothing else is created
echo "[Info]Testing a distorted pipe format..."
ls|grep a
# Should see "workspace" if nothing else is created
echo "[Info]Testing grep prime with small ranged input..."
cd $PROJECT_ROOT
cd test-bin
./range_generator 50 | ./grep_prime
# Should see "2\n3\n5\n7\n11\n13\n17\n19\n23\n29\n31\n37\n41\n43\n47\n" ( prime within 50)
echo "[Info]Testing a larger output for pipe within grep prime..."
./random_generator 10000 | head -n 500 | ./grep_prime | ./test_echo
# Should see many very large prime numbers(values vary by randomness (26 total this runtime)
./random_generator 10000 | head -n 500 | ./grep_prime | ./test_echo | ./stat_output
# Should see number of very large prime numbers(values vary by randomness (26 this runtime)
echo "[Info]Testing sending a very large output through pipe..."
./random_generator 200000 | tail -n 500 | ./grep_prime | ./test_echo | ./stat_output
# Should see number of very large prime numbers(values vary by randomness (21 this runtime)
./random_generator 500000 >tmp_output_size.txt
echo "[Info]Viewing size of original pipe..."
ll | grep tmp_output_size.txt
# Should see size for this file
rm -rf tmp_output_size.txt
./random_generator 500000 | tail -n 50000 | head -n 500 | ./grep_prime | ./test_echo >tmp_output.txt
cat tmp_output.txt
# Should see many very large prime numbers(values vary by randomness (21 total this runtime)
echo "[Info]Testing whole pipe from input redirection to output redirection..."
./test_echo <tmp_output.txt | head -n 1 | ./test_echo > tmp_output.txt
cat tmp_output.txt
# Should see first numver of previous file
echo "[Info]Testing with pipe in multiple lines..."
./random_generator     50 |
tail -n 30 | head -n 20 |
 ./grep_prime  | ./test_echo >tmp_output.txt
# Should see some very large prime numbers(values vary by randomness (2 total this runtime)
cat tmp_output.txt
echo "[Info]Testing with broken pipe with unknown command..."
./random_generator    50 | tail -n 30 | i_am_unknown | ./test_echo
# Should report unknown command error
echo "[Info]Testing with pipe after previous output is redirected..."
./random_generator 10 >tmp_output.txt | ./test_echo
# Should see nothing
echo "[Info]Viewing output..."
cat tmp_output.txt
# Should see the random numbers
echo "[Info]Testing with pipe after previous output is appended..."
./random_generator 10 >>tmp_output.txt | ./test_echo
# Should see nothing
echo "[Info]Viewing output..."
cat tmp_output.txt
# Should see random number two times

rm -rf tmp_output.txt
