#include "FileDirectory.h"

using namespace std;

int main()
{
	/*TCHAR szCurDir[MAX_PATH];
	DWORD dwCurDir = GetCurrentDirectory(sizeof(szCurDir) / sizeof(TCHAR), szCurDir);
	cout << szCurDir << endl;*/

	TCHAR szDir[MAX_PATH] = "C:";
	cout << szDir << endl;

	FileDirectory f1;
	f1.Traversal(f1.GetRoot());
	cout << "End!" << endl;

	return 0;
}