//
//  FlickrBrowserViewController.h
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 3/25/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  This class controls what to display in our table view controllers. This is
//  the parent class of the other view controllers. This is an abstract class.

#import <UIKit/UIKit.h>
#import "ImageViewController.h"
#import "FlickrFetcher.h"



@interface FlickrPhotoTableViewController : UITableViewController

@property (nonatomic, strong) NSArray *photos;

- (NSString *)titleForRow:(NSUInteger)row;
- (NSString *)subtitleForRow:(NSUInteger)row;
- (FlickrPhotoFormat)photoFormat;

@end
