MP_DIR=.
SHELL_DIR=${MP_DIR}
TEST_CPP_DIR=${MP_DIR}/test_examples
TOOL_DIR=${MP_DIR}/toolchain
TEST_DIR=${MP_DIR}/test

CMAKEFLAGS= -Wdeprecated -Wdev

.PHNOY: clean all test

all:
	make shell; make test
shell:
	@ echo "Building shell kernal..."
	cd ${SHELL_DIR};mkdir -p build; cd build; cmake .. ${CMAKEFLAGS}; make
	ln -sf build/csh .
	@ echo "Done."
	@ echo "Building toolchain..."
	cd ${TOOL_DIR};mkdir -p tool-bin;cd tool-bin;cmake .. ${CMAKEFLAGS};make
	@ echo " Adding prebuilt executable:"
	ln -sf ${TOOL_DIR}/tool-bin .
	@ echo "Done."

test: shell
	@ echo "Building test cpp..."
	cd ${TEST_CPP_DIR};mkdir -p test-bin; cd test-bin;cmake .. ${CMAKEFLAGS}; make
	ln -sf ${TEST_CPP_DIR}/test-bin .
	cd ${TEST_DIR}/ls_project;make all;
	cp -r ${TEST_CPP_DIR}/caffe0 ${MP_DIR}/tool-bin
	python3 test/benchmark.py
	@ echo "Done".

clean:
	cd ${SHELL_DIR}; rm -rf build
	cd ${TEST_CPP_DIR}; rm -rf test-bin
	cd ${TOOL_DIR}; rm -rf tool-bin
	cd ${TEST_DIR}/ls_project;make clean;
	rm -rf ./csh
	rm -rf ./test-bin
	rm -rf ./tool-bin
