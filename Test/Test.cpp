  
#include "StdAfx.h"
#include "cv.h"  
#include "highgui.h"  

#include <opencv2/opencv.hpp>   
#include <cstdio>   
#include <cstdlib>   
#include <Windows.h>   
using namespace std;  
int main()  
{  
	

   // ����Haar������������   
    // haarcascade_frontalface_alt.xmlϵOpenCV�Դ��ķ����� �������һ����ϵ��ļ�·��   
   const char *pstrCascadeFileName = "haarcascade_frontalface_alt.xml";  
    CvHaarClassifierCascade *pHaarCascade = NULL;  
    pHaarCascade = (CvHaarClassifierCascade*)cvLoad(pstrCascadeFileName);  
  
   // ����ͼ��   
	const char *pstrImageName = "aa1.jpg";  
  IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);  
     
    IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);  
    cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);  
  
    // ����ʶ������   
   if (pHaarCascade != NULL)  
    {         
        CvScalar FaceCirclecolors[] =   
       {  
            {{0, 0, 255}},  
            {{0, 128, 255}},  
            {{0, 255, 255}},  
            {{0, 255, 0}},  
           {{255, 128, 0}},  
            {{255, 255, 0}},  
          {{255, 0, 0}},  
            {{255, 0, 255}}  
        };  
 
       CvMemStorage *pcvMStorage = cvCreateMemStorage(0);  
        cvClearMemStorage(pcvMStorage);  
        // ʶ��   
        DWORD dwTimeBegin, dwTimeEnd;  
        dwTimeBegin = GetTickCount();  
        CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarCascade, pcvMStorage);  
       dwTimeEnd = GetTickCount();  
 
       printf("��������: %d   ʶ����ʱ: %d ms\n", pcvSeqFaces->total, dwTimeEnd - dwTimeBegin);  
          
       // ���   
       for(int i = 0; i <pcvSeqFaces->total; i++)  
      {  
           CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i);  
            CvPoint center;  
           int radius;  
           center.x = cvRound((r->x + r->width * 0.5));  
           center.y = cvRound((r->y + r->height * 0.5));  
            radius = cvRound((r->width + r->height) * 0.25);  
            cvCircle(pSrcImage, center, radius, FaceCirclecolors[i % 8], 2);  
        }  
       cvReleaseMemStorage(&pcvMStorage);  
   }  
     
   const char *pstrWindowsTitle = "�������";  
   cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);  
    cvShowImage(pstrWindowsTitle, pSrcImage);  
  
  cvWaitKey(0);  

  cvDestroyWindow(pstrWindowsTitle);  
  cvReleaseImage(&pSrcImage);   
   cvReleaseImage(&pGrayImage);  
    return 0;  
}