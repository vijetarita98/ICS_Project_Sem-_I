#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/statvfs.h> // Required for disk space usage

#define MONITOR_INTERVAL 1

// --- CPU Data Structure and Functions ---
typedef struct {
    long long user;
    long long nice;
    long long system;
    long long idle;
    long long iowait;
} CpuTime;

void get_cpu_times(CpuTime *t) {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) {
        perror("Error: Failed to open /proc/stat");
        exit(EXIT_FAILURE);
    }
    // Read the first line (aggregate CPU)
    fscanf(fp, "cpu %lld %lld %lld %lld %lld",
           &t->user, &t->nice, &t->system, &t->idle, &t->iowait);
    fclose(fp);
}


// --- Memory Data Structure and Functions ---
typedef struct {
    long long total; // In MB
    long long used;  // In MB
} MemInfo;

void get_mem_info(MemInfo *m) {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) return;

    char line[128];
    long long total_kb = 0, available_kb = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "MemTotal:")) {
            sscanf(line, "MemTotal: %lld kB", &total_kb);
        } else if (strstr(line, "MemAvailable:")) {
            sscanf(line, "MemAvailable: %lld kB", &available_kb);
        }
    }
    fclose(fp);

    // Convert kB to MB (1024 kB/MB)
    m->total = total_kb / 1024;
    m->used = (total_kb - available_kb) / 1024;
}


// --- Disk Space Usage Data and Functions ---
typedef struct {
    long long total; // In GB
    long long used;  // In GB
} DiskUsage;

// Uses statvfs() to get total and used space of the root filesystem ("/")
void get_disk_usage(DiskUsage *d) {
    struct statvfs vfs;
    if (statvfs("/", &vfs) != 0) return;

    // Calculate total and used space in bytes
    unsigned long long total_bytes = (unsigned long long)vfs.f_bsize * vfs.f_blocks;
    unsigned long long used_bytes = (unsigned long long)vfs.f_bsize * (vfs.f_blocks - vfs.f_bfree);

    // Convert bytes to GB (1024^3)
    d->total = total_bytes / (1024 * 1024 * 1024);
    d->used = used_bytes / (1024 * 1024 * 1024);
}


// --- Main Monitoring Loop ---
int main() {
    CpuTime prev_t, current_t;
    MemInfo mem_info;
    DiskUsage disk_usage;

    get_cpu_times(&prev_t); // Initial CPU snapshot

    while (1) {
        // Clear screen and move cursor to top-left
        printf("\033[H\033[J");
        sleep(MONITOR_INTERVAL);
        
        get_cpu_times(&current_t);
        get_mem_info(&mem_info);
        get_disk_usage(&disk_usage); // Get disk space usage

        // --- CPU Calculation ---
        long long prev_total = prev_t.user + prev_t.nice + prev_t.system + prev_t.idle + prev_t.iowait;
        long long current_total = current_t.user + current_t.nice + current_t.system + current_t.idle + current_t.iowait;
        long long total_delta = current_total - prev_total;
        long long idle_delta = (current_t.idle + current_t.iowait) - (prev_t.idle + prev_t.iowait);
        double cpu_usage = (total_delta > 0) ? (100.0 * (1.0 - (double)idle_delta / total_delta)) : 0.0;
        
        // --- Output Display ---
        printf("----------------------------------------\n");
        printf("--- Real-Time System Monitor ---\n");
        printf("----------------------------------------\n");
        printf("Refresh: %d second(s)\n\n", MONITOR_INTERVAL);

        // CPU Display
        printf("  CPU Usage:       %.1f%%\n\n", cpu_usage);

        // Memory Display
        printf("  Memory Usage\n");
        printf("  Total RAM:   %7lld MB\n", mem_info.total);
        printf("  Used RAM:    %7lld MB\n", mem_info.used);
        if (mem_info.total > 0) {
            printf("  Usage %%:     %7.1f%%\n\n", 100.0 * (double)mem_info.used / mem_info.total);
        }

        // Disk Space Display
        printf("  Disk Space Usage (Root '/')\n");
        printf("  Total Disk:  %7lld GB\n", disk_usage.total);
        printf("  Used Disk:   %7lld GB\n", disk_usage.used);
        
        if (disk_usage.total > 0) {
            printf("  Usage %%:     %7.1f%%\n", 100.0 * (double)disk_usage.used / disk_usage.total);
        }
        printf("----------------------------------------\n");

        // Update previous values
        prev_t = current_t;
    }
    return 0;
}