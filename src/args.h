/*------*\
| Encoding: UTF-8
| License: MIT
| Original Author: Blake Siviour
| Year: 2022
| Project: appledouble
| Project Summary: Generates appledouble files on any filesystem using copyfile.
| File Summary: Parses the user's arguments.
\*------*/

#ifndef ARGS_H_
#define ARGS_H_

int ParseArgs(ExecInfo *Info, const int argc, const char *argv[]);

#endif