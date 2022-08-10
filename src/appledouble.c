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
#include <libgen.h>
#include "customDefs.h"

int MakeAppleDouble(ExecInfo *Info) {
	//Make input path absolute before trying anything else
	char OldFPath[strlen(Info->Config.FPath) + 2];
	strcpy(OldFPath, Info->Config.FPath);
	
	//realpath does not have any options to not follow symlinks, so we must run it on the parent folder.
	if (!Info->Config.Opt_rr) {
		//Get basename and dirname
		char TempFDirPath[strlen(Info->Config.FPath) + 3];
		char TempFBasePath[strlen(Info->Config.FPath) + 3];
		dirname_r(Info->Config.FPath, TempFDirPath);
		basename_r(Info->Config.FPath, TempFBasePath);

		//Resolve '.' paths as they aren't by basename_r or dirname_r for some reason
		while (!strcmp(TempFBasePath, ".") && strcmp(TempFDirPath, ".")) {
			basename_r(TempFDirPath, TempFBasePath);
			dirname_r(TempFDirPath, TempFDirPath);
		}
		
		//If it ends with ".." or the entire path is "." then we don't need to worry about symlinks
		if (!strcmp(TempFBasePath, "..") || (!strcmp(TempFBasePath, ".") && !strcmp(TempFDirPath, "."))) {
			realpath(OldFPath, Info->Config.FPath);
		//Otherwise get the absolute path of the parent folder and add the target's name to the end
		} else {
			realpath(TempFDirPath, Info->Config.FPath);
			strcat(Info->Config.FPath, "/");
			strcat(Info->Config.FPath, TempFBasePath);
		}
	} else {
		realpath(OldFPath, Info->Config.FPath);
	}
	
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
			//Don't run if the input file path ends with '..' or '.' (this shouldn't ever happen)
			} else if (OutputPath[i + 3] == '.' && (OutputPath[i + 4] == '.' || OutputPath[i + 4] == '\0')) {
				fprintf(stderr, "Error: input file (full: \"%s\", relative: \"%s\") is \"..\" or \".\"\nPlease change your input path or use -r.", Info->Config.FPath, OldFPath);
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