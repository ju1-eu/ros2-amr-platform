# Basis-Image: ROS 2 Jazzy (aktuellste Version)
FROM ros:jazzy-ros-base

# 1. System-Tools & ROS-Treiber (Basis)
RUN apt-get update && apt-get install -y \
    usbutils \
    udev \
    iputils-ping \
    python3-pip \
    v4l-utils \
    # Kamera-Treiber (Backup) & Lidar
    ros-jazzy-v4l2-camera \
    ros-jazzy-rplidar-ros \
    ros-jazzy-rmw-cyclonedds-cpp \
    # Build-Tools
    cmake \
    git \
    libtool \
    autoconf \
    && rm -rf /var/lib/apt/lists/*

# 2. HailoRT (Runtime) - Build aus Quellcode (CACHED)
# Wenn Sie diesen Block nicht ändern, nutzt Docker den Cache von vorhin!
WORKDIR /tmp
RUN git clone https://github.com/hailo-ai/hailort.git && \
    cd hailort && \
    git checkout v4.23.0 && \
    cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --config Release && \
    cmake --install build/ && \
    ldconfig && \
    rm -rf /tmp/hailort

# 3. NEU: Offizieller Raspberry Pi Kamera-Treiber (ros2_camera)
# Wir installieren libcamera und bauen den Node, der das RAW-Format versteht.
RUN apt-get update && apt-get install -y \
    libcamera-dev \
    libcamera-apps \
    python3-jinja2 \
    ros-jazzy-camera-info-manager \
    ros-jazzy-image-transport \
    && rm -rf /var/lib/apt/lists/*

# Node klonen
WORKDIR /ros2_ws/src
RUN git clone https://github.com/raspberrypi/ros2_camera.git

# Workspace bauen (Compiling the Camera Node)
WORKDIR /ros2_ws
RUN . /opt/ros/jazzy/setup.sh && colcon build

# 4. Komfort & Setup
# WICHTIG: Beide Setup-Dateien laden!
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
RUN echo "source /ros2_ws/install/setup.bash" >> ~/.bashrc

# 5. Entrypoint
CMD ["bash"]
