#ifndef __TEST_H__KJAHC38DJ__
#define __TEST_H__KJAHC38DJ__

/* -------PROTOTYPES------- */
// Starts a testing sesssion
void start_tests(const char* msg);
// Ends a testing session
void end_tests();
// Starts a testing sesssion on record.csv
void start_timer(const char* msg);
// Ends a testing session on record.csv
void end_timer();
// Calls a testing function. The given test function should
// exit the program with an error if the test does not succeed.
void test(void (*test_fun)());
#endif
