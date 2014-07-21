//
//  ImageViewController.h
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 3/25/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  This class is the container for the imageView and displays the images as
//  directed by segues from the tableViewControllers.

#import <UIKit/UIKit.h>

@interface ImageViewController : UIViewController

@property (nonatomic, strong) NSURL *imageURL;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *spinner;


@end
