driver: supervisor factory_lines driver.o statemodel.o actions.o state.o accepting.o shipping.o processing.o manufacturing.o
	gcc driver.o statemodel.o actions.o state.o accepting.o shipping.o processing.o manufacturing.o -o driver -lpthread

supervisor: supervisor.c message.h shmem-ex.h
	gcc supervisor.c -o supervisor -lpthread

factory_lines: factory_lines.c message.h shmem-ex.h
	gcc factory_lines.c -o factory_lines -lpthread

driver.o: driver.c actions.h statemodel.h
	gcc -c driver.c

actions.o: actions.c actions.h message.h shmem-ex.h
	gcc -c actions.c -o actions.o -lpthread

statemodel.o: actions.h statemodel.h statemodel.c 
	gcc -c statemodel.c

state.o: state.h state.c
	gcc -c state.c -o state.o
	
accepting.o: state.h accepting.h accepting.c
	gcc -c accepting.c

shipping.o: state.h shipping.h shipping.c
	gcc -c shipping.c

processing.o: state.h processing.h processing.c
	gcc -c processing.c

manufacturing.o: state.h manufacturing.h manufacturing.c
	gcc -c manufacturing.c

clean:
	rm *.o ; rm driver ; rm factory_lines ; rm supervisor
