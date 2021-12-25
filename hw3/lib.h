#include <tcl.h>
#include <readline/history.h>
//history variables
HIST_ENTRY **mylist;
HISTORY_STATE *myhist; 
//variables
//array of strings for auto-complete functionality
//
extern char *all_commands[] ;


typedef struct function
   {
      char* cube ;
      struct function* next ;
      struct function* prev ;
   }cubes_list ;


Tcl_Interp *interp ;
//starts the tcl-interpeter and initializes the history variables. //
void init();
//
int MyExit(Tcl_Interp *);
///////////////////////////////////////////////////////////
//the functions passed as the 3rd parameter to the Tcl_CreateObjCommand function(for less, ls and history), //
//so that when the user enters a command that is not tcl,                                                   //
//creates the command in the interpeter and calls the following func.                                       //
int my_cmd(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
// for intesect //
int cube_intersect(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
//for supercube //
int supercube(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
//for distance. //
int distance(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
//for supercube //
int cube_cover(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
//for sharp //
int sharp(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);

int sharp_f(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);
/////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
//because above functions must return TCL_OK or TCL_ERROR, //
//create the following functions separately(auxiliary),    //
//instead to implement this code inline                    //
//so that they can then be used by more than one functions.//

char *my_bitwise_and_or(char* str1, char *str2, char* operation);
void and_cubes_list(cubes_list* cubes_list1, cubes_list* cubes_list2, cubes_list** and_result);
//auxiliary function for cuve_cover //
int cover(char *str1, char* str2) ;
//auxiliary function for sharp //
void my_sharp(char* str1, char* str2, cubes_list** sharp_result);
//if row_result is valid, my_sharp add it to the sharp_result, with add_list //
void add_list(cubes_list** sharp_result, char* cube);
//emty the list, to reffil it with new content. //
void my_free(cubes_list** list_to_delete);

//chechs if the cubes  str1, str2 are the same length, if their length is even. //
//and if the contains invalid characters .                                      //
int check_input(char* str1, char *str2);
//The my_cmd calls show_history when user enters "hist" command to shell. //
void show_history();
//when the user passes enter, the following function is called to pass the command to the interpeter //

int read_graph(ClientData line, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[]);

int my_rlhandler(char* line) ;
//the following function returns all matches of user input with thl commands and filenames, //
//using the instruction_generator for sthe instructions.                                     //
char **filename_command_completion(const char *, int, int);
char *command_generator(const char *, int);



