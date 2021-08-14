# VISUAL STUDIO VERSION

> &copy; 2021 by dbj@dbj.org -- https://dbj.org/license_dbj

# 3D [Convex hull](https://en.wikipedia.org/wiki/Convex_hull_algorithms)

- 3D [Convex hull](https://en.wikipedia.org/wiki/Convex_hull) implementation using C and OpenGL library.
- Random points generated using user’s selection, followed by algorithm joining them. 

## How to build

- Use the visual studio solution in the `srcfiles` folder.
- Not necessary to build but please make sure to read [`srcfiles\glut\readme.md`](srcfiles/glut/readme.md)

## How to run

- Debug build `srcfiles/Debug/MARIATANOVIC.exe`
- Release build `srcfiles/Release/MARIATANOVIC.exe`

## Usage

- On right click, menu with several options for number of points in 3d space. 
  - To quickly avoid repeated memory leaks currently in there we simply remove the context menu after its first use. Roadmap is of course, to free list of Point and list of PLanes on new point set size selection.
- Choosing one of them starts the application. 
- User can rotate figure using touchpad/mouse in all directions.
- Application exits pressing ESC on keyboard.
