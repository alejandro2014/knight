# Height map editor

This project is a fork of the project "height map editor", located in http://hme.sourceforge.net/

The roadmap of the project is as follows:

* Refactoring of all the code
* Creation of a console able to perform the same operations that are done manually in the bitmap
* Creation of a 3d view that will show the result of the operations in real time
* Enhancement of the menus and widgets, giving the application a more professional look

In order to create the 3 three views (2d, 3d, and console) a deep refactoring is needed. The goal is to separate
the points of the map from their representation, so it's relative easy to include a new view
