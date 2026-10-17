Real-Time System Monitor
A lightweight, terminal-based system monitoring tool developed in C as part of the Introduction to Computer Science (ICS) group project under Prof. Palash Das.
Features
- CPU Monitoring: Displays CPU utilization percentage.
- Memory Monitoring: Shows total RAM, used RAM, and utilization percentage.
- Disk Monitoring: Displays total and used disk space on the root filesystem.
- Live Dashboard: Periodically refreshes system statistics.
- Automatic Monitoring: Retrieves system information without requiring user input.
Tech Stack
- C
- GCC Compiler
- Linux / WSL Ubuntu
How to Run
Extract the repository and open a terminal in the project directory.
Compile the program:
gcc project.c -o system_monitor

Run the executable:
./system_monitor

The program displays a live dashboard of CPU, memory, and disk usage. Press Ctrl + C to stop execution.
Sample Output
--- Real-Time System Monitor ---
CPU Usage: 4.6%

Memory Usage:
Total RAM: 19645 MB
Used RAM: 4708 MB
Usage: 24.0%

Disk Space Usage:
Total Disk: 62 GB
Used Disk: 50 GB
Usage: 80.6%


Note: The displayed values are illustrative and vary depending on system usage.
Note: The displayed values are illustrative and vary depending on system usage.
