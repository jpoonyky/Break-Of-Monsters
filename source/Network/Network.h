#pragma once

class Network
{
private:
	WSAData wsaData;

	SOCKET sock;
	struct sockaddr_in addr;
public:
	void Startup()
	{
		WSAStartup( MAKEWORD( 2 , 0 ) , &wsaData );

		sock = socket( AF_INET , SOCK_DGRAM , 0 );

		addr.sin_family = AF_INET;
		addr.sin_port = htons( 12345 );
		addr.sin_addr.S_un.S_addr = inet_addr( "172.22.102.71" );
	}

	enum type
	{
		NONE,		//	�l�b�g���[�N����
		SAVER,		//	�T�[�o�[�Ƃ��Ďg�p
		CLIENT,		//	�N���C�A���g�Ƃ��Ďg�p
	};
};