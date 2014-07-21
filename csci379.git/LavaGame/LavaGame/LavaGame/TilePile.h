//
//  TilePile.h
//  LavaGame
//
//  Created by Lorenzo O. Espares on 5/5/14.
//  Copyright (c) 2014 bucknell.edu. All rights reserved.
//
//  A pile of tiles which the game displays to the user.

#import <Foundation/Foundation.h>
#import "Tile.h"

@interface TilePile : NSObject

- (void)addTile:(Tile *)tile atTop:(BOOL)atTop;
- (Tile *)pickTile;
- (NSUInteger)TileCount;


@end
