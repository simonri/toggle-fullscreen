#include <napi.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>


/*BOOL CALLBACK speichereFenster(HWND hwnd, LPARAM lParam)
{
    const DWORD TITLE_SIZE = 1024;
    WCHAR windowTitle[TITLE_SIZE];

    GetWindowTextW(hwnd, windowTitle, TITLE_SIZE);

    int length = ::GetWindowTextLength(hwnd);
    std::wstring title(&windowTitle[0]);
    if (!IsWindowVisible(hwnd) || length == 0 || title == L"Program Manager")
    {
        return TRUE;
    }

    std::vector<std::wstring>& titles = *reinterpret_cast<std::vector<std::wstring>*>(lParam);
    titles.push_back(title);

    return TRUE;
}

Napi::Value GetWindows(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  std::vector<std::wstring> titles;
  EnumWindows(speichereFenster, reinterpret_cast<LPARAM>(&titles));
  
  Napi::Array titlesArray = Napi::Array::New(env, titles.size());

  uint32_t i = 0;

  for (const auto& title : titles) {
    std::cout << typeid(ci).name() << '\n';
    std::wcout << i << " : " << title << std::endl;
    titlesArray[i++] = Napi::String::New(info.Env(), string_cast<std::string>(title));
    i++;
  }

  return titlesArray;
}*/

Napi::Value ToggleFullscreen(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  std::string arg0 = info[0].As<Napi::String>();

  HWND hwnd = FindWindow(nullptr, arg0.c_str());

  if (GetWindowLongPtr(hwnd, GWL_STYLE) & WS_POPUP)
  {
    SetWindowLongPtr(hwnd, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW);
    SetWindowPos(hwnd, NULL, 0, 0, 600, 400, SWP_FRAMECHANGED);
  }
  else
  {
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    SetWindowLongPtr(hwnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
  }

  return Napi::Number::New(env, 0);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "toggleFullscreen"), Napi::Function::New(env, ToggleFullscreen));
  // exports.Set(Napi::String::New(env, "getWindows"), Napi::Function::New(env, GetWindows));
  return exports;
}

NODE_API_MODULE(addon, Init)