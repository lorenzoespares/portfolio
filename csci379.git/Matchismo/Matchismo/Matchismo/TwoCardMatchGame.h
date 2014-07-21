//
//  TwoCardMatchGame.h
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/19/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  A game that is a subclass of CardMatchingGame. This class takes care of
//  two card matching.

#import "CardMatchingGame.h"

@interface TwoCardMatchGame : CardMatchingGame

- (void)flipCardAtIndex:(NSUInteger)index;


@end
