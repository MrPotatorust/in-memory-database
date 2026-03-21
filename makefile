compile:
	@ gcc server.c ./src/global_vars.c ./src/helpers.c ./src/config_parser/config.c ./src/actions.c ./src/seeder.c -o server -Wall -Wextra -Wshadow -Wconversion -Wcast-qual -Wunreachable-code
	@ gcc client.c -o client -Wall -Wextra -Wshadow -Wconversion -Wcast-qual -Wunreachable-code