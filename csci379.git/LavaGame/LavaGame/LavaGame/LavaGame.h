//
//  LavaGame.h
//  LavaGame
//
//  Created by Lorenzo O. Espares on 5/5/14.
//  Copyright (c) 2014 bucknell.edu. All rights reserved.
//
//  This class contains the logic of the game, where stepping on floor tiles is
//  safe and stepping in lava results in death.

#import <Foundation/Foundation.h>
#import "Tile.h"
#import "TilePile.h"

@interface LavaGame : NSObject
- (instancetype)initWithTileCount:(NSUInteger)count
                        usingPile:(TilePile *)pile;
- (Tile *)tileAtIndex:(NSUInteger)index;
- (void)updatewithTileAtIndex:(NSUInteger)index;


@property (readonly, nonatomic) NSString *state;
@property (readwrite, nonatomic) NSMutableArray *pileoftiles;
@property (strong, nonatomic) TilePile *pile;
@property (readwrite, nonatomic) NSInteger numtiles;


@end
