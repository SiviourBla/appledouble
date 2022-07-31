/*------*\
| Encoding: UTF-8
| License: MIT
| Original Author: Blake Siviour
| Year: 2022
| Project: appledouble
| Project Summary: Generates appledouble files on any filesystem using copyfile.
| File Summary: Only contains the main function, calls everything else and specifies the program's version.
\*------*/

#include <stdio.h>
#include <copyfile.h>
#include <string.h>
#include "customDefs.h"
#include "args.h"
#include "appledouble.h"

int main(int argc, char *argv[]) {
	ExecInfo Info = {
		//Version ID
		2,
		//Version Name
		"1.0.0"
	};
	Info.Config.CFFlags = COPYFILE_XATTR | COPYFILE_PACK | COPYFILE_EXCL | COPYFILE_NOFOLLOW;
	Info.Config.Opt_R = 0;
	
	if (argc < 2) {
		DisplayHelp(Info);
		return 0;
	}
	int ArgsResponse = ParseArgs(&Info, argc, (const char**)argv);
	switch(ArgsResponse) {
		//Successful
		case 0:
			break;
		//Failed
		//Errors have already been printed in the ParseArgs function
		case 1:
			return 1;
		//Help page requested
		case 2:
			DisplayHelp(Info);
			return 0;
		default:
			fprintf(stderr, "ParseArgs function outputted an unknown value: \"%d\"!\n", ArgsResponse);
			return 1;
	}
	
	return MakeAppleDouble(&Info);
}