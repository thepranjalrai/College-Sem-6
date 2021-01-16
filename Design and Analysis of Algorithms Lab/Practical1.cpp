#include <iostream>
#include <chrono>		// duration()
#include <stdlib.h>     // srand(), rand()
#include <time.h>       // time()
#include <math.h>		// sqrt()
#include <algorithm>	// sort()

using namespace std;
using namespace chrono;

const int size_1 = 25000;	//Array to be searched from
const int keys_size = 20;	//Keys to be searched

int array_1[size_1];
int keys[keys_size] = {324, 69, 9930, 1324, 2555, 8765, 7, 5221, 4912, 1169,
					   347, 432, 22, 9932, 123, 69420, 2301, 9291, 48, 4322};

float linear_times[keys_size];	//Arrays to store time duration per search operation per algorithm
float binary_times[keys_size];

void fill_elements(int* array, int size)	//Function to randomly initialize sample arrays
{
	float k = 2;

	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		array[i] = rand() % (3 * size) + (size / k);
		k = int(sqrt(array_1[i])*3.14);
	}
}

int linear_search(int* array, int size, int key)	//Linear search function
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == key)
			return i;
	}

	return -1;
}

int binarySearch(int arr[], int l, int r, int x) //Binary Search function
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

int main()		//Driver function
{
	fill_elements(array_1, size_1);		//Initialize sample array
	sort(array_1, array_1 + size_1);	//Sort the sample array

	cout << "\nEXECUTING\n";

	for (int i = 0; i < keys_size; i++)	//Evaluating Linear Search
	{
		auto start = high_resolution_clock::now();					//Start timing
		int index = linear_search(array_1, size_1, keys[i]);		//Perform search
		auto stop = high_resolution_clock::now();					//Stop timing
		auto duration = duration_cast<nanoseconds>(stop - start);
		linear_times[i] = duration.count();							//Save time period

		if (index >= 0) cout << i << "] " << "Found " << keys[i] << " at : i = " << index << endl; //Print which keys are found
	}

	for (int i = 0; i < keys_size; i++)	//Evaluating Binary Search, similarly as above 
	{
		auto start = high_resolution_clock::now();
		int index = binarySearch(array_1, 0, size_1-1, keys[i]);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		binary_times[i] = duration.count();
	}

	cout << "\nKEYS\n";		//Display Keys
	for(int x : keys) cout << x << "\t";
	cout << endl;

	cout << "\nTime periods in LINEAR SEARCH (ns)\n";	//Display time periods of linear search
	float sum = 0;
	float linear_avg;
	for (int i = 0; i < keys_size; i++)
	{
		cout << linear_times[i] << "\t";
		sum += linear_times[i];

	}
	linear_avg = sum / keys_size;						//Calculate average 

	cout << "\nTime periods in BINARY SEARCH (ns)\n";	//Display time periods of binary search
	sum = 0;
	float binary_avg;
	for (int i = 0; i < keys_size; i++)
	{
		cout << binary_times[i] << "\t";
		sum += binary_times[i];
	}
	binary_avg = sum / keys_size;						//Calculate average

	cout << "\n\nANALYSIS\n";
	cout << "Evaluated on same dataset and keyset.\n\n";
	cout << "Data set size : " << size_1 << endl;
	cout << "Key count : " << keys_size << endl;

	cout << "\nAverage Linear Search time = " << linear_avg << "ns";
	cout << "\nAverage Binary Search time = " << binary_avg << "ns";

	cout << "\n\n\n............................";
}