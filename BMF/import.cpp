/**
* This file is part of Batman "Fix".
*
* Batman "Fix" is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* The Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Batman "Fix" is distributed in the hope that it will be useful,
* But WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Batman "Fix". If not, see <http://www.gnu.org/licenses/>.
**/

#include "import.h"
#include "log.h"

#include <comdef.h>

extern std::wstring host_app;

const std::wstring BMF_IMPORT_EARLY = L"Early";
const std::wstring BMF_IMPORT_LATE  = L"Late";
const std::wstring BMF_IMPORT_LAZY  = L"Lazy";
const std::wstring BMF_IMPORT_PROXY = L"Proxy";

const std::wstring BMF_IMPORT_ROLE_DXGI   = L"dxgi";
const std::wstring BMF_IMPORT_ROLE_D3D11  = L"d3d11";
const std::wstring BMF_IMPORT_ROLE_D3D9   = L"d3d9";
const std::wstring BMF_IMPORT_ROLE_OPENGL = L"opengl";

const std::wstring BMF_IMPORT_ARCH_X64   = L"x64";
const std::wstring BMF_IMPORT_ARCH_WIN32 = L"Win32";

import_t imports [BMF_MAX_IMPORTS];

void
BMF_LoadEarlyImports64 (void)
{
  int success = 0;

  for (int i = 0; i < BMF_MAX_IMPORTS; i++) {

    // Skip libraries that are already loaded
    if (imports [i].hLibrary != NULL)
      continue;

    bool         blacklisted = false;
    std::wstring blacklist   =
      imports [i].blacklist != nullptr ?
        imports [i].blacklist->get_value_str () :
        L"";

    if (blacklist.find (host_app) != std::wstring::npos)
      blacklisted = true;

    if (imports [i].filename != nullptr) {
      if (imports [i].when != nullptr) {
        if (imports [i].architecture != nullptr) {
          if (imports [i].architecture->get_value () == BMF_IMPORT_ARCH_X64 &&
              imports [i].when->get_value         () == BMF_IMPORT_EARLY) {

            dll_log.LogEx (true, L"  * Loading Early Custom Import %s... ",
              imports [i].filename->get_value_str ().c_str ());

            if (! blacklisted) {
              imports [i].hLibrary = LoadLibrary (
                imports [i].filename->get_value_str ().c_str ()
              );

              if (imports [i].hLibrary != NULL) {
                dll_log.LogEx (false, L"success!\n");
                ++success;
              } else  {
                _com_error err (HRESULT_FROM_WIN32 (GetLastError ()));

                imports [i].hLibrary = (HMODULE)-2;
                dll_log.LogEx (false, L"failed: 0x%04X (%s)!\n",
                               err.WCode (), err.ErrorMessage () );
              }
            } else {
              dll_log.LogEx (false, L"failed: Host App is Blacklisted!\n");
            }
          }
        }
      }
    }
  }

  if (success > 0)
    dll_log.LogEx (false, L"\n");
}

void
BMF_LoadLateImports64 (void)
{
  int success = 0;

  for (int i = 0; i < BMF_MAX_IMPORTS; i++) {

    // Skip libraries that are already loaded
    if (imports [i].hLibrary != NULL)
      continue;

    bool         blacklisted = false;
    std::wstring blacklist   =
      imports [i].blacklist != nullptr ?
        imports [i].blacklist->get_value_str () :
        L"";

    if (blacklist.find (host_app) != std::wstring::npos)
      blacklisted = true;

    if (imports [i].filename != nullptr) {
      if (imports [i].when != nullptr) {
        if (imports [i].architecture != nullptr) {
          if (imports [i].architecture->get_value () == BMF_IMPORT_ARCH_X64 &&
              imports [i].when->get_value         () == BMF_IMPORT_LATE) {

            dll_log.LogEx (true, L"  * Loading Late Custom Import %s... ",
              imports [i].filename->get_value_str ().c_str ());

            if (! blacklisted) {
              imports [i].hLibrary = LoadLibrary (
                imports [i].filename->get_value_str ().c_str ()
              );

              if (imports [i].hLibrary != NULL) {
                dll_log.LogEx (false, L"success!\n");
                ++success;
              } else  {
                _com_error err (HRESULT_FROM_WIN32 (GetLastError ()));

                imports [i].hLibrary = (HMODULE)-2;
                dll_log.LogEx (false, L"failed: 0x%04X (%s)!\n",
                               err.WCode (), err.ErrorMessage () );
              }
            } else {
              dll_log.LogEx (false, L"failed: Host App is Blacklisted!\n");
            }
          }
        }
      }
    }
  }

  if (success > 0)
    dll_log.LogEx (false, L"\n");
}

void
BMF_LoadLazyImports64 (void)
{
  int success = 0;

  for (int i = 0; i < BMF_MAX_IMPORTS; i++) {

    // Skip libraries that are already loaded
    if (imports [i].hLibrary != NULL)
      continue;

    bool         blacklisted = false;
    std::wstring blacklist   =
      imports [i].blacklist != nullptr ?
        imports [i].blacklist->get_value_str () :
        L"";

    if (blacklist.find (host_app) != std::wstring::npos)
      blacklisted = true;

    if (imports [i].filename != nullptr) {
      if (imports [i].when != nullptr) {
        if (imports [i].architecture != nullptr) {
          if (imports [i].architecture->get_value () == BMF_IMPORT_ARCH_X64 &&
              imports [i].when->get_value         () == BMF_IMPORT_LAZY) {

            dll_log.LogEx (true, L"  * Loading Lazy Custom Import %s... ",
                imports [i].filename->get_value_str ().c_str ());

            if (! blacklisted) {
              imports [i].hLibrary = LoadLibrary (
                imports [i].filename->get_value_str ().c_str ()
              );

              if (imports [i].hLibrary != NULL) {
                dll_log.LogEx (false, L"success!\n");
                ++success;
              } else  {
                _com_error err (HRESULT_FROM_WIN32 (GetLastError ()));

                imports [i].hLibrary = (HMODULE)-3;
                dll_log.LogEx (false, L"failed: 0x%04X (%s)!\n",
                               err.WCode (), err.ErrorMessage () );
              }
            } else {
              dll_log.LogEx (false, L"failed: Host App is Blacklisted!\n");
            }
          }
        }
      }
    }
  }

  if (success > 0)
    dll_log.LogEx (false, L"\n");
}

void
BMF_LoadEarlyImports32 (void)
{
  int success = 0;

  for (int i = 0; i < BMF_MAX_IMPORTS; i++) {

    // Skip libraries that are already loaded
    if (imports [i].hLibrary != NULL)
      continue;

    bool         blacklisted = false;
    std::wstring blacklist   =
      imports [i].blacklist != nullptr ?
        imports [i].blacklist->get_value_str () :
        L"";

    if (blacklist.find (host_app) != std::wstring::npos)
      blacklisted = true;

    if (imports [i].filename != nullptr) {
      if (imports [i].when != nullptr) {
        if (imports [i].architecture != nullptr) {
          if (imports [i].architecture->get_value () == BMF_IMPORT_ARCH_WIN32 &&
              imports [i].when->get_value         () == BMF_IMPORT_EARLY) {

            dll_log.LogEx (true, L"  * Loading Early Custom Import %s... ",
              imports [i].filename->get_value_str ().c_str ());

            if (! blacklisted) {
              imports [i].hLibrary = LoadLibrary (
                imports [i].filename->get_value_str ().c_str ()
              );

              if (imports [i].hLibrary != NULL) {
                dll_log.LogEx (false, L"success!\n");
                ++success;
              } else  {
                _com_error err (HRESULT_FROM_WIN32 (GetLastError ()));

                imports [i].hLibrary = (HMODULE)-2;
                dll_log.LogEx (false, L"failed: 0x%04X (%s)!\n",
                               err.WCode (), err.ErrorMessage () );
              }
            } else {
              dll_log.LogEx (false, L"failed: Host App is Blacklisted!\n");
            }
          }
        }
      }
    }
  }

  if (success > 0)
    dll_log.LogEx (false, L"\n");
}

void
BMF_LoadLateImports32 (void)
{
  int success = 0;

  for (int i = 0; i < BMF_MAX_IMPORTS; i++) {

    // Skip libraries that are already loaded
    if (imports [i].hLibrary != NULL)
      continue;

    bool         blacklisted = false;
    std::wstring blacklist   =
      imports [i].blacklist != nullptr ?
        imports [i].blacklist->get_value_str () :
        L"";

    if (blacklist.find (host_app) != std::wstring::npos)
      blacklisted = true;

    if (imports [i].filename != nullptr) {
      if (imports [i].when != nullptr) {
        if (imports [i].architecture != nullptr) {
          if (imports [i].architecture->get_value () == BMF_IMPORT_ARCH_WIN32 &&
              imports [i].when->get_value         () == BMF_IMPORT_LATE) {

            dll_log.LogEx (true, L"  * Loading Late Custom Import %s... ",
              imports [i].filename->get_value_str ().c_str ());

            if (! blacklisted) {
              imports [i].hLibrary = LoadLibrary (
                imports [i].filename->get_value_str ().c_str ()
                );

              if (imports [i].hLibrary != NULL) {
                dll_log.LogEx (false, L"success!\n");
                ++success;
              } else  {
                _com_error err (HRESULT_FROM_WIN32 (GetLastError ()));

                imports [i].hLibrary = (HMODULE)-2;
                dll_log.LogEx (false, L"failed: 0x%04X (%s)!\n",
                               err.WCode (), err.ErrorMessage () );
              }
            } else {
              dll_log.LogEx (false, L"failed: Host App is Blacklisted!\n");
            }
          }
        }
      }
    }
  }

  if (success > 0)
    dll_log.LogEx (false, L"\n");
}

void
BMF_LoadLazyImports32 (void)
{
  int success = 0;

  for (int i = 0; i < BMF_MAX_IMPORTS; i++) {

    // Skip libraries that are already loaded
    if (imports [i].hLibrary != NULL)
      continue;

    bool         blacklisted = false;
    std::wstring blacklist   =
      imports [i].blacklist != nullptr ?
        imports [i].blacklist->get_value_str () :
        L"";

    if (blacklist.find (host_app) != std::wstring::npos)
      blacklisted = true;

    if (imports [i].filename != nullptr) {
      if (imports [i].when != nullptr) {
        if (imports [i].architecture != nullptr) {
          if (imports [i].architecture->get_value () == BMF_IMPORT_ARCH_WIN32 &&
              imports [i].when->get_value         () == BMF_IMPORT_LAZY) {

            dll_log.LogEx (true, L"  * Loading Lazy Custom Import %s... ",
                imports [i].filename->get_value_str ().c_str ());

            if (! blacklisted) {
              imports [i].hLibrary = LoadLibrary (
                imports [i].filename->get_value_str ().c_str ()
                );

              if (imports [i].hLibrary != NULL) {
                dll_log.LogEx (false, L"success!\n");
                ++success;
              } else  {
                _com_error err (HRESULT_FROM_WIN32 (GetLastError ()));

                imports [i].hLibrary = (HMODULE)-3;
                dll_log.LogEx (false, L"failed: 0x%04X (%s)!\n",
                               err.WCode (), err.ErrorMessage () );
              }
            } else {
              dll_log.LogEx (false, L"failed: Host App is Blacklisted!\n");
            }
          }
        }
      }
    }
  }

  if (success > 0)
    dll_log.LogEx (false, L"\n");
}

void
BMF_UnloadImports (void)
{
  // Unload in reverse order, because that's safer :)
  for (int i = BMF_MAX_IMPORTS - 1; i >= 0; i--) {
    if (imports [i].hLibrary > 0) {
      dll_log.LogEx ( true,
                        L"Unloading Custom Import %s... ",
                          imports [i].filename->get_value_str ().c_str () );
      if (FreeLibrary (imports [i].hLibrary)) {
        dll_log.LogEx (false, L"success!\n");
      } else {
        _com_error err (HRESULT_FROM_WIN32 (GetLastError ()));

        dll_log.LogEx (false, L"failed: 0x%04X (%s)!\n",
          err.WCode (), err.ErrorMessage () );
      }
    }
  }
}