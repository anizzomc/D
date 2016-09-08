#!/usr/bin/env bash
FILES=$(find test/src -name "*.c")

echo '

/* This is auto-generated code. Edit at your own peril. */
#include <stdio.h>
#include <stdlib.h>

#include "../cutest/CuTest.h"

'

for f in $FILES
do
	cat $f | grep '^void Test' | 
    	sed -e 's/(.*$//' \
        	-e 's/$/(CuTest*);/' \
        	-e 's/^/extern /'
done

echo \
'

void RunAllTests(void) 
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

'
for f in $FILES
do
	cat $f | grep '^void Test' | 
	    sed -e 's/^void //' \
	        -e 's/(.*$//' \
	        -e 's/^/    SUITE_ADD_TEST(suite, /' \
	        -e 's/$/);/'
done

echo \
'
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    CuStringDelete(output);
    CuSuiteDelete(suite);
}

int main(void)
{
    RunAllTests();
}
'
