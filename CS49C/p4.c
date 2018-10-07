#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <string.h>
#pragma comment(lib, "User32.lib")

void DisplayErrorBox(LPTSTR lpszFunction);
int totalFiles;
LONGLONG totalFileSize;

void printcomma(int n)  //method to print comma
{
	if (n < 1000)
	{
		printf("%*d", 10, n);
		return;
	}
	printcomma(n / 1000);
	printf(",%03d", n % 1000);
}

int main(int argc, TCHAR *argv[])
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	char szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0, dwRet;
	FILETIME ftWrite;
	SYSTEMTIME stUTC, stLocal;

	// If the directory is not specified as a command-line argument,
	// print usage.

	if (argc != 2)
	{
		printf("\nUsage: %s <directory name>\n", argv[0]);
		return (-1);
	}

	// Check that the input path plus 3 is not longer than MAX_PATH.
	// Three characters are for the "\*" plus NULL appended below.

	if (strlen(argv[1]) > (MAX_PATH - 3))
	{
		printf("\nDirectory path is too long.\n");
		return (-1);
	}

	printf("\nDirectory of %s\n\n", argv[1]);

	// Prepare string for use with FindFile functions.  First, copy the
	// string to a buffer, then append '\*' to the directory name.

	strcpy(szDir, argv[1]);
	strcat(szDir, "\\*");

	// Find the first file in the directory.

	hFind = FindFirstFile(szDir, &ffd);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		DisplayErrorBox(TEXT("FindFirstFile"));
		return dwError;
	}

	// List all the files in the directory with some info about them.

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			ftWrite = ffd.ftLastWriteTime;
			FileTimeToSystemTime(&ftWrite, &stUTC);
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
			WORD hour = stLocal.wHour;
			char a[] = { 'A', 'M', '\0' };
			if (hour > 12)
			{
				hour = hour % 12;
				a[0] = 'P';
			}
			printf("%02d/%02d/%d  %02d:%02d %s   <DIR>\t\t%s\n",
				stLocal.wMonth,
				stLocal.wDay,
				stLocal.wYear,
				hour,
				stLocal.wMinute,
				a,
				ffd.cFileName);
		}
		else
		{
			if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))  /* don't print hidden files */
			{
				totalFiles = totalFiles + 1;
				filesize.LowPart = ffd.nFileSizeLow;
				filesize.HighPart = ffd.nFileSizeHigh;
				ftWrite = ffd.ftLastWriteTime;
				FileTimeToSystemTime(&ftWrite, &stUTC);
				SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
				WORD hour = stLocal.wHour;
				char a[] = { 'A', 'M', '\0' };
				if (hour > 12)
				{
					hour = hour % 12;
					a[0] = 'P';
				}
				printf("%02d/%02d/%d  %02d:%02d %s  \t",
					stLocal.wMonth,
					stLocal.wDay,
					stLocal.wYear,
					hour,
					stLocal.wMinute,
					a);
				if (filesize.QuadPart < 1000)
				{
					printf("%*d", 14, filesize.QuadPart);
				}
				else
				{
					printcomma(filesize.QuadPart);
				}
				printf(" %s\n", ffd.cFileName);
				totalFileSize += filesize.QuadPart;
			}
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	printf("\t       %d File(s) ", totalFiles);
	printcomma(totalFileSize);
	printf(" bytes");
	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		DisplayErrorBox(TEXT("FindFirstFile"));
	}

	FindClose(hFind);
	return dwError;
}


void DisplayErrorBox(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and clean up

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40)*sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}