//
//  NewFlickrBrowserViewControllerPad.m
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 4/7/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "NewFlickrBrowserViewControllerPad.h"
#import "FlickrFetcher.h"

@interface NewFlickrBrowserViewControllerPad ()

@end

@implementation NewFlickrBrowserViewControllerPad

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
// Returns the photo format to use for the photo.  The value can be
// FlickrPhotoFormatSquare (75x75), FlickrPhotoFormatLarge (1024x768), or
// FlickrPhotoFormatOriginal (at least 1024x768).
//
- (FlickrPhotoFormat)photoFormat {
    return FlickrPhotoFormatOriginal;
}

@end
