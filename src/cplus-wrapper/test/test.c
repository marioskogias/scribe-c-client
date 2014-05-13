#include <stdio.h>
#include <stdlib.h>

#include <scribe_client/client.h>

int main(int argc, char **argv) 
{
    printf("Opening connection\n");
    struct scribe_client * c = open_connection("83.212.113.88", 1463);

    printf("Sending message\n");
    int res = scribe_log(c, "LOGS", "Hello from new C");
    printf("Result: %d\n", res);

    printf("Closing connection\n");
    close_connection(c);    
    
    return 0;
}
