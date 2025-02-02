#ifndef FIRESMOKEDETECT_H
#define FIRESMOKEDETECT_H

#include "BaseModel.h"
#include <vector>
#include <opencv2/core.hpp> // 确保包含OpenCV核心模块

// 结构体定义，用于存储火焰和烟雾检测结果
struct FireSmokeDetection {
    int id;                          // 检测到的对象 ID（例如火焰或烟雾的类别 ID）
    float confidence;                // 置信度
    cv::Rect_<float> box;            // 检测框，使用浮点数表示坐标
};

// 火焰烟雾检测结果结构体
struct FireSmokeDetResult {
    std::vector<FireSmokeDetection> detections;   // 火焰烟雾检测结果列表
    bool ready_; // 标志检测结果是否准备好

    // 默认构造函数
    FireSmokeDetResult() : ready_(false) {} // 初始化 ready 为 false

    // 复制构造函数
    FireSmokeDetResult(const FireSmokeDetResult& other)
        : detections(other.detections), ready_(other.ready_) {}

    // 赋值操作符
    FireSmokeDetResult& operator=(const FireSmokeDetResult& other) {
        if (this != &other) { // 防止自我赋值
            detections = other.detections; // 深拷贝 detections
            ready_ = other.ready_; // 复制 ready
        }
        return *this;
    }
};


// 火焰与烟雾检测类，继承自BaseModel
class FireSmokeDet : public BaseModel<FireSmokeDetResult> {
public:
    // 默认构造函数
    FireSmokeDet();

    // 初始化模型
    int init(const std::string& modelPath) override;

    // 获取RKNN上下文
    rknn_context* get_rknn_context() override;

    // 模型推理
    int infer(const cv::Mat& inputData) override;

    // 获取检测结果
    FireSmokeDetResult getResult() const;

    // 默认析构函数
    ~FireSmokeDet();

private:
    FireSmokeDetResult result_; // 存储检测结果
};

#endif // FIRESMOKEDETECT_H
