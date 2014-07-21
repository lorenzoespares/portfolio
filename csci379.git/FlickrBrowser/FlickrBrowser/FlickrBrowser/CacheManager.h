//
//  CacheManager.h
//  FlickrBrowser
//
//  Created by Lorenzo O. Espares on 4/8/14.
//  Copyright (c) 2014 Lorenzo O. Espares. All rights reserved.
//
//  Manages the Cache to be used to store recently accessed images.
//

#import <Foundation/Foundation.h>

@interface CacheManager : NSObject

@property (retain, nonatomic)NSCache *cache;

+(CacheManager *)sharedInstance;
-(void)setCache:(id)obj forKey:(NSString *)key;
-(id)getCacheForKey:(NSString *)key;


@end
