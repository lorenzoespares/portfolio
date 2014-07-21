//
//  ImageViewController.m
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 3/25/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "ImageViewController.h"
#import "CacheManager.h"

@interface ImageViewController () <UIScrollViewDelegate>
@property (weak, nonatomic) IBOutlet UIScrollView *scrollView;
@property (strong, nonatomic) UIImageView *imageView;


@end

@implementation ImageViewController

//
// Sets the URL for the image we are displaying.  Since the URL is changing,
// the image will change too.
//
- (void)setImageURL:(NSURL *)imageURL {
    _imageURL = imageURL;
    [self resetImage];
}

//
// Replaces the current image we are displaying with the one pointed to by the
// image URL.  If there is no scroll view, do nothing. Also takes care of the
// newtork activity indicator to notify the user when the app is doing
// something. The photo is retrieved from the cache if it exists in the cache,
// otherwise do work to fetch the image.
//
- (void)resetImage {
    if (self.scrollView == nil)
        return;
    self.scrollView.contentSize = CGSizeZero;
    self.imageView.image = nil;
    NSURL *imageURL = self.imageURL;
    NSData *imageData = [[CacheManager sharedInstance] getCacheForKey:(NSString *)imageURL];
    if (imageData != nil) {
        UIImage *image = [[UIImage alloc] initWithData:imageData];
        self.scrollView.zoomScale = 1.0;
        self.imageView.image = image;
        self.imageView.frame = CGRectMake(0.0, 0.0, image.size.width, image.size.height);
        self.scrollView.contentSize = self.imageView.frame.size;
        self.spinner.hidesWhenStopped = YES;
        return;
    } else {
    [self viewDidLayoutSubviews];
    [self.spinner startAnimating];
    self.spinner.hidesWhenStopped = YES;
    dispatch_queue_t imageFetchQueue = dispatch_queue_create("image fetcher", DISPATCH_QUEUE_SERIAL);
    dispatch_async(imageFetchQueue, ^{
        [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
        //[NSThread sleepForTimeInterval:2.0];
        NSData *imageData = [[NSData alloc] initWithContentsOfURL:self.imageURL];
        [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
        UIImage *image = [[UIImage alloc] initWithData:imageData];
        if (self.imageURL == imageURL){
            dispatch_async(dispatch_get_main_queue(), ^{
                if (image != nil) {
                    self.scrollView.zoomScale = 1.0;
                    self.imageView.image = image;
                    self.imageView.frame = CGRectMake(0.0, 0.0, image.size.width, image.size.height);
                    self.scrollView.contentSize = self.imageView.frame.size;

                }
                [self.spinner stopAnimating];
            });
        }
    });
    }
}

//
// Allows the scroll view to be resized to fit the current dimensions of
// the screen
//
- (void)FillScreenwithScrollView
{
    self.scrollView.frame = CGRectMake(0, 0, self.view.bounds.size.width,
                                            self.view.bounds.size.height);
}

//
// Positions the spinner so that it is in the center of the view.
//
- (void)viewDidLayoutSubviews {
    self.spinner.center = self.view.center;
}

//
// Initializes the view.  Creates the image view and adds it to the scrollview.
// If there is an image waiting to be displayed, it displays it. Automatically
// fits the image to the scroll view.
//
- (void)viewDidLoad {
    [super viewDidLoad];
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:
            @selector(detectOrientation)
            name:UIDeviceOrientationDidChangeNotification object:nil];
    self.imageView = [[UIImageView alloc] initWithFrame:CGRectZero];
    [self.scrollView addSubview:self.imageView];
    self.scrollView.minimumZoomScale = 0.2;
    self.scrollView.maximumZoomScale = 2.0;
    self.scrollView.delegate = self;
    [self resetImage];
}

//
// Makes the frame of the image fit into the scroll view. This method is called
// when the device sends an orientation notification and promptly
// calls the proper if statement depending on the orientation of the device.
//
-(void) detectOrientation {
    [self resetImage];
    [self FillScreenwithScrollView];
    if (([[UIDevice currentDevice] orientation] == UIDeviceOrientationLandscapeLeft) ||
        ([[UIDevice currentDevice] orientation] == UIDeviceOrientationLandscapeRight)) {
        self.imageView.frame = CGRectMake(0, 0, self.imageView.image.size.width,
                                          self.imageView.image.size.height);
        self.scrollView.contentSize = self.imageView.frame.size;
    }
}

//
// Tells the scroll view which view to use for scrolling.
//
- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView {
    return self.imageView;
}

@end

