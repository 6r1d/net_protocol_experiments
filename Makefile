all:
	gcc -O3 -Wall -Wextra --std=c89 -pedantic -Idyad/src dyad/src/dyad.c cmd_serv.c -o cmd_serv
	gcc -O3 -Wall -Wextra --std=c89 -pedantic -Idyad/src dyad/src/dyad.c request_command.c -o request_command
