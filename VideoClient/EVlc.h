#pragma once
#include <vlc.h>
#include <string>

class VlcSize
{
public:
	int nWidth;
	int nHeight;
	VlcSize(int width = 0, int height = 0)
	{
		nWidth = width;
		nHeight = height;
	}
	VlcSize(const VlcSize& ss)
	{
		nWidth = ss.nWidth;
		nHeight = ss.nHeight;
	}
	VlcSize& operator=(const VlcSize& ss)
	{
		if (&ss != this)
		{
			nWidth = ss.nWidth;
			nHeight = ss.nHeight;
		}
		return *this;
	}
};

class EVlc
{
public:
	EVlc();
	~EVlc();
	//StrUrl如果包含中文 请传入utf-8格式字符串
	int SetMedia(std::string& StrUrl);
#ifdef WIN32
	int SetHWnd(HWND& hWnd);
#endif
	int Play();
	int Pause();
	int Stop();
	float GetPostion();
	void SetPostion(float& pos);
	int GetVolume();
	int SetVolume(int& volume);
	VlcSize GetMedaInfo();
	float GetLenght();
	std::string Unicode2Utf8(const std::wstring& str);
protected:
	libvlc_instance_t* m_instance;
	libvlc_media_t* m_media;
	libvlc_media_player_t* m_player;
	std::string m_url;
#ifdef WIN32
	HWND m_hwnd;
#endif
};

