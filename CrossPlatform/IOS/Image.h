//
//  Image
//  GetSocial
//
//  Created by Tuan
//
//
#import <UIKit/UIKit.h>
@interface Image :UIViewController <UIImagePickerControllerDelegate,UINavigationControllerDelegate>{
    UIImagePickerController *myPicker;
    UIViewController *currentModalViewController;
    UIImageView *imageView;
}
-(void)openImage;

@end

@interface NonRotatingUIImagePickerController : UIImagePickerController
@end