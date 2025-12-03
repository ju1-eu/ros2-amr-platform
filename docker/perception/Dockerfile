# Basis-Image: ROS 2 Jazzy (aktuellste Version)
FROM ros:jazzy-ros-base

# 1. System-Tools installieren
# usbutils = lsusb (Hardware-Check)
# v4l-utils = Kamera-Tools
# iputils-ping = Netzwerk-Check
RUN apt-get update && apt-get install -y \
    usbutils \
    iputils-ping \
    python3-pip \
    v4l-utils \
    && rm -rf /var/lib/apt/lists/*

# 2. ROS-Treiber installieren
# Wir laden die offiziellen Pakete für USB-Kameras und den RPLIDAR
RUN apt-get update && apt-get install -y \
    ros-jazzy-v4l2-camera \
    ros-jazzy-rplidar-ros \
    && rm -rf /var/lib/apt/lists/*

# 3. Arbeitsverzeichnis
WORKDIR /ros2_ws

# 4. Komfort: ROS automatisch laden
# Damit wir nicht jedes Mal "source ..." tippen müssen
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc

# 5. Entrypoint
CMD ["bash"]
