compile:
	@ gcc main.c ./src/global_vars.c ./src/helpers.c ./src/config_parser/config.c ./src/actions.c ./src/seeder.c -o main -Wall -Wall -Wextra -Wshadow -Wconversion -Wcast-qual -Wunreachable-code 