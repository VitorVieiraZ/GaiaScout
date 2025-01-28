# GeoScout Setup Guide

This guide will help you set up the project for development and deployment on Android and iOS platforms using Qt Creator.

## Installation

### Prerequisites

Before starting, ensure you have the following installed on your system:

- **Qt Creator**
- Supported version: **6.6.3**
- Android or iOS development tools:
  - **For Android**:
    - Android Studio (for SDK, NDK, and platform tools)
    - JDK (Java Development Kit)
    - Gradle
  - **For iOS**:
    - Xcode (ensure command-line tools are installed)

---

### Step-by-Step Installation

1. **Download and Install Qt Creator**
   - Visit the [Qt Downloads page](https://www.qt.io/download) and download Qt Creator.
   - During the installation process, ensure the following components are selected:
     - **Qt version 6.6.3**
     - **Android Kits** (for Android development)
     - **iOS Kits** (for iOS development, macOS required).

2. **Set Up Development Environment**

   #### For Android:
   - Install Android Studio and ensure the following are configured:
     - **SDK**: Configure the Android SDK path in Qt Creator.
     - **NDK**: Use the version compatible with Qt 6.6.3 (usually installed via Android Studio).
     - **JDK**: Make sure Java is installed and added to your system's `PATH`.
     - **Gradle**: Install Gradle and ensure it is correctly configured.

   #### For iOS:
   - Install Xcode from the Mac App Store.
   - Launch Xcode and install additional command-line tools if prompted.
   - Ensure Xcode is correctly set up to sign and build iOS apps.

3. **Open the Project**
   - Clone the repository to your local machine:
     ```bash
     git clone https://github.com/VitorVieiraZ/GaiaScout.git
     cd GaiaScout
     ```
   - Open the project in Qt Creator by selecting the `.pro` file or CMakeLists.txt.

4. **Configure the Kits**
   - In Qt Creator:
     - Go to **Tools > Options > Kits**.
     - Ensure the required kits for Android and/or iOS are properly configured and associated with Qt version **6.6.3**.

5. **Build and Deploy**
   - Select the appropriate kit (e.g., Android or iOS).
   - Click the **Build** button to compile the project.
   - Connect your Android or iOS device to your computer.
   - Click **Run** to deploy and test the application on the device.

---

## Additional Notes

- For Android development, make sure USB debugging is enabled on your device.
- For iOS development, you may need a valid Apple Developer account to sign and deploy applications.
- Always verify your configurations to ensure compatibility with Qt 6.6.3.

For further assistance, refer to the official [Qt Documentation](https://doc.qt.io/).
