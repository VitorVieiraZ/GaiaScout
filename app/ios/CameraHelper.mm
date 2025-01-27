#include <UIKit/UIKit.h>
#include <CoreLocation/CoreLocation.h>
#include <CoreMotion/CoreMotion.h>
#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "../cpp/cameracontroller.h"

// Declare a global instance of CLLocationManager and CMMotionManager
CLLocationManager* locationManager = nil;
CMMotionManager* motionManager = nil;

// Objective-C++ interface for CameraController
@interface CameraControllerDelegate : NSObject <UINavigationControllerDelegate, UIImagePickerControllerDelegate>
@property (nonatomic, assign) CameraController* controller;
@end

@implementation CameraControllerDelegate

- (void)imagePickerController:(UIImagePickerController*)picker didFinishPickingMediaWithInfo:(NSDictionary*)info {
    // Get the captured image
    UIImage* image = [info objectForKey:UIImagePickerControllerOriginalImage];
    if (image) {
        // Save the image to a temporary file
        NSData* imageData = UIImageJPEGRepresentation(image, 1.0); // Save as JPEG
        NSString* tempDir = NSTemporaryDirectory();
        NSString* fileName = [NSString stringWithFormat:@"photo_%@.jpg", [[NSDate date] description]];
        NSString* filePath = [tempDir stringByAppendingPathComponent:fileName];
        [imageData writeToFile:filePath atomically:YES];

        // Gather additional attributes (direction, acceleration, etc.)
        CLLocation* currentLocation = locationManager.location;
        double latitude = currentLocation ? currentLocation.coordinate.latitude : 0.0;
        double longitude = currentLocation ? currentLocation.coordinate.longitude : 0.0;
        double direction = currentLocation ? currentLocation.course : 0.0; // Course is the direction in degrees

        // Get acceleration data
        CMAcceleration acceleration = {0, 0, 0};
        if (motionManager.accelerometerAvailable && motionManager.accelerometerActive) {
            acceleration = motionManager.accelerometerData.acceleration;
        }

        // Create a metadata dictionary
        NSDictionary* metadata = @{
            @"latitude": @(latitude),
            @"longitude": @(longitude),
            @"direction": @(direction),
            @"accelerationX": @(acceleration.x),
            @"accelerationY": @(acceleration.y),
            @"accelerationZ": @(acceleration.z)
        };

        // Convert metadata to a JSON string
        NSData* jsonData = [NSJSONSerialization dataWithJSONObject:metadata options:0 error:nil];
        NSString* jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];

        // Emit the photoSaved signal with the file path and metadata
        QString qFilePath = QString::fromNSString(filePath);
        QString qMetadata = QString::fromNSString(jsonString);
        emit self.controller->photoSaved(qFilePath, QJsonDocument::fromJson(qMetadata.toUtf8()).object());

        // Dismiss the camera view
        [picker dismissViewControllerAnimated:YES completion:nil];
    } else {
        qDebug() << "Failed to capture image.";
    }
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController*)picker {
    // Dismiss the camera view
    [picker dismissViewControllerAnimated:YES completion:nil];

    // Emit the photoSelected signal (if needed)
    emit self.controller->photoSelected();
}

@end

// Function to open the native camera and capture a photo
void openNativeCameraIOS(CameraController* controller) {
    // Initialize location and motion managers if they don't exist
    if (!locationManager) {
        locationManager = [[CLLocationManager alloc] init];
        [locationManager requestWhenInUseAuthorization]; // Request location permissions
    }

    if (!motionManager) {
        motionManager = [[CMMotionManager alloc] init];
    }

    // Check if the camera is available
    if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]) {
        UIImagePickerController* picker = [[UIImagePickerController alloc] init];
        picker.sourceType = UIImagePickerControllerSourceTypeCamera;

        // Create a delegate for the picker
        CameraControllerDelegate* delegate = [[CameraControllerDelegate alloc] init];
        delegate.controller = controller;
        picker.delegate = delegate;

        // Present the camera view
        UIWindow* window = [[UIApplication sharedApplication] keyWindow];
        UIViewController* rootViewController = window.rootViewController;
        if (rootViewController) {
            [rootViewController presentViewController:picker animated:YES completion:nil];
        } else {
            qDebug() << "Failed to find root view controller for camera.";
        }
    } else {
        qDebug() << "Camera is not available on this device.";
    }
}