#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


/* function definitions */
void bubbleSort(vector<int>& a);
vector<int> merge_vectors(vector<int> vec1, vector<int> vec2);

int main (int argc, const char * argv[]) 
{
	int cut_num = 8;
	int input_num;
	vector<int> Input_list;

	while(cin >> input_num){
		Input_list.push_back(input_num);
	}
	int size = cut_num;

	vector<int> Split_input_list[size];
	int n = (Input_list.size() - 1) / cut_num + 1;
	for(int k = 0; k < size; ++k){
        auto start_itr = next(Input_list.cbegin(), k*n);
        auto end_itr = next(Input_list.cbegin(), k*n + n);
 
        Split_input_list[k].resize(n);
        if (k*n + n > Input_list.size()){
            end_itr = Input_list.cend();
            Split_input_list[k].resize(Input_list.size() - k*n);
        }
        copy(start_itr, end_itr, Split_input_list[k].begin());
	}

	//bubble sort
	int sort_pos = 0;
	for(vector<int> temp : Split_input_list){
		bubbleSort(temp);
		Split_input_list[sort_pos] = temp;
		sort_pos++;
	}

	Split_input_list[0] = merge_vectors(Split_input_list[0], Split_input_list[1]);
	Split_input_list[1] = merge_vectors(Split_input_list[2], Split_input_list[3]);
	Split_input_list[2] = merge_vectors(Split_input_list[4], Split_input_list[5]);
	Split_input_list[3] = merge_vectors(Split_input_list[6], Split_input_list[7]);


	Split_input_list[0] = merge_vectors(Split_input_list[0], Split_input_list[1]);
	Split_input_list[1] = merge_vectors(Split_input_list[2], Split_input_list[3]);

	Split_input_list[0] = merge_vectors(Split_input_list[0], Split_input_list[1]);

	for (int i : Split_input_list[0]){
		cout << i << ' ';
	}

  return 0;
}


void bubbleSort(vector<int>& a)
{
      bool swapp = true;
      while(swapp){
        swapp = false;
        for (size_t i = 0; i < a.size()-1; i++) {
            if (a[i]>a[i+1] ){
                a[i] += a[i+1];
                a[i+1] = a[i] - a[i+1];
                a[i] -=a[i+1];
                swapp = true;
            }
        }
    }
}

vector<int> merge_vectors(vector<int> vec1, vector<int> vec2){
	vector<int> vec3;
	vec3.reserve(vec1.size() + vec2.size());
  merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(vec3));
  return vec3;
}
