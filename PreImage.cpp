#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

void GetImgNameList(std::string ImgReadPath,std::vector<cv::String> &ImgNameList);

void renameSizeSave(std::vector<cv::String> &VstrImgNamesOne);

int main(int argc, char const *argv[])
{
    std::string ImgReadPathOne = "/home/yujr/seg/SemOrg/images-";
    std::vector<cv::String> ImgNameList; 
    
    GetImgNameList(ImgReadPathOne,ImgNameList);
   
    renameSizeSave(ImgNameList);

    return 0;
}


void GetImgNameList(std::string ImgReadPath,std::vector<cv::String> &ImgNameList)
{
    for (size_t i = 0; i < 628; i++)
    {
        std::stringstream ImgName;
        ImgName << ImgReadPath << std::setfill('0') << std::setw(5) << i << ".bmp";
        ImgNameList.push_back(ImgName.str());
         
    }
}

void renameSizeSave(std::vector<cv::String> &VstrImgNamesOne)
{
    std::string ImgWritePath = "/home/yujr/openslam_openseqslam/datasets/SemOrg/seg/images-";

    int j=1;
    for (size_t i = 0; i < VstrImgNamesOne.size(); i++)
    {
        cv::Mat srcImg = cv::imread(VstrImgNamesOne[i],CV_LOAD_IMAGE_UNCHANGED);
        
        if (srcImg.empty())
        {
            std::cerr << std::endl << "Failed to load image at : " << VstrImgNamesOne[i] << std::endl;
        }
        else
        {
            cv::Mat srcImg2;
            cv::Size dstSize = cv::Size(64,32);
            cv::resize(srcImg,srcImg2,dstSize,0,0,cv::INTER_LINEAR);

            std::stringstream strName;
            strName << ImgWritePath << std::setfill('0') << std::setw(5) << j++ << ".bmp";
            cv::imwrite(strName.str(), srcImg2);
        }
    }
}