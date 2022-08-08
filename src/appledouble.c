/*------*\
| Encoding: UTF-8
| License: MIT
| Original Author: Blake Siviour
| Year: 2022
| Project: appledouble
| Project Summary: Generates appledouble files on any filesystem using copyfile.
| File Summary: Generates the appledouble file.
\*------*/

#include <stdio.h>
#include <copyfile.h>
#include <string.h>
#include <stdlib.h>
#include "customDefs.h"

int MakeAppleDouble(ExecInfo *Info) {
	//Make input path absolute before trying anything else
	char OldFPath[strlen(Info->Config.FPath) + 2];
	strcpy(OldFPath, Info->Config.FPath);
	//realpath(OldFPath, Info->Config.FPath);
	
	//Loop through the input path and add "._" to the beginning of the file/folder's name for the output
	char OutputPath[strlen(Info->Config.FPath) + 4];
	int FixedName = 0;
	for (int i = strlen(Info->Config.FPath); i >= 0; i--) {
		OutputPath[i + (2 * !FixedName)] = Info->Config.FPath[i];
		if (Info->Config.FPath[i] == '/' && !FixedName) {
			OutputPath[i + 2] = '_';
			OutputPath[i + 1] = '.';
			//If the file already was an appledouble and the "R" option wasn't provided throw an error and exit
			if (!Info->Config.Opt_R && OutputPath[i + 3] == '.' && OutputPath[i + 4] == '_') {
				fprintf(stderr, "Error: input file (\"%s\") is already an appledouble\nUse -R to convert it anyway\n", Info->Config.FPath);
				return 1;
			}
			OutputPath[i] = '/';
			FixedName = 1;
		}
	}
	//If the inputted file path does not have any folders
	if (!FixedName) {
		OutputPath[1] = '_';
		OutputPath[0] = '.';
	}
	
	//If copyfile outputs a value other than 0, it has failed
	int ResultCode = copyfile(Info->Config.FPath, OutputPath, NULL, Info->Config.CFFlags);
	if (ResultCode) {
		fprintf(stderr, "Error: copyfile failed with error code %d!\nInput file: \"%s\"\nOutput file: \"%s\"\n", ResultCode, Info->Config.FPath, OutputPath);
		fprintf(stderr, "Please refer to copyfile's error codes through 'man 3 copyfile' for more information\n");
	}
	return ResultCode;
}