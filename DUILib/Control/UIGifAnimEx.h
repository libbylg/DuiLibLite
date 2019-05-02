#ifndef GifAnimUIEX_h__
#define GifAnimUIEX_h__
#pragma once
/* write by wangji 2016.03.16
** ������gif�ؼ���gdi+������ռ��CPU���ߵ����⣬�������ximage���
** ע�⣺ʹ�õ�ʱ����Ԥ����ͷ�ļ��а���UIlib.hǰ�ȶ����USE_XIMAGE_EFFECT
** #define USE_XIMAGE_EFFECT
** 
*/
#ifdef USE_XIMAGE_EFFECT
namespace DUILIB
{
	class CLabelUI;

	class DUILIB_API CGifAnimExUI : public CLabelUI
	{
		UI_DECLARE_CONTROL(CGifAnimExUI)
	public:
		CGifAnimExUI(void);
		~CGifAnimExUI(void);
	public:
		virtual LPCTSTR	GetClass() const;
		virtual LPVOID	GetInterface(LPCTSTR pstrName);
		virtual void Init();
		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		virtual void SetVisible(BOOL bVisible = true);
		virtual void SetInternVisible(BOOL bVisible = true);
		virtual BOOL DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
		virtual void DoEvent(struct TEventUI& event);
	public:
		void StartAnim();
		void StopAnim();
	protected:
		struct Imp;
		Imp* m_pImp;
	};
}
#endif //USE_XIMAGE_EFFECT
#endif // GifAnimUIEx_h__