#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	Mat input_img, output_img;
	input_img = imread(argv[1], IMREAD_GRAYSCALE);
	if (input_img.empty())
	{
		cerr << "Couldn't open image . Exit program...................." << endl;
		return 1;
	}
	output_img = input_img.clone();
	//--------------------------------------------------------------------------------------------
	vector<vector<uchar>> pixel(input_img.rows, vector<uchar>(input_img.cols));
	uchar newPixelValue;
	for (int i{}; i < input_img.rows; i++)
		for (int j{}; j < input_img.cols; j++)
		{
			pixel[i][j] = input_img.at<uchar>(i, j);
		}
	for (int i{}; i < input_img.rows; i++)
		for (int j{}; j < input_img.cols; j++)
		{
			if ((i == 0 || j == 0) || (i == input_img.rows - 1 || j == input_img.cols - 1)) continue;
			newPixelValue = 0;
			for (int x = i - 1; x <= i + 1; x++)
				for (int y = j - 1; y <= j + 1; y++)
				{
					newPixelValue += pixel[x][y] / 9;
				}
			pixel[i][j] = newPixelValue;
		}
	for (int i{}; i < output_img.rows; i++)
		for (int j{}; j < output_img.cols; j++)
		{
			output_img.at<uchar>(i, j) = pixel[i][j];
		}
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], input_img);
	namedWindow("Average Filter 3x3", WINDOW_AUTOSIZE);
	imshow("Average Filter 3x3", output_img);
	waitKey();
	return 0;
}
