#ifdef _WIN32
#include "windows_ime_manager.h"
#include "Window/window.h"

#pragma comment(lib, "imm32.lib")

namespace Retro3D
{
	void WindowsIMEManager::EnableInput()
	{
		if (mInputMethodContext != nullptr)
		{
			mHwnd = (HWND)mInputMethodContext->GetIMContextWindow()->GetOSWindowHandle();

			if (mHwnd)
			{
				if (CreateCaret(mHwnd, NULL, 1, 1))
				{
					mImmContext = ImmGetContext(mHwnd);
					if (mImmContext)
					{
						ImmReleaseContext(mHwnd, mImmContext);
						ImmAssociateContextEx(mHwnd, NULL, IACE_DEFAULT);
						mInputEnabled = true;
					}
				}
			}
		}
	}

	void WindowsIMEManager::DisableInput()
	{
		if (mHwnd && mImmContext)
		{
			ImmAssociateContextEx(mHwnd, NULL, 0);
			mInputEnabled = false;
		}
	}

	void WindowsIMEManager::SetContext(ITextInputMethodContext* arg_context)
	{
		mInputMethodContext = arg_context;

		if (mInputEnabled)
		{
			EnableInput();
		}
	}

	bool WindowsIMEManager::GetString(std::string& out_string)
	{
		// Try get result string
		int stringSize = ::ImmGetCompositionString(mImmContext, GCS_RESULTSTR, NULL, 0);

		if (stringSize > 0)
		{
			int stringLength = stringSize / sizeof(wchar_t);

			// increase buffer size for terminating null character,  
			stringSize += sizeof(WCHAR);

			HGLOBAL hstr = GlobalAlloc(GHND, stringSize);
			if (hstr == NULL)
			{
			}

			LPSTR lpstr = (LPSTR)GlobalLock(hstr);
			if (lpstr == NULL)
			{
			}

			// Get the result strings into lpstr
			ImmGetCompositionString(mImmContext, GCS_RESULTSTR, lpstr, stringSize);
			ImmReleaseContext(mHwnd, mImmContext);

			GlobalUnlock(hstr);
			GlobalFree(hstr);
			return true;
		}

		return false;
	}
}

#endif
