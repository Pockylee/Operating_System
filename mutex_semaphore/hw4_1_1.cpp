#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <string>
using namespace std;

long long counts[3] = {0};
int thread_num;
long long int series_len;
string input_series;
pthread_t thread_id[4];
sem_t semaphore[3];

struct count_thread{
	int thread_id_copy;
	long long int start_pos;
	long long int end_pos;
};
void *count_algo(void* arg);


int main(){

	cin >> thread_num;
	cin >> series_len;
	cin >> input_series;

	struct count_thread count_toeach[thread_num];
	struct count_thread count_funct;

	sem_init(&semaphore[0], 0, 1);
	sem_init(&semaphore[1], 0, 1);
	sem_init(&semaphore[2], 0, 1);


	//start thread counting
	for(int i = 0; i< thread_num;i++){
		count_toeach[i].thread_id_copy = i;
		count_toeach[i].start_pos = (i / (double)thread_num) * series_len;
		count_toeach[i].end_pos = ((i + 1) / (double)thread_num) * series_len;
		pthread_create(&thread_id[i], NULL, count_algo, &count_toeach[i]);
	}

	for(int i = 0; i< thread_num;i++){
		pthread_join(thread_id[i], NULL);
	}

	cout << "0: " << counts[0] << endl;
	cout << "1: " << counts[1] << endl;
	cout << "2: " << counts[2] << endl;

	return 0;
}

void *count_algo(void* arg){
	count_thread *count_funct;
	count_funct = (count_thread*)arg;
	long long int start_pos_funct = count_funct->start_pos;
	long long int end_pos_funct = count_funct->end_pos;
	//cout << start_pos_funct << end_pos_funct<< endl;
	for (long long int i = start_pos_funct; i < end_pos_funct;i++){
		if (input_series[i] == '0'){
			sem_wait(&semaphore[0]);
			counts[0]++;
			sem_post(&semaphore[0]);
		}
		else if (input_series[i] == '1'){
			sem_wait(&semaphore[1]);
			counts[1]++;
			sem_post(&semaphore[1]);
		}
		else if (input_series[i] == '2'){
			sem_wait(&semaphore[2]);
			counts[2]++;
			sem_post(&semaphore[2]);
		}
	}

	pthread_exit(NULL);
}



