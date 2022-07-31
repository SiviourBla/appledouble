# appledouble

Generates appledouble files on any filesystem using copyfile.

This can be useful when you are sharing files stored on a filesystem that supports extended attributes with another mac through a protocol that doesn't (for example, sharing a folder stored on an [APFS Volume](https://en.wikipedia.org/wiki/Apple_File_System) to another mac through [NFS](https://en.wikipedia.org/wiki/Network_File_System)).

### ![!](https://via.placeholder.com/15/ff1111/ff1111.png) **This program uses Apple's copyfile library and thus should only function on macOS.**

## More information

 - The `copyfile` manual can be accessed through `man 3 copyfile` or [here](https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/copyfile.3.html).
 - The appledouble format's [wikipedia page](https://en.wikipedia.org/wiki/AppleDouble_format)

## Usage

	appledouble [-frRh] file

## Options

 - `-f`
	- Overwrite any existing appledouble files
 - `-r`
	 - Follow symlinks
 - `-R`
	 - Attempt to convert existing appledouble files
 - `-a`
	 - Copy POSIX and ACL information in addition to extended attributes
 - `-h`
	 - Print the help page and exit

