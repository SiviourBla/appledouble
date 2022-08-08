/*------*\
| Encoding: UTF-8
| License: MIT
| Original Author: Blake Siviour
| Year: 2022
| Project: appledouble
| Project Summary: Generates appledouble files on any filesystem using copyfile.
| File Summary: Displays different information about the program.
\*------*/

#include <stdio.h>
#include <copyfile.h>
#include "customDefs.h"

void DisplayInfo(ExecInfo *Info, const int DisplayMode) {
	char VersionText[] = "appledouble v%s\n";
	char HelpText[] =
		"--------------------\n"
		"Generate appledouble files on any filesystem using copyfile\n"
		"\n"
		"More info:\n"
		"        appledouble: https://en.wikipedia.org/wiki/AppleDouble_format\n"
		"        copyfile: man 3 copyfile\n"
		"\n"
		"Usage:\n"
		"        appledouble [-frRavhA] file\n" 
		"\n"
		"Options:\n" 
		"        -f    Overwrite any existing appledouble files\n"//COPYFILE_UNLINK + !COPYFILE_EXCL
		"        -r    Follow symlinks\n"//!COPYFILE_NOFOLLOW
		"        -R    Attempt to convert existing appledouble files\n"//!COPYFILE_NOFOLLOW
		"        -a    Copy POSIX and ACL information in addition to extended attributes\n"//COPYFILE_SECURITY
		"        -v    Display the version number\n"
		"        -h    Display this help page\n"
		"        -A    Display the about page\n"
		"\n";
	char AboutText[] =
		"--------------------\n"
		"Author: Blake Siviour\n"
		"\n"
		"License:\n"
		"        MIT License\n"
		"        \n"
		"        Copyright (c) 2022 Blake Siviour\n"
		"        \n"
		"        Permission is hereby granted, free of charge, to any person obtaining a copy\n"
		"        of this software and associated documentation files (the \"Software\"), to deal\n"
		"        in the Software without restriction, including without limitation the rights\n"
		"        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
		"        copies of the Software, and to permit persons to whom the Software is\n"
		"        furnished to do so, subject to the following conditions:\n"
		"        \n"
		"        The above copyright notice and this permission notice shall be included in all\n"
		"        copies or substantial portions of the Software.\n"
		"        \n"
		"        THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
		"        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
		"        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
		"        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
		"        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
		"        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
		"        SOFTWARE.\n"
		"\n"
		"Source and Bugs:\n"
		"        The source code is available at https://github.com/SiviourBla/appledouble/\n"
		"        Bugs are listed and can be reported at https://github.com/SiviourBla/appledouble/issues\n"
		"\n";
	
	switch(DisplayMode) {
		//Version
		case 0:
			printf(VersionText, Info->VersionString);
			break;
		//Help
		case 1:
			printf(VersionText, Info->VersionString);
			printf("%s", HelpText);
			break;
		//About
		case 2:
			printf(VersionText, Info->VersionString);
			printf("%s", AboutText);
			break;
		default:
			fprintf(stderr, "Error: DisplayInfo function was called with an unknown id %d!", DisplayMode);
	}
}