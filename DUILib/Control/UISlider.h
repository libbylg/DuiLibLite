#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#include "Control/UIProgress.h"

namespace DUI
{
    class DUILIB_API CSliderUI : public CProgressUI
    {
        UI_DECLARE_CONTROL(CSliderUI)
    public:
        CSliderUI();

        LPCTSTR GetClass() const;
        UINT GetControlFlags() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        void SetEnabled(BOOL bEnable = TRUE);

        int GetChangeStep();
        void SetChangeStep(int step);
        void SetThumbSize(SIZE szXY);
        RECT GetThumbRect() const;
        LPCTSTR GetThumbImage() const;
        void SetThumbImage(LPCTSTR pStrImage);
        LPCTSTR GetThumbHotImage() const;
        void SetThumbHotImage(LPCTSTR pStrImage);
        LPCTSTR GetThumbPushedImage() const;
        void SetThumbPushedImage(LPCTSTR pStrImage);

        void DoEvent(struct TEVENT_UI& event);
        void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
        void PaintForeImage(HDC hDC);

        void SetValue(int nValue);
        void SetCanSendMove(BOOL bCanSend);
        BOOL GetCanSendMove() const;
    protected:
        SIZE m_szThumb;
        UINT m_uButtonState;
        int  m_nStep;

        CStringUI m_sThumbImage;
        CStringUI m_sThumbHotImage;
        CStringUI m_sThumbPushedImage;

        CStringUI m_sImageModify;
        BOOL      m_bSendMove;
    };
}

#endif // __UISLIDER_H__