#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
	Mat input_img, output_img;
	input_img = imread(argv[1], IMREAD_COLOR);
	if (input_img.empty())
	{
		cerr << "Couldn't open image . Exit program...................." << endl;
		return 1;
	}
	output_img = input_img.clone();
	//--------------------------------------------------------------------------------------------
	vector<vector<Vec3b>> pixel(input_img.rows, vector<Vec3b>(input_img.cols));
	Vec3b newPixel;
	newPixel[0] = newPixel[1] = newPixel[2] = 0;
	for (int i{}; i < input_img.rows; i++)
		for (int j{}; j < input_img.cols; j++)
		{
			pixel[i][j] = input_img.at<Vec3b>(i, j);
		}
	for (int i{}; i < input_img.rows; i++)
		for (int j{}; j < input_img.cols; j++)
		{
			if ((i == 0 || j == 0) || (i == input_img.rows - 1 || j == input_img.cols - 1)) continue;
			newPixel[0] = newPixel[1] = newPixel[2] = 0;
			for (int x = i - 1; x <= i + 1; x++)
				for (int y = j - 1; y <= j + 1; y++)
				{
					newPixel[0] += pixel[x][y][0] / 9;
					newPixel[1] += pixel[x][y][1] / 9;
					newPixel[2] += pixel[x][y][2] / 9;
				}
			pixel[i][j] = newPixel;
		}
	for (int i{}; i < output_img.rows; i++)
		for (int j{}; j < output_img.cols; j++)
		{
			output_img.at<Vec3b>(i, j) = pixel[i][j];
		}
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], input_img);
	namedWindow("AfteraverageFilter.jpg", WINDOW_AUTOSIZE);
	imshow("AfteraverageFilter.jpg", output_img);

	waitKey();
	return 0;
}
