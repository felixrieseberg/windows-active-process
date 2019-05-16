#include <node.h>
#include <nan.h>

#define _WIN32_WINNT 0x0601

#ifdef _WIN32
#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#include <psapi.h>
#else
#include <stdbool.h>
#endif

#ifdef _WIN32
bool _GetActiveProcessName(TCHAR *buffer, DWORD cchLen)
{
  HWND fg = GetForegroundWindow();
  if (fg)
  {
    DWORD pid;

    GetWindowThreadProcessId(fg, &pid);
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);

    if (hProcess)
    {
      BOOL ret = QueryFullProcessImageName(hProcess, 0, buffer, &cchLen);

	    CloseHandle(hProcess);
      return (ret != FALSE);
    }
  }
  return false;
}
#endif // _WIN32

NAN_METHOD(GetActiveProcessName) {
  Nan::HandleScope scope;

  #ifdef _WIN32
  TCHAR buffer[1024];
  if (_GetActiveProcessName(buffer, 1024))
  {
    info.GetReturnValue().Set(Nan::New(buffer).ToLocalChecked());
  }
  else
  {
    info.GetReturnValue().Set(Nan::EmptyString());
  }
  #else
  info.GetReturnValue().Set(Nan::EmptyString());
  #endif
}

NAN_MODULE_INIT(Init) {
  Nan::SetMethod(target, "getActiveProcessName", GetActiveProcessName);
}

#if NODE_MAJOR_VERSION >= 10
NAN_MODULE_WORKER_ENABLED(processname, Init)
#else
NODE_MODULE(processname, Init)
#endif
