#define WIN32_LEAN_AND_MEAN


int CALLBACK DialogProcedure(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL initHook();
BOOL unHook();