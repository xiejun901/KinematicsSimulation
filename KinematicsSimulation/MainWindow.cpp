#include"MainWindow.h"
MainWindow::MainWindow() :
m_hwnd(0),
m_pDirect2dFactory(nullptr),
m_pRenderTarget(nullptr),
m_pLightSlateGrayBrush(nullptr),
m_pCornflowerBlueBrush(nullptr)
{
}
MainWindow::~MainWindow()
{
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pLightSlateGrayBrush);
	SafeRelease(&m_pCornflowerBlueBrush);
}
void MainWindow::RunMessageLoop()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

HRESULT MainWindow::Initialize()
{
	HRESULT hr;
	//m_Paricle = Particle(Vector2D<float>(100.0f, 100.0f), Vector2D<float>(100.0f, 0.0f), Vector2D<float>(0.0f, 300.0f), 10.0f);
	m_ParicleContainer.push_back(Particle(Vector2D<float>(100.0f, 100.0f), Vector2D<float>(100.0f, 0.0f), Vector2D<float>(0.0f, 300.0f), 10.0f));
	clocktime = 0;
	hr = CreateDeviceIndependentResources();
	if (SUCCEEDED(hr))
	{
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = MainWindow::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = HINST_THISCOMPONENT;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"D2DDemoApp";
		RegisterClassEx(&wcex);

		FLOAT dpiX, dpiY;
		m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);
		m_hwnd = CreateWindow(
			L"D2DDemoApp",
			L"Direct2D Demo App",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
			static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			this
			);

		hr = m_hwnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			ZeroMemory(&m_DwmTimingInfo, sizeof(m_DwmTimingInfo));
			m_DwmTimingInfo.cbSize = sizeof(m_DwmTimingInfo);

			// Get the composition refresh rate. If the DWM isn't running,
			// get the refresh rate from GDI -- probably going to be 60Hz
			if (FAILED(DwmGetCompositionTimingInfo(NULL, &m_DwmTimingInfo)))
			{
				HDC hdc = GetDC(m_hwnd);
				m_DwmTimingInfo.rateCompose.uiDenominator = 1;
				m_DwmTimingInfo.rateCompose.uiNumerator = GetDeviceCaps(hdc, VREFRESH);
				ReleaseDC(m_hwnd, hdc);
			}
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_hwnd);
		}
	}
	return hr;
}

HRESULT MainWindow::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
	return hr;
}

HRESULT MainWindow::CreateDeviceResources()
{
	HRESULT hr = S_OK;
	if (!m_pRenderTarget)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget
			);
		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::LightSlateGray),
				&m_pLightSlateGrayBrush);
		}
		if (SUCCEEDED(hr))
		{
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
				&m_pCornflowerBlueBrush);
		}
	}
	return hr;
}
void MainWindow::DiscardDeviceResources()
{
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pLightSlateGrayBrush);
	SafeRelease(&m_pCornflowerBlueBrush);
}
LRESULT CALLBACK MainWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		MainWindow *pMainWindow = (MainWindow *)pcs->lpCreateParams;
		::SetWindowLongPtrW(hwnd, GWLP_USERDATA, PtrToUlong(pMainWindow));
		result = 1;
	}
	else
	{
		MainWindow *pMainWindow = reinterpret_cast<MainWindow *>(static_cast<LONG_PTR>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA)));
		bool wasHandle = false;
		if (pMainWindow)
		{
			switch (message)
			{
			case WM_SIZE:
			{
							UINT width = LOWORD(lParam);
							UINT height = HIWORD(lParam);
							pMainWindow->OnResize(width, height);
			}
				result = 0;
				wasHandle = true;
				break;
			case WM_DISPLAYCHANGE:
				////{
				////	InvalidateRect(hwnd, nullptr, false);
				////}
				////result = 0;
				////wasHandle = true;
				////break;
			case WM_PAINT:
			{
							 PAINTSTRUCT ps;
							 BeginPaint(hwnd, &ps);
							 pMainWindow->OnRender();
							 EndPaint(hwnd, &ps);
							 //ValidateRect(hwnd, nullptr);
			}
				result = 0;
				wasHandle = true;
				break;
			case WM_DESTROY:
			{
							   PostQuitMessage(0);
			}
				result = 0;
				wasHandle = true;
				break;
			}
		}
		if (!wasHandle)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}
	return result;
}
HRESULT MainWindow::OnRender()
{
	HRESULT hr = S_OK;
	//创建设备依赖资源，包含一个呈现器，两个SolidBrush;
	hr = CreateDeviceResources();
	if (SUCCEEDED(hr))
	{
		m_pRenderTarget->BeginDraw();
		//创建了一个单位矩阵传SetTranform()方法里去，转换呈现器？没懂。。。应该是创建个用于旋转的矩阵就能旋转，单位矩阵应该就是不变吧
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
		//检测呈现器的绘制区域大小
		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
		clocktime++;
		if (clocktime == 60)
		{
			clocktime = 0;
			m_ParicleContainer.push_back(Particle(Vector2D<float>(100.0f, 100.0f), Vector2D<float>(100.0f, 0.0f), Vector2D<float>(0.0f, 300.0f), 10.0f + static_cast<float>(rand()%20)));
		}
		drawParticleContainer(rtSize);
		hr = m_pRenderTarget->EndDraw();

	}
	InvalidateRect(m_hwnd, nullptr, false);
	return hr;
}
void MainWindow::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
}

void MainWindow::emitParitcle(Particle p)
{
	m_ParicleContainer.push_back(p);
}
void MainWindow::drawParticleContainer(D2D1_SIZE_F rtSize)
{
	for (auto &particles : m_ParicleContainer)
	{
		particles.position = particles.position + 1.0f / 60.0f*particles.velocity;
		particles.velocity = particles.velocity + 1.0f / 60.0f*particles.acceleration;
		const float r = particles.radius;
		if (particles.position.gety() + r > rtSize.height)
		{
			particles.velocity.negtivey();
			particles.position.addy(rtSize.height - particles.position.gety() - r);
		}
		if (particles.position.gety() - r < 0.0)
		{
			particles.velocity.negtivey();
			particles.position.addy(r - particles.position.gety());
		}
		if (particles.position.getx() + r > rtSize.width)
		{
			particles.velocity.negtivex();
			particles.position.addx(rtSize.width - particles.position.getx() - r);
		}
		if (particles.position.getx() - r < 0.0)
		{
			particles.velocity.negtivex();
			particles.position.addx(r - particles.position.getx());
		}
		const float x = particles.position.getx();
		const float y = particles.position.gety();
		D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), r, r);
		m_pRenderTarget->FillEllipse(&ellipse, m_pCornflowerBlueBrush);
	}
}
