#!/bin/bash
ORIG_TERM=$(stty -g)
TMP_CAM_LOG=$(mktemp /tmp/cam_stream_log.XXXXXX)
PIPE=/tmp/cam_pipe
# 标记：是否已经执行过清理，防止重复打印
CLEANUP_DONE=0

cleanup() {
    # 已经清理过，直接退出函数，不再重复执行
    if [ "$CLEANUP_DONE" -eq 1 ]; then
        return
    fi
    CLEANUP_DONE=1

    exec >/dev/tty 2>/dev/tty
    stty "$ORIG_TERM"
    echo -e "\n收到停止信号，正在关闭推流进程..."

    if CAM_PID=$(pidof rpicam-vid); then
        kill -SIGINT "$CAM_PID" 2>/dev/null
        wait "$CAM_PID" 2>/dev/null
    fi

    if [ -n "$FFMPEG_PID" ]; then
        kill "$FFMPEG_PID" 2>/dev/null
        wait "$FFMPEG_PID" 2>/dev/null
    fi

    pkill -f rpicam-vid 2>/dev/null
    pkill -f ffmpeg 2>/dev/null
    rm -f "$TMP_CAM_LOG" "$PIPE"
    echo "推流已全部停止，脚本退出"
}

# 捕获信号，去掉多余重复触发隐患
trap cleanup SIGINT SIGTERM EXIT

rm -f "$PIPE"
mkfifo "$PIPE"

# 先启动相机写入管道
rpicam-vid \
-t 0 \
--preview 50,50,800,600 \
--rotation 180 \
--width 1280 --height 720 \
--framerate 20 \
--mode 1280:720:25 \
--codec h264 \
--verbose 0 \
-o "$PIPE" 2>"$TMP_CAM_LOG" &
CAM_PID=$!

sleep 0.5

# 后启动ffmpeg读取管道
ffmpeg \
-hide_banner -loglevel error \
-probesize 50M \
-analyzeduration 30000000 \
-f h264 \
-i "$PIPE" \
-c:v copy \
-f rtsp \
rtsp://127.0.0.1:8554/cam 2>/dev/null &
FFMPEG_PID=$!

# 等待相机进程结束
wait "$CAM_PID"

# 去掉脚本末尾手动调用cleanup，EXIT trap会自动处理
