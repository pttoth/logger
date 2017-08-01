# logger
A VERY lightweight c++ logger writing simultenously to the standard output and to a logfile

planned features(in order of priority):
	
	- Need asynchronous background thread for file input operations
		Right now, the file logging procedure is synchronous, meaning
		the program will wait for file operations to finish, before continuing.
		(right now, setFile("") can be used to disable file logging)
	
	- Ability to read logging configuration settings from file
