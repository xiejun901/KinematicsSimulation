#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_
#pragma once

#include<windows.h>

#include<stdlib.h>
#include<math.h>
#include<vector>

#include<d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <dwmapi.h>

#include"Vector2d.h"
#include"Particle.h"

template<class Interface>
inline void SafeRelease(Interface ** pp)
{
	if (*pp != nullptr)
	{
		(*pp)->Release();
		*pp = nullptr;
	}
}
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

class MainWindow
{
public:
	MainWindow();
	~MainWindow();
	HRESULT Initialize();//初始化，返回值为初始化状态（是否成功之类的）
	void RunMessageLoop();
private:
	HRESULT CreateDeviceIndependentResources();//
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();
	virtual HRESULT OnRender();
	void OnResize(UINT width, UINT height);
	/***************************************************************************************************************************************
	*CALLBACK: 表明此函数将作为回调函数。
	*1  回调函数必须有关键词 CALLBACK；回调函数本身必须是全局函数或者静态函数。不要使用类的成员函数(也就是说 要使用全局函数) 作为callback函数，在成员函数前使用static,也就是在函数前加上static修饰词，可以声明回调函数。
	*2  回调函数并不由开发者直接调用执行(只是使用系统接口API函数作为起点)
	*3  回调函数通常作为参数传递给系统API，由该API来调用
	*4  回调函数可能被系统API调用一次，也可能被循环调用多次
	*/
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnTimer();
	void emitParitcle(Particle);
	void drawParticleContainer(D2D1_SIZE_F rtSize);
private:
	HWND m_hwnd;
	ID2D1Factory *m_pDirect2dFactory;//
	ID2D1HwndRenderTarget *m_pRenderTarget;
	ID2D1SolidColorBrush *m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush *m_pCornflowerBlueBrush;
	DWM_TIMING_INFO m_DwmTimingInfo;

	/******************/
	//Vector2D position;// = Vector2D(10.0L, 20.0L);
	//Vector2D velocity;// = Vector2D(50.0L, -1.0*50.0L);
	//Vector2D acceleration;// = Vector2D(0.0L, 10.0L);
	Particle m_Paricle;
	std::vector<Particle> m_ParicleContainer;
	int clocktime;
};

#endif