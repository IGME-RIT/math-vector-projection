#Vector Projection

Projection is a useful operation with many applications.

Given two vectors __x__ and __y__, the projection of __x__ onto __y__, commonly denoted proj<sub>__y__</sub>(__x__) or __x__<sub>||__y__</sub>, is a scalar multiple of __y__ based on the length of __x__ in the direction of __y__. It can be calculated as __x__<sub>||__y__</sub> = ((__x__ &middot; __y__) / (__y__ &middot; __y__)) __y__

The Rejection operation is also introduced. Commonly denoted __x__<sub>&perp;__y__</sub>, it is the vector orthogonal to __y__ in the same half-space as __x__ with magnitude equal to the component of __x__ in that direction. It is more easily calculated as __x__<sub>&perp;__y__</sub> = __x__ - __x__<sub>||__y__</sub>.

#Setup

You will need to have CMake installed on your computer, and properly added to your path.  In order to setup, run the following in a shell, then open the project in your preferred editor. Windows has been configured for use with Visual Studio.

Windows:
```
cd path/to/folder
setup.cmd
```
Linux:
```
cd path/to/folder
./setup
```
