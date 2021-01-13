#include <iostream>
#include <chrono>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <algorithm>

using namespace std;
using namespace chrono;

const int size_1 = 5000;
int array_1[5000];
//const int size_2 = 10000;
//int array_2[10000];

const int keys_size = 10;
int keys[keys_size] = {324, 69, 9930, 1324, 2555, 8765, 7, 5221, 4912, 1169};

float linear_times[keys_size];
float binary_times[keys_size];

void fill_elements(int* array, int size)
{
	float k = 2;

	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		array[i] = rand() % (3 * size) + (size / k);
		k = int(sqrt(array_1[i])*3.14);
	}
}

int linear_search(int* array, int size, int key)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == key)
			return i;
	}

	return -1;
}

int binarySearch(int arr[], int l, int r, int x)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		if (arr[mid] == x)
			return mid;

		if (arr[mid] > x)
			return binarySearch(arr, l, mid - 1, x);

		return binarySearch(arr, mid + 1, r, x);
	}

	return -1;
}

int main()
{
	fill_elements(array_1, size_1);
	sort(array_1, array_1 + size_1);
	//fill_elements(array_2, size_2);
	//sort(array_2, array_2 + size_2);


	/*
	for (int i = 0; i < size_1; i++)
	{
		cout << array_1[i] << "\t";
		if (i % 22 == 0) { cout << endl; }
	}
	*/

	cout << "Performing LINEAR SEARCH of " << keys_size << " elements.\n\n";
	for (int i = 0; i < keys_size; i++)
	{
		auto start = high_resolution_clock::now();

		int index = linear_search(array_1, size_1, keys[i]);
		if (index >= 0) cout << "Found " << keys[i] << " at : i = " << index << endl;

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		//cout << "Time taken : " << duration.count() << "ms" << endl << endl;

		linear_times[i] = duration.count();
	}

	cout << "\n\nPerforming BINARY SEARCH of " << keys_size << " elements.\n\n";

	for (int i = 0; i < keys_size; i++)
	{
		auto start = high_resolution_clock::now();

		int index = binarySearch(array_1, 0, size_1-1, keys[i]);
		if(index >= 0) cout << "Found " << keys[i] << " at : i = " << index << endl;

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		//cout << "Time taken : " << duration.count() << "ms" << endl << endl;
		
		binary_times[i] = duration.count();
	}

	int sum = 0;
	int linear_avg;
	for (int i = 0; i < keys_size; i++)
	{
		sum += linear_times[i];
	}
	linear_avg = sum / keys_size;

	sum = 0;
	int binary_avg;
	for (int i = 0; i < keys_size; i++)
	{
		sum += binary_times[i];
	}
	binary_avg = sum / keys_size;

	cout << "\n\nANALYSIS\n";
	cout << "Evaluated on same dataset and keyset.\n\n";
	cout << "Data set size : " << size_1 << endl;
	cout << "Key count : " << keys_size << endl;

	cout << "\nAverage Linear Search time = " << linear_avg;
	cout << "\nAverage Binary Search time = " << binary_avg;

	cout << "\n\n\n............................";
}
