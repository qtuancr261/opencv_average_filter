#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector>
using namespace cv;
using namespace std;
void averageFilter(Mat& input, Mat& output, vector<vector<double>>& kernel)
{
	double newRValue{}, newGValue{}, newBValue{};
	int halfSize = kernel.size() / 2;
	for (int i{ halfSize }; i < input.rows - halfSize; i++)
	{
		Vec3b* output_pixrow = output.ptr<Vec3b>(i);
		for (int j{ halfSize }; j < input.cols - halfSize; j++)
		{
			newRValue = newGValue = newBValue = 0;
			for (int x = { -halfSize }; x <= halfSize; x++)
			{
				Vec3b* input_pixrow = input.ptr<Vec3b>(i + x);
				for (int y = { -halfSize }; y <= halfSize; y++)
				{
					newBValue += input_pixrow[j + y][0] * kernel[x + halfSize][y + halfSize];
					newGValue += input_pixrow[j + y][1] * kernel[x + halfSize][y + halfSize];
					newRValue += input_pixrow[j + y][2] * kernel[x + halfSize][y + halfSize];
				}
			}
			output_pixrow[j] = Vec3b(newBValue, newGValue, newRValue);
		}
	}
}
/*void averageFilter(Mat& input, Mat& output, vector<vector<double>>& kernel)
{
	double newRValue{}, newGValue{}, newBValue{};
	int halfSize = kernel.size() / 2;
	for (int i{ halfSize }; i < input.rows - halfSize; i++)
	{
		for (int j{ halfSize }; j < input.cols - halfSize; j++)
		{
			newRValue = newGValue = newBValue = 0;
			for (int x = { -halfSize }; x <= halfSize; x++)
			{
				for (int y = { -halfSize }; y <= halfSize; y++)
				{
					newBValue += input.at<Vec3b>(i + x, j + y)[0] * kernel[x + halfSize][y + halfSize];
					newGValue += input.at<Vec3b>(i + x, j + y)[1] * kernel[x + halfSize][y + halfSize];
					newRValue += input.at<Vec3b>(i + x, j + y)[2] * kernel[x + halfSize][y + halfSize];
				}
			}
			output.at<Vec3b>(i, j) = Vec3b(newBValue, newGValue, newRValue);
		}
	}
}*/
int main(int argc, char *argv[])
{
	double start{ (double)getTickCount() };
	Mat input_img;
	input_img = imread(argv[1], IMREAD_COLOR);
	if (input_img.empty())
	{
		cerr << "Couldn't open image . Exit program...................." << endl;
		return 1;
	}
	Mat output_img(input_img.clone());
	//--------------------------------------------------------------------------------------------
	int kernelSize{};
	cout << " Nhap vao kich thuoc m cua ma tran Kernel: ";
	cin >> kernelSize;
	vector<vector<double>> kernel(kernelSize, vector<double>(kernelSize, 1 / pow(kernelSize, 2.0)));
	averageFilter(input_img, output_img, kernel);
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], input_img);
	namedWindow("average Filter", WINDOW_AUTOSIZE);
	imshow("average Filter", output_img);
	double end{ (double)(getTickCount() - start) / getTickFrequency() };
	cout << " Timing : " << end << endl;
	waitKey();
	return 0;
}
