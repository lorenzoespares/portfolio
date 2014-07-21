//
//  SetMatchingGame.h
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/19/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  A game that is a subclass of three CardMatchingGame. This class takes care
//  of set card matching.

#import "SetPlayingCard.h"
#import "SetPlayingCardDeck.h"
#import "ThreeCardMatchGame.h"

@interface SetMatchingGame : ThreeCardMatchGame

- (void)compareThreeCards: (SetPlayingCard *)card withtwootherCards:
(NSArray *)otherCards;

@property (readonly, nonatomic) NSInteger score;
@property (readonly, nonatomic) NSUInteger matchScore;
@property (readonly, nonatomic) SetPlayingCard * firstsetcard;
@property (readonly, nonatomic) SetPlayingCard * secondsetcard;
@property (readonly, nonatomic) SetPlayingCard * thirdsetcard;
@property (readonly, nonatomic) NSString *statustext;

@end
