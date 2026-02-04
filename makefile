compile:
# 	@ gcc main.c ./src/global_vars.c ./src/helpers.c ./src/config_parser/config.c ./src/actions.c ./src/seeder.c -o main -Wall -Wextra -Wshadow -Wconversion -Wcast-qual -Wunreachable-code
	@ gcc server.c ./src/global_vars.c ./src/helpers.c ./src/actions.c -o server -Wall -Wextra -Wshadow -Wconversion -Wcast-qual -Wunreachable-code
	@ gcc client.c -o client -Wall -Wextra -Wshadow -Wconversion -Wcast-qual -Wunreachable-code