//  基于OpenCV和Winsock的图像传输（接收）
//

#include "WinsockMatTransmissionServer.h"  
#ifdef _DEBUG
#pragma comment(lib,"opencv_core2410d.lib")
#pragma comment(lib,"opencv_highgui2410d.lib")
#pragma comment(lib,"opencv_imgproc2410d.lib")
#else
#pragma comment(lib,"opencv_core2410.lib")
#pragma comment(lib,"opencv_highgui2410.lib")
#pragma comment(lib,"opencv_imgproc2410.lib")
#endif // DEBUG
int main()
{
	WinsockMatTransmissionServer socketMat;
	if (socketMat.socketConnect(8001) < 0)
	{
		return 0;
	}

	cv::Mat image;
	while (1)
	{
		if (socketMat.receive(image) > 0)
		{
			cv::imshow("Receive", image);
			cv::waitKey(1);
		}
		else
		{
			socketMat.socketDisconnect();
			if (socketMat.socketConnect(8001) < 0)
			{
				std::cout << "connect failed" << std::endl;
				return 0;
			}
		}
	}

	socketMat.socketDisconnect();
	return 0;
}