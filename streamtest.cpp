/*
Task:
Given stream of bits. Each bit represented as int.
1. Find pattern '1xxxxxxxx0' in stream
2. Extract 'xxxxxxxx' value
3. Print most frequent 'xxxxxxxx' value
*/

#include <ctime>
#include <stdio.h>
#include <stdlib.h>

const int StreamSize = 10000;
int stream[StreamSize];

const int GradientSize = 256;

// dec 510 == bin 0111111110
// dec 512 == bin 1000000000
// dec 513 == bin 1000000001

void init(int data[StreamSize]); // fill stream with random values
int parseStream_long(int data[StreamSize]);
int parseStream_short(int data[StreamSize]); // same as 'parseStream_long', but less LOC

int main(void)
{
	init(stream);

	printf("parseStream_short: %d\n", parseStream_short(stream));

	printf("parseStream_long : %d\n", parseStream_long(stream));

	return 0;
}

void init(int data[StreamSize])
{
	srand(time(NULL));
	for(int i = 0 ; i < StreamSize ; ++i)
		data[i] = rand() % 2;
}

int parseStream_short(int data[StreamSize])
{
	int counter[GradientSize] = {0};
	int mostFrequentValue = 0;
	for(int i = 0, reader = 0 ; i < StreamSize - 10 ; ++i, reader = ( reader << 1 ) | data[i], (reader & 513 ^ 512) ? 0 : (++counter[(reader & 510) >> 1], reader = 0) ) {}
	for(int i = GradientSize - 1 ; i > -1 ; (counter[i] > counter[mostFrequentValue]) ? (mostFrequentValue = i) : (0), --i) {}
	return mostFrequentValue;
}

int parseStream_long(int data[StreamSize])
{
	// extract values
	// fill gradient

	int counter[GradientSize] = {0}; // gradient
	int reader = 0; // stream reader

	for( int i = 0 ; i < StreamSize - 10 ; ++i ) // read stream
	{
		reader = ( reader << 1 ) | data[i]; // read next bit

		if( ! (reader & 513 ^ 512)) // check for '1xxxxxxxx0' pattern
		{
			++counter[ (reader & 510) >> 1 ]; // fill gradient
			reader = 0; // flush stream reader
		}
	}

	// find most frequent value (max in gradient)

	int mostFrequentValue = 0;
	
	for(int i = GradientSize - 1 ; i > -1 ; --i)
		if(counter[i] > counter[mostFrequentValue])
			mostFrequentValue = i;

	return mostFrequentValue;
}
