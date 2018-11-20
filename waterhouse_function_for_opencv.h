//update from 2018.11.08 



#pragma once
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>



//using namespace cv;
using namespace std;




//function name----------------------------------------------------------------------------

cv::Size NarrowSize(cv::Size input_size, float narrow_rate);
void NarrowMatToScreenSize(cv::Mat & input_img);
void AutoSizeImshow(cv::Mat input_img);
void PutImageIntoWindowRatio(cv::Mat & input_mat, cv::Mat & output_mat, const int limit_width, const int limit_height);
bool MyImageORoperator(cv::Mat & mat_input_1, cv::Mat & mat_input_2, cv::Mat & mat_ouput);
bool MyImageANDoperator(cv::Mat & mat_input_1, cv::Mat & mat_input_2, cv::Mat & mat_ouput);




//function content-------------------------------------------------------------------------

cv::Size NarrowSize(cv::Size input_size, float narrow_rate) {
	input_size.height = input_size.height * narrow_rate;
	input_size.width = input_size.width * narrow_rate;
	return input_size;
}

void NarrowMatToScreenSize(cv::Mat & input_img) {
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);  //'取得高度的像素
	int	ScreenWidth = GetSystemMetrics(SM_CXSCREEN);   //'取得寬度的像素

	cv::Size showing_size = input_img.size();
	while (1) {
		if (showing_size.height > ScreenHeight || showing_size.width > ScreenWidth) {
			showing_size = NarrowSize(showing_size, 0.5);
			continue;
		}
		break;
	}
	resize(input_img, input_img, showing_size);
}

void AutoSizeImshow(cv::Mat input_img) {
	if (input_img.empty()) { MessageBox(NULL, (LPCTSTR)_T("error! input_img is empty!"), NULL, MB_OK); return; }

	static int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);  //'取得高度的像素
	static int	ScreenWidth = GetSystemMetrics(SM_CXSCREEN);   //'取得寬度的像素
	static int window_counter = 0;
	window_counter = window_counter + 1;

	cv::Size showing_size = input_img.size();
	while (1) {
		if (showing_size.height > ScreenHeight || showing_size.width > ScreenWidth) {
			showing_size = NarrowSize(showing_size, 0.5);
			continue;
		}
		break;
	}
	if (showing_size.empty()) { MessageBox(NULL, (LPCTSTR)"error! the size will be zero!", NULL, MB_OK); return; }
	
	cv::Mat showing_img;
	cv::resize(input_img, showing_img, showing_size);
	string window_name = "window";
	window_name = window_name + to_string(window_counter);
	cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
	cv::imshow(window_name, showing_img);
	cv::waitKey(0);
}

void PutImageIntoWindowRatio(cv::Mat & input_mat, cv::Mat & output_mat, const int limit_width, const int limit_height) {
	if (input_mat.empty()) { MessageBox(NULL, (LPCTSTR)"input_mat is empty", NULL, MB_OK); return; }

	int output_width, output_height, narrow_ratio;
	if ((double)input_mat.rows / input_mat.cols > (double)limit_height / limit_width) {
		output_height = limit_height;
		output_width = (double)input_mat.cols * output_height / input_mat.rows;
	}
	else {
		output_width = limit_width;
		output_height = (double)input_mat.rows * output_width / input_mat.cols;
	}
	cv::resize(input_mat, output_mat, cv::Size(output_width, output_height));
}

//https ://blog.csdn.net/qq_34784753/article/details/55805076 
bool MyImageORoperator(cv::Mat & mat_input_1, cv::Mat & mat_input_2, cv::Mat & mat_ouput) {
	if (mat_input_1.type() != mat_input_2.type()) { MessageBox(NULL, (LPCTSTR)_T("error! two input type is different"), NULL, MB_OK); return 0; }
	if (mat_input_1.size != mat_input_2.size) { MessageBox(NULL, (LPCTSTR)_T("error! two input size is different"), NULL, MB_OK); return 0; }
	
	mat_ouput = mat_input_1.clone();
	int rowNumber = mat_ouput.rows;
	int colNumber = mat_ouput.cols;
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			//mat_ouput.at<uchar>(i, j) = (mat_input_1.at<uchar>(i, j) || mat_input_2.at<uchar>(i, j));
			if (mat_input_1.at<uchar>(i, j) > mat_input_2.at<uchar>(i, j)) {
				mat_ouput.at<uchar>(i, j) = mat_input_1.at<uchar>(i, j);
			}
			else {
				mat_ouput.at<uchar>(i, j) = mat_input_2.at<uchar>(i, j);
			}
		}
	}
	return 1;
}

bool MyImageANDoperator(cv::Mat & mat_input_1, cv::Mat & mat_input_2, cv::Mat & mat_ouput) {
	if (mat_input_1.type() !=mat_input_2.type()) { MessageBox(NULL, (LPCTSTR)_T("error! two input type is different"), NULL, MB_OK); return 0; }
	if (mat_input_1.size != mat_input_2.size) { MessageBox(NULL, (LPCTSTR)_T("error! two input size is different"), NULL, MB_OK); return 0; }
	
	mat_ouput = mat_input_1.clone();
	int rowNumber = mat_ouput.rows;
	int colNumber = mat_ouput.cols;
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			mat_ouput.at<uchar>(i, j) = (mat_input_1.at<uchar>(i, j) < mat_input_2.at<uchar>(i, j)) ? mat_input_1.at<uchar>(i, j) : mat_input_2.at<uchar>(i, j);
		}
	}
	return 1;
}
