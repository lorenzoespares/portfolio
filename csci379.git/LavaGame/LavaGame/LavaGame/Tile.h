//
//  Tile.h
//  LavaGame
//
//  Created by Lorenzo O. Espares on 5/5/14.
//  Copyright (c) 2014 bucknell.edu. All rights reserved.
//
//  This class represents a tile that the user can tap in the game.

#import <Foundation/Foundation.h>

@interface Tile : NSObject

@property (strong, nonatomic) NSString *tiletype;
@property (nonatomic) NSUInteger value;
@property (nonatomic, getter = isFaceUp) BOOL faceUp;


@end
