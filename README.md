# appledouble

Generates appledouble files on any filesystem using copyfile.

This can be useful when you are working with programs that don't support extended attrubutes or filesystems/network shares that stop finder from automatically creating appledouble files while still allowing appledouble files to be manually uploaded.

### ![!](https://via.placeholder.com/15/ff1111/ff1111.png) **This program uses Apple's copyfile library and thus should only function on macOS.**

## More information

 - The `copyfile` manual can be accessed through `man 3 copyfile` or [here](https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/copyfile.3.html).
 - The appledouble format's [wikipedia page](https://en.wikipedia.org/wiki/AppleDouble_format)

## Usage

	appledouble [-frRdavhA] file

## Options

 - `-f`
	- Overwrite any existing appledouble files
 - `-r`
	 - Follow symlinks
 - `-R`
	 - Attempt to convert existing appledouble files
 - `-d`
 	 - Enables debug and dry run mode
 - `-a`
	 - Copy POSIX and ACL information in addition to extended attributes
 - `-v`
 	 - Print the version number and exit
 - `-h`
	 - Print the help page and exit
 - `-A`
 	 - Print the about page
