# logger
A VERY basic c++ logger

Features:
- Similar usage to std::cout

- Three different log outputs

	logger::log, logger::debug and logger::error,  
	these can individually be disabled and directed to a file.

- Can write simultenously to the standard output and to logfiles

Planned features(in order of priority):
- Need asynchronous background thread for file input operations

	Right now, the file logging procedure is synchronous, meaning the program will wait for logger's file operations to finish, before continuing.  
	Currently setFile("") can be used to disable file logging
	
- Ability to read logging configuration settings from file
