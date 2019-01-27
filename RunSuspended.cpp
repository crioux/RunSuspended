#include<Windows.h>
#include<stdio.h>
#include<conio.h>

LPWSTR chop_command_line(LPWSTR cmdlinew)
{
	// find the rest of the command line
	bool inquote = false;
	wchar_t c;
	while ((c = *cmdlinew) != 0)
	{
		if (c == L'"')
		{
			inquote = !inquote;
		}
		else if (!inquote && c == ' ')
		{
			// eat whitespace
			while (*cmdlinew == ' ')
			{
				cmdlinew++;
			}
			break;
		}
		cmdlinew++;
	}
	return cmdlinew;
}

int wmain(int argc, wchar_t **argv)
{
	LPWSTR cmdlinew = GetCommandLineW();
	cmdlinew = chop_command_line(cmdlinew);
	
	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(pi));

	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(STARTUPINFO);

	if (*cmdlinew == 0)
	{
		wprintf(L"RunSuspended v1.0 - Copyright (c) 2019, Christien Rioux\n\nUsage: RunSuspended <command line of program to run>\n");
		exit(0);
	}

	wprintf(L"Starting process suspended: %s\n", cmdlinew);

	BOOL ok = CreateProcessW(NULL, cmdlinew, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
	if (!ok)
	{
		wchar_t err[256];
		memset(err, 0, 256);
		DWORD dwLastError = GetLastError();
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), err, 255, NULL);

		fwprintf(stderr, L"Failed: %s\n", err);

		return dwLastError;
	}

	wprintf(L"Started process id %d, thread id %d\n", pi.dwProcessId, pi.dwThreadId);

	wprintf(L"Press any key to resume suspended process...\n");
	_getch();

	ResumeThread(pi.hThread);

	WaitForSingleObject(pi.hProcess,INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	return 0;
}