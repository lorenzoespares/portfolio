//
//  MainTagsViewControllerPad.m
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 4/7/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "MainTagsViewControllerPad.h"
#import "NewFlickrBrowserViewControllerPad.h"

#import "FlickrFetcher.h"

@interface MainTagsViewControllerPad () <UISplitViewControllerDelegate>

@end

@implementation MainTagsViewControllerPad

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
// Initializes the controller after it has been created from the storyboard.
//
- (void)awakeFromNib {
    self.splitViewController.delegate = self;
    [super awakeFromNib];
}

//
// Asks the delegate if split view controller should hide the master view
// controller when in the given orientation.  We don't ever want to hide the
// master view controller.
//
- (BOOL)splitViewController:(UISplitViewController *)splitViewController
   shouldHideViewController:(UIViewController *)viewController
              inOrientation:(UIInterfaceOrientation)orientation
{
    return NO;
}

//
// Prepares to segue to the ImageViewController.  Do some introspection that's
// probably not necessary, but it shows some capabilities of Objective-C.  Sets
// the title of the new view controller too.
//
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    NSIndexPath *indexPath = [self.tableView indexPathForCell:sender];
    NewFlickrBrowserViewControllerPad *listwithTags = segue.destinationViewController;
    [listwithTags setPhotos:[self.variabledict objectForKey:[self titleForRow:indexPath.row]]];
    [listwithTags.tableView reloadData];
}

@end
