// VideoPlay.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "vlc.h"
#include <Windows.h>

std::string Unicode2Utf8(const std::wstring& str)
{
	std::string strinfo;
	
	int lenght = ::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.size(), NULL, 0, NULL, NULL);
	strinfo.resize(lenght);
	::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.size(), (LPSTR)strinfo.c_str(), strinfo.size(), NULL, NULL);
	return strinfo;
}

int main()
{
	int argc = 1;
	char* argv[2];
	argv[0] = (char*)"--ignore-config";
	libvlc_instance_t* vlc_ins=libvlc_new(argc,argv);
	std::string path = Unicode2Utf8(L"C:\\Users\\19343\\Desktop\\西游记.mp4");
	libvlc_media_t* media = libvlc_media_new_path(vlc_ins,path.c_str());
	//media = libvlc_media_new_location();
	libvlc_media_player_t* player = libvlc_media_player_new_from_media(media);
	do
	{
		int ret = libvlc_media_player_play(player);
		if (ret == -1)
		{
			printf("error found!\r\n");
		}
		Sleep(300);
		int volume = libvlc_audio_get_volume(player);
		printf("当前视频音量:%d\r\n", volume);
		libvlc_time_t tm=libvlc_media_player_get_length(player);
		printf("%02d:%02d:%02d\r\n", (int)tm / 3600000, (int)(tm / 60000) % 60, (int)(tm/1000) % 60);
		int width = libvlc_video_get_width(player);
		int height = libvlc_video_get_height(player);
		printf("width=%d height=%d\r\n", width, height);
		getchar();
		libvlc_media_player_pause(player);
		volume = 30;
		libvlc_audio_set_volume(player, volume);
		printf("最大视频音量:%d\r\n", volume);
		float position=libvlc_media_player_get_position(player);
		printf("当前播放位置:%f\r\n", position);
		position = 0.5;
		libvlc_media_player_set_position(player,position);
		getchar();
		libvlc_media_player_play(player);
		position = libvlc_media_player_get_position(player);
		printf("当前播放位置:%f\r\n", position);
		getchar();
		libvlc_media_player_stop(player);
	} while (0);
	libvlc_media_player_release(player);
	libvlc_media_release(media);
	libvlc_release(vlc_ins);
}
