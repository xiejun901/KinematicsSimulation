#include"MainWindow.h"

int WINAPI WinMain(
	HINSTANCE /* hInstance */,
	HINSTANCE /* hPrevInstance */,
	LPSTR /* lpCmdLine */,
	int /* nCmdShow */
	)
{
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	Vector2D<float> v1(2.0, 3.0);
	Vector2D<float> v2(2.0, 3.0);
	Vector2D<float> v3;
	v3 = v1 + v2;

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			MainWindow app;

			if (SUCCEEDED(app.Initialize()))
			{
				app.RunMessageLoop();
			}
		}
		CoUninitialize();
	}

	return 0;
}