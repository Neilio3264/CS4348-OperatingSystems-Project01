# Directory Overview

1. include
   1. Houses all the include files for the programs. Split into folders according to their respective programs
2. lib
   1. Houses all the object files that are created through [make]()
3. bin
   1. Houses all the executable files that are created through [make]()
4. Log
   1. Houses the log file created through the [Log Program]()
5. src
   1. Houses all the source .cpp files for the programs. Once again split into folders according to the programs. The Driver Program main resides in the root of /src

# File List

1. **Driver Program**
   1. `main.cpp`: the only file for the driver program. Responsible for handling the forks for the processes and communicating between the programs.
2. **Encryption Program**
   1. `krypto.cpp`: the main file for the encryption program. This is where a single instance of the program is created and run.
   2. `encryption.cpp`: this file handles the logic for the encryption class. The logic in this case is handling the 6 possible actions that can be called by the encryption program. This is also where the input is mapped to the correct action state and the remaining input is set as the argument.
   3. `encryption.h`: this file defines the class creation for the encryption class. This file also defines the *runCommand* method. This method acts as a selector to choose the correct action step and method call.
   4. `encryption_states.h`: this file simply defines enums for the action states. They are used throughout the program to ensure the program is in the correct state when calling various methods
3. **Log Program**
   1. `zotikos.cpp`: the main file for the log program. The pattern followed for the single instance logger is similar to ostream with cout.
   2. `logger.cpp`: the goal of this file is to define the logger class such that it is thread safe. The main logic of the log program resides in *print*. In this method, you write to the file if the queue has data to be read. Otherwise, you set the thread to periodically check the queue and allow the thread to sleep for a set duration.
   3. `log_stream.cpp`: this file simply houses the creation of the output string that will be sent to the file. It combines the time, state, and input to the stream.
   4. `logger.h`: this file defines the logger class as a singleton and also includes the *log_stream* link to the actual logger object.
   5. `log_stream.h`: this file defines the stream class. It also inherits ostream so that the logger can be utilized like cout with overloaded operators.
   6. `timeutil.h`: a simple util file that grabs and formats the time as per the logger requirements.
   7. `log_states.h`: a file that defines enums with the possible states that the logger must handle.

# Compile and Run

NOTE: All files are included for run in the zip. To skip compile, go to /bin and run ./driver

To run this code, I have created 3 makefiles, 1 for each program.
The makefiles are housed as follows:

1. Driver Program: /src/Makefile
2. Encryption Program: /src/Log/Makefile
3. Log Program: /src/Encryption/Makefile

In order to run any of these files, `cd` to the indicated directory (or include the path in the command) and first run `make clean`. This will ensure any existing object files are removed for a fresh run. Next run `make`.

If the make is successful, an output file should be created in /bin. To run the exe, cd to the /bin folder and run `./[exe]` (**assuming UNIX system**).

The 3 outputs files are as follows (only the `driver` is intended to be run):

1. Driver Program: /bin/driver
2. Encryption Program: /bin/krypto
3. Log Program: /bin/zotikos
