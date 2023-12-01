
#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

#include "dlist.h"
using namespace Project2;

#include "UnitTest++.h"

TEST(beginEnd_vectorFromDlist)
{
	string data[] = { "the", "quick", "brown", "fox" };
	dlist<string> ls(data, data + sizeof(data) / sizeof(*data));
	vector<string> v(ls.begin(), ls.end());

	CHECK(equal(v.begin(), v.end(), ls.begin()));
}

static bool isEven(short s)
{
	return s % 2 == 0;
}

TEST(copyIf)
{
	// Source data
	short sourceData[] = { 1, 2, 3, 4, 5, 6 };
	dlist<short> sourceLs(
		sourceData,
		sourceData + sizeof(sourceData) / sizeof(*sourceData));

	// Copy to destination
	dlist<short> result;
	copy_if(sourceLs.begin(), sourceLs.end(), back_inserter(result), isEven);

	// Verify result contains filtered data
	short expectedData[] = { 2, 4, 6 };
	dlist<short> expected(
		expectedData,
		expectedData + sizeof(expectedData) / sizeof(*expectedData));

	CHECK(equal(result.begin(), result.end(), expected.begin()));
}

TEST(find)
{
	// Source data
	short data[] = { 1, 2, 3, 4, 5, 6 };
	dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

	// Find the 2
	dlist<short>::iterator i = find(ls.begin(), ls.end(), 2);

	// Verify result
	CHECK(i != ls.end());
	dlist<short>::iterator pos(ls.begin());
	CHECK(i == ++pos);
}

TEST(accumulate)
{
   const int EXPECTED_RESULT = 55;

   dlist<int> dl;
   dlist<int>::iterator i;
   i = dl.insert(dl.begin(), 5);
   i = dl.insert(i, 4);
   i = dl.insert(i, 3);
   i = dl.insert(i, 2);
   i = dl.insert(i, 1);
   dl.insert(dl.end(), 6);
   dl.insert(dl.end(), 7);
   dl.insert(dl.end(), 8);
   dl.insert(dl.end(), 9);
   dl.insert(dl.end(), 10);

   CHECK(EXPECTED_RESULT == accumulate(dl.begin(), dl.end(), 0));
}

void reverseString(string &s)
{
   reverse(s.begin(), s.end());
}

TEST(for_each)
{
   string inputData[] = { "the", "quick", "brown", "fox" };
   dlist<string> dlInput(inputData, inputData + 4);
   string resultData[] = { "eht", "kciuq", "nworb", "xof" };
   dlist<string> dlResult(resultData, resultData + 4);

   for_each(dlInput.begin(), dlInput.end(), reverseString);

   CHECK(dlResult == dlInput);
}

int square(int i)
{
   return i * i;
}

TEST(transform)
{
   int inputData[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
   dlist<int> dlInput(inputData, inputData + 10);
   int resultData[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
   deque<int> dqResult(resultData, resultData + 10);

   deque<int> dqTransformed;
   transform(dlInput.begin(),
             dlInput.end(),
             back_inserter(dqTransformed),
             square);

   CHECK(dqResult == dqTransformed);
}

int main()
{
   return UnitTest::RunAllTests();
}
