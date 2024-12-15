#include "pch.h"
#include "EVlc.h"

EVlc::EVlc()
{
	m_instance = libvlc_new(0, NULL);
	m_media = NULL;
	m_player = NULL;
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
	if (m_instance == NULL)return -1;
	m_media = libvlc_media_new_location(m_instance, StrUrl.c_str());
	if (m_media == NULL)return -2;
	m_player = libvlc_media_player_new_from_media(m_media);
	if (m_player == NULL)return -3;
	return 0;
}

int EVlc::SetHWnd(HWND& hWnd)
{
	if (!m_player||!m_media||!m_instance)return -1;
	libvlc_media_player_set_hwnd(m_player,hWnd);
	return 0;
}

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

