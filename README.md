# RunSuspended

Ever had a program you'd like to debug, from its entrypoint, and found that the only way to do that
was to launch the process with Visual Studio?

Doesn't work if you have a complicated run script, or a hairy environment setup, does it?

This tool is what you want.

For example, lets say you wanted to debug 'notepad.exe' from the entrypoint:

```
G:\run_suspended\Release>RunSuspended.exe notepad
Starting process suspended: notepad
Started process id 5672, thread id 32420
Press any key to resume suspended process...
```

Then you attach Visual Studio to pid 5672, it breakpoints for you at the start of the program, you
add whatever other breakpoints you'd like to stop at, then you can hit a key in the console where 
you ran 'RunSuspended' and let the program continue executing to your breakpoints.

* RunSuspended binary is targeted for Win32, but it can run Win64 subprocesses. 
* RunSuspended is linked statically, so no extra runtime is required for use.
* RunSuspended linked with the WinXP toolchain, so it should work on Windows XP or newer.
