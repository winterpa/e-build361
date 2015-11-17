#include <semaphore.h>

typedef struct {
   	int order_size;
	sem_t super_sema;
	sem_t factory_sema;
	sem_t print_sema;
} shared_data ;

#define SHMEM_KEY  0x948
#define SHMEM_SIZE sizeof(shared_data)

