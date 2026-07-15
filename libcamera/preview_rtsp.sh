#!/bin/bash
# preview_rtsp.sh - 树莓派实时视频推流脚本

echo "启动 MediaMTX..."
mediamtx &

# 等待 MediaMTX 启动
sleep 3

echo "启动摄像头实时推流..."

# 使用管道将 rpicam-vid 的输出直接传给 ffmpeg
rpicam-vid \
    --width 1920 \
    --height 1080 \
    --framerate 30 \
    --codec h264 \
    --profile main \
    --level 4.2 \
    --bitrate 5000000 \
    --timeout 0 \
    --output - | ffmpeg \
        -i pipe:0 \
        -c:v copy \
        -f rtsp \
        -rtsp_transport tcp \
        "rtsp://localhost:8554/cam"

# 如果喜欢更低的延迟/分辨率，可以使用这个配置：
# rpicam-vid \
#     --width 640 \
#     --height 480 \
#     --framerate 30 \
#     --codec h264 \
#     --profile baseline \
#     --bitrate 2000000 \
#     --timeout 0 \
#     --output - | ffmpeg \
#         -i pipe:0 \
#         -c:v copy \
#         -f rtsp \
#         -rtsp_transport tcp \
#         "rtsp://localhost:8554/cam"
