all:	clean threads procs

procs:
	clang -Wall -Wpedantic -Wextra -Werror -o procs procs.c

threads:
	clang -Wall -Wpedantic -Wextra -Werror -o threads threads.c -pthread
	
clean:
	rm -f *.o procs threads