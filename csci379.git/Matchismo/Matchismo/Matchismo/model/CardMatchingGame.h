//
//  CardMatchingGame.h
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/5/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  A class that takes care of the logic for the card matching game. 

#import <Foundation/Foundation.h>
#import "Deck.h"
#import "PlayingCard.h"

@interface CardMatchingGame : NSObject

- (instancetype)initWithCardCount:(NSUInteger)count
                        usingDeck:(Deck *)deck;
- (void)flipCardAtIndex:(NSUInteger)index;
- (Card *)cardAtIndex:(NSUInteger)index;

- (void)resetscore;
- (void)setscore:(NSUInteger)score;
- (NSUInteger)getscore;
- (void)setMatchscore:(NSUInteger)score;
- (NSUInteger)getMatchscore;


@property (readonly, nonatomic) NSInteger score;
@property (readwrite, nonatomic) NSInteger matched;
@property (readwrite, nonatomic) NSString * firstcard;
@property (readwrite, nonatomic) NSString * secondcard;
@property (readwrite, nonatomic) NSString * thirdcard;
@property (readonly, nonatomic) NSUInteger matchScore;
@property (readwrite, nonatomic) NSMutableArray *cards;
@property (readwrite, nonatomic) NSInteger threecardcount;

@property (strong, nonatomic) Deck *deck;
@property (readwrite, nonatomic) NSString *statustext;

@end
