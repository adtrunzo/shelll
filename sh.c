#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh.h"

int sh( int argc, char **argv, char **envp )
{
  char *prompt = calloc(PROMPTMAX, sizeof(char));
  char *commandline = calloc(MAX_CANON, sizeof(char));
  char *command, *arg, *commandpath, *p, *pwd, *owd;
  char **args = calloc(MAXARGS, sizeof(char*));
  int uid, i, status, argsct, go = 1;
  struct passwd *password_entry;
  char *homedir;
  struct pathelement *pathlist;

  uid = getuid();
  password_entry = getpwuid(uid);               /* get passwd info */
  homedir = password_entry->pw_dir;		/* Home directory to start
 						   out with*/
 
  prompt = " loosh> ";  
  if ( (pwd = getcwd(NULL, PATH_MAX+1)) == NULL )
  {
    perror("getcwd");
    exit(2);
  }
  owd = calloc(strlen(pwd) + 1, sizeof(char));
  memcpy(owd, pwd, strlen(pwd));
  prompt[0] = ' '; prompt[1] = '\0';

  /* Put PATH into a linked list */
  pathlist = get_path();

int MAXLINE = 1024;


struct command {
	int argc;
	char *argv[MAXARGS];
	enum builtin_t{
		NONE, QUIT, JOBS, BG, FG } builtin;
};


void runBuiltinCommand(struct command *cmd, int bg){
	if(!strcmp(cmd->argv[0], "quit")){
		exit(0);
	}
}


void runSystemCommand(struct command *cmd, int bg){
	pid_t childPid;
	// Fork
	if ((childPid = fork()) < 0){
		perror("fork() error");
	}else if (childPid == 0) {
		if (execvp(cmd->argv[0], cmd->argv) < 0) {
			printf("%s: Command Not Found\n", cmd->argv[0]);
			exit(0);
		}
	}
	else{
		if(bg){
			printf("Child in background [%d]\n", childPid);
		}else{
			wait(&childPid);
		}
	}
}
/*
int parsebuiltin(const char *commandline, struct command *cmd){

	char array[MAXLINE];
	const char delims[10] = " \t\r\n";
	char *line = array;
	char *token;
	char *endline;
	int is_bg;

	if (commandline == NULL){
		perror("command line is NULL\n");
	}

	(void) strncpy(line, commandline, MAXLINE);
	endline = line + strlen(line);

	// build argv list
	cmd->argc = 0;

	while (line < endline) {
		//skip delims
		line += strspn (line, delims);
		if (line >= endline){ break;}

		// find token delim
		token = line + strcspn (line, delims);

		//terminate the token
		*token = '\0';

		//record token as arg
		cmd->argv[cmd->argc++] = line;

		//check if argv is full
		if (cmd->argc >= MAXARGS-1) {break;}

		line = token + 1;

}

	//arg list must end with null 
	cmd->argv[cmd->argc]==NULL;

	if(cmd->argc == 0){
		return 1;
	}
}*/
int parse(const char *commandline, struct command *cmd){
	char array[MAXLINE];
	const char delims[10] = " \t\r\n";
	char *line = array;
	char *token;
	char *endline;
	int is_bg;

	if (commandline == NULL){
		perror("command line is NULL\n");
	}

	(void) strncpy(line, commandline, MAXLINE);
	endline = line + strlen(line);

	// build argv list
	cmd->argc = 0;

	while (line < endline) {
		//skip delims
		line += strspn (line, delims);
		if (line >= endline){ break;}

		// find token delim
		token = line + strcspn (line, delims);

		//terminate the token
		*token = '\0';

		//record token as arg
		cmd->argv[cmd->argc++] = line;

		//check if argv is full
		if (cmd->argc >= MAXARGS-1) {break;}

		line = token + 1;

}

	//arg list must end with null 
	cmd->argv[cmd->argc]==NULL;

	if(cmd->argc == 0){
		return 1;
	}

//	cmd->builtin = parsebuiltin(commandline, cmd);

	if ((is_bg = (*cmd->argv[cmd->argc=1] == '4')) != 0 ){
		cmd->argv[--cmd->argc] = NULL;
	}
	return is_bg;
}

void eval(char *commandline) {
	int bg;
	struct command cmd;

	printf("Evaluating '%s' '\n", commandline);

	//parse commandline into structure
	
	bg = parse(commandline, &cmd);
	//printf("Found command %s\n", cmd.argv[0]);

	if (bg == -1) {return;}

	if (cmd.argv[0] == NULL) {return;}

	if (cmd.builtin == NONE){
		runSystemCommand(&cmd, bg);
	}else{
		runBuiltinCommand(&cmd, bg);
	}
}




  while ( go )
  {
    //printf("> ");
    //
	printf("%s", prompt);
	if((fgets(commandline, MAX_CANON, stdin) == NULL) && ferror(stdin)){
		perror("fgets error");
	}
  	if (feof(stdin)){
		printf("\n");
		exit(0);
	}

	commandline[strlen(commandline)-1] = '\0';
	
	eval(commandline);


		        /* Evaluate */
	//eval(commandline);


			        /* Update job statuses */
//        update_jobs();
	  
	/* print your prompt */

    /* get command line and process */
	
    //fgets(commandline, stdin);
    /* check for each built in command and implement */

     /*  else  program to exec */
    {
       /* find it */
       /* do fork(), execve() and waitpid() */

      /* else */
        /* fprintf(stderr, "%s: Command not found.\n", args[0]); */
    }
  }

} /* sh() */

char *which(char *command, struct pathelement *pathlist )
{
   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */

} /* which() */

char *where(char *command, struct pathelement *pathlist )
{
  /* similarly loop through finding all locations of command */
} /* where() */

void list ( char *dir )
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
} /* list() */

