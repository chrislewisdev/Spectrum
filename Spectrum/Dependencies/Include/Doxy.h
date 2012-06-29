/*******************************************************************
*CEngine
*Doxy.h by Chris Lewis
*This file exists solely for containing general documentation blocks that do not belong in a specific file.
*******************************************************************/

/// \mainpage CEngine Documentation
///
/// \section Intro Introduction
/// CEngine is a C++ 2D Game Engine being written by Chris Lewis.
///
///It's in early stages (read: not yet properly usable) and isn't specifically designed for anyone in particular apart from myself. I've been making small/basic/unfinished games in C++ for a couple years now and this engine is basically being designed to meet my own needs, so that I'm not stuck rewriting an engine for every game I make and also because I think it's fun.
///
///The current goals of the engine are outlined in EngineFeatures.txt which is basically a dump for any plans I have so far for the project. It summarises about everything I think is important for the project so far.
///
///The doxyfile in the top of the folder heirarchy is used for generating doxygen documentation. If you want to generate your own local documentation for CEngine just run doxygen in this directory and it should all work out. Including my own generated files would probably just clutter up the repository and I figured it wasn't necessary for now. Full, prettified documentation would be included in a final release, naturally (if such a thing ever sees the light of day).
///
///The project is being built with Visual Studio 2010 as can probably be inferred from the VS project files in the repo. It's all been setup to (hopefully) compile without any need for configuration on anyone else's end, with third-party libraries/headers provided in the Dependencies folder (which the project should automatically search for files). It hasn't been set up for a  Release build yet so it won't compile into a .lib that's too friendly with other projects, but that will be set up when necessary later on.
///
///A UMLet UML diagram is also provided. It's not 100% consistent as some smaller details get changed over time and will be expanded over time to cover the full class make-up of the project.

/// \namespace CEngine
/// \brief General namespace for all CEngine classes/definitions/etc.