# Knight 0.3.3

Knight is an editor of heightmaps. Still it doesn't do much, but little by little is taking shape. It will be an editor with different inputs:
A 2d view, a 3d view and a console. This project is a fork of the project "height map editor", located in http://hme.sourceforge.net/

Updates
-------
* 0.3.3 - Refactored all the structure of the programs in order to compile separate projects: api, 2d, console and main
* 0.3.2 - Changed the name of the program, from "Height Map Editor" to "Knight". Changed the versioning. The versions of the former hme where 1.x,
whereas here it has been downgraded to 0.x. This is in order to reflect that still is work in progress and we don't have a usable version yet. The shell 
is interactive now. Validation of parameters. Able to get commands in text form, this opens the door to scripting. Migrated functionality to api calls.
* 15/12/2015 - The refactoring phase is taking place and it's quite advanced by now. The idea is to create an API for the editor, and from this API
it'll be possible to connect a 2d editor (what we have so far), a 3d editor and a console. The idea is to make all of them inter-changeable. The
focus is now in extracting all the functionality to the API. The rotation operations (rotate / flip), the inversion of height, and the smooth
operations are now part of the API. The menu.c is becoming thiner and thiner, and will be eventually a very thin layer for the API calls

Roadmap
-------
* 0.4 - Fully operative shell. All the functionality of the program is migrated to api calls
* 0.5 - Restored 2d functionality of the old program. Widget engine completed. Console and 2d views are equivalent
* 0.7 - 3d view with openGl, not very interactive
* 0.8 - Interactive 3d view
* 0.9 - Bug-fixing, documentation, design
* 1.0 - Finished! (so far)

Credits
-------
* Alejandro Ruperez. Refactoring, API design and continuity of the project from height map editor v1.3.1
* Radu Privantu. Original program Height Map Editor
* Stefan Hellkvist. Origina generation of terrains (sdlplasma)
