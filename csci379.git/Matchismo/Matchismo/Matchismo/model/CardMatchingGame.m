//
//  CardMatchingGame.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/5/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "CardGameViewController.h"
#import "CardMatchingGame.h"

static const NSUInteger matchBonus = 4;
static const NSUInteger flipCost = 1;
static const NSUInteger mismatchPenalty = 2;

@interface CardMatchingGame ()
@property (readwrite, nonatomic) NSInteger score;
@property (readwrite, nonatomic) NSUInteger matchScore;
//@property (strong, nonatomic) NSMutableArray *cards;
@property (readwrite, nonatomic) NSInteger numcards;



@end

@implementation CardMatchingGame

//
// Initializes the cards we will be using with count cards from the deck.  If
// there are not enough cards to initialize, return nil.
//
- (instancetype)initWithCardCount:(NSUInteger)count usingDeck:(Deck *)deck
{
    self = [super init];
    self.deck = deck;
    if (self != nil) {
        _cards = [[NSMutableArray alloc] init];
        for (NSUInteger i = 0; i < count; i++) {
            Card *card = [deck drawRandomCard];
            if (card != nil)
                _cards[i] = card;
            else {
                self = nil;
                break;
            }
        }
    }
    return self;
}

//
// Returns the card at the specified index.  If the index is out of range,
// return nil.
//
- (Card *)cardAtIndex:(NSUInteger)index {
    return index < [self.cards count] ? self.cards[index] : nil;
}

//
// Compares card to the other card.  Card is face down.  Looks through the
// other cards until it finds one that's face up.  Compares the cards and
// adjusts the score.  If there's no match, turns the other card face down and
// reduces the score by the mismatch penalty.  If there's a match, card and the
// other card become unplayable.  Increases the score according to the type of
// match.  If there's no face up card, nothing happens.
//
- (void)compareOtherFaceUpPlayableCardTo:(Card *)card {
    for (Card *otherCard in self.cards) {
        if (otherCard.isFaceUp && !otherCard.isUnplayable) {
            //set card contents to defined properties
            self.firstcard = [card description];
            self.secondcard = [otherCard description];
            
            self.matchScore = [card match:@[otherCard]];
            if (self.matchScore != 0) {
                card.unplayable = YES;
                otherCard.unplayable = YES;
                self.matched = 1;
                // set matched to 1 to display "Matched... for 4 point"
                // in view controller
                
                NSInteger points = self.matchScore * matchBonus;
                self.score += points;
                self.statustext = [NSString stringWithFormat:
                                   @"Matched %1$@ & %2$@ for %3$ld points",
                                   _firstcard, _secondcard, (long)points];
                
            } else {
                otherCard.faceUp = NO;
                self.matched = 2;
                // set matched to 2 to display "Do not match, 2 point penalty"
                // in view controller
                
                self.statustext = [NSString stringWithFormat:
                                   @"%1$@ and %2$@ don't match! 2 point penalty",
                                   _secondcard, _firstcard];
                self.score -= mismatchPenalty;
            }
            break;
        }
    }
}

//
// Flips the card at the given index.  If the card was face down, searches the
// other cards looking for one that's face up (and playable) and compares them.
// Adjusts the score accordingly.
//
- (void)flipCardAtIndex:(NSUInteger)index {
    self.numcards++;
    Card *card = [self cardAtIndex:index];
    if (card != nil && !card.isUnplayable) {
        if (!card.isFaceUp) {
            
            self.matched = 0;
            // set matched to 0 to display "Flipped card" in UpdateUI
            // in view controller

            [self compareOtherFaceUpPlayableCardTo:card];
            self.score -= flipCost;
        }
        card.faceUp = !card.isFaceUp;
    }
}


// resets the score to 0.
- (void)resetscore {
    self.score = 0;
}

// sets the score.
- (void)setscore:(NSUInteger)score {
    self.score = score;
}

// gets the score.
- (NSUInteger)getscore {
    return self.score;
}

// sets the match score.
- (void)setMatchscore:(NSUInteger)score {
    self.matchScore = score;
}

// gets the match score.
- (NSUInteger)getMatchscore {
    return self.matchScore;
}


@end
