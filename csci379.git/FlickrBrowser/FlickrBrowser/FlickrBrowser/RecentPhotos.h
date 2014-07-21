//
//  RecentPhotos.h
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 3/26/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  This class holds the last 20 photos viewed by the user. The recent content
//  persist by saving it to userdefaults.

#import <Foundation/Foundation.h>

@interface RecentPhotos : NSObject

+ (NSArray *)getRecentPhotos;
+ (void)addPhoto:(NSDictionary *)photo;

@end
