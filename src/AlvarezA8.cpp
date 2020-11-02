//============================================================================
// Name        : AlvarezA8.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;

void buildArray(int [], int ,string);
void displayArray(int [],int , int);
bool checkIfHeap(int [],int, int);
void heapSort(int [],int, int);
void buildHeap(int [],int, int);
void heapify(int [], int, int);



void buildArray(int array[],int arraySize, string textFileLoco){
	ifstream textFile;
	textFile.open(textFileLoco);				//this takes a windows file location and opens it as an inputstream

	int i = 0;									//i is used to go through all array spots
	int spot = 0;								//spot is used to iterate by three characters, so we add 3 each iteration
	string line;
	getline(textFile,line,'\n');				//file is only 1 line so we grab one line of the file
	while(i<arraySize){
		array[i] = stoi(line.substr(spot,3));	//turning our substrings into integers for the array
		//cout << array[i] <<endl; <- making sure it grabbed ints correctly :D
		i++;
		spot += 3;

	}
	textFile.close();							// always remember to close your files

}

void displayArray(int array[], int low, int high){

	for(int i = low;i<(high+1)/10;i++){			//upper limit is high+1/10 because an index of 99/10 would only be 9 rows
		for(int j = 0; j<10 ; j++){				//this is to get us 10 per row
			cout << array[i*10+j] << " , " ;	//i*10 to get us to the correct tens digit and add j to get to correct ones digit
		}
		cout <<endl;							//new line every 10 items
	}
}

bool checkIfHeap(int array[],int low, int high){

	if(low < (high -2)/2){						// the current low is lower than the last parent, checks out
		return true;
	}
	if (array[low] >= array[2*low + 1] && array[low] >= array[2*low + 2] && checkIfHeap(array, 2*low + 1, high) && checkIfHeap(array, 2*low + 2, high)) { // recursively checking the leafs of each parent for every parent
	    return true;
	}

	return false;
}

void heapSort(int array[], int low, int high){
	int temp;
	buildHeap(array, low, high);
	for(int finalEl = high;finalEl >= 0;finalEl--){		// we start from the rear and sort 'Downwards'
		temp = array[0];
		array[0] = array[finalEl];
		array[finalEl] = temp;
		heapify(array, 0, finalEl-1);         		    // takes finalEl - 1 because we want to heapify the tree by the last node to the second to last by LEVEL of tree
	}
}

void buildHeap(int array[], int low , int high){	//
	int length = high +1;
	for (int i = (length/2)-1;i>=0; i--){   //this i starts at the middle of the array, which should be the last parent
		heapify(array, i, high);
	}
}

void heapify(int array[], int low,int high){	//turns the subtree into a heap
	int temp;
	int temp2;
	int largeIndex;
	temp = array[low];							// start at the lower index
	largeIndex = 2*low +1;						//this is to get us to the first leaf
	while(largeIndex <=high){					//if greater than high, we are out of bounds
		if(largeIndex< high){					//should always hit
			if(array[largeIndex]<array[largeIndex+1]){    //makes sure that the next node isnt larger than prev
				largeIndex = largeIndex + 1;				//if it is we move our upper index up one
			}
		}
		if(temp > array[largeIndex]){				//now if the lower index is larger than the leaf(which it should) we exit the while loop
			break;
		}
		else{										//if it isnt, we swap the parent and leaf that our in opposite places
			temp2 = array[low];
			array[low] = array[largeIndex];
			array[largeIndex] = temp2;
			low = largeIndex;						//these two lines "reset" our index and move up our leaf index (2x+1)
			largeIndex = 2 * low +1;
		}
	}
}

int main() {
	int low, high;
	low = 0;              	// low array index
	high = 99;			 	// high array index
	bool b;
	int list[100];
	string p ="c:/CS20/a81data.txt";
	cout << "main: building first array (from a81data.txt)" << endl;
	buildArray (list, 100, p);
	cout << "main: displaying first array" << endl << endl;
	displayArray (list, low, high);
	cout << endl;
	b=checkIfHeap (list, low, high);
	if (b)cout << "main: the first array is already a heap" << endl << endl;
	else
		cout << "main: the first array is not a heap" << endl << endl;
	cout << "main: now building heap" << endl;
	buildHeap (list, low, high);
	cout << "main: now displaying first array after heaping" << endl << endl;
	displayArray (list, low, high);
	b=checkIfHeap (list, low, high);
	if (b)
		cout << endl << "main: after heaping, the first array is a heap" << endl << endl;
	else{
		cout << endl << "main: after heaping, the first array is not a heap" << endl;
		return 4;
	}
	p ="c:/CS20/a82data.txt";
	cout << "main: building second array (from a82data.txt)" << endl;
	buildArray (list, 100, p);
	cout << "main: displaying second array" << endl << endl;
	displayArray (list, low, high);
	heapSort (list, low, high);

	cout << endl << "main: displaying second array, which should now be sorted" << endl << endl;
	b=checkIfHeap (list, low, high);
		if (b)
			cout << endl << "main: after heaping, the second array is a heap" << endl << endl;
		else{
			cout << endl << "main: after heaping, the second array is not a heap" << endl;
			return 4;
		}
	displayArray (list, low, high);




	return 0;
}
