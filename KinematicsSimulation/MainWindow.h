#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_
#pragma once

#include<windows.h>

#include<stdlib.h>
#include<math.h>

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
	HRESULT Initialize();//��ʼ��������ֵΪ��ʼ��״̬���Ƿ�ɹ�֮��ģ�
	void RunMessageLoop();
private:
	HRESULT CreateDeviceIndependentResources();//
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();
	virtual HRESULT OnRender();
	void OnResize(UINT width, UINT height);
	/***************************************************************************************************************************************
	*CALLBACK: �����˺�������Ϊ�ص�������
	*1  �ص����������йؼ��� CALLBACK���ص��������������ȫ�ֺ������߾�̬��������Ҫʹ����ĳ�Ա����(Ҳ����˵ Ҫʹ��ȫ�ֺ���) ��Ϊcallback�������ڳ�Ա����ǰʹ��static,Ҳ�����ں���ǰ����static���δʣ����������ص�������
	*2  �ص����������ɿ�����ֱ�ӵ���ִ��(ֻ��ʹ��ϵͳ�ӿ�API������Ϊ���)
	*3  �ص�����ͨ����Ϊ�������ݸ�ϵͳAPI���ɸ�API������
	*4  �ص��������ܱ�ϵͳAPI����һ�Σ�Ҳ���ܱ�ѭ�����ö��
	*/
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnTimer();
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
};

#endif