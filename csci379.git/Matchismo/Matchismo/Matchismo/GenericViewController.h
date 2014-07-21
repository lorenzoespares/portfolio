//
//  GenericViewController.h
//  Matchismo
//
//  Created by Lorenzo O. Espares on 2/23/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
// This class is the superclass of the other two view controllers.
//

#import <UIKit/UIKit.h>
#import "Deck.h"

@interface GenericViewController : UIViewController

- (IBAction)redeal:(id)sender;
- (void)setFlipsText;
- (void)setScoreText;
- (void)updateUI;

@property (readwrite, nonatomic) NSInteger currentCardCount;

@end
