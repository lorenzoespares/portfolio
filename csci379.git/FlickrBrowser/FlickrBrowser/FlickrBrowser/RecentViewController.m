//
//  RecentViewController.m
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 3/26/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "RecentViewController.h"
#import "RecentPhotos.h"
#import "CacheManager.h"

@interface RecentViewController ()

@end

@implementation RecentViewController

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
// Sets photos to the array of photos in the RecentPhotos class. This method
// is called whenever the RecentViewController will appear, ie. whenever the
// "Most Recent" tab is selected.
- (void) viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.photos = [RecentPhotos getRecentPhotos];
    [self.tableView reloadData];
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
    static NSString *CellIdentifier = @"RecentPhoto";
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
// Prepares to segue to the ImageViewController. Updates the table view with the
// most recent picture viewed in real time, in a separate thread.
// Also adds the selected photo to cache, to enable faster retrieval of photos.
// The tableview is then updated in the main thread to reflect changes in the
// array of recent photos.
//
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    NSIndexPath *indexPath = [self.tableView indexPathForCell:sender];
    ImageViewController *imageViewController = segue.destinationViewController;
    NSURL *url = [FlickrFetcher urlForPhoto:self.photos[indexPath.row]
                                     format:[self photoFormat]];
    [imageViewController setImageURL:url];
    [imageViewController setTitle:[self titleForRow:indexPath.row]];
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^{
        [RecentPhotos addPhoto:self.photos[indexPath.row]];
        self.photos = [RecentPhotos getRecentPhotos];
        NSPurgeableData *imageData;
        imageData = [[NSPurgeableData alloc] initWithContentsOfURL:url];
        [[CacheManager sharedInstance] setCache:imageData forKey:(NSString *)url];
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.tableView reloadData];
        });
    });
}

@end
