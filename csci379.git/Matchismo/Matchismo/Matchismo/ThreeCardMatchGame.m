//
//  ThreeCardMatchGame.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/19/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "ThreeCardMatchGame.h"



@interface ThreeCardMatchGame()
@property (readwrite, nonatomic) NSUInteger matchBonus;
@property (readwrite, nonatomic) NSUInteger flipCost;
@property (readwrite, nonatomic) NSUInteger mismatchPenalty;
@end

@implementation ThreeCardMatchGame

//
// Compares a card to the other cards. For a three card matching game, the
// otherCards array contains two other cards. Checks if the two other cards
// are face up.  Compares the cards and adjusts the score.  If there's no
// match, turns the other card face down and reduces the score by the mismatch
// penalty.  If there's a match, card and two other cards become unplayable.
// Increases the score according to the type of match.  If there's no face up
// card, nothing happens.
- (void)compareThreeCards: (Card *)card withtwootherCards:
(NSArray *)otherCards{
    PlayingCard *firstcard = [otherCards firstObject];
    PlayingCard *secondcard = [otherCards lastObject];
    NSUInteger currentscore = [super getscore];
    if (firstcard.isFaceUp && !firstcard.isUnplayable) {
        if (secondcard.isFaceUp && !secondcard.isUnplayable) {
            self.firstcard = [card description];
            self.secondcard = [firstcard description];
            self.thirdcard = [secondcard description];
            
            [super setMatchscore:[card match:otherCards]];
            if (self.matchScore != 0) {
                card.unplayable = YES;
                firstcard.unplayable = YES;
                secondcard.unplayable = YES;
                super.matched = 1;
                // set matched to 1 to display "Matched... for 4 point"
                // in view controller
                
                NSUInteger score = [super getMatchscore] * self.matchBonus;
                [super setscore:(currentscore + score)];
            } else {
                card.faceUp = !card.isFaceUp;
                firstcard.faceUp = NO;
                secondcard.faceUp = NO;
                super.matched = 2;
                // set matched to 2 to display "Do not match, 2 point penalty"
                // in view controller
                
                [super setscore:(currentscore - self.mismatchPenalty)];
            }
        }
    }
}

//
// Flips the card at the given index. Each card flipped is stored in a mutable
// array, which allows for comparison of more than 2 cards. The first two cards
// flipped are stored in the array. The third card flipped is compared to the
// other two cards to find a match or not. Adjusts the score accordingly.
//
- (void)flipCardAtIndex:(NSUInteger)index{
    Card *card = [self cardAtIndex:index];
    NSUInteger currentscore = [super getscore];
    if (self.threecardcount == 0) {
        self.othertwocards = [[NSMutableArray alloc]init];
    }
    if (card != nil && !card.isUnplayable) {
        if (!card.isFaceUp) {
            
            self.matched = 0;
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
            
            [super setscore:(currentscore - self.flipCost)];
        }
        card.faceUp = !card.isFaceUp;
    }
    
}

// sets the flipCost.
//- (void)setFlipCost:(NSUInteger)cost {
//    self.flipCost = cost;
//}



@end

