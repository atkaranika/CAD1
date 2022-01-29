#include "lib.h"
#include <stdlib.h>
#include<stdio.h>

#include <readline/readline.h>
#include <string.h>
#include <math.h>

#define NUM_COMMAND 172
int **graph_array = NULL;
int size = 0;                                                                         
int rat = 0;  

char *all_commands[] = 
   {
      "after","appen", "apply",	"argc","argv","argv0","array","auto_execok","auto_import","auto_load", 	"auto_mkindex","auto_path","auto_qualify",
      "auto_reset","bgerror","binary","break","catch","cd","chan","clock","close","concat","continue","coroutine","dde","dict", 	"encoding",
      "env" ,"eof" ,"error","errorInfo","load","re_syntax","tcl_startOfNextWord","errorCode","lmap","pwd","tcl_rcFileNam","eval","lrange","read",
      "tcl_startOfPreviousWord","exec","lrepeat","refchan","tcl_traceCompile","exit","lreplace","regexp","tcl_traceExec","expr","lreverse","registry",
      "tcl_version","fblocked","lsearch","regsub","tcl_wordBreakAfter","fconfigure","lset","rename","tcl_wordBreakBefore","fcopy","lsort", "return",
      "tcl_wordchars","file","mathfunc","safe","tcltest","fileevent","mathop","scan","tell","filename","oo::copy","subst","unknown","history",
      "memory","seek","throw","flush","msgcat","self","time","for","my","set","timerate","foreach","namespace","socket","tm","format","next","source", 	
      "trace","gets","nextto","split","transchan","glob","oo::class","string","try","global","oo::define""switch""unload""http","puts","cube_intersect",
      "oo::objdefine","tailcal","unset","if","oo::object", 	"Tcl","update","incr","open ","tcl::prefix","uplevel","info","list","proc","tcl_platform","llength",
      "package","tcl_endOfWord","upvar","interp","parray ","tcl_findLibrary","variable","join","pid","tcl_interactive","vwait","lappend","pkg::create","tcl_library", 	
      "while","lassign","pkg_mkIndex","tcl_nonwordchars","yield","lindex","platform ","tcl_patchLevel","yieldto","linsert","platform::shell", "tcl_pkgPath","zlib",
      "tcl_precision","supercube","distance", "cube_cover","sharp_f","sharp","quit","ls","less","off" , "read_graph" , "draw_graph", "write_graph", "graph_critical_path",
   };



int MyExit()
   {
     
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
      Tcl_CreateObjCommand(interp, "read_graph",(Tcl_ObjCmdProc *)read_graph, "read_graph", NULL);
      Tcl_CreateObjCommand(interp, "draw_graph",(Tcl_ObjCmdProc *)draw_graph, "draw_graph", NULL);
      Tcl_CreateObjCommand(interp, "write_graph",(Tcl_ObjCmdProc *)write_graph, "write_graph", NULL);
      Tcl_CreateObjCommand(interp, "graph_critical_path",(Tcl_ObjCmdProc *)graph_critical_path, "graph_critical_path", NULL);
      //initialise history functions - Begin a session in which the history functions might be used.//
      using_history();
   }

//1.opens the file given by objv[1], in which there are 2 types of inputs: ni->nh w, RAT x //
//2.In order to create the adjacency matrix(which is dinamicaly allocated) firstly reads   //
//3.the entire file, and finds the max i(from all ni) which will be the dimension of the   //
//4.matrix. Then rereads the file and for each record of the format ni->nj w, executes     //
//5.graph_array[i][j] = w, and for record RAT x assigns to global variable rat the value x.//
//6.         n0  n1 n2  .. .. .. nm                                                        //
//7.      n0 -1 w01 w02 .. .. .. w0m   (if there is such a record in file)                 //
//8.      n1 -1 ..  ..  .. .. .. ..                                                        //
//9.      :                                                                                //     
//10.     :                                                                                //     
//11.     nm  -1 -1  -1 ..  .. .. -1                                                       //       
int read_graph(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
   {
      FILE* filePointer ;
      int bufferLength = 255;
      char buffer[bufferLength];
      char * ni;
      char line_buffer[bufferLength];
     
      int n_i, n_j ;                         //ni -> nj in input file. //
      int weight ;


      filePointer = fopen(Tcl_GetString(objv[1]), "r");
      if (filePointer == NULL)
         {
            printf("Error! Unable to open file. Try again\n");
            return TCL_OK;
         }
      //1.to create the array i have to find its size so i find the number of nodes //
      //2.to be used in dynamic memory allocation.                                  //
      size = 0 ;
      while (fgets(buffer, bufferLength, filePointer)) 
         {
            strcpy(line_buffer,buffer);
            ni = strtok(line_buffer," ");
            if (strcmp(ni,"RAT") == 0)
            {
               ni = strtok(NULL," ");
               rat = atoi(ni);
               continue;
            }
            if (atoi(ni+1) > size)
               {
                  size =atoi(ni+1);
               }
            ni = strtok(NULL," ");

            ni = strtok(NULL," ");
            if (atoi(ni+1)  > size)
               {
                  size = atoi(ni+1);
               }
         }
      
      size++ ;
      graph_array = (int**)malloc(size*sizeof(int*));
      for (int i = 0 ; i < size ; i++)
         {
            *(graph_array+i) = (int*)malloc(size*sizeof(int));
            for (int j = 0 ; j < size ; j++)
               {
                  graph_array[i][j] = -1;
               }
         }
     
      fseek(filePointer,0,SEEK_SET);
 
      while (fgets(buffer, bufferLength, filePointer)) 
         {
            strcpy(line_buffer,buffer);
            ni = strtok(line_buffer," ");  
            if (strcmp(ni,"RAT") == 0)
               {
                  continue;
               }  
            n_i = atoi(ni+1);
            ni = strtok(NULL," ");
            ni = strtok(NULL," ");
            n_j = atoi(ni+1);
            weight = atoi(strtok(NULL," ")); 
            graph_array[n_i][n_j] = weight;
         }
      
      fclose(filePointer);
      return TCL_OK ;
   }
//1.In order to create the draw_graph.dot and display the produced png with critical path hightlighted  //
//2.firstly we write in the file in the appropriate form the data of the graph_array and we call the    //
//3.identify_longest_path to find which edges of the graph must be highlighted(color attr in label).    //

int draw_graph(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
   {
      FILE *fp;
      char buffer[50] = {0}; 
      int *longest_path;
      int *dist;
      fp = fopen("draw_graph.dot", "w");

      if (graph_array == NULL)
         {
            printf("you have not read any graph yet\n");
            return TCL_OK;
         }
      if (fp == NULL)
         {
            printf("Unable to open file. Try again!\n");
         }
      
      dist = (int*)malloc(size*sizeof(int));
      identify_longest_path(&dist, &longest_path);

      fputs("digraph {\n", fp);
      fputs("node [fillcolor = \"lightgray\", fontsize = 10]", fp);
      for (int i = 0 ; i < size ; i++)
         {
            for (int j = 0 ; j < size ; j++)
               {
                  if (graph_array[i][j] != -1)
                     {
                        int k = 0 ;
                        while(longest_path[k] != -1)
                           {
                              if (longest_path[k] == i && longest_path[k+1] == j)
                                 {
                                     sprintf(buffer, "\t %d -> %d [label = \" %d \", color = \"blue\"];\n", i, j, graph_array[i][j]);
                                    break;
                                 }
                              k++;
                           }
                        if (longest_path[k] == -1)
                           {
                              sprintf(buffer, "\t %d -> %d [label = \" %d \"];\n", i, j, graph_array[i][j]);
                           }
                       
                        fputs(buffer, fp);
                     }
               }
         }
      fputs("}", fp);
      fclose(fp);
      system("dot -Tpng draw_graph.dot -o outpout.png");
      system("xdg-open outpout.png");
      free(longest_path);
      free(dist);
      return TCL_OK;
   }
int write_graph(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
   {
      FILE *fp;
      char buffer[50] = {0}; 
      fp = fopen(Tcl_GetString(objv[1]), "w");
      if (graph_array == NULL)
         {
            printf("you have not read any graph yet\n");
            return TCL_OK;
         }
      if (fp == NULL)
         {
            printf("Unable to open file. Try again!\n");
            return TCL_OK;
         }
      fputs("digraph {\n", fp);
      fputs("node [fillcolor = \"lightgray\", fontsize = 10]", fp);
      for (int i = 0 ; i < size ; i++)
         {
            for (int j = 0 ; j < size ; j++)
               {
                  if (graph_array[i][j] != -1)
                     {
                        sprintf(buffer, "\t %d -> %d [label = \" %d \"];\n", i, j, graph_array[i][j]);
                        fputs(buffer, fp);
                     }
               }
         }
      fputs("}", fp);
      fclose(fp);
      return TCL_OK;
   }

//1.In order to print the critical path we call the identify_longest_path algorithm, and then we print the slacks //
//2.with the following algorithm.                                                                                 //
//3.Initially all the slacks are equal to inf, slacks of pos are rat - at(dist[i] from identify_longest_path)     //
//4.a queue is kept in which a node is added when has informed from all its succ. about slack and it keeps the    //
//5.worst. When a node is removed from the  queue, imforms all its pred. about slack. Hence, crossing the graph   //
//6.backwards all nodes are informed                                                                              //

int graph_critical_path(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
   {
      int *dist;
      int size_dist = 0;
      int slack[size];
      int pred[size];
      int j;                 //iterator for crtitcal_path. //
      int length_critical_path = 0;
      int col = 0;
      int succ[size];
      int *longest_path;
      queue_list *queue;
      queue_list *current;
   
      dist = (int*)malloc(size*sizeof(int));
      identify_longest_path(&dist, &longest_path);

      printf("=====Critical path=======\n");
      j = 0;
      while(longest_path[j] != -1)
         {
            printf("node %d\n", longest_path[j]);
            j++;
         }

      //print slack //
      //1.start from the pos and backtrace //
      queue = (queue_list*)malloc(sizeof(queue_list));
      if (queue == NULL)
         {
            printf("Error! Memory not allocated\n");
            free(longest_path);
            free(queue);
            exit(0);
         }
      queue->prev = NULL;
      queue->next = NULL; 
      queue->node = -1;  

      j = 0;
      //Initially entered in queue only pos .//
      //1.In order to see when the node i will enter the queue we keep information, //
      //2.about how many successors informed him about slack.                       //
      for(int i = 0 ; i < size ; i++)
         {
            slack[i] = __INT_MAX__;
            //find if node-i is a po. //
            succ[i] = 0;
            for(col = 0; col < size; col++)
               {
                  if (graph_array[i][col] != -1)
                     {
                        succ[i]++ ;
                     }
                
               }
            if (succ[i] == 0)
               {
                  slack[i] = rat - dist[i];
                  add_queue_list(&queue, i);
               }
         }

      current = queue->next;
      while(current != NULL)
         {
            //for all predecessors of current. //
            for(int row = 0 ; row < size ; row++)
               {
                  if (graph_array[row][current->node] != -1)
                     {
                        //keep the worst slack. //
                        if (slack[row] > slack[current->node] + (dist[current->node] - (dist[row] + graph_array[row][current->node])))
                        {
                            slack[row] = slack[current->node] + (dist[current->node] - (dist[row] + graph_array[row][current->node]));
                        }
                       succ[row]--;
                       
                        if (succ[row] == 0)
                           {
                              add_queue_list(&queue, row);
                              continue;
                           }
                     }  
               }

            //free current(first node). //
            current->prev->next = current->next;
            if(current->next!=NULL)
               {
                  current->next->prev = current->prev;
               }
            free(current);
            current = queue->next;
         }
      printf("Slack of all nodes\n");
      //print critical_path. //
      for(int i = 0; i < size ; i++)
         {
            printf("slack %d: %d\n", i, slack[i]);
         }

      //find which nodes have th sizeimum distance, and add them to the queue. //
      free(longest_path);
      free(dist);
      free(queue);
      return TCL_OK;
   }

//1.In order to identify longest path firstly we run topo-sort to find the node with max distance.     //
//2.and we keep the previous of each node which gives the max distance, then we begin with the po with //
//3.max dist and crossing backward the graph we add to the path each recorded prev[i]                  //
void identify_longest_path(int **dist, int **longest_path)
   {
      int pred[size];
      int prev[size];            //the previous of each node that gives it the greatest dist. //
      int final_node;            //will be the node with the longest distance,to find the longest path. //
      queue_list* queue;
      queue_list* current;
      int* local_dist = *dist;
      
      queue = (queue_list*)malloc(sizeof(queue_list));
      if (queue == NULL)
         {
            printf("Error! Memory not allocated\n");
            exit(0);
         }
      queue->prev = NULL;
      queue->next = NULL;
      //initialize the list and insert the input nodes in list. //
      for(int i = 0 ; i < size ; i++)
         {
            local_dist[i] = 0;
            pred[i] = 0;
            prev[i] = i;                  //1.Initally each node has previous itself         //
                                          //2.so than the algorithm stops when it find a PI .//
                                          //3.than it when prev[i] = i.                      //

            //count predecessors of node-i. //
            for(int row = 0 ; row < size ; row++)
               {
                  if (graph_array[row][i] != -1)
                     {
                        pred[i]++;
                     }  
               }
            //Initially enter to the array only pi. //
            if (pred[i] == 0)
               {
                  add_queue_list(&queue, i);
               }
         }
     
     
      //1.current will always be the head->next, because we always look at the first node of the list.   //
      //2.then all its successors are informed of the new distance info and eventually keep the largest, //
      //3.when a node receive an update from all of its pred, it enters to the queue, (if pred[i]) == 0. //
      current = queue->next;
      final_node = current->node;     //Initialy final_node is one of the PIs. //
      while(current != NULL)
         {
            //for all sucessors of current. //
            for(int col = 0 ; col < size ; col++)
               {
                  if (graph_array[current->node][col] != -1)
                     {
                        if (local_dist[current->node]+graph_array[current->node][col] > local_dist[col])
                           {
                              local_dist[col] = local_dist[current->node]+graph_array[current->node][col];
                              prev[col] = current->node;
                           }
                        
                        pred[col]--;
                        if (pred[col] == 0)
                           {
                              add_queue_list(&queue, col);
                           }
                     }
               }
            //free current(first node). //
            current->prev->next = current->next;
            if(current->next!=NULL)
               {
                  current->next->prev = current->prev;
               }
            free(current);
            current = queue->next;
         }
      //find final_node and crossing back the graph, find the longest path. //
      for(int i = 0; i < size; i++)
         {
            if (local_dist[final_node] <= local_dist[i])
               {
                  final_node = i;
               }
         }
     
      int i = final_node;
      *longest_path =  (int*)malloc(sizeof(int));
      (*longest_path)[0] = -1;
      int j = 1 ;
      while(prev[i] != i)
         {   
            *longest_path  = (int*)realloc( *longest_path ,sizeof(int)*(j+1)) ;
            if (*longest_path == NULL)
               {
                  perror("realloc fails!");
               }
             (*longest_path)[j] = i;
            i = prev[i];
            j++;
         }
      *longest_path  = (int*)realloc( *longest_path ,sizeof(int)*(j+1)) ;
      if (*longest_path == NULL)
         {
            perror("realloc fails!");
         }
       (*longest_path)[j] = prev[i];

      reverse(*longest_path , j+1);
      free(queue);
      return ; 
   }

void reverse(int arr[], int n)
{
    for (int low = 0, high = n - 1; low < high; low++, high--)
    {
        int temp = arr[low];
        arr[low] = arr[high];
        arr[high] = temp;
    }
}

void add_queue_list(queue_list** queue, int node)
   {
      queue_list* new_node;
      new_node = (queue_list*)malloc(sizeof(queue_list));
      new_node->node = node;
      new_node->next = NULL; 
      queue_list* current;
      
      for(current = *queue ; current != NULL ; current = current->next)
         {
            if (current->next == NULL)
               {
                  current->next = new_node ;
                  new_node->prev = current ;
                  break; 
               }
         }
   }
//1.input format for cube_intersect, supercube, distance, cube_cover, sharp //
//2.     <command> <cube1> <cube2>                                          //
//3.         |       |        |                                             //
//4.eg.  supercube 101010   010101                                          //

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
      //1.intersect is the result of intersect operation. If 2 consecutive zeros are found  //
      //2.then the distance counter(dinstance) increases by 1. The counter variable becomes //
      //3.2 only when the zeros are in appropriate positions.                               //
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

//1.sharp_f cube1 {cube2 cube3 cube4.....cube_n}. //
//2.sharp_result1 = cube1 sharp cube2.            //
//3.sharp_result2 = cube1 sharp cube3.            //
//4.and_result = sharp_result1 and sharp_result2. //
//5.sharp_result2 = cube1 sharp cube4.            //
//6.and_result = and_result and sharp_result2     //

//absorb operation is included in and operation.  //
int sharp_f(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
   {
      cubes_list* sharp_result1 ;   //left_cube # first_cube. //
      cubes_list* sharp_result2;    //left_cube # (i-th in i iteration). //
      cubes_list* and_result ;      //final result. //
      cubes_list* current ;         //list iterator. //
      cubes_list* and_result_temp;  //1.provision result of and (step-3)                       //
                                    //2.because in each iteration we will have a               //
                                    //3.new result of the and operation, the "and_list"must    //
                                    //4.be emty, and because we need the result for the next   //
                                    //5.iteration we keep it in the "and_result_temp".         //

      char* input ;                 //in the objv[2] position all the contents are inserted. //

      char* objv1 ;
      char* objv2 ;
      //1.(left cube) # f : if the first argument is "off" then the left cube for the sharp operation //
      //2.will be 11 11 .. and the f will be the second argument.                                     //
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
      sharp_result1->prev = NULL;
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
                  //delete all nodes except for the first one. //
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


void my_sharp(char* str1, char* str2, cubes_list** sharp_result)
   {
      char* row_of_result ;      //1.in each iteration row_of_result is found and //
                                 //2.if it is valid entered in the array.         //
      char substring_str1[3];    //3.two digits of str1 and str2 bettween         //
      char substring_str2[3];    //4.whitch is executed binary and                //
      char* and_result ;
      int invalid  = 0;          //1.is set 1 if a cube is invalid //
                                 //2.(contains 00)                 //
      int row_counter = 0 ; 
      row_of_result = (char*)malloc(strlen(str1)*sizeof(char)+1);
      
      //1.the rows of the final array(sharp result) will be the sizeimum //
      //2.cube digit number/2                                           //
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
            //1.the result "and" is inserted in the i-th position of sting   //
            //2.where i is the current row of the result which is calculated.//
            row_of_result[2*i] = and_result[0];
            row_of_result[2*i+1] = and_result[1];
            add_list(sharp_result, row_of_result);
            free(and_result);
         }
      absorb(sharp_result);
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

//1.checks if input of user has odd number of digits,       //
//2.if the two cubes have not the same number of digits,   //
//3.if one of cubes has a invalid digit(eg. 2,3,4,....),   //
//4.i.e != 0 or 1
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

//my_bitwise_and_or performs "and" or "or" operation depending on operation argument. // 
char *my_bitwise_and_or(char* str1, char *str2, char* operation)
   {
      char *result ;
      result = (char*)calloc(strlen(str1)+1, sizeof(char));
   
      //1.convert str1,str2 to int and perform bitwise AND operation,  //
      //2.append to result string.                                     //
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
//1.and_bubes_list performs and operation between 2 list of cubes. //
//2.     cube_list1 and cube_list2 = cube_list3.                   //
//3.        |        |       |            |                        //
//4.eg.  101010            111010      101010                      //
//5.     111101            111111      111101                      //
//6.     010111            101001      010111                      //

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

//1.shows the whole history of inputs, with the following manner:                                    //
//2.history_get_history_state: Return a structure describing the current state of the input history. //
//3.Return a NULL terminated array of HIST_ENTRY * which is the current input history.               //
//4.Element 0 of this list is the beginning of time. If there is no history, return NULL.            //
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
            if (realloc(buffer, sizeof(objv[i])+3) == NULL)
               {
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
            int rc = Tcl_Eval(interp, line);
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



