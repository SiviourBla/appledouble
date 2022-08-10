/*------*\
| Encoding: UTF-8
| License: MIT
| Original Author: Blake Siviour
| Year: 2022
| Project: appledouble
| Project Summary: Generates appledouble files on any filesystem using copyfile.
| File Summary: Defines ExecInfo and ExecConfig structs, which stores version info and all the data MakeAppleDouble() requires.
\*------*/

#ifndef CUSTOMDEFS_H_
#define CUSTOMDEFS_H_

typedef struct ExecConfig {
	copyfile_flags_t CFFlags;
	int Opt_R;
	int Opt_rr;
	int Opt_D;
	char FPath[3334];
} ExecConfig;

typedef struct ExecInfo {
	char VersionString[50];
	ExecConfig Config;
} ExecInfo;

#endif