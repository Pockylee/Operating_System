#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <random>
#include <iomanip>
using namespace std;

#define INTERVAL 100000
int thread_num;
long long int point_num, circle_points = 0;

pthread_t thread_id[4];
sem_t semaphore;
void *draw_circle(void* arg);

struct draw_thread{
	int thread_id_copy;
};

int main(){


	cin >> thread_num;
	cin >> point_num;

	struct draw_thread draw_toeach[thread_num];
	struct draw_thread draw_funct;

	sem_init(&semaphore, 0, 1);

	for(long long int i = 0;i < thread_num;i++){
		draw_toeach[i].thread_id_copy = i;
		pthread_create(&thread_id[i], NULL, draw_circle, &draw_toeach[i]);
	}

	for(long long int i = 0;i < thread_num;i++){
		pthread_join(thread_id[i], NULL);
	}

	cout << "get: " << circle_points << endl;
    cout << "Pi: " << fixed << setprecision(6) << (double)(circle_points * 4) / point_num << endl;



	return 0;
}



void *draw_circle(void* arg){
	draw_thread *draw_funct;
	draw_funct = (draw_thread*)arg;
	int thread_id_funct = draw_funct->thread_id_copy;

	double rand_x, rand_y, origin_dist ;


	srand(time(NULL));
	for (long long int i = 0; i < (point_num / thread_num); i++) {
		rand_x = double(rand() % (point_num + 1)) / point_num;
        rand_y = double(rand() % (point_num + 1)) / point_num;
  
        // Distance between (x, y) from the origin
        origin_dist = rand_x * rand_x + rand_y * rand_y;
  
        // Checking if (x, y) lies inside the define
        // circle with R=1
        if (origin_dist <= 1){
        	sem_wait(&semaphore);
            circle_points++;
            sem_post(&semaphore);
        }

	}



	pthread_exit(NULL);
}