# ICS_Project_Sem-_I
ICS  Group Project
How to Run the Program .

1. Extract the ZIP file
Right-click on the ZIP file and choose “Extract Here” or use the command:
unzip project.zip
2. Open a terminal on a Linux system (or WSL Ubuntu on Windows).
Compile the code using GCC (make sure project.c exists in the folder):
3.Compile the code using GCC (make sure project.c exists in the folder):
gcc project.c 
4.Run the program:
./a.out

Hence ,Expected Input :
No user input is required.
The program automatically reads system information from Linux files:

Expected Output :
The program displays a live console dashboard with CPU, memory, and disk usage. It updates every half-second.

Sample Output : 
--- Real-Time System Monitor ---
Refresh: 1 second(s)
CPU Usage:
4.6%
Memory Usage
Total RAM:
19645 MB
Used RAM:
4708 MB
Usage %:
24.0%
Disk Space Usage 
Total Disk:
62 GB
Used Disk:
50 GB
Usage %:
80.6%
----------------------------

  So  ,
    CPU Usage – Percentage of time CPU was busy during the last interval.
    Memory Usage – Amount of memory used versus total memory, along with percentage.
    Disk Usage – Amount of disk used versus total disk space on the root filesystem, with percentage.
Note : 
    Values change in real-time as system usage changes.
    The display is refreshed using system("clear") so only the latest values are shown .
