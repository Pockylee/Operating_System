#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <pthread.h>
using namespace std;


/* function definitions */

void* bubbleSort(void* arg);
void* merge_vectors(void* arg);

vector<int> Split_input_list[16];
vector<int> Merge_output_list[15];

struct bubble_thread {
	vector<int> list;
	int position;
};

struct merge_thread {
	vector<int> list_1;
	vector<int> list_2;
	int position;
};

int main (int argc, const char * argv[]) 
{
	int cut_num = 16;
	int input_num;
	vector<int> Input_list;
	pthread_t thread_ID[16];
	pthread_t thread_merge_ID[15];

	struct bubble_thread bubble_toeach[16];
	struct bubble_thread bubble_funct;

	struct merge_thread merge_toeach[15];
	struct merge_thread merge_funct;


	while(cin >> input_num){
		Input_list.push_back(input_num);
	}

	//cut vector into multi subvector
	int size = cut_num;
	int n = (Input_list.size() - 1) / cut_num + 1;
	for(int k = 0; k < size; ++k){
        auto start_itr = next(Input_list.cbegin(), k*n);
        auto end_itr = next(Input_list.cbegin(), k*n + n);
 
        Split_input_list[k].resize(n);
        if (k*n + n > Input_list.size())
        {
            end_itr = Input_list.cend();
            Split_input_list[k].resize(Input_list.size() - k*n);
        }
        copy(start_itr, end_itr, Split_input_list[k].begin());
	}

	//bubble sort
	int sort_pos = 0;
	for(vector<int> temp : Split_input_list){
		bubble_toeach[sort_pos].list = temp;
		bubble_toeach[sort_pos].position = sort_pos;
		pthread_create(&thread_ID[sort_pos],NULL,bubbleSort,&bubble_toeach[sort_pos]);
		sort_pos++;
	}

	pthread_join(thread_ID[0],NULL);
    pthread_join(thread_ID[1],NULL);
    pthread_join(thread_ID[2],NULL);
    pthread_join(thread_ID[3],NULL);
    pthread_join(thread_ID[4],NULL);
    pthread_join(thread_ID[5],NULL);
    pthread_join(thread_ID[6],NULL);
    pthread_join(thread_ID[7],NULL);


    pthread_join(thread_ID[8],NULL);
    pthread_join(thread_ID[9],NULL);
    pthread_join(thread_ID[10],NULL);
    pthread_join(thread_ID[11],NULL);
    pthread_join(thread_ID[12],NULL);
    pthread_join(thread_ID[13],NULL);
    pthread_join(thread_ID[14],NULL);
    pthread_join(thread_ID[15],NULL);

    for(int i=0;i< size / 2; i++){
    	merge_toeach[i].list_1 = Split_input_list[i*2];
    	merge_toeach[i].list_2 = Split_input_list[i*2 + 1];
    	merge_toeach[i].position = i;
    	pthread_create(&thread_merge_ID[i],NULL,merge_vectors,&merge_toeach[i]);
    }

	pthread_join(thread_merge_ID[0],NULL);
	pthread_join(thread_merge_ID[1],NULL);
	pthread_join(thread_merge_ID[2],NULL);
	pthread_join(thread_merge_ID[3],NULL);
	pthread_join(thread_merge_ID[4],NULL);
	pthread_join(thread_merge_ID[5],NULL);
	pthread_join(thread_merge_ID[6],NULL);
	pthread_join(thread_merge_ID[7],NULL);

	for(int i=0;i< size / 4; i++){
    	merge_toeach[i + 8].list_1 = Merge_output_list[i*2];
    	merge_toeach[i + 8].list_2 = Merge_output_list[i*2 + 1];
    	merge_toeach[i + 8].position = i + 8;
    	pthread_create(&thread_merge_ID[i + 8],NULL,merge_vectors,&merge_toeach[i + 8]);
    }

	pthread_join(thread_merge_ID[8],NULL);
	pthread_join(thread_merge_ID[9],NULL);
	pthread_join(thread_merge_ID[10],NULL);
	pthread_join(thread_merge_ID[11],NULL);



	for(int i=0;i< size / 8; i++){
    	merge_toeach[i + 12].list_1 = Merge_output_list[i*2 + 8];
    	merge_toeach[i + 12].list_2 = Merge_output_list[i*2 + 9];
    	merge_toeach[i + 12].position = i + 12;
    	pthread_create(&thread_merge_ID[i + 12],NULL,merge_vectors,&merge_toeach[i + 12]);
    }

	pthread_join(thread_merge_ID[12],NULL);
	pthread_join(thread_merge_ID[13],NULL);

	int last_pos = 14;
	merge_toeach[last_pos].list_1 = Merge_output_list[last_pos - 2];
    merge_toeach[last_pos].list_2 = Merge_output_list[last_pos - 1];
    merge_toeach[last_pos].position = last_pos;
    pthread_create(&thread_merge_ID[last_pos],NULL,merge_vectors,&merge_toeach[last_pos]);

    pthread_join(thread_merge_ID[14],NULL);
  
	for (int i : Merge_output_list[last_pos]){
		cout << i << ' ';
	}

  return 0;
}


void* bubbleSort(void* arg){
	bubble_thread *bubble_funct;
	bubble_funct = (bubble_thread*)arg;
	vector<int>& a = bubble_funct->list;
	int put_back_pos = bubble_funct->position;
    bool swapp = true;
    while(swapp){
       	swapp = false;
        for (size_t i = 0; i < a.size()-1; i++) {
            if (a[i]>a[i+1] ){
                a[i] += a[i+1];
                a[i+1] = a[i] - a[i+1];
                a[i] -= a[i+1];
                swapp = true;
            }
        }
    }
    Split_input_list[put_back_pos] = bubble_funct->list;
    pthread_exit(NULL);
}


void* merge_vectors(void* arg){
	merge_thread *merge_funct;
	merge_funct = (merge_thread*)arg;
	vector<int> b = merge_funct->list_1;
	vector<int> c = merge_funct->list_2;
	int put_back_pos = merge_funct->position;
	vector<int> d;
	d.reserve(b.size() + c.size());
	merge(b.begin(), b.end(), c.begin(), c.end(), back_inserter(d));

	Merge_output_list[put_back_pos] = d;
	pthread_exit(NULL);
}

