//
//  MainTagsViewController.m
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 3/25/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "MainTagsViewController.h"
#import "NewFlickrBrowserViewController.h"

#import "FlickrFetcher.h"

@interface MainTagsViewController ()
@property (strong, nonatomic) NSMutableDictionary *mytags;
@property (strong, nonatomic) NSArray *separatedtags;
@property (strong, nonatomic) NSMutableArray *mytagkeys;
@property (strong, nonatomic) UIRefreshControl *refreshControl;

@end

@implementation MainTagsViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
    self.photos = [FlickrFetcher bucknellPhotos];

    // Do any additional setup after loading the view.
    
    [self retrievetags];
}

//
//  Accesses each photo and retrieves the tags associated with that photo. The
//  tags are originally one long string, so each tag is extracted using the
//  componentsSeparatedByString method. Objects are stored as key = tag,
//  value = tag occurence in self.mytags, and objects are stored as key = tag,
//  value = photos associated with tag in self.variabledict.
- (void)retrievetags{
    _mytags = [[NSMutableDictionary alloc] init];
    _mytagkeys = [[NSMutableArray alloc] init];
    _variabledict = [[NSMutableDictionary alloc] init];
    
    for (int i = 0; i < self.photos.count; i++) {
        NSArray *variablephotos = [[NSArray alloc] init];
        variablephotos = [variablephotos arrayByAddingObject:self.photos[i]];
        NSString *phototags = [self.photos[i][FLICKR_TAGS] description];
        _separatedtags = [phototags componentsSeparatedByString:@" "];
        for (int j = 0; j < _separatedtags.count; j++) {
            if ([_mytags objectForKey:_separatedtags[j]] != nil) {
                NSNumber *increment = [_mytags objectForKey:_separatedtags[j]];
                increment = [NSNumber numberWithInt:[increment intValue]+1];
                [_mytags setValue:increment forKey:_separatedtags[j]];
                NSArray *appendphotos = [_variabledict objectForKey:_separatedtags[j]];
                NSMutableArray *newphotos = [[NSMutableArray alloc] init];
                [newphotos addObjectsFromArray:appendphotos];
                [newphotos addObjectsFromArray:variablephotos];
                [_variabledict setValue:newphotos forKey:_separatedtags[j]];
            } else {
                [_mytags setValue:[NSNumber numberWithInt:1] forKey:_separatedtags[j]];
                [_variabledict setValue:variablephotos forKey:_separatedtags[j]];
            }
            if (![self.mytagkeys containsObject:_separatedtags[j]])
                [_mytagkeys addObject:_separatedtags[j]];
        }
    }
    [_mytagkeys sortUsingComparator:^NSComparisonResult(NSString *string1, NSString *string2) {
        return [string1.description caseInsensitiveCompare:string2.description];
    }];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//
// Calls the commands in the method when the screen is refreshing.
//
- (IBAction)refresh{
    [self.refreshControl beginRefreshing];
    dispatch_queue_t queue = dispatch_queue_create("edu.bucknell.tableView", DISPATCH_QUEUE_SERIAL);
    dispatch_async(queue, ^{
        [self retrievetags];
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.tableView reloadData];
            [self.refreshControl endRefreshing];
        });
    });
}


#pragma mark - Table view data source
//
// Determines the title for a row.  This is the tag that is associated with a
// photo.
//
- (NSString *)titleForRow:(NSUInteger)row {
    return self.mytagkeys[row];
}

//
// Determines the subtitle for a row.  This is the number of occurences of the
// tag in the array of photos.
//
- (NSString *)subtitleForRow:(NSUInteger)row {
    NSString * retval = [[self.mytags objectForKey:self.mytagkeys[row]] stringValue];
    return retval;
}

//
// Configures a cell that will display at a given row in our table.
//
- (UITableViewCell *)tableView:(UITableView *)tableView
         cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Tag Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier
                                                            forIndexPath:indexPath];
    cell.textLabel.text = [self titleForRow:indexPath.row];
    cell.detailTextLabel.text = [self subtitleForRow:indexPath.row];
    
    return cell;
}

#pragma mark - Navigation

//
// Prepares to segue to the ImageViewController.  Do some introspection that's
// probably not necessary, but it shows some capabilities of Objective-C.  Sets
// the title of the new view controller too.
//
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    NSIndexPath *indexPath = [self.tableView indexPathForCell:sender];
    NewFlickrBrowserViewController *listwithTags = segue.destinationViewController;
    [listwithTags setPhotos:[_variabledict objectForKey:[self titleForRow:indexPath.row]]];
    [listwithTags.tableView reloadData];
}

@end
