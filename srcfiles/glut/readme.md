
# GLUT and WIN10

This folder contains GLUT for WIN32

GLUT is OK but (very) old. It works on WIN10 same as ever before and is quite OK. 

But. Please do not install it "globally" on your machine. You might use it in different projects on that same machine but ever so slightly tweaked not by you but whoever you are using the code from. Thus you might use unknowingly slightly different glut version per project etc.

Ditto. To save you a lot of trouble and instead of thinking GLUT is "trouble" please do use Visual Studio project features to include and link GLUT locally to the project.

Always start from here: https://user.xmission.com/~nate/glut.html

Remember that is code from 2001 and x64 was not that prevailing. Thus; **that is 32 bit stuff only** in [glut-3.7.6-bin.zip](https://user.xmission.com/~nate/glut/glut-3.7.6-bin.zip) (117 KB)

It is certainly possible to do your own Visual Studio x64 build using [glut-3.7.6-src.zip](https://user.xmission.com/~nate/glut/glut-3.7.6-src.zip) (4.76 MB). 

## By default GLUT is x86 only

The easiest way for your Visual Studio builds to finish successfully is to copy from (the `glut` folder in here) `glut32.lib` and `glut32.dll` to the root folder of  the solution. Just as we have done in here. 

x64 targets are removed from this solution.

## NOTES

- glut is primarily WIN32 lib, thus many if not all CRT headers you will need to include "by hand"
  - like for example `stdlib.h`
- I follow common header policy (`common.h`) thus header files shenanigans are all solved in one place
  - I especially like not to include headers which are not required
  - Warning level is /W4
    - Be sure to remove all warnings
