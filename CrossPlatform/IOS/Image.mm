//
//  Photo
//  GetSocial
//
//  Created by Tuan on 24/03/13.
//
//
#import "Image.h"

@implementation NonRotatingUIImagePickerController
- (BOOL)shouldAutorotate
{
    return YES;
}
@end
@implementation Image
-(void)openImage
{
    myPicker = [[NonRotatingUIImagePickerController alloc] init];
    myPicker.delegate=self;
    myPicker.sourceType=UIImagePickerControllerSourceTypeCamera;
    
    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    currentModalViewController = [UIViewController alloc];
    [window addSubview:currentModalViewController.view];
    [currentModalViewController presentViewController:myPicker animated:true completion:^{}];
    
}
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info {
    self->myPicker = picker;
    [picker dismissModalViewControllerAnimated:YES];
    imageView.image= [info objectForKey:@"UIImagePickerControllerOriginalImage"];
    NSData *webData = UIImagePNGRepresentation(imageView.image);
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *localFilePath = [documentsDirectory stringByAppendingPathComponent:@"avatar.png"];
    [webData writeToFile:localFilePath atomically:YES];
    NSLog(@"localFilePath.%@",localFilePath);
    
}

-(void)imagePickerControllerDidCancel:(UIImagePickerController *) Picker {
    
    [currentModalViewController dismissViewControllerAnimated:true completion:^{}];
    [currentModalViewController.view.superview removeFromSuperview];
    [currentModalViewController release];
   // [self->myPicker release];
    
}
@end
