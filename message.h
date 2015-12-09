#include <sys/types.h>
#define MAXNAMELEN 20

typedef struct {
	uint32_t mtype ; /* 1: request, 2: permission , 3: production */
	struct {
		uint32_t id ; /* ID of sending process */
		uint32_t num_items ; /* Items made during iteration */
		uint32_t iteration ; /* Current iteration */
	} info ;
} msgBuf ;

#define MSG_SIZE (sizeof(msgBuf))

#define BASE_MAILBOX_NAME 0x20

void printMsg( msgBuf *m ) ;
