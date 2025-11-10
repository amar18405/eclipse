OS CODES

1)
LINUX CODES
#!/bin/bash
# Arithmetic Calculator
while true
do
    echo "Enter first number : "
    read m
    echo "Enter second number : "
    read n

    printf "1) Addition\n2) Subtraction\n3) Multiplication\n4) Division\n"
    echo "Enter choice of operation to be performed : "
    read choice

    case $choice in
        1) echo "$m + $n = `expr $m + $n`";;
        2) echo "$m - $n = `expr $m - $n`";;
        3) echo "$m * $n = `expr $m \* $n`";;
        4) 
            if [ "$(echo "$n == 0" | bc)" -eq 1 ]; then
    		echo "Division by zero is not allowed."
	    else
    		echo "$m / $n = $(echo "scale=2; $m / $n" | bc)"
	    fi
	    ;;
        *) echo "Wrong Choice boss! Try Again";;
    esac

    echo "Do you want to perform another operation? (y/n)"
    read answer
    if [ "$answer" != "y" ]; then
        echo "Goodbye!"
        break
    fi
done


directory named mydir with a subdirectory subdir inside it; the -p flag makes parent directories if they don’t exist.
mkdir -p mydir/subdir
Creates a new file named file1.txt and writes the text between EOF markers into it.
cat > mydir/subdir/file1.txt << EOF
This is the content of file1.txt
EOF
➤ Copies file1.txt to a new file named file2.txt in the same directory.
cp mydir/subdir/file1.txt mydir/subdir/file2.txt
➤ Changes the permissions of file1.txt so the owner can read, write, and execute, while others can only read.
chmod 744 mydir/subdir/file1.txt
chmod 744 mydir/subdir/file2.txt
Lists all files in mydir/subdir with detailed information like permissions, size, and modification time.
ls -l mydir/subdir

2)
ORPHAN/ZOMBIE
orphan 
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    int pid = fork();
    if(pid>0)
    {
          printf("Parent process id %d\n", getpid());
          printf("Child process id %d\n", pid);
    }
    else
    {
        if(pid == 0)
        {
              sleep(10);
              printf("Child process id %d\n", getpid());
              printf("Parent process id %d\n", getppid());
        }
    }
  return 0;
}

zombie
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
  pid_t pid;
  if((pid=fork())<0)
    printf("\t fork error\n");
  else
  if(pid==0)
    printf("Child process id is %d\n",getpid());
  else
  {
    sleep(10);
    printf("*parent\n");
    system("ps -axj | tail");
    }
    exit(0);
    }

3)
FCFS CPU ALGORITHM
#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

void sortByArrival(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int start_time[n];
    float total_tat = 0, total_wt = 0;

    // Input
    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time and Burst Time for process %d: ", i + 1);
        scanf("%d%d%d", &p[i].pid, &p[i].at, &p[i].bt);
    }

    // Sort by Arrival Time
    sortByArrival(p, n);

    int time = 0;

    // FCFS Scheduling
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        start_time[i] = time;

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_tat += p[i].tat;
        total_wt += p[i].wt;

        time = p[i].ct;
    }

    // Output Table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time   : %.2f\n", total_wt / n);

    // Gantt Chart
    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("-\n|");

    // Process IDs
    for (int i = 0; i < n; i++) {
        printf("  P%d   |", p[i].pid);
    }

    // Bottom bar
    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("-\n");

    // Timeline
    printf("%d", start_time[0]);
    for (int i = 0; i < n; i++) {
        printf("       %d", p[i].ct);
    }

    printf("\n");

    return 0;
}

4)
SRTF CPU ALGORITHM
#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;      
    int at;      
    int bt;        
    int rt;        
    int ct;        
    int tat;      
    int wt;        
    int completed;
};

int main() {
    int n, completed = 0, currentTime = 0, minRT, shortest;
    float totalTAT = 0, totalWT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, Burst Time for Process %d: ", i + 1);
        scanf("%d%d%d", &p[i].pid, &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;  
        p[i].completed = 0;  
    }

    printf("\n--- Gantt Chart ---\n");
    printf("0");

    while (completed != n) {
        shortest = -1;
        minRT = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].completed == 0 && p[i].rt < minRT) {
                minRT = p[i].rt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            printf(" | Idle | %d", currentTime + 1);
            currentTime++;
            continue;
        }

        printf(" | P%d | %d", p[shortest].pid, currentTime + 1);
        p[shortest].rt--;
        currentTime++;

        if (p[shortest].rt == 0) {
            p[shortest].completed = 1;
            completed++;

            p[shortest].ct = currentTime;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;

            totalTAT += p[shortest].tat;
            totalWT += p[shortest].wt;
        }
    }

    printf("\n");

    printf("\n--- Process Table ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", totalTAT / n);
    printf("\nAverage WT = %.2f\n", totalWT / n);

    return 0;
}

5)
PIPES
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2]; // fd[0] - read end, fd[1] - write end
    pid_t pid;
    char write_msg[] = "Hello through pipe!";
    char read_msg[100];

    if (pipe(fd) == -1) {
        printf("pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        printf("fork failed");
        return 1;
    }

    if (pid > 0) {
        // Parent process - write to pipe
        close(fd[0]); // Close read end

        write(fd[1], write_msg, strlen(write_msg) + 1); // +1 to include null terminator
        close(fd[1]); // Close write end after writing
    } else {
        // Child process - read from pipe
        close(fd[1]); // Close write end

        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child message: %s\n", read_msg);

        close(fd[0]); // Close read end after reading
    }

    return 0;
}

6)
READER-WRITER
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

sem_t mutex, wrt;
pthread_t tid;
int sharevar=99;
pthread_t writers[5], readers[5];
int readcount=0;

void reader(void param)
{
  sem_wait(&mutex);
  readcount++;
  if(readcount==1)
    sem_wait(&wrt);
  sem_post(&mutex);
  
  printf("\n%d reader is reading shared variable=%d", readcount, sharevar);
  sleep(1);
  sem_wait(&mutex);
  readcount--;
  if(readcount==0)
     sem_post(&wrt);
  sem_post(&mutex);
  
  printf("\n%d Reader is done", readcount+1);
  pthread_exit(NULL);
}

void writer(void param)
{
  printf("\n Writer is trying to enter");
  sem_wait(&wrt);
  printf("\n Writer has entered CS");
  sharevar++;
  printf("\n Writer changed the value of shared variable to %d", sharevar);
  sem_post(&wrt);
  printf("\n Writer is out of CS");
  pthread_exit(NULL);
}

int main()
{
  int n2, i;
  printf("Enter the number of readers:");
  scanf("%d",&n2);
  sem_init(&mutex, 0, 1);
  sem_init(&wrt, 0, 1);
  for (i=0; i<n2; i++)
      {
        pthread_create(&writers[i], NULL, writer, NULL);
        pthread_create(&readers[i], NULL, reader, NULL);
      }
  for (i=0; i<n2; i++)
      {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
      }
}

7)
BANKER'S ALGORITHM
#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;      
    int at;      
    int bt;        
    int rt;        
    int ct;        
    int tat;      
    int wt;        
    int completed;
};

int main() {
    int n, completed = 0, currentTime = 0, minRT, shortest;
    float totalTAT = 0, totalWT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, Burst Time for Process %d: ", i + 1);
        scanf("%d%d%d", &p[i].pid, &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;  
        p[i].completed = 0;  
    }

    printf("\n--- Gantt Chart ---\n");
    printf("0");

    while (completed != n) {
        shortest = -1;
        minRT = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].completed == 0 && p[i].rt < minRT) {
                minRT = p[i].rt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            printf(" | Idle | %d", currentTime + 1);
            currentTime++;
            continue;
        }

        printf(" | P%d | %d", p[shortest].pid, currentTime + 1);
        p[shortest].rt--;
        currentTime++;

        if (p[shortest].rt == 0) {
            p[shortest].completed = 1;
            completed++;

            p[shortest].ct = currentTime;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;

            totalTAT += p[shortest].tat;
            totalWT += p[shortest].wt;
        }
    }

    printf("\n");

    printf("\n--- Process Table ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", totalTAT / n);
    printf("\nAverage WT = %.2f\n", totalWT / n);

    return 0;
}

8)
FIFO PAGE REPLACEMENT ALGORITHM
#include <stdio.h>

int main() {
    int frames, pages;
   
    printf("Enter the number of pages: ");
    scanf("%d", &pages);
   
    int arr[pages];
   
    printf("Enter the page reference string: ");
    for(int i = 0; i < pages; i++) {
        scanf("%d", &arr[i]);
    }
   
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
   
    int Frames[frames];
   
    for(int i = 0; i < frames; i++) {
        Frames[i] = -1;
    }
   
    int pointer = 0;
    int faults = 0;
   
    for (int i = 0; i < pages; i++){
        int page = arr[i];
        int found = 0;
       
        for (int j = 0; j< frames; j++){
            if(Frames[j] == page) {
                found = 1;
                break;
            }
        }
       
        if (!found) {
            Frames[pointer] = page;
            pointer = (pointer + 1) % frames;
            faults++;
           
            printf("Page %d caused a page fault. \nFrames: ", page);
            for (int k = 0; k < frames; k++) {
                if (Frames[k] != -1){
                    printf("%d ", Frames[k]);
                }
                else{
                    printf("- ");
                }
            }
            printf("\n");
        }
        else {
            printf("Page %d hit. Frames unchanged. \n", page);
        }
    }
   
    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
} 
   

9)
LRU PAGE REPLACEMENR ALGORITHM
#include <stdio.h>

#define MAX 10

int main()
{
    int frames[MAX];
    int pages[100], n, fcount;
    int i, j, k, faults = 0;
    
    printf("Enter the number of pages: \n");
    scanf("%d", &n);
    
    printf("Enter the page reference string: \n");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    printf("Enter the number of frames: \n");
    scanf("%d", &fcount);
    
    for(i = 0; i < fcount; i++)
    {
        frames[i] = -1;
    }
    
    int RU[fcount];
    for(i = 0; i < fcount; i++) {
        RU[i] = -1;
    }
    
    for(i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = 0;
        
        for(j = 0; j < fcount; j++)
        {
            if(frames[j] == page)
            {
                found = 1;
                RU[j] = i;
                break;
            }
        }
        
        if(!found)
        {
            faults++;
            int index = 0;
            int min_time = RU[0];
            
            for(k = 1; k < fcount; k++)
            {
                if(RU[k] < min_time)
                {
                    min_time = RU[k];
                    index = k;
                }
            }
            
            frames[index] = page;
            RU[index] = i;
        }
        
        printf("Frames after accessing page %d: ", page);
        for(j = 0; j < fcount; j++) {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    
    printf("Total Page Faults: %d\n", faults);
    
    return 0;
}
