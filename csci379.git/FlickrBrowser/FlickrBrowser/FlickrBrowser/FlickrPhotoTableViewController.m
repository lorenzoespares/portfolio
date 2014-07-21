//
//  FlickrBrowserViewController.m
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 3/25/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "FlickrPhotoTableViewController.h"

@interface FlickrPhotoTableViewController ()

@end

@implementation FlickrPhotoTableViewController

//
// Sets the array of photos that we will display.  Since the array is changing,
// we need to reload the table.
//
- (void)setPhotos:(NSArray *)photos {
    _photos = photos;
    [self.tableView reloadData];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

#pragma mark - Table view data source
//
// Returns the number of rows in the table.  It is equal to the number of
// entries in our photo array.
//
- (NSInteger)tableView:(UITableView *)tableView
 numberOfRowsInSection:(NSInteger)section
{
    return [self.photos count];
}

//
// Determines the title for a row. This is an abstract method.
//
- (NSString *)titleForRow:(NSUInteger)row {
    return nil;
}

//
// Determines the subtitle for a row.  This is an abstract method.
//
- (NSString *)subtitleForRow:(NSUInteger)row {
    return nil;
}

//
// Configures a cell that will display at a given row in our table.
// This is an abstract method.
//
- (UITableViewCell *)tableView:(UITableView *)tableView
         cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return nil;
}

//
// Abstract method to prepare for segue.
//
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
}

//
// Returns the photo format to use for the photo.  The value can be
// FlickrPhotoFormatSquare (75x75), FlickrPhotoFormatLarge (1024x768), or
// FlickrPhotoFormatOriginal (at least 1024x768).  This is an abstract method.
//
- (FlickrPhotoFormat)photoFormat {
    return 0;
}

@end

