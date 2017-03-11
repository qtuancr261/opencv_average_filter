#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void averageFilter(Mat& input, Mat& output, vector<vector<double>>& kernel)
{
	double newPixelValue{};
	int halfSize = kernel.size() / 2 ;
	for (int i{halfSize}; i < input.rows - halfSize; i++)
		for (int j{halfSize}; j < input.cols - halfSize; j++)
		{
			newPixelValue = 0;
			for (int x = {-halfSize}; x <= halfSize; x++)
				for (int y = { -halfSize }; y <= halfSize; y++)
				{
					newPixelValue += input.at<uchar>(i + x , j + y)*kernel[x + halfSize][y + halfSize];
				}
			output.at<uchar>(i, j) = newPixelValue;
		}
}
int main(int argc, char *argv[])
{
	double start{ (double)getTickCount() };
	Mat input_img;
	input_img = imread(argv[1], IMREAD_GRAYSCALE);
	if (input_img.empty())
	{
		cerr << "Couldn't open image . Exit program...................." << endl;
		return 1;
	}
	Mat output_img(input_img.clone());
	//-------------------------------------------------------------------------------------------
	int kernelSize{};
	cout << " Nhap vao kich thuoc m cua ma tran Kernel: ";
	cin >> kernelSize;
	vector<vector<double>> kernel (kernelSize, vector<double>(kernelSize, 1/pow(kernelSize, 2.0)));
	averageFilter(input_img, output_img, kernel);
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	imshow(argv[1], input_img);
	namedWindow("Average Filter", WINDOW_AUTOSIZE);
	imshow("Average Filter", output_img);
	double end{ (double)(getTickCount() - start) / getTickFrequency() };
	cout << " Timing : " << end << endl;
	waitKey();
	return 0;
}
