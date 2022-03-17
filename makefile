a.out: project2-main.o route-records.o
	gcc main.o route-records.o -o a.out
project2-main.o: project2-main.c route-records.h
	gcc -c project2-main.c -o project2-main.o
route-records.o: route-records.c route-records.h
	gcc -c route-records.c -o route-records.o
clean:
	rm -rf *.o
