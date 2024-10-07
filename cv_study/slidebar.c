#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fsream>

using namespace std;

int g_slider_position =0;
int g_run =1,g_dontset=0'
cv::ViderCpture g_cap;

void onTrackbarSlide( int pos,void *){
	g_cap.set(cv::CAP_PROP_POS_FRAMES,pos);
	if ( !g_dontset){
	  g_run=1;
	}
	g_dontset =0;
}

