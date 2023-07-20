
#include <QDebug>
#include <libraw/libraw.h>
#include <opencv2/opencv.hpp>


int main(int argc, char *argv[])
{
    LibRaw RawProcessor;

    // 打开一个.raw文件
    const char* raw_file = "E:\\test.ARW"; // 你的ARW文件路径
    RawProcessor.open_file(raw_file);

//    RawProcessor.imgdata.params.gamm[0] = 2.2; // 标准sRGB gamma
//    RawProcessor.imgdata.params.gamm[1] = 4.5; // 标准sRGB toe slope

//    RawProcessor.imgdata.params.exp_correc = 1; // 开启曝光补偿
//    RawProcessor.imgdata.params.exp_shift = 1.0; // 曝光补偿量，正数为增加曝光，负数为减少曝光

//    RawProcessor.imgdata.params.output_color = 1; // sRGB色彩空间

    // 使用自动白平衡
    RawProcessor.imgdata.params.use_camera_wb = 1; // 开启相机白平衡
    // 解压缩.raw文件
    RawProcessor.unpack();
    // 转换为图像
    RawProcessor.dcraw_process();

    // 将LibRaw图像转换为OpenCV Mat对象
    libraw_processed_image_t *image_ptr = RawProcessor.dcraw_make_mem_image();

    cv::Mat image = cv::Mat(image_ptr->height, image_ptr->width,
                                CV_8UC3, image_ptr->data);
    cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
//    cv::imwrite("E:\\raw.png", image);
    cv::resize(image, image,cv::Size(0,0), 0.1, 0.1);
    cv::imshow("raw",image);


    cv::Mat jpg = cv::imread("E:\\test.JPG");
    cv::resize(jpg, jpg,cv::Size(0,0), 0.1, 0.1);
    cv::imshow("jpg",jpg);

    cv::waitKey(0);

    qInfo() << "over";
    // 清理
    LibRaw::dcraw_clear_mem(image_ptr);
    RawProcessor.recycle();
    return 0;
}
