//
//  MainTagsViewController.h
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 3/25/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  This class controls what to display in the table view labeled "Tags". The
//  tags are displayed in the table view and segues into the
//  NewFlickrBrowserViewController to display the photos associated with each
//  tag.
//

#import "FlickrPhotoTableViewController.h"

@interface MainTagsViewController : FlickrPhotoTableViewController

@property (strong, nonatomic) NSMutableDictionary *variabledict;

@end
