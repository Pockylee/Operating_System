#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
using namespace std;

int main(){
	ifstream file;
	ofstream output_file;
	int process_num, arrival_time, burst_time, start_time, total_wait, total_turnaround;
	vector<int> Arrival_list, Burst_list, Wait_list, Start_list, End_list, Turnaround_list;


	cin >> process_num;
	for(int i = 0 ; i < process_num ;i++){
		cin >> arrival_time;
		Arrival_list.push_back(arrival_time);
	}
	for(int i = 0 ; i < process_num ;i++){
		cin >> burst_time;
		Burst_list.push_back(burst_time);
	}


	//start_list and End_list generation
	for (int id = 0; id < process_num ;id++){
		if(id == 0){
			Start_list.push_back(0);
			End_list.push_back(Burst_list[id]);
			continue;
		}
		start_time = Start_list[id - 1] + Burst_list[id - 1];
		Start_list.push_back(start_time);
		End_list.push_back(End_list[id - 1] + Burst_list[id]);
	}

	//wait_list and turnaround_list generation
	for (int id = 0; id < process_num ;id++){
		Wait_list.push_back(Start_list[id] - Arrival_list[id]);
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