#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
using namespace cv;
using namespace std;
void averageFilter(Mat& input, Mat& output, vector<vector<double>>& kernel)
{
	double newRValue{}, newGValue{}, newBValue{};
	int halfSize = kernel.size() / 2;
	for (int i{ halfSize }; i < input.rows - halfSize; i++)
		for (int j{ halfSize }; j < input.cols - halfSize; j++)
		{
			newRValue = newGValue = newBValue = 0;
			for (int x = { -halfSize }; x <= halfSize; x++)
				for (int y = { -halfSize }; y <= halfSize; y++)
				{
					newBValue += input.at<Vec3b>(i + x, j + y)[0] * kernel[x + halfSize][y + halfSize];
					newGValue += input.at<Vec3b>(i + x, j + y)[1] * kernel[x + halfSize][y + halfSize];
					newRValue += input.at<Vec3b>(i + x, j + y)[2] * kernel[x + halfSize][y + halfSize];
				}
			output.at<Vec3b>(i, j) = Vec3b(newBValue, newGValue, newRValue);
		}
}
int main(int argc, char *argv[])
{
	Mat input_img;
	input_img = imread(argv[1], IMREAD_COLOR);
	if (input_img.empty())
	{
		cerr << "Couldn't open image . Exit program...................." << endl;
		return 1;
	}
	Mat output_img(input_img.rows, input_img.cols, CV_8UC3);
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

	waitKey();
	return 0;
}
