//
//  TilePile.m
//  LavaGame
//
//  Created by Lorenzo O. Espares on 5/5/14.
//  Copyright (c) 2014 bucknell.edu. All rights reserved.
//

#import "TilePile.h"
#import "Tile.h"

@interface TilePile()
@property (strong, nonatomic)NSMutableArray *pile;
@end

@implementation TilePile

//
// Initializes the pile of tiles so that there are 212 tiles in the pile
//
- (instancetype)init {
    self = [super init];
    if (self != nil) {
        _pile = [[NSMutableArray alloc] init];
        for (NSUInteger rank = 1; rank <= [self TileCount]; rank++) {
            NSUInteger number = (arc4random()%4)+1; //Generates Number from 1-4
            for (NSUInteger count = 1; count <= 4; count++) {
                Tile *tile = [[Tile alloc] init];
                if(count == number) {
                    tile.tiletype = @"floor";
                } else {
                    tile.tiletype = @"lava";
                }
                tile.value = rank;
                [self addTile:tile atTop:YES];
            }
        }
        for (NSUInteger finish = 1; finish <= 12; finish++){
            Tile *tile = [[Tile alloc] init];
            tile.tiletype = @"end";
            [self addTile:tile atTop:YES];
        }
    }
    return self;
}

//
// Returns the number of floor tiles in the game.
//
- (NSUInteger)TileCount {
    return 50;
}


//
// Adds a tile to the pile. If atTop is YES, add the tile to the top of the
// pile. Otherwise, add it to the bottom.
//
- (void)addTile:(Tile *)tile atTop:(BOOL)atTop {
    if (tile == nil)
        return;
    if (atTop)
        [self.pile insertObject:tile atIndex:0];
    else
        [self.pile addObject:tile];
}

//
// Draws the top tile from the pile. If the pile is empty, return nil.
//
- (Tile *)pickTile {
    Tile *toptile = nil;
    if ([self.pile count] != 0) {
        toptile = self.pile[0];
        [self.pile removeObjectAtIndex:0];
    }
    return toptile;
}

@end
