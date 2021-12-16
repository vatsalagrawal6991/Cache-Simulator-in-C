sim : sim.o
	gcc sim.o -o sim -lm -Wall -Wextra --pedantic

sim.o : main.c
	gcc -c main.c -o sim.o -Wall -Wextra --pedantic

run : sim
	./sim $(num_sets) $(num_blocks) $(size_block) $(eviction_policy) $(trace_file) $(output_file)

clean :
	rm -r sim.o sim
