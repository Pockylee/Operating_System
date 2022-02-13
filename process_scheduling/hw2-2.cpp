#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main(){
	ifstream file;
	ofstream output_file;
	int process_num, arrival_time, burst_time, total_wait, total_turnaround;
	int small_burst;
	int small_index;
	vector<int> Arrival_list, Burst_list, Wait_list, Turnaround_list;
	vector<int> Final_list;

	cin >> process_num;
	for(int i = 0 ; i < process_num ;i++){
		cin >> arrival_time;
		Arrival_list.push_back(arrival_time);
	}
	for(int i = 0 ; i < process_num ;i++){
		cin >> burst_time;
		Burst_list.push_back(burst_time);
	}

	//starting list generation
	int now_pos=0, target_process;
	vector<int> Round_compare, Arrival_list_copy = Arrival_list, Burst_list_copy;
	for (int id = 0; id < process_num ;id++){
		for (int pos = 0; pos < process_num ;pos++){
			if(Arrival_list_copy[pos] <= now_pos){
				Round_compare.push_back(pos);
			}
		}

		for (int pos = 0; pos < process_num ;pos++){
			if((find(Round_compare.begin(), Round_compare.end(), pos) != Round_compare.end())){
				Burst_list_copy.push_back(Burst_list[pos]);
			}
			else{
				Burst_list_copy.push_back(99999);
			}
		}

		small_burst = *min_element(Burst_list_copy.begin(), Burst_list_copy.end());
    	vector<int>::iterator itr = find(Burst_list_copy.begin(), Burst_list_copy.end(), small_burst);

    	target_process = distance(Burst_list_copy.begin(), itr);

		for (int i=0; i < Burst_list[target_process];i++){
			Final_list.push_back(target_process);
		}
		Round_compare.clear();
		Burst_list_copy.clear();
		Arrival_list_copy[target_process] = 99999;
		now_pos += Burst_list[target_process];
	}

	int check_process = Final_list[0];
	int start_time = 0, end_time;
	int position = 0, count_fillin = 0;
	vector<int> Start_list = Arrival_list;
	for (int temp : Final_list){
		//cout << temp << ",";
		if(temp != check_process){
			check_process = temp;
			Start_list[temp] = position;
			check_process = temp;
			count_fillin++;
		}
		position++;
	}

	vector<int> End_list;
	for (int id = 0; id < process_num ;id++){
		End_list.push_back(Start_list[id] + Burst_list[id]);
	}


	for (int id = 0; id < process_num ;id++){
		Turnaround_list.push_back(End_list[id] - Arrival_list[id]);
		Wait_list.push_back(Start_list[id] - Arrival_list[id]);
	}

	total_wait = accumulate( Wait_list.begin(), Wait_list.end(), 0.0); 
	total_turnaround = accumulate( Turnaround_list.begin(), Turnaround_list.end(), 0.0);


	for (int id = 0; id < process_num ;id++){

		cout << Wait_list[id] << " " << Turnaround_list[id] << "\n";
	}
	cout << total_wait << "\n" << total_turnaround;


	return 0;
}