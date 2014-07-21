//
//  CardGameViewController.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 1/29/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "CardGameViewController.h"
#import "CardMatchingGame.h"
#import "PlayingCard.h"
#import "PlayingCardDeck.h"
#import "PlayingCardCollectionViewCell.h"
#import "CardGameViewController_Protected.h"


@interface CardGameViewController ()
@property (weak, nonatomic) IBOutlet UILabel *scoreLabel;
@property (weak, nonatomic) IBOutlet UILabel *statusLabel;

@end

@implementation CardGameViewController

//
// Initializes the model.
//
- (void)viewDidLoad {
    [super viewDidLoad];
    self.statusLabel.text = [NSString stringWithFormat:
                             @"Welcome to the card matching game."];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//
// Returns the number of cards in the game.
//
- (NSUInteger)startingCardCount {
    return 22;
}

//
// Creates a new deck of cards.
//
- (Deck *)createDeck {
    return [[PlayingCardDeck alloc] init];
}


//
// Updates the cell with the current properties of the playing card.
//
- (void)updateCell:(UICollectionViewCell *)cell usingCard:(Card *)card {
    PlayingCardView *playingCardView =
                ((PlayingCardCollectionViewCell *)cell).playingCardView;
    PlayingCard *playingCard = (PlayingCard *)card;
    playingCardView.rank = playingCard.rank;
    playingCardView.suit = playingCard.suit;
    playingCardView.faceUp = playingCard.isFaceUp;
    playingCardView.alpha = playingCard.isUnplayable ? 0.3 : 1.0;
}

//
// Creates a cell for the specified index path and updates it.
//
- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView
                  cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    UICollectionViewCell *cell = [collectionView
                        dequeueReusableCellWithReuseIdentifier:@"PlayingCard"
                                  forIndexPath:indexPath];
    Card *card = [self.game cardAtIndex:indexPath.item];
    [self updateCell:cell usingCard:card];
    return cell;
}

//
// Starts a new game by dealing the cards, setting the flip count to 0 and
// updating the UI.
//
- (void)startNewGame {
    self.game = [[CardMatchingGame alloc] initWithCardCount:self.startingCardCount
                                                  usingDeck:[self createDeck]];
    [super startNewGame];
}


@end
