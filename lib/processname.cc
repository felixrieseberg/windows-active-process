#include <node_api.h>

#define NAPI_CALL(env, call)                                      \
  do {                                                            \
    napi_status status = (call);                                  \
    if (status != napi_ok) {                                      \
      const napi_extended_error_info* error_info = NULL;          \
      napi_get_last_error_info((env), &error_info);               \
      bool is_pending;                                            \
      napi_is_exception_pending((env), &is_pending);              \
      if (!is_pending) {                                          \
        const char* message = (error_info->error_message == NULL) \
            ? "empty error message"                               \
            : error_info->error_message;                          \
        napi_throw_error((env), NULL, message);                   \
        return NULL;                                              \
      }                                                           \
    }                                                             \
  } while(0)


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
bool GetActiveProcessName(WCHAR *buffer, DWORD *cchLen)
{
  HWND fg = GetForegroundWindow();
  if (fg)
  {
    DWORD pid;

    GetWindowThreadProcessId(fg, &pid);
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);

    if (hProcess)
    {
      BOOL ret = QueryFullProcessImageNameW(hProcess, 0, buffer, cchLen);
      CloseHandle(hProcess);
      return (ret != FALSE);
    }
  }
  return false;
}
#endif // _WIN32

static napi_value Method(napi_env env, napi_callback_info info) {
#ifdef _WIN32
  WCHAR buffer[1024];
  DWORD len = 1024;
  if (GetActiveProcessName(buffer, &len))
  {
    napi_value str = NULL;
    NAPI_CALL(env, napi_create_string_utf16(env, (char16_t*)buffer, len, &str));
    return str;
  }
#endif
  napi_value ret = NULL;
  NAPI_CALL(env, napi_get_undefined(env, &ret));
  return ret;
}

NAPI_MODULE_INIT() {
  napi_value result = NULL;
  NAPI_CALL(env, napi_create_object(env, &result));
  napi_value fn = NULL;
  NAPI_CALL(env, napi_create_function(env, "getActiveProcessName", 0, Method, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, result, "getActiveProcessName", fn));
  return result;
}
