//
//  GenericViewController.m
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/23/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//

#import "GenericViewController.h"

#import "CardMatchingGame.h"
//#import "TwoCardMatchGame.h"
//#import "ThreeCardMatchGame.h"
#import "SetMatchingGame.h"
#import "CardGameViewController_Protected.h"

@interface GenericViewController () <UICollectionViewDataSource>
@property (weak, nonatomic) IBOutlet UILabel * flipsLabel;
@property (nonatomic) NSUInteger flipCount;
//@property (strong, nonatomic) IBOutletCollection(UIButton) NSArray *cardButtons;
@property (weak, nonatomic) IBOutlet UILabel *scoreLabel;
@property (weak, nonatomic) IBOutlet UILabel *statusLabel;
@property (weak, nonatomic) IBOutlet UIButton *deal;
@property (weak, nonatomic) IBOutlet UIButton *addSetCards;
@property (weak, nonatomic) IBOutlet UICollectionView *cardCollectionView;
@property (weak, nonatomic) IBOutlet UIView *firstSetView;
@property (weak, nonatomic) IBOutlet UIView *secondSetView;
@property (weak, nonatomic) IBOutlet UIView *thirdSetView;
@property (weak, nonatomic) Card *flippedcard;
@property (weak, nonatomic) NSMutableArray *tempArray;
@end

@implementation GenericViewController

//
// Initializes the model.
//
- (void)viewDidLoad {
    [super viewDidLoad];
    [self startNewGame];
}

//
// Reports the number of sections in the collection view.
//
- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}

//
// Returns the number of items in this section.
//
- (NSInteger)collectionView:(UICollectionView *)collectionView
     numberOfItemsInSection:(NSInteger)section
{
    //return self.startingCardCount;
    return self.currentCardCount;
}

//
// Updates the cell using the information from a card.  This is an abstract
// method.
//
- (void)updateCell:(UICollectionViewCell *)cell usingCard:(Card *)card {
}

//
// Creates a cell for the specified index path and updates it.  This is an
// abstract method.
//
- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView
                  cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    return nil;
}

//
// Starts a new game by dealing the cards, setting the flip count to 0 and
// updating the UI.
//
- (void)startNewGame {
    self.flipCount = 0;
    self.currentCardCount = self.startingCardCount;
    self.addSetCards.enabled = YES;
    self.addSetCards.alpha = 1.0;
    [self updateUI];
}

//
// Creates a new deck.  This is an abstract method that must be implemented in
// a subclass.
//
- (Deck *)createDeck {
	NSException *exception = [NSException exceptionWithName:
                              @"Abstract Method Not Overridden"
                            reason:@"You must override the createDeck method"
												   userInfo:nil];
	[exception raise];
    return nil;
}

//
// Updates the view using the information from a card.  This is an abstract
// method.
//
-(void)updateView:(UIView *)view usingCard:(Card *)card{
}

//
// Flips the card that was tapped and updates the flip count.
//
- (IBAction)flipCard:(UITapGestureRecognizer *)tap{
    CGPoint tapLocation = [tap locationInView:self.cardCollectionView];
    NSIndexPath *path = [self.cardCollectionView
                         indexPathForItemAtPoint:tapLocation];
    if (path != nil){
        self.flippedcard = [self.game cardAtIndex:path.item];
        [self.game flipCardAtIndex:path.item];
        self.flipCount++;
        [self updateUI];
    }
}

//
// Updates the user interface to reflect the current state of the model.  Also
// updates the flip count, the score and the result of the last flip. For the
// set game, this also displays the set cards selected.
//
- (void)updateUI {
    for (UICollectionViewCell *cell in [self.cardCollectionView visibleCells]) {
        NSIndexPath *indexPath = [self.cardCollectionView indexPathForCell:cell];
        Card *card = [self.game cardAtIndex:indexPath.item];
        if(self.game.matched == 1){
            self.currentCardCount-=3;
            [self.cardCollectionView reloadData];
            self.game.matched = 0;
        }
        [self updateCell:cell usingCard:card];
        [self.cardCollectionView reloadData];
    }

    self.flipsLabel.text = [NSString stringWithFormat:@"Flips: %d",
                            self.flipCount];
    self.scoreLabel.text = [NSString stringWithFormat:@"Score: %d",
                            self.game.score];
    if(self.game.matched == 0 && ![self.game isKindOfClass:
                                   [SetMatchingGame class]]) {
        self.statusLabel.text = [[NSString stringWithFormat:@"Flipped up %@",
                                  self.flippedcard]description];
    } else {
        if (self.game.threecardcount == 1){
            [self updateView:self.firstSetView usingCard:self.flippedcard];
            [self updateView:self.secondSetView usingCard:nil];
            [self updateView:self.thirdSetView usingCard:nil];
        }
        else if (self.game.threecardcount == 2)
            [self updateView:self.secondSetView usingCard:self.flippedcard];
        else if (self.game.threecardcount == 0)
            [self updateView:self.thirdSetView usingCard:self.flippedcard];
        self.statusLabel.text = self.game.statustext;
    }
}

// Redeals the deck and effectively resets the game by starting a new game.
- (IBAction)redeal:(id)sender {
    [self viewDidLoad];
}

//
// Adds 3 more set cards if the user can't find a set match. The view
// automatically scrolls down to the last added card.
//
- (IBAction)addSetCards:(UIButton *)sender {
    for (int i = 0; i < 3; i++) {
        Card *card = [self.game.deck drawRandomCard];
        if(card != nil)
            [self.game.cards addObject:card];
        else{
            self.statusLabel.text = @"There are no more cards in the deck.";
            sender.enabled = NO;
            sender.alpha = 0.3;
        }
        self.currentCardCount++;
    }
    [self updateUI];
    NSIndexPath *lastIndexPath = [NSIndexPath indexPathForItem:
                                  (self.currentCardCount-1) inSection:0];
    [self.cardCollectionView scrollToItemAtIndexPath: lastIndexPath
                           atScrollPosition:UICollectionViewScrollPositionBottom
                                            animated:YES];
}

// Updates the number of flips displayed.
- (void)setFlipsText {
    self.flipsLabel.text = [NSString stringWithFormat:@"Flips: %lu",
                            (unsigned long)self.flipCount];
}

// Updates the score displayed.
- (void)setScoreText {
    self.scoreLabel.text = [NSString stringWithFormat:@"Score: %ld",
                            (long)self.game.score];
}

@end