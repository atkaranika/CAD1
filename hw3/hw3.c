#include<stdio.h>
#include <readline/history.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <tcl.h>
#include "lib.h"

int main(int argc , char * argv[])
   {
       
        char* buffer ;
        init();
        //When the user hits their tab key Readline will invoke the filename_command_completion
        rl_attempted_completion_function = filename_command_completion;
        while(1)
            {
                buffer = readline("% ");
                
                //pass it to the haldler to excecute the command.
                if( strcmp(buffer, "quit") == 0)
                    {
                        MyExit(interp);
                        
                        return 0 ;
                    }
                    my_rlhandler(buffer);
            
                    free(buffer);
            }
        
        return 0 ;
    }