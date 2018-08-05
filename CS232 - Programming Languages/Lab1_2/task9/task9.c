#include <stdio.h>
void message_dispatcher();

int main() {
    
    
    
    typedef union message_content // allows for interpretation
    {
        char _254_chars[254];
        unsigned short _127_shorts[127];
        struct // see a struct
        {
            char name[32];
            time_t creat_t;
            unsigned short size;
            unsigned short inode_ref;
        } fd;
    } MESSAGE_CONTENT;
    typedef struct message
    {
        unsigned short message_type; // how to read the message
        MESSAGE_CONTENT message; // 254 bytes of some content
    } MESSAGE; // 256 bytes in total
    MESSAGE message_buffer[1024];
    
    
    
    
    
    char buffer[255];
    
    FILE *inputfile = NULL;
    
    inputfile = fopen("input.txt","r");
    
    if(inputfile == NULL){
        return(1);
    }
    while (fgets(buffer, sizeof(buffer), inputfile) != NULL) {
        
        printf("content of file: %s\n", buffer);
        message_dispatcher();
        
        
    }
    
}
void message_dispatcher(){



}