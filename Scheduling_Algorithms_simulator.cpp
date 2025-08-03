#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// A structure to represent an entry in the Gantt chart
struct GanttEntry {
    int pid;
    int start_time;
    int end_time;
    bool is_idle = false;
};

// The Process structure, updated for new features
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    
    // Mutable properties
    int remaining_time;
    int completion_time = 0;
    int turnaround_time = 0;
    int waiting_time = 0;
};

// --- Utility Functions ---

// Comparator to sort processes by arrival time
bool compareArrival(const Process& a, const Process& b) {
    if (a.arrival_time == b.arrival_time) {
        return a.pid < b.pid;
    }
    return a.arrival_time < b.arrival_time;
}

// Function to print the final results table
void printResults(const vector<Process>& processes) {
    // Sort by PID for consistent output
    vector<Process> sorted_processes = processes;
    sort(sorted_processes.begin(), sorted_processes.end(), [](const Process& a, const Process& b) {
        return a.pid < b.pid;
    });

    double total_waiting_time = 0;
    double total_turnaround_time = 0;

    cout << "\n--- Final Results ---\n";
    cout << left << setw(5) << "PID"
              << setw(15) << "Arrival Time"
              << setw(15) << "Burst Time"
              << setw(20) << "Completion Time"
              << setw(20) << "Turnaround Time"
              << setw(15) << "Waiting Time" << endl;

    for (const auto& p : sorted_processes) {
        cout << left << setw(5) << p.pid
                  << setw(15) << p.arrival_time
                  << setw(15) << p.burst_time
                  << setw(20) << p.completion_time
                  << setw(20) << p.turnaround_time
                  << setw(15) << p.waiting_time << endl;
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }

    cout << "\nAverage Turnaround Time: " << total_turnaround_time / processes.size() << endl;
    cout << "Average Waiting Time: " << total_waiting_time / processes.size() << endl;
}

// Function to print the Gantt Chart
void printGanttChart(const vector<GanttEntry>& chart) {
    cout << "\n--- Gantt Chart ---\n";

    // Print top border
    for (const auto& entry : chart) {
        cout << "+";
        for (int i = 0; i < (entry.end_time - entry.start_time) * 3; ++i) cout << "-";
    }
    cout << "+\n|";

    // Print process IDs
    for (const auto& entry : chart) {
        string name = entry.is_idle ? "IDLE" : "P" + to_string(entry.pid);
        int duration = (entry.end_time - entry.start_time) * 3;
        int padding = (duration - name.length()) / 2;
        for (int i = 0; i < padding; ++i) cout << " ";
        cout << name;
        for (int i = 0; i < duration - padding - name.length(); ++i) cout << " ";
        cout << "|";
    }
    cout << "\n";

    // Print bottom border
    for (const auto& entry : chart) {
        cout << "+";
        for (int i = 0; i < (entry.end_time - entry.start_time) * 3; ++i) cout << "-";
    }
    cout << "+\n";

    // Print time markers
    cout << chart.front().start_time;
    for (const auto& entry : chart) {
        int duration = (entry.end_time - entry.start_time) * 3;
        for (int i = 0; i < duration - to_string(entry.end_time).length() + 1; ++i) cout << " ";
        cout << entry.end_time;
    }
    cout << "\n\n";
}

// --- Scheduling Algorithms ---

// First Come First Serve (FCFS)
void findFCFS(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrival);
    vector<GanttEntry> gantt_chart;
    int current_time = 0;

    for (auto& p : processes) {
        if (current_time < p.arrival_time) {
            gantt_chart.push_back({-1, current_time, p.arrival_time, true});
            current_time = p.arrival_time;
        }
        gantt_chart.push_back({p.pid, current_time, current_time + p.burst_time});
        current_time += p.burst_time;
        p.completion_time = current_time;
        p.turnaround_time = p.completion_time - p.arrival_time;
        p.waiting_time = p.turnaround_time - p.burst_time;
    }
    printGanttChart(gantt_chart);
}


// Shortest Job First (SJF) - Non-Preemptive
void findSJF(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrival);
    vector<GanttEntry> gantt_chart;
    int current_time = 0;
    int completed = 0;
    vector<bool> is_completed(processes.size(), false);

    while (completed < processes.size()) {
        int shortest_job_idx = -1;
        int min_burst = INT_MAX;

        // Find the shortest job that has arrived
        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].arrival_time <= current_time && !is_completed[i]) {
                if (processes[i].burst_time < min_burst) {
                    min_burst = processes[i].burst_time;
                    shortest_job_idx = i;
                }
            }
        }

        if (shortest_job_idx == -1) {
            // Find the next process to arrive and fast-forward time
            int next_arrival = INT_MAX;
            for(int i = 0; i < processes.size(); ++i) {
                if(!is_completed[i]) {
                    next_arrival = min(next_arrival, processes[i].arrival_time);
                }
            }
            if (current_time < next_arrival) {
                 gantt_chart.push_back({-1, current_time, next_arrival, true});
                 current_time = next_arrival;
            }
        } else {
            Process& p = processes[shortest_job_idx];
            gantt_chart.push_back({p.pid, current_time, current_time + p.burst_time});
            current_time += p.burst_time;
            p.completion_time = current_time;
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.burst_time;
            is_completed[shortest_job_idx] = true;
            completed++;
        }
    }
    printGanttChart(gantt_chart);
}


// Shortest Remaining Time First (SRTF) - Preemptive (Efficient Implementation)
void findSRTF(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrival);

    // Custom comparator for the priority queue (min-heap on remaining time)
    auto compare = [](const Process* a, const Process* b) {
        if (a->remaining_time == b->remaining_time) return a->pid > b->pid;
        return a->remaining_time > b->remaining_time;
    };
    priority_queue<Process*, vector<Process*>, decltype(compare)> ready_queue(compare);
    
    vector<GanttEntry> gantt_chart;
    int current_time = 0;
    int completed = 0;
    int process_idx = 0;

    while (completed < processes.size()) {
        // Add newly arrived processes to the ready queue
        while (process_idx < processes.size() && processes[process_idx].arrival_time <= current_time) {
            ready_queue.push(&processes[process_idx]);
            process_idx++;
        }

        if (ready_queue.empty()) {
            if(process_idx < processes.size()){
                gantt_chart.push_back({-1, current_time, processes[process_idx].arrival_time, true});
                current_time = processes[process_idx].arrival_time;
            }
            continue; // Go back to check for new arrivals at the new current_time
        }

        Process* current_process = ready_queue.top();
        ready_queue.pop();

        int start_exec_time = current_time;
        int time_to_run = 1; // Run for 1 time unit and re-evaluate

        // Optimization: Run until next process arrives or current process finishes
        int next_arrival_time = (process_idx < processes.size()) ? processes[process_idx].arrival_time : INT_MAX;
        time_to_run = min(current_process->remaining_time, next_arrival_time - current_time);
        
        current_time += time_to_run;
        current_process->remaining_time -= time_to_run;

        gantt_chart.push_back({current_process->pid, start_exec_time, current_time});

        if (current_process->remaining_time == 0) {
            current_process->completion_time = current_time;
            current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
            current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
            completed++;
        } else {
            // If not finished, add it back to the queue
            ready_queue.push(current_process);
        }
    }
    printGanttChart(gantt_chart);
}


// Round Robin
void findRoundRobin(vector<Process>& processes, int quantum) {
    sort(processes.begin(), processes.end(), compareArrival);
    queue<Process*> ready_queue;
    vector<GanttEntry> gantt_chart;
    
    int current_time = 0;
    int process_idx = 0;

    // Initially add processes that arrive at or before time 0
    while(process_idx < processes.size() && processes[process_idx].arrival_time <= current_time) {
        ready_queue.push(&processes[process_idx++]);
    }
    
    while (!ready_queue.empty()) {
        Process* current_process = ready_queue.front();
        ready_queue.pop();
        
        int start_exec_time = max(current_time, current_process->arrival_time);

        if(current_time < start_exec_time) {
             gantt_chart.push_back({-1, current_time, start_exec_time, true});
             current_time = start_exec_time;
        }

        int time_to_run = min(quantum, current_process->remaining_time);
        
        gantt_chart.push_back({current_process->pid, current_time, current_time + time_to_run});
        
        current_process->remaining_time -= time_to_run;
        current_time += time_to_run;

        // Add any processes that arrived while this one was running
        while(process_idx < processes.size() && processes[process_idx].arrival_time <= current_time) {
            ready_queue.push(&processes[process_idx++]);
        }
        
        if (current_process->remaining_time > 0) {
            ready_queue.push(current_process);
        } else {
            current_process->completion_time = current_time;
            current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
            current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
        }

        // If queue is empty but more processes are waiting to arrive
        if(ready_queue.empty() && process_idx < processes.size()) {
             if(current_time < processes[process_idx].arrival_time) {
                 gantt_chart.push_back({-1, current_time, processes[process_idx].arrival_time, true});
                 current_time = processes[process_idx].arrival_time;
             }
             while(process_idx < processes.size() && processes[process_idx].arrival_time <= current_time) {
                ready_queue.push(&processes[process_idx++]);
            }
        }
    }
    printGanttChart(gantt_chart);
}


// --- Main Function ---

int main() {
    cout << "*** PROCESS SCHEDULING ALGORITHMS SIMULATOR ***" << endl;
    int n;
    cout << "\nEnter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "Enter details for Process P" << i + 1 << endl;
        cout << "\tArrival time: ";
        cin >> processes[i].arrival_time;
        cout << "\tBurst time: ";
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
        cout << endl;
    }

    cout << "Select the Process Scheduling Algorithm" << endl;
    cout << "1. First Come First Serve (FCFS)" << endl;
    cout << "2. Shortest Job First (SJF - Non-Preemptive)" << endl;
    cout << "3. Shortest Remaining Time First (SRTF - Preemptive)" << endl;
    cout << "4. Round Robin" << endl;
    cout << "\nEnter the number: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            findFCFS(processes);
            break;
        case 2:
            findSJF(processes);
            break;
        case 3:
            findSRTF(processes);
            break;
        case 4:
            int quantum;
            cout << "Enter Time Quantum: ";
            cin >> quantum;
            findRoundRobin(processes, quantum);
            break;
        default:
            cout << "Invalid choice. Exiting." << endl;
            return 1;
    }

    printResults(processes);

    return 0;
}
