/*
 * FrameTest.cpp
 *
 * Author: Christopher Gillis
 * Created on: October 8, 2015
 *
 * A simple test program to ensure that frames can be constructed and 
 * deconstructed properly.
 */

#include "Frame.h"
#include <iostream>
using std::cout;
using std::endl;
#include <cstdio>

int main()
{
	/* Test constructors */
	// Test with standard arguments
	Frame testFrame(1, "some test info", NOT_EOP);
	
	cout << "Seq Num: " << testFrame.getSeqNum() << endl
		 << "Payload: " << testFrame.getPayload() << endl;
	printf("End-of-packet byte (ASCII): %d\n\n", testFrame.getEOP());

	// Test with improper sequence and eop arguments 
	Frame testFrame2(100, "some other info", 'A');

	cout << "SeqNum: " << testFrame2.getSeqNum() << endl
		 << "Payload: " << testFrame2.getPayload() << endl;
	printf("End-of-packet byte (ASCII): %d\n\n", testFrame2.getEOP());

	// Test the boundaries of the payload
	Frame testFrame3(10023, "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50", 'B');

	cout << "SeqNum: " << testFrame3.getSeqNum() << endl
		 << "Payload: " << testFrame3.getPayload() << endl
		 << "Payload Length: " << strlen(testFrame3.getPayload()) << endl;
	printf("End-of-packet byte (ASCII): %d\n\n", testFrame3.getEOP());

	// Test the error detection bytes
	char testEd[2];
	testFrame.calcErrorDetect(testEd);

	cout << "Testing error detection" << endl;
	if (strncmp(testEd, testFrame.getEd(), 2) != 0)
	{
		cout << "Error detection works!" << endl;
	}
	else
	{
		cout << "Problem with error detection" << endl;
	}

	testFrame3.calcErrorDetect(testEd);
	if (strncmp(testEd, testFrame.getEd(), 2) == 0)
	{
		cout << "Still works!" << endl;
	}
	else
	{
		cout << "Problem with error detection" << endl;
	}

	if (strncmp(testEd, testFrame3.getEd(), 2) == 0)
	{
		cout << "Works completely!" << endl;
	}
	else
	{
		cout << "Problem with error detection" << endl;
	}

	/* Test constructing string from frame */
	cout << endl << "Testing string construction from frame" << endl;
	char frame_str[135];
	testFrame.constructFrame(frame_str);
	cout << frame_str << endl;

	/* Test deconstructing frame from string */
	cout << endl << "Testing frame construction from string" << endl;
	Frame strTestFrame;
	strTestFrame.deconstructFrame(frame_str);

	cout << "Seq Num: " << strTestFrame.getSeqNum() << endl
		 << "Payload: " << strTestFrame.getPayload() << endl;
	printf("End-of-packet byte (ASCII): %d\n", strTestFrame.getEOP());

	/* Test the error detection bytes */
	if (strncmp(strTestFrame.getEd(), testFrame.getEd(), 2) == 0)
	{
		cout << "We can construct and deconstruct frames!" << endl;
	}
	else
	{
		cout << "Problems in frame construction or deconstruction" << endl;
	}
	return 0;
}
