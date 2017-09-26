//  基于OpenCV和Winsock的图像传输（发送）
//

#include "WinsockMatTransmissionClient.h"  
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
	WinsockMatTransmissionClient socketMat;
	if (socketMat.socketConnect("127.0.0.1", 8001) < 0)
	{
		return 0;
	}

	cv::VideoCapture capture(0);
	cv::Mat image;

	while (1)
	{
		if (!capture.isOpened())
			return 0;

		capture >> image;

		if (image.empty())
			return 0;

		socketMat.transmit(image);
		
		cv::imshow("Client", image);
		//cv::waitKey(30);
		if (cv::waitKey(1)==27)
			break;
	}

	socketMat.socketDisconnect();
	return 0;
}