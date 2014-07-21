//
//  2CardMatchingGame.h
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/19/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "CardMatchingGame.h"

@interface _CardMatchingGame : CardMatchingGame

- (void)flipCardAtIndex:(NSUInteger)index;
- (Card *)cardAtIndex:(NSUInteger)index;

@end
