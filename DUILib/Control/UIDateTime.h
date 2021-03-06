#ifndef __UIDATETIME_H__
#define __UIDATETIME_H__

#include "Control/UILabel.h"

namespace DUI
{
    class CDateTimeWnd;

    /// ʱ��ѡ��ؼ�
    class DUILIB_API CDateTimeUI : public CLabelUI
    {
        UI_DECLARE_CONTROL(CDateTimeUI)
            friend class CDateTimeWnd;
    public:
        CDateTimeUI();
        LPCTSTR GetClass() const;
        LPVOID GetInterface(LPCTSTR pstrName);

        SYSTEMTIME& GetTime();
        void SetTime(SYSTEMTIME* pst);

        void SetReadOnly(BOOL bReadOnly);
        BOOL IsReadOnly() const;

        void UpdateText();

        void DoEvent(struct TEVENT_UI& event);

    protected:
        SYSTEMTIME m_sysTime;
        int        m_nDTUpdateFlag;
        BOOL       m_bReadOnly;

        CDateTimeWnd* m_pWindow;
    };
}
#endif // __UIDATETIME_H__