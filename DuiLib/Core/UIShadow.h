#ifndef __UISHADOW_H__
#define __UISHADOW_H__

#include "Utils/Utils.h"

namespace DUILIB
{

    class DUILIB_API CShadowUI
    {
    public:
        friend class CManagerUI;

        CShadowUI(void);
        virtual ~CShadowUI(void);

    public:
        // bShow为真时才会创建阴影
        void ShowShadow(BOOL bShow);
        BOOL IsShowShadow() const;

        void DisableShadow(BOOL bDisable);
        BOOL IsDisableShadow() const;

        // 算法阴影的函数
        BOOL SetSize(int NewSize = 0);
        BOOL SetSharpness(unsigned int NewSharpness = 5);
        BOOL SetDarkness(unsigned int NewDarkness = 200);
        BOOL SetPosition(int NewXOffset = 5, int NewYOffset = 5);
        BOOL SetColor(COLORREF NewColor = 0);

        // 图片阴影的函数
        BOOL SetImage(LPCTSTR szImage);
        BOOL SetShadowCorner(RECT rcCorner);	// 九宫格方式描述阴影

        // 把自己的阴影样式复制到传入参数
        BOOL CopyShadow(CShadowUI* pShadow);

        //	创建阴影窗体，由CPaintManagerUI自动调用,除非自己要单独创建阴影
        void Create(CManagerUI* pPaintManager);
    protected:

        //	初始化并注册阴影类
        static BOOL Initialize(HINSTANCE hInstance);

        // 保存已经附加的窗体句柄和与其关联的阴影类,方便在ParentProc()函数中通过句柄得到阴影类
        static std::map<HWND, CShadowUI*>& GetShadowMap();

        //	子类化父窗体
        static LRESULT CALLBACK ParentProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        // 父窗体改变大小，移动，或者主动重绘阴影时调用
        void Update(HWND hParent);

        // 通过算法计算阴影
        void MakeShadow(UINT32* pShadBits, HWND hParent, RECT* rcParent);

        // 计算alpha预乘值
        inline DWORD PreMultiply(COLORREF cl, UCHAR nAlpha)
        {
            return (GetRValue(cl) * (DWORD)nAlpha / 255) |
                (GetGValue(cl) * (DWORD)nAlpha / 255) << 8 |
                (GetBValue(cl) * (DWORD)nAlpha / 255) << 16;
        }

    protected:
        enum ShadowStatus
        {
            SS_ENABLED = 1,				// Shadow is enabled, if not, the following one is always false
            SS_VISABLE = 1 << 1,		// Shadow window is visible
            SS_PARENTVISIBLE = 1 << 2	// Parent window is visible, if not, the above one is always false
        };


        static BOOL s_bHasInit;

        CManagerUI* m_pManager;		// 父窗体的CPaintManagerUI，用来获取素材资源和父窗体句柄
        HWND			 m_hWnd;			// 阴影窗体的句柄
        LONG_PTR		 m_OriParentProc;	// 子类化父窗体
        BYTE			 m_Status;
        BOOL			 m_bIsImageMode;	// 是否为图片阴影模式
        BOOL			 m_bIsShowShadow;	// 是否要显示阴影
        BOOL			m_bIsDisableShadow;
        // 算法阴影成员变量
        unsigned char m_nDarkness;	// Darkness, transparency of blurred area
        unsigned char m_nSharpness;	// Sharpness, width of blurred border of shadow window
        signed char m_nSize;	// Shadow window size, relative to parent window size

        // The X and Y offsets of shadow window,
        // relative to the parent window, at center of both windows (not top-left corner), signed
        signed char m_nxOffset;
        signed char m_nyOffset;

        // Restore last parent window size, used to determine the update strategy when parent window is resized
        LPARAM m_WndSize;

        // Set this to true if the shadow should not be update until next WM_PAINT is received
        BOOL m_bUpdate;

        COLORREF m_Color;	// Color of shadow

        // 图片阴影成员变量
        CDuiString	m_sShadowImage;
        RECT		m_rcShadowCorner;
    };



}

#endif //__UISHADOW_H__