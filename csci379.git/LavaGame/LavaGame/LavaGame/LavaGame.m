//
//  LavaGame.m
//  LavaGame
//
//  Created by Lorenzo O. Espares on 5/5/14.
//  Copyright (c) 2014 bucknell.edu. All rights reserved.
//

#import "LavaGame.h"
#import "LGViewController.h"

@interface LavaGame()
@property (readwrite, nonatomic) NSString *state;
@end

@implementation LavaGame

//
// Initializes the tiles we will be using. If there are not enough tiles,
// return nil.
//
- (instancetype)initWithTileCount:(NSUInteger)count
                        usingPile:(TilePile *)pile{
    self = [super init];
    self.pile = pile;
    self.state = @"continue";
    if (self != nil) {
        _pileoftiles = [[NSMutableArray alloc] init];
        for (NSUInteger i = 0; i < count; i++) {
            Tile* tile = [pile pickTile];
            if (tile != nil)
                _pileoftiles[i] = tile;
            else {
                self = nil;
                break;
            }
        }
    }
    return self;
}

//
// Returns the tile at the specified index. If the index is out of range,
// return nil.
//
- (Tile *)tileAtIndex:(NSUInteger)index {
    return index < [self.pileoftiles count] ? self.pileoftiles[index] : nil;
}

//
// Updates the game state depending on the tile selected. The user wins only
// when all floor tiles (50) have been selected consecutively. Stepping on a
// lava tile results in a loss for the user.
//
- (void)updatewithTileAtIndex:(NSUInteger)index {
    Tile *tile = [self tileAtIndex:index];
    if (tile != nil && (![self.state isEqual:@"gameover"] && ![self.state isEqual:@"win"])) {
        NSLog(@"%@", tile.tiletype);
        if (self.numtiles == self.pile.TileCount){
            self.state = @"win";
        }
        else if ([tile.tiletype  isEqual: @"lava"]) {
            self.state = @"gameover";
        } else if ([tile.tiletype isEqual: @"floor"]){
            self.state = @"continue";
        }
    }
}


@end
