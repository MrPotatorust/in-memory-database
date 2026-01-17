compile:
	@ gcc main.c ./src/global_vars.c ./src/helpers.c ./src/config.c ./src/actions.c ./src/seeder.c -o main -Wall -Wshadow -Wconversion -Wcast-qual -Wunreachable-code 