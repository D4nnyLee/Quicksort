all: swap rejoin n_recur rand rejoin_dll

swap: swap_sll.c
	gcc swap_sll.c -o swap

rejoin: rejoin_sll.c
	gcc rejoin_sll.c -o rejoin

n_recur: swap_sll.c
	gcc n_recur.c -o n_recur

rand: randtest.c
	gcc randtest.c -o rand

rejoin_dll: rejoin_dll.c
	gcc $< -o $@

clean:
	rm swap rejoin n_recur rand rejoin_dll
