#ifndef __UICONTROL__H__
#define __UICONTROL__H__

#include "Core/UIDefine.h"
#include "Core/UIDelegate.h"
#include "Core/UIManager.h"

namespace DUI
{

    /////////////////////////////////////////////////////////////////////////////////////
    //


    class CManagerUI;
    class CControlUI;

    // Flags for CControlUI::GetControlFlags()
#define UIFLAG_TABSTOP       0x00000001
#define UIFLAG_SETCURSOR     0x00000002
#define UIFLAG_WANTRETURN    0x00000004


    typedef struct DUILIB_API TPERCENTINFO_UI
    {
        double left;
        double top;
        double right;
        double bottom;
    } TPERCENTINFO_UI;

    // Structure for notifications from the system
    // to the control implementation.
    typedef struct DUILIB_API TEVENT_UI
    {
        int Type;
        CControlUI* pSender;
        DWORD dwTimestamp;
        POINT ptMouse;
        TCHAR chKey;
        WORD wKeyState;
        WPARAM wParam;
        LPARAM lParam;
    } TEVENT_UI;

    class CNotifyPumpUI;

    union TMSGMAPFUNC_UI
    {
        PMSG_UI pfn;   // generic member function pointer
        LRESULT(CNotifyPumpUI::* pfn_Notify_lwl)(WPARAM, LPARAM);
        void (CNotifyPumpUI::* pfn_Notify_vn)(TNOTIFY_UI&);
    };

    typedef CControlUI* (CALLBACK* FINDCONTROLPROC)(CControlUI*, LPVOID);

#define UI_DECLARE_CONTROL(class_name)\
public:\
	static CControlUI* CreateControl();

#define UI_IMPLEMENT_CONTROL(class_name)\
	CControlUI* class_name::CreateControl()\
	{ return new class_name; }

    class DUILIB_API CControlUI
    {
        UI_DECLARE_CONTROL(CControlUI)
    public:
        CControlUI();
        virtual ~CControlUI();

    public:
        virtual CStringUI GetName() const;
        virtual void SetName(LPCTSTR pstrName);
        virtual LPCTSTR GetClass() const;
        virtual LPVOID GetInterface(LPCTSTR pstrName);
        virtual UINT GetControlFlags() const;

        virtual BOOL Activate();
        virtual CManagerUI* GetManager() const;
        virtual void SetManager(CManagerUI* pManager, CControlUI* pParent, BOOL bInit = TRUE);
        virtual CControlUI* GetParent() const;
        void setInstance(HINSTANCE instance = NULL);

        // 定时器
        BOOL SetTimer(UINT nTimerID, UINT nElapse);
        void KillTimer(UINT nTimerID);

        // 文本相关
        virtual CStringUI GetText() const;
        virtual void SetText(LPCTSTR pstrText);

        virtual BOOL IsResourceText() const;
        virtual void SetResourceText(BOOL bResource);

        virtual BOOL IsDragEnabled() const;
        virtual void SetDragEnable(BOOL bDrag);

        virtual BOOL IsDropEnabled() const;
        virtual void SetDropEnable(BOOL bDrop);

        // 图形相关
        LPCTSTR GetGradient();
        void SetGradient(LPCTSTR pStrImage);
        DWORD GetBkColor() const;
        void SetBkColor(DWORD dwBackColor);
        DWORD GetBkColor2() const;
        void SetBkColor2(DWORD dwBackColor);
        DWORD GetBkColor3() const;
        void SetBkColor3(DWORD dwBackColor);
        DWORD GetForeColor() const;
        void SetForeColor(DWORD dwForeColor);
        LPCTSTR GetBkImage();
        void SetBkImage(LPCTSTR pStrImage);
        LPCTSTR GetForeImage() const;
        void SetForeImage(LPCTSTR pStrImage);

        DWORD GetFocusBorderColor() const;
        void SetFocusBorderColor(DWORD dwBorderColor);
        BOOL IsColorHSL() const;
        void SetColorHSL(BOOL bColorHSL);
        SIZE GetBorderRound() const;
        void SetBorderRound(SIZE cxyRound);
        BOOL DrawImage(HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);

        //边框相关
        int GetBorderSize() const;
        void SetBorderSize(int nSize);
        DWORD GetBorderColor() const;
        void SetBorderColor(DWORD dwBorderColor);
        void SetBorderSize(RECT rc);
        int GetLeftBorderSize() const;
        void SetLeftBorderSize(int nSize);
        int GetTopBorderSize() const;
        void SetTopBorderSize(int nSize);
        int GetRightBorderSize() const;
        void SetRightBorderSize(int nSize);
        int GetBottomBorderSize() const;
        void SetBottomBorderSize(int nSize);
        int GetBorderStyle() const;
        void SetBorderStyle(int nStyle);

        // 位置相关
        virtual RECT GetRelativePos() const; // 相对(父控件)位置
        virtual RECT GetClientPos() const; // 客户区域（除去scrollbar和inset）
        virtual const RECT& GetPos() const;
        virtual void SetPos(RECT rc, BOOL bNeedInvalidate = TRUE);
        virtual void Move(SIZE szOffset, BOOL bNeedInvalidate = TRUE);
        virtual int GetWidth() const;
        virtual int GetHeight() const;
        virtual int GetX() const;
        virtual int GetY() const;
        virtual RECT GetPadding() const;
        virtual void SetPadding(RECT rcPadding); // 设置外边距，由上层窗口绘制
        virtual SIZE GetFixedXY() const;         // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
        virtual void SetFixedXY(SIZE szXY);      // 仅float为TRUE时有效
        virtual int GetFixedWidth() const;       // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
        virtual void SetFixedWidth(int cx);      // 预设的参考值
        virtual int GetFixedHeight() const;      // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
        virtual void SetFixedHeight(int cy);     // 预设的参考值
        virtual int GetMinWidth() const;
        virtual void SetMinWidth(int cx);
        virtual int GetMaxWidth() const;
        virtual void SetMaxWidth(int cx);
        virtual int GetMinHeight() const;
        virtual void SetMinHeight(int cy);
        virtual int GetMaxHeight() const;
        virtual void SetMaxHeight(int cy);
        virtual TPERCENTINFO_UI GetFloatPercent() const;
        virtual void SetFloatPercent(TPERCENTINFO_UI piFloatPercent);
        virtual void SetFloatAlign(UINT uAlign);
        virtual UINT GetFloatAlign() const;

        // 鼠标提示
        virtual CStringUI GetToolTip() const;
        virtual void SetToolTip(LPCTSTR pstrText);
        virtual void SetToolTipWidth(int nWidth);
        virtual int	  GetToolTipWidth(void);	// 多行ToolTip单行最长宽度

        // 光标
        virtual WORD GetCursor();
        virtual void SetCursor(WORD wCursor);

        // 快捷键
        virtual TCHAR GetShortcut() const;
        virtual void SetShortcut(TCHAR ch);

        // 菜单
        virtual BOOL IsContextMenuUsed() const;
        virtual void SetContextMenuUsed(BOOL bMenuUsed);

        // 用户属性
        virtual const CStringUI& GetUserData(); // 辅助函数，供用户使用
        virtual void SetUserData(LPCTSTR pstrText); // 辅助函数，供用户使用
        virtual UINT_PTR GetTag() const; // 辅助函数，供用户使用
        virtual void SetTag(UINT_PTR pTag); // 辅助函数，供用户使用

        // 一些重要的属性
        virtual BOOL IsVisible() const;
        virtual void SetVisible(BOOL bVisible = TRUE);
        virtual void SetInternVisible(BOOL bVisible = TRUE); // 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
        virtual BOOL IsEnabled() const;
        virtual void SetEnabled(BOOL bEnable = TRUE);
        virtual BOOL IsMouseEnabled() const;
        virtual void SetMouseEnabled(BOOL bEnable = TRUE);
        virtual BOOL IsKeyboardEnabled() const;
        virtual void SetKeyboardEnabled(BOOL bEnable = TRUE);
        virtual BOOL IsFocused() const;
        virtual void SetFocus();
        virtual BOOL IsFloat() const;
        virtual void SetFloat(BOOL bFloat = TRUE);

        virtual CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

        void Invalidate();
        BOOL IsUpdateNeeded() const;
        void NeedUpdate();
        void NeedParentUpdate();
        DWORD GetAdjustColor(DWORD dwColor);

        virtual void Init();
        virtual void DoInit();

        virtual void Event(TEVENT_UI& event);
        virtual void DoEvent(TEVENT_UI& event);

        // 自定义(未处理的)属性
        void AddCustomAttribute(LPCTSTR pstrName, LPCTSTR pstrAttr);
        LPCTSTR GetCustomAttribute(LPCTSTR pstrName) const;
        BOOL RemoveCustomAttribute(LPCTSTR pstrName);
        void RemoveAllCustomAttribute();

        virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
        CControlUI* ApplyAttributeList(LPCTSTR pstrList);

        virtual SIZE EstimateSize(SIZE szAvailable);
        virtual BOOL Paint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl = NULL); // 返回要不要继续绘制
        virtual BOOL DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
        virtual void PaintBkColor(HDC hDC);
        virtual void PaintBkImage(HDC hDC);
        virtual void PaintStatusImage(HDC hDC);
        virtual void PaintForeColor(HDC hDC);
        virtual void PaintForeImage(HDC hDC);
        virtual void PaintText(HDC hDC);
        virtual void PaintBorder(HDC hDC);

        virtual void DoPostPaint(HDC hDC, const RECT& rcPaint);

        //虚拟窗口参数
        void SetVirtualWnd(LPCTSTR pstrValue);
        CStringUI GetVirtualWnd() const;

    public:
        CEventSource OnInit;
        CEventSource OnDestroy;
        CEventSource OnSize;
        CEventSource OnEvent;
        CEventSource OnNotify;

    protected:
        CManagerUI* m_pManager;
        CControlUI* m_pParent;
        CStringUI m_sVirtualWnd;
        CStringUI m_sName;
        BOOL m_bUpdateNeeded;
        BOOL m_bMenuUsed;
        RECT m_rcItem;
        RECT m_rcPadding;
        SIZE m_cXY;
        SIZE m_cxyFixed;
        SIZE m_cxyMin;
        SIZE m_cxyMax;
        BOOL m_bVisible;
        BOOL m_bInternVisible;
        BOOL m_bEnabled;
        BOOL m_bMouseEnabled;
        BOOL m_bKeyboardEnabled;
        BOOL m_bFocused;
        BOOL m_bFloat;
        TPERCENTINFO_UI m_piFloatPercent;
        UINT m_uFloatAlign;
        BOOL m_bSetPos; // 防止SetPos循环调用

        BOOL m_bDragEnabled;
        BOOL m_bDropEnabled;

        BOOL m_bResourceText;
        CStringUI m_sText;
        CStringUI m_sToolTip;
        TCHAR m_chShortcut;
        CStringUI m_sUserData;
        UINT_PTR m_pTag;

        CStringUI m_sGradient;
        DWORD m_dwBackColor;
        DWORD m_dwBackColor2;
        DWORD m_dwBackColor3;
        DWORD m_dwForeColor;
        CStringUI m_sBkImage;
        CStringUI m_sForeImage;
        DWORD m_dwBorderColor;
        DWORD m_dwFocusBorderColor;
        BOOL m_bColorHSL;
        int m_nBorderSize;
        int m_nBorderStyle;
        int m_nTooltipWidth;
        WORD m_wCursor;
        SIZE m_cxyBorderRound;
        RECT m_rcPaint;
        RECT m_rcBorderSize;
        HINSTANCE m_instance;

        CStringMapUI m_mCustomAttrHash;
    };

} // namespace DUI

#endif // __UICONTROL__H__
