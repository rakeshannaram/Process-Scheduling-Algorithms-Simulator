# Process-Scheduling-Algorithms-Simulator
Output 1:

*** PROCESS SCHEDULING ALGORITHMS SIMULATOR ***

Enter the number of processes: 5
Enter details for Process P1
	Arrival time: 0
	Burst time: 5

Enter details for Process P2
	Arrival time: 2
	Burst time: 3

Enter details for Process P3
	Arrival time: 1
	Burst time: 8

Enter details for Process P4
	Arrival time: 4
	Burst time: 2

Enter details for Process P5
	Arrival time: 3
	Burst time: 4

Select the Process Scheduling Algorithm
1. First Come First Serve (FCFS)
2. Shortest Job First (SJF - Non-Preemptive)
3. Shortest Remaining Time First (SRTF - Preemptive)
4. Round Robin

Enter the number: 3

--- Gantt Chart ---
+---+---+---+---+---+------+---------+------------+------------------------+
|P1 |P1 |P1 |P1 |P1 |  P4  |   P2    |     P5     |           P3           |
+---+---+---+---+---+------+---------+------------+------------------------+
0   1   2   3   4   5      7        10           14                       22


--- Final Results ---
PID  Arrival Time   Burst Time     Completion Time     Turnaround Time     Waiting Time   
1    0              5              5                   5                   0              
2    2              3              10                  8                   5              
3    1              8              22                  21                  13             
4    4              2              7                   3                   1              
5    3              4              14                  11                  7              

Average Turnaround Time: 9.6
Average Waiting Time: 5.2


=== Code Execution Successful ===

Output 2:

*** PROCESS SCHEDULING ALGORITHMS SIMULATOR ***

Enter the number of processes: 5
Enter details for Process P1
	Arrival time: 0
	Burst time: 5

Enter details for Process P2
	Arrival time: 2
	Burst time: 3

Enter details for Process P3
	Arrival time: 1
	Burst time: 8

Enter details for Process P4
	Arrival time: 4
	Burst time: 2

Enter details for Process P5
	Arrival time: 3
	Burst time: 4

Select the Process Scheduling Algorithm
1. First Come First Serve (FCFS)
2. Shortest Job First (SJF - Non-Preemptive)
3. Shortest Remaining Time First (SRTF - Preemptive)
4. Round Robin

Enter the number: 4
Enter Time Quantum: 2

--- Gantt Chart ---
+------+------+------+------+------+------+------+---+---+------+------+------+
|  P1  |  P3  |  P2  |  P1  |  P5  |  P4  |  P3  |P2 |P1 |  P5  |  P3  |  P3  |
+------+------+------+------+------+------+------+---+---+------+------+------+
0      2      4      6      8     10     12     14  15  16     18     20     22


--- Final Results ---
PID  Arrival Time   Burst Time     Completion Time     Turnaround Time     Waiting Time   
1    0              5              16                  16                  11             
2    2              3              15                  13                  10             
3    1              8              22                  21                  13             
4    4              2              12                  8                   6              
5    3              4              18                  15                  11             

Average Turnaround Time: 14.6
Average Waiting Time: 10.2


=== Code Execution Successful ===

Output 3:

*** PROCESS SCHEDULING ALGORITHMS SIMULATOR ***

Enter the number of processes: 5
Enter details for Process P1
	Arrival time: 0
	Burst time: 5

Enter details for Process P2
	Arrival time: 2
	Burst time: 3

Enter details for Process P3
	Arrival time: 1
	Burst time: 8

Enter details for Process P4
	Arrival time: 4
	Burst time: 2

Enter details for Process P5
	Arrival time: 3
	Burst time: 4

Select the Process Scheduling Algorithm
1. First Come First Serve (FCFS)
2. Shortest Job First (SJF - Non-Preemptive)
3. Shortest Remaining Time First (SRTF - Preemptive)
4. Round Robin

Enter the number: 2

--- Gantt Chart ---
+---------------+------+---------+------------+------------------------+
|      P1       |  P4  |   P2    |     P5     |           P3           |
+---------------+------+---------+------------+------------------------+
0               5      7        10           14                       22


--- Final Results ---
PID  Arrival Time   Burst Time     Completion Time     Turnaround Time     Waiting Time   
1    0              5              5                   5                   0              
2    2              3              10                  8                   5              
3    1              8              22                  21                  13             
4    4              2              7                   3                   1              
5    3              4              14                  11                  7              

Average Turnaround Time: 9.6
Average Waiting Time: 5.2


=== Code Execution Successful ===

Outpur 4:

*** PROCESS SCHEDULING ALGORITHMS SIMULATOR ***

Enter the number of processes: 5
Enter details for Process P1
	Arrival time: 0
	Burst time: 5

Enter details for Process P2
	Arrival time: 2
	Burst time: 3

Enter details for Process P3
	Arrival time: 1
	Burst time: 8

Enter details for Process P4
	Arrival time: 4
	Burst time: 2

Enter details for Process P5
	Arrival time: 3
	Burst time: 4

Select the Process Scheduling Algorithm
1. First Come First Serve (FCFS)
2. Shortest Job First (SJF - Non-Preemptive)
3. Shortest Remaining Time First (SRTF - Preemptive)
4. Round Robin

Enter the number: 1

--- Gantt Chart ---
+---------------+------------------------+---------+------------+------+
|      P1       |           P3           |   P2    |     P5     |  P4  |
+---------------+------------------------+---------+------------+------+
0               5                       13        16           20     22


--- Final Results ---
PID  Arrival Time   Burst Time     Completion Time     Turnaround Time     Waiting Time   
1    0              5              5                   5                   0              
2    2              3              16                  14                  11             
3    1              8              13                  12                  4              
4    4              2              22                  18                  16             
5    3              4              20                  17                  13             

Average Turnaround Time: 13.2
Average Waiting Time: 8.8


=== Code Execution Successful ===
