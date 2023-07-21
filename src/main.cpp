
#include <QDebug>
#include <libraw/libraw.h>
#include <opencv2/opencv.hpp>
#include <QString>

int main(int argc, char *argv[])
{
    LibRaw RawProcessor;

    // 打开一个.raw文件
    const char* raw_file = "E:\\test.ARW"; // 你的ARW文件路径
    RawProcessor.open_file(raw_file);

    for (int use_camera_wb : {0,1}){
        for (int use_auto_wb : {0,1}){
            for (int output_color : {0,1,2,3,4,5}){
                for (int no_auto_bright : {0,1}){
                    for (int user_qual : {0,1, 2,3}){
                        for (int highlight : {0,1, 2,3}){



                            RawProcessor.imgdata.params.use_camera_wb = use_camera_wb;
                            RawProcessor.imgdata.params.use_auto_wb = use_auto_wb;
                            RawProcessor.imgdata.params.output_color = output_color;
                            RawProcessor.imgdata.params.no_auto_bright = no_auto_bright;
                            RawProcessor.imgdata.params.user_qual = user_qual;
                            RawProcessor.imgdata.params.highlight = highlight;


                            // 解压缩.raw文件
                            RawProcessor.unpack();
                            // 转换为图像
                            RawProcessor.dcraw_process();

                            // 将LibRaw图像转换为OpenCV Mat对象
                            libraw_processed_image_t *image_ptr = RawProcessor.dcraw_make_mem_image();

                            cv::Mat image = cv::Mat(image_ptr->height, image_ptr->width,
                                                        CV_8UC3, image_ptr->data);
                            cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
                            cv::resize(image, image,cv::Size(0,0), 0.125, 0.125);

                            QString name = QString("E:\\raw_%1_%2_%3_%4_%5_%6.png")
                                    .arg(use_camera_wb).arg(use_auto_wb).arg(output_color)
                                    .arg(no_auto_bright).arg(user_qual).arg(highlight);
                            cv::imwrite(name.toStdString().c_str() , image);

                            // 清理
                            LibRaw::dcraw_clear_mem(image_ptr);
                        }
                    }
                }
            }
        }
    }


    cv::Mat jpg = cv::imread("E:\\test.JPG");
    cv::resize(jpg, jpg,cv::Size(0,0), 0.1, 0.1);
    cv::imshow("jpg",jpg);

    cv::waitKey(0);

    RawProcessor.recycle();
    return 0;
}
