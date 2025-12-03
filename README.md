# ros2-amr-platform - Autonomous Mobile Robot
Architektur nach Bloch-Standard:
- **Ebene 1 (Firmware):** ESP32 Micro-ROS (Motor Control)
- **Ebene 2 (Perception):** Docker Container für LiDAR & Hailo AI
- **Ebene 3 (Navigation):** Docker Container für Nav2 & SLAM
