//
//  ThreeCardMatchGame.h
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/19/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  A game that is a subclass of CardMatchingGame. This class takes care of
//  three card matching.

#import "CardMatchingGame.h"

@interface ThreeCardMatchGame : CardMatchingGame

- (void)compareThreeCards: (Card *)card withtwootherCards:
                        (NSArray *)otherCards;
- (void)flipCardAtIndex:(NSUInteger)index;
- (void)setFlipCost:(NSUInteger)cost;

@property (strong, nonatomic) NSMutableArray *othertwocards;

@end
