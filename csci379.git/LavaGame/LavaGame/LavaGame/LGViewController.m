//
//  LGViewController.m
//  LavaGame
//
//  Created by Lorenzo O. Espares on 5/5/14.
//  Copyright (c) 2014 bucknell.edu. All rights reserved.
//

@import AVFoundation;
#import "LGViewController.h"
#import "LavaGame.h"
#import "Tile.h"
#import "TilePile.h"
#import "TileCollectionViewCell.h"
#import "StatusView.h"

@interface LGViewController () <UICollectionViewDataSource>
@property (strong, nonatomic) AVAudioSession *audioSession;
@property (strong, nonatomic) AVAudioPlayer *audioplayer;

@property (weak, nonatomic) IBOutlet UICollectionView *tileCollectionView;
@property (weak, nonatomic) IBOutlet UIView *statusview;
@property (weak, nonatomic) IBOutlet UILabel *timerlabel;
@property (weak, nonatomic) IBOutlet UIButton *replay;
@property (weak, nonatomic) IBOutlet UIButton *mainmenu;
@property (strong, nonatomic) NSTimer *timer;
@property (strong, nonatomic) NSDate *startDate;

@end

@implementation LGViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self startNewGame];
    
    self.tileCollectionView.scrollEnabled = NO;
    [_statusview setHidden:YES];
    
    self.audioSession = [AVAudioSession sharedInstance];

}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//
// Returns the number of tiles in the game.
//
- (NSUInteger)startingTileCount {
    return 212;
}

//
// Returns the number of items in this section.
//
- (NSInteger)collectionView:(UICollectionView *)collectionView
     numberOfItemsInSection:(NSInteger)section
{
    return self.startingTileCount;
}

//
// Creates a cell for the specified index path and updates it based on the type
// of the tile.
//
- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView
                  cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    UICollectionViewCell *cell = [collectionView
                                  dequeueReusableCellWithReuseIdentifier:@"TileCell"
                                  forIndexPath:indexPath];
    Tile *tile = [self.game tileAtIndex:indexPath.item];
    [self updateCell:cell usingTile:tile];
    return cell;
}

//
// Updates the cell with the current properties of the tile.
//
- (void)updateCell:(UICollectionViewCell *)cell usingTile:(Tile *)tile{
    TileView *tileView =
    ((TileCollectionViewCell *)cell).tileview;
    tileView.tiletype = tile.tiletype;
}

//
// Updates the view based on the current properties of the game.
//
- (void)updateView:(UIView *)view{
    StatusView *newview = (StatusView *)view;
    newview.status = self.game.state;
}

//
// Updates the user interface to reflect the current state of the model.  Also
// updates the views, buttons, and labels displayed.
//
- (void)updateUI {
    if(self.game.state != nil){
        [self updateView:self.statusview];
        if(![self.game.state isEqual:@"continue"]){
            [self.statusview setHidden:NO];
            [self.view bringSubviewToFront:self.statusview];
            [self.view bringSubviewToFront:self.timerlabel];
            [_replay setHidden:NO];
            [_mainmenu setHidden:NO];
            if ([self.game.state isEqual:@"win"]) {
                [self configureAudioPlayer: @"win"];
                [self.audioplayer setVolume:2.0];
                [self.audioplayer prepareToPlay];
                [self.audioplayer play];
            } else if ([self.game.state isEqual:@"gameover"]) {
                [self configureAudioPlayer: @"death"];
                self.timerlabel.text = @"DEAD";
                [self.audioplayer prepareToPlay];
                [self.audioplayer play];
            }
            self.currenttile = 0;
        }
    }
}

//
// Performs actions depending on tile selected. If the tile is a floor tile, the
// screen scrolls up and a sound is played. After a tile is selected, updateUI
// is called.
//
- (IBAction)selectTile:(UITapGestureRecognizer *)tap{
    CGPoint tapLocation = [tap locationInView:self.tileCollectionView];
    NSIndexPath *path = [self.tileCollectionView
                         indexPathForItemAtPoint:tapLocation];
    if (path != nil && (path.item >= self.currenttile) &&
        [self.game.state isEqual: @"continue"]){
        self.game.numtiles++;
        Tile *tile = [self.game tileAtIndex:path.item];
        [self.game updatewithTileAtIndex:path.item];
        if ([tile.tiletype isEqual: @"floor"]){
            [self configureAudioPlayer: @"pewpew"];
            [self.audioplayer prepareToPlay];
            [self.audioplayer play];
            NSIndexPath *nextIndexPath = [NSIndexPath indexPathForItem:
                                          (self.currenttile - 1) inSection:0];
            [self.tileCollectionView scrollToItemAtIndexPath: nextIndexPath
                                            atScrollPosition:UICollectionViewScrollPositionBottom
                                                    animated:YES];
            self.currenttile -= 4;
            [self timerTick:_timer];
        }
        [self updateUI];
    }
}

//
// Starts a new game by creating a new pile of tiles, resetting the timerlabel
// and reference date, redrawing the tiles, scrolling to the bottom of the
// screen, and hiding views, buttons, and labels.
//
- (void)startNewGame {
    self.timerlabel.text = @"00.000";
    _startDate = [NSDate date];
    self.game = [[LavaGame alloc] initWithTileCount:self.startingTileCount
                                          usingPile:[self getnewtiles]];
    self.currenttile = self.startingTileCount - 4;
    for (UICollectionViewCell *cell in [self.tileCollectionView visibleCells]) {
        NSIndexPath *indexPath = [self.tileCollectionView indexPathForCell:cell];
        Tile* tile = [self.game tileAtIndex:indexPath.item];
        
        [self updateCell:cell usingTile:tile];
        [self.tileCollectionView reloadData];
    }
    NSIndexPath *lastIndexPath = [NSIndexPath indexPathForItem:
                                  (self.startingTileCount - 1) inSection:0];
    NSLog(@"%@", lastIndexPath);
    [self.tileCollectionView scrollToItemAtIndexPath: lastIndexPath
                                    atScrollPosition:UICollectionViewScrollPositionBottom
                                            animated:YES];
    [self.view sendSubviewToBack:self.statusview];
    [self.view sendSubviewToBack:self.timerlabel];
    [_replay setHidden:YES];
    [_mainmenu setHidden:YES];
    _timer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self
                                            selector:@selector(timerTick:) userInfo:nil repeats:NO];
}

//
// Restarts the game by calling startNewGame.
//
-(IBAction)replay:(id)sender{
    [self startNewGame];
}

//
// Selector method which gets called after a certain interval of the timer.
//
- (void)timerTick:(NSTimer *)timer {
    NSDate *currentDate = [NSDate date];
    NSTimeInterval timeInterval = [currentDate timeIntervalSinceDate:_startDate];
    NSDate *timerDate = [NSDate dateWithTimeIntervalSince1970:timeInterval];
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"ss.SSS"];
    [dateFormatter setTimeZone:[NSTimeZone timeZoneForSecondsFromGMT:0.0]];
    self.timerlabel.text = [dateFormatter stringFromDate:timerDate];
}

//
// Creates a new pile of tiles.
//
- (TilePile *)getnewtiles {
    return [[TilePile alloc] init];
}

// Create audio player with background music with specified filename.

- (void)configureAudioPlayer:(NSString *)filename {
    NSString *audiopath = [[NSBundle mainBundle] pathForResource:filename
                                                          ofType:@"caf"];
    NSURL *backgroundMusicURL = [NSURL fileURLWithPath:audiopath];
    self.audioplayer = [[AVAudioPlayer alloc] initWithContentsOfURL:
                        backgroundMusicURL error:nil];
}

@end
