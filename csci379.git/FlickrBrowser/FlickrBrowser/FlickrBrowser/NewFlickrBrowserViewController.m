//
//  NewFlickrBrowserViewController.m
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 3/25/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "NewFlickrBrowserViewController.h"
#import "MainTagsViewController.h"
#import "RecentPhotos.h"
#import "CacheManager.h"

@interface NewFlickrBrowserViewController ()

@end

@implementation NewFlickrBrowserViewController


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

#pragma mark - Table view data source
//
// Determines the title for a row.  This is just the title for a picture.
// Note that if there is no title for a photo, the result is an NSNull object.
// Sending it description gives @"<null>", a string.
//
- (NSString *)titleForRow:(NSUInteger)row {
    return [self.photos[row][FLICKR_PHOTO_TITLE] description];
}

//
// Determines the subtitle for a row.  This is just the owner of a picture.
// Note that if there is no title for a photo, the result is an NSNull object.
// Sending it description gives @"<null>", a string.
//
- (NSString *)subtitleForRow:(NSUInteger)row {
    return [self.photos[row] valueForKeyPath:FLICKR_PHOTO_DESCRIPTION];
}

//
// Configures a cell that will display at a given row in our table.
//
- (UITableViewCell *)tableView:(UITableView *)tableView
         cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Flickr Photo";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier
                                                            forIndexPath:indexPath];
    cell.textLabel.text = [self titleForRow:indexPath.row];
    cell.detailTextLabel.text = [self subtitleForRow:indexPath.row];
    
    return cell;
}

//
// Returns the photo format to use for the photo.  The value can be
// FlickrPhotoFormatSquare (75x75), FlickrPhotoFormatLarge (1024x768), or
// FlickrPhotoFormatOriginal (at least 1024x768).
//
- (FlickrPhotoFormat)photoFormat {
    return FlickrPhotoFormatLarge;
}

#pragma mark - Navigation

//
// Prepares to segue to the ImageViewController. Adds the photo to recently
// viewed photos and adds it to cache.
//
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {

    NSIndexPath *indexPath = [self.tableView indexPathForCell:sender];
    ImageViewController *imageViewController = segue.destinationViewController;
    NSURL *url = [FlickrFetcher urlForPhoto:self.photos[indexPath.row]
                                     format:[self photoFormat]];
    
    [imageViewController setTitle:[self titleForRow:indexPath.row]];
    [imageViewController setTitle:[self titleForRow:indexPath.row]];
    [RecentPhotos addPhoto:self.photos[indexPath.row]];
    
    [imageViewController setImageURL:url];
    
    NSPurgeableData *imageData;
    imageData = [[NSPurgeableData alloc] initWithContentsOfURL:url];
    [[CacheManager sharedInstance] setCache:imageData forKey:(NSString *)url];
}



@end
