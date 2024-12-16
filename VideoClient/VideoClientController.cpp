#include "pch.h"
#include "VideoClientController.h"

VideoClientController::VideoClientController():m_vlc(EVlc())
{
	m_dlg.m_controller = this;
}

VideoClientController::~VideoClientController()
{
}

int VideoClientController::Init(CWnd*& pWnd)
{
	pWnd = &m_dlg;
	return 0;
}

int VideoClientController::Invoke()
{
	INT_PTR nResponse = m_dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}
	return nResponse;
}

int VideoClientController::SetMedia(std::string& strUrt)
{
	return m_vlc.SetMedia(strUrt);
}

float VideoClientController::VideCtrl(EVlcCommand cmd)
{
	switch (cmd)
	{
	case EVLC_PLAY:
		return (float)m_vlc.Play();
		break;
	case EVLC_PAUSE:
		return (float)m_vlc.Pause();
		break;
	case EVLC_STOP:
		return (float)m_vlc.Stop();
		break;
	case EVLC_GET_VOLUME:
		return (float)m_vlc.GetVolume();
		break;
	case EVLC_GET_POSITION:
		return (float)m_vlc.GetPostion();
		break;
	case EVLC_GET_LENGHT:
		return m_vlc.GetLenght();
	default:
		break;
	}
	return -1.0;
}

void VideoClientController::SetPostion(float pos)
{
	m_vlc.SetPostion(pos);
}

int VideoClientController::SetWnd(HWND hWnd)
{
	return m_vlc.SetHWnd(hWnd);
}

int VideoClientController::SetVolume(int volume)
{
	return m_vlc.SetVolume(volume);
}

VlcSize VideoClientController::GetMedainfo()
{
	return m_vlc.GetMedaInfo();
}

std::string VideoClientController::Unicode2Utf8(const std::wstring& str)
{
	return m_vlc.Unicode2Utf8(str);
}
