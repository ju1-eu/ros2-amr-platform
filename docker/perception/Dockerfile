# Inhalt aus 03-Layer2-Perception.md
FROM ros:jazzy-ros-base

# 1. System-Tools & ROS-Treiber
RUN apt-get update && apt-get install -y \
    usbutils \
    iputils-ping \
    python3-pip \
    v4l-utils \
    ros-jazzy-v4l2-camera \
    ros-jazzy-rplidar-ros \
    ros-jazzy-rmw-cyclonedds-cpp \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /ros2_ws

# Komfort: ROS automatisch laden
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc

CMD ["bash"]
