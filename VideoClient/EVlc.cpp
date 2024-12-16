#include "pch.h"
#include "EVlc.h"

EVlc::EVlc()
{
	m_instance = libvlc_new(0, NULL);
	m_media = NULL;
	m_player = NULL;
	m_hwnd = NULL;
}

EVlc::~EVlc()
{
	if (m_player != NULL)
	{
		libvlc_media_player_t* tmp = m_player;
		m_player = NULL;
		libvlc_media_player_release(tmp);
	}

	if (m_media != NULL)
	{
		libvlc_media_t* tmp = m_media;
		m_media = NULL;
		libvlc_media_release(tmp);
	}

	if (m_instance != NULL)
	{
		libvlc_instance_t* tmp = m_instance;
		m_media = NULL;
		libvlc_release(tmp);
	}
}

int EVlc::SetMedia(std::string& StrUrl)
{
	if (m_instance == NULL||(m_hwnd==NULL))return -1;
	if (m_url == StrUrl)return 0;
	m_url = StrUrl;
	if (m_media != NULL)
	{
		libvlc_media_release(m_media);
		m_media = NULL;
	}
	m_media = libvlc_media_new_location(m_instance, StrUrl.c_str());
	if (m_media == NULL)return -2;

	if (m_player != NULL)
	{
		libvlc_media_player_release(m_player);
		m_player = NULL;
	}
	m_player = libvlc_media_player_new_from_media(m_media);
	if (m_player == NULL)return -3;

	if (!m_player || !m_media || !m_instance)return -1;
	libvlc_media_player_set_hwnd(m_player, m_hwnd);
	return 0;
}

#ifdef WIN32
int EVlc::SetHWnd(HWND& hWnd)
{
	m_hwnd = hWnd;
	return 0;
}
#endif
int EVlc::Play()
{
	if (!m_player || !m_media || !m_instance)return -1;
	return libvlc_media_player_play(m_player);
}

int EVlc::Pause()
{
	if (!m_player || !m_media || !m_instance)return -1;
	libvlc_media_player_pause(m_player);
	return 0;
}

int EVlc::Stop()
{
	if (!m_player || !m_media || !m_instance)return -1;
	libvlc_media_player_stop(m_player);
	return 0;
}

float EVlc::GetPostion()
{
	if (!m_player || !m_media || !m_instance)return -1.0;
	return libvlc_media_player_get_position(m_player);
}

void EVlc::SetPostion(float& pos)
{
	if (!m_player || !m_media || !m_instance)return;
	libvlc_media_player_set_position(m_player,pos);
}

int EVlc::GetVolume()
{
	if (!m_player || !m_media || !m_instance)return -1;
	return libvlc_audio_get_volume(m_player);
}

int EVlc::SetVolume(int& volume)
{
	if (!m_player || !m_media || !m_instance)return -1;
	return libvlc_audio_set_volume(m_player, volume);
}

VlcSize EVlc::GetMedaInfo()
{
	if (!m_player || !m_media || !m_instance)return VlcSize(-1,-1);
	return VlcSize(libvlc_video_get_width(m_player), libvlc_video_get_width(m_player));
}

float EVlc::GetLenght()
{
	if (!m_player || !m_media || !m_instance)return -0.1;
	libvlc_time_t tm=libvlc_media_player_get_length(m_player);
	if (tm)
	{
		return tm / 1000.0f;
	}
	return -1.0f;
}

std::string EVlc::Unicode2Utf8(const std::wstring& str)
{
	std::string strinfo;

	int lenght = ::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.size(), NULL, 0, NULL, NULL);
	strinfo.resize(lenght);
	::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.size(), (LPSTR)strinfo.c_str(), strinfo.size(), NULL, NULL);
	return strinfo;
}

