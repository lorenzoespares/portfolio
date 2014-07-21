//
//  ImageViewControllerPad.m
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 4/7/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "ImageViewControllerPad.h"

@interface ImageViewControllerPad ()

@end

@implementation ImageViewControllerPad

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//
// Positions the activity indicator so that it is centered within the detail
// view controller.
//
- (void)viewDidLayoutSubviews {
    UIViewController *detailViewController = self.splitViewController.viewControllers[1];
    CGSize detailSize = detailViewController.view.frame.size;
    self.spinner.center = CGPointMake(detailSize.width / 2.0, detailSize.height / 2.0);
}
@end
