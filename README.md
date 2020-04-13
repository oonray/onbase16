#onlib16

install:
```
make
sudo make install
```

usage:
```c
#include <onlib16/16.h>

//use stuff
```
compile:
```
gcc <your.c> -l onlib16  -o <yourbin>
```

You can grab a base16 binray from the releases.
example:
```
base16 -ex ABCD
```

usage:
```
If no output file is specified it will printthe data to stdout
	-h	Help
	-e	Encode
	-d	Decode
	-x	Data
	-f	Input File
	-o	Output File
	-a	Alphabet. If none is provided default will be used.
```


