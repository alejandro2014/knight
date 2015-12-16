# Height map editor

This project is a fork of the project "height map editor", located in http://hme.sourceforge.net/

The roadmap of the project is as follows:

* Refactoring of all the code
* Creation of a console able to perform the same operations that are done manually in the bitmap
* Creation of a 3d view that will show the result of the operations in real time
* Enhancement of the menus and widgets, giving the application a more professional look

In order to create the 3 three views (2d, 3d, and console) a deep refactoring is needed. The goal is to separate
the points of the map from their representation, so it's relative easy to include a new view

Updates
-------
* 15/12/2015 - The refactoring phase is taking place and it's quite advanced by now. The idea is to create an API for the editor, and from this API it'll be possible to connect a 2d editor (what we have so far), a 3d editor and a console. The idea is to make all of them inter-changeable. The focus is now in extracting all the functionality to the API. The rotation operations (rotate / flip), the inversion of height, and the smooth operations are now part of the API. The menu.c is becoming thiner and thiner, and will be eventually a very thin layer for the API calls
