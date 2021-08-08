# Contribution stuff

## C++ Code style conventions
### Variable Name Cases
#### File names
Write file names in all lowercase, and in one word.
If you have two words (ie: string utils), do a C style contraction into one word. (ie: strutils.cpp)
#### Namespace and Class names
Pascal case, the first letter of every word is capital. (ie: ThisIsPascalCase)
#### Constants and anything inline
Screaming case, all caps seperated by underscores. (ie: SCREAMING_CASE)
#### Functions, Methods, Variables, and instances of a class
Camel case, first letter lowercase, no spaces, first letter of subsequent words capital. (ie: thisIsCamelCase)

### Curly Brace Location
#### Namespaces, Classes, and Methods
The curly brace is always on the next line.
```c++
namespace ThisNamespace
{
    class ThisClass
    {
    public:
        int aFunction(int x) 
		{
	    	return -x;
		}
    }
}
```

#### If and Else
If and else will always be on the same line.
```c++
if (x == 1) {
	printf("X is equal to 1");
} else if (x == 2) {
	printf("X is equal to 2");
} else {
	printf("X is not 1 nor 2";)
}
```

#### For and While
For and while loops will have the curly brace on the same line unless there are more than 10 lines of significant code inside of them.
```c++
for (int i=0; i<s.length; i++) {
	printf("%c\n", s[i]);
}

while (true)
{
	theCurly();
	braceIn();
	thisWile();
	loopIsOnA();
	seperateLine();
	because();
	itContains();
	moreThanTen();
	linesOf();
	important();
	codeAsItIs();
	anInfinte();
	loop();
}
