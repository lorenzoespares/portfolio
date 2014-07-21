//
//  StatusView.h
//  LavaGame
//
//  Created by Lorenzo O. Espares on 5/6/14.
//  Copyright (c) 2014 bucknell.edu. All rights reserved.
//
//  A UIView that displays the status of the game, whether the user has won or
//  lost.

#import <UIKit/UIKit.h>

@interface StatusView : UIView

@property (strong, nonatomic) NSString *status;

@end
