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
