//
//  LGViewController.h
//  LavaGame
//
//  Created by Lorenzo O. Espares on 5/5/14.
//  Copyright (c) 2014 bucknell.edu. All rights reserved.
//
//  This class handles the display of the main game, which shows the user the
//  lava and floor tiles. 

#import <UIKit/UIKit.h>
#import "LavaGame.h"

@interface LGViewController : UIViewController

@property (strong, nonatomic) LavaGame *game;
@property (readwrite, nonatomic) NSInteger currenttile;
- (NSUInteger)startingTileCount;
- (TilePile *)getnewtiles;
- (void)updateCell:(UICollectionViewCell *)cell usingTile:(Tile *)tile;
- (void)startNewGame;

@end
