# Basis-Image: ROS 2 Jazzy (aktuellste Version)
FROM ros:jazzy-ros-base

# 1. System-Tools & ROS-Treiber installieren
# usbutils = lsusb
# ros-jazzy-rmw-cyclonedds-cpp = Kommunikationstreiber
RUN apt-get update && apt-get install -y \
    usbutils \
    iputils-ping \
    python3-pip \
    v4l-utils \
    ros-jazzy-v4l2-camera \
    ros-jazzy-rplidar-ros \
    ros-jazzy-rmw-cyclonedds-cpp \
    # --- NEU: Build-Tools für HailoRT ---
    cmake \
    git \
    libtool \
    autoconf \
    && rm -rf /var/lib/apt/lists/*

# 2. HailoRT (Runtime) aus Quellcode bauen
# Wir bauen die Software direkt im Container, um Versionskonflikte zu vermeiden.
WORKDIR /tmp
RUN git clone https://github.com/hailo-ai/hailort.git && \
    cd hailort && \
    cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --config Release && \
    cmake --install build/ && \
    ldconfig && \
    rm -rf /tmp/hailort

# 3. Arbeitsverzeichnis für ROS
WORKDIR /ros2_ws

# 4. Komfort: ROS automatisch laden
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc

# 5. Entrypoint
CMD ["bash"]
