//
//  SetMatchingGame.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/19/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "SetMatchingGame.h"

static const NSUInteger matchBonus = 3;

@interface SetMatchingGame()
@property (readwrite, nonatomic) NSInteger score;
@property (readwrite, nonatomic) NSUInteger matchScore;
@property (readwrite, nonatomic) SetPlayingCard * firstsetcard;
@property (readwrite, nonatomic) SetPlayingCard * secondsetcard;
@property (readwrite, nonatomic) SetPlayingCard * thirdsetcard;
@property (readwrite, nonatomic) NSString *statustext;


@end

@implementation SetMatchingGame

//
// Overridden inherited method from ThreeCardMatchingGame. The logic and
// functionality is the same, except that this method has been tailored to
// compare SetPlayingCards.
//
- (void)compareThreeCards: (SetPlayingCard *)card withtwootherCards:
(NSArray *)otherCards{
    SetPlayingCard *firstcard = [otherCards firstObject];
    SetPlayingCard *secondcard = [otherCards lastObject];
    if (firstcard.isFaceUp && !firstcard.isUnplayable) {
        if (secondcard.isFaceUp && !secondcard.isUnplayable) {
            self.firstsetcard = card;
            self.secondsetcard = firstcard;
            self.thirdsetcard = secondcard;
            
            self.matchScore = [card matchset:otherCards];
            if (self.matchScore != 0) {
                card.unplayable = YES;
                firstcard.unplayable = YES;
                secondcard.unplayable = YES;
                [self.cards removeObject:card];
                [self.cards removeObject:firstcard];
                [self.cards removeObject:secondcard];

                super.matched = 1;
                self.statustext = @"Set Matched for 3 points!";
                // set matched to 1 to display "Matched... for 4 point"
                // in view controller
                
                NSUInteger newscore = self.matchScore * matchBonus;
                self.score = self.score + newscore;

            } else {
                card.faceUp = !card.isFaceUp;
                firstcard.faceUp = NO;
                secondcard.faceUp = NO;
                super.matched = 2;
                self.statustext = @"Not a Set!";
                // set matched to 2 to display "Do not match, 2 point penalty"
                // in view controller
                
            }
        }
    }
}

//
// Overridden inherited method that has been tailored to flip SetPlayingCards.
//
- (void)flipCardAtIndex:(NSUInteger)index{
    Card *c = [self cardAtIndex:index];
    SetPlayingCard *card = (SetPlayingCard *)c;
    if (self.threecardcount == 0) {
        self.othertwocards = [[NSMutableArray alloc]init];
    }
    if (card != nil && !card.isUnplayable) {
        if (!card.isFaceUp) {
            
            self.matched = 0;
            self.statustext = @"Flipped up.";
            // set matched to 0 to display "Flipped card" in UpdateUI
            // in view controller
            
            if (self.threecardcount == 2) {
                [self compareThreeCards:card withtwootherCards:
                 self.othertwocards];
                self.threecardcount = 0;
            } else {
                [self.othertwocards insertObject:card atIndex:
                 self.threecardcount];
                self.threecardcount++;
            }

        }
        card.faceUp = !card.isFaceUp;
    }
    
}

@end
