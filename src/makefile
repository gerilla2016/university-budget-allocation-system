PROGRAMS = university-budget
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

all: $(PROGRAMS)

clean:
	rm -f *.o $(PROGRAMS) $(PROGRAMS).exe driver driver.exe

queue.o: queue.c queue.h item.h
	$(CC) $(CFLAGS) -c queue.c

priorityQueueDepartment.o: priorityQueueDepartment.c priorityQueueDepartment.h department.h
	$(CC) $(CFLAGS) -c priorityQueueDepartment.c

resourceManagement.o: resourceManagement.c resourceManagement.h queue.h priorityQueueDepartment.h department.h item.h
	$(CC) $(CFLAGS) -c resourceManagement.c

driver.o: driver.c resourceManagement.h
	$(CC) $(CFLAGS) -c driver.c

$(PROGRAMS): driver.o queue.o priorityQueueDepartment.o resourceManagement.o
	$(CC) $(CFLAGS) -o $(PROGRAMS) driver.o queue.o priorityQueueDepartment.o resourceManagement.o
