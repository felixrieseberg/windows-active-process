#include <node.h>
#include <v8.h>

#define _WIN32_WINNT 0x0601

#ifdef _WIN32
#include <windows.h>
#include <malloc.h>
#include <stdio.h>
#include <psapi.h>
#else
#include <stdbool.h>
#endif

using namespace v8;

#ifdef _WIN32
bool GetActiveProcessName(TCHAR *buffer, DWORD cchLen)
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

void Method(const v8::FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  #ifdef _WIN32
  TCHAR buffer[1024];
  if (GetActiveProcessName(buffer, 1024))
  {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, buffer));
  }
  else
  {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, ""));
  }
  #else
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, ""));
  #endif
}

void Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  exports->Set(String::NewFromUtf8(isolate, "getActiveProcessName"),
      FunctionTemplate::New(isolate, Method)->GetFunction());
}

NODE_MODULE(quiethours, Init)