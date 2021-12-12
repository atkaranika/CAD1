#include "lib.h"
#include <stdlib.h>
#include<stdio.h>

#include <readline/readline.h>
#include <string.h>

#define NUM_COMMAND 168

char *all_commands[] = 
   {
      "after", 
      "appen", 
      "apply",	
      "argc",
      "argv",
      "argv0",
      "array",
      "auto_execok",
      "auto_import",
      "auto_load", 	
      "auto_mkindex",
      "auto_path",
      "auto_qualify",
      "auto_reset",
      "bgerror",
      "binary",
      "break",
      "catch",
      "cd",
      "chan",
      "clock",
      "close",
      "concat",
      "continue",
      "coroutine",
      "dde",
      "dict", 	
      "encoding",
      "env" ,
      "eof" ,
      "error",
      "errorInfo",
      "load",
      "re_syntax",
      "tcl_startOfNextWord",
      "errorCode",
      "lmap",
      "pwd",
      "tcl_rcFileNam",
      "eval",
      "lrange",
      "read",
      "tcl_startOfPreviousWord",
      "exec",
      "lrepeat",
      "refchan",
      "tcl_traceCompile",
      "exit",
      "lreplace",
      "regexp",
      "tcl_traceExec",
      "expr",
      "lreverse",
      "registry",
      "tcl_version",
      "fblocked",
      "lsearch",
      "regsub",
      "tcl_wordBreakAfter",
      "fconfigure",
      "lset",
      "rename",
      "tcl_wordBreakBefore",
      "fcopy",
      "lsort", 
      "return",
      "tcl_wordchars",
      "file",
      "mathfunc",
      "safe",
      "tcltest",
      "fileevent",
      "mathop",
      "scan",
      "tell",
      "filename",
      "memory",
      "seek",
      "throw",
      "flush",
      "msgcat",
      "self",
      "time",
      "for",
      "my",
      "set",
      "timerate",
      "foreach",
      "namespace",
      "socket",
      "tm",
      "format",
      "next",
      "source", 	
      "trace",
      "gets",
      "nextto",
      "split",
      "transchan",
      "glob",
      "oo::class",
      "string",
      "try",
      "global",
      "oo::copy",
      "subst",
      "unknown",
      "history",
      "oo::define",
      "switch",
      "unload",
      "http",
      "oo::objdefine",
      "tailcal",
      "unset",
      "if",
      "oo::object", 	
      "Tcl",
      "update",
      "incr", 	
      "open ",	
      "tcl::prefix", 	
      "uplevel",
      "info",
      "package",
      "tcl_endOfWord",
      "upvar",
      "interp",
      "parray ",
      "tcl_findLibrary",
      "variable",
      "join", 	
      "pid", 	
      "tcl_interactive", 	
      "vwait",
      "lappend", 	
      "pkg::create",	
      "tcl_library", 	
      "while",
      "lassign", 	
      "pkg_mkIndex", 	
      "tcl_nonwordchars", 	
      "yield",
      "lindex", 	
      "platform ",	
      "tcl_patchLevel", 	
      "yieldto",
      "linsert",
      "platform::shell", 	
      "tcl_pkgPath", 	
      "zlib",
      "list", 
      "proc",	
      "tcl_platform",
      "llength",
      "puts",
      "cube_intersect",
      "tcl_precision",
      "supercube",
      "distance", 
      "cube_cover",
      "sharp_f",
      "sharp",
      "quit",
      "ls",
      "less",
      "off",
   };

int MyExit(Tcl_Interp *interp)
   {
      Tcl_DeleteInterp(interp); 
      rl_clear_history();
      Tcl_Finalize();
      return 0;
   }

void init()
   {
      interp = Tcl_CreateInterp() ;
      Tcl_CreateObjCommand(interp, "ls",(Tcl_ObjCmdProc *)my_cmd, NULL, NULL);
      Tcl_CreateObjCommand(interp, "less",(Tcl_ObjCmdProc *)my_cmd, NULL, NULL);
      Tcl_CreateObjCommand(interp, "history",(Tcl_ObjCmdProc *)my_cmd, NULL, NULL);
      Tcl_CreateObjCommand(interp, "cube_intersect",(Tcl_ObjCmdProc *)cube_intersect, NULL, NULL);
      Tcl_CreateObjCommand(interp, "supercube",(Tcl_ObjCmdProc *)supercube, NULL, NULL);
      Tcl_CreateObjCommand(interp, "distance",(Tcl_ObjCmdProc *)distance, NULL, NULL);
      Tcl_CreateObjCommand(interp, "cube_cover",(Tcl_ObjCmdProc *)cube_cover, NULL, NULL);
      Tcl_CreateObjCommand(interp, "sharp",(Tcl_ObjCmdProc *)sharp, NULL, NULL);
      Tcl_CreateObjCommand(interp, "cover_f",(Tcl_ObjCmdProc *)sharp, NULL, NULL);
      Tcl_CreateObjCommand(interp, "sharp_f",(Tcl_ObjCmdProc *)sharp_f, NULL, NULL);
      Tcl_CreateObjCommand(interp, "off",(Tcl_ObjCmdProc *)sharp_f, "off", NULL);
      //initialise history functions - Begin a session in which the history functions might be used.//
      using_history();
   }

int cube_intersect(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
   {  
      char* result ;
      if (check_input(Tcl_GetString(objv[1]), Tcl_GetString(objv[2])) != 0)
         {  
            return TCL_OK;
         }
      result = my_bitwise_and_or(Tcl_GetString(objv[1]), Tcl_GetString(objv[2]), "and");
      printf("%s\n", result);
      free(result);
      return TCL_OK ;
   }

int supercube(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
   {  
      char* result ;
      if (check_input(Tcl_GetString(objv[1]), Tcl_GetString(objv[2])) != 0)
         {  
            return TCL_OK;
         }
      result = my_bitwise_and_or(Tcl_GetString(objv[1]), Tcl_GetString(objv[2]), "or");
      printf("%s\n", result);
      free(result);
      return TCL_OK ;
   }
int distance(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
   {
      int distance = 0;
      int counter = 0;
      char * intersect ;

      if (check_input(Tcl_GetString(objv[1]), Tcl_GetString(objv[2])) != 0)
         {  
            return TCL_OK;
         }
      //intersect is the result of intersect operation. If 2 consecutive zeros are found  //
      //then the distance counter(dinstance) increases by 1. The counter variable becomes //
      //2 only when the zeros are in appropriate positions.                               //
      intersect = my_bitwise_and_or(Tcl_GetString(objv[1]), Tcl_GetString(objv[2]), "and");
      for(int i = 0 ; i < strlen(intersect) ;  i++)
         {  
            if (intersect[i] == '0')
               {
                  counter++;
               }
            if (i % 2 == 1)
               {
                  if  (counter == 2)
                     {
                        distance++;
                     }
                  counter = 0;
               }
         }

      printf("distance: %d\n", distance);
      return TCL_OK ;
   }

int cube_cover(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
   {
      if (check_input(Tcl_GetString(objv[1]), Tcl_GetString(objv[2])) != 0)
         {  
            return TCL_OK;
         }
      if (cover(Tcl_GetString(objv[1]), Tcl_GetString(objv[2])))
         {
            printf("yes\n");
            return TCL_OK;
         }
      printf("no\n");
      return TCL_OK;
   }

//sharp_f left cube {first_cube, second_cube.......,last_cube}             //
//1. sharp operation between the left and the first cube of the list       //
//2. the same for the second cube of function,                             //
//3. and operation between the results from 1. and 2.                      //
//4. sharp operation bretween left and thrird cube of the list.            //
//5. and operation between the results from 4. and 5.                      //
//repeat the process (add-sharp) until we reach the last cube of the list. //

int sharp_f(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
   {
      cubes_list* sharp_result1 ;   //left_cube # first_cube. //
      cubes_list* sharp_result2;    //left_cube # (i-th in i iteration). //
      cubes_list* and_result ;      //final result. //
      cubes_list* current ;         //list iterator. //
      cubes_list *and_result_temp;  //provision result of and (step-3)                       //
                                    //because in each iteration we will have a               //
                                    //new result of the and operation, the "and_list"must    //
                                    //be emty, and because we need the result for the next   //
                                    //iteration we keep it in the "and_result_temp".         //

      char* input ;                 //in the objv[2] position all the contents are inserted. //

      char* objv1 ;
      char* objv2 ;
      //(left cube) # f : if the first argument is "off" then the left cube for the sharp operation //
      //will be 11 11 .. and the f will be the second argument.                                     //
      if (line == "off")         
         {
            objv2 = Tcl_GetString(objv[1]) ;
            input = strtok(Tcl_GetString(objv[1]), " ") ;
            objv1 = (char*)malloc(strlen(input)*sizeof(char)+1) ;
            for (int i = 0 ; i < strlen(input) ; i++)
               {
                  objv1[i] = '1';
               }
            objv1[strlen(input)] = '\0';
         }
      else 
         {
            objv1 = Tcl_GetString(objv[1]) ;
            objv2 = Tcl_GetString(objv[2]) ;
            input = strtok(Tcl_GetString(objv[2]), " ") ;
         }
     
      sharp_result1 = (cubes_list*)malloc(sizeof(cubes_list));
      sharp_result1->prev = NULL ;
      sharp_result1->next = NULL;
      
      sharp_result2 = (cubes_list*)malloc(sizeof(cubes_list));
      sharp_result2->prev = NULL ;
      sharp_result2->next = NULL;

      and_result_temp = (cubes_list*)malloc(sizeof(cubes_list));
      and_result_temp->prev = NULL ;
      and_result_temp->next = NULL;

      and_result = (cubes_list*)malloc(sizeof(cubes_list));
      and_result->prev = NULL ;
      and_result->next = NULL;
      //sharp operation between the left and the first cube of the list. //
      my_sharp(objv1, input, &sharp_result1);
      input = strtok(NULL, " ");
      if (input != NULL)
         {
            if (check_input(objv1, input) != 0)
               {  
                  my_free(&sharp_result1);
                  my_free(&sharp_result2);
                  my_free(&and_result);
                  my_free(&and_result_temp);
                  
                  free(sharp_result1);
                  free(sharp_result2);
                  free(and_result);
                  free(and_result_temp);
                  return TCL_OK;
               }
            //the same for the second cube of function. //
            my_sharp(objv1, input, &sharp_result2);
            //and operation between two sharp result. //
            and_cubes_list(sharp_result1, sharp_result2,  &and_result);
            and_result_temp->next = and_result->next ;
            and_result->next = NULL ;
            while(1)
               { 
                  input = strtok(NULL, " ");
                  if (input == NULL)
                     {
                        break ;
                     }
                  my_free(&sharp_result2);
                  //sharp operation bretween left and i-th cube of the list //  
                  my_sharp(objv1, input, &sharp_result2);
                  //and operation between the results from previous and operation result and current sharp//
                  and_cubes_list(and_result_temp, sharp_result2,  &and_result);
                  and_result_temp->next = and_result->next ;
                  and_result->next = NULL ;
               }
            printf("-------RESULT------------\n");
            and_result->next = and_result_temp->next ;
            and_result_temp->next = NULL ;
            for(current = and_result->next ; current != NULL ; current = current->next)
               {
                  printf("%s\n", current->cube);
               }
         }
         else 
            {
               printf("-------RESULT------------\n");
               for(current = sharp_result1->next ; current != NULL ; current = current->next)
                  {
                     printf("%s\n", current->cube);
                  }
            }
         if (line == "off")
            {
               free(objv1);
            }
         my_free(&sharp_result1);
         my_free(&sharp_result2);
         my_free(&and_result);
         my_free(&and_result_temp);
         
         free(sharp_result1);
         free(sharp_result2);
         free(and_result);
         free(and_result_temp);
   }

void my_free(cubes_list** list_to_delete)
{
   cubes_list* current ; 
   if ((*list_to_delete)->next == NULL)
      {
         return ;
      }
   if ((*list_to_delete)->next->next == NULL)
      {
         free((*list_to_delete)->next->cube);
         free((*list_to_delete)->next);
         return ;
      }
   for(current = (*list_to_delete)->next ->next; current->next != NULL ; current = current->next)
      {
         free(current->prev->cube);
         free(current->prev);
      }
   free(current->prev->cube);
   free(current->prev);
   free(current->cube);
   free(current);
   (*list_to_delete)->next = NULL;
}
int cover(char *str1, char* str2)
   {
      for(int i = 0 ; i < strlen(str1) ; i++)
         {
            if (str1[i] < str2[i])
               {
                  return 0 ; 
               }
         }
      return 1 ;
   }

int sharp(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
   {
      int result_size ;
      cubes_list* sharp_result ; 
      char* fisrt_cube ;

      sharp_result = (cubes_list*)malloc(sizeof(cubes_list));
      sharp_result->prev = NULL ;
      sharp_result->next = NULL;

      if (check_input(Tcl_GetString(objv[1]), Tcl_GetString(objv[2])) != 0)
         {  
            return TCL_OK;
         }
      my_sharp(Tcl_GetString(objv[1]), Tcl_GetString(objv[2]), &sharp_result) ;

      cubes_list* current;
      for(current = sharp_result->next ; current != NULL ; current = current->next)
         {
            printf("%s\n", current->cube);
         }
      free(sharp_result);
      return TCL_OK;
   }

void my_sharp(char* str1, char* str2, cubes_list** sharp_result)
   {
      char* row_of_result ;      //in each iteration row_of_result is found and //
                                 //if it is valid entered in the array.         //
      char substring_str1[3];    //two digits of str1 and str2 bettween         //
      char substring_str2[3];    //whitch is executed binary and                //
      char* and_result ;
      int invalid  = 0;          //is set 1 if a cube is invalid //
                                 //(contains 00)                 //
      int row_counter = 0 ; 
      row_of_result = (char*)malloc(strlen(str1)*sizeof(char)+1);
      
      //the rows of the final array(sharp result) will be the maximum //
      //cube digit number/2 //
      for(int i = 0 ; i < strlen(str1)/2 ; i+=1)
         {  
            invalid = 0 ;
            //substring of right and left cube to take the i-th literal cube encoding //
            memcpy(substring_str1, &str1[2*i], 2) ;
            memcpy(substring_str2, &str2[2*i], 2) ;
            substring_str1[2] = '\0';
            substring_str2[2] = '\0';

            //substring_str2 inverted //
            substring_str2[0] = substring_str2[0] == '1' ? '0' : '1' ;
            substring_str2[1] = substring_str2[1] == '1' ? '0' : '1' ;
        
            and_result = my_bitwise_and_or(substring_str1, substring_str2, "and");
            //if and _result is invalid then we continue without //
            //include to the final array.                        //
            if (strcmp(and_result, "00") == 0)
               {
                  free(and_result);
                  continue ;   
               }
            //initially the result is initialiazed to str1 // 
            strcpy(row_of_result, str1);
            //check if exists "00" //
            for(int j = 0 ; j < strlen(row_of_result) ; j+=2)
               {
                  if (row_of_result[j] == '0' && row_of_result[j+1] == '0')
                     {
                        invalid = 1 ;
                        break ; 
                     }
               }
            if (invalid == 1) 
               {
                  free(and_result);
                  continue ;
               }
            //the result "and" is inserted in the i-th position of sting //
            //where i is the current row of the result which is calculated.//
            row_of_result[2*i] = and_result[0];
            row_of_result[2*i+1] = and_result[1];
            add_list(sharp_result, row_of_result);
            free(and_result);
         }
      
      free(row_of_result);
   }


void add_list(cubes_list** sharp_result, char* cube)
   {
      cubes_list* new_cube;
      new_cube = (cubes_list*)malloc(sizeof(cubes_list));
      new_cube->cube = (char*)calloc(strlen(cube)+1, sizeof(char));
      new_cube->next = NULL ; 
      strcpy(new_cube->cube, cube);

      cubes_list* current;
      
      for(current = *sharp_result ; current != NULL ; current = current->next)
         {
            if (current->next == NULL)
               {
                  current->next = new_cube ;
                  new_cube->prev = current ;
                  break; 
               }
         }
   }

void absorb(cubes_list** sharp_result)
   {
      cubes_list* current;
      cubes_list* current_in;
      cubes_list* current_next ; //free(current_in) and in the next iteration i want to get current->next. //
         
      for(current = (*sharp_result)->next ; current != NULL ; current = current->next)
         {
            for(current_in = (*sharp_result)->next ; current_in != NULL ; current_in = current_next)
               {
                  if (current != current_in)
                     {
                        if (cover(current->cube, current_in->cube) || current->cube == current_in->cube)
                           {
                              current_in->prev->next = current_in->next ;
                              if (current_in->next != NULL)
                              {
                                  current_in->next->prev = current_in->prev ;
                              }
                              current_next = current_in->next ;
                              free(current_in->cube);
                              free(current_in);
                           }
                           else current_next = current_in->next;
                     }
                  else current_next = current_in->next;
               }
         }
   }

int check_input(char* str1, char *str2)
   {
      if (strlen(str1) != strlen(str2))
         {
            printf("the cubes do not have the same number of columns\n");
            return -1 ;
         }
      if (strlen(str1) % 2 != 0)
         {
            printf("the cubes have odd number of digits\n");
            return -1 ;
         }
      for(int i = 0 ; i < strlen(str1) ; i++)
         {
            if ((str1[i] != '0' && str1[i] != '1' ) || (str2[i] != '0' && str2[i] != '1')) 
               {
                    printf("%c , %c", str1[i] , str2[i]) ;
                  printf("The digits of the cube must be 0 or 1\n");
                  return -1 ;
               }
         }
      return 0 ;
      
   }
char *my_bitwise_and_or(char* str1, char *str2, char* operation)
   {
      char *result ;
      result = (char*)calloc(strlen(str1)+1, sizeof(char));
   
      // convert str1,str2 to int and perform bitwise AND operation, //
      //append to result string.                                     //
      if (strcmp(operation,"and") == 0)
         {
            for(int i = 0 ; i < strlen(str1); i++)
               {
                  result[i] =  (char)((str1[i] - '0' & str2[i] - '0') + '0');
                  
               }
            result[strlen(str1)] = '\0';
         }
      else if (strcmp(operation,"or") == 0)
         {
            for(int i = 0 ; i < strlen(str1) ; i++)
               {
                  result[i] =  (char)((str1[i] - '0' | str2[i] - '0') + '0');
               }
         }

      return result ; 
   }

void and_cubes_list(cubes_list* cubes_list1, cubes_list* cubes_list2, cubes_list** and_result)
   {
      cubes_list* current1 ; 
      cubes_list* current2 ; 
      char* row_of_result ;
      int invalid = 0 ;
  
      for(current1 = cubes_list1->next ; current1 != NULL ; current1 = current1->next)
         {
            for(current2 = cubes_list2->next ; current2 != NULL ; current2 = current2->next)
               {
                  invalid = 0 ;
                  row_of_result = my_bitwise_and_or(current1->cube, current2->cube, "and");
                  for(int j = 0 ; j < strlen(row_of_result) ; j+=2)
                     {
                        if (row_of_result[j] == '0' && row_of_result[j+1] == '0')
                           {
                              invalid = 1 ;
                              break ; 
                           }
                     }
                  if (invalid == 1) 
                     {
                        free(row_of_result);
                        continue ;
                     }
                  add_list(and_result, row_of_result);
                  free(row_of_result);
               }
         }
      absorb(and_result);
   }

//shows the whole history of inputs, with the following manner:                                    //
//history_get_history_state: Return a structure describing the current state of the input history. //
//Return a NULL terminated array of HIST_ENTRY * which is the current input history.               //
//Element 0 of this list is the beginning of time. If there is no history, return NULL.            //
void show_history()
   {
      myhist = history_get_history_state ();
      //retrieve the history list. //
      mylist = history_list ();
      for (int i = 0; i < myhist->length; i++) 
         { 
            //output history list. //
            printf ("%d. %s  %s\n",i+1 ,mylist[i]->line, mylist[i]->timestamp);
         }
   }

int my_cmd(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
   {
      int i = 0 ;
      char *buffer =  (char*)malloc(strlen(Tcl_GetString(*objv))+1);

      strcpy(buffer ,  Tcl_GetString(*(objv)));
      if (strcmp(buffer, "history") == 0)
         {
            show_history();
            free(buffer);
            return TCL_OK ;
         }
      
      //concatenate all separate obv[i] to get the whole command line //
      for (i =  1 ; i <  objc ; i++)
         {
            //+3 : 2 bytes for char '\0' at strcat and 1 for space " " //
            if(realloc(buffer, sizeof(objv[i])+3) == NULL){
               perror("realloc fails!");
            }
            strcat(buffer ," ");
            strcat(buffer , Tcl_GetString(*(objv+i)));
         }

      //pass the whole command line to system //
      if (system(buffer) == -1)
         {
            Tcl_Obj *infoObj = Tcl_GetVar2Ex(interp, "errorInfo", NULL, TCL_GLOBAL_ONLY);
            printf("%s\n",Tcl_GetString(infoObj));
            free(buffer);
            return TCL_ERROR;
         }
      free(buffer);
      return TCL_OK;
   }

int my_rlhandler( char* line)
   {
      if (line==NULL)
         {
            // Ctrl-D will allow us to exit nicely
               printf( "\nNULLBURGER\n");
         
         }
      else
         {
            // If line wasn't empty, store it so that uparrow retrieves it, and we introduce it in the history //
            if (*line!=0)
               {
                  add_history(line);
               }
            
            //give to interpeter the command to execute //
            int rc = Tcl_Eval( interp, line);
            if (rc != TCL_OK)
               {
                  Tcl_Obj *infoObj = Tcl_GetVar2Ex(interp, "errorInfo", NULL, TCL_GLOBAL_ONLY);
                  printf("%s\n",Tcl_GetString(infoObj));
                  return TCL_ERROR;
               }
            return TCL_OK;

         }
   }
//Each time it’s called, command_generator returns a completion that matches the given text. When it can’t find any more options it returns NULL. //
char* command_generator(const char *text, int state)
   {
      //static because we want it will return to the point from which it started. //
      static int list_index, len;
      char *name;
      //state = 0 => first call of the function. //
      if (!state) 
         {
            list_index = 0;
            len = strlen(text);
         }
      //controls one by one the current input with its commands //
      while ((name = all_commands[list_index++])) 
         {
             if(list_index == NUM_COMMAND)
               {
                  break ; 
               }
            if (strncmp(name, text, len) == 0) 
               {
                  return strdup(name);
               }
         }
      //when the matches with its commands are finished it returns the match with the file. //
      return NULL;
   }

char** filename_command_completion(const char *text, int start, int end)
   {
      //this list includes matches from text(current input of user) and tcl commands and text and filenames from current Directory. //
      char ** return_array = (char **)NULL ;
      //if start = 0. This means that we should complete with tcl instuctions. //
      if (start == 0)
         {
            return_array = rl_completion_matches(text, command_generator);
         }
      // else auto-complete with filename is done automatically by GNU-readline. //
      return return_array;
   }



