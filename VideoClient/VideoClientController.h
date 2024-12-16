#pragma once
#include <string>
#include "EVlc.h"
#include "VideoClientDlg.h"

enum EVlcCommand
{
	EVLC_PLAY,
	EVLC_PAUSE,
	EVLC_STOP,
	EVLC_GET_VOLUME,
	EVLC_GET_POSITION,
	EVLC_GET_LENGHT
};

class VideoClientController
{
public:
	VideoClientController();
	~VideoClientController();
	int Init(CWnd*& pWnd);
	int Invoke();
	int SetMedia(std::string& strUrt);
	float VideCtrl(EVlcCommand cmd);
	void SetPostion(float pos);
	int SetWnd(HWND hWnd);
	int SetVolume(int volume);
	VlcSize GetMedainfo();
	std::string Unicode2Utf8(const std::wstring& str);
public:
	EVlc m_vlc;
	CVideoClientDlg m_dlg;
};

