/*------*\
| Encoding: UTF-8
| License: MIT
| Original Author: Blake Siviour
| Year: 2022
| Project: appledouble
| Project Summary: Generates appledouble files on any filesystem using copyfile.
| File Summary: Parses the user's arguments.
\*------*/

#include <stdio.h>
#include <string.h>
#include <copyfile.h>
#include <unistd.h>
#include "customDefs.h"
#include "args.h"
#include "info.h"

int ParseArgs(ExecInfo *Info, const int argc, const char *argv[]) {
	//Used for the error messages
	char FullCommand[3333];
	strcpy(FullCommand, argv[0]);
	int FullCommandIndex = strlen(FullCommand);
	int LastPath[] = { -1, 1 };
	
	//Error message templates
	char InvalidArgMessage[] = 
		"Error: invalid option \'%c\' at position %d of argument %d:\n"
		"        %s\n"
		"        %s%s^ Invalid option '%c'%s\n"
		"Use the option 'h' for help\n";
	char InvalidPathMessage[] = 
		"Error: input file could not be opened (\"%s\": argument %d):\n"
		"        %s\n"
		"        %s%s^ failed to open input file%s\n";
	char MultiplePathMessage[] = 
		"Error: multiple input files found (\"%s\" and \"%s\": arguments %d and %d):\n"
		"        %s\n"
		"        %s%s^ multiple inputs provided%s\n";
	
	char FormatRedText[] = "\x1B[31m";
	char FormatClearText[] = "\x1B[0m";
	
	//If there is no console, don't colour text
	if (!isatty(1)) {
		FormatRedText[0] = '\0';
		FormatClearText[0] = '\0';
	}
	
	//FreeArgs is used to prevent the same option from being used multiple times
	int FreeArgs[127];
	for (int i = 0; i < 127; i++) {
		FreeArgs[i] = 1;
	}
	
	for (int i = 1; i < argc; i++) {
		strcat(FullCommand, " \"");
		strcat(FullCommand, argv[i]);
		strcat(FullCommand, "\"");
		
		if (argv[i][0] == '-') {
			int ii = 1;
			
			while (argv[i][ii] != '\0' || ii == 1) {
				//Can't declare variables inside switch statements
				char CommandMarkerOffset[FullCommandIndex + ii + 2];
				int iii;
				//Skip if the current option has been used before
				if ((int)argv[i][ii] < 127 && FreeArgs[(int)argv[i][ii]]) {
					FreeArgs[(int)argv[i][ii]] = 0;
					switch(argv[i][ii]) {
						//Overwrite any existing appledouble files
						case 'f':
							Info->Config.CFFlags += COPYFILE_UNLINK;
							Info->Config.CFFlags -= COPYFILE_EXCL;
							break;
						//Follow symlinks
						case 'r':
							Info->Config.Opt_rr = 1;
							Info->Config.CFFlags -= COPYFILE_NOFOLLOW;
							break;
						//Allow the input file to be an appledouble file
						case 'R':
							Info->Config.Opt_R = 1;
							break;
						//Copy POSIX and ACL information in addition to extended attributes
						case 'a':
							Info->Config.CFFlags += COPYFILE_SECURITY;
							break;
						//Display the version number
						case 'v':
							DisplayInfo(Info, 0);
							return 2;
						//Display the help page
						case 'h':
							DisplayInfo(Info, 1);
							return 2;
						//Display the about page
						case 'A':
							DisplayInfo(Info, 2);
							return 2;
						//Throw an error and exit if an unknown option is provided
						default:
							for (iii = 0; iii < FullCommandIndex + ii + 2; iii++) {
								CommandMarkerOffset[iii] = ' ';
							}
							CommandMarkerOffset[iii] = '\0';
							fprintf(stderr, InvalidArgMessage, argv[i][ii], ii, i, FullCommand, CommandMarkerOffset, FormatRedText, argv[i][ii], FormatClearText);
							return 1;
					}
				}
				ii++;
			}
		} else {
			//Null will never be an option, so it's safe to use
			if (FreeArgs[0]) {
				strcpy(Info->Config.FPath, argv[i]);
				FreeArgs[0] = 0;
				LastPath[0] = i;
				LastPath[1] = FullCommandIndex + 2;
				//Throw an error and exit if the file does not exist or is unreadable
				FILE *InputFile;
				InputFile = fopen(Info->Config.FPath,"r");
				if(InputFile == NULL) {
					char CommandMarkerOffset[FullCommandIndex + 3];
					for (int iii = 0; iii < FullCommandIndex + 2; iii++) {
						CommandMarkerOffset[iii] = ' ';
					}
					CommandMarkerOffset[FullCommandIndex + 2] = '\0';
					fprintf(stderr, InvalidPathMessage, argv[i], i, FullCommand, FormatRedText, CommandMarkerOffset, FormatClearText);
					return 1;
				} else {
					fclose(InputFile);
				}
			//If multiple paths have been provided, throw an error message and exit
			} else {
				char CommandMarkerOffset[FullCommandIndex + 3];
				for (int iii = 0; iii < FullCommandIndex + 2; iii++) {
					char AddChar = ' ';
					if (LastPath[1] < iii) {
						AddChar = '_';
					} else if (LastPath[1] == iii) {
						AddChar = '^';
					}
					CommandMarkerOffset[iii] = AddChar;
				}
				CommandMarkerOffset[FullCommandIndex + 2] = '\0';
				fprintf(stderr, MultiplePathMessage, Info->Config.FPath, argv[i], LastPath[0], i, FullCommand, FormatRedText, CommandMarkerOffset, FormatClearText);
				return 1;
			}
		}
		FullCommandIndex += strlen(argv[i]) + 3;
	}
	
	//If no path was given
	if (Info->Config.FPath[0] == '\0') {
		fprintf(stderr, "Error: No path was provided\n");
		return 1;
	}
	
	return 0;
}