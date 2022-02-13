#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main(){
	ifstream file;
	ofstream output_file;
	int process_num, arrival_time, burst_time, total_wait, total_turnaround, time_quantum;
	int small_burst;
	int small_index;
	vector<int> Arrival_list, Burst_list;
	vector<int> Final_list, Queue_list,Queue_list_srtf;

	cin >> process_num;
	for(int i = 0 ; i < process_num ;i++){
		cin >> arrival_time;
		Arrival_list.push_back(arrival_time);
	}
	for(int i = 0 ; i < process_num ;i++){
		cin >> burst_time;
		Burst_list.push_back(burst_time);
	}
	cin >> time_quantum;

	//starting list generation
	int now_pos=0, target_process;
	vector<int> Round_compare, Arrival_list_copy = Arrival_list, Burst_list_copy = Burst_list;
	int total_length = accumulate( Burst_list.begin(), Burst_list.end(), 0.0); 
	int time_quantum_count = 1, change = 0;



	for (int l = 0; l < total_length ;l++){

		for (int pos = 0; pos < process_num ;pos++){
			if(Arrival_list_copy[pos] <= l && Burst_list_copy[pos] != 0){
				Queue_list.push_back(pos);
				Arrival_list_copy[pos] = 99999;
				break;
			}
		}

		if(Queue_list.size() != 0 ){
			if(change == 1){
				time_quantum = 1;
				change = 0;
			}
			int queue_target = Queue_list[0];
			Final_list.push_back(Queue_list[0]);
			Burst_list_copy[Queue_list[0]]--;
			if(time_quantum_count == time_quantum){
				for (int pos = 0; pos < process_num ;pos++){
					if(Arrival_list_copy[pos] <= l+1 && Burst_list_copy[pos] != 0){
						Queue_list.push_back(pos);
						Arrival_list_copy[pos] = 99999;
						break;
					}
				}
	
				if(Burst_list_copy[Queue_list[0]] == 0){
					Queue_list.erase(Queue_list.begin());
				}
				else{
					Queue_list.erase(Queue_list.begin());
					//Queue_list.push_back(queue_target);
					Queue_list_srtf.push_back(queue_target);
				}
				
				time_quantum_count = 1;

			}
			else if (Burst_list_copy[Queue_list[0]] == 0){
				Queue_list.erase(Queue_list.begin());
				time_quantum_count = 1;

			}

			else{
				time_quantum_count++;
			}
		}

		else{
			change = 1;
			int queue_target = Queue_list_srtf[0];
			int compare = Burst_list_copy[Queue_list_srtf[0]];
			for(int queue_list_srtf: Queue_list_srtf){
				if(Burst_list_copy[queue_list_srtf]<compare){
					queue_target = queue_list_srtf;
				}
			}


			Final_list.push_back(queue_target);
			Burst_list_copy[queue_target]--;
			if(time_quantum_count == time_quantum){
	
				if(Burst_list_copy[queue_target] == 0){
					Queue_list_srtf.erase(remove(Queue_list_srtf.begin(), Queue_list_srtf.end(), queue_target), Queue_list_srtf.end());
				}
				else{
					Queue_list_srtf.erase(remove(Queue_list_srtf.begin(), Queue_list_srtf.end(), queue_target), Queue_list_srtf.end());
					Queue_list_srtf.push_back(queue_target);
				}
				
				time_quantum_count = 1;

			}
			else if (Burst_list_copy[queue_target] == 0){
				Queue_list_srtf.erase(remove(Queue_list_srtf.begin(), Queue_list_srtf.end(), queue_target), Queue_list_srtf.end());
				time_quantum_count = 1;

			}

			else time_quantum_count++;

		}
	}

	vector<int> Wait_list(process_num);

	vector<int> End_list(process_num), End_list_last(process_num);
	int temp=Final_list[0];
	int start_position=0, end_position=0;
	for(int final_p : Final_list){
		if (final_p!= temp){
			if(End_list[final_p] != 0){
				Wait_list[final_p] += end_position - End_list[final_p];
			}
			End_list[temp] = end_position;
 
			temp = final_p;

		}
		end_position++;
		if(end_position == total_length){
			End_list[final_p] = end_position;
		}
	}


	

	int start_time;
	vector<int> Start_list;
	for(int id=0; id < process_num;id++){
		vector<int>::iterator itr = find(Final_list.begin(), Final_list.end(), id);
    	start_time = distance(Final_list.begin(), itr);
    	Start_list.push_back(start_time);
	}
 

 	vector<int> Turnaround_list;
	for(int id=0; id < process_num;id++){
		Wait_list[id] += Start_list[id] - Arrival_list[id];
		Turnaround_list.push_back(End_list[id] - Arrival_list[id]);
	}


	total_wait = accumulate( Wait_list.begin(), Wait_list.end(), 0.0); 
	total_turnaround = accumulate( Turnaround_list.begin(), Turnaround_list.end(), 0.0);

	for (int id = 0; id < process_num ;id++){
		cout << Wait_list[id] << " " << Turnaround_list[id] << "\n";

	}
	cout << total_wait << "\n" << total_turnaround;



	return 0;
}