#import <UIKit/UIKit.h>
#include "../cpp/shareutils.h"

@interface IOSShareUtils : NSObject
+ (void)shareFile:(NSString *)filePath;
@end

@implementation IOSShareUtils
+ (void)shareFile:(NSString *)filePath {
    NSURL *fileURL = [NSURL fileURLWithPath:filePath];
    if (!fileURL) {
        NSLog(@"Failed to create file URL for path: %@", filePath);
        return;
    }

    UIViewController *rootViewController = [[[UIApplication sharedApplication] keyWindow] rootViewController];
    if (!rootViewController) {
        NSLog(@"Failed to get root view controller.");
        return;
    }

    UIActivityViewController *activityViewController = [[UIActivityViewController alloc] initWithActivityItems:@[fileURL] applicationActivities:nil];
    if (!activityViewController) {
        NSLog(@"Failed to create UIActivityViewController.");
        return;
    }

    [rootViewController presentViewController:activityViewController animated:YES completion:nil];
}
@end

// Define the iOS-specific function
void shareFileIOS(const QString &filePath) {
    [IOSShareUtils shareFile:filePath.toNSString()];
}