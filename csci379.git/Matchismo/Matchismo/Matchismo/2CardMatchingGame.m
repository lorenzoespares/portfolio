//
//  2CardMatchingGame.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/19/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "2CardMatchingGame.h"

@implementation _CardMatchingGame

//
// Compares card to the other card.  Card is face down.  Looks through the
// other cards until it finds one that's face up.  Compares the cards and
// adjusts the score.  If there's no match, turns the other card face down and
// reduces the score by the mismatch penalty.  If there's a match, card and the
// other card become unplayable.  Increases the score according to the type of
// match.  If there's no face up card, nothing happens.
//
- (void)compareOtherFaceUpPlayableCardTo:(Card *)card {
    [super compareOtherFaceUpPlayableCardTo: card];
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

@end
