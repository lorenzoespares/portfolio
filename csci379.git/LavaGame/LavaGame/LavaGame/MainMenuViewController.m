//
//  MainMenuViewController.m
//  LavaGame
//
//  Created by Lorenzo O. Espares on 5/7/14.
//  Copyright (c) 2014 bucknell.edu. All rights reserved.
//

#import "MainMenuViewController.h"
#import "LGViewController.h"
#import "StatusView.h"

@interface MainMenuViewController ()
@property (weak, nonatomic) IBOutlet UIView *statusview;
@property (weak, nonatomic) IBOutlet UIButton *play;
@property (strong, nonatomic) UINavigationController *parent;
@end

@implementation MainMenuViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    StatusView *newview = (StatusView *)self.statusview;
    newview.status = @"main.png";
    
    self.parent = (UINavigationController *)self.parentViewController;
    self.parent.navigationBar.hidden = YES;
    
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
